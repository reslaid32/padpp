/**
 * @file Range.h
 * @ingroup cppapi
 * @brief Template class representing a numeric range with minimum and maximum values.
 *
 * This utility template models a range `[min, max]` and provides
 * methods to check whether a value falls within the range.
 */

#pragma once

#include <ostream>
#include <type_traits>
#include <utility>

namespace padpp
{

/**
 * @ingroup cppapi
 * @brief Represents a range of values from `min` to `max` inclusive.
 *
 * Template parameter `T` specifies the type of the range bounds.
 *
 * Provides a static factory method `create()` for deducing common type
 * from heterogeneous arguments.
 *
 * Example usage:
 * ```cpp
 * auto r = padpp::Range<int>::create(1, 5);
 * bool inside = r.within(3); // true
 * ```
 *
 * @tparam T Type of the range bounds.
 */
template <typename T> struct Range
{
  /**
   * @brief Factory method to create a Range with deduced common type.
   *
   * Accepts heterogeneous types `U` and `V` and returns a Range
   * with the common type of both arguments.
   *
   * @tparam U Type of the minimum bound argument.
   * @tparam V Type of the maximum bound argument.
   * @param min Minimum bound value.
   * @param max Maximum bound value.
   * @return Range with deduced common type.
   */
  template <typename U, typename V>
  static Range
  create(U&& min, V&& max)
  {
    using DeducedT = std::common_type_t<U, V>;
    return Range<DeducedT>(std::forward<U>(min), std::forward<V>(max));
  }

  /// Minimum value of the range.
  T min;
  /// Maximum value of the range.
  T max;

  /**
   * @brief Constructs a range from given minimum and maximum.
   *
   * Accepts heterogeneous types convertible to `T`.
   *
   * @tparam U Type of min argument.
   * @tparam V Type of max argument.
   * @param min Minimum bound.
   * @param max Maximum bound.
   */
  template <typename U, typename V>
  Range(U&& min, V&& max) : min(std::forward<U>(min)), max(std::forward<V>(max))
  {
  }

  /**
   * @brief Checks if a value lies within the range, inclusive.
   *
   * @tparam U Type of the value to check.
   * @param v Value to test.
   * @return true if `v` in `[min, max]`, false otherwise.
   */
  template <typename U>
  bool
  within(const U& v) const
  {
    return v >= min && v <= max;
  }
};

/**
 * @ingroup cppapi
 * @brief Stream output operator for Range.
 *
 * Prints the range in the format `[min, max]`.
 *
 * @tparam T Type of the Range bounds.
 * @param os Output stream.
 * @param range Range to print.
 * @return Reference to the output stream.
 */
template <typename T>
std::ostream&
operator<<(std::ostream& os, const Range<T>& range)
{
  return os << "[" << range.min << ", " << range.max << "]";
}

} // namespace padpp
