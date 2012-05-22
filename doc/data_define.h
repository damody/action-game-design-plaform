#pragma once
#include <string>
#include <vector>
#include "Vector3.h"
#include "Polygon.h"

struct AttackType
{
	std::string m_Name;	//���������W
	size_t	m_TypeHash;	//�W�r�� Hash
	/*
	* Punsh ����
	* Knife �M
	* Fire  ��
	* Freeze �B
	* Burst  �z��
	*/
	float	m_HealablePercent;	//�i�Q�M¡���ʤ���
	std::string	m_ShaderName;	//�ϥΪ��S�Ĥ��W
};

//�C�@�ӧ����P�w�ҧt����T
struct Attack
{
	Polygon	m_Area;		//�d��
	int	m_Damage,	//�ˮ`
		m_FixDamage,	//����ˮ`
		m_Strength;	//�P�w�j��
	size_t	m_TypeHash;	//�ˮ`���� Hash �Ѧr�겣��
};
typedef std::vector<Attack> Attacks;

//�C�@�Ӱʧ@ Frame �ҧt����T
struct FrameInfo
{
	int	m_OffsetX,	//�H��X��V�����ץ��q
		m_OffsetY,	//�H��Y��V�����ץ��q
		m_ConsumeMP,	//����MP
		m_ConsumeHP,	//����HP
		m_ZMove,	//�W�U�����ʥi��
		m_Defend;	//�o�Ӱʧ@�����m�O
	float	m_FrameTime;	//�o�� Frame ���檺�ɶ�
	Vector3	m_Acceleration,	//�[�t��
		m_FixMove;	//�T�w���ʶq
	Polygons	m_Bodys;	//����
	Attacks		
};

//�C�@�쪱�a�ҭn�O������T
struct PlayerRecord{
	std::string	m_Name;	//���a�W��
	int	m_KilledSum,	//���H��
		m_AttackSum,	//�`�ˮ`
		m_HPLostSum,	//�`����q
		m_MPUsageSum,	//�`MP�ϥζq
		m_HealSum,	//�`�^��q
		m_Picking;	//�`�ߪ��~��
	bool	m_Win;		//���S��Ĺ
};

//�C�@�ӭ^���ݭn�Ψ쪺��T
struct HeroInfo
{
	//���n���򥻰ʧ@�w�q
	enum Action
	{
		STANDING,		//����
		WALKING,		//����
		RUNNING,		//�]�B
		STOP_RUNNING,		//����]�B
		HEAVY_WEAPON_WALK,	//�t���樫
		HEAVY_WEAPON_RUN,	//�t���]�B
		LIGHT_WEAPON_STAND_ATTACK,	//���Z������
		LIGHT_WEAPON_JUMP_ATTACK,	//���Z������
		LIGHT_WEAPON_RUN_ATTACK,	//���Z���]��
		LIGHT_WEAPON_DASH_ATTACK,	//���Z���ħ�
		LIGHT_WEAPON_THROW,		//���Z����X
		HEAVY_WEAPON_THROW,		//���Z����X
		LIGHT_WEAPON_JUMP_THROW,	//���Z�����_�ɥ�X
		HEAVY_WEAPON_JUMP_THROW,	//���Z�����_�ɥ�X
		DRINK,			//�ܶ���
		LIGHT_PUNCH,		//����
		LIGHT_KICK,		//���}
		HEAVY_PUNCH,		//����
		HEAVY_KICK,		//���}
		SUPER_PUNCH,		//�׵���
		SUPER_PUNCH,		//�׵��}
		JUMP_PUNCH,		//����
		JUMP_KICK,		//���}
		RUN_PUNCH,		//�]��
		RUN_KICK,		//�]�}
		FORWARD_FLY_ROWING,	//�e��½
		BACKWARD_FLY_ROWING,	//���½
		FORWARD_ROWING,		//�e�u
		BACKWARD_ROWING,	//��u
		DEFEND,			//���m
		DEFEND_PUNCH,		//������
		DEFEND_KICK,		//�����}
		CATCHING,		//��H
		CAUGHT,			//�Q��
		FALLING,		//�^��
		JUMP,			//��
		CROUCH,			//��
		INJURED,		//����
		FORWARD_LYING,		//�w�b�a�W
		BACKWARD_LYING,		//���b�a�W
		BASIC_ACTION_END	//�򥻰ʧ@������
	};
	std::string	m_Name;		//�H���W��
	Action		m_Status;
	int		m_MP,		//�ثe�]�q
			m_Visable,	//-1:invisible 0:flash 1:visible
			m_MaxMP,	//�̤j�]�q
			m_HP,		//�ثe��q
			m_MaxHP,	//�̤j��q
			m_Shield,	//�ثe�@�ޭ�
			m_Fall,		//���˭ȡA�|�v�T�i�_�¨�
			m_MaxFall,	//�̤j���˭�
			m_Defend,	//���m��
			m_MaxDefend,	//�̤j���m��
			m_Alive,	//����O�_�٬���
			m_Life,		//�ثe�ѤU���X���R
			m_PhysicsDefense,	//���z���m�O
			m_MagicDefense;		//�]�k���m�O
	float		m_RemainTime,	//�ثeframe�ٳѤU���ɶ�
			m_FlashTime,	//�{�{�ɶ�
			m_InvincibleTime,	//�L�Įɶ�
			m_InvisibleTime,	//���ήɶ�
			m_AntiPhysicsPercent,	//���z���
			m_AntiPhysicsPercent,	//���z���%��
			m_AntiMagicPercent,	//�]�k���
			m_AntiMagicPercent;	//�]�k���%��
};

