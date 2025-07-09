#pragma once

namespace padpp
{

struct Version
{
  const unsigned char maj, min, pat;

  static Version& current();
};

}
