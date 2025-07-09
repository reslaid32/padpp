/*
 * C-API of Pkcs7BytePadder
 */

// Commited by reslaid32
// PKCS7 Padder

#ifndef PADDER_FACTORY_C_H
#define PADDER_FACTORY_C_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif
  typedef void* padpp_handle_t;

  padpp_handle_t padpp_create(const char* name);

  void padpp_destroy(padpp_handle_t padder);

  int padpp_pad(padpp_handle_t padder, uint8_t* dst, size_t* dst_len,
                const uint8_t* src, size_t src_len, size_t block_size);

  int padpp_unpad(padpp_handle_t padder, uint8_t* dst, size_t* dst_len,
                  const uint8_t* src, size_t src_len, size_t block_size);
#ifdef __cplusplus
}
#endif

#endif