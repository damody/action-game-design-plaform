
#pragma warning(disable:4819)
#pragma once
#include <cmath>
#include "math/Polygon2D.h"
#include "math/AABB2D.h"
#include "ball/Axis_bind.h"

//#include "Tbox.h"

template <class ParentPtr, class GetPolygons>
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
	struct collision{
		int hitter;
		ParentPtrs victims;
	};
	typedef std::vector<collision> Collisions;

private:
	ParentPtrs m_ParentPtrs;
	MyAxis_binds mXbinds, mYbinds;

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
		/*for ( ParentPtrs::iterator it = m_ParentPtrs.begin();
		                it != m_ParentPtrs.end(); ++it )
		{
			GetPolygon()( *it )->CheckBuildAABB();
		}*/
		mXbinds.clear();
		for ( ParentPtrs::iterator it = m_ParentPtrs.begin();
			it != m_ParentPtrs.end(); ++it )
		{
			Polygon2Ds poly = (Polygon2Ds)GetPolygons()( *it );
			for(Polygon2Ds::iterator it_poly = poly.begin();
				it_poly != poly.end(); ++it_poly)
			{
				it_poly->CheckBuildAABB();
				mXbinds.push_back( MyAxis_bind( *it, &( it_poly->AABB().m_Max ) ) );
				mXbinds.push_back( MyAxis_bind( *it, &( it_poly->AABB().m_Min ) ) );
			}
		}

		std::sort( mXbinds.begin(), mXbinds.end(), Compare_x<MyAxis_bind> );
	}
	template<class ParentPtr2, class GetPolygons2>
	Collisions GetCollision( ParentPtr2 obj, GetPolygons2 getpolys )
	{
		Collisions res;

		if ( m_ParentPtrs.empty() )
		{
			return res;
		}
		
		//Polygon2D poly = *getpoly( obj );
		Polygon2Ds polys1 = getpolys( obj );
		if( polys1.size() == 0)
		{
			return res;
		}
		//poly.CheckBuildAABB();
		//poly.CheckBuildPolygon();
		//AABB2D aabb = poly.AABB();
		bool isCollision = false;
		
		for( ParentPtrs::iterator it = m_ParentPtrs.begin(); it != m_ParentPtrs.end(); ++it ){
			Polygon2Ds polys2 = (Polygon2Ds)GetPolygons()( *it );
			for(int ipolys1 = 0; ipolys1 < polys1.size(); ipolys1 ++ ){
				collision tc = {};
				tc.hitter = ipolys1;
				for(Polygon2Ds::iterator ipolys2 = polys2.begin(); ipolys2 != polys2.end(); ipolys2 ++ ){
					//Z軸
					if(abs(ipolys2->GetZPoint() - polys1[ipolys1].GetZPoint()) > ipolys2->GetZRange() + polys1[ipolys1].GetZRange()){
						break;
					}
					//XY 平面
					ipolys2->CheckBuildPolygon();
					polys1[ipolys1].CheckBuildPolygon();
					if( ipolys2->IsCollision(polys1[ipolys1])){
						tc.victims.push_back(*it);
						break;
					}
				}
				if(tc.victims.size() != 0){
					res.push_back(tc);
				}
			}
		}

		return res;
	}
	void AddPtr( ParentPtr p )
	{
/*		assert( !GetPolygon()( p )->Points().empty() );*/
		m_ParentPtrs.push_back( p );
// 		mXbinds.push_back( MyAxis_bind( m_ParentPtrs.back(), &( GetPolygon()( m_ParentPtrs.back() )->AABB().m_Max ) ) );
// 		mXbinds.push_back( MyAxis_bind( m_ParentPtrs.back(), &( GetPolygon()( m_ParentPtrs.back() )->AABB().m_Min ) ) );
	}
	void AddPtrs( const ParentPtrs& ps )
	{
		for ( ParentPtrs::const_iterator it = ps.begin();
		                it != ps.end(); ++it )
		{
// 			assert( !GetPolygon()( *it )->Points().empty() );
			m_ParentPtrs.push_back( *it );
// 			mXbinds.push_back( MyAxis_bind( m_ParentPtrs.back(), &( GetPolygon()( m_ParentPtrs.back() )->AABB().m_Max ) ) );
// 			mXbinds.push_back( MyAxis_bind( m_ParentPtrs.back(), &( GetPolygon()( m_ParentPtrs.back() )->AABB().m_Min ) ) );
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

// 		for ( MyAxis_binds::iterator it = mXbinds.begin();
// 		                it != mXbinds.end(); ++it )
// 		{
// 			if ( it->m_ParentPtr == p )
// 			{
// 				if ( doubleCheck )
// 				{
// 					mXbinds.erase( it );
// 					break;
// 				}
// 				else
// 				{
// 					it = mXbinds.erase( it ) - 1;
// 				}
// 			}
// 		}
	}
};

/*
struct GetPolygonFromTbox
{
	Polygon2D* operator()(Tbox* tbox){return &(tbox->m_Polygon2D);}
};
*/




