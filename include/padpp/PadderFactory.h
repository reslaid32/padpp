/**
 * @file PadderFactory.h
 * @ingroup cppapi
 * @brief C++ factory for creating IBytePadder instances by name.
 *
 * This header defines the `PadderFactory` singleton used to register and
 * instantiate padder implementations by string identifiers (e.g. `"pkcs7"`, `"iso9797_m2"`).
 *
 * The factory is thread-safe and supports dynamic extension.
 *
 * To register a padder, use `PadderRegistrar`:
 * ```cpp
 * static padpp::PadderRegistrar reg("pkcs7", [] {
 *   return std::make_unique<padpp::Pkcs7BytePadder>();
 * });
 * ```
 */

#pragma once

#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

#include "IBytePadder.h"
#include "Support.h"

namespace padpp
{

/**
 * @ingroup cppapi
 * @brief Singleton factory for named padder creation.
 *
 * This factory allows padder types to be registered and instantiated by string
 * name. Internally thread-safe.
 */
struct _PADPP_PUBLIC PadderFactory
{
  /// Type alias for a padder creation function.
  using Creator = std::function<std::unique_ptr<IBytePadder>()>;

  /**
   * @brief Returns the singleton instance of the factory.
   */
  static PadderFactory& instance();

  /**
   * @brief Registers a new padder creator under a given name.
   *
   * Typically used via `PadderRegistrar` at static initialization time.
   *
   * @param name     Unique name (e.g., "pkcs7").
   * @param creator  Function that returns a new padder instance.
   * @return true if inserted, false if already exists.
   */
  bool register_creator(const std::string& name, Creator creator);

  /**
   * @brief Creates a padder by name.
   *
   * @param name  Name of the registered padder.
   * @return Unique pointer to a padder instance, or nullptr if not found.
   */
  std::unique_ptr<IBytePadder> create(const std::string& name) const;

private:
  /// Private constructor.
  PadderFactory();
  /// Destructor.
  ~PadderFactory();

  /// Deleted copy constructor.
  PadderFactory(const PadderFactory&) = delete;
  /// Deleted assignment.
  PadderFactory& operator=(const PadderFactory&) = delete;

  mutable std::mutex mutex_;
  std::unordered_map<std::string, Creator> creators_;
};

/**
 * @ingroup cppapi
 * @brief Helper to register padders with PadderFactory at static init.
 *
 * Use this type in a static context to auto-register a padder:
 * ```cpp
 * static padpp::PadderRegistrar reg("ansi923", [] {
 *   return std::make_unique<padpp::Ansi923BytePadder>();
 * });
 * ```
 */
struct _PADPP_EXPORT PadderRegistrar
{
  /**
   * @brief Registers a padder with the factory at construction.
   *
   * @param name     Name to register under.
   * @param creator  Function to create a new padder instance.
   */
  PadderRegistrar(const std::string& name, PadderFactory::Creator creator);
};

} // namespace padpp
