#pragma once
#include "math\Vector3.h"
#include "path\LinearLine.h"
#include "path\BezierCurve.h"
#include "path\BsplineCurve.h"
#include "path\HSplineCurve.h"

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

class FlyingPath
{
private:
	LinearLine	m_Linear;
	BezierCurve	m_Bezier;
	BsplineCurve	m_Bspline;
	HsplineCurve	m_Hspline;

public:
	FlyingPath(void);
	~FlyingPath(void);

	void	AddPoint();
	Vector3 GetValue();
};

