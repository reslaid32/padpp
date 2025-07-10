#define _PADPP_BUILDING

#include "../include/padpp-c/Support.h"

#include "../include/padpp-c/Ansi923BytePadder.h"
#include "../include/padpp/Ansi923BytePadder.h"
#include "../include/padpp/PadderFactory.h"

#include "../include/padpp/Exceptions.h"
#include "../include/padpp/Range.h"

namespace padpp
{

namespace
{
static PadderRegistrar
    registrar("ansi923", [] { return std::make_unique<Ansi923BytePadder>(); });
}

void
Ansi923BytePadder::__validate_blk_sz(size_type blk_sz) const
{
  Range<size_type> range = { 1, 255 };
  if (!range.within(blk_sz))
    throw invalid_value(blk_sz, range);
}

void
Ansi923BytePadder::__validate_padded_len(size_type srclen, size_type blk_sz) const
{
  if (srclen % blk_sz != 0)
    throw invalid_value(srclen % blk_sz, 0);
}

void
Ansi923BytePadder::__validate_padding_len(uint8_t padlen, size_type blk_sz) const
{
  if (padlen == 0)
    throw invalid_value(padlen, 0, ExpectationHint::Ne);
  if (padlen > blk_sz)
    throw invalid_value(padlen, Range<size_type>{ 1, blk_sz });
}

void
Ansi923BytePadder::__validate_byte(uint8_t v, uint8_t expected) const
{
  if (v != expected)
    throw invalid_value(v, expected);
}

void
Ansi923BytePadder::__prepare_buffer(byte_buffer& dst, size_type size) const
{
  dst.clear();
  dst.reserve(size);
}

void
Ansi923BytePadder::__padded_prepare(byte_buffer& dst, byte_span src,
                                    size_type padlen) const
{
  __prepare_buffer(dst, src.size() + padlen);
}

void
Ansi923BytePadder::__unpadded_prepare(byte_buffer& dst, byte_span src,
                                      size_type padlen) const
{
  __prepare_buffer(dst, src.size() - padlen);
}

void
Ansi923BytePadder::__pad_store(byte_buffer& dst, byte_span src, size_type padlen) const
{
  dst.insert(dst.end(), src.begin(), src.end());
  dst.insert(dst.end(), padlen - 1, 0x00);
  dst.push_back(static_cast<uint8_t>(padlen));
}

void
Ansi923BytePadder::__pad_store_samebuf(byte_buffer& dst, byte_span src,
                                       size_type padlen) const
{
  dst.resize(src.size() + padlen - 1, 0x00);
  dst.push_back(static_cast<uint8_t>(padlen));
}

void
Ansi923BytePadder::__unpad_store(byte_buffer& dst, byte_span src,
                                 size_type padlen) const
{
  dst.assign(src.begin(), src.end() - padlen);
}

void
Ansi923BytePadder::pad(byte_buffer& dst, byte_span src, size_type blk_sz) const
{
  __validate_blk_sz(blk_sz);

  size_type padlen = blk_sz - (src.size() % blk_sz);
  if (padlen == 0)
    padlen = blk_sz;

  if (dst.data() == src.data() && dst.size() == src.size())
    return __pad_store_samebuf(dst, src, padlen);

  __padded_prepare(dst, src, padlen);
  __pad_store(dst, src, padlen);
}

void
Ansi923BytePadder::unpad(byte_buffer& dst, byte_span src, size_type blk_sz) const
{
  __validate_padded_len(src.size(), blk_sz);

  uint8_t padlen = src.back();
  __validate_padding_len(padlen, blk_sz);

  for (size_type i = src.size() - padlen; i < src.size() - 1; ++i)
    __validate_byte(src[i], 0x00);

  __unpadded_prepare(dst, src, padlen);
  __unpad_store(dst, src, padlen);
}

}

using namespace padpp;

extern "C"
{
  _PADPP_PUBLIC padpp_handle_t
  padpp_create_ansi923()
  {
    try
    {
      return new Ansi923BytePadder();
    }
    catch (...)
    {
      return nullptr;
    }
  }

  _PADPP_PUBLIC void
  padpp_destroy_ansi923(padpp_handle_t ctx)
  {
    delete static_cast<Ansi923BytePadder*>(ctx);
  }

  _PADPP_PUBLIC int
  padpp_pad_ansi923(padpp_handle_t ctx, uint8_t* dst, size_t* dst_len,
                    const uint8_t* src, size_t src_len, size_t block_size)
  {
    if (!ctx || !dst || !dst_len || !src)
      return -1;

    try
    {
      auto* padder = static_cast<Ansi923BytePadder*>(ctx);
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
  padpp_unpad_ansi923(padpp_handle_t ctx, uint8_t* dst, size_t* dst_len,
                      const uint8_t* src, size_t src_len, size_t block_size)
  {
    if (!ctx || !dst || !dst_len || !src)
      return -1;

    try
    {
      auto* padder = static_cast<Ansi923BytePadder*>(ctx);
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
