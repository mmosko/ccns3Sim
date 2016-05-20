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

#include "ns3/ccnx-codec-hashvalue.h"
#include "ns3/ccnx-codec-registry.h"
#include "ns3/ccnx-schema-v1.h"
#include "ns3/ccnx-tlv.h"
#include "ns3/ccnx-hash-value.h"

using namespace ns3;
using namespace ns3::ccnx;

NS_LOG_COMPONENT_DEFINE ("CCNxCodecHashValue");
NS_OBJECT_ENSURE_REGISTERED(CCNxCodecHashValue);

static bool _codecRegistered = false;
static const char * _tidStrings[] = {
    CCNxSchemaV1_TID_INTEREST_KEYIDREST,
    CCNxSchemaV1_TID_INTEREST_HASHREST,
    NULL
};

static void
_RegisterCodec()
{
  if (!_codecRegistered) {
      _codecRegistered = true;
      Ptr<CCNxFieldCodec> codec = CreateObject<CCNxCodecHashValue>();

      for (int i = 0; _tidStrings[i] != NULL; ++i) {
	  CCNxTypeIdentifier tid(_tidStrings[i]);
	  printf("Trying to register %s\n", tid.GetTid().c_str());
	  CCNxCodecRegistry::RegisterTidCodec(tid, codec);
      }
  }
}

TypeId
CCNxCodecHashValue::GetTypeId ()
{
  _RegisterCodec();
  static TypeId tid = TypeId ("ns3::ccnx::CCNxCodecHashValue")
    .SetParent<CCNxFieldCodec> ()
    .AddConstructor<CCNxCodecHashValue> ()
    .SetGroupName ("CCNx");
  return tid;
}

CCNxCodecHashValue::CCNxCodecHashValue ()
{
  // empty
}

CCNxCodecHashValue::~CCNxCodecHashValue ()
{
  // empty
}


TypeId
CCNxCodecHashValue::GetInstanceTypeId () const
{
  return CCNxCodecHashValue::GetTypeId ();
}

Ptr<CCNxField>
CCNxCodecHashValue::Deserialize (Buffer::Iterator &input, const CCNxTypeIdentifier &parent, size_t *bytesRead)
{
  NS_LOG_FUNCTION (this << &input);

  // skip the "T"
  CCNxTlv::ReadType (input);
  uint16_t nestedLength = CCNxTlv::ReadLength (input);

  NS_ASSERT_MSG(nestedLength >= 8, "Must have at least 8 bytes to read");

  uint64_t value = input.ReadNtohU64 ();
  input.Next (nestedLength - 8); // skip the padding

  NS_LOG_DEBUG ("Deserialized KeyIdRestr " << value);

  *bytesRead = nestedLength + CCNxTlv::GetTLSize();

  return Create<CCNxHashValue> (value);
}

uint32_t
CCNxCodecHashValue::GetSerializedSize (Ptr<const CCNxField> packetElement)
{
  Ptr<const CCNxHashValue> hash = DynamicCast<const CCNxHashValue, const CCNxField>(packetElement);
  uint32_t bytes = CCNxTlv::GetTLSize() + hash->GetValue()->size();
  return bytes;
}

void
CCNxCodecHashValue::Serialize (Ptr<const CCNxField> packetElement, uint16_t tlvType, Buffer::Iterator &output)
{
  Ptr<const CCNxHashValue> hash = DynamicCast<const CCNxHashValue, const CCNxField>(packetElement);

  uint32_t bytes = GetSerializedSize(packetElement);
  CCNxTlv::WriteTypeLength (output, tlvType, bytes - CCNxTlv::GetTLSize());
  Ptr<CCNxBuffer> b = hash->CreateBuffer();
  output.Write (b->Begin (), b->End ());
}

void
CCNxCodecHashValue::Print (Ptr<const CCNxField> packetElement, std::ostream &os) const
{
  Ptr<const CCNxHashValue> hash = DynamicCast<const CCNxHashValue, const CCNxField>(packetElement);
  hash->Print(os);
}
