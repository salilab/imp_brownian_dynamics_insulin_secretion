/**
 *  \file IMP/insulinsecretion/DockingStateDecorator.h
 *  \brief Add a decorator to an insulin vesicle to describe its docking state, which is the time needed between docked to secreted states, e.g., semi-fusion time.
 *
 * Description:
 * 1, Set a decorator to describe the docking state of an insulin vesicle.
 * 2, It starts with zero.
 *
 *
 *  Copyright 2007-2019 IMP Inventors. All rights reserved.
 */

#ifndef IMPINSULINSECRETION_DOCKING_STATE_DECORATOR_H
#define IMPINSULINSECRETION_DOCKING_STATE_DECORATOR_H

#include <IMP/insulinsecretion/insulinsecretion_config.h>
#include <IMP/Decorator.h>
#include <IMP/decorator_macros.h>

IMPINSULINSECRETION_BEGIN_NAMESPACE
//TODO: add tester

//! A decorator to an insulin vesicle to describe its docking state.
/** 
    1, Set a decorator to describe the docking state of an insulin vesicle.
    2, It starts with zero.
    @param dstate an integer that describes the docking state.
*/
class IMPINSULINSECRETIONEXPORT DockingStateDecorator
: public Decorator 
{
 //! Add an integer to the particle  
 // returns the value of the name attribute, or default_value if
 //the name attribute is missing
 static void do_setup_particle(Model *m, 
                               ParticleIndex pi,
                               int dstate = 0) {
   m->add_attribute(get_dstate_key(), pi, dstate);
 }

 static void do_setup_particle(Model *m, ParticleIndex pi,
                                DockingStateDecorator o) {
   do_setup_particle(m, pi, o.get_dstate());
 }

 public:
  static bool get_is_setup(Model *m, ParticleIndex pi) {
    return m->get_has_attribute(get_dstate_key(), pi);
  }

  Int get_dstate() const {
    return get_model()->get_attribute(get_dstate_key(), get_particle_index());
  }

  void set_dstate(Int d) { 
    get_model()->set_attribute(get_dstate_key(), get_particle_index(), d);
  }

  IMP_DECORATOR_METHODS(DockingStateDecorator, Decorator);
  /** Add the specified docking state to the particle. */
  IMP_DECORATOR_SETUP_1(DockingStateDecorator, Int, dstate);
  IMP_DECORATOR_SETUP_1(DockingStateDecorator, DockingStateDecorator, other);
  /** Get the key used to store the docking state. */
  static IntKey get_dstate_key();
};

IMPINSULINSECRETION_END_NAMESPACE

#endif /* IMPINSULINSECRETION_DOCKING_STATE_DECORATOR_H */