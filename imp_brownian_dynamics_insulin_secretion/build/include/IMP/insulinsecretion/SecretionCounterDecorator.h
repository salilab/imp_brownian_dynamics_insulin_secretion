/**
 *  \file IMP/insulinsecretion/SecretionCounterDecorator.h
 *  \brief Add a secretion decorator to a granule to count the number of secretion events occured to it.
 *
 * Description:
 * 1, Set a decorator to count the number of secretion events. 
 * 2, It starts with zero.
 *
 *
 *  Copyright 2007-2019 IMP Inventors. All rights reserved.
 */

#ifndef IMPINSULINSECRETION_SECRETION_COUNTER_DECORATOR_H
#define IMPINSULINSECRETION_SECRETION_COUNTER_DECORATOR_H

#include <IMP/insulinsecretion/insulinsecretion_config.h>
#include <IMP/PairContainer.h>
#include <IMP/SingletonContainer.h>
#include <IMP/Decorator.h>
#include <IMP/decorator_macros.h>

IMPINSULINSECRETION_BEGIN_NAMESPACE
//TODO: add tester

//! A simple decorator to count for the number of secretion events occured to this granule
/** 
    1, Set a decorator to count the collision times between Granule[i] and periphery. 
    2, It starts with zero.
    @param secretion an integer that records the number of secretion events.
*/
class IMPINSULINSECRETIONEXPORT SecretionCounterDecorator
: public Decorator 
{
 //! Add an integer to the particle  
 // returns the value of the name attribute, or default_value if
 //the name attribute is missing
 static void do_setup_particle(Model *m, 
                               ParticleIndex pi,
                               int secretion) {
   m->add_attribute(get_secretion_key(), pi, secretion);
 }

 static void do_setup_particle(Model *m, ParticleIndex pi,
                                SecretionCounterDecorator o) {
   do_setup_particle(m, pi, o.get_secretion());
 }

 public:
  static bool get_is_setup(Model *m, ParticleIndex pi) {
    return m->get_has_attribute(get_secretion_key(), pi);
  }

  Int get_secretion() const {
    return get_model()->get_attribute(get_secretion_key(), get_particle_index());
  }

  void set_secretion(Int d) { // TODO should be integer
    get_model()->set_attribute(get_secretion_key(), get_particle_index(), d);
  }

  IMP_DECORATOR_METHODS(SecretionCounterDecorator, Decorator);
  /** Add the specified secretion to the particle. */
  IMP_DECORATOR_SETUP_1(SecretionCounterDecorator, Int, secretion);
  IMP_DECORATOR_SETUP_1(SecretionCounterDecorator, SecretionCounterDecorator, other);
  /** Get the key used to store the secretion. */
  static IntKey get_secretion_key();
};

IMPINSULINSECRETION_END_NAMESPACE

#endif /* IMPINSULINSECRETION_SECRETION_COUNTER_DECORATOR_H */