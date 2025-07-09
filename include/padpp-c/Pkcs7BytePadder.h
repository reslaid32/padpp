/*
 * C-API of Pkcs7BytePadder
 * On PadderFactory with name "pkcs7"
 */

// Commited by reslaid32
// PKCS7 Padder

#ifndef PKCS7_BYTE_PADDER_C_H
#define PKCS7_BYTE_PADDER_C_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif
  typedef void* padpp_pkcs7_padder_t;

  padpp_pkcs7_padder_t padpp_pkcs7_create();
  void padpp_pkcs7_destroy(padpp_pkcs7_padder_t ctx);

  int padpp_pkcs7_pad(padpp_pkcs7_padder_t ctx, uint8_t* dst, size_t* dst_len,
                      const uint8_t* src, size_t src_len, size_t block_size);

  int padpp_pkcs7_unpad(padpp_pkcs7_padder_t ctx, uint8_t* dst, size_t* dst_len,
                        const uint8_t* src, size_t src_len, size_t block_size);

#ifdef __cplusplus
}
#endif

#endif