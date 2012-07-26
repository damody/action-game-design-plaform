#pragma once
#include <vector>
#include <string>
namespace boost{namespace serialization{class access;}}
struct Consume
{
	// 0 時只對next有用，1 時只對 hitdata有用
	int	m_JumpRule;
	//要消耗的 hp
	int	m_HP;
	//要消耗的 mp
	int	m_MP;
	/*夠的話 跳到 m_EnoughFrameName 的第 m_EnoughFrame 格
	std::string	m_EnoughFrameName;
	int		m_EnoughFrame;
	//夠的話直接繼續執行*/
	//不夠的話 跳到 m_NotEnoughFrameName 的第 m_NotEnoughFrame 格
	std::string	m_NotEnoughFrameName;
	int		m_NotEnoughFrame;


	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar &	m_JumpRule;
		ar &	m_HP;
		ar &	m_MP;
		ar &	m_NotEnoughFrameName;
		ar &	m_NotEnoughFrame;
	}
};
typedef std::vector<Consume> Consumes;
