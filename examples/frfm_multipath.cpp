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
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/ndnSIM-module.h"
#include "fw/frfm_strategy.hpp"

#include <sys/time.h>
#include "ns3/ndnSIM/utils/mem-usage.hpp"
#include "ns3/ndnSIM/model/cs/ndn-content-store.hpp"
#include "ns3/ndnSIM/utils/mem-usage.hpp"
namespace ns3 {
/*
void PeriodicStatsPrinter (Ptr<Node> node, Time next)
{
	Ptr<Node> pit = node->GetObject<ndn::Node> ();

  std::cout << Simulator::Now ().ToDouble (Time::S) << "\t"
            << node->GetId () << "\t"
            << Names::FindName (node) << "\t"
            << pit->GetObject<ndn::L3Protocol()->getForwarder()->getPit () << "\n";

  Simulator::Schedule (next, PeriodicStatsPrinter, node, next);
}*/
int main(int argc, char* argv[])
{
  CommandLine cmd;
  cmd.Parse(argc, argv);
  AnnotatedTopologyReader topologyReader("", 25);
  topologyReader.SetFileName("src/ndnSIM/examples/topologies/frfm.txt");
  topologyReader.Read();

  // Install NDN stack on all nodes
  ndn::StackHelper ndnHelper;
  ndnHelper.SetDefaultRoutes(true);
  //ndnHelper.SetPit ("ns3::ndn::pit::Persistent::AggregateStats");
  ndnHelper.setCsSize(1000);
  ndnHelper.InstallAll();

  // Set BestRoute strategy
  ndn::StrategyChoiceHelper::InstallAll("/", "/localhost/nfd/strategy/frfm");
  //Specifying producers nodes

  Ptr<Node> conusmer = Names::Find<Node>("Node0");
  Ptr<Node> router1 = Names::Find<Node>("Node1");
  Ptr<Node> router2 = Names::Find<Node>("Node2");
  Ptr<Node> router3 = Names::Find<Node>("Node3");
  Ptr<Node> router4 = Names::Find<Node>("Node4");
  Ptr<Node> router5 = Names::Find<Node>("Node5");
  Ptr<Node> router6 = Names::Find<Node>("Node6");
  Ptr<Node> router7 = Names::Find<Node>("Node7");
  Ptr<Node> producer = Names::Find<Node>("Node8");
/*
  // see more http://www.nsnam.org/doxygen/classns3_1_1_names.html
   Names::Add ("consumer", conusmer);
   Names::Add ("router1", router1);
   Names::Add ("router2", router2);
   Names::Add ("router3", router3);
   Names::Add ("router4", router4);
   Names::Add ("router5", router5);
   Names::Add ("router6", router6);
   Names::Add ("router7", router7);
   Names::Add ("producer", producer);
*/
  //Specifying consumer nodes and containers
  NodeContainer consumerNodes1;
  consumerNodes1.Add(Names::Find<Node>("Node0"));
/*
  // set up periodic PIT stats printer  ndn-simple-with-pit-count-stats.cc
    std::cout << "Time" << "\t"
              << "NodeId" << "\t"
              << "NodeName" << "\t"
              << "NumberOfPitEntries" << "\n";
    Simulator::Schedule (Seconds (1), PeriodicStatsPrinter, router1 , Seconds (1));
    Simulator::Schedule (Seconds (1), PeriodicStatsPrinter, router2, Seconds (1));
    Simulator::Schedule (Seconds (1), PeriodicStatsPrinter, router3, Seconds (1));
    Simulator::Schedule (Seconds (1), PeriodicStatsPrinter, router4 , Seconds (1));
    Simulator::Schedule (Seconds (1), PeriodicStatsPrinter, router5, Seconds (1));
    Simulator::Schedule (Seconds (1), PeriodicStatsPrinter, router6, Seconds (1));
    Simulator::Schedule (Seconds (1), PeriodicStatsPrinter, router7, Seconds (1));
    */
  // Specifying content name
  std::string prefix1 = "kr/ac/ce/ccn/presentation/forwarding/";

  // Installing Consumer application
  ndn::AppHelper consumerHelper1("ns3::ndn::ConsumerCbr");
  consumerHelper1.SetPrefix(prefix1);
  consumerHelper1.SetAttribute("Frequency", StringValue("1000")); // 100 interests a second
  consumerHelper1.SetAttribute ("PayloadSize", UintegerValue (1024));
  consumerHelper1.SetAttribute ("Size", DoubleValue (10240));
  consumerHelper1.Install(conusmer);


  // Installing producer application
  ndn::AppHelper producerHelper1("ns3::ndn::Producer");
  producerHelper1.SetPrefix(prefix1);
  producerHelper1.SetAttribute("PayloadSize", StringValue("1024"));
  producerHelper1.Install(producer);

  //ndn::CsTracer::InstallAll("cs-trace.txt", Seconds(1));
  L2RateTracer::InstallAll("rate-l2trace.txt", Seconds(1.0));
  ndn::L3RateTracer::InstallAll("rate-l3trace.txt", Seconds(1.0));
  ndn::AppDelayTracer::InstallAll("app-delays-trace.txt");
  L2RateTracer::InstallAll("drop-trace.txt", Seconds(0.5));


  Simulator::Stop(Seconds(50.0));
  Simulator::Run();
  Simulator::Destroy();

  return 0;
}
} // namespace ns3

int
main(int argc, char* argv[])
{
  return ns3::main(argc, argv);
}
