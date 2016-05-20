/*
 * ccnx-tid-codec.cc
 *
 *  Created on: May 18, 2016
 *      Author: mmosko
 */

#include "ccnx-field-codec.h"

using namespace ns3;
using namespace ns3::ccnx;

NS_OBJECT_ENSURE_REGISTERED(CCNxFieldCodec);

TypeId
CCNxFieldCodec::GetTypeId ()
{
  static TypeId tid = TypeId ("ns3::ccnx::CCNxFieldCodec")
    .SetParent<CCNxCodec> ()
    .SetGroupName ("CCNx");
  return tid;
}

CCNxFieldCodec::CCNxFieldCodec ()
{
  // TODO Auto-generated constructor stub

}

CCNxFieldCodec::~CCNxFieldCodec ()
{
  // TODO Auto-generated destructor stub
}

