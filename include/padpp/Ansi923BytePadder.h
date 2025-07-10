/**
 * @file Ansi923BytePadder.h
 * @ingroup cppapi
 * @brief C++ implementation of the ANSI X9.23 padding algorithm.
 *
 * This class implements the byte-level ANSI X9.23 padding and unpadding
 * logic. It is registered under the PadderFactory with name `"ansi923"`.
 *
 * The algorithm adds padding bytes followed by a single length byte at the
 * end, conforming to ANSI X9.23 standard.
 */

#pragma once

#include "IBytePadder.h"
#include "Support.h"

namespace padpp
{

/**
 * @ingroup cppapi
 * @brief C++ padder for ANSI X9.23.
 */
struct _PADPP_PUBLIC Ansi923BytePadder : public IBytePadder
{
  /// Pads the input buffer using ANSI X9.23 rules.
  void pad(byte_buffer& dst, byte_span src, size_type blk_sz) const override;

  /// Removes ANSI X9.23 padding from the buffer.
  void unpad(byte_buffer& dst, byte_span src, size_type blk_sz) const override;

private:
  //
  // Validation methods (throw padpp::invalid_value on failure)
  //

  /// Validates that block size is non-zero and acceptable.
  void __validate_blk_sz(size_type blk_sz) const;

  /// Validates that the padded length is valid for the input length and block size.
  void __validate_padded_len(size_type srclen, size_type blk_sz) const;

  /// Validates that the padding length byte is within expected range.
  void __validate_padding_len(uint8_t padlen, size_type blk_sz) const;

  /// Validates that the padding byte equals the expected value.
  void __validate_byte(uint8_t v, uint8_t expected) const;

  //
  // Buffer preparation helpers
  //

  /// Ensures `dst` is sized to `size` and zeroed if needed.
  void __prepare_buffer(byte_buffer& dst, size_type size) const;

  /// Prepares the padded buffer by copying `src` and appending pad bytes.
  void __padded_prepare(byte_buffer& dst, byte_span src, size_type padlen) const;

  /// Prepares the unpadded buffer by copying only the unpadded content.
  void __unpadded_prepare(byte_buffer& dst, byte_span src, size_type padlen) const;

  //
  // Buffer writing logic
  //

  /// Writes the padded result to `dst` normally (new buffer or separate).
  void __pad_store(byte_buffer& dst, byte_span src, size_type padlen) const;

  /// Writes the padded result when `dst` and `src` may alias.
  void __pad_store_samebuf(byte_buffer& dst, byte_span src, size_type padlen) const;

  /// Writes the result of unpadding into `dst`.
  void __unpad_store(byte_buffer& dst, byte_span src, size_type padlen) const;
};

} // namespace padpp
