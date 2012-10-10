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
	for( ConditionDatas::iterator cIter = m_ConditionDatas.begin() ; cIter != m_ConditionDatas.end() ; ++cIter )
	{
		//call Lua to do something

		//----------------------
		//time to remove it
		if( cIter->m_time <= 0 )
		{
			cIter->m_time = 0;
		}else
		{
			m_Enable = true;
			cIter->m_time--;
		}
	}
}
