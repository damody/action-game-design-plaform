#pragma once
#include <vector>
#include <string>

struct Consume
{
	// 0 �ɥu��next���ΡA1 �ɥu�� hitdata����
	int	m_JumpRule;
	//�n���Ӫ� hp
	int	m_HP;
	//�n���Ӫ� mp
	int	m_MP;
	/*������ ���� m_EnoughFrameName ���� m_EnoughFrame ��
	std::string	m_EnoughFrameName;
	int		m_EnoughFrame;
	//�����ܪ����~�����*/
	//�������� ���� m_NotEnoughFrameName ���� m_NotEnoughFrame ��
	std::string	m_NotEnoughFrameName;
	int		m_NotEnoughFrame;
};
typedef std::vector<Consume> Consumes;
