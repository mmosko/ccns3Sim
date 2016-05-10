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

#ifndef CCNS3SIM_MODEL_MESSAGES_VALIDATION_PUBLICKEY_CCNX_VALIDATION_PUBLICKEY_H_
#define CCNS3SIM_MODEL_MESSAGES_VALIDATION_PUBLICKEY_CCNX_VALIDATION_PUBLICKEY_H_

#include "ns3/ccnx-validation-algorithm.h"
#include "ns3/ccnx-keyid.h"
#include "ns3/ccnx-signature.h"
#include "ns3/ccnx-key.h"
#include "ns3/ccnx-time.h"

namespace ns3 {
namespace ccnx {

/**
 * This is an intermediate class for all public key algorithms.  It takes care of most all aspects
 * of `CCNxValidationAlgorithm` for public key algorithms.
 *
 * To implement a concrete public key validation section, such as for RSA-SHA256, one derives
 * from this class implements `GetInstanceType()`, `GetCodec()` and `GetCryptoSuiteType()`.
 */
class CCNxValidationPublicKey : public CCNxValidationAlgorithm
{
public:
  static TypeId GetTypeId (void);

  /**
   * Minimum constructor for RSA-SHA256: you must have a keyid and a signature.
   *
   * @param signature
   * @param keyId
   */
  CCNxValidationPublicKey (Ptr<const CCNxSignature> signature, Ptr<const CCNxKeyId> keyId);

  /**
   * Constructor that includes the public key in the wire format in addition to the keyid and signature.
   *
   * @param signature
   * @param keyId
   * @param publicKey
   */
  CCNxValidationPublicKey (Ptr<const CCNxSignature> signature, Ptr<const CCNxKeyId> keyId, Ptr<const CCNxKey> publicKey);

  /**
   * Constructor that includes the public key in the wire format in addition to the keyid and signature.
   *
   * @param signature
   * @param keyId
   * @param publicKey
   */
  CCNxValidationPublicKey (Ptr<const CCNxSignature> signature, Ptr<const CCNxKeyId> keyId, Ptr<const CCNxKey> publicKey,
                           Ptr<const CCNxTime> signatureTime);



  virtual ~CCNxValidationPublicKey ();



private:
  Ptr<const CCNxSignature> m_signature;
  Ptr<const CCNxKeyId> m_keyId;
};

} // namespace ns3::ccnx
} // namespace ns3


#endif /* CCNS3SIM_MODEL_MESSAGES_VALIDATION_PUBLICKEY_CCNX_VALIDATION_PUBLICKEY_H_ */
