#pragma once
#include <vector>

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
};
typedef std::vector<Attack> Attacks;
