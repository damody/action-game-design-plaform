#include "StdGame.h"
#include "main.h"
#include "DX11/InitDirect3DApp.h"
#include <auto_link_agal.hpp>
#include <auto_link_sgal.hpp>

extern "C" void __cdecl free(
	void * pUserData
	)
{
	if (GC_base(pUserData) != 0)
		GC_FREE(pUserData);
	else
	{
		_free_dbg(pUserData, _NORMAL_BLOCK);
	}
}

extern "C" void * __cdecl malloc(size_t _Size)
{
	return GC_MALLOC(_Size);
}

extern "C" void * __cdecl realloc(void * _Memory, size_t _NewSize)
{
	return GC_REALLOC(_Memory, _NewSize);
}

extern "C" void * __cdecl calloc(size_t _Count, size_t _Size)
{
	return GC_MALLOC(_Count * _Size);
}

int main( int argc, char* argv[] )
{
	putenv("GC_FIND_LEAK=1");
	InitDirect3DApp theApp;
	theApp.initApp( argc, argv );
	theApp.run();
	printf("Total number of bytes allocated is %lu\n",
		(unsigned long)GC_get_total_bytes());
	printf("Final heap size is %lu bytes\n",
		(unsigned long)GC_get_heap_size());
}
