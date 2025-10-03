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

#include <IMP/insulinsecretion/DockingStateDecorator.h>

IMPINSULINSECRETION_BEGIN_NAMESPACE

IntKey DockingStateDecorator::get_dstate_key() {
  static IntKey k("dstate");
  return k;
}

void DockingStateDecorator::show(std::ostream &out) const {
  out << "Docking state " << get_dstate() << std::endl;
}

IMPINSULINSECRETION_END_NAMESPACE
