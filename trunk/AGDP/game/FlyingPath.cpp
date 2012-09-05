#include "StdGame.h"
#include "FlyingPath.h"

FlyingPath::FlyingPath( void ): m_Type( FlyingType::LINEARLINE_PATH )
{
}

FlyingPath::FlyingPath( FlyingType::e type ): m_Type( type )
{
}

FlyingPath::~FlyingPath( void )
{
}

Vector3 FlyingPath::CalcStraightPos( const Vector3& p0, const Vector3& p1, float scalar )
{
	return p0 * ( 1 - scalar ) + p1 * scalar;
}

Vector3 FlyingPath::CalcBezierCurvePos( const Vector3& start, const Vector3& cnt1, const Vector3& cnt2, const Vector3& end, float scalar )
{
	return start * pow( 1 - scalar, 3 ) + 3 * cnt1 * scalar * pow( 1 - scalar, 2 ) + 3 * cnt2 * pow( scalar, 2 ) * ( 1 - scalar ) + end * pow( scalar, 3 );
}

Vector3 FlyingPath::CalcHSplineCurvePos( const Vector3& p4, const Vector3& p3, const Vector3& p2, const Vector3& p1, float Scalar, float c /*= 0.4f*/ )
{
	float S2 = Scalar * Scalar, S3 = Scalar * Scalar * Scalar, tension = ( 1.0f - c ) / 2;
	Vector3 start = p2, end = p3, cnt1 = ( p1 - p3 ) * tension, cnt2 = ( p2 - p4 ) * tension;
	Vector3 out = ( start * ( -2.0f * S3 + 3.0f * S2 ) +
	                end * ( 2.0f * S3 -  3.0f * S2 + 1 ) +
	                cnt1 * ( S3 - S2 ) +
	                cnt2 * ( S3 - 2 * S2 + Scalar ) );
	return out;
}

Vector3 FlyingPath::CalcBSplineCurvePos( const Vector3& start, const Vector3& cnt1, const Vector3& cnt2, const Vector3& end, float Scalar )
{
	float S2 = Scalar * Scalar, S3 = Scalar * Scalar * Scalar;
	Vector3 out = ( start * ( 1.0f + 3.0f * ( S2 - Scalar ) - S3 ) +
	                cnt1 * ( 4.0f - 6.0f * S2 + 3.0f * S3 ) +
	                cnt2 * ( 1.0f + 3.0f * ( Scalar + S2 - S3 ) ) +
	                end * S3 ) / 6.0f;
	return out;
}

Vector3 FlyingPath::GetValue( float time )
{
	CheckSort();

	if ( m_points.empty() )
	{
		return Vector3::ZERO;
	}

	const int size = ( int )m_points.size();

	if ( size == 1 )
	{
		return m_points[0].pos;
	}
	else if ( m_points[0].time > time )
	{
		return m_points[0].pos;
	}

	int i = 0;

	if ( m_points.back().time >= time || m_Type == FlyingType::LINEARLINE_PATH )
	{
		for ( i = 0; i < size; i++ )
		{
			if ( m_points[i].time > time )
			{
				time = ( time - m_points[i - 1].time ) / ( m_points[i].time - m_points[i - 1].time );
				break;
			}
		}
	}
	else
	{
		switch ( m_Type )
		{
		case FlyingType::BEZIERCURVE_PATH :
			i = ( size / 4 ) * 4;
			time = time - m_points[size - 1].time;
			break;

		case FlyingType::BSPLINECURVE_PATH :
		case FlyingType::HSPLINECURVE_PATH :
			i = size;
			time = time - m_points[i - 1].time;
			break;
		}
	}

	int index[4] = {0};

	switch ( m_Type )
	{
	case FlyingType::BEZIERCURVE_PATH :
		index[0] = i;
		index[1] = i + 1;
		index[2] = i + 2;
		index[3] = i + 3;

		for ( int j = 0; j < 4; ++j )
		{
			if ( index[j] < 0 )
			{
				index[j] = 0;
			}

			if ( index[j] >= size )
			{
				index[j] = size - 1;
			}
		}

		return m_position + CalcBezierCurvePos( m_points[index[0]].pos, m_points[index[1]].pos, m_points[index[2]].pos, m_points[index[3]].pos, time );

	case  FlyingType::BSPLINECURVE_PATH :
		index[0] = i - 2;
		index[1] = i - 1;
		index[2] = i;
		index[3] = i + 1;

		for ( int j = 0; j < 4; ++j )
		{
			if ( index[j] < 0 )
			{
				index[j] = 0;
			}

			if ( index[j] >= size )
			{
				index[j] = size - 1;
			}
		}

		return m_position + CalcBSplineCurvePos( m_points[index[0]].pos, m_points[index[1]].pos, m_points[index[2]].pos, m_points[index[3]].pos, time );

	case  FlyingType::HSPLINECURVE_PATH :
		index[0] = i - 2;
		index[1] = i - 1;
		index[2] = i;
		index[3] = i + 1;

		for ( int j = 0; j < 4; ++j )
		{
			if ( index[j] < 0 )
			{
				index[j] = 0;
			}

			if ( index[j] >= size )
			{
				index[j] = size - 1;
			}
		}

		return m_position + CalcHSplineCurvePos( m_points[index[0]].pos, m_points[index[1]].pos, m_points[index[2]].pos, m_points[index[3]].pos, time );

	case FlyingType::LINEARLINE_PATH :
		index[0] = i - 1;
		index[1] = i;

		for ( int j = 0; j < 2; ++j )
		{
			if ( index[j] < 0 )
			{
				index[j] = 0;
			}

			if ( index[j] >= size )
			{
				index[j] = size - 1;
			}
		}

		return m_position + CalcStraightPos( m_points[index[0]].pos, m_points[index[1]].pos, time );

	default:
		return m_position;
	}
}






