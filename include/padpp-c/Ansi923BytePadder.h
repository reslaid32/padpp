/*
 * C-API of Ansi923BytePadder
 * On PadderFactory with name "ansi923"
 */

// Commited by reslaid32
// ANSI 9.23 Padder

#ifndef ANSI923_BYTE_PADDER_C_H
#define ANSI923_BYTE_PADDER_C_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

  typedef void* padpp_ansi923_padder_t;

  padpp_ansi923_padder_t padpp_ansi923_create();
  void padpp_ansi923_destroy(padpp_ansi923_padder_t ctx);

  int padpp_ansi923_pad(padpp_ansi923_padder_t ctx, uint8_t* dst, size_t* dst_len,
                        const uint8_t* src, size_t src_len, size_t block_size);

  int padpp_ansi923_unpad(padpp_ansi923_padder_t ctx, uint8_t* dst, size_t* dst_len,
                          const uint8_t* src, size_t src_len, size_t block_size);

#ifdef __cplusplus
}
#endif

#endif