#pragma once
#define AGAL_LIB_NAME "agal"

#  define AGAL_LIB_PREFIX "lib"

#if defined(_M_IX86)
#  define AGAL_LIB_PLATFORM "-x86"
#elif defined(_WIN32)
#  define AGAL_LIB_PLATFORM "-x64"
#endif

#ifdef _DLL
#  if defined(_DEBUG)
// MDd
#    define AGAL_LIB_RT_OPT "-gd"
#  else
// MD
#    define AGAL_LIB_RT_OPT
#  endif
#else
#  if defined(_DEBUG)
// MTd
#    define AGAL_LIB_RT_OPT "-sgd"
#  else
// MT
#    define AGAL_LIB_RT_OPT "-s"
#  endif
#endif

#  pragma comment(lib, AGAL_LIB_PREFIX AGAL_LIB_NAME  AGAL_LIB_RT_OPT AGAL_LIB_PLATFORM ".lib")
// static MDd x86 : libAGAL-gd-x86.lib
// static MD x86 :  libAGAL-x86.lib
// static MTd x86 : libAGAL-sgd-x86.lib
// static MT x86 :  libAGAL-s-x86.lib

