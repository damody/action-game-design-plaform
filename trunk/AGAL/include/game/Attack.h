#pragma once
#include <vector>
#include "math\Polygon2D.h"

namespace boost {namespace serialization {class access;}}
//�C�@�ӧ����P�w�ҧt����T
struct Attack
{

	//�d��
	Polygon2D m_Area;
	//�ˮ`
	int	m_Injury;
	//�P�w�j��
	int	m_Strength;
	//�ˮ`����
	int	m_Kind;
	//�ˮ`�ĪG
	int	m_Effect;
	//������ x ��V���k������
	float	m_DVX;
	//������ y ��V�W�U������
	float	m_DVY;
	//������ z ��V�W�U������
	float	m_DVZ;
	//Z��V���e��
	float	m_ZWidth;
	//���˭�
	int	m_Fall;
	//�}����
	int	m_BreakDefend;
	//�������y���
	int	m_AttackRest;
	//�A�������
	int	m_ReAttackRest;


	friend class boost::serialization::access;
	template<class Archive>
	void serialize( Archive& ar, const unsigned int version )
	{
		ar& m_Area;
		ar& m_Injury;
		ar& m_Strength;
		ar& m_Kind;
		ar& m_Effect;
		ar& m_DVX;
		ar& m_DVY;
		ar& m_DVZ;
		ar& m_ZWidth;
		ar& m_Fall;
		ar& m_BreakDefend;
		ar& m_AttackRest;
		ar& m_ReAttackRest;
	}
};
typedef std::vector<Attack> Attacks;

const std::string effectTable[] =
{
	"Fire",
	"BlackFire",
	"PurpleFire",
	"Freeze",
	"IceSlow",
	"Punch",
	"Knife",
	"Thunder",
	"Palsy",
	"Faint",
	"End"
};