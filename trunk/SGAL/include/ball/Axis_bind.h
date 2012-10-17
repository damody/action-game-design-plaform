#pragma once
#include "math/Vector2.h"

template<class ParentPtr>
struct Axis_bind
{
	float *m_x, *m_y;
	ParentPtr m_ParentPtr;

	Axis_bind( ParentPtr p, float* _x, float* _y)
		: m_x( _x ), m_y( _y ), m_ParentPtr( p ) {}
	Axis_bind( ParentPtr p, Vector2& _v)
		: m_x( &_v.x ), m_y( &_v.y ), m_ParentPtr( p ) {}
	Axis_bind( Vector2& _v)
		: m_x( &_v.x ), m_y( &_v.y ), m_ParentPtr( 0 ) {}
	bool operator == ( ParentPtr p ) const
	{
		return m_ParentPtr == p;
	}

};

template<class Tptr>
bool Compare_x( const Tptr& lhs, const Tptr& rhs )
{
	return *lhs.m_x < *rhs.m_x;
}

template<class Tptr>
bool Compare_y( const Tptr& lhs, const Tptr& rhs )
{
	return *lhs.m_y < *rhs.m_y;
}

template<class _Ty>
struct axis_y_greater
		: public std::binary_function<_Ty, _Ty, bool>
{
	// functor for operator>
	bool operator()( const _Ty& _Left, const _Ty& _Right ) const
	{
		// apply operator> to operands
		return *_Left.m_y >= *_Right.m_y;
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
		return *_Left.m_y <= *_Right.m_y;
	}
};
