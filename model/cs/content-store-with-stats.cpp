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

#include "content-store-with-stats.hpp"

#include "../../utils/trie/random-policy.hpp"
#include "../../utils/trie/lru-policy.hpp"
#include "../../utils/trie/fifo-policy.hpp"
#include "../../utils/trie/lfu-policy.hpp"

#define NS_OBJECT_ENSURE_REGISTERED_TEMPL(type, templ)                                             \
  static struct X##type##templ##RegistrationClass {                                                \
    X##type##templ##RegistrationClass()                                                            \
    {                                                                                              \
      ns3::TypeId tid = type<templ>::GetTypeId();                                                  \
      tid.GetParent();                                                                             \
    }                                                                                              \
  } x_##type##templ##RegistrationVariable

namespace ns3 {
namespace ndn {

using namespace ndnSIM;

namespace cs {

// explicit instantiation and registering
/**
 * @brief ContentStore with stats and LRU cache replacement policy
 **/
template class ContentStoreWithStats<lru_policy_traits>;

/**
 * @brief ContentStore with stats and random cache replacement policy
 **/
template class ContentStoreWithStats<random_policy_traits>;

/**
 * @brief ContentStore with stats and FIFO cache replacement policy
 **/
template class ContentStoreWithStats<fifo_policy_traits>;

/**
 * @brief ContentStore with stats and Least Frequently Used (LFU) cache replacement policy
 **/
template class ContentStoreWithStats<lfu_policy_traits>;

NS_OBJECT_ENSURE_REGISTERED_TEMPL(ContentStoreWithStats, lru_policy_traits);
NS_OBJECT_ENSURE_REGISTERED_TEMPL(ContentStoreWithStats, random_policy_traits);
NS_OBJECT_ENSURE_REGISTERED_TEMPL(ContentStoreWithStats, fifo_policy_traits);

NS_OBJECT_ENSURE_REGISTERED_TEMPL(ContentStoreWithStats, lfu_policy_traits);

#ifdef DOXYGEN
// /**
//  * \brief Content Store with stats implementing LRU cache replacement policy
//  */
class Stats::Lru : public ContentStoreWithStats<lru_policy_traits> {
};

/**
 * \brief Content Store with stats implementing FIFO cache replacement policy
 */
class Stats::Fifo : public ContentStoreWithStats<fifo_policy_traits> {
};

/**
 * \brief Content Store with stats implementing Random cache replacement policy
 */
class Stats::Random : public ContentStoreWithStats<random_policy_traits> {
};

/**
 * \brief Content Store with stats implementing Least Frequently Used cache replacement policy
 */
class Stats::Lfu : public ContentStoreWithStats<lfu_policy_traits> {
};

#endif

} // namespace cs
} // namespace ndn
} // namespace ns3
