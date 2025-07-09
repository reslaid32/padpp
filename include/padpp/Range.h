#pragma once

#include <ostream>
#include <type_traits>
#include <utility>

namespace padpp
{

template <typename T> struct Range
{
  template <typename U, typename V>
  static Range
  create(U&& min, V&& max)
  {
    using DeducedT = std::common_type_t<U, V>;
    return Range<DeducedT>(std::forward<U>(min), std::forward<V>(max));
  }

  T min, max;

  template <typename U, typename V>
  Range(U&& min, V&& max) : min(std::forward<U>(min)), max(std::forward<V>(max))
  {
  }

  /* Supports L/R References */
  template <typename U>
  bool
  within(const U& v) const
  {
    return v >= min && v <= max;
  }
};

template <typename T>
std::ostream&
operator<<(std::ostream& os, const Range<T>& range)
{
  return os << "[" << range.min << ", " << range.max << "]";
}

}