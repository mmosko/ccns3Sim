/*
 * Copyright (c) 2016, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL XEROX OR PARC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/* ################################################################################
 * #
 * # PATENT NOTICE
 * #
 * # This software is distributed under the BSD 2-clause License (see LICENSE
 * # file).  This BSD License does not make any patent claims and as such, does
 * # not act as a patent grant.  The purpose of this section is for each contributor
 * # to define their intentions with respect to intellectual property.
 * #
 * # Each contributor to this source code is encouraged to state their patent
 * # claims and licensing mechanisms for any contributions made. At the end of
 * # this section contributors may each make their own statements.  Contributor's
 * # claims and grants only apply to the pieces (source code, programs, text,
 * # media, etc) that they have contributed directly to this software.
 * #
 * # There is no guarantee that this section is complete, up to date or accurate. It
 * # is up to the contributors to maintain their portion of this section and up to
 * # the user of the software to verify any claims herein.
 * #
 * # Do not remove this header notification.  The contents of this section must be
 * # present in all distributions of the software.  You may only modify your own
 * # intellectual property statements.  Please provide contact information.
 *
 * - Palo Alto Research Center, Inc
 * This software distribution does not grant any rights to patents owned by Palo
 * Alto Research Center, Inc (PARC). Rights to these patents are available via
 * various mechanisms. As of January 2016 PARC has committed to FRAND licensing any
 * intellectual property used by its contributions to this software. You may
 * contact PARC at cipo@parc.com for more information or visit http://www.ccnx.org
 */

#include "ns3/test.h"
#include "ns3/ccnx-interestlifetime.h"

#include "../TestMacros.h"

using namespace ns3;
using namespace ns3::ccnx;

namespace TestSuiteCCNxInterestLifetime {

BeginTest (Constructor)
{
  Ptr<CCNxTime> time = Create<CCNxTime>(3600);
  Ptr<CCNxInterestLifetime> interestLifetime = Create<CCNxInterestLifetime> (time);
  bool exists = (interestLifetime);
  NS_TEST_EXPECT_MSG_EQ (exists, true, "Gut null pointer");
}
EndTest()

BeginTest (GetInterestLifetime)
{
  Ptr<CCNxTime> time = Create<CCNxTime>(3600);
  Ptr<CCNxInterestLifetime> interestLifetime = Create<CCNxInterestLifetime> (time);
  bool exists = (interestLifetime);
  NS_TEST_EXPECT_MSG_EQ (exists, true, "Gut null pointer");

  Ptr<CCNxTime> lifetimeValue = interestLifetime->GetInterestLifetime();
  bool timeExists = (lifetimeValue);
  NS_TEST_EXPECT_MSG_EQ (timeExists, true, "Gut null pointer");

  bool truth = lifetimeValue->getTime() == 3600;
  NS_TEST_EXPECT_MSG_EQ (truth, true, "Values should match");
}
EndTest()

BeginTest (Print)
{
  Ptr<CCNxTime> time = Create<CCNxTime>(3600);
  Ptr<CCNxInterestLifetime> interestLifetime = Create<CCNxInterestLifetime> (time);
  bool exists = (interestLifetime);
  NS_TEST_EXPECT_MSG_EQ (exists, true, "Gut null pointer");

  interestLifetime->Print(std::cout);
}
EndTest()

BeginTest (GetInstanceTLVType)
{
  Ptr<CCNxTime> time = Create<CCNxTime>(3600);
  Ptr<CCNxInterestLifetime> interestLifetime = Create<CCNxInterestLifetime> (time);
  bool exists = (interestLifetime);
  NS_TEST_EXPECT_MSG_EQ (exists, true, "Gut null pointer");

  uint16_t result = interestLifetime->GetInstanceTLVType ();
  NS_TEST_EXPECT_MSG_EQ (result, 1, "Got wrong value");
}
EndTest()

BeginTest (GetInstanceTypeId)
{
  Ptr<CCNxTime> time = Create<CCNxTime>(3600);
  Ptr<CCNxInterestLifetime> interestLifetime = Create<CCNxInterestLifetime> (time);
  bool exists = (interestLifetime);
  NS_TEST_EXPECT_MSG_EQ (exists, true, "Gut null pointer");

  TypeId type = interestLifetime->GetInstanceTypeId ();
  bool truth = type.GetName() == "ns3::ccnx::CCNxInterestLifetime";
  NS_TEST_EXPECT_MSG_EQ (truth, true, "Names should match");
}
EndTest()

BeginTest (Equals)
{
  Ptr<CCNxInterestLifetime> a = Create<CCNxInterestLifetime> (Create<CCNxTime>(3600));
  Ptr<CCNxInterestLifetime> b = Create<CCNxInterestLifetime> (Create<CCNxTime>(3600));
  Ptr<CCNxInterestLifetime> c = Create<CCNxInterestLifetime> (Create<CCNxTime>(3600));

  Ptr<CCNxInterestLifetime> w = Create<CCNxInterestLifetime> (Create<CCNxTime>(1200));

  // transitivity of equals
  NS_TEST_EXPECT_MSG_EQ (a->Equals (b), true, "not equal");
  NS_TEST_EXPECT_MSG_EQ (b->Equals (c), true, "not equal");
  NS_TEST_EXPECT_MSG_EQ (c->Equals (a), true, "not equal");

  // and the counter case
  NS_TEST_EXPECT_MSG_EQ (a->Equals (w), false, "not equal");

  // Negative test
  NS_TEST_EXPECT_MSG_EQ (a->Equals (0), false, "null value");
}
EndTest ()


/**
 * @ingroup ccnx-test
 *
 * Test Suite for CCNxInterestLifetime
 */
static class TestSuiteCCNxInterestLifetime : public TestSuite
{
public:
  TestSuiteCCNxInterestLifetime () : TestSuite ("ccnx-interestlifetime", UNIT)
  {
    AddTestCase (new Constructor (), TestCase::QUICK);
    AddTestCase (new GetInterestLifetime (), TestCase::QUICK);
    AddTestCase (new Print (), TestCase::QUICK);
    AddTestCase (new GetInstanceTLVType (), TestCase::QUICK);
    AddTestCase (new GetInstanceTypeId (), TestCase::QUICK);
    AddTestCase (new Equals (), TestCase::QUICK);
  }
} g_TestSuiteCCNxInterestLifetime;

} // namespace TestSuiteCCNxInterestLifetime
