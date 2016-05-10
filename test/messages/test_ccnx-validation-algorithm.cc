/*
 * Copyright (c) 2016, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Patent rights are not granted under this agreement. Patent rights are
 *       available under FRAND terms.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL XEROX or PARC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "ns3/test.h"
#include "ns3/ccnx-validation-algorithm.h"

#include "../TestMacros.h"

using namespace ns3;
using namespace ns3::ccnx;

namespace TestSuiteCCNxValidationAlgorithm {

BeginTest (Constructor)
{
#if 0
/**
 * \ingroup ccnx-messages
 *
 * Represents the Validation section of a CCNx message.
 */
  class CCNxValidation : public Object
  {
public:
    static TypeId GetTypeId (void);

    CCNxValidation ();
    virtual ~CCNxValidation ();

    /**
     * Returns the TypeId of this instance.  Because it is a virtual member, it will
     * return the TypeId of the concrete class that implements CCNxValidation.
     * @return The instance's TypeId
     */
    virtual TypeId GetInstanceTypeId (void) const = 0;
    virtual Ptr<CCNxSigner> CreateSigner () = 0;
    virtual Ptr<CCNxVerifier> CreateVerifier () = 0;
  };
#endif
}
EndTest ()

/**
 * @ingroup ccnx-test
 *
 * Test Suite for CCNxValidationAlgorithm
 */
static class TestSuiteCCNxValidationAlgorithm : public TestSuite
{
public:
  TestSuiteCCNxValidationAlgorithm () : TestSuite ("ccnx-validation-algorithm", UNIT)
  {
    AddTestCase (new Constructor (), TestCase::QUICK);
  }
} g_TestSuiteCCNxValidationAlgorithm;

} // namespace TestSuiteCCNxValidationAlgorithm
