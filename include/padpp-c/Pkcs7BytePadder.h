/*
 * C-API of Pkcs7BytePadder
 * On PadderFactory with name "pkcs7"
 */

// Commited by reslaid32
// PKCS7 Padder

#ifndef PADPPC_PKCS7_BYTE_PADDER_C_H
#define PADPPC_PKCS7_BYTE_PADDER_C_H

#include <stddef.h>
#include <stdint.h>

#include "Support.h"

_PADPP_EXTERN_C _PADPP_CXX_only({)

  typedef void* padpp_pkcs7_padder_t;

  _PADPP_PUBLIC padpp_pkcs7_padder_t padpp_pkcs7_create();
  _PADPP_PUBLIC void padpp_pkcs7_destroy(padpp_pkcs7_padder_t ctx);

  _PADPP_PUBLIC int padpp_pkcs7_pad(padpp_pkcs7_padder_t ctx, uint8_t* dst,
                                    size_t* dst_len, const uint8_t* src,
                                    size_t src_len, size_t block_size);

  _PADPP_PUBLIC int padpp_pkcs7_unpad(padpp_pkcs7_padder_t ctx, uint8_t* dst,
                                      size_t* dst_len, const uint8_t* src,
                                      size_t src_len, size_t block_size);

_PADPP_CXX_only(
})

#endif
