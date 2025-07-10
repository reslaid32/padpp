/*
 * C-API of ISO9797_M2_BytePadder
 * On PadderFactory with name "iso9797_m2"
 */

// Commited by reslaid32
// ISO9797 M2 Padder

#ifndef PADPPC_ISO9797_M2_BYTE_PADDER_C_H
#define PADPPC_ISO9797_M2_BYTE_PADDER_C_H

#include <stddef.h>
#include <stdint.h>

#include "Support.h"

_PADPP_EXTERN_C _PADPP_CXX_only({)

  typedef void* padpp_iso9797_m2_padder_t;

  _PADPP_PUBLIC padpp_iso9797_m2_padder_t padpp_iso9797_m2_create();
  _PADPP_PUBLIC void padpp_iso9797_m2_destroy(padpp_iso9797_m2_padder_t ctx);

  _PADPP_PUBLIC int padpp_iso9797_m2_pad(
      padpp_iso9797_m2_padder_t ctx, uint8_t* dst, size_t* dst_len,
      const uint8_t* src, size_t src_len, size_t block_size);

  _PADPP_PUBLIC int padpp_iso9797_m2_unpad(
      padpp_iso9797_m2_padder_t ctx, uint8_t* dst, size_t* dst_len,
      const uint8_t* src, size_t src_len, size_t block_size);

_PADPP_CXX_only(
})

#endif
