#pragma once
#include <vector>
#include <map>
#include "LuaMap.h"
#include "Consume.h"
#include "math\Polygon2D.h"
#include "Attack.h"
#include "HitData.h"
#include "CatchInfo.h"
#include "BeCatch.h"
#include "BloodInfo.h"
#include "Body.h"
#include "Creation.h"
#include "EffectData.h"

namespace boost {namespace serialization {class access;}}
//�C�@�Ӱʧ@ Frame �ҧt����T
struct FrameInfo
{
	//�ʧ@���A
	int			m_HeroAction;
	//Frame Name
	std::string	m_FrameName;
	//Frame index of action
	int			m_FrameIndex;
	//Next Frame Name
	std::string	m_NextFrameName;
	//Next Frame index of action
	int			m_NextFrameIndex;
	//���Ū�J�Ϥ���id
	int			m_PictureID;
	//��ܹϤ��� x ��m
	int			m_PictureX;
	//��ܹϤ��� y ��m
	int			m_PictureY;
	//�H��X��V�����ץ��q
	float		m_CenterX;
	//�H��Y��V�����ץ��q
	float		m_CenterY;
	//���Ӹ�T
	Consume		m_Consume;
	//x��V���k�����ʥi��
	float		m_DVX;
	//y��V�W�U�����ʥi��
	float		m_DVY;
	//Z��V�W�U�����ʥi��
	float		m_DVZ;
	//�o�� Frame �����ơA�@��1/60��
	int			m_Wait;
	//�O�_�n�M�� KeyQueue �����
	int			m_ClearKeyQueue;
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
	//����гy
	Creations	m_Creations;
	//����
	std::string m_sound;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize( Archive& ar, const unsigned int version )
	{
		ar& 	m_HeroAction;
		ar& 	m_FrameName;
		ar& 	m_FrameIndex;
		ar& 	m_NextFrameName;
		ar& 	m_NextFrameIndex;
		ar& 	m_PictureID;
		ar& 	m_PictureX;
		ar& 	m_PictureY;
		ar& 	m_CenterX;
		ar& 	m_CenterY;
		ar& 	m_Consume;
		ar& 	m_DVX;
		ar& 	m_DVY;
		ar& 	m_DVZ;
		ar& 	m_Wait;
		ar& 	m_ClearKeyQueue;
		ar& 	m_Bodys;
		ar& 	m_Attacks;
		ar& 	m_HitDatas;
		ar& 	m_Catchs;
		ar& 	m_BeCatch;
		ar& 	m_BloodInfos;
		ar& 	m_Creations;
	}
};
typedef std::vector<FrameInfo> FrameInfos;
typedef std::map<std::string, FrameInfos> FramesMap;
