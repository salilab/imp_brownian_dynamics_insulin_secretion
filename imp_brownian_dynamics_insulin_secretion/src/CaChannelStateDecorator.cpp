/**
 *  \file IMP/insulinsecretion/CaChannelStateDecorator.cpp
  *  \brief Add a decorator to a Ca2+ channel to describe its opening state.
 *
 * Description:
 * 1, Set a decorator to describe the Ca2+ channel opening state.
 * 2, It is either 0 (i.e., closed) or 1 (i.e., open). 
 *
 *
 *  Copyright 2007-2019 IMP Inventors. All rights reserved.
 */

#include <IMP/insulinsecretion/CaChannelStateDecorator.h>

IMPINSULINSECRETION_BEGIN_NAMESPACE

IntKey CaChannelStateDecorator::get_channelstate_key() {
  static IntKey k("ChannelState");
  return k;
}

void CaChannelStateDecorator::show(std::ostream &out) const {
  out << "The binary state of the Calcium channel " << get_channelstate() << std::endl;
}

IMPINSULINSECRETION_END_NAMESPACE
