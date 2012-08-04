#include "SystemClass.h"

int main()
{
	SystemClass* _system = new SystemClass();
	bool result;
	result = _system->Initialize();
	if(result)
	{
		_system->Run();
	}
	_system->Shutdown();

	//system("pause");
	return 0;
} 