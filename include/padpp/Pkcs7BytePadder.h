/*
 * On PadderFactory with name "pkcs7"
 */

// Commited by reslaid32
// PKCS7 Padder

#pragma once

#include "Exceptions.h"
#include "IBytePadder.h"
#include "Range.h"

namespace padpp
{

struct Pkcs7BytePadder : public IBytePadder
{
  //
  // Public functions
  //
  void pad(byte_buffer& dst, byte_span src, size_type blk_sz) const override;
  void unpad(byte_buffer& dst, byte_span src, size_type blk_sz) const override;

private:
  //
  // Private functions
  //

  //
  // Validators
  //  on failed -> throws 'invalid_value'
  //
  void __validate_blk_sz(size_type blk_sz) const;
  void __validate_padded_len(size_type srclen, size_type blk_sz) const;
  void __validate_padding(uint8_t padlen, byte_span src) const;

  //
  // Buffer preparation
  //
  void __prepare_buffer(byte_buffer& dst, size_type size) const;
  void __padded_prepare(byte_buffer& dst, byte_span src, size_type padlen) const;
  void __unpadded_prepare(byte_buffer& dst, byte_span src, size_type padlen) const;

  //
  // Buffer storing
  //
  void __pad_store(byte_buffer& dst, byte_span src, size_type padlen) const;
  void __unpad_store(byte_buffer& dst, byte_span src, size_type padlen) const;
};

}