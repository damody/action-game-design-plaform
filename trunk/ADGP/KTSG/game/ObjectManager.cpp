#include "ObjectManager.h"


ObjectMG::ObjectMG(void)
{
	m_CTrashCan.clear();
	m_WTrashCan.clear();
}


ObjectMG::~ObjectMG(void)
{
}

void ObjectMG::Update( float dt )
{
	CleanTrashCan();

	for (Chees::iterator it = m_Chees.begin(); it != m_Chees.end();it++)
	{
		(*it)->Update(dt);
	}

	for (Weapons::iterator it = m_Weapons.begin(); it != m_Weapons.end();it++)
	{
		(*it)->Update(dt);
	}
}

void ObjectMG::UpdateDataToDraw()
{
	for (Chees::iterator it = m_Chees.begin(); it != m_Chees.end();it++)
	{
		(*it)->UpdateDataToDraw();
	}
	std::stable_sort(m_Weapons.begin(),m_Weapons.end(),SortWeapon);
	for (Weapons::iterator it = m_Weapons.begin(); it != m_Weapons.end();it++)
	{
		(*it)->UpdateDataToDraw();
	}
}

Chee** ObjectMG::CreateChee(const std::string& chee,const Vector3& pos,const Vector3& vel,int num/*=1*/,int team/*=0*/ )
{
	Chee_RawPtr* c = new Chee_RawPtr [num];
	for(int i=0;i<num;i++)
	{
		c[i]= Chee_RawPtr(new Chee(chee));
		c[i]->SetPosition(pos);
		c[i]->SetVelocity(vel);
		c[i]->SetTeam(team);
		m_Chees.push_back(c[i]);
	}
	return c;

}

Weapon** ObjectMG::CreateWeapon(const std::string& weapon,const Vector3& pos,int num/*=1*/,int team/*=0*/ )
{
	Weapon_RawPtr* w = new Weapon_RawPtr [num];
	for(int i=0;i<num;i++)
	{
		w[i]= Weapon_RawPtr(new Weapon(weapon));
		w[i]->SetPosition(pos);
		w[i]->SetTeam(team);
		m_Weapons.push_back(w[i]);
	}
	return w;
}

void ObjectMG::Clear()
{
	m_Chees.clear();
	m_Weapons.clear();
}

void ObjectMG::ClearChee()
{
	m_Chees.clear();
}

void ObjectMG::ClearWeapon()
{
	m_Weapons.clear();
}

bool ObjectMG::CheeEmpty()
{
	return m_Chees.empty();
}

bool ObjectMG::WeaponEmpty()
{
	return m_Chees.empty();
}

Chees::iterator ObjectMG::CheeVectorBegin()
{
	return m_Chees.begin();
}

Chees::iterator ObjectMG::CheeVectorEnd()
{
	return m_Chees.end();
}

Weapons::iterator ObjectMG::WeaponVectorBegin()
{
	return m_Weapons.begin();
}

Weapons::iterator ObjectMG::WeaponVectorEnd()
{
	return m_Weapons.end();
}

Chee* ObjectMG::GetClosestChee(const Vector3& pos )
{
	float d = 99999;
	Chee* c = NULL;
	for (Chees::iterator it = m_Chees.begin(); it != m_Chees.end();it++)
	{
		if((*it)->Position().distance(pos) < d)
		{
			d = (*it)->Position().distance(pos);
			c = (*it);
		}	
	}
	return c;
}

Chee* ObjectMG::GetClosestCheeFromFriend(const Vector3& pos,int team )
{
	float d = 99999;
	Chee* c = NULL;
	for (Chees::iterator it = m_Chees.begin(); it != m_Chees.end();it++)
	{
		if((*it)->Team()==0 || (*it)->Team() != team)
			continue;
		if((*it)->Position().distance(pos) < d)
		{
			d = (*it)->Position().distance(pos);
			c = (*it);
		}	
	}
	return c;
}

Chee* ObjectMG::GetClosestCheeFromEnemy(const Vector3& pos,int team )
{
	float d = 99999;
	Chee* c = NULL;
	for (Chees::iterator it = m_Chees.begin(); it != m_Chees.end();it++)
	{
		if((*it)->Team()!=0 && (*it)->Team() == team)
			continue;
		if((*it)->Position().distance(pos) < d)
		{
			d = (*it)->Position().distance(pos);
			c = (*it);
		}	
	}
	return c;
}

/*
Weapon* ObjectMG::GetClosestWeaponOnFloor(const Vector3& pos )
{

}

Weapon* ObjectMG::GetClosestThrownWeaponFromFriend(const Vector3& pos,int team )
{

}

Weapon* ObjectMG::GetClosestThrownWeaponFromEnemy(const Vector3& pos,int team )
{

}
*/

int ObjectMG::AmountChee()
{
	return m_Chees.size();
}

int ObjectMG::AmountWeapons()
{
	return m_Weapons.size();
}

void ObjectMG::Distory( Chee_RawPtr chee,int time/*=0*/ )
{
	if(!InCTrashCan(chee))
	{
		Chees::iterator it;
		for (it = m_Chees.begin(); it != m_Chees.end();it++)
		{
			if(*it == chee)
			{
				break;
			}
		}
		CTrash th;
		th.m_Trash=it;
		th.m_Time=time;
		m_CTrashCan.push_back(th);
	}
	
}

void ObjectMG::Distory( Weapon_RawPtr weapon,int time/*=0*/ )
{
	if (!InWTrashCan(weapon))
	{
		Weapons::iterator it;
		for (it = m_Weapons.begin(); it != m_Weapons.end();it++)
		{
			if(*it == weapon)
			{
				break;
			}
		}

		WTrash th;
		th.m_Trash=it;
		th.m_Time=time;
		m_WTrashCan.push_back(th);
	}
}

void ObjectMG::Distory( Chees::iterator it,int time/*=0*/ )
{
	if (!InCTrashCan(*it))
	{
		CTrash th;
		th.m_Trash=it;
		th.m_Time=time;
		m_CTrashCan.push_back(th);
	}
}

void ObjectMG::Distory( Weapons::iterator it,int time/*=0*/ )
{
	if(!InWTrashCan(*it)){
		WTrash th;
		th.m_Trash=it;
		th.m_Time=time;
		m_WTrashCan.push_back(th);
	}
}

void ObjectMG::CleanTrashCan()
{
	for (CTrashCan::iterator it=m_CTrashCan.begin();it != m_CTrashCan.end();)
	{
		
		if (it->m_Time <= 0)
		{
			delete(*(it->m_Trash));
			m_Chees.erase(it->m_Trash);
			it=m_CTrashCan.erase(it);

		}else{
			it->m_Time--;
			it++;
		}
	}

	for (WTrashCan::iterator it=m_WTrashCan.begin();it != m_WTrashCan.end();)
	{
		if (it->m_Time <= 0)
		{
			delete(*(it->m_Trash));
			m_Weapons.erase(it->m_Trash);
			it=m_WTrashCan.erase(it);
		}else{
			it->m_Time--;
			it++;
		}
	}
}

bool ObjectMG::InCTrashCan(Chee_RawPtr chee)
{
	for (CTrashCan::iterator it=m_CTrashCan.begin();it != m_CTrashCan.end();it++)
	{
		if(*(it->m_Trash) ==chee) 
				return true;
	}


	return false;
}

bool ObjectMG::InWTrashCan( Weapon_RawPtr weapon )
{
	for (WTrashCan::iterator it=m_WTrashCan.begin();it != m_WTrashCan.end();it++)
	{
		if(*(it->m_Trash) ==weapon) 
			return true;
	}


	return false;
}
