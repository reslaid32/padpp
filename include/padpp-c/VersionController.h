#ifndef PADPPC_VERSION_CONTROLLER_C_H
#define PADPPC_VERSION_CONTROLLER_C_H

#include "Support.h"

struct padpp_Version
{
  /*
   * Major: x.x.x
   *        |
   */
  const unsigned char maj;

  /*
   * Minor: x.x.x
   *          |
   */
  const unsigned char min;

  /*
   * Patch: x.x.x
   *            |
   */
  const unsigned char pat;
};

typedef struct padpp_Version padpp_version_t;

_PADPP_EXTERN_C _PADPP_CXX_only({)

  _PADPP_PUBLIC padpp_version_t padpp_Version_current();

_PADPP_CXX_only(
})

#endif
