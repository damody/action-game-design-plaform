#include "game/SmallFunction.h"


std::wstring RevisePath(std::wstring path) //�ץ����|"\\"���D
{
	int idx = 0;
	int temp = 0;

	while(true)
	{
		int idx = path.find(L"\\", temp);

		if(idx == -1)
		{
			break;
		}

		path.insert(idx, L"\\");
		temp = idx + 2;
	}

	return path;
}
