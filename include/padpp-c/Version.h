/**
 * @file VersionController.h
 * @ingroup capi
 * @brief Version information API for the padpp C interface.
 *
 * This header provides access to the current version of the padpp library,
 * exposed as a structure with major, minor, and patch components.
 */

#ifndef PADPPC_VERSION_CONTROLLER_C_H
#define PADPPC_VERSION_CONTROLLER_C_H

#include "./Support.h"

_PADPP_EXTERN_C_BEGIN

/**
 * @defgroup capi C API
 * @brief Public C interface for the padpp library.
 * @{
 */

/**
 * @brief Represents the semantic version of the padpp library.
 *
 * Structure fields follow the semantic versioning format: major.minor.patch
 *
 * All fields are constant and reflect the version at compile time.
 */
struct padpp_Version
{
  /** @brief Major version component (X.0.0) */
  const unsigned char maj;

  /** @brief Minor version component (0.X.0) */
  const unsigned char min;

  /** @brief Patch version component (0.0.X) */
  const unsigned char pat;
};

/**
 * @brief Alias for `struct padpp_Version`
 */
typedef struct padpp_Version padpp_version_t;

/**
 * @ingroup capi
 * @brief Returns the current version of the padpp library.
 *
 * @return A `padpp_version_t` structure containing the version information.
 */
_PADPP_PUBLIC padpp_version_t padpp_Version_current(void);

/** @} */

_PADPP_EXTERN_C_END

#endif // PADPPC_VERSION_CONTROLLER_C_H
