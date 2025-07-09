#pragma once

#include <cstddef>
#include <exception>
#include <sstream>
#include <string>

#include "Range.h"

namespace padpp
{

enum class ExpectationHint
{
  Eq = 0,
  Ne = 1
};

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

template <typename T = std::size_t> struct invalid_value : public std::exception
{
private:
  std::string str;

public:
  invalid_value(std::string_view msg) : str(msg) {}

  template <typename U> invalid_value(U&& v)
  {
    std::ostringstream oss;
    oss << "invalid_value"
        << "{" << v << "}";
    str = oss.str();
  }

  template <typename U, typename V>
  invalid_value(U&& v, V&& expected, ExpectationHint ehint = ExpectationHint::Eq)
  {
    std::ostringstream oss;
    oss << "invalid_value" << "{" << v << "}" << "must be " << to_string(ehint)
        << " " << expected;
    str = oss.str();
  }

  template <typename U> invalid_value(U&& v, Range<T> range)
  {
    std::ostringstream oss;
    oss << "invalid_value" << "{" << v << "}" << " must be in " << range;
    str = oss.str();
  }

  const char*
  what() const noexcept
  {
    return str.c_str();
  }
};

}