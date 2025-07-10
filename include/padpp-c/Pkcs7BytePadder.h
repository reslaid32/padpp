/**
 * @file Pkcs7BytePadder.h
 * @ingroup capi
 * @brief C API for PKCS7 padding implementation in padpp.
 *
 * This header provides functions for creating, destroying, and using a PKCS7 padder.
 *
 * It can also be created via the generic PadderFactory using the name `"pkcs7"`.
 */

#ifndef PADPPC_PKCS7_BYTE_PADDER_C_H
#define PADPPC_PKCS7_BYTE_PADDER_C_H

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
 * @brief Creates a new PKCS7 padder instance.
 * @return A handle to the newly created PKCS7 padder.
 */
_PADPP_PUBLIC padpp_handle_t padpp_create_pkcs7(void);

/**
 * @brief Destroys a previously created PKCS7 padder instance.
 * @param ctx The padder handle to destroy.
 */
_PADPP_PUBLIC void padpp_destroy_pkcs7(padpp_handle_t ctx);

/**
 * @brief Pads input data using PKCS7.
 *
 * @param ctx        The padder context.
 * @param dst        Output buffer (must be large enough to hold padded data).
 * @param dst_len    Input: size of dst buffer; Output: actual size of padded data.
 * @param src        Input buffer to pad.
 * @param src_len    Length of input buffer.
 * @param block_size Block size to pad to.
 * @return 0 on success, non-zero on error.
 */
_PADPP_PUBLIC int padpp_pad_pkcs7(padpp_handle_t ctx, uint8_t* dst,
                                  size_t* dst_len, const uint8_t* src,
                                  size_t src_len, size_t block_size);

/**
 * @brief Removes PKCS7 padding from input data.
 *
 * @param ctx        The padder context.
 * @param dst        Output buffer for unpadded data.
 * @param dst_len    Input: size of dst buffer; Output: actual size of unpadded data.
 * @param src        Input buffer with padded data.
 * @param src_len    Length of input buffer.
 * @param block_size Block size used during padding.
 * @return 0 on success, non-zero on error.
 */
_PADPP_PUBLIC int padpp_unpad_pkcs7(padpp_handle_t ctx, uint8_t* dst,
                                    size_t* dst_len, const uint8_t* src,
                                    size_t src_len, size_t block_size);

/** @} */

_PADPP_EXTERN_C_END

#endif // PADPPC_PKCS7_BYTE_PADDER_C_H
