/**
 * @file ISO9797_M2_BytePadder.h
 * @ingroup capi
 * @brief C API for ISO/IEC 9797-2 Padding Method 2 (M2) padder in padpp.
 *
 * This header defines a C interface for the ISO9797 Method 2 padder.
 * This method supports **only one-way padding** and may not support unpadding reliably.
 *
 * Can also be constructed via the generic PadderFactory using the name `"iso9797_m2"`.
 *
 * @note This implementation is marked as **NOT UNIT TEST READY**.
 */

#ifndef PADPPC_ISO9797_M2_BYTE_PADDER_C_H
#define PADPPC_ISO9797_M2_BYTE_PADDER_C_H

#include <stddef.h>
#include <stdint.h>

#include "./Support.h"
#include "./Type.h"

_PADPP_EXTERN_C_BEGIN

/**
 * @defgroup capi C API
 * @brief Public C interface for the padpp library.
 * @{
 */

/**
 * @brief Creates a new ISO9797 M2 padder instance.
 * @return A handle to the padder, or NULL on failure.
 */
_PADPP_PUBLIC padpp_handle_t padpp_create_iso9797_m2(void);

/**
 * @brief Destroys an ISO9797 M2 padder instance.
 * @param ctx The padder handle to destroy.
 */
_PADPP_PUBLIC void padpp_destroy_iso9797_m2(padpp_handle_t ctx);

/**
 * @brief Applies ISO9797 Method 2 padding to the input data.
 *
 * @param ctx         Padder context.
 * @param dst         Output buffer for padded data.
 * @param dst_len     Input: max size of `dst`; Output: actual size of padded data.
 * @param src         Input buffer with raw data.
 * @param src_len     Size of the input buffer.
 * @param block_size  Block size for padding alignment.
 * @return 0 on success, non-zero on error (e.g. buffer too small).
 */
_PADPP_PUBLIC int padpp_pad_iso9797_m2(padpp_handle_t ctx, uint8_t* dst,
                                       size_t* dst_len, const uint8_t* src,
                                       size_t src_len, size_t block_size);

/**
 * @brief Placeholder for unpadding function for ISO9797 M2.
 *
 * ISO9797 Method 2 is not designed to be reversible in the general case.
 *
 * @param ctx         Padder context.
 * @param dst         Output buffer for unpadded data.
 * @param dst_len     Input: max size of `dst`; Output: actual unpadded length.
 * @param src         Input buffer with padded data.
 * @param src_len     Size of the input buffer.
 * @param block_size  Block size that was used during padding.
 * @return 0 on success (if implemented), non-zero on failure.
 */
_PADPP_PUBLIC int padpp_unpad_iso9797_m2(padpp_handle_t ctx, uint8_t* dst,
                                         size_t* dst_len, const uint8_t* src,
                                         size_t src_len, size_t block_size);

/** @} */

_PADPP_EXTERN_C_END

#endif // PADPPC_ISO9797_M2_BYTE_PADDER_C_H
