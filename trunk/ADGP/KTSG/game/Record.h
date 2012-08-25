#pragma once

namespace boost{namespace serialization{class access;}}
struct Record
{
	int team;
	int Kill;    //���ļ�
	int Attack;  //����
	int HPLost;  //�l��q
	int MPUsage; //���]�q
	int Picking; //�B�_���~�ƥ�
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
