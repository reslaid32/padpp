
#include <padpp/Version.h>
#include <stdio.h>

int
main(void)
{
  padpp::Version ver = padpp::Version::current();
  printf("padpp version: %u.%u.%u\n", ver.maj, ver.min, ver.pat);
  return 0;
}