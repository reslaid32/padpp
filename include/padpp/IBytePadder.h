#pragma once

#include <cstddef>
#include <cstdint>
#include <span>
#include <vector>

namespace padpp
{

struct IBytePadder
{
  using size_type = std::size_t;

  using byte_span = std::span<std::uint8_t>;
  using byte_buffer = std::vector<std::uint8_t>;

  virtual void pad(byte_buffer& dst, byte_span src, size_type blk_sz) const = 0;
  virtual void unpad(byte_buffer& dst, byte_span src, size_type blk_sz) const = 0;

  virtual ~IBytePadder() = default;
};

}