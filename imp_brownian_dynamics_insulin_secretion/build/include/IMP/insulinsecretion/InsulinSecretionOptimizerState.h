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

#ifndef IMPINSULINSECRETION_INSULIN_SECRETION_OPTIMIZER_STATE_H
#define IMPINSULINSECRETION_INSULIN_SECRETION_OPTIMIZER_STATE_H

#include <IMP/insulinsecretion/insulinsecretion_config.h> 
#include <IMP/insulinsecretion/SecretionCounterDecorator.h>
#include <IMP/insulinsecretion/MaturationStateDecorator.h>
#include <IMP/algebra/Transformation3D.h>
#include <IMP/algebra/ReferenceFrame3D.h>
#include <IMP/atom/Hierarchy.h>
#include <IMP/OptimizerState.h>
#include <algorithm>
#include <limits>

IMPINSULINSECRETION_BEGIN_NAMESPACE 

/**
   An optimizer detects the docking state of insulin vesicles and increments it by 1. 
   When this value exceeds the ready_state, it updates the SecretionCounter decorator 
   and randomly resets the insulin vesicles near the nucleus.

 */
class IMPINSULINSECRETIONEXPORT InsulinSecretionOptimizerState
: public OptimizerState 
{
 private:
   typedef OptimizerState P; // define P as the member initializer
   Particles vesicles_;
   algebra::Sphere3D nucleus_sphere_;
   int ready_state_;
   double cut_off_; // cut-off for new locations where vesicles are reset
   unsigned int periodicity_; // the framee interval

  //! Secret insulin vesicles
  void count_secretion();

  //! Reset insulin vesicles
  void do_reset(ParticleIndex pi);

  //! get random vector in and without overlapping with particles
  algebra::Vector3D get_random_vector_in(algebra::Sphere3D sphere, core::XYZR xyzr) const;

 protected:
  //! Update the optimizer state.
  // The number of times this method has been called since the last reset or start of the optimization run is passed with call_num.
  virtual void do_update(unsigned int call_num) override; // Cause a compile error if this method does not override a parent method

 public:
  /**
      An An optimizer state that detects the collision of insulin 
      vesicles and periphery in the vicinty of Ca2+ channels in the open state. 
      When there is a collision, update the SecretionCounter 
      decorator and randomly resets the insulin vesicles near the nucleus.

     @param vesicles insulin vesicles
     @param nucleus_sphere, a sphere3D object which represents the nucleus
     @param ready_state an integer defining the ready state of the docking state decorator
     @param cut_off the cut-off from the NE surface to vesicle center to reset vesicles, it needs to be larger than 2*R_vesicleS, A
     @param periodicity the frame interval for updating this optimizer state
   */

  InsulinSecretionOptimizerState
    ( Model *m,
      ParticleIndexesAdaptor vesicles,
      algebra::Sphere3D nucleus_sphere,
      int ready_state,
      double cut_off,
      unsigned int periodicity=1 );
  
  //! sets the cut_off for resetting insulin vesicles after secretion
  //!in A
  void set_cut_off(double cut_off) 
  { cut_off_= cut_off; }

  //! returns the cut_off for resetting insulin vesicles after secretion
  //!in A
  double get_cut_off() const 
  { return cut_off_; }

  //! Set the particles to use.
  void set_vesicles(const Particles &vesicles) { vesicles_ = vesicles; }

  IMP_OBJECT_METHODS(InsulinSecretionOptimizerState);
};

IMP_OBJECTS(InsulinSecretionOptimizerState, InsulinSecretionOptimizerStates);

IMPINSULINSECRETION_END_NAMESPACE

#endif /* IMPINSULINSECRETION_INSULIN_SECRETION_OPTIMIZER_STATE_H */
