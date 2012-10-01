#include "CollisionFunction.h"

bool Collision_Attack_Body( const Attack& a, const Body& b )
{
	return a.m_Area.CollisionZ(b.m_Area) && a.m_Area.IsCollision(b.m_Area);
}

bool Collision_Attack_Bodys( const Attack& a, const Bodys& b )
{
	for (auto it = b.begin();it != b.end();++it)
	{
		if (Collision_Attack_Body(a, *it))
			return true;
	}
}

bool Collision_CatchInfo_Body( const CatchInfo& a, const Body& b )
{
	return a.m_Area.CollisionZ(b.m_Area) && a.m_Area.IsCollision(b.m_Area);
}

bool Collision_CatchInfo_Bodys( const CatchInfo& a, const Bodys& b )
{
	for (auto it = b.begin();it != b.end();++it)
	{
		if (Collision_CatchInfo_Body(a, *it))
			return true;
	}
}

bool Collision_Body_Attack( const Body& a, const Attack& b )
{
	return a.m_Area.CollisionZ(b.m_Area) && a.m_Area.IsCollision(b.m_Area);
}

bool Collision_Body_Attacks( const Body& a, const Attacks& b )
{
	for (auto it = b.begin();it != b.end();++it)
	{
		if (Collision_Body_Attack(a, *it))
			return true;
	}
}

bool Collision_Body_CatchInfo( const Body& a, const CatchInfo& b )
{
	return a.m_Area.CollisionZ(b.m_Area) && a.m_Area.IsCollision(b.m_Area);
}

bool Collision_Body_CatchInfos( const Body& a, const CatchInfos& b )
{
	for (auto it = b.begin();it != b.end();++it)
	{
		if (Collision_Body_CatchInfo(a, *it))
			return true;
	}
}
