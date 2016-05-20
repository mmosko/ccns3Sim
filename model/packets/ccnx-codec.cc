/*
 * ccnx-codec.cc
 *
 *  Created on: May 18, 2016
 *      Author: mmosko
 */

#include "ccnx-codec.h"

using namespace ns3;
using namespace ns3::ccnx;

NS_OBJECT_ENSURE_REGISTERED(CCNxCodec);

TypeId
CCNxCodec::GetTypeId ()
{
  static TypeId tid = TypeId ("ns3::ccnx::CCNxCodec")
    .SetParent<Object> ()
    .SetGroupName ("CCNx");
  return tid;
}

CCNxCodec::CCNxCodec ()
{
  // TODO Auto-generated constructor stub

}

CCNxCodec::~CCNxCodec ()
{
  // TODO Auto-generated destructor stub
}

