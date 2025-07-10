/*
 * C-API of Ansi923BytePadder
 * On PadderFactory with name "ansi923"
 */

// Commited by reslaid32
// ANSI 9.23 Padder

#ifndef PADPPC_ANSI923_BYTE_PADDER_C_H
#define PADPPC_ANSI923_BYTE_PADDER_C_H

#include <stddef.h>
#include <stdint.h>

#include "Support.h"

_PADPP_EXTERN_C _PADPP_CXX_only({)

  typedef void* padpp_ansi923_padder_t;

  _PADPP_PUBLIC padpp_ansi923_padder_t padpp_ansi923_create();
  _PADPP_PUBLIC void padpp_ansi923_destroy(padpp_ansi923_padder_t ctx);

  _PADPP_PUBLIC int padpp_ansi923_pad(padpp_ansi923_padder_t ctx, uint8_t* dst,
                                      size_t* dst_len, const uint8_t* src,
                                      size_t src_len, size_t block_size);

  _PADPP_PUBLIC int padpp_ansi923_unpad(padpp_ansi923_padder_t ctx, uint8_t* dst,
                                        size_t* dst_len, const uint8_t* src,
                                        size_t src_len, size_t block_size);

_PADPP_CXX_only(
})

#endif
