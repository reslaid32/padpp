#pragma once

#include "Support.h"

namespace padpp
{

struct _PADPP_PUBLIC Version
{
  const unsigned char maj, min, pat;

  static Version& current();
};

}
