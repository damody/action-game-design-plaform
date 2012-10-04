#include "StdGame.h"
#include "ObjectManager.h"


ObjectManager::ObjectManager( void )
{
	m_TrashCan.clear();
}


ObjectManager::~ObjectManager( void )
{
}

void ObjectManager::Update( float dt )
{
	CleanTrashCan();

	for ( Objects::iterator it = m_Objects.begin(); it != m_Objects.end(); it++ )
	{
		( *it )->Update( dt );
	}
}

void ObjectManager::UpdateDataToDraw()
{
	for ( Objects::iterator it = m_Objects.begin(); it != m_Objects.end(); it++ )
	{
		( *it )->UpdateDataToDraw();
	}
}

Object** ObjectManager::CreateObject( const std::wstring& obj, const Vector3& pos, const Vector3& vel, int num/*=1*/, int team/*=0*/ )
{
	Object_RawPtr* object = new Object_RawPtr [num];

	for ( int i = 0; i < num; i++ )
	{
		object[i] = Object_RawPtr( new Object( obj ) );
		object[i]->SetPosition( pos );
		object[i]->SetVelocity( vel );
		object[i]->SetTeam( team );
		m_Objects.push_back( object[i] );
	}

	return object;
}

void ObjectManager::Clear()
{
	m_Objects.clear();
}

bool ObjectManager::ObjectEmpty()
{
	return m_Objects.empty();
}


Objects::iterator ObjectManager::ObjectVectorBegin()
{
	return m_Objects.begin();
}

Objects::iterator ObjectManager::ObjectVectorEnd()
{
	return m_Objects.end();
}

Object* ObjectManager::GetClosestChee( const Vector3& pos )
{
	float d = 99999;
	Object* c = NULL;

	for ( Objects::iterator it = m_Objects.begin(); it != m_Objects.end(); it++ )
	{
		if(( *it )->ObjectType()!=ObjectType::CHEE)continue;
		if ( ( *it )->Position().distance( pos ) < d )
		{
			d = ( *it )->Position().distance( pos );
			c = ( *it );
		}
	}

	return c;
}

Object* ObjectManager::GetClosestCheeFromFriend( const Vector3& pos, int team )
{
	float d = 99999;
	Object* c = NULL;

	for ( Objects::iterator it = m_Objects.begin(); it != m_Objects.end(); it++ )
	{
		if(( *it )->ObjectType()!=ObjectType::CHEE)continue;
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

Object* ObjectManager::GetClosestCheeFromEnemy( const Vector3& pos, int team )
{
	float d = 99999;
	Object* c = NULL;

	for ( Objects::iterator it = m_Objects.begin(); it != m_Objects.end(); it++ )
	{
		if(( *it )->ObjectType()!=ObjectType::CHEE)continue;
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
	int i=0,a=0;
	while(i < m_Objects.size())
	{
		if(m_Objects[i]->ObjectType()==ObjectType::CHEE)
		{a++;}
		i++;
	}
	return a;
}

void ObjectManager::Destory(  Object* obj, int time/*=0*/ )
{
	if ( !InTrashCan( obj ) )
	{
		Objects::iterator it = GetObjectIt( obj );

		if ( it != m_Objects.end() )
		{
			Trash th;
			th.m_Trash = obj;
			th.m_Time = time;
			m_TrashCan.push_back( th );
		}
	}
}

void ObjectManager::CleanTrashCan()
{
	for ( TrashCan::iterator it = m_TrashCan.begin(); it != m_TrashCan.end(); )
	{
		if ( it->m_Time <= 0 )
		{
			m_Objects.erase( GetObjectIt( it->m_Trash ) );
			delete( it->m_Trash  );
			it = m_TrashCan.erase( it );
		}
		else
		{
			it->m_Time--;
			it++;
		}
	}

}

bool ObjectManager::InTrashCan( Object* obj )
{
	for ( TrashCan::iterator it = m_TrashCan.begin(); it != m_TrashCan.end(); it++ )
	{
		if ( it->m_Trash == obj )
		{
			return true;
		}
	}

	return false;
}

Objects::iterator ObjectManager::GetObjectIt( Object* obj )
{
	Objects::iterator it;

	for ( it = m_Objects.begin(); it != m_Objects.end(); it++ )
	{
		if ( *it == obj )
		{
			break;
		}
	}

	return it;
}