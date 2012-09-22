#include "StdGame.h"
#include "ObjectManager.h"


ObjectManager::ObjectManager( void )
{
	m_CTrashCan.clear();
	m_WTrashCan.clear();
}


ObjectManager::~ObjectManager( void )
{
}

void ObjectManager::Update( float dt )
{
	CleanTrashCan();

	for ( Chees::iterator it = m_Chees.begin(); it != m_Chees.end(); it++ )
	{
		( *it )->Update( dt );
	}

	for ( Weapons::iterator it = m_Weapons.begin(); it != m_Weapons.end(); it++ )
	{
		( *it )->Update( dt );
	}
}

void ObjectManager::UpdateDataToDraw()
{
	for ( Chees::iterator it = m_Chees.begin(); it != m_Chees.end(); it++ )
	{
		( *it )->UpdateDataToDraw();
	}

	std::stable_sort( m_Weapons.begin(), m_Weapons.end(), SortWeapon );

	for ( Weapons::iterator it = m_Weapons.begin(); it != m_Weapons.end(); it++ )
	{
		( *it )->UpdateDataToDraw();
	}
}

Chee** ObjectManager::CreateChee( const std::string& chee, const Vector3& pos, const Vector3& vel, int num/*=1*/, int team/*=0*/ )
{
	Chee_RawPtr* c = new Chee_RawPtr [num];

	for ( int i = 0; i < num; i++ )
	{
		c[i] = Chee_RawPtr( new Chee( chee ) );
		c[i]->SetPosition( pos );
		c[i]->SetVelocity( vel );
		c[i]->SetTeam( team );
		m_Chees.push_back( c[i] );
	}

	return c;
}

Weapon** ObjectManager::CreateWeapon( const std::string& weapon, const Vector3& pos, int num/*=1*/, int team/*=0*/ )
{
	Weapon_RawPtr* w = new Weapon_RawPtr [num];

	for ( int i = 0; i < num; i++ )
	{
		w[i] = Weapon_RawPtr( new Weapon( weapon ) );
		w[i]->SetPosition( pos );
		w[i]->SetTeam( team );
		m_Weapons.push_back( w[i] );
	}

	return w;
}

void ObjectManager::Clear()
{
	m_Chees.clear();
	m_Weapons.clear();
}

void ObjectManager::ClearChee()
{
	m_Chees.clear();
}

void ObjectManager::ClearWeapon()
{
	m_Weapons.clear();
}

bool ObjectManager::CheeEmpty()
{
	return m_Chees.empty();
}

bool ObjectManager::WeaponEmpty()
{
	return m_Weapons.empty();
}

Chees::iterator ObjectManager::CheeVectorBegin()
{
	return m_Chees.begin();
}

Chees::iterator ObjectManager::CheeVectorEnd()
{
	return m_Chees.end();
}

Weapons::iterator ObjectManager::WeaponVectorBegin()
{
	return m_Weapons.begin();
}

Weapons::iterator ObjectManager::WeaponVectorEnd()
{
	return m_Weapons.end();
}

Chee* ObjectManager::GetClosestChee( const Vector3& pos )
{
	float d = 99999;
	Chee* c = NULL;

	for ( Chees::iterator it = m_Chees.begin(); it != m_Chees.end(); it++ )
	{
		if ( ( *it )->Position().distance( pos ) < d )
		{
			d = ( *it )->Position().distance( pos );
			c = ( *it );
		}
	}

	return c;
}

Chee* ObjectManager::GetClosestCheeFromFriend( const Vector3& pos, int team )
{
	float d = 99999;
	Chee* c = NULL;

	for ( Chees::iterator it = m_Chees.begin(); it != m_Chees.end(); it++ )
	{
		if ( ( *it )->Team() == 0 || ( *it )->Team() != team )
		{
			continue;
		}

		if ( ( *it )->Position().distance( pos ) < d )
		{
			d = ( *it )->Position().distance( pos );
			c = ( *it );
		}
	}

	return c;
}

Chee* ObjectManager::GetClosestCheeFromEnemy( const Vector3& pos, int team )
{
	float d = 99999;
	Chee* c = NULL;

	for ( Chees::iterator it = m_Chees.begin(); it != m_Chees.end(); it++ )
	{
		if ( ( *it )->Team() != 0 && ( *it )->Team() == team )
		{
			continue;
		}

		if ( ( *it )->Position().distance( pos ) < d )
		{
			d = ( *it )->Position().distance( pos );
			c = ( *it );
		}
	}

	return c;
}

/*
Weapon* ObjectManager::GetClosestWeaponOnFloor(const Vector3& pos )
{

}

Weapon* ObjectManager::GetClosestThrownWeaponFromFriend(const Vector3& pos,int team )
{

}

Weapon* ObjectManager::GetClosestThrownWeaponFromEnemy(const Vector3& pos,int team )
{

}
*/

int ObjectManager::AmountChee()
{
	return m_Chees.size();
}

int ObjectManager::AmountWeapons()
{
	return m_Weapons.size();
}

void ObjectManager::Destory( Chee_RawPtr chee, int time/*=0*/ )
{
	if ( !InCTrashCan( chee ) )
	{
		Chees::iterator it = GetCheeIt( chee );

		if ( it != m_Chees.end() )
		{
			CTrash th;
			th.m_Trash = chee;
			th.m_Time = time;
			m_CTrashCan.push_back( th );
		}
	}
}

void ObjectManager::Destory( Weapon_RawPtr weapon, int time/*=0*/ )
{
	if ( !InWTrashCan( weapon ) )
	{
		Weapons::iterator it = GetWeaponIt( weapon );

		if ( it != m_Weapons.end() )
		{
			WTrash th;
			th.m_Trash = weapon;
			th.m_Time = time;
			m_WTrashCan.push_back( th );
		}
	}
}

void ObjectManager::Destory( Chees::iterator it, int time/*=0*/ )
{
	if ( !InCTrashCan( *it ) )
	{
		CTrash th;
		th.m_Trash = *it;
		th.m_Time = time;
		m_CTrashCan.push_back( th );
	}
}

void ObjectManager::Destory( Weapons::iterator it, int time/*=0*/ )
{
	if ( !InWTrashCan( *it ) )
	{
		WTrash th;
		th.m_Trash = *it;
		th.m_Time = time;
		m_WTrashCan.push_back( th );
	}
}

void ObjectManager::CleanTrashCan()
{
	for ( CTrashCan::iterator it = m_CTrashCan.begin(); it != m_CTrashCan.end(); )
	{
		if ( it->m_Time <= 0 )
		{
			m_Chees.erase( GetCheeIt( it->m_Trash ) );
			delete( it->m_Trash  );
			it = m_CTrashCan.erase( it );
		}
		else
		{
			it->m_Time--;
			it++;
		}
	}

	for ( WTrashCan::iterator it = m_WTrashCan.begin(); it != m_WTrashCan.end(); )
	{
		if ( it->m_Time <= 0 )
		{
			m_Weapons.erase( GetWeaponIt( it->m_Trash ) );
			delete( it->m_Trash );
			it = m_WTrashCan.erase( it );
		}
		else
		{
			it->m_Time--;
			it++;
		}
	}
}

bool ObjectManager::InCTrashCan( Chee_RawPtr chee )
{
	for ( CTrashCan::iterator it = m_CTrashCan.begin(); it != m_CTrashCan.end(); it++ )
	{
		if ( it->m_Trash == chee )
		{
			return true;
		}
	}

	return false;
}

bool ObjectManager::InWTrashCan( Weapon_RawPtr weapon )
{
	for ( WTrashCan::iterator it = m_WTrashCan.begin(); it != m_WTrashCan.end(); it++ )
	{
		if ( it->m_Trash == weapon )
		{
			return true;
		}
	}

	return false;
}

Chees::iterator ObjectManager::GetCheeIt( Chee* chee )
{
	Chees::iterator it;

	for ( it = m_Chees.begin(); it != m_Chees.end(); it++ )
	{
		if ( *it == chee )
		{
			break;
		}
	}

	return it;
}

Weapons::iterator ObjectManager::GetWeaponIt( Weapon* weapon )
{
	Weapons::iterator it;

	for ( it = m_Weapons.begin(); it != m_Weapons.end(); it++ )
	{
		if ( *it == weapon )
		{
			break;
		}
	}

	return it;
}
