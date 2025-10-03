/**
 *  \file IMP/insulinsecretion/InsulinSecretionOptimizerState.h
 *  \brief An optimizer detects the docking state of insulin vesicles and increments it by 1. 
 *         When this value exceeds the ready_state, it updates the SecretionCounter decorator 
 *         and randomly resets the insulin vesicles near the nucleus.
 *
 * Description:
 * 1. Get optimizer state for each frame of the trajectory (insulin vesicles).
 * 3. Check all vesicles for their maturation state decorator, and add 1 to the decorator.
 * 4. When the docking state exceeds the ready_state, update the secretion counter decorator.
 * 5. Resets the vesicle positions randomly within a cut-off near the nucleus without overlapping
 *    with any other organelles. Reset the MaturationState and DockingStatedecorator for vesicles to 0.
 * 6. Update the optimizer state.
 *
 *
 *  Copyright 2007-2019 IMP Inventors. All rights reserved.
 */

#include <IMP/insulinsecretion/InsulinSecretionOptimizerState.h>
#include <IMP/core.h>
#include <IMP/algebra/Transformation3D.h>
#include <IMP/algebra/ReferenceFrame3D.h>
#include <IMP/atom/Hierarchy.h>
#include <algorithm>
#include <limits>

IMPINSULINSECRETION_BEGIN_NAMESPACE

//! for the definition of the optimizer state
InsulinSecretionOptimizerState::InsulinSecretionOptimizerState
( Model *m,
  ParticleIndexesAdaptor vesicles,
  algebra::Sphere3D nucleus_sphere,
  int ready_state,
  double cut_off,
  unsigned int periodicity)
  : P(m, "InsulinSecretionOptimizerState%1%"),
  nucleus_sphere_(nucleus_sphere),
  ready_state_(ready_state),
  periodicity_(periodicity),
  cut_off_(cut_off)
{
  IMP_OBJECT_LOG;
  set_period(periodicity);
  for(ParticleIndex pi : vesicles) {
    vesicles_.push_back(m->get_particle(pi));
  }
}

//! update the optimizer state
void InsulinSecretionOptimizerState::do_update
( unsigned int call_num) {
  IMP_OBJECT_LOG;
  count_secretion();                         
}

//! update the secretion counter decorator
void InsulinSecretionOptimizerState::count_secretion() {
  set_was_used(true);
  //double occupancy ; // occupancy = number of bound patches / total number of patches
  Model* m= get_model();
  for (Particles::const_iterator pi = vesicles_.begin(); pi != vesicles_.end();++pi){
    Particle *p = *pi;
    int state = insulinsecretion::MaturationStateDecorator(p).get_state(); // get the maturation state
    insulinsecretion::MaturationStateDecorator(p).set_state(state+1);
    int dstate = insulinsecretion::DockingStateDecorator(p).get_dstate(); 
    if (dstate == -1){
      insulinsecretion::DockingStateDecorator(p).set_dstate(1); // for each optimizer state, vesicle gains one maturation state.
    }
    else if (dstate == ready_state_){
      int counter = insulinsecretion::SecretionCounterDecorator(p).get_secretion();
      insulinsecretion::SecretionCounterDecorator(p).set_secretion(counter+1); // the count of secretion evens is +1
      insulinsecretion::MaturationStateDecorator(p).set_state(0); // reset to the imature state
      insulinsecretion::DockingStateDecorator(p).set_dstate(0);
      do_reset(p -> get_index());
    }
    else if (dstate >= 1 && dstate < ready_state_){
      insulinsecretion::DockingStateDecorator(p).set_dstate(dstate+1); // for each optimizer state, vesicle gains one maturation state.
    }
    else if (dstate > ready_state_){
      std::cerr << "Error: Incorrect docking state of insulin vesicless." << std::endl;
      exit(1);
    }
  }
}

//! Reser insulin vesicles
void InsulinSecretionOptimizerState::do_reset(ParticleIndex pi) 
{
  Model* m= get_model();
  IMP_FUNCTION_LOG;
  IMP_LOG_TERSE("Reseting: " << get_particle(m, pi)->get_name() << std::endl);
  IMP_UNUSED(pi);     
  core::XYZR xyzr0(m, pi); // granule
  algebra::Sphere3D near_nucleus = algebra::Sphere3D(nucleus_sphere_.get_center(), 
                                                   nucleus_sphere_.get_radius() + cut_off_ - xyzr0.get_radius());
  algebra::Vector3D v2 = get_random_vector_in(near_nucleus, xyzr0);
  xyzr0.set_coordinates(v2); // reset the insulin vesicles
  xyzr0.set_coordinates_are_optimized(true);
}

//! reset the position of vesicles
algebra::Vector3D InsulinSecretionOptimizerState::get_random_vector_in(algebra::Sphere3D sphere,
                                                                        core::XYZR xyzr) const {
  IMP_FUNCTION_LOG;
  IMP_LOG_TERSE("Searching for the a random vector to reset" << std::endl);
  //set_was_used(true);
  //double occupancy ; // occupancy = number of bound patches / total number of patches
  Model* m= get_model(); 
  int i = 1;                                                         
  while (i > 0) {
    algebra::Vector3D random_vector = algebra::get_random_vector_in(sphere);
    algebra::Vector3D new_v_from_origin= (random_vector - nucleus_sphere_.get_center());
    double new_d_from_origin= new_v_from_origin.get_magnitude();
    if (new_d_from_origin > nucleus_sphere_.get_radius() + xyzr.get_radius()){
      bool overlap1 = false;
      for (Particles::const_iterator pi = vesicles_.begin(); pi != vesicles_.end();++pi){
        Particle *p = *pi;
        core::XYZR xyzr0(p); // vesicle  
        double distance1 = (random_vector - xyzr0.get_coordinates()).get_magnitude();
        if (distance1 <= xyzr.get_radius() + xyzr0.get_radius()){
          overlap1 = true;
          break;
        }
      }
      if(overlap1 == false){
        IMP_LOG_TERSE("Searched"<< i << "for the a random vector to reset" << std::endl);
        return random_vector;
        break;
      }
    }
    i++;
  }
}


IMPINSULINSECRETION_END_NAMESPACE
