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
#include "ns3/ccnx-type-identifier.h"

#include "../TestMacros.h"

using namespace ns3;
using namespace ns3::ccnx;

namespace TestSuiteCCNxTypeIdentifier {

BeginTest (Constructor_Number)
{
  CCNxTypeIdentifier tid(5);
  NS_TEST_EXPECT_MSG_EQ(tid.size(), 1, "Wrong size");
  NS_TEST_EXPECT_MSG_EQ(tid[0], 5, "TID[0] should be 5");
}
EndTest ()

BeginTest (Constructor_Parent)
{
  CCNxTypeIdentifier parent(5);
  CCNxTypeIdentifier child(parent, 6);
  NS_TEST_EXPECT_MSG_EQ(child.size(), 2, "Wrong size");
  NS_TEST_EXPECT_MSG_EQ(child[0], 5, "TID[0] should be 5");
  NS_TEST_EXPECT_MSG_EQ(child[1], 6, "TID[1] should be 6");
}
EndTest ()

BeginTest (Constructor_String)
{
  CCNxTypeIdentifier tid("1.2.3.4");
  unsigned values[] = { 1, 2, 3, 4 };

  NS_TEST_EXPECT_MSG_EQ(tid.size(), 4, "Wrong size");

  for (int i = 0; i < tid.size(); ++i) {
      NS_TEST_EXPECT_MSG_EQ(tid[i], values[i], "Component " << i << " incorrect");
  }
}
EndTest ()

BeginTest (Constructor_Copy)
{
  CCNxTypeIdentifier parent("1.2.3.4");
  CCNxTypeIdentifier copy(parent);
  bool isEquals = parent == copy;
  NS_TEST_EXPECT_MSG_EQ(isEquals, true, "Copy is not equal to original");
}
EndTest ()

BeginTest (Constructor_GetTid_Single)
{
  CCNxTypeIdentifier parent(77);
  std::string truth = "77";
  NS_TEST_EXPECT_MSG_EQ(parent.GetTid(), truth, "GetTid for single component wrong");
}
EndTest ()

BeginTest (Constructor_GetTid_Multiple)
{
  std::string truth = "77.1234.8";
  CCNxTypeIdentifier parent(truth);
  NS_TEST_EXPECT_MSG_EQ(parent.GetTid(), truth, "GetTid for multiple components wrong");
}
EndTest ()

BeginTest (Constructor_Operator_Less)
{
  struct {
    std::string	a;
    std::string b;
    bool isLess;
    bool sentinel;
  } testVectors[] = {
      { "5", "1", false, false },
      { "5", "5", false, false },
      { "5", "7", true, false },
      { "5", "5.1", true, false },
      { "5.5", "5.1", false, false },
      { "5.5", "5.5", false, false },
      { "5.5", "5.7", true, false },
      { "", "", false, true },
  };

  for (int i = 0; !testVectors[i].sentinel; ++i) {
      CCNxTypeIdentifier a(testVectors[i].a);
      CCNxTypeIdentifier b(testVectors[i].b);

      bool isLess = a < b;
      NS_TEST_EXPECT_MSG_EQ(isLess, testVectors[i].isLess, "Incorrect result on index " << i);
  }
}
EndTest ()

BeginTest (Constructor_Operator_Equals)
{
  CCNxTypeIdentifier a("5.7.99.1000");
  CCNxTypeIdentifier b("5.7.99.1000");
  CCNxTypeIdentifier c("5.7.99.1000");

  CCNxTypeIdentifier x("5.7.99");
  CCNxTypeIdentifier y("5.7.99.1000.2000");
  CCNxTypeIdentifier z("5.7.77.1000");

  NS_TEST_EXPECT_MSG_EQ((a == b), true, "a != b");
  NS_TEST_EXPECT_MSG_EQ((b == c), true, "b != c");
  NS_TEST_EXPECT_MSG_EQ((c == a), true, "c != a");

  NS_TEST_EXPECT_MSG_EQ((a == x), false, "a == x");
  NS_TEST_EXPECT_MSG_EQ((a == y), false, "a == y");
  NS_TEST_EXPECT_MSG_EQ((a == z), false, "a == z");
}
EndTest ()


/**
 * @ingroup ccnx-test
 *
 * Test Suite for CCNxTypeIdentifier
 */
static class TestSuiteCCNxTypeIdentifier : public TestSuite
{
public:
  TestSuiteCCNxTypeIdentifier () : TestSuite ("ccnx-type-identifier", UNIT)
  {
    AddTestCase (new Constructor_Number (), TestCase::QUICK);
    AddTestCase (new Constructor_Parent (), TestCase::QUICK);
    AddTestCase (new Constructor_String (), TestCase::QUICK);
    AddTestCase (new Constructor_Copy (), TestCase::QUICK);
    AddTestCase (new Constructor_GetTid_Single (), TestCase::QUICK);
    AddTestCase (new Constructor_GetTid_Multiple (), TestCase::QUICK);
    AddTestCase (new Constructor_Operator_Less (), TestCase::QUICK);
    AddTestCase (new Constructor_Operator_Equals (), TestCase::QUICK);
  }
} g_TestSuiteCCNxTypeIdentifier;

} // namespace TestSuiteCCNxTypeIdentifier
