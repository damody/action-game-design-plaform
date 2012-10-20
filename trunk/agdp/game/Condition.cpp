#include "StdGame.h"
#include "Condition.h"

ConditionClass::ConditionClass()
{
	m_ConditionDatas.resize(CONDITION_MAX_SIZE);
	for( unsigned int idx = 0;idx < CONDITION_MAX_SIZE;idx++ )
	{
		m_ConditionDatas[idx].m_effectIndex = int(idx);
		m_ConditionDatas[idx].m_time = 0;
	}
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
		if( m_ConditionDatas[idx].m_time > 0 )
		{
			m_Enable = true;
			m_PresentCondition.push_back(idx);
			m_ConditionDatas[idx].m_time--;
		}else
		{
			m_ConditionDatas[idx].m_time = 0;
		}
	}
}

std::vector<int>& ConditionClass::GetPresentConditionIndex()
{
	return m_PresentCondition;
}
