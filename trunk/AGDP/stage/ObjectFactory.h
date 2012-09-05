#pragma once
#include "algo/nway.h"
#include "algo/RandomWay.h"
#include "algo/StraightWay.h"
#include "algo/SwirlWay.h"
#include "ball/straight.h"
#include "ball/split.h"
#include "ball/homing.h"
#include "ball/gravity.h"
#include "ball/delay.h"
#include "path/BezierCurve.h"
#include "path/BsplineCurve.h"
#include "path/HSplineCurve.h"
#include "path/LinearLine.h"

class TrajectoryFactory
{
public:
	enum TrajectoryKind
	{
	        TRAJECTORY_ERROR = 100,
	        NWAY,
	        RANDOM_WAY,
	        STRAIGHT_WAY,
	        SWIR_WAY
	};
	static int Generate( const char* type, Trajectory*& out )
	{
		if ( strcmp( type, "nway" ) == 0 )
		{
			out = new NWay;
			return NWAY;
		}
		else if ( strcmp( type, "randomway" ) == 0 )
		{
			out = new RandomWay;
			return RANDOM_WAY;
		}
		else if ( strcmp( type, "straightway" ) == 0 )
		{
			out = new StraightWay;
			return STRAIGHT_WAY;
		}
		else if ( strcmp( type, "swirlway" ) == 0 )
		{
			out = new SwirlWay;
			return SWIR_WAY;
		}

		return TRAJECTORY_ERROR;
	}
};

class BehaviorFactory
{
public:
	enum BehaviorKind
	{
	        BEHAVIOR_ERROR = 200,
	        STRAIGHT,
	        GRAVITY,
	        HOMING,
	        SPLIT
	};
	static int Generate( const char* type, Behavior*& out )
	{
		if ( strcmp( type, "straight" ) == 0 )
		{
			out = new Straight;
			return STRAIGHT;
		}
		else if ( strcmp( type, "gravity" ) == 0 )
		{
			out = new Gravity;
			return GRAVITY;
		}
		else if ( strcmp( type, "homing" ) == 0 )
		{
			out = new Homing;
			return HOMING;
		}
		else if ( strcmp( type, "split" ) == 0 )
		{
			out = new Split;
			return SPLIT;
		}

		return BEHAVIOR_ERROR;
	}
};

class PathFactory
{
public:
	enum PathKind
	{
	        PATH_ERROR = 300,
	        BEZIER_CURVE,
	        BSPLINE_CURVE,
	        HSPLINE_CURVE,
	        LINEAR_LINE
	};
	static int Generate( const char* type, PathInterpolater*& out )
	{
		if ( strcmp( type, "beziercurve" ) == 0 )
		{
			out = new BezierCurve;
			return BEZIER_CURVE;
		}
		else if ( strcmp( type, "bsplinecurve" ) == 0 )
		{
			out = new BsplineCurve;
			return BSPLINE_CURVE;
		}
		else if ( strcmp( type, "hsplinecurve" ) == 0 )
		{
			out = new HsplineCurve;
			return HSPLINE_CURVE;
		}
		else if ( strcmp( type, "linearline" ) == 0 )
		{
			out = new LinearLine;
			return LINEAR_LINE;
		}

		return PATH_ERROR;
	}
};
