#pragma once
#pragma warning(disable:4819)
#include <cmath>
#include <algorithm>
#include "ball/Axis_bind.h"

template <class ParentPtr, class GetAABB>
class ptrManager
{
public:
	typedef std::vector<ParentPtr> ParentPtrs;
	//typedef bool (*CompareBall)(const ParentPtr lhs, const ParentPtr rhs);
	typedef Axis_bind<ParentPtr> MyAxis_bind;
	typedef std::vector<MyAxis_bind> MyAxis_binds;
	/*GetCollision 專用回傳結構
	 * hitter	:傳入者的第幾個該屬性
	 * victims	:此屬性擊中了哪些人
	 */
	struct collision
	{
		int hitter;
		ParentPtrs victims;
	};
	typedef std::vector<collision> Collisions;

private:
	ParentPtrs m_ParentPtrs;
	MyAxis_binds mXbinds, mYbinds, mZbinds;

private:
	void DoubleCheck( ParentPtrs& pps ) //check and correct when this vector have the same element
	{
		for ( int i = 0; i < pps.size() - 1; i++ )
		{
			for ( int j = i + 1; j < pps.size(); j++ )
			{
				if ( pps.at( i ) == pps.at( j ) )
				{
					pps.erase( pps.begin() + j );
					i--;
					//break;
				}
			}
		}
	}

public:
	ptrManager() {m_ParentPtrs.empty();}
	~ptrManager() {}
	bool Empty() {return m_ParentPtrs.empty();}
	const ParentPtrs& m() {return m_ParentPtrs;}
	void PrepareForCollision() // every loop before you want to GetCollision
	{
		std::sort( mXbinds.begin(), mXbinds.end(), Compare_x<MyAxis_bind> );
	}
	template<class ParentPtr2, class GetAABB2>
	Collisions GetCollision( ParentPtr2 obj )
	{
		Collisions res;

		if ( m_ParentPtrs.empty() )
		{
			return res;
		}

		AABB2D& aabb = GetAABB2()( obj );

		if ( aabb.m_Min.x > 1e19 ) { return res; }

		MyAxis_binds::iterator x_index_max, x_index_min, tmp, tmp2;
		x_index_max = std::upper_bound( mXbinds.begin(), mXbinds.end(), MyAxis_bind( aabb.m_Max ), Compare_x<MyAxis_bind> );
		x_index_min = std::lower_bound( mXbinds.begin(), mXbinds.end(), MyAxis_bind( aabb.m_Min ), Compare_x<MyAxis_bind> );
		//std::cout << "attack min x:" << aabb.m_Min.x << ", max x:" << aabb.m_Max.x << std::endl;

		if ( x_index_max - x_index_min > 0 )
		{
			mYbinds.clear();
			std::copy( x_index_min, x_index_max, std::back_inserter( mYbinds ) );
			//無法判斷大於aabb的範圍
// 			tmp = std::partition( mYbinds.begin(), mYbinds.end(),      // range
// 			                      std::bind2nd( axis_y_less<MyAxis_bind>(), MyAxis_bind( aabb.m_Max ) ) );
// 			tmp = std::partition( mYbinds.begin(), tmp,        // range
// 			                       std::bind2nd( axis_y_greater<MyAxis_bind>(), MyAxis_bind( aabb.m_Min ) ) ); // criterion
// 
// 			if ( tmp - mYbinds.begin() > 0 )
// 			{
// 				for ( MyAxis_binds::iterator it = mYbinds.begin(); it != tmp; it++ )
// 				{
// 					collision co;
// 					co.victims.push_back( it->m_ParentPtr );
// 					co.hitter = 0;
// 					res.push_back( co );
// 				}
// 			}
// 			else
			{
				for ( MyAxis_binds::iterator it = mYbinds.begin(); it != mYbinds.end(); it++ )
				{
					if ( GetAABB()( it->m_ParentPtr ).IsCollision( aabb ) )
					{
						collision co;
						co.victims.push_back( it->m_ParentPtr );
						co.hitter = 0;
						res.push_back( co );
					}
				}
			}
		}

		return res;
	}
	void AddPtr( ParentPtr p )
	{
		m_ParentPtrs.push_back( p );
		mXbinds.push_back( MyAxis_bind( p, GetAABB()( p ).m_Max  ) );
		mXbinds.push_back( MyAxis_bind( p, GetAABB()( p ).m_Min  ) );
	}
	void AddPtrs( const ParentPtrs& ps )
	{
		for ( ParentPtrs::const_iterator it = ps.begin();
		                it != ps.end(); ++it )
		{
			AddPtr( *it );
		}
	}
	void ErasePtr( ParentPtr p )
	{
		/*		bool doubleCheck = false;*/
		for ( ParentPtrs::iterator it = m_ParentPtrs.begin();
		                it != m_ParentPtrs.end(); ++it )
		{
			if ( *it == p )
			{
				m_ParentPtrs.erase( it );
				break;
			}
		}

		for ( MyAxis_binds::iterator it = mXbinds.begin();
		                it != mXbinds.end(); ++it )
		{
			if ( it->m_ParentPtr == p )
			{
				it = --mXbinds.erase( it );
			}
		}
	}
};

