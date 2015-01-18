#pragma once
#define LUABIND_LIB_NAME "Luabind"

#if defined(LUAJIT_LIB_DYNAMIC)
#  define LUABIND_LIB_PREFIX
#elif defined(_WIN32)
#  define LUABIND_LIB_PREFIX "lib"
#endif

#if defined(_WIN64)
#  define LUABIND_LIB_PLATFORM "-x64"
#elif defined(_WIN32)
#  define LUABIND_LIB_PLATFORM "-x86"
#endif

#ifdef _DLL
#  if defined(_DEBUG)
// MDd
#    define LUABIND_LIB_RT_OPT "-gd"
#  else
// MD
#    define LUABIND_LIB_RT_OPT
#  endif
#else
#  if defined(_DEBUG)
// MTd
#    define LUABIND_LIB_RT_OPT "-sgd"
#  else
// MT
#    define LUABIND_LIB_RT_OPT "-s"
#  endif
#endif

#  pragma comment(lib, LUABIND_LIB_PREFIX LUABIND_LIB_NAME  LUABIND_LIB_RT_OPT LUABIND_LIB_PLATFORM ".lib")
// static MDd x86 : libLuabind-gd-x86.lib
// static MD x86 :  libLuabind-x86.lib
// static MTd x86 : libLuabind-sgd-x86.lib
// static MT x86 :  libLuabind-s-x86.lib

// dynamic MDd x86 : Luabind-gd-x86.lib
// dynamic MD x86 :  Luabind-x86.lib
// dynamic MTd x86 : Luabind-sgd-x86.lib
// dynamic MT x86 :  Luabind-s-x86.lib