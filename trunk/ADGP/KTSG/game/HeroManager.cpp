#include "StdGame.h"
#include "HeroManager.h"
#include "global.h"

HeroManager::HeroManager(void)
{
}


HeroManager::~HeroManager(void)
{
}

void HeroManager::Update( float dt )
{
	CleanTrash();
	for (Heroes::iterator it = m_Heroes.begin(); it != m_Heroes.end();it++)
	{
		(*it)->Update(dt);	
	}
}

void HeroManager::UpdateDataToDraw()
{
	for (Heroes::iterator it = m_Heroes.begin(); it != m_Heroes.end();it++)
	{
		(*it)->UpdateDataToDraw();	
	}
	std::stable_sort(m_Heroes.begin(),m_Heroes.end(),SortHero);
}

Hero* HeroManager::Create(const std::string& hero,const Vector3& pos,int team/*=0*/ )
{
	Hero_RawPtr h = Hero_RawPtr(new Hero(hero));
	h->SetPosition(pos);
	h->SetTeam(team);
	m_Heroes.push_back(h);
	return m_Heroes.back();
}

void HeroManager::Clear()
{
	m_Heroes.clear();
	m_TrashCan.clear();
}

void HeroManager::ClearDeadBody()
{

}

bool HeroManager::Empty()
{
	return m_Heroes.empty();
}

Heroes::iterator HeroManager::HeroVectorBegin()
{
	return m_Heroes.begin();
}

Heroes::iterator HeroManager::HeroVectorEnd()
{
	return m_Heroes.end();
}

int HeroManager::AmountHeroes()
{
	return m_Heroes.size();
}

int HeroManager::AmountEnemy(int team)
{
	int amount=0;
	for (Heroes::iterator it = m_Heroes.begin(); it != m_Heroes.end();it++)
	{
		if((*it)->Team()!=0 && (*it)->Team() == team)
							continue;
		amount++;
	}
	return amount;
}

Hero* HeroManager::GetClosestHero(const Vector3& pos )
{
	float d = 99999;
	Hero* h = NULL;
	for (Heroes::iterator it = m_Heroes.begin(); it != m_Heroes.end();it++)
	{
		if((*it)->Position().distance(pos) < d)
		{
			d = (*it)->Position().distance(pos);
			h = (*it);
		}	
	}
	return h;
}

Hero* HeroManager::GetClosestFriend(const Vector3& pos,int team )
{
	float d = 99999;
	Hero* h = NULL;
	for (Heroes::iterator it = m_Heroes.begin(); it != m_Heroes.end();it++)
	{
		if((*it)->Team()==0 || (*it)->Team() != team)
							continue;
		if((*it)->Position().distance(pos) < d)
		{
			d = (*it)->Position().distance(pos);
			h = (*it);
		}	
	}
	return h;
}

Hero* HeroManager::GetClosestEnemy(const Vector3& pos,int team )
{
	float d = 99999;
	Hero* h = NULL;
	for (Heroes::iterator it = m_Heroes.begin(); it != m_Heroes.end();it++)
	{
		if((*it)->Team()!=0 && (*it)->Team() == team)
			continue;
		if((*it)->Position().distance(pos) < d)
		{
			d = (*it)->Position().distance(pos);
			h = (*it);
		}	
	}
	return h;
}

void HeroManager::Distory( Heroes::iterator it,int time/*=0*/ )
{
	if (!InTrashCan(*it))
	{
		Trash th;
		th.m_Trash=it;
		th.m_Time=time;
		m_TrashCan.push_back(th);
	}	
}

void HeroManager::Distory( Hero_RawPtr hero,int time/*=0*/ )
{
	if (!InTrashCan(hero))
	{
		Heroes::iterator it;
		for (it = m_Heroes.begin(); it != m_Heroes.end();it++)
		{
			if(*it == hero)
			{
				break;
			}
		}
		Trash th;
		th.m_Trash=it;
		th.m_Time=time;
		m_TrashCan.push_back(th);
	}
}

void HeroManager::CleanTrash()
{
	for (TrashCan::iterator it= m_TrashCan.begin(); it != m_TrashCan.end() ; )
	{
		if (it->m_Time <= 0)
		{
			delete(*(it->m_Trash));
			m_Heroes.erase(it->m_Trash);
			it=m_TrashCan.erase(it);
			
		}else{
			it->m_Time--;
			it++;
		}
	}
}

bool HeroManager::InTrashCan( Hero_RawPtr hero )
{
	for (TrashCan::iterator it=m_TrashCan.begin();it != m_TrashCan.end();it++)
	{
		if(*(it->m_Trash) ==hero) 
			return true;
	}

	return false;
}





