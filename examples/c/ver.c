
#include <padpp-c/VersionController.h>
#include <stdio.h>

int
main(void)
{
  padpp_version_t ver = padpp_Version_current();
  printf("padpp version: %u.%u.%u\n", ver.maj, ver.min, ver.pat);
  return 0;
}