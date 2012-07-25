#pragma once
#include <vector>
#include <map>
#include "HeroAction.h"
#include "Consume.h"
#include "math\Polygon2D.h"
#include "Attack.h"
#include "HitData.h"
#include "CatchInfo.h"
#include "BeCatch.h"
#include "BloodInfo.h"
#include "Body.h"

//�C�@�Ӱʧ@ Frame �ҧt����T
struct FrameInfo
{
	//�ʧ@���A
	HeroAction::e	m_HeroAction;
	//Frame Name
	std::string	m_FrameName;
	//Frame index of action
	int		m_FrameIndex;
	//Next Frame Name
	std::string	m_NextFrameName;
	//Next Frame index of action
	int		m_NextFrameIndex;
	//���Ū�J�Ϥ���id
	int	m_PictureID;
	//��ܹϤ��� x ��m
	int	m_PictureX;
	//��ܹϤ��� y ��m
	int	m_PictureY;
	//�H��X��V�����ץ��q
	float	m_CenterX;
	//�H��Y��V�����ץ��q
	float	m_CenterY;
	//���Ӹ�T
	Consume	m_Consume;
	//x��V���k�����ʥi��
	float	m_DVX;
	//y��V�W�U�����ʥi��
	float	m_DVY;
	//Z��V�W�U�����ʥi��
	float	m_DVZ;
	//�o�� Frame �����ơA�@��1/60��
	int	m_Wait;
	//�O�_�n�M�� KeyQueue �����
	bool	m_ClearKeyQueue;
	//����
	Bodys		m_Bodys;
	//�����P�w
	Attacks		m_Attacks;
	//���ۧP�w
	HitDatas	m_HitDatas;
	//��H�P�w
	CatchInfos	m_Catchs;
	//�Q��P�w
	BeCatch		m_BeCatch;
	//�y���T
	BloodInfos	m_BloodInfos;
};
typedef std::vector<FrameInfo> FrameInfos;
typedef std::map<std::string, FrameInfos> FramesMap;
