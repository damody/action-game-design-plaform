#ifndef _SHAKE_H_
#define _SHAKE_H_
#pragma once

#include "OffsetCalculate.h"

class Shake: public OffsetCalculate
{
public:
	Shake(void);
	~Shake(void);
private:
	void Calculate( OffsetControl& OC, float deltaTime );
};

#endif // _SHAKE_H_