#define _PADPP_BUILDING

#include "../include/padpp-c/Support.h"

#include "../include/padpp-c/PadderFactory.h"
#include "../include/padpp/PadderFactory.h"
#include <cstring>

namespace padpp
{

PadderFactory&
PadderFactory::instance()
{
  static PadderFactory factory;
  return factory;
}

PadderFactory::PadderFactory() = default;

PadderFactory::~PadderFactory() = default;

bool
PadderFactory::register_creator(const std::string& name, Creator creator)
{
  std::lock_guard<std::mutex> lock(mutex_);
  auto [it, inserted] = creators_.emplace(name, std::move(creator));
  return inserted;
}

std::unique_ptr<IBytePadder>
PadderFactory::create(const std::string& name) const
{
  std::lock_guard<std::mutex> lock(mutex_);
  auto it = creators_.find(name);
  if (it != creators_.end())
    return it->second();
  return nullptr;
}

PadderRegistrar::PadderRegistrar(const std::string& name,
                                 PadderFactory::Creator creator)
{
  PadderFactory::instance().register_creator(name, std::move(creator));
}

struct PadderHandle
{
  std::unique_ptr<IBytePadder> padder;
};

}

using namespace padpp;

extern "C"
{
  _PADPP_PUBLIC padpp_handle_t
  padpp_create(const char* name)
  {
    if (!name)
      return nullptr;

    auto ptr = PadderFactory::instance().create(std::string(name));
    if (!ptr)
      return nullptr;

    PadderHandle* handle = new PadderHandle;
    handle->padder = std::move(ptr);
    return handle;
  }

  _PADPP_PUBLIC void
  padpp_destroy(padpp_handle_t padder)
  {
    if (padder)
      delete static_cast<PadderHandle*>(padder);
  }

  _PADPP_PUBLIC int
  padpp_pad(padpp_handle_t padder, uint8_t* dst, size_t* dst_len,
            const uint8_t* src, size_t src_len, size_t block_size)
  {
    if (!padder || !dst_len || !src)
      return -1;

    try
    {
      std::vector<uint8_t> src_vec(src, src + src_len);
      std::vector<uint8_t> dst_vec;

      static_cast<PadderHandle*>(padder)->padder->pad(dst_vec, src_vec, block_size);

      if (*dst_len < dst_vec.size())
        return -2;

      std::memcpy(dst, dst_vec.data(), dst_vec.size());
      *dst_len = dst_vec.size();

      return 0;
    }
    catch (...)
    {
      return -3;
    }
  }

  _PADPP_PUBLIC int
  padpp_unpad(padpp_handle_t padder, uint8_t* dst, size_t* dst_len,
              const uint8_t* src, size_t src_len, size_t block_size)
  {
    if (!padder || !dst_len || !src)
      return -1;

    try
    {
      std::vector<uint8_t> src_vec(src, src + src_len);
      std::vector<uint8_t> dst_vec;

      static_cast<PadderHandle*>(padder)->padder->unpad(dst_vec, src_vec,
                                                        block_size);

      if (*dst_len < dst_vec.size())
        return -2;

      std::memcpy(dst, dst_vec.data(), dst_vec.size());
      *dst_len = dst_vec.size();

      return 0;
    }
    catch (...)
    {
      return -3;
    }
  }

} // extern "C"
