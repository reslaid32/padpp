/**
 * @file ISO9797_M1_BytePadder.h
 * @ingroup cppapi
 * @brief C++ implementation of the ISO/IEC 9797-1 Padding Method 1 (M1).
 *
 * This class implements the ISO9797-1 Method 1 padding algorithm.
 * The algorithm appends zero bytes (0x00) to the input until its size is a multiple of block size.
 * The implementation is available in the PadderFactory under the name `"iso9797_m1"`.
 *
 * @note This implementation is **one-way padding only**, and is **not unit test ready**.
 *       The `unpad()` method is currently a placeholder and may not work correctly.
 */

#pragma once

#include "IBytePadder.h"
#include "Support.h"

namespace padpp
{

/**
 * @ingroup cppapi
 * @brief ISO9797 Method 1 padder implementation.
 *
 * Adds zero-byte padding as per ISO/IEC 9797-1 Method 1.
 * Designed for block-aligned padding with fixed-size ciphers.
 */
struct _PADPP_PUBLIC ISO9797_M1_BytePadder : public IBytePadder
{
  /**
   * @brief Applies ISO9797 M1 padding to the input buffer.
   *
   * Pads `src` with 0x00 bytes to the next multiple of `blk_sz`.
   *
   * @param dst       Output buffer for padded result.
   * @param src       Input buffer.
   * @param blk_sz    Block size to pad to.
   */
  void pad(byte_buffer& dst, byte_span src, size_type blk_sz) const override;

  /**
   * @brief Unpadding is not fully supported for this algorithm.
   *
   * The Method 1 scheme does not carry padding length, so this function may not reliably remove padding.
   *
   * @param dst       Output buffer for unpadded result.
   * @param src       Padded input buffer.
   * @param blk_sz    Block size used during padding.
   */
  void unpad(byte_buffer& dst, byte_span src, size_type blk_sz) const override;
};

} // namespace padpp
