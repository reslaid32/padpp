#ifndef VERSION_CONTROLLER_C_H
#define VERSION_CONTROLLER_C_H

struct padpp_Version
{
  const unsigned char maj;
  const unsigned char min;
  const unsigned char pat;
};

typedef struct padpp_Version padpp_version_t;

#ifdef __cplusplus
extern "C"
{
#endif

  padpp_version_t padpp_Version_current();

#ifdef __cplusplus
}
#endif

#endif