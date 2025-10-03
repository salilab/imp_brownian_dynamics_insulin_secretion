/**
 *  \file IMP/insulinsecretion/MaturationStateDecorator.cpp
 *  \brief Add a decorator to an insulin vesicle to describe its maturation state, 0 = imature, matured_state = mature.
 *
 * Description:
 * 1, Set a decorator to describe the maturation state of an insulin vesicle.
 * 2, It starts with zero.
 *
 *
 *  Copyright 2007-2019 IMP Inventors. All rights reserved.
 */

#include <IMP/insulinsecretion/MaturationStateDecorator.h>

IMPINSULINSECRETION_BEGIN_NAMESPACE

IntKey MaturationStateDecorator::get_state_key() {
  static IntKey k("state");
  return k;
}

void MaturationStateDecorator::show(std::ostream &out) const {
  out << "Maturation state " << get_state() << std::endl;
}

IMPINSULINSECRETION_END_NAMESPACE
