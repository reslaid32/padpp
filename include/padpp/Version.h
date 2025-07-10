/**
 * @file VersionController.h
 * @ingroup cppapi
 * @brief Represents the semantic version of the padpp library.
 *
 * Holds major, minor, and patch version components.
 */

#pragma once

#include "Support.h"

namespace padpp
{

/**
 * @ingroup cppapi
 * @brief Semantic version representation.
 *
 * Contains the major, minor, and patch version numbers of the library.
 */
struct _PADPP_PUBLIC Version
{
  /// Major version number.
  const unsigned char maj;

  /// Minor version number.
  const unsigned char min;

  /// Patch version number.
  const unsigned char pat;

  /**
   * @brief Returns the current version of the library.
   *
   * @return Reference to the current version instance.
   */
  static Version& current();
};

} // namespace padpp
