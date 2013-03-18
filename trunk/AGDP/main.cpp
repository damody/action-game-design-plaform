#include "StdGame.h"
#include "main.h"
#include "DX11/InitDirect3DApp.h"
#include <auto_link_agal.hpp>
#include <auto_link_sgal.hpp>
extern "C"
{
#include <private/gc_priv.h>
};


extern "C" void __cdecl free(void * pUserData)
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
	GC_start_debugging();
	GC_set_find_leak(true);
	InitDirect3DApp* theApp = new InitDirect3DApp;
	theApp->initApp( argc, argv );
	theApp->run();
	delete theApp;
	printf("using %d marker threads\n", GC_get_parallel() + 1);
	printf("Completed %u collections\n", (unsigned)GC_get_gc_no());
	printf("Total size since gc is %lu MB\n",
		(unsigned long)GC_get_bytes_since_gc()/1024/1024);
	printf("Total size allocated is %lu MB\n",
		(unsigned long)GC_get_total_bytes()/1024/1024);
	printf("Final heap size is %lu MB\n",
		(unsigned long)GC_get_heap_size()/1024/1024);
	GC_gcollect();
}
