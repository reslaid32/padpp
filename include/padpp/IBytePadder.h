/**
 * @file IBytePadder.h
 * @ingroup cppapi
 * @brief Interface for all byte-oriented padding strategies in padpp.
 *
 * This interface defines the core contract for any block padding algorithm.
 * Implementations should inherit from this and implement `pad()` and `unpad()`.
 *
 * Common derived implementations:
 * - Ansi923BytePadder
 * - Pkcs7BytePadder
 * - ISO9797_M1_BytePadder
 * - ISO9797_M2_BytePadder
 */

#pragma once

#include <cstddef>
#include <cstdint>
#include <span>
#include <vector>

namespace padpp
{

/**
 * @ingroup cppapi
 * @brief Abstract base class for byte-level padder algorithms.
 */
struct IBytePadder
{
  /// Type for byte counts and lengths.
  using size_type = std::size_t;

  /// View over a buffer of bytes.
  using byte_span = std::span<std::uint8_t>;

  /// Writable dynamic byte buffer.
  using byte_buffer = std::vector<std::uint8_t>;

  /**
   * @brief Applies padding to `src`, writing to `dst`.
   *
   * Implementations must align `src` to the specified `blk_sz`, writing the result into `dst`.
   *
   * @param dst       Destination buffer to receive padded data.
   * @param src       Input buffer (unmodified).
   * @param blk_sz    Block size for alignment.
   */
  virtual void pad(byte_buffer& dst, byte_span src, size_type blk_sz) const = 0;

  /**
   * @brief Removes padding from `src`, writing to `dst`.
   *
   * Implementations must detect and strip the padding applied during `pad()`.
   *
   * @param dst       Destination buffer to receive unpadded data.
   * @param src       Padded input buffer.
   * @param blk_sz    Block size originally used for padding.
   */
  virtual void unpad(byte_buffer& dst, byte_span src, size_type blk_sz) const = 0;

  /// Virtual destructor for safe polymorphic usage.
  virtual ~IBytePadder() = default;
};

} // namespace padpp
