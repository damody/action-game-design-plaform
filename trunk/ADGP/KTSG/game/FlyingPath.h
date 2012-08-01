#pragma once
#include "math\Vector3.h"
#include "path\LinearLine.h"
#include "path\BezierCurve.h"
#include "path\BsplineCurve.h"
#include "path\HSplineCurve.h"

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

