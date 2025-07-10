/**
 * @file Pkcs7BytePadder.h
 * @ingroup cppapi
 * @brief C++ implementation of the PKCS#7 padding algorithm.
 *
 * This padder implements PKCS#7 (also known as PKCS7) padding, commonly used in cryptographic
 * protocols such as CMS, TLS, and block cipher encryption with padding.
 *
 * The implementation is registered in the PadderFactory under the name `"pkcs7"`.
 */

#pragma once

#include "IBytePadder.h"
#include "Support.h"

namespace padpp
{

/**
 * @ingroup cppapi
 * @brief PKCS#7 byte padder implementation.
 *
 * Pads input so that total size becomes a multiple of block size by appending N
 * bytes, each with the value N (e.g., `0x03 0x03 0x03` if 3 bytes needed).
 */
struct _PADPP_PUBLIC Pkcs7BytePadder : public IBytePadder
{
  /**
   * @brief Applies PKCS#7 padding to the input buffer.
   *
   * Appends bytes of value equal to the padding length.
   *
   * @param dst       Output buffer for padded result.
   * @param src       Input buffer to pad.
   * @param blk_sz    Block size to align to.
   */
  void pad(byte_buffer& dst, byte_span src, size_type blk_sz) const override;

  /**
   * @brief Removes PKCS#7 padding from the input buffer.
   *
   * Validates and strips trailing padding bytes based on their value.
   *
   * @param dst       Output buffer for unpadded result.
   * @param src       Padded input buffer.
   * @param blk_sz    Block size used during padding.
   */
  void unpad(byte_buffer& dst, byte_span src, size_type blk_sz) const override;

private:
  //
  // Validators
  //

  /**
   * @brief Validates that the block size is non-zero and acceptable.
   *
   * @throws invalid_value if block size is zero.
   */
  void __validate_blk_sz(size_type blk_sz) const;

  /**
   * @brief Validates that input length is acceptable for padding.
   *
   * @throws invalid_value if input is too long for block size.
   */
  void __validate_padded_len(size_type srclen, size_type blk_sz) const;

  /**
   * @brief Validates that padding bytes are correct according to PKCS#7.
   *
   * @throws invalid_value if padding is invalid.
   */
  void __validate_padding(uint8_t padlen, byte_span src) const;

  //
  // Buffer preparation
  //

  /// Resizes or clears the destination buffer to required size.
  void __prepare_buffer(byte_buffer& dst, size_type size) const;

  /// Writes padded result into destination.
  void __padded_prepare(byte_buffer& dst, byte_span src, size_type padlen) const;

  /// Writes unpadded result into destination.
  void __unpadded_prepare(byte_buffer& dst, byte_span src, size_type padlen) const;

  //
  // Buffer storing
  //

  /// Stores padded data in destination buffer.
  void __pad_store(byte_buffer& dst, byte_span src, size_type padlen) const;

  /// Stores unpadded data in destination buffer.
  void __unpad_store(byte_buffer& dst, byte_span src, size_type padlen) const;
};

} // namespace padpp
