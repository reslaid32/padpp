/*
 * C-API of ISO9797_M2_BytePadder
 * On PadderFactory with name "iso9797_m2"
 */

// Commited by reslaid32
// ISO9797 M2 Padder

#ifndef ISO9797_M2_BYTE_PADDER_C_H
#define ISO9797_M2_BYTE_PADDER_C_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

  typedef void* padpp_iso9797_m2_padder_t;

  padpp_iso9797_m2_padder_t padpp_iso9797_m2_create();
  void padpp_iso9797_m2_destroy(padpp_iso9797_m2_padder_t ctx);

  int padpp_iso9797_m2_pad(padpp_iso9797_m2_padder_t ctx, uint8_t* dst,
                           size_t* dst_len, const uint8_t* src, size_t src_len,
                           size_t block_size);

  int padpp_iso9797_m2_unpad(padpp_iso9797_m2_padder_t ctx, uint8_t* dst,
                             size_t* dst_len, const uint8_t* src,
                             size_t src_len, size_t block_size);

#ifdef __cplusplus
}
#endif

#endif