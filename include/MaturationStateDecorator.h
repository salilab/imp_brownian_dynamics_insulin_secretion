/**
 *  \file IMP/insulinsecretion/MaturationStateDecorator.h
 *  \brief Add a decorator to an insulin vesicle to describe its maturation state, 0 = imature, matured_state = mature.
 *
 * Description:
 * 1, Set a decorator to describe the maturation state of an insulin vesicle.
 * 2, It starts with zero.
 *
 *
 *  Copyright 2007-2019 IMP Inventors. All rights reserved.
 */

#ifndef IMPINSULINSECRETION_MATURATION_STATE_DECORATOR_H
#define IMPINSULINSECRETION_MATURATION_STATE_DECORATOR_H

#include <IMP/insulinsecretion/insulinsecretion_config.h>
#include <IMP/Decorator.h>
#include <IMP/decorator_macros.h>

IMPINSULINSECRETION_BEGIN_NAMESPACE
//TODO: add tester

//! A decorator to an insulin vesicle to describe its maturation state, 0 = imature, matured_state = mature.
/** 
    1, Set a decorator to describe the maturation state of an insulin vesicle.
    2, It starts with zero.
    @param state an integer that describes the maturation state.
*/
class IMPINSULINSECRETIONEXPORT MaturationStateDecorator
: public Decorator 
{
 //! Add an integer to the particle  
 // returns the value of the name attribute, or default_value if
 //the name attribute is missing
 static void do_setup_particle(Model *m, 
                               ParticleIndex pi,
                               int state) {
   m->add_attribute(get_state_key(), pi, state);
 }

 static void do_setup_particle(Model *m, ParticleIndex pi,
                                MaturationStateDecorator o) {
   do_setup_particle(m, pi, o.get_state());
 }

 public:
  static bool get_is_setup(Model *m, ParticleIndex pi) {
    return m->get_has_attribute(get_state_key(), pi);
  }

  Int get_state() const {
    return get_model()->get_attribute(get_state_key(), get_particle_index());
  }

  void set_state(Int d) { 
    get_model()->set_attribute(get_state_key(), get_particle_index(), d);
  }

  IMP_DECORATOR_METHODS(MaturationStateDecorator, Decorator);
  /** Add the specified maturation state to the particle. */
  IMP_DECORATOR_SETUP_1(MaturationStateDecorator, Int, state);
  IMP_DECORATOR_SETUP_1(MaturationStateDecorator, MaturationStateDecorator, other);
  /** Get the key used to store the maturation state. */
  static IntKey get_state_key();
};

IMPINSULINSECRETION_END_NAMESPACE

#endif /* IMPINSULINSECRETION_MATURATION_STATE_DECORATOR_H */