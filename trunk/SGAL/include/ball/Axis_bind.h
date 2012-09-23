#pragma once
#include "math/Vector2.h"
//#include "ball/ball.h"
//#include "ball/Tbox.h"

template<class ParentPtr>
struct Axis_bind
{
	float* x, *y;
	ParentPtr m_ParentPtr;

	Axis_bind( ParentPtr b )
		: x( &( b->m_Position.x ) ), y( &( b->m_Position.y ) ), m_ParentPtr( b ) {}
	Axis_bind( ParentPtr b, Vector2* vec2 )
		: x( &( vec2->x ) ), y( &( vec2->y ) ), m_ParentPtr( b ) {}
	Axis_bind( float* val )
		: x( val ), y( val ), m_ParentPtr( 0 )
	{}
	bool operator == ( ParentPtr b ) const
	{
		return m_ParentPtr == b;
	}

};

template<class Tptr>
bool Compare_x( const Tptr& lhs, const Tptr& rhs )
{
	return *lhs.x < *rhs.x;
}

template<class _Ty>
struct axis_y_greater
		: public std::binary_function<_Ty, _Ty, bool>
{
	// functor for operator>
	bool operator()( const _Ty& _Left, const _Ty& _Right ) const
	{
		// apply operator> to operands
		return *_Left.y > *_Right.y;
	}
};

template<class _Ty>
struct axis_y_less
		: public std::binary_function<_Ty, _Ty, bool>
{
	// functor for operator>
	bool operator()( const _Ty& _Left, const _Ty& _Right ) const
	{
		// apply operator> to operands
		return *_Left.y < *_Right.y;
	}
};