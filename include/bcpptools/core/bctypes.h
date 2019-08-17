/**
*  \file    types.h
*  \brief   Generic type-related stuff for c sources
*/
#ifndef __bctools__types__
#define __bctools__types__


#ifdef __cplusplus

#include <cstddef>
#include <cstdint>
#include <string>

#else

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#endif


// === Compiler Check =========================================================
#if !defined(_BCCOMPILER_MSVC) && !defined(_BCCOMPILER_GCC) && !defined(_BCCOMPILER_MINGW)
#error bctools error: Compiler not supported
#endif

// === Basic Types ============================================================
typedef     uint32_t            bcpixel_t;

// === Strings and Filenames ==================================================
#ifdef _BCPLATFORM_WINDOWS

#   include <wchar.h>

    typedef const wchar_t*          bcfilename_t;
#   define BCFILENAME(x)            (L##x)
#   define BC_PATH_SEPARATOR_CHAR   (L'\\')
#   define BC_PATH_SEPARATOR_STRING (L"\\")

#else

    typedef char*                   bcparam_t;
    typedef const char*             bcfilename_t;
#   define BCFILENAME(x)            (x)
#   define BC_PATH_SEPARATOR_CHAR   ('/')
#   define BC_PATH_SEPARATOR_STRING ("/")

#endif

#ifdef __cplusplus

#ifdef _BCPLATFORM_WINDOWS
    typedef std::wstring            bcnativestr_t;
#else
    typedef std::string             bcnativestr_t;
#endif

#endif

#ifdef __cplusplus
static const size_t BCSIZE_MAX = ~((size_t)0);
#else
#define             BCSIZE_MAX  (~((size_t)0))
#endif

#endif //__bctools__types__
