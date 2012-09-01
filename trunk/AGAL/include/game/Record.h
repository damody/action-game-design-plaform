#pragma once

namespace boost{namespace serialization{class access;}}
struct Record
{
	int team;
	int Kill;    //殺敵數
	int Attack;  //攻擊
	int HPLost;  //損血量
	int MPUsage; //耗魔量
	int Picking; //拾起物品數目
	int Status; //1: win, -1: lose, 0:unknown

	Record():team(0),Kill(0),Attack(0),HPLost(0),MPUsage(0),Picking(0),Status(0)
	{}

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & Kill;    
		ar & Attack;  
		ar & HPLost;  
		ar & MPUsage; 
		ar & Picking; 
		ar & Status; 
	}
};
SHARE_PTR(Record)
