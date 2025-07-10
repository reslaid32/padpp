/**
 * @file ISO9797_M2_BytePadder.h
 * @ingroup capi
 * @brief C API for ISO/IEC 9797-1 Padding Method 2 (M2) padder in padpp.
 *
 * This header defines a standalone interface to the ISO9797 Method 2 padder,
 * usable directly from C.
 *
 * It can also be created via the generic PadderFactory using the name `"iso9797_m2"`.
 */

#ifndef PADPPC_ISO9797_M2_BYTE_PADDER_C_H
#define PADPPC_ISO9797_M2_BYTE_PADDER_C_H

#include <stddef.h>
#include <stdint.h>

#include "./Support.h"
#include "./Type.h"

/**
 * @defgroup capi C API
 * @brief Public C interface for the padpp library.
 * @{
 */

_PADPP_EXTERN_C _PADPP_CXX_only({)

  /**
   * @brief Creates a new ISO9797 M2 padder instance.
   * @return A handle to the padder, or NULL on error.
   */
  _PADPP_PUBLIC padpp_handle_t padpp_create_iso9797_m2(void);

  /**
   * @brief Destroys an ISO9797 M2 padder instance.
   * @param ctx Padder handle to destroy.
   */
  _PADPP_PUBLIC void padpp_destroy_iso9797_m2(padpp_handle_t ctx);

  /**
   * @brief Pads data using ISO9797 Method 2.
   *
   * @param ctx         Padder context.
   * @param dst         Output buffer for padded data.
   * @param dst_len     Input: size of `dst`; Output: actual padded length.
   * @param src         Input buffer with raw data.
   * @param src_len     Size of input buffer.
   * @param block_size  Block size to align to.
   * @return 0 on success, non-zero on error.
   */
  _PADPP_PUBLIC int padpp_pad_iso9797_m2(padpp_handle_t ctx, uint8_t* dst,
                                         size_t* dst_len, const uint8_t* src,
                                         size_t src_len, size_t block_size);

  /**
   * @brief Removes ISO9797 Method 2 padding from data.
   *
   * @param ctx         Padder context.
   * @param dst         Output buffer for unpadded data.
   * @param dst_len     Input: size of `dst`; Output: actual unpadded length.
   * @param src         Input buffer with padded data.
   * @param src_len     Size of input buffer.
   * @param block_size  Block size originally used for padding.
   * @return 0 on success, non-zero on error.
   */
  _PADPP_PUBLIC int padpp_unpad_iso9797_m2(padpp_handle_t ctx, uint8_t* dst,
                                           size_t* dst_len, const uint8_t* src,
                                           size_t src_len, size_t block_size);

_PADPP_CXX_only(
})

/** @} */ // end of capi

#endif // PADPPC_ISO9797_M2_BYTE_PADDER_C_H
