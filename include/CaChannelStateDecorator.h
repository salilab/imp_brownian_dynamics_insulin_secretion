/**
 *  \file IMP/insulinsecretion/CaChannelStateDecorator.h
 *  \brief Add a decorator to a Ca2+ channel to describe its open/closed state.
 *
 * Description:
 * 1, Set a decorator to describe the Ca2+ channel opening state.
 * 2, It is either 0 (i.e., closed) or 1 (i.e., open). 
 *
 *
 *  Copyright 2007-2019 IMP Inventors. All rights reserved.
 */

#ifndef IMPINSULINSECRETION_CaCHANNEL_STATE_DECORATOR_H
#define IMPINSULINSECRETION_CaCHANNEL_STATE_DECORATOR_H

#include <IMP/insulinsecretion/insulinsecretion_config.h>
#include <IMP/Decorator.h>
#include <IMP/decorator_macros.h>

IMPINSULINSECRETION_BEGIN_NAMESPACE
//TODO: add tester

//! Add a decorator to a Ca2+ channel to describe its open/closed state.
/** 
    1, Set a decorator to describe the Ca2+ channel opening state.
    2, It is either 0 (i.e., closed) or 1 (i.e., open).

    @param a binary state that describes whether it is open or closed.
 */   
class IMPINSULINSECRETIONEXPORT CaChannelStateDecorator
: public Decorator 
{
 //! Add an integer to the particle  
 // returns the value of the name attribute, or default_value if
 //the name attribute is missing
 static void do_setup_particle(Model *m, 
                               ParticleIndex pi,
                               int channelstate = 0) {
   m->add_attribute(get_channelstate_key(), pi, channelstate);
 }

 static void do_setup_particle(Model *m, ParticleIndex pi,
                                CaChannelStateDecorator o) {
   do_setup_particle(m, pi, o.get_channelstate());
 }

 public:
  static bool get_is_setup(Model *m, ParticleIndex pi) {
    return m->get_has_attribute(get_channelstate_key(), pi);
  }

  Int get_channelstate() const {
    return get_model()->get_attribute(get_channelstate_key(), get_particle_index());
  }

  void set_channelstate(Int d) { // TODO should be integer
    get_model()->set_attribute(get_channelstate_key(), get_particle_index(), d);
  }

  IMP_DECORATOR_METHODS(CaChannelStateDecorator, Decorator);
  IMP_DECORATOR_SETUP_1(CaChannelStateDecorator, Int, channelstate);
  IMP_DECORATOR_SETUP_1(CaChannelStateDecorator, CaChannelStateDecorator, other);
  /** Get the key used to store the state. */
  static IntKey get_channelstate_key();
};

IMPINSULINSECRETION_END_NAMESPACE

#endif /* IMPINSULINSECRETION_CaCHANNEL_STATE_DECORATOR_H */