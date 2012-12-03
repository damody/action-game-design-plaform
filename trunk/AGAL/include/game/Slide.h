#pragma once
#include "OffsetCalculate.h"

class Slide : public OffsetCalculate
{
public:
	Slide(void);
	~Slide(void);
private:
	void Calculate( OffsetControl& OC, float deltaTime );
};