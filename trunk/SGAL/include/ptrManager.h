
#pragma warning(disable:4819)
#pragma once
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
	ParentPtrs GetCollision( ParentPtr2 obj, GetPolygons2 getpolys )
	{
		ParentPtrs res;

		if ( m_ParentPtrs.empty() )
		{
			return res;
		}
		
		//Polygon2D poly = *getpoly( obj );
		Polygon2Ds polys = getpolys( obj );
		if( polys.size() == 0)
		{
			return res;
		}
		//poly.CheckBuildAABB();
		//poly.CheckBuildPolygon();
		//AABB2D aabb = poly.AABB();
		bool isCollision = false;
		AABB2D aabb = polys.at(0).AABB();
		for(Polygon2Ds::iterator it_poly = polys.begin();
			it_poly != polys.end(); ++it_poly)
		{
			for(Vec2s::const_iterator it_vec2 = it_poly->const_Points().begin();
				it_vec2 != it_poly->const_Points().end(); ++it_vec2)
			{
				aabb.AddPoint(*it_vec2);
			}
		}
		MyAxis_binds::iterator x_index_max, x_index_min, tmp;
		x_index_max = std::upper_bound( mXbinds.begin(), mXbinds.end(), MyAxis_bind( aabb.m_Max.x ), Compare_x<MyAxis_bind> );
		x_index_min = std::lower_bound( mXbinds.begin(), mXbinds.end(), MyAxis_bind( aabb.m_Min.x ), Compare_x<MyAxis_bind> );

		if ( x_index_max - x_index_min > 0 )
		{
			mYbinds.clear();
			std::copy( x_index_min, x_index_max, std::back_inserter( mYbinds ) );
			//                                                                                                   ----------larger------------|--smaller---   mYbinds
			tmp = std::partition( mYbinds.begin(), mYbinds.end(),                             //                                          Min.y
			                      std::bind2nd( axis_y_greater<MyAxis_bind>(), MyAxis_bind( aabb.m_Min.y ) ) );
			tmp = std::partition( mYbinds.begin(), tmp,      // range                         //                 ----middle----|---larger----|--smaller---   mYbinds
			                      std::bind2nd( axis_y_less<MyAxis_bind>(), MyAxis_bind( aabb.m_Max.y ) ) ); //            Max.y         Min.y

			if ( tmp - mYbinds.begin() > 0 )
			{
				for ( MyAxis_binds::iterator it = mYbinds.begin();
				                it != tmp; it++ )
				{
					isCollision = false;
					Polygon2Ds _polys = (Polygon2Ds)GetPolygons()(it->m_ParentPtr);
					for(Polygon2Ds::iterator it_poly = _polys.begin();
						it_poly != _polys.end(); ++it_poly)
					{
						for(Polygon2Ds::iterator it_target = polys.begin();
							it_target != polys.end(); ++it_target)
						{
							if( it_poly->zIsCollision( *it_target ) )
							{
								it_poly->CheckBuildPolygon();
								if( it_poly->IsCollision( *it_target ) )
								{
									isCollision = true;
									break;
								}
							}
						}
						if(isCollision)
						{
							res.push_back(it->m_ParentPtr);
							break;
						}
					}
					/*if ( getpolys( it->m_ParentPtr )->zIsCollision( poly ) )
					{
						if ( getpolys( it->m_ParentPtr )->IsCollision( poly ) )
						{
							res.push_back( it->m_ParentPtr );
						}
					}*/

					/*for(Polygons::iterator it_poly = polys.begin();
						it_poly != polys.end(); ++it_poly)
					{
						if(it->m_ParentPtr->m_Polygon2D.zIsCollision(*it_poly) &&
							it->m_ParentPtr->m_Polygon2D.IsCollision(*it_poly))
						{
							res.push_back(it->m_ParentPtr);
							break;
						}
					}*/
				}
			}
		}

		/*
		for(ParentPtrs::iterator it = m_ParentPtrs.begin();
			it != m_ParentPtrs.end(); ++it)
		{
			for(Polygons::iterator it_target = polys.begin();
				it_target != polys.end(); ++it_target)
			{
				if( GetPolygon()(*it)->IsCollision(*it_target) )
				{
					res.push_back(*it);
					break;
				}
			}
		}
		*/
		if ( res.size() > 1 )
		{
			DoubleCheck( res );
		}

		for( ParentPtrs::iterator it = res.begin();
			it != res.end(); ++it)
		{
			if(*it == obj)
			{
				it = res.erase(it)-1;
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




