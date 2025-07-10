#ifndef PADPPC_TYPE_C_H
#define PADPPC_TYPE_C_H

/**
 * @brief Opaque handle representing a padder context.
 *
 * The actual algorithm implementation is selected dynamically using
 * `padpp_create()` with a string identifier.
 */
typedef void* padpp_handle_t;

#endif
