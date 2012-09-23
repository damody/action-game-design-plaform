#include "StdGame.h"
#include "HeroManager.h"
#include "global.h"

HeroManager::HeroManager( void )
{
}


HeroManager::~HeroManager( void )
{
}

void HeroManager::Update( float dt )
{
	CleanTrash();
	BodysCollision.PrepareForCollision();
	for ( Heroes::iterator it = m_Heroes.begin(); it != m_Heroes.end(); it++ )
	{
		( *it )->Update( dt );

		Heroes t_heros = BodysCollision.GetCollision(*it, GetPolygonsFromAttack());
		for(Heroes::iterator it_hero = t_heros.begin();
			it_hero != t_heros.end(); ++it_hero)
		{
			std::cout << "be hit" << std::endl;
			// do something....
		}
	}
}

void HeroManager::UpdateDataToDraw()
{
	for ( Heroes::iterator it = m_Heroes.begin(); it != m_Heroes.end(); it++ )
	{
		( *it )->UpdateDataToDraw();
	}

	std::stable_sort( m_Heroes.begin(), m_Heroes.end(), SortHero );
}

Hero* HeroManager::Create( const std::string& hero, const Vector3& pos, int team/*=0*/ )
{
	Hero_RawPtr h = Hero_RawPtr( new Hero( hero ) );
	h->SetPosition( pos );
	h->SetTeam( team );
	m_Heroes.push_back( h );
	BodysCollision.AddPtr(m_Heroes.back());
	AttacksCollision.AddPtr(m_Heroes.back());
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

int HeroManager::AmountEnemy( int team )
{
	int amount = 0;

	for ( Heroes::iterator it = m_Heroes.begin(); it != m_Heroes.end(); it++ )
	{
		if ( ( *it )->Team() != 0 && ( *it )->Team() == team )
		{
			continue;
		}

		amount++;
	}

	return amount;
}

Hero* HeroManager::GetClosestHero( const Vector3& pos )
{
	float d = 99999;
	Hero* h = NULL;

	for ( Heroes::iterator it = m_Heroes.begin(); it != m_Heroes.end(); it++ )
	{
		if ( ( *it )->Position().distance( pos ) < d )
		{
			d = ( *it )->Position().distance( pos );
			h = ( *it );
		}
	}

	return h;
}

Hero* HeroManager::GetClosestFriend( const Vector3& pos, int team )
{
	float d = 99999;
	Hero* h = NULL;

	for ( Heroes::iterator it = m_Heroes.begin(); it != m_Heroes.end(); it++ )
	{
		if ( ( *it )->Team() == 0 || ( *it )->Team() != team )
		{
			continue;
		}

		if ( ( *it )->Position().distance( pos ) < d )
		{
			d = ( *it )->Position().distance( pos );
			h = ( *it );
		}
	}

	return h;
}

Hero* HeroManager::GetClosestEnemy( const Vector3& pos, int team )
{
	float d = 99999;
	Hero* h = NULL;

	for ( Heroes::iterator it = m_Heroes.begin(); it != m_Heroes.end(); it++ )
	{
		if ( ( *it )->Team() != 0 && ( *it )->Team() == team )
		{
			continue;
		}

		if ( ( *it )->Position().distance( pos ) < d )
		{
			d = ( *it )->Position().distance( pos );
			h = ( *it );
		}
	}

	return h;
}

void HeroManager::Destory( Heroes::iterator it, int time/*=0*/ )
{
	if ( !InTrashCan( *it ) )
	{
		Trash th;
		th.m_Trash = *it;
		th.m_Time = time;
		m_TrashCan.push_back( th );
	}
}

void HeroManager::Destory( Hero_RawPtr hero, int time/*=0*/ )
{
	if ( !InTrashCan( hero ) )
	{
		Heroes::iterator it = GetHeroIt( hero );

		if ( it != m_Heroes.end() )
		{
			Trash th;
			th.m_Trash = hero;
			th.m_Time = time;
			m_TrashCan.push_back( th );
		}
	}
}

void HeroManager::CleanTrash()
{
	for ( TrashCan::iterator it = m_TrashCan.begin(); it != m_TrashCan.end() ; )
	{
		if ( it->m_Time <= 0 )
		{
			m_Heroes.erase( GetHeroIt( it->m_Trash ) );
			delete( it->m_Trash );
			it = m_TrashCan.erase( it );
		}
		else
		{
			it->m_Time--;
			it++;
		}
	}
}

bool HeroManager::InTrashCan( Hero_RawPtr hero )
{
	for ( TrashCan::iterator it = m_TrashCan.begin(); it != m_TrashCan.end(); it++ )
	{
		if (  it->m_Trash == hero )
		{
			return true;
		}
	}

	return false;
}

Heroes::iterator HeroManager::GetHeroIt( Hero* hero )
{
	Heroes::iterator it;

	for ( it = m_Heroes.begin(); it != m_Heroes.end(); it++ )
	{
		if ( *it == hero )
		{
			break;
		}
	}

	return it;
}






