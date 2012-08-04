#include "HeroManager.h"
#include "global.h"

HeroManager::HeroManager(void)
{
}


HeroManager::~HeroManager(void)
{
}

Hero* HeroManager::Create( std::string hero,Vector3 pos,int team/*=0*/ )
{
	Hero_RawPtr h = Hero_RawPtr(new Hero(hero));
	h->SetPosition(pos);
	h->SetTeam(team);
	m_Heroes.push_back(h);
	return m_Heroes.back();
}

void HeroManager::Delete( Hero_RawPtr hero )
{
	for (Heroes::iterator it = m_Heroes.begin(); it != m_Heroes.end();it++)
	{
		if(*it == hero)
		{
			m_Heroes.erase(it);
			return;
		}
	}
}

void HeroManager::Clear()
{
	m_Heroes.clear();
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

Hero* HeroManager::GetClosestHero( Vector3 pos )
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

Hero* HeroManager::GetClosestFriend( Vector3 pos,int team )
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

Hero* HeroManager::GetClosestEnemy( Vector3 pos,int team )
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



