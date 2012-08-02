#pragma once
#include "math\Vector3.h"
#include "path\PathInterpolater.h"

struct FlyingType{
	enum e{
		DEFAULT,		//�����O
		BEZIERCURVE_PATH,	//�ۭq���|-BezierCurve����
		BSPLINECURVE_PATH,	//�ۭq���|-BsplineCurve����
		HSPLINECURVE_PATH,	//�ۭq���|-HSplineCurve����
		LINEARLINE_PATH,	//�ۭq���|-LinearLine����
		CHASE			//�l��
	};
};

class FlyingPath: public PathInterpolater
{
public:
	FlyingPath(void);
	~FlyingPath(void);

	Vector3 GetValue(FlyingType::e type,float time);
};

