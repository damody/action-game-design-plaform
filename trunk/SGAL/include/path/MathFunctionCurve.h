//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : Untitled
//  @ File Name : MathFunctionCurve.h
//  @ Date : 2011/9/3
//  @ Author :
//
//


#if !defined(_MATHFUNCTIONCURVE_H)
#define _MATHFUNCTIONCURVE_H

#include "PathInterpolater.h"

class MathFunctionCurve : public PathInterpolater
{
public:
	Vector3 GetValue( float time );
};

#endif  //_MATHFUNCTIONCURVE_H