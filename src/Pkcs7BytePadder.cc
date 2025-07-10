#define _PADPP_BUILDING

#include "../include/padpp-c/Support.h"

#include "../include/padpp-c/Pkcs7BytePadder.h"
#include "../include/padpp/PadderFactory.h"
#include "../include/padpp/Pkcs7BytePadder.h"

#include "../include/padpp/Exceptions.h"
#include "../include/padpp/Range.h"

namespace padpp
{

namespace
{
static PadderRegistrar registrar("pkcs7", []
                                 { return std::make_unique<Pkcs7BytePadder>(); });
}

void
Pkcs7BytePadder::__validate_blk_sz(size_type blk_sz) const
{
  Range<size_type> range = { 1, 255 };
  if (!range.within(blk_sz))
    throw invalid_value(blk_sz, range);
}

void
Pkcs7BytePadder::__validate_padded_len(size_type len, size_type blk_sz) const
{
  if (len % blk_sz != 0)
    throw invalid_value(len & blk_sz, 0);
}

void
Pkcs7BytePadder::__validate_padding(uint8_t padlen, byte_span src) const
{
  if (padlen == 0 || padlen > src.size())
    throw invalid_value(padlen, { 1, src.size() });

  for (size_type i = src.size() - padlen; i < src.size(); ++i)
    if (src[i] != padlen)
      throw invalid_value(src[i], padlen);
}

void
Pkcs7BytePadder::__prepare_buffer(byte_buffer& dst, size_type size) const
{
  dst.clear();
  dst.reserve(size);
}

void
Pkcs7BytePadder::__padded_prepare(byte_buffer& dst, byte_span src,
                                  size_type padlen) const
{
  __prepare_buffer(dst, src.size() + padlen);
}

void
Pkcs7BytePadder::__unpadded_prepare(byte_buffer& dst, byte_span src,
                                    size_type padlen) const
{
  __prepare_buffer(dst, src.size() - padlen);
}

void
Pkcs7BytePadder::__pad_store(byte_buffer& dst, byte_span src, size_type padlen) const
{
  dst.insert(dst.end(), src.begin(), src.end());
  dst.insert(dst.end(), padlen, static_cast<uint8_t>(padlen));
}

void
Pkcs7BytePadder::__unpad_store(byte_buffer& dst, byte_span src, size_type padlen) const
{
  dst.assign(src.begin(), src.end() - padlen);
}

void
Pkcs7BytePadder::pad(byte_buffer& dst, byte_span src, size_type blk_sz) const
{
  __validate_blk_sz(blk_sz);

  size_type padlen = blk_sz - (src.size() % blk_sz);
  if (padlen == 0)
    padlen = blk_sz;

  __padded_prepare(dst, src, padlen);
  __pad_store(dst, src, padlen);
}

void
Pkcs7BytePadder::unpad(byte_buffer& dst, byte_span src, size_type blk_sz) const
{
  __validate_padded_len(src.size(), blk_sz);

  uint8_t padlen = src.back();
  __validate_padding(padlen, src);

  __unpadded_prepare(dst, src, padlen);
  __unpad_store(dst, src, padlen);
}

}

using namespace padpp;

extern "C"
{
  _PADPP_PUBLIC padpp_handle_t
  padpp_create_pkcs7()
  {
    try
    {
      return new Pkcs7BytePadder();
    }
    catch (...)
    {
      return nullptr;
    }
  }

  _PADPP_PUBLIC void
  padpp_destroy_pkcs7(padpp_handle_t ctx)
  {
    delete static_cast<Pkcs7BytePadder*>(ctx);
  }

  _PADPP_PUBLIC int
  padpp_pad_pkcs7(padpp_handle_t ctx, uint8_t* dst, size_t* dst_len,
                  const uint8_t* src, size_t src_len, size_t block_size)
  {
    if (!ctx || !dst || !dst_len || !src)
      return -1;

    try
    {
      auto* padder = static_cast<Pkcs7BytePadder*>(ctx);
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
  padpp_unpad_pkcs7(padpp_handle_t ctx, uint8_t* dst, size_t* dst_len,
                    const uint8_t* src, size_t src_len, size_t block_size)
  {
    if (!ctx || !dst || !dst_len || !src)
      return -1;

    try
    {
      auto* padder = static_cast<Pkcs7BytePadder*>(ctx);
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
