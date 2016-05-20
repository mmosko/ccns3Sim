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

#ifndef CCNS3SIM_MODEL_PACKETS_CCNX_TYPE_IDENTIFIER_H_
#define CCNS3SIM_MODEL_PACKETS_CCNX_TYPE_IDENTIFIER_H_

#include <ostream>
#include <string>
#include <vector>

namespace ns3
{
  namespace ccnx
  {


    /**
     * @ingroup ccnx-packet
     *
     * NOTE: The text below describes the implementation plan, but the current code does
     * not follow this in complete detail.  Currently, the FixedHeader, PerHopHeader,
     * and Interest/ContentObject codecs are not programmable. Only the codecs for fields
     * inside an Interest, Content Object, and Validation sections are programmable.
     *
     * These codecs are set in the provided implementation.  The user may replace them
     * or add their own codecs for their own types.
     *
     * - 3.1.<type> = Interest fields
     *    - 3.1.0 = Name
     *    - 3.1.1 - Payload
     *    - 3.1.2 = KeyIdRestriction
     *    - 3.1.3 = ContentObjectHashRestriction
     *
     * - 3.2.<type> = Content Object
     *    - 3.2.0 = Name
     *    - 3.2.1 = Payload
     *    - 3.2.5 = PayloadType
     *    - 3.2.6 = Expiry
     *
     * - 3.3.<type> = Validation Algorithm
     *    - 3.3.0x1FFF = Opaque CryptoSuite
     *    - 3.3.0x1FFF.9 = Opaque CryptoSuite KeyId
     *
     * - 4.<type> = Name Segment Codecs
     *    - 4.1 = Name Segment
     *    - 4.2 = IPID
     *    - 4.16 = Chunk
     *    - 4.19 = Version
     *    - 4.0x1000 = App0
     *    - 4.0x1001 = App1
     *    - 4.0x1002 = App2
     *    - 4.0x1003 = App3
     *
     * @subsection Implementation Plan
     *
     * The ccns3Sim packet encoder/decoder uses a SNMP MIB OID style identifier to
     * specify the codec (encoder/decoder) for each field in a packet.  We call these
     * Type Identifiers (TIDs).  This class manages the CCNx TLV Type Identifers (TIDs).
     *
     * This method allows complete packet format variability.  We only provide codec implementations
     * for the CCNx 1.0 TLV format, but a user could replace the "" (empty string) codec to work with any packet
     * format, so long as one can determine it from the leading bytes of the packet.
     *
     * The top-level OID value represents the section of the packet:
     * "" (empty) = Packet Codec
     *
     * TODO: Add a symbolic name, so a TID could be presented as something like
     * "FixedHeader.PT_INTEREST", etc.
     *
     * @subsubsection CCNx 1.0 Packet Codec
     * The default "" (empty) codec implements the CCNx 1.0 TLV packet format.  Currently, this
     * codec is not able to be changed and is only implemented in ccnx-packet.cc.
     *
     * - 1 = Fixed Header Codec (not implemented yet)
     * - 2 = Per Hop header Codec (implemented as CCNxCodecPerHopHeader, not using this scheme yet)
     * - 3 = Packet Body Codec (uses this scheme)
     * - 4 = Name Segment Codecs
     *
     * @subsubsection Fixed Header
     * The fixed header is defined by Version then by PacketType.  There is currenlty only
     * the "version 2" codec:
     *
     * 1.2.<packetType> defines the codec for the fixed header based on the packet type.
     * This allows the user to add new packet types and specify a codec for it.
     *
     * @subsubsection PerHop Headers
     * The per-hop header section is a list of TLVs.  Each TLV codec
     * is referenced as:
     * - 2.<tlvType>
     *
     * @subsubsection Packet Body
     * The packet payload is the CCNx message plus Validation Algorithm plus Validation Payload.
     *
     * The 3.<tlvtype> TID prefix is used for the body of the packet.  There are currently only
     * four TLV types defined in this TID prefix:
     *
     * - 3.1 = Interest
     * - 3.2 = Content Object
     * - 3.3 = Validation Algorithm
     * - 3.4 = Validation Payload
     *
     * @subsubsection CCNxName
     * Within an Interest and ContentObject, the default codec for the CCNxName (3.1.0 and 3.2.0)
     * use the CCNxCodecName class.  This uses the CCNxName registry of name TLV types to dereference the
     * codec.  It is a separate registry from the TLV identifier registry specified here.  It is flat,
     * not hierarchical.
     *
     * - 4.1 = Name Segment
     * - 4.2 = IPID
     * - 4.16 = Chunk
     * - 4.19 = Version
     *
     * @subsubsection Crypto Suite
     * Within the CCNxValidationAlgorithm, the CryptoSuite uses this same TLV Identifier registry.  For
     * example:
     *
     * - 3.3.2 = CRC32C
     * - 3.3.4 = HMAC-SHA256
     * - 3.3.5 = VMAC-128
     * - 3.3.6 = RSA-SHA256
     * - 3.3.7 = EC-SECP-256K1
     * - 3.3.8 = EC-SECP-384R1
     *
     * A user may add their own crypto suite by adding (or replacing) the above TIDs.
     */
    class CCNxTypeIdentifier
    {
    public:
      typedef unsigned IdentiferType;

      /**
       * Creates the root of a TID tree with `value`.
       *
       * @param value
       */
      CCNxTypeIdentifier (IdentiferType value);

      /**
       * Copy constructor
       * @param parent
       */
      CCNxTypeIdentifier (const CCNxTypeIdentifier &parent);

      /**
       * Constructs a child TID from a parent
       *
       * Example:
       * {
       *    CCNxTypeIdentifier parent("3.4.5");
       *    CCNxTypeIdentifier child(parent, 7);
       *    // child = "3.4.5.7"
       * }
       * @param parent The parents type (as a prefix for the child)
       * @param value The child's type value
       */
      CCNxTypeIdentifier (const CCNxTypeIdentifier &parent, IdentiferType value);

      /**
       * Constructs a TID from the string representation
       *
       * Example:
       * @code
       * {
       *    CCNxTypeIdentifier tid("1.2.3.4");
       * }
       * @endcode
       *
       * @param tid The string representation (e.g. "1.2.3.4")
       */
      CCNxTypeIdentifier (const std::string tid);

      virtual ~CCNxTypeIdentifier ();

      /**
       * Returns the canonical string representation of a TID, which
       * is a dotted string like an SNMP OID.
       *
       * Example:
       * @code
       * {
       *     CCNxTypeIdentifier tid("1.2.3.4");
       *     printf("%s", tid.GetTid());
       *     // "1.2.3.4"
       * }
       * @return
       */
      const std::string GetTid() const;

      /**
       * A total order on TIDs, used to store them in a std::map.
       *
       * A TID 'a' is lexicographically less than another TID 'b' if for each TID
       * component (dot separator) if, component by component, each component of 'a'
       * is equal to 'b' or a a first component in 'a' is less than in 'b'.
       *
       * Note that this operates on the numeric value of each component, not the
       * string representation of the TID (as in GetTid()).
       *
       * @param other The other TID to compare against
       * @return true If this TID is lexicographically less than the other TID.
       * @return false if this TID is equal to or greater than other.
       */
      bool operator < (const CCNxTypeIdentifier &other) const;

      /**
       * Two TIDs are equal if they have the same number of components and each
       * component is numerically equal to the other.
       *
       * In this case, one could compare the GetTid() values for the same result.
       *
       * @param other
       * @return true if equal
       * @return false if not equal
       */
      bool operator == (const CCNxTypeIdentifier &other) const;

      /**
       * Negation of operator ==.
       *
       * @param other
       * @return
       */
      bool operator != (const CCNxTypeIdentifier &other) const;

      /**
       * Return the number of components in the TID.
       *
       * For example "1.22.333.4444" has a size of 4.
       *
       * Example:
       * @code
       * {
       *    CCNxTypeIdentifier tid("1.2.3.4");
       *    for (int i = 0; i < tid.size(); ++i) {
       *       printf("%u ", tid[i]);
       *    }
       * }
       * @endcode
       *
       * @return The number of components in the TID
       */
      size_t size() const;

      /**
       * Returns the value of the `offset` TID component.
       *
       * It is an error to ask for a component beyond the `size()` of the TID.
       *
       * Example:
       * @code
       * {
       *    CCNxTypeIdentifier tid("1.2.3.4");
       *    for (int i = 0; i < tid.size(); ++i) {
       *       printf("%u ", tid[i]);
       *    }
       * }
       * @endcode
       *
       * @param offset
       */
      IdentiferType operator [] (size_t offset) const;

      friend std::ostream & operator << (std::ostream &os, const CCNxTypeIdentifier &tid);

    protected:
      std::vector <IdentiferType> m_components;
    };

  } /* namespace ccnx */
} /* namespace ns3 */

#endif /* CCNS3SIM_MODEL_PACKETS_CCNX_TYPE_IDENTIFIER_H_ */
