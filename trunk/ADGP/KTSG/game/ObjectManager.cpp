#include "ObjectManager.h"


ObjectMG::ObjectMG(void)
{
}


ObjectMG::~ObjectMG(void)
{
}

void ObjectMG::Update( float dt )
{
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

	for (Weapons::iterator it = m_Weapons.begin(); it != m_Weapons.end();it++)
	{
		(*it)->UpdateDataToDraw();
	}
}

Chee** ObjectMG::CreateChee( std::string chee,Vector3 pos,Vector3 vel,int num/*=1*/,int team/*=0*/ )
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

Weapon** ObjectMG::CreateWeapon( std::string weapon,Vector3 pos,int num/*=1*/,int team/*=0*/ )
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

void ObjectMG::Delete( Chee_RawPtr chee )
{
	for (Chees::iterator it = m_Chees.begin();it != m_Chees.end();it++)
	{
		if((*it) ==chee)
			m_Chees.erase(it);
	}
}

void ObjectMG::Delete(Weapon_RawPtr weapon )
{
	for (Weapons::iterator it = m_Weapons.begin();it != m_Weapons.end();it++)
	{
		if((*it) ==weapon)
			m_Weapons.erase(it);
	}
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

Chee* ObjectMG::GetClosestChee( Vector3 pos )
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

Chee* ObjectMG::GetClosestCheeFromFriend( Vector3 pos,int team )
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

Chee* ObjectMG::GetClosestCheeFromEnemy( Vector3 pos,int team )
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

Weapon* ObjectMG::GetClosestWeaponOnFloor( Vector3 pos )
{

}

Weapon* ObjectMG::GetClosestThrownWeaponFromFriend( Vector3 pos,int team )
{

}

Weapon* ObjectMG::GetClosestThrownWeaponFromEnemy( Vector3 pos,int team )
{

}

int ObjectMG::AmountChee()
{
	return m_Chees.size();
}

int ObjectMG::AmountWeapons()
{
	return m_Weapons.size();
}
