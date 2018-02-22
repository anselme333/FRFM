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
#ifndef NDNSIM_EXAMPLES_NDN_FRFM_HPP
#define NDNSIM_EXAMPLES_NDN_FRFM_HPP
#include "face/face.hpp"
#include "fw/strategy.hpp"

namespace nfd {
namespace fw {

class frfm : public Strategy {
public:
  frfm(Forwarder& forwarder, const Name& name = STRATEGY_NAME);

  virtual ~frfm();

  virtual void
  afterReceiveInterest(const Face& inFace, const Interest& interest,
                       shared_ptr<fib::Entry> fibEntry, shared_ptr<pit::Entry> pitEntry) DECL_OVERRIDE;

public:
  static const Name STRATEGY_NAME;

};

} // namespace fw
} // namespace nfd

#endif // NDNSIM_EXAMPLES_NDN_LOAD_BALANCER_RANDOM_LOAD_BALANCER_STRATEGY_HPP
