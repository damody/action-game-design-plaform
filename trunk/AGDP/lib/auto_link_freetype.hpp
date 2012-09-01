#pragma once
#define FREETYPE2_LIB_NAME "freetype249"

#if defined(zlib_LIB_DYNAMIC)
#  define FREETYPE2_LIB_PREFIX
#elif defined(_WIN32)
#  define FREETYPE2_LIB_PREFIX "lib"
#endif

#if defined(_WIN64)
#  define FREETYPE2_LIB_PLATFORM "-x64"
#elif defined(_WIN32)
#  define FREETYPE2_LIB_PLATFORM "-x86"
#endif

#ifdef _DLL
#  if defined(_DEBUG)
// MDd
#    define FREETYPE2_LIB_RT_OPT "-gd"
#  else
// MD
#    define FREETYPE2_LIB_RT_OPT
#  endif
#else
#  if defined(_DEBUG)
// MTd
#    define FREETYPE2_LIB_RT_OPT "-sgd"
#  else
// MT
#    define FREETYPE2_LIB_RT_OPT "-s"
#  endif
#endif

#  pragma comment(lib, FREETYPE2_LIB_PREFIX FREETYPE2_LIB_NAME FREETYPE2_LIB_RT_OPT FREETYPE2_LIB_PLATFORM ".lib")
// static MDd x86 : libfreetype249-gd-x86.lib
// static MD x86 :  libfreetype249-x86.lib
// static MTd x86 : libfreetype249-sgd-x86.lib
// static MT x86 :  libfreetype249-s-x86.lib

