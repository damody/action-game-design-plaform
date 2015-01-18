#pragma once
#define LUA_LIB_NAME "liblua"

#if defined(_M_IX86)
#  define LUA_LIB_PLATFORM "-x86"
#else
#  define LUA_LIB_PLATFORM "-x64"
#endif

#ifdef _DLL
#  if defined(_DEBUG)
// MDd
#    define LUA_LIB_RT_OPT "-gd"
#  else
// MD
#    define LUA_LIB_RT_OPT
#  endif
#else
#  if defined(_DEBUG)
// MTd
#    define LUA_LIB_RT_OPT "-sgd"
#  else
// MT
#    define LUA_LIB_RT_OPT "-s"
#  endif
#endif

#  pragma comment(lib, LUA_LIB_NAME  LUA_LIB_RT_OPT LUA_LIB_PLATFORM ".lib")
