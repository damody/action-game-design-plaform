#pragma once
#pragma warning(disable:4819)
#include <cmath>
#include <algorithm>

template <class ParentPtr, class GetAABB>
class ptrManager
{
public:
	typedef std::vector<ParentPtr> ParentPtrs;
	//typedef bool (*CompareBall)(const ParentPtr lhs, const ParentPtr rhs);

	typedef AABB3D<ParentPtr> MyAABB3D;
	typedef std::vector<MyAABB3D*> MyAABB3Ds;

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
	MyAABB3Ds mAABBs;
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
	template<class ParentPtr2, class GetAABB2>
	Collisions GetCollision(ParentPtr2 obj)
	{
		Collisions res;
		
		if (m_ParentPtrs.empty()) { return res; }

		AABB3D<ParentPtr2>& aabbOrigin = GetAABB2()(obj);
		AABB3D<ParentPtr2> aabb = aabbOrigin;
		MyAABB3Ds bodys = mAABBs;

		if (aabb.m_Min.x > 1e19) { return res; }

		MyAABB3Ds::iterator end_of_victims = std::partition(bodys.begin(), bodys.end(), 
															std::bind2nd(AABB_is_collision<MyAABB3D*, AABB3D<ParentPtr2>>(), aabb));
		
		for(MyAABB3Ds::iterator i_vic = bodys.begin(); i_vic != end_of_victims; i_vic++){
			//每個都是AABB已碰撞，判斷多邊形碰撞

			/*※這段程式並不一般化，有違 template 本意，目前僅試作使其能達到正確的碰撞效果*/
			Bodys& bodyData = (*i_vic)->m_ParentPtr->GetBodys();
			for(auto i_body = bodyData.begin(); i_body != bodyData.end(); i_body ++){
				Attacks& atkData = aabb.m_ParentPtr->GetAttacks();
				for(int i_atk = 0; i_atk != atkData.size(); i_atk ++){
					if(atkData[i_atk].m_Area.IsCollision(i_body->m_Area) ){
						collision* co = new collision;
						co->victims.push_back((*i_vic)->m_ParentPtr);
						co->hitter = i_atk;
						res.push_back(co);
					}
				}
			}

			/*if(isCollision( i_vic->m_ParentPtr, aabb->m_ParentPtr)){
				collision* co = new collision;
				co->victims.push_back((*i_vic)->m_ParentPtr);
				co->hitter = 0;
				res.push_back(co);
			//}*/
		}

		return res;
	}
	void AddPtr(ParentPtr p)
	{
		m_ParentPtrs.push_back(p);
		mAABBs.push_back(&GetAABB()(p));
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
		for (ParentPtrs::iterator it = m_ParentPtrs.begin(); it != m_ParentPtrs.end(); ++it)
		{
			if (*it == p)
			{
				m_ParentPtrs.erase(it);
				break;
			}
		}

		for(MyAABB3Ds::iterator i = mAABBs.begin(); i != mAABBs.end(); ++i){
			if((*i)->m_ParentPtr == p){
				i = --mAABBs.erase(i);
			}
		}
	}
};

