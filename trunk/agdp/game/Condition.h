#pragma once
#define CONDITION_MAX_SIZE 20
#include <vector>
#include "Lua/LuaCell.h"

class ConditionClass
{
public:
	ConditionClass( class Hero* hero , LuaCell_Sptr luadata );
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
	};
	typedef std::vector <ConditionData> ConditionDatas;

	bool m_Enable;
	std::vector<int> m_PresentCondition;
	ConditionDatas m_ConditionDatas;
	LuaCell_Sptr m_LuaCell;
	class Hero* m_Hero;//一個狀態綁定一個Hero
};
typedef ConditionClass Condition;