#pragma once
#define CONDITION_MAX_SIZE 20
#include <vector>

class ConditionClass
{
public:
	ConditionClass();
	void Add( const int effectIndex , const int time );
	void Update( float dt );
	bool IsEnable()
	{
		return m_Enable;
	}
	std::vector<int>& GetPresentConditionIndex();
private:
	
private:
	struct ConditionData
	{
		int m_effectIndex;
		int m_time;
	};typedef std::vector <ConditionData> ConditionDatas;

	bool m_Enable;
	std::vector<int> m_PresentCondition;
	ConditionDatas m_ConditionDatas;
};
typedef ConditionClass Condition;