#include "stdafx.h"
#include "main.h"
#include "DX11/InitDirect3DApp.h"

int main()
{
	InitDirect3DApp theApp(GetModuleHandle(NULL));
	theApp.initApp();
	return theApp.run();
}
