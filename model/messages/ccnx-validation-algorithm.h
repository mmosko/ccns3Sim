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


#ifndef CCNS3SIM_MODEL_MESSAGES_CCNX_VALIDATION_ALGORITHM_H_
#define CCNS3SIM_MODEL_MESSAGES_CCNX_VALIDATION_ALGORITHM_H_

#include "ns3/object.h"
#include "ns3/header.h"
#include "ns3/ccnx-keyid.h"
#include "ns3/ccnx-crypto-suite.h"
#include "ns3/ccnx-byte-array.h"

namespace ns3 {
namespace ccnx {

/**
 * @ingroup ccnx-messages
 *
 * The validation algorithm contains information needed to understand how the validation
 * payload was created.  It is also part of the protected region of the validation (e.g. the CRC, MAC, or signature).
 *
 * The `CCNxValidationAlgorithm` is a CCNx packet field.  It carries the algorithm-specific data that is
 * the output of a crypto suite.  The CCNxValidationAlgorithm does not perform any cryptographic functions.
 *
 * Specific `CCNxValidationAlgorithm` implementation should derive from this class and implement a specific
 * validation algorithm.
 *
 * Because the KeyId is an integral piece of information for the forwarding and processing of packets,
 * all validation algorithms must support the functions to test for and retrieve a keyid.  Some
 * validation algorithms (e.g. CRC32C) will always return false for `HasKeyId()`.
 *
 */
class CCNxValidationAlgorithm : public Object
{
public:
  /**
   * Required by ns3::Object
   *
   * @return
   */
  static TypeId GetTypeId (void);

  /**
   * Returns the TypeId of this instance.  Because it is a virtual member, it will
   * return the TypeId of the concrete class that implements CCNxValidation.
   * @return The instance's TypeId
   */
  virtual TypeId GetInstanceTypeId (void) const = 0;


  virtual ~CCNxValidationAlgorithm ();

  /**
   * Determines if the validation has a KeyId, which may be used by
   * a forwarder when matching an Interest.
   *
   * @return true If the instance has a KeyId
   * @return false If there is not a KeyId available.
   */
  virtual bool HasKeyId () const = 0;

  /**
   * Return the instance's KeyId.
   *
   * @return non-null The KeyId if present (HasKeyId is true)
   * @return Ptr<CCNxKeyId>(0) If the KeyId is not present (HasKeyId is false)
   */
  virtual Ptr<CCNxKeyId> GetKeyId () const = 0;

  /**
   * Returns the crypto suite used by the instance of CCNxValidation.
   *
   * @return cryptosuite The cryptosuite used by the validation.
   */
  virtual CCNxCryptoSuite::CryptoSuiteType GetCryptoSuite () const = 0;

  /**
   * Returns the codec to use with this message type.  THis will be specific to
   * the actual implementation class.
   *
   * @return
   */
  virtual Ptr<ns3::Object> GetCodec () = 0;
};

}   /* namespace ccnx */
} /* namespace ns3 */

#endif /* CCNS3SIM_MODEL_MESSAGES_CCNX_VALIDATION_ALGORITHM_H_ */
