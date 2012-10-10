#pragma once
#define CONDITION_MAX_SIZE 20
#include <vector>

class ConditionClass
{
public:
	ConditionClass();
	void Add( const int effectIndex , const int time );
	void Update( float dt );
	bool Test()
	{
		return m_Enable;
	}
private:
	struct ConditionData
	{
		int m_effectIndex;
		int m_time;
	};typedef std::vector <ConditionData> ConditionDatas;

	bool m_Enable;
	ConditionDatas m_ConditionDatas;
};
typedef ConditionClass Condition;
typedef std::vector <Condition> Conditions;