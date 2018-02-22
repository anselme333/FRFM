/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2011-2015  Regents of the University of California.
 *
 * This file is part of ndnSIM. See AUTHORS for complete list of ndnSIM authors and
 * contributors.
 *
 * ndnSIM is free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * ndnSIM is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * ndnSIM, e.g., in COPYING.md file.  If not, see <http://www.gnu.org/licenses/>.
 **/
//FRFM: Fast and Reliable Forwarding  Mechanism for Content Centric Networking (CCN)
#include "frfm_strategy.hpp"
#include <ndn-cxx/util/random.hpp>
#include "core/logger.hpp"

NFD_LOG_INIT("frfm");
namespace nfd {
namespace fw {

const Name frfm::STRATEGY_NAME("ndn:/localhost/nfd/strategy/frfm");
NFD_REGISTER_STRATEGY(frfm);
frfm::frfm(Forwarder& forwarder, const Name& name)
  : Strategy(forwarder, name)
{
}

frfm::~frfm()
{
}
void
frfm::afterReceiveInterest(const Face& inFace, const Interest& interest,
                                                 shared_ptr<fib::Entry> fibEntry,
                                                 shared_ptr<pit::Entry> pitEntry)
{
   const fib::NextHopList& nexthops = fibEntry->getNextHops();
   for (fib::NextHopList::const_iterator it = nexthops.begin(); it != nexthops.end(); ++it)
   {
   shared_ptr<Face> outFace = it->getFace();
   if (pitEntry->canForwardTo(*outFace))
   {
   this->sendInterest(pitEntry, outFace);
   }
   }
   if (!pitEntry->hasUnexpiredOutRecords())
   {
   this->rejectPendingInterest(pitEntry);
   }
   }
} // namespace fw
} // namespace nfd
