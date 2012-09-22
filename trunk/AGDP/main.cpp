#include "StdGame.h"
#include "main.h"
#include "DX11/InitDirect3DApp.h"
#include <auto_link_agal.hpp>
#include <auto_link_sgal.hpp>

int main( int argc, char* argv[] )
{
	InitDirect3DApp theApp;
	theApp.initApp( argc, argv );
	return theApp.run();
}
