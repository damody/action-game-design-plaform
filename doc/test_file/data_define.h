#pragma once
#include <string>
#include <vector>
#include <cstdlib>
#include "math/Vector3.h"
#include "math/Polygon2D.h"
#include <deque>

class Hero;

//��������
struct AttackType
{
	//���������W��
	//Punsh ����
	//Knife �M
	//Fire  ��
	//Freeze �B
	//Burst  �z��
	std::string m_Name;
	//�W�r�� Hash
	size_t	m_TypeHash;
	//�i�Q�M¡���ʤ���
	float	m_HealablePercent;
	//�ϥΪ��S�Ĥ��W
	std::string	m_ShaderName;
};

//�������A�޲z��
class AttackTypeManager
{
public:
	//���U�s�������A�A�^�ǲ��ͪ� hash ��
	size_t RegisterAttackType(const AttackType &);
	//�� hash �ȡA����Ӫ��������A
	const AttackType& FindAttackType(size_t hash);
};


//�C�@�ӧ����P�w�ҧt����T
struct Attack
{
	//������m
	Vector3	m_Position;
	//�d��
	Polygon2D m_Area;
	//Z��V���e��
	int	m_ZWidth;
	//�ˮ`
	int	m_Damage;
	//����ˮ`
	int	m_FixDamage;
	//�P�w�j��
	int	m_Strength;
	//�ˮ`���� Hash �Ѧr�겣��
	size_t	m_TypeHash;
};
typedef std::vector<Attack> Attacks;


//���n���򥻰ʧ@�w�q
enum HeroAction
{
	//����
	STANDING,
	//����
	WALKING,
	//�]�B
	RUNNING,
	//����]�B
	STOP_RUNNING,
	//�t���樫
	HEAVY_WEAPON_WALK,
	//�t���]�B
	HEAVY_WEAPON_RUN,
	//���Z������
	LIGHT_WEAPON_STAND_ATTACK,
	//���Z������
	LIGHT_WEAPON_JUMP_ATTACK,
	//���Z���]��
	LIGHT_WEAPON_RUN_ATTACK,
	//���Z���ħ�
	LIGHT_WEAPON_DASH_ATTACK,
	//���Z����X
	LIGHT_WEAPON_THROW,
	//���Z����X
	HEAVY_WEAPON_THROW,
	//���Z�����_�ɥ�X
	LIGHT_WEAPON_JUMP_THROW,
	//���Z�����_�ɥ�X
	HEAVY_WEAPON_JUMP_THROW,
	//�ܶ���
	DRINK,
	//����
	LIGHT_PUNCH,
	//���}
	LIGHT_KICK,
	//����
	HEAVY_PUNCH,
	//���}
	HEAVY_KICK,
	//�׵���
	SUPER_PUNCH,
	//�׵��}
	SUPER_KICK,
	//����
	JUMP_PUNCH,
	//���}
	JUMP_KICK,
	//�]��
	RUN_PUNCH,
	//�]�}
	RUN_KICK,
	//�e��½
	FORWARD_FLY_ROWING,
	//���½
	BACKWARD_FLY_ROWING,
	//�e�u
	FORWARD_ROWING,
	//��u
	BACKWARD_ROWING,
	//���m
	DEFEND,
	//������
	DEFEND_PUNCH,
	//�����}
	DEFEND_KICK,
	//��H
	CATCHING,
	//�Q��
	CAUGHT,
	//�^��
	FALLING,
	//��
	JUMP,
	//��
	CROUCH,
	//����
	INJURED,
	//�w�b�a�W
	FORWARD_LYING,
	//���b�a�W
	BACKWARD_LYING,
	//�񵴩�
	UNIQUE_SKILL,
	//�򥻰ʧ@������
	BASIC_ACTION_END
};


//�C�@�Ӱʧ@ Frame �ҧt����T
struct FrameInfo
{
	//�ʧ@���A
	HeroAction m_HeroAction;
	//Frame index of all
	int	m_FrameIndex;
	//�H��X��V�����ץ��q
	int	m_OffsetX;
	//�H��Y��V�����ץ��q
	int	m_OffsetY;
	//����MP
	int	m_ConsumeMP;
	//����HP
	int	m_ConsumeHP;
	//�W�U�����ʥi��
	int	m_ZMoveable;
	//�o�Ӱʧ@�����m�O
	int	m_Defend;
	//�o�� Frame ���檺�ɶ�
	float	m_FrameTime;
	//�[�t��
	Vector3	m_Acceleration;
	//�T�w���ʶq
	Vector3	m_FixMove;
	//����
	Polygon2Ds	m_Bodys;
	//�����P�w
	Attacks		m_Attacks;
};


//�C�@�쪱�a�ҭn�O������T
struct PlayerRecord
{
	//���a�W��
	std::string	m_Name;
	//���H��
	int	m_KilledSum;
	//�`�ˮ`
	int	m_AttackSum;
	//�`����q
	int	m_HPLostSum;
	//�`MP�ϥζq
	int	m_MPUsageSum;
	//�`�^��q
	int	m_HealSum;
	//�`�ߪ��~��
	int	m_Picking;
	//���S��Ĺ
	bool	m_Win;
};


//�C�@�ӭ^���ݭn�Ψ쪺��T
struct HeroInfo
{
	//�H���W��
	std::string	m_Name;
	//�ثe�ʧ@���A
	HeroAction	m_Status;
	//�ثe�]�q
	int		m_MP;
	//-1:invisible 0:flash 1:visible
	int		m_Visable;
	//�̤j�]�q
	int		m_MaxMP;
	//�ثe��q
	int		m_HP;
	//�̤j��q
	int		m_MaxHP;
	//�ثe�@�ޭ�
	int		m_Shield;
	//���˭ȡA�|�v�T�i�_�¨�
	int		m_Fall;
	//�̤j���˭�
	int		m_MaxFall;
	//���m��
	int		m_Defend;
	//�̤j���m��
	int		m_MaxDefend;
	//����O�_�٬���
	int		m_Alive;
	//�ثe�ѤU���X���R
	int		m_Life;
	//���z���m�O
	int		m_PhysicsDefense;
	//�]�k���m�O
	int		m_MagicDefense;
	//�ثeframe�ٳѤU���ɶ�
	float		m_RemainTime;
	//�{�{�ɶ�
	float		m_FlashTime;
	//�L�Įɶ�
	float		m_InvincibleTime;
	//���ήɶ�
	float		m_InvisibleTime;
	//���z���
	float		m_AntiPhysics;
	//���z���%��
	float		m_AntiPhysicsPercent;
	//�]�k���
	float		m_AntiMagic;
	//�]�k���%��
	float		m_AntiMagicPercent;
	// false:Right true:Left
	bool		m_FaceSide;
};


//����̡A�O���U���䪺����
class Controller
{
public:
	// ����̫��U����
	virtual void PutKey(Hero* hero) = 0;
	virtual ~Controller(){}
};


class AI : public Controller
{
public:
	// AI ���U����
	virtual void PushKey(Hero* hero);
	virtual ~AI();
};


struct InputKey
{
	enum ActionKey
	{
		UP,
		DOWN,
		RIGHT,
		LEFT,
		ATTACK1,
		ATTACK2,
		ATTACK3,
		ATTACK4,
		JUMP,
		DEFINED,
		NONE
	};
	//���U�h������
	float m_Time;
	//�N���ʧ@
	ActionKey	m_Key;
};
typedef std::deque<InputKey> InputKeys;

class Player : public Controller
{
public:
	// ���a���U����
	virtual void PushKey(Hero* hero);
	virtual ~Player();
	void	SetKeyMapping(char key, InputKey::ActionKey value);
	void	GetUserInput();
};

class Hero
{
protected:
	//�ثe�� Frame �ٳѤU�h�֮ɶ�
	float	m_FrameTime;
	//�ثe�� Frame index
	int	m_CurrentFrame;
	//�^������T�A�ѩ�^����T�`�`�ݭn�ǨӶǥh�ҥH�Ϋ���
	HeroInfo	*m_HeroInfo;
	//��J���C
	InputKeys	m_InputKeys;
};
typedef std::list<Hero> Herolist;

class FighterSceneManager
{
	
};

