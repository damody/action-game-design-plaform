#pragma once
#define SGAL_LIB_NAME "sgal"

#  define SGAL_LIB_PREFIX "lib"

#if defined(_M_IX86)
#  define SGAL_LIB_PLATFORM "-x86"
#elif defined(_WIN32)
#  define SGAL_LIB_PLATFORM "-x64"
#endif

#ifdef _DLL
#  if defined(_DEBUG)
// MDd
#    define SGAL_LIB_RT_OPT "-gd"
#  else
// MD
#    define SGAL_LIB_RT_OPT
#  endif
#else
#  if defined(_DEBUG)
// MTd
#    define SGAL_LIB_RT_OPT "-sgd"
#  else
// MT
#    define SGAL_LIB_RT_OPT "-s"
#  endif
#endif

#  pragma comment(lib, SGAL_LIB_PREFIX SGAL_LIB_NAME  SGAL_LIB_RT_OPT SGAL_LIB_PLATFORM ".lib")
// static MDd x86 : libSGAL-gd-x86.lib
// static MD x86 :  libSGAL-x86.lib
// static MTd x86 : libSGAL-sgd-x86.lib
// static MT x86 :  libSGAL-s-x86.lib

