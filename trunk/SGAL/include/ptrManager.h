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
	typedef std::vector<collision*> Collisions;

	struct compareXLength_
	{
		bool operator()(ParentPtr i, ParentPtr j) { return i->GetBodyAABB().m_Len.x < j->GetBodyAABB().m_Len.x; }
	} m_compareXLength;
	struct compareYLength_
	{
		bool operator()(ParentPtr i, ParentPtr j) { return i->GetBodyAABB().m_Len.y < j->GetBodyAABB().m_Len.y; }
	} m_compareYLength;
	struct compareZLength_
	{
		bool operator()(ParentPtr i, ParentPtr j) { return i->GetBodyAABB().m_Len.z < j->GetBodyAABB().m_Len.z; }
	} m_compareZLength;

private:
	ParentPtrs m_ParentPtrs;
	MyAxis_binds mXbinds, mYbinds, mZbinds;
	float	m_MaxLenX, m_MaxLenY, m_MaxLenZ;
private:
	void DoubleCheck(ParentPtrs& pps)   //check and correct when this vector have the same element
	{
		for (int i = 0; i < pps.size() - 1; i++)
		{
			for (int j = i + 1; j < pps.size(); j++)
			{
				if (pps.at(i) == pps.at(j))
				{
					pps.erase(pps.begin() + j);
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
		std::sort(mXbinds.begin(), mXbinds.end(), Compare_x<MyAxis_bind>);
		auto maxLenIterator = std::max_element(m_ParentPtrs.begin(), m_ParentPtrs.end(), m_compareXLength);
		m_MaxLenX = (*maxLenIterator)->GetBodyAABB().m_Len.x;
		maxLenIterator = std::max_element(m_ParentPtrs.begin(), m_ParentPtrs.end(), m_compareYLength);
		m_MaxLenY = (*maxLenIterator)->GetBodyAABB().m_Len.y;
		maxLenIterator = std::max_element(m_ParentPtrs.begin(), m_ParentPtrs.end(), m_compareZLength);
		m_MaxLenZ = (*maxLenIterator)->GetBodyAABB().m_Len.z;
	}
	template<class ParentPtr2, class GetAABB2>
	Collisions GetCollision(ParentPtr2 obj)
	{
		Collisions res;

		if (m_ParentPtrs.empty())
		{
			return res;
		}

		AABB3D<ParentPtr2>& aabbOrigin = GetAABB2()(obj);
		AABB3D<ParentPtr2> aabb = aabbOrigin;

		if (aabb.m_Min.x > 1e19) { return res; }

		//加大成最長的aabb

		if (m_MaxLenX > aabb.m_Len.x)
		{
			aabb.Larger((m_MaxLenX - aabb.m_Len.x) * 0.5f, 0.0f, 0.0f);
		}

		if (m_MaxLenY > aabb.m_Len.y)
		{
			aabb.Larger(0.0f, (m_MaxLenY - aabb.m_Len.y) * 0.5f, 0.0f);
		}

		if (m_MaxLenZ > aabb.m_Len.z)
		{
			aabb.Larger(0.0f, 0.0f, (m_MaxLenZ - aabb.m_Len.z) * 0.5f);
		}

		MyAxis_binds::iterator x_index_max, x_index_min, tmp, tmp2;
		x_index_max = std::upper_bound(mXbinds.begin(), mXbinds.end(), MyAxis_bind(aabb.m_Max), Compare_x<MyAxis_bind>);
		x_index_min = std::lower_bound(mXbinds.begin(), mXbinds.end(), MyAxis_bind(aabb.m_Min), Compare_x<MyAxis_bind>);
		//std::cout << "attack min x:" << aabb.m_Min.x << ", max x:" << aabb.m_Max.x << std::endl;

		if (x_index_max - x_index_min > 0)
		{
			mYbinds.clear();
			std::copy(x_index_min, x_index_max, std::back_inserter(mYbinds));
			//無法判斷大於aabb的範圍
			tmp = std::partition(mYbinds.begin(), mYbinds.end(),       // range
			                     std::bind2nd(axis_y_less<MyAxis_bind>(), MyAxis_bind(aabb.m_Max)));
			tmp = std::partition(mYbinds.begin(), tmp,         // range
			                     std::bind2nd(axis_y_greater<MyAxis_bind>(), MyAxis_bind(aabb.m_Min)));      // criterion

			if (tmp - mYbinds.begin() > 0)
			{
				mZbinds.clear();
				std::copy(mYbinds.begin(), tmp, std::back_inserter(mZbinds));
				tmp = std::partition(mZbinds.begin(), mZbinds.end(),       // range
				                     std::bind2nd(axis_z_less<MyAxis_bind>(), MyAxis_bind(aabb.m_Max)));
				tmp = std::partition(mZbinds.begin(), tmp,         // range
				                     std::bind2nd(axis_z_greater<MyAxis_bind>(), MyAxis_bind(aabb.m_Min)));      // criterion

				if (tmp - mZbinds.begin() > 0)
				{
					ParentPtrs victims;

					for (MyAxis_binds::iterator it = mZbinds.begin(); it != tmp; it++)
					{
						if (std::find(victims.begin(), victims.end(), it->m_ParentPtr) == victims.end() && obj != it->m_ParentPtr)
						{
							collision* co = new collision;
							co->victims.push_back(it->m_ParentPtr);
							co->hitter = 0;
							res.push_back(co);
							victims.push_back(it->m_ParentPtr);
						}
					}
				}
				else
				{
					for (MyAxis_binds::iterator it = mYbinds.begin(); it != mYbinds.end(); it++)
					{
						if (GetAABB()(it->m_ParentPtr).IsCollision(aabb))
						{
							collision* co = new collision;
							co->victims.push_back(it->m_ParentPtr);
							co->hitter = 0;
							res.push_back(co);
						}
					}
				}
			}
			else
			{
				for (MyAxis_binds::iterator it = mYbinds.begin(); it != mYbinds.end(); it++)
				{
					if (GetAABB()(it->m_ParentPtr).IsCollision(aabb))
					{
						collision* co = new collision;
						co->victims.push_back(it->m_ParentPtr);
						co->hitter = 0;
						res.push_back(co);
					}
				}
			}
		}

		return res;
	}
	void AddPtr(ParentPtr p)
	{
		m_ParentPtrs.push_back(p);
		mXbinds.push_back(MyAxis_bind(p, GetAABB()(p).m_Max));
		mXbinds.push_back(MyAxis_bind(p, GetAABB()(p).m_Min));
	}
	void AddPtrs(const ParentPtrs& ps)
	{
		for (ParentPtrs::const_iterator it = ps.begin();
		                it != ps.end(); ++it)
		{
			AddPtr(*it);
		}
	}
	void ErasePtr(ParentPtr p)
	{
		/*		bool doubleCheck = false;*/
		for (ParentPtrs::iterator it = m_ParentPtrs.begin();
		                it != m_ParentPtrs.end(); ++it)
		{
			if (*it == p)
			{
				m_ParentPtrs.erase(it);
				break;
			}
		}

		for (MyAxis_binds::iterator it = mXbinds.begin();
		                it != mXbinds.end(); ++it)
		{
			if (it->m_ParentPtr == p)
			{
				it = --mXbinds.erase(it);
			}
		}
	}
};

