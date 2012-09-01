#pragma once
#define LUACELL_LIB_NAME "luacell"

#  define LUACELL_LIB_PREFIX "lib"

#if defined(_M_IX86)
#  define LUACELL_LIB_PLATFORM "-x86"
#elif defined(_WIN32)
#  define LUACELL_LIB_PLATFORM "-x64"
#endif

#ifdef _DLL
#  if defined(_DEBUG)
// MDd
#    define LUACELL_LIB_RT_OPT "-gd"
#  else
// MD
#    define LUACELL_LIB_RT_OPT
#  endif
#else
#  if defined(_DEBUG)
// MTd
#    define LUACELL_LIB_RT_OPT "-sgd"
#  else
// MT
#    define LUACELL_LIB_RT_OPT "-s"
#  endif
#endif

#  pragma comment(lib, LUACELL_LIB_PREFIX LUACELL_LIB_NAME  LUACELL_LIB_RT_OPT LUACELL_LIB_PLATFORM ".lib")
// static MDd x86 : libLUACELL-gd-x86.lib
// static MD x86 :  libLUACELL-x86.lib
// static MTd x86 : libLUACELL-sgd-x86.lib
// static MT x86 :  libLUACELL-s-x86.lib

