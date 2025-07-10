/**
 * @file ISO9797_M2_BytePadder.h
 * @ingroup cppapi
 * @brief C++ implementation of the ISO/IEC 9797-1 Padding Method 2 (M2).
 *
 * This padder implements the ISO 9797-1 Method 2 (also known as bit padding).
 * It appends a `0x80` byte followed by zero or more `0x00` bytes to align the buffer to a block size.
 *
 * The implementation is registered in the PadderFactory under the name `"iso9797_m2"`.
 */

#pragma once

#include "IBytePadder.h"
#include "Support.h"

namespace padpp
{

/**
 * @ingroup cppapi
 * @brief ISO9797 Method 2 padder implementation.
 *
 * Performs bit padding using a `0x80` followed by `0x00` bytes.
 * Commonly used in CBC-MAC and legacy cryptographic systems.
 *
 * Example:
 * ```cpp
 * padpp::ISO9797_M2_BytePadder padder;
 * std::vector<uint8_t> out;
 * padder.pad(out, in, 8);
 * ```
 */
struct _PADPP_PUBLIC ISO9797_M2_BytePadder : public IBytePadder
{
  /**
   * @brief Pads the input buffer using ISO9797 M2 scheme.
   *
   * Appends 0x80 and zero bytes to align to `blk_sz`.
   *
   * @param dst       Destination buffer for padded result.
   * @param src       Input buffer.
   * @param blk_sz    Block size to pad to.
   */
  void pad(byte_buffer& dst, byte_span src, size_type blk_sz) const override;

  /**
   * @brief Removes ISO9797 M2 padding from the input.
   *
   * Searches for 0x80 from the end, removing trailing 0x00 bytes.
   *
   * @param dst       Destination buffer for unpadded data.
   * @param src       Padded input buffer.
   * @param blk_sz    Block size used during padding.
   */
  void unpad(byte_buffer& dst, byte_span src, size_type blk_sz) const override;
};

} // namespace padpp
