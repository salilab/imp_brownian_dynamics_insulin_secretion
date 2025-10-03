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

#ifndef IMPINSULINSECRETION_VESICLE_DOCKING_OPTIMIZER_STATE_H
#define IMPINSULINSECRETION_VESICLE_DOCKING_OPTIMIZER_STATE_H

#include <IMP/insulinsecretion/insulinsecretion_config.h> 
#include <IMP/insulinsecretion/DockingStateDecorator.h>
#include <IMP/insulinsecretion/CaChannelStateDecorator.h>
#include <IMP/algebra/Transformation3D.h>
#include <IMP/algebra/ReferenceFrame3D.h>
#include <IMP/atom/Hierarchy.h>
#include <IMP/OptimizerState.h>
#include <algorithm>
#include <limits>
#include <IMP/SingletonContainer.h> // a container for Singletons
#include <IMP/container/CloseBipartitePairContainer.h>  // Return all spatially-proximals pairs of particles (a,b) from the two SingletonContainers

IMPINSULINSECRETION_BEGIN_NAMESPACE 

/**
   An optimizer state that docks the insulin vesicle when
   it is in the vicinty of Ca2+ channels in the open state. 
   When docked, the docking state decorator gets updated. 

 */
class IMPINSULINSECRETIONEXPORT VesicleDockingOptimizerState
: public OptimizerState 
{
 private:
   typedef OptimizerState P; // define P as the member initializer
   IMP::PointerMember<IMP::container::CloseBipartitePairContainer>
     close_bipartite_pair_container_; // maintains a list of nearby particle pairs in a bipartite graph
   int ready_state_;
   unsigned int periodicity_; // the framee interval

  //! rigidify the calcium channel and insulin vesicle upon docking
  void rigidify_pair(ParticleIndexPair pip);

 protected:
  //! Update the optimizer state.
  // The number of times this method has been called since the last reset or start of the optimization run is passed with call_num.
  virtual void do_update(unsigned int call_num) override; // Cause a compile error if this method does not override a parent method

 public:
  /**
      An optimizer state that docks the insulin vesicle when
      it is in the vicinty of Ca2+ channels in the open state. 
      When docked, the docking state decorator gets updated. 

     @param vesicles_container container of diffusing vesicles (which may change dynamically after construction)
     @param cachannel_container container of calcium channels on cell membrane (which may change dynamically after construction)
     @param contact_range the range of sphere distance in angstroms under which vesicles and cachannel will be tested for rigidification
     @param slack slack in angstroms for an IMP::container::CloseBipartitePairContainer object that tracks nearby vesicles and glucose
                  (affects running time - large slack may result in a longer list of pairs being tracked, up to contact_range+2*slack,
                  but the maintenance of CloseBipartitePairContainer may be faster). To increase the efficiency, the stored list actually 
                  includes all pairs that are closer than distance_cutoff + 2 * slack. This allows us to reuse the list and only recompute 
                  it when a particle moves more than slack.
     @param ready_state an integer defining the ready state of the docking state decorator
     @param periodicity the frame interval for updating this optimizer state
   */

  VesicleDockingOptimizerState
    ( IMP::SingletonContainerAdaptor vesicles_container,
      IMP::SingletonContainerAdaptor cachannel_container,
      double contact_range,
      double slack,
      int ready_state,
      unsigned int periodicity=1 );

  IMP_OBJECT_METHODS(VesicleDockingOptimizerState);
};

IMP_OBJECTS(VesicleDockingOptimizerState, VesicleDockingOptimizerStates);

IMPINSULINSECRETION_END_NAMESPACE

#endif /* IMPINSULINSECRETION_VESICLE_DOCKING_OPTIMIZER_STATE_H */
