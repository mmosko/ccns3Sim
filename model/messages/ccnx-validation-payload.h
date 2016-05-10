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


#ifndef CCNS3SIM_MODEL_MESSAGES_CCNX_VALIDATION_PAYLOAD_H_
#define CCNS3SIM_MODEL_MESSAGES_CCNX_VALIDATION_PAYLOAD_H_

#include "ns3/header.h"
#include "ns3/ccnx-signature.h"
#include "ns3/simple-ref-count.h"

namespace ns3 {
namespace ccnx {

/**
 * @ingroup ccnx-messages
 *
 * The validation payload contains the output of the validation algorithm.  It could be
 * the output of a CRC, a MAC (e.g. HMAC), or a signature (e.g. RSA-SHA256).
 *
 * Usually, a concrete implementation of a `CCNxValidation` does not need to override
 * this class.
 */
class CCNxValidationPayload : public SimpleRefCount<CCNxValidationPayload>
{
public:
  CCNxValidationPayload (Ptr<const CCNxSignature> validationPayload);
  virtual ~CCNxValidationPayload ();

  virtual Ptr<const CCNxSignature> GetPayload () const;

  /**
   * Returns the codec to use with this message type.  THis will be specific to
   * the actual implementation class.  It will default to `CCNxCodecValidationPayload`.
   *
   * @return
   */
//  virtual Ptr<ns3::Header> GetCodec ();

protected:
  Ptr<const CCNxSignature> m_validationPayload;
};

}   /* namespace ccnx */
} /* namespace ns3 */

#endif /* CCNS3SIM_MODEL_MESSAGES_CCNX_VALIDATION_PAYLOAD_H_ */
