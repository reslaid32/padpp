/**
 * @file Exceptions.h
 * @ingroup cppapi
 * @brief Exception types and validation utilities for padpp.
 *
 * Defines the `invalid_value` exception for signaling invalid input values,
 * and the `ExpectationHint` enum for describing expected conditions.
 */

#pragma once

#include <cstddef>
#include <exception>
#include <sstream>
#include <string>

#include "Range.h"

namespace padpp
{

/**
 * @ingroup cppapi
 * @brief Hint indicating the expected condition for a value.
 */
enum class ExpectationHint
{
  /// Expect equal
  Eq = 0,

  /// Expect not equal
  Ne = 1
};

/**
 * @ingroup cppapi
 * @brief Converts an ExpectationHint to its string representation.
 *
 * @param ehint Expectation hint enum value.
 * @return Corresponding string ("eq", "ne", or "unknown").
 */
inline const char*
to_string(ExpectationHint ehint)
{
  switch (ehint)
  {
  case ExpectationHint::Eq:
    return "eq";
  case ExpectationHint::Ne:
    return "ne";
  default:
    return "unknown";
  }
}

/**
 * @ingroup cppapi
 * @brief Exception thrown for invalid input values.
 *
 * Provides detailed error messages including the invalid value, expected
 * value or range, and expectation hint.
 *
 * @tparam T Type used for range checking (default is std::size_t).
 */
template <typename T = std::size_t> struct invalid_value : public std::exception
{
private:
  /// Error message string
  std::string str;

public:
  /**
   * @brief Constructs exception with a custom message.
   * @param msg Message describing the error.
   */
  invalid_value(std::string_view msg) : str(msg) {}

  /**
   * @brief Constructs exception with the invalid value.
   * Message format: "invalid_value{value}".
   *
   * @tparam U Type of the invalid value.
   * @param v The invalid value.
   */
  template <typename U> invalid_value(U&& v)
  {
    std::ostringstream oss;
    oss << "invalid_value"
        << "{" << v << "}";
    str = oss.str();
  }

  /**
   * @brief Constructs exception with the invalid value, expected value,
   *        and expectation hint.
   * Message format: "invalid_value{value} must be eq expected" or
   * "invalid_value{value} must be ne expected".
   *
   * @tparam U Type of the invalid value.
   * @tparam V Type of the expected value.
   * @param v Actual invalid value.
   * @param expected Expected value.
   * @param ehint Expectation hint (default is Eq).
   */
  template <typename U, typename V>
  invalid_value(U&& v, V&& expected, ExpectationHint ehint = ExpectationHint::Eq)
  {
    std::ostringstream oss;
    oss << "invalid_value" << "{" << v << "}" << " must be " << to_string(ehint)
        << " " << expected;
    str = oss.str();
  }

  /**
   * @brief Constructs exception with the invalid value and valid range.
   * Message format: "invalid_value{value} must be in [min, max]".
   *
   * @tparam U Type of the invalid value.
   * @param v Invalid value.
   * @param range Valid range of values.
   */
  template <typename U> invalid_value(U&& v, Range<T> range)
  {
    std::ostringstream oss;
    oss << "invalid_value" << "{" << v << "}" << " must be in " << range;
    str = oss.str();
  }

  /**
   * @brief Returns the exception message.
   * @return C-string containing the message.
   */
  const char*
  what() const noexcept
  {
    return str.c_str();
  }
};

} // namespace padpp