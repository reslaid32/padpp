/**
 * @file Ansi923BytePadder.h
 * @ingroup capi
 * @brief C API for ANSI X9.23 padding padder in padpp.
 *
 * This header defines a C interface for the ANSI X9.23 padding algorithm.
 *
 * It can also be created via the generic PadderFactory using the name `"ansi923"`.
 */

#ifndef PADPPC_ANSI923_BYTE_PADDER_C_H
#define PADPPC_ANSI923_BYTE_PADDER_C_H

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
 * @brief Creates a new ANSI923 padder instance.
 *
 * @return A handle to the padder, or NULL on failure.
 */
_PADPP_PUBLIC padpp_handle_t padpp_create_ansi923(void);

/**
 * @brief Destroys an ANSI923 padder instance.
 *
 * @param ctx The padder handle to destroy.
 */
_PADPP_PUBLIC void padpp_destroy_ansi923(padpp_handle_t ctx);

/**
 * @brief Applies ANSI X9.23 padding to input data.
 *
 * @param ctx         Padder context.
 * @param dst         Output buffer for padded data.
 * @param dst_len     Input: max size of `dst`; Output: actual padded size.
 * @param src         Input buffer to be padded.
 * @param src_len     Length of input buffer.
 * @param block_size  Padding block size.
 * @return 0 on success, non-zero on error.
 */
_PADPP_PUBLIC int padpp_pad_ansi923(padpp_handle_t ctx, uint8_t* dst,
                                    size_t* dst_len, const uint8_t* src,
                                    size_t src_len, size_t block_size);

/**
 * @brief Removes ANSI X9.23 padding from input data.
 *
 * @param ctx         Padder context.
 * @param dst         Output buffer for unpadded data.
 * @param dst_len     Input: max size of `dst`; Output: actual unpadded size.
 * @param src         Input buffer with padded data.
 * @param src_len     Length of input buffer.
 * @param block_size  Block size originally used for padding.
 * @return 0 on success, non-zero on error.
 */
_PADPP_PUBLIC int padpp_unpad_ansi923(padpp_handle_t ctx, uint8_t* dst,
                                      size_t* dst_len, const uint8_t* src,
                                      size_t src_len, size_t block_size);

/** @} */

_PADPP_EXTERN_C_END

#endif // PADPPC_ANSI923_BYTE_PADDER_C_H
