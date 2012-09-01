#include "StdGame.h"
#include "main.h"
#include "DX11/InitDirect3DApp.h"
#include <auto_link_agal.hpp>
#include <auto_link_sgal.hpp>

int main()
{
	InitDirect3DApp theApp;
	theApp.initApp();
	return theApp.run();
}
