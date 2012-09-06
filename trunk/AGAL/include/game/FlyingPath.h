#pragma once
#include <cmath>
#include "math\Vector3.h"
#include "path\PathInterpolater.h"

struct FlyingType
{
	enum e
	{
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
	FlyingPath( void );
	FlyingPath( FlyingType::e type );
	~FlyingPath( void );

	FlyingType::e m_Type;
	Vector3 GetValue( float time );

	static Vector3 CalcStraightPos( const Vector3& p0, const Vector3& p1, float scalar ); //一維貝茲
	static Vector3 CalcBezierCurvePos( const Vector3& start, const Vector3& cnt1, const Vector3& cnt2, const Vector3& end, float scalar ); //三維貝茲
	static Vector3 CalcHSplineCurvePos( const Vector3& p4, const Vector3& p3, const Vector3& p2, const Vector3& p1, float Scalar, float c = 0.4f ); //H-spline
	static Vector3 CalcBSplineCurvePos( const Vector3& start, const Vector3& cnt1, const Vector3& cnt2, const Vector3& end, float Scalar ); //B-spline
};

