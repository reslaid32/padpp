#ifndef PADPPC_SUPPORT_C_H
#define PADPPC_SUPPORT_C_H

#ifndef _PADPP_VISIBILITY_DEFAULT
#ifdef __GNUC__
#define _PADPP_VISIBILITY_DEFAULT __attribute__((visibility("default")))
#else
#define _PADPP_VISIBILITY_DEFAULT
#endif
#endif

/*
 *    Windows imports/exports from/to dynlib only marked symbols.
 * Unix/Linux imports/exports from/to dynlib all non-static symbols with visibility == default.
 */
#ifdef _WIN32
#define _PADPP_EXPORT __declspec(dllexport)
#define _PADPP_IMPORT __declspec(dllimport)
#else /* Unix/Linux */
#define _PADPP_EXPORT
#define _PADPP_IMPORT _PADPP_VISIBILITY_DEFAULT
#endif

/*
 * We exports symbols to dylib when building the library.
 * But when using library we imports them.
 */

#ifdef _PADPP_BUILDING
#define _PADPP_PUBLIC _PADPP_EXPORT
#else
#define _PADPP_PUBLIC _PADPP_IMPORT
#endif

#ifdef __cplusplus
#define _PADPP_CXX_only(Code) Code
#define _PADPP_C_only(Code)
#else
#define _PADPP_CXX_only(Code)
#define _PADPP_C_only(Code) code
#endif

// clang-format off
#define _PADPP_EXTERN_C       _PADPP_CXX_only(extern "C")
#define _PADPP_EXTERN_C_BEGIN _PADPP_EXTERN_C _PADPP_CXX_only({)
#define _PADPP_EXTERN_C_END                   _PADPP_CXX_only(})
// clang-format on

#endif
