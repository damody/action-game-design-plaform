#pragma once
#include "math/Vector3.h"

template<class ParentPtr>
struct Axis_bind
{
	float *m_x, *m_y, *m_z;
	ParentPtr m_ParentPtr;

	Axis_bind( ParentPtr p, float* _x, float* _y, float* _z)
		: m_x( _x ), m_y( _y ), m_z( &_v.z), m_ParentPtr( p ) {}
	Axis_bind( ParentPtr p, Vector3& _v)
		: m_x( &_v.x ), m_y( &_v.y ), m_z( &_v.z), m_ParentPtr( p ) {}
	Axis_bind( Vector3& _v)
		: m_x( &_v.x ), m_y( &_v.y ), m_z( &_v.z), m_ParentPtr( 0 ) {}
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

template<class Tptr>
bool Compare_z( const Tptr& lhs, const Tptr& rhs )
{
	return *lhs.m_z < *rhs.m_z;
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

template<class _Ty>
struct axis_z_greater
	: public std::binary_function<_Ty, _Ty, bool>
{
	// functor for operator>
	bool operator()( const _Ty& _Left, const _Ty& _Right ) const
	{
		// apply operator> to operands
		return *_Left.m_z >= *_Right.m_z;
	}
};

template<class _Ty>
struct axis_z_less
	: public std::binary_function<_Ty, _Ty, bool>
{
	// functor for operator>
	bool operator()( const _Ty& _Left, const _Ty& _Right ) const
	{
		// apply operator> to operands
		return *_Left.m_z <= *_Right.m_z;
	}
};
