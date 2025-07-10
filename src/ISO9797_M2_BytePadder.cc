#define _PADPP_BUILDING

#include "../include/padpp-c/Support.h"

#include "../include/padpp-c/ISO9797_M2_BytePadder.h"
#include "../include/padpp/ISO9797_M2_BytePadder.h"
#include "../include/padpp/PadderFactory.h"

namespace padpp
{

namespace
{
const bool registered = PadderFactory::instance().register_creator(
    "iso9797_m2", [] { return std::make_unique<ISO9797_M2_BytePadder>(); });
}

void
ISO9797_M2_BytePadder::pad(byte_buffer& dst, byte_span src, size_type blk_sz) const
{
  if (blk_sz == 0 || blk_sz > 255)
    throw invalid_value(blk_sz, Range<size_type>{ 1, 255 });

  size_type rem = src.size() % blk_sz;
  size_type padlen = rem ? blk_sz - rem : blk_sz;

  dst.clear();
  dst.reserve(src.size() + padlen);

  dst.insert(dst.end(), src.begin(), src.end());

  dst.push_back(0x80);

  if (padlen > 1)
    dst.insert(dst.end(), padlen - 1, 0x00);
}

void
ISO9797_M2_BytePadder::unpad(byte_buffer& dst, byte_span src, size_type blk_sz) const
{
  if (blk_sz == 0 || blk_sz > 255)
    throw invalid_value(blk_sz, Range<size_type>{ 1, 255 });

  if (src.size() % blk_sz != 0)
    throw invalid_value(src.size() & blk_sz, 0);

  ssize_t i = static_cast<ssize_t>(src.size()) - 1;

  while (i >= 0 && src[i] == 0x00)
    --i;

  if (i < 0 || src[i] != 0x80)
    throw std::runtime_error("Invalid ISO9797 M2 padding: missing 0x80 marker");

  dst.assign(src.begin(), src.begin() + i);
}

}

using namespace padpp;

extern "C"
{
  _PADPP_PUBLIC padpp_iso9797_m2_padder_t
  padpp_iso9797_m2_create()
  {
    try
    {
      return new ISO9797_M2_BytePadder();
    }
    catch (...)
    {
      return nullptr;
    }
  }

  _PADPP_PUBLIC void
  padpp_iso9797_m2_destroy(padpp_iso9797_m2_padder_t ctx)
  {
    delete static_cast<ISO9797_M2_BytePadder*>(ctx);
  }

  _PADPP_PUBLIC int
  padpp_iso9797_m2_pad(padpp_iso9797_m2_padder_t ctx, uint8_t* dst, size_t* dst_len,
                       const uint8_t* src, size_t src_len, size_t block_size)
  {
    if (!ctx || !dst || !dst_len || !src)
      return -1;

    try
    {
      auto* padder = static_cast<ISO9797_M2_BytePadder*>(ctx);
      std::vector<uint8_t> input(src, src + src_len);
      std::vector<uint8_t> output;

      padder->pad(output, input, block_size);

      if (*dst_len < output.size())
        return -2;

      std::copy(output.begin(), output.end(), dst);
      *dst_len = output.size();
      return 0;
    }
    catch (...)
    {
      return -3;
    }
  }

  _PADPP_PUBLIC int
  padpp_iso9797_m2_unpad(padpp_iso9797_m2_padder_t ctx, uint8_t* dst,
                         size_t* dst_len, const uint8_t* src, size_t src_len,
                         size_t block_size)
  {
    if (!ctx || !dst || !dst_len || !src)
      return -1;

    try
    {
      auto* padder = static_cast<ISO9797_M2_BytePadder*>(ctx);
      std::vector<uint8_t> input(src, src + src_len);
      std::vector<uint8_t> output;

      padder->unpad(output, input, block_size);

      if (*dst_len < output.size())
        return -2;

      std::copy(output.begin(), output.end(), dst);
      *dst_len = output.size();
      return 0;
    }
    catch (...)
    {
      return -3;
    }
  }
} // extern "C"
