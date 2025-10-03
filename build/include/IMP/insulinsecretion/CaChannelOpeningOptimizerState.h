/**
 *  \file IMP/insulinsecretion/CaChannelOpeningOptimizerState.h
 *  \brief An optimizer state that updates the open/closed state of Ca2+ channles. 
 *
 * Description:
 * 1, Get optimizer state for each frame of the trajectory (CaChannel).
 * 2, Set the binary state parameter (i.e., 0 or 1) for a subset of Ca2+ channels.
 * 3, Update the optimizer state.
 *
 *
 *  Copyright 2007-2019 IMP Inventors. All rights reserved.
 */

#ifndef IMPINSULINSECRETION_CaCHANNEL_OPENING_OPTIMIZER_STATE_H 
#define IMPINSULINSECRETION_CaCHANNEL_OPENING_OPTIMIZER_STATE_H

#include <IMP/insulinsecretion/insulinsecretion_config.h> // provide macros to mark functions and classes as exported and to set up namespaces
#include <IMP/insulinsecretion/CaChannelStateDecorator.h>
#include <IMP/OptimizerState.h> // an owning Optimizer commits to a new set of coordinates
#include <IMP/core/PeriodicOptimizerState.h>

IMPINSULINSECRETION_BEGIN_NAMESPACE

/**
   An optimizer state that updates the open/closed of Ca2+ channles. 
 */

class IMPINSULINSECRETIONEXPORT CaChannelOpeningOptimizerState
: public core::PeriodicOptimizerState 
{
 private:
   typedef core::PeriodicOptimizerState P; // define P as the member initializer
   Particles cachannel_; // Ca2+ channel
   int oscillation_;
   int troughn_; // the number of Ca2+ channels in the opening state at the trough
   int peakn_; // the number of Ca2+ channels in the opening state at the peak
   unsigned int periodicity_; // the frame interval

  //! update the secretion counter decorator
  void channel_oscillation(); 

 protected:
  //! Update the optimizer state.
  // The number of times this method has been called since the last reset or start of the optimization run is passed with call_num.
  virtual void do_update(unsigned int call_num) override; // Cause a compile error if this method does not override a parent method

 public:
  /**
     An optimizer state that updates the open/closed of Ca2+ channles. 

     @param cachannel Ca2+ channels
     @param troughn the number of Ca2+ channels in the opening state at the trough
     @param oscilation the opening state of Ca2+ channels to detect oscilation
     @param peakn the number of Ca2+ channels in the opening state at the peak
     @param periodicity the frame interval for updating this optimizer state
   */
  CaChannelOpeningOptimizerState
    ( Model *m,
      ParticleIndexesAdaptor cachannel,
      int oscillation,
      int troughn,
      int peakn,
      unsigned int periodicity = 1 );

  //! Set the particles to use.
  void set_cachannel(const Particles &cachannel) { cachannel_ = cachannel; }

  IMP_OBJECT_METHODS(CaChannelOpeningOptimizerState);
};

IMP_OBJECTS(CaChannelOpeningOptimizerState, CaChannelOpeningOptimizerStates);

IMPINSULINSECRETION_END_NAMESPACE

#endif /* IMPINSULINSECRETION_CaCHANNEL_OPENING_OPTIMIZER_STATE_H */
