#include "../include/padpp/VersionController.h"
#include "../include/padpp-c/VersionController.h"

static padpp::Version _version = { 0, 1, 0 };

padpp::Version&
padpp::Version::current()
{
  return _version;
}

extern "C"
{
  padpp_version_t
  padpp_Version_current()
  {
    return { _version.maj, _version.min, _version.pat };
  }
}
