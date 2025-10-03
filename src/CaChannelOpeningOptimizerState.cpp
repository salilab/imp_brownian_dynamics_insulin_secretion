/**
 *  \file IMP/insulinsecretion/CaChannelOpeningOptimizerState.cpp
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

#include <IMP/insulinsecretion/CaChannelOpeningOptimizerState.h>
#include <IMP/core.h>
#include <IMP/atom/Hierarchy.h>
#include <algorithm>
#include <limits>

IMPINSULINSECRETION_BEGIN_NAMESPACE

//! for the definition of the optimizer state
CaChannelOpeningOptimizerState::CaChannelOpeningOptimizerState
( Model *m,
  ParticleIndexesAdaptor cachannel,
  int oscillation,
  int troughn,
  int peakn,
  unsigned int periodicity)
  : P(m, "CaChannelOpeningOptimizerState%1%"),
  troughn_(troughn),
  peakn_(peakn),
  oscillation_(oscillation),
  periodicity_(periodicity)
{
  IMP_OBJECT_LOG;
  set_period(periodicity);
  for(ParticleIndex pi : cachannel) {
    cachannel_.push_back(m->get_particle(pi));
  }
}

//! update the optimizer state
void CaChannelOpeningOptimizerState::do_update
( unsigned int call_num) {
  IMP_OBJECT_LOG;
  channel_oscillation();
}

//! oscillating the voltage for the opening of Ca2+ channles
void CaChannelOpeningOptimizerState::channel_oscillation() {
  set_was_used(true);
  Model* m = get_model(); 
  int count = 0; 
  int totaln = cachannel_.size();
  bool found = false;
  for (Particles::const_iterator pi = cachannel_.begin(); pi != cachannel_.end();++pi){
    Particle *p = *pi;
    int channel_state = insulinsecretion::CaChannelStateDecorator(p).get_channelstate();
    if (channel_state == -1){
      ++count;
    }
    else if (channel_state == oscillation_){
      found = true;
    }
    else{
      insulinsecretion::CaChannelStateDecorator(p).set_channelstate(channel_state + 1);
    }
  }
  if (found == true){
    if (count == peakn_){
      int open_start = (totaln > troughn_ && troughn_ > 0) ? std::rand() % (totaln - troughn_) : 0;
      for (int pind = 0; pind < totaln; ++pind) {
        Particle *p = cachannel_[pind];
        insulinsecretion::CaChannelStateDecorator(p).set_channelstate(0);
      }
      if (troughn_ > 0) {
        for (int pind = open_start; pind < open_start + troughn_; ++pind) {
            Particle *p = cachannel_[pind];
            insulinsecretion::CaChannelStateDecorator(p).set_channelstate(-1);
        }
      }
    }
    else if (count == troughn_){
      int open_start = (totaln > peakn_ && peakn_ > 0) ? std::rand() % (totaln - peakn_) : 0;
      for (int pind = 0; pind < totaln; ++pind) {
        Particle *p = cachannel_[pind];
        insulinsecretion::CaChannelStateDecorator(p).set_channelstate(0);
      }
      for (int pind = open_start; pind < open_start + peakn_; ++pind){
        Particle *p = cachannel_[pind];
        insulinsecretion::CaChannelStateDecorator(p).set_channelstate(-1);
      }
    }
    else {
      std::cerr << "Error: Incorrect number of Ca2+ channels in the open state." << std::endl;
      exit(1);
    }
  }
}
IMPINSULINSECRETION_END_NAMESPACE