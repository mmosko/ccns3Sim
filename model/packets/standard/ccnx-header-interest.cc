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

#include "ns3/log.h"
#include "ns3/ccnx-header-interest.h"
#include "ns3/ccnx-schema-v1.h"
#include "ns3/ccnx-tlv.h"
#include "ns3/ccnx-type-identifier.h"
#include "ns3/ccnx-codec-registry.h"

using namespace ns3;
using namespace ns3::ccnx;

NS_LOG_COMPONENT_DEFINE ("CCNxHeaderInterest");

NS_OBJECT_ENSURE_REGISTERED (CCNxHeaderInterest);

static const CCNxTypeIdentifier _tidName("3.1.0");
static const CCNxTypeIdentifier _tidPayload("3.1.1");
static const CCNxTypeIdentifier _tidKeyIdRestr("3.1.2");
static const CCNxTypeIdentifier _tidHashRestr("3.1.3");

TypeId
CCNxHeaderInterest::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::ccnx::CCNxHeaderInterest")
    .SetParent<Header> ()
    .SetGroupName ("CCNx")
    .AddConstructor<CCNxHeaderInterest> ();
  return tid;
}

TypeId
CCNxHeaderInterest::GetInstanceTypeId (void) const
{
  return GetTypeId ();
}


void
CCNxHeaderInterest::DoInitialize()
{
  Ptr<CCNxFieldCodec> m_nameCodec = CCNxCodecRegistry::LookupTidCodec(_tidName);
  Ptr<CCNxFieldCodec> m_keyIdRestrictionCodec = CCNxCodecRegistry::LookupTidCodec(_tidKeyIdRestr);
  Ptr<CCNxFieldCodec> m_hashRestrictionCodec = CCNxCodecRegistry::LookupTidCodec(_tidHashRestr);
  Ptr<CCNxFieldCodec> m_payloadCodec = CCNxCodecRegistry::LookupTidCodec(_tidPayload);
}

// virtual from Header

uint32_t
CCNxHeaderInterest::GetSerializedSize (void) const
{
  uint32_t bytes = CCNxTlv::GetTLSize ();     // first header
  bytes += m_nameCodec->GetSerializedSize (m_interest->GetName()); // name TLV

  if (m_interest->GetKeyidRestriction ())
    {
      bytes += m_keyIdRestrictionCodec->GetSerializedSize(m_interest->GetKeyidRestriction ());
    }

  if (m_interest->GetHashRestriction ())
    {
      bytes += m_hashRestrictionCodec->GetSerializedSize(m_interest->GetHashRestriction ());
    }

  if (m_interest->GetPayload ())
    {
      bytes += m_payloadCodec->GetSerializedSize(m_interest->GetPayload ());
    }

  return bytes;
}

void
CCNxHeaderInterest::Serialize (Buffer::Iterator outputIterator) const
{
  NS_LOG_FUNCTION (this << &outputIterator);

  uint16_t bytes = (uint16_t) GetSerializedSize ();
  NS_ASSERT_MSG (bytes >= CCNxTlv::GetTLSize (), "Serialize size must be at least 4 bytes");

  // -4 because it includes the T_INTEREST TLV.
  CCNxTlv::WriteTypeLength (outputIterator, CCNxSchemaV1::T_INTEREST, bytes - CCNxTlv::GetTLSize ());

  // The name codec includes the T_NAME TLV
  m_nameCodec->Serialize (m_interest->GetName(), CCNxSchemaV1::T_NAME, outputIterator);

  if (m_interest->GetKeyidRestriction ())
    {
      m_keyIdRestrictionCodec->Serialize(m_interest->GetKeyidRestriction (), CCNxSchemaV1::T_KEYID_REST, outputIterator);
    }

  if (m_interest->GetHashRestriction ())
    {
      m_hashRestrictionCodec->Serialize(m_interest->GetKeyidRestriction (), CCNxSchemaV1::T_HASH_REST, outputIterator);
    }

  if (m_interest->GetPayload ())
    {
      m_hashRestrictionCodec->Serialize(m_interest->GetPayload (), CCNxSchemaV1::T_PAYLOAD, outputIterator);
    }
}

uint32_t
CCNxHeaderInterest::Deserialize (Buffer::Iterator inputIterator)
{
  NS_LOG_FUNCTION (this << &inputIterator);
  NS_ASSERT_MSG (inputIterator.GetSize () >= CCNxTlv::GetTLSize (), "Need to have at least 4 bytes to read");
  Buffer::Iterator iterator = inputIterator;

  uint32_t bytesRead = 0;

  uint16_t messageType = CCNxTlv::ReadType (iterator);
  if (messageType == CCNxSchemaV1::T_INTEREST)
    {
      uint16_t messageLength = CCNxTlv::ReadLength (iterator);
      NS_LOG_DEBUG ("Message type " << messageType << " length " << messageLength);

      // Do not count the initial 4 bytes read until the very end so we can compare
      // bytesRead against messageLength (which is the inner length)

      Ptr<const CCNxName> name;
      Ptr<CCNxHashValue> keyidRestr = Ptr<CCNxHashValue> (0);
      Ptr<CCNxHashValue> hashRestr = Ptr<CCNxHashValue> (0);
      Ptr<CCNxBuffer> payload = Ptr<CCNxBuffer> (0);

      const CCNxTypeIdentifier interestTid(CCNxSchemaV1_TID_INTEREST);

      while (bytesRead < messageLength)
        {
          uint16_t nestedType = CCNxTlv::ReadType (iterator);
          uint16_t nestedLength = CCNxTlv::ReadLength (iterator);

          // now backup for 4 bytes
          iterator.Prev(CCNxTlv::GetTLSize());

          bytesRead += CCNxTlv::GetTLSize ();

          NS_LOG_DEBUG ("Nested  type " << nestedType << " length " << nestedLength << " bytesRead " << bytesRead);
          NS_ASSERT_MSG (bytesRead + nestedLength <= messageLength, "length goes beyond end of messageLength");

          size_t bytesRead = 0;
          CCNxTypeIdentifier nestedTid(interestTid, nestedType);
          switch (nestedType)
            {
            case CCNxSchemaV1::T_NAME:
              {
        	Ptr<CCNxField> field = m_nameCodec->Deserialize(iterator, nestedTid, &bytesRead);
		name = DynamicCast<CCNxName, CCNxField>(field);
		break;
              }

            case CCNxSchemaV1::T_KEYID_REST:
              {
        	Ptr<CCNxField> field = m_keyIdRestrictionCodec->Deserialize(iterator, nestedTid, &bytesRead);
		keyidRestr = DynamicCast<CCNxHashValue, CCNxField>(field);
		break;
              }

            case CCNxSchemaV1::T_HASH_REST:
              {
        	Ptr<CCNxField> field = m_hashRestrictionCodec->Deserialize(iterator, nestedTid, &bytesRead);
        	hashRestr = DynamicCast<CCNxHashValue, CCNxField>(field);
		break;
              }

            case CCNxSchemaV1::T_PAYLOAD:
              {
        	Ptr<CCNxField> field = m_payloadCodec->Deserialize(iterator, nestedTid, &bytesRead);
        	payload = DynamicCast<CCNxBuffer, CCNxField>(field);
		break;
              }

            default:
              NS_ASSERT_MSG (true, "Unknown nested type " << nestedType);
            }

          bytesRead += nestedLength;
        }

      m_interest = Create<CCNxInterest> (name, payload, keyidRestr, hashRestr);

    }
  else
    {
      NS_ASSERT_MSG (false, "Message type is not T_INTEREST");
    }

  // add the initial TL length
  return bytesRead + CCNxTlv::GetTLSize ();
}

//Ptr<const CCNxName>
//CCNxHeaderInterest::DeserializeName (Buffer::Iterator &start, uint16_t length)
//{
//  NS_LOG_FUNCTION (this << &start);
//
//  /*
//   * The while loop in Deserialize has read the 4 bytes of T and L of the T_NAME
//   * So we need to back up 4 bytes so CCNxCodecName can read the T_NAME and length.
//   */
//  start.Prev (CCNxTlv::GetTLSize ());
//  m_nameCodec.Deserialize (start);
//  NS_LOG_DEBUG ("Deserialized name " << m_nameCodec.GetHeader ());
//
//  // now skip over the name
//  start.Next (length + CCNxTlv::GetTLSize ());
//
//  return m_nameCodec.GetHeader ();
//}
//
//Ptr<CCNxHashValue>
//CCNxHeaderInterest::DeserializeKeyIdRest (Buffer::Iterator &start, uint16_t length)
//{
//  NS_LOG_FUNCTION (this << &start);
//
//  // We defined a CCNxHashValue as an 8 byte value plus 24 bytes of padding.
//  NS_ASSERT_MSG (length >= 8, "Must be at least 8 bytes in KeyIdRestriction");
//
//  uint64_t value = start.ReadNtohU64 ();
//  start.Next (length - 8); // skip the padding
//
//  NS_LOG_DEBUG ("Deserialized KeyIdRestr " << value);
//
//  return Create<CCNxHashValue> (value);
//}
//
//Ptr<CCNxHashValue>
//CCNxHeaderInterest::DeserializeHashRest (Buffer::Iterator &start, uint16_t length)
//{
//  NS_LOG_FUNCTION (this << &start);
//  NS_ASSERT_MSG (length >= 8, "Must be at least 8 bytes in ObjectHashRestriction");
//
//  uint64_t value = start.ReadNtohU64 ();
//  start.Next (length - 8); // skip the padding
//
//  NS_LOG_DEBUG ("Deserialized ObjectHashRestr " << value);
//  return Create<CCNxHashValue> (value);
//}
//
//Ptr<CCNxBuffer>
//CCNxHeaderInterest::DeserializePayload (Buffer::Iterator &start, uint16_t length)
//{
//  NS_LOG_FUNCTION (this << &start);
//
//  Ptr<CCNxBuffer> payload = Create<CCNxBuffer> (0);
//  payload->AddAtStart (length);
//  start.Read (payload->Begin (), length);
//
//  NS_LOG_DEBUG ("Deserialized Payload length " << length);
//  return payload;
//}

void
CCNxHeaderInterest::Print (std::ostream &os) const
{
  if (m_interest)
    {
      os << *m_interest;
    }
  else
    {
      os << "NULL header";
    }
}

CCNxHeaderInterest::CCNxHeaderInterest () : m_interest (0)
{
  // empty
}

CCNxHeaderInterest::~CCNxHeaderInterest ()
{
  // empty (use DoDispose)
}

Ptr<CCNxInterest>
CCNxHeaderInterest::GetHeader () const
{
  return m_interest;
}

void
CCNxHeaderInterest::SetHeader (Ptr<CCNxInterest> interest)
{
  m_interest = interest;
}

