#define _PADPP_BUILDING

#include "../include/padpp-c/Support.h"

#include "../include/padpp-c/Version.h"
#include "../include/padpp/Version.h"

static padpp::Version _version = { 0, 1, 2 };

padpp::Version&
padpp::Version::current()
{
  return _version;
}

extern "C"
{
  _PADPP_PUBLIC padpp_version_t
  padpp_Version_current()
  {
    return { _version.maj, _version.min, _version.pat };
  }
}
