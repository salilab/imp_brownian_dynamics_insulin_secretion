/**
 *  \file IMP/insulinsecretion/VesicleDockingOptimizerState.h
 *  \brief An optimizer state that docks the insulin vesicle when
 *         it is in the vicinty of Ca2+ channels in the open state. 
 *         When docked, the docking state decorator gets updated. 
 *
 * Description:
 * 1. Get the optimizer state for each frame of the trajectory (insulin vesicles and calcium channels).
 * 2. Docking occurs when the distance between the vesicle surface and Ca²⁺ channels is within the contact range plus a slack margin.
 * 3. Once docked, the calcium channels and insulin vesicles form a rigid body, and the docking state decorator is set to 1.
 * 4. The docking state increments by 1 for docked vesicles.
 * 5. Update the optimizer state.
 *
 *
 *  Copyright 2007-2019 IMP Inventors. All rights reserved.
 */

#include <IMP/insulinsecretion/VesicleDockingOptimizerState.h>
#include <IMP/core.h>
#include <IMP/algebra/Transformation3D.h>
#include <IMP/algebra/ReferenceFrame3D.h>
#include <IMP/atom/Hierarchy.h>
#include <algorithm>
#include <limits>
#include <IMP/core/rigid_bodies.h>

IMPINSULINSECRETION_BEGIN_NAMESPACE

//! for the definition of the optimizer state
VesicleDockingOptimizerState::VesicleDockingOptimizerState
( IMP::SingletonContainerAdaptor cachannel_container, // stores a shared collection of Singletons
  IMP::SingletonContainerAdaptor vesicles_container,
  double contact_range,
  double slack,
  int ready_state,
  unsigned int periodicity)
  : P(vesicles_container ? vesicles_container->get_model() :  nullptr, // store granules in NULL pointers, assign the pointer NULL to a pointer variable in case you do not have exact address to be assigned. 
    "VesicleDockingOptimizerState%1%"), // “%1%” is a replaced with a unique number, so multiple restraints will be named MyRestraint1, MyRestraint2, etc.
  ready_state_(ready_state),
  periodicity_(periodicity)
{
  IMP_OBJECT_LOG;
  set_period(periodicity);
  close_bipartite_pair_container_ =
    new IMP::container::CloseBipartitePairContainer // Return all spatially-proximals pairs of particles (a,b) from the two SingletonContainers A and B, where a is in A and b is in B. 
    ( vesicles_container,
      cachannel_container,
      contact_range,
      slack);
}

//! update the optimizer state
void VesicleDockingOptimizerState::do_update
( unsigned int call_num) 
{
  IMP_OBJECT_LOG;
  close_bipartite_pair_container_->do_score_state_before_evaluate();
  IMP_CONTAINER_FOREACH   // The macros take the name of the container and the operation to perform.                                
  (IMP::container::CloseBipartitePairContainer,
   close_bipartite_pair_container_,
   {
    ParticleIndexPair const& pip = _1;
    rigidify_pair(pip);         
   }
  );          
}

//! update the secretion counter decorator
void VesicleDockingOptimizerState::rigidify_pair
( ParticleIndexPair pip)
{
  set_was_used(true);
  //double occupancy ; // occupancy = number of bound patches / total number of patches
  Model* m= get_model();
  IMP_USAGE_CHECK(core::XYZR::get_is_setup(m, pip[0]),
                  "particles for rigidifications must be spheres as well");
  int dstate = insulinsecretion::DockingStateDecorator(m, pip[1]).get_dstate(); 
  core::RigidBody rb0= core::RigidBody(m, pip[0]);
  ParticleIndexes members = rb0.get_member_indexes(); 
  if (std::find(members.begin(), members.end(), pip[1]) != members.end()) {
    if (dstate == ready_state_){
      core::XYZR caxyzr(m, pip[0]); // granule
      double original_radius= caxyzr.get_radius();
      rb0.remove_member(pip[1]);
      caxyzr.set_radius(original_radius);
    }
  }
  else if (dstate == 0){
    int channelstate = insulinsecretion::CaChannelStateDecorator(m, pip[0]).get_channelstate();
    if (channelstate == -1){
      core::XYZR caxyzr(m, pip[0]); // granule
      core::XYZR xyzr(m, pip[1]); // glucose
      double original_radius= caxyzr.get_radius();
      rb0.add_member(pip[1]);
      caxyzr.set_radius(original_radius);
      xyzr.set_coordinates_are_optimized(false);
      insulinsecretion::DockingStateDecorator(m, pip[1]).set_dstate(-1);
    }
  }
}

IMPINSULINSECRETION_END_NAMESPACE
