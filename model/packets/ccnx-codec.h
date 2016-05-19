/*
 * ccnx-codec.h
 *
 *  Created on: May 18, 2016
 *      Author: mmosko
 */

#ifndef CCNS3SIM_MODEL_PACKETS_STANDARD_CCNX_CODEC_H_
#define CCNS3SIM_MODEL_PACKETS_STANDARD_CCNX_CODEC_H_

#include "ns3/object.h"

namespace ns3
{
  namespace ccnx
  {

    /**
     * A general codec.
     *
     * It is specialized as a `CCNxNs3PacketCodec` to decode an NS3 packet and
     * a `CCNxFieldCodec` to decode fields within an NS3 packet.  The difference
     * is that a packet codec takes an `ns3::Packet` as its arguments and
     * a field codec takes an `ns3::BufferIterator` as its argument.
     */
    class CCNxCodec : public Object
    {
    public:
      CCNxCodec ();
      virtual ~CCNxCodec ();
      static TypeId GetTypeId();
      virtual TypeId GetInstanceTypeId (void) const = 0;

    };

  } /* namespace ccnx */
} /* namespace ns3 */

#endif /* CCNS3SIM_MODEL_PACKETS_STANDARD_CCNX_CODEC_H_ */
