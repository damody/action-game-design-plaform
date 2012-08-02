#pragma once
#include "math\Vector3.h"
#include "path\PathInterpolater.h"

struct FlyingType{
	enum e{
		DEFAULT,		//受重力
		BEZIERCURVE_PATH,	//自訂路徑-BezierCurve內插
		BSPLINECURVE_PATH,	//自訂路徑-BsplineCurve內插
		HSPLINECURVE_PATH,	//自訂路徑-HSplineCurve內插
		LINEARLINE_PATH,	//自訂路徑-LinearLine內插
		CHASE			//追蹤
	};
};

class FlyingPath: public PathInterpolater
{
public:
	FlyingPath(void);
	~FlyingPath(void);

	Vector3 GetValue(FlyingType::e type,float time);
};

