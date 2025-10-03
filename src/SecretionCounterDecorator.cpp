/**
 *  \file IMP/insulinsecretion/SecretionCounterDecorator.cpp
 *  \brief Add a secretion decorator to a granule to count the number of secretion events occured to it.
 *
 * Description:
 * 1, Set a decorator to count the number of secretion events. 
 * 2, It starts with zero.
 *
 *
 *  Copyright 2007-2019 IMP Inventors. All rights reserved.
 */

#include <IMP/insulinsecretion/SecretionCounterDecorator.h>

IMPINSULINSECRETION_BEGIN_NAMESPACE

IntKey SecretionCounterDecorator::get_secretion_key() {
  static IntKey k("secretion");
  return k;
}

void SecretionCounterDecorator::show(std::ostream &out) const {
  out << "SecretionCounter " << get_secretion() << std::endl;
}

IMPINSULINSECRETION_END_NAMESPACE
