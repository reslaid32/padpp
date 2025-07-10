/**
 * @file PadderFactory.h
 * @ingroup capi
 * @brief Generic C API padder factory interface for padpp.
 *
 * Provides a generic interface to create and use any padder implementation
 * by name (e.g. "pkcs7", "iso9797_m1", etc).
 *
 * This interface abstracts away the specific algorithm and exposes a uniform
 * way to pad/unpad data using dynamically selected strategies.
 */

#ifndef PADPPC_PADDER_FACTORY_C_H
#define PADPPC_PADDER_FACTORY_C_H

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
 * @brief Creates a new padder instance by name.
 *
 * @param name Name of the padder (e.g. "pkcs7", "iso9797_m1").
 * @return Handle to the created padder instance, or NULL on failure.
 */
_PADPP_PUBLIC padpp_handle_t padpp_create(const char* name);

  /**
   * @brief Destroys a padder instance.
   *
   * @param padder The padder handle to destroy.
   */
  _PADPP_PUBLIC void padpp_destroy(padpp_handle_t padder);

  /**
   * @brief Applies padding using the selected padder.
   *
   * @param padder      The padder context.
   * @param dst         Output buffer (must be large enough).
   * @param dst_len     Input: max length of `dst`, Output: actual padded length.
   * @param src         Input buffer with raw data.
   * @param src_len     Length of input buffer.
   * @param block_size  Block size for padding.
   * @return 0 on success, non-zero on error (e.g. invalid input or buffer too small).
   */
  _PADPP_PUBLIC int padpp_pad(padpp_handle_t padder, uint8_t* dst,
                              size_t* dst_len, const uint8_t* src,
                              size_t src_len, size_t block_size);

  /**
   * @brief Removes padding from a previously padded buffer.
   *
   * @param padder      The padder context.
   * @param dst         Output buffer for unpadded data.
   * @param dst_len     Input: max length of `dst`, Output: actual unpadded length.
   * @param src         Input buffer with padded data.
   * @param src_len     Length of input buffer.
   * @param block_size  Block size used during padding.
   * @return 0 on success, non-zero on error (e.g. invalid padding).
   */
  _PADPP_PUBLIC int padpp_unpad(padpp_handle_t padder, uint8_t* dst,
                                size_t* dst_len, const uint8_t* src,
                                size_t src_len, size_t block_size);

_PADPP_CXX_only(
})

/** @} */ // end of capi

#endif // PADPPC_PADDER_FACTORY_C_H
