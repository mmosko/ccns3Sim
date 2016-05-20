/*
 * ccnx-packet-element.h
 *
 *  Created on: May 18, 2016
 *      Author: mmosko
 */

#ifndef CCNS3SIM_MODEL_MESSAGES_CCNX_FIELD_H_
#define CCNS3SIM_MODEL_MESSAGES_CCNX_FIELD_H_

#include <ostream>
#include "ns3/simple-ref-count.h"

namespace ns3
{
  namespace ccnx
  {

    /**
     * Abstract base class for all fields in a CCNx Packet
     */
    class CCNxField : public SimpleRefCount<CCNxField>
    {
    public:
      CCNxField ();
      virtual ~CCNxField ();

//      static TypeId GetTypeId();
//
      virtual std::ostream & Print(std::ostream &os) const = 0;
    };

  } /* namespace ccnx */
} /* namespace ns3 */

#endif /* CCNS3SIM_MODEL_MESSAGES_CCNX_FIELD_H_ */
