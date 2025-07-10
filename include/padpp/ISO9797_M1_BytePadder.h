/*
 * On PadderFactory with name "iso9797_m1"
 *
 * NOT UNIT TEST READY. ONE WAY PADDING.
 */

// Commited by reslaid32
// ISO9797 M1 Padder

#pragma once

#include "Exceptions.h"
#include "IBytePadder.h"
#include "Range.h"
#include "Support.h"

namespace padpp
{

struct _PADPP_PUBLIC ISO9797_M1_BytePadder : public IBytePadder
{
  //
  // Public functions
  //
  void pad(byte_buffer& dst, byte_span src, size_type blk_sz) const override;
  void unpad(byte_buffer& dst, byte_span src, size_type blk_sz) const override;
};

}
