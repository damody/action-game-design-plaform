#include "StdGame.h"
#include "Condition.h"
#include "game\Hero.h"

ConditionClass::ConditionClass( class Hero* hero , LuaCell_Sptr luadata )
{
	m_ConditionDatas.resize(CONDITION_MAX_SIZE);
	for( unsigned int idx = 0;idx < CONDITION_MAX_SIZE;idx++ )
	{
		m_ConditionDatas[idx].m_effectIndex = int(idx);
		m_ConditionDatas[idx].m_time = -1;
	}
	m_LuaCell = luadata;
	m_Hero = hero;
}

void ConditionClass::Add( const int effectIndex , const int time )
{
	m_ConditionDatas[effectIndex].m_effectIndex = effectIndex;
	m_ConditionDatas[effectIndex].m_time = time*60;
}

void ConditionClass::Update( float dt )
{
	m_Enable = false;
	if( !m_PresentCondition.empty() )
	{
		m_PresentCondition.clear();
	}
	for( unsigned int idx = 0; idx<CONDITION_MAX_SIZE ;idx++ )
	{
		//call Lua to do something

		//----------------------
		//time to remove it
		if( m_ConditionDatas[idx].m_time >= 0 )
		{
			m_Enable = true;
			m_PresentCondition.push_back(idx);
			luabind::call_function<int>(m_LuaCell->GetLuaState(), "ConditionUpdate",m_Hero,idx,m_ConditionDatas[idx].m_time);
			m_ConditionDatas[idx].m_time--;

		}else
		{
			m_ConditionDatas[idx].m_time = -1;
		}
	}
}

std::vector<int>& ConditionClass::GetPresentConditionIndex()
{
	return m_PresentCondition;
}
