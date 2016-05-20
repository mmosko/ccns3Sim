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

#include <stdlib.h>

#include "ns3/assert.h"
#include "ccnx-type-identifier.h"

using namespace ns3;
using namespace ns3::ccnx;

CCNxTypeIdentifier::CCNxTypeIdentifier (CCNxTypeIdentifier::IdentiferType value)
{
  m_components.push_back(value);
  std::cout << "CCNxTypeIdentifier value: " << GetTid() << std::endl;
}

CCNxTypeIdentifier::CCNxTypeIdentifier (const CCNxTypeIdentifier::CCNxTypeIdentifier &parent)
{
  m_components = parent.m_components;
  std::cout << "CCNxTypeIdentifier copy: " << parent.GetTid() << " to "<< GetTid() << std::endl;
}

CCNxTypeIdentifier::CCNxTypeIdentifier (const CCNxTypeIdentifier &parent, CCNxTypeIdentifier::IdentiferType value)
{
  m_components = parent.m_components;
  m_components.push_back(value);
  std::cout << "CCNxTypeIdentifier append: " << parent.GetTid() << " to "<< GetTid() << std::endl;
}

CCNxTypeIdentifier::CCNxTypeIdentifier (const std::string tid)
{
  // Need to strdup it because we don't want to modify the original TID
  char *cstr = strdup(tid.c_str());
  char *p = strtok(cstr, ".");
  while (p) {
      int value = atoi(p);
      m_components.push_back(value);
      p = strtok(NULL, ".");
  }
  free(cstr);
}

CCNxTypeIdentifier::~CCNxTypeIdentifier ()
{
  // empty
}

const std::string
CCNxTypeIdentifier::GetTid() const
{
  // Inefficient, but correct.  We should cache this value as the CCNxTypeIdentifier is a const class.
  std::string s;
  if (size() > 0) {
      s.append(std::to_string(m_components[0]));
  }

  for (int i = 1; i < size(); ++i) {
      s.append(".");
      s.append(std::to_string(m_components[i]));
  }

  return s;
}

bool
CCNxTypeIdentifier::operator < (const CCNxTypeIdentifier &other) const
{
  // Assuming all components are equal, the shorter one is less
  bool isLess = (size() < other.size() ? true : false);
  size_t minsize = std::min(size(), other.size());

  for (size_t i = 0; i < minsize; ++i) {
      if (m_components[i] < other.m_components[i]) {
	  isLess = true;
	  break;
      } else if (m_components[i] > other.m_components[i]) {
	  isLess = false;
	  break;
      }
  }
  return isLess;
}


bool
CCNxTypeIdentifier::operator == (const CCNxTypeIdentifier &other) const
{
  bool isEqual = false;
  if (size() == other.size()) {
      isEqual = true;
      for (int i = 0; i < size(); i++) {
	  if (m_components[i] != other.m_components[i]) {
	      isEqual = false;
	      break;
	  }
      }
  }
  return isEqual;
}

bool
CCNxTypeIdentifier::operator != (const CCNxTypeIdentifier &other) const
{
  return !(*this == other);
}

size_t
CCNxTypeIdentifier::size() const
{
  return m_components.size();
}

CCNxTypeIdentifier::IdentiferType
CCNxTypeIdentifier::operator [] (size_t offset) const
{
  NS_ASSERT_MSG(offset < size(), "Component " << offset << " beyond size " << size());
  return m_components[offset];
}

std::ostream &
ns3::ccnx::operator << (std::ostream &os, const CCNxTypeIdentifier &tid)
{
  os << tid.GetTid();
  return os;
}
