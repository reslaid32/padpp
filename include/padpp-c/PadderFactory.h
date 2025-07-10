/*
 * C-API of Pkcs7BytePadder
 */

// Commited by reslaid32
// PKCS7 Padder

#ifndef PADPPC_PADDER_FACTORY_C_H
#define PADPPC_PADDER_FACTORY_C_H

#include <stddef.h>
#include <stdint.h>

#include "Support.h"

_PADPP_EXTERN_C _PADPP_CXX_only({)

  typedef void* padpp_handle_t;

  _PADPP_PUBLIC padpp_handle_t padpp_create(const char* name);

  _PADPP_PUBLIC void padpp_destroy(padpp_handle_t padder);

  _PADPP_PUBLIC int padpp_pad(padpp_handle_t padder, uint8_t* dst,
                              size_t* dst_len, const uint8_t* src,
                              size_t src_len, size_t block_size);

  _PADPP_PUBLIC int padpp_unpad(padpp_handle_t padder, uint8_t* dst,
                                size_t* dst_len, const uint8_t* src,
                                size_t src_len, size_t block_size);
_PADPP_CXX_only(
})

#endif
