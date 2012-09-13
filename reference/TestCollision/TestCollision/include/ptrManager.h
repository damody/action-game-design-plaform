
#pragma warning(disable:4819)
#pragma once
#include "math/Polygon2D.h"
#include "math/AABB2D.h"
#include "Axis_bind.h"
#include "Tbox.h"

template <class ParentPtr, class GetPolygon>
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

public:
	ptrManager(){m_ParentPtrs.empty();}
	~ptrManager(){}
	bool Empty(){return m_ParentPtrs.empty();}
	const ParentPtrs& m(){return m_ParentPtrs;}

	template<class ParentPtr2, class GetPolygon2>
	ParentPtrs GetCollision(ParentPtr2 obj, GetPolygon2 getpoly)
	{
		ParentPtrs res;
		if(m_ParentPtrs.empty())
			return res;
		Polygons polys = getpoly(obj);
		for(Polygons::iterator it = polys.begin();
			it != polys.end(); ++it)
		{
			it->CheckBuildEdges();
		}


		AABB2D aabb(polys[0]);
		aabb.Larger(50);
		MyAxis_binds::iterator x_index_max, x_index_min, tmp;
		x_index_max = std::upper_bound(mXbinds.begin(), mXbinds.end(), MyAxis_bind(&aabb.m_Max.x), Compare_x<MyAxis_bind>);
		x_index_min = std::lower_bound(mXbinds.begin(), mXbinds.end(), MyAxis_bind(&aabb.m_Min.x), Compare_x<MyAxis_bind>);
		if(x_index_max-x_index_min > 0)
		{
			mYbinds.clear();
			std::copy(x_index_min, x_index_max, std::back_inserter(mYbinds));
			tmp = std::partition(mYbinds.begin(), mYbinds.end(),
				std::bind2nd(axis_y_greater<MyAxis_bind>(), MyAxis_bind(&aabb.m_Min.y)));
			tmp = std::partition(mYbinds.begin(), tmp,       // range
				std::bind2nd(axis_y_less<MyAxis_bind>(), MyAxis_bind(&aabb.m_Max.y)));
			if(tmp - mYbinds.begin() > 0)
			for(MyAxis_binds::iterator it = mYbinds.begin();
				it != tmp; it++)
			{
				for(Polygons::iterator it_poly = polys.begin();
					it_poly != polys.end(); ++it_poly)
				{
					if(it->m_ParentPtr->m_Polygon2D.zIsCollision(*it_poly) &&
						it->m_ParentPtr->m_Polygon2D.IsCollision(*it_poly))
					{
						res.push_back(it->m_ParentPtr);
						break;
					}
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

		return res;
	}
	void AddPtr(ParentPtr p)
	{
		assert(!GetPolygon()(p)->Points().empty());
		m_ParentPtrs.push_back(p);
		mXbinds.push_back(m_ParentPtrs.back());
	}
	void AddPtrs( const ParentPtrs& ps)
	{
		for(ParentPtrs::const_iterator it = ps.begin();
			it != ps.end(); ++it)
		{
			assert(!GetPolygon()(*it)->Points().empty());
			m_ParentPtrs.push_back(*it);
			mXbinds.push_back(m_ParentPtrs.back());
		}
	}
};

struct GetPolygonFromTbox
{
	Polygon2D* operator()(Tbox* tbox){return &(tbox->m_Polygon2D);}
};

struct GetPolygonsFromTbox
{
	Polygons polygons; 
	Polygons operator()(Tbox* tbox)
	{
		polygons.push_back(tbox->m_Polygon2D);
		return polygons;
	}
};


