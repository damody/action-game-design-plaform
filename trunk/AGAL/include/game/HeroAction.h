#pragma once
#include <string>
#include <map>
#include "Lua/LuaCell.h"

class LuaMap : public std::map<std::string, int>
{
public:
	LuaMap(){}
	LuaMap(LuaCell_Sptr lsptr)
	{
		keys.clear();
		keys = lsptr->GetLuaTableKeys("Action");
		this->clear();
		for(int i=0; i<keys.size(); i++)
		{
			(*this)[keys[i]] = lsptr->GetLua<int>("Action/%s", keys[i].c_str());
		}
	}
	LuaMap(std::string path)
	{
		LuaCell_Sptr lsptr = LuaCell_Sptr( new LuaCell );
		lsptr->InputLuaFile(path.c_str());
		keys.clear();
		keys = lsptr->GetLuaTableKeys("Action");
		this->clear();
		for(int i=0; i<keys.size(); i++)
		{
			(*this)[keys[i]] = lsptr->GetLua<int>("Action/%s", keys[i].c_str());
		}
	}
	~LuaMap(){}

	strings GetKeys()
	{
		return keys;
	}
	void LoadHeroAction(LuaCell_Sptr lsptr)
	{
		keys.clear();
		keys = lsptr->GetLuaTableKeys("Action");
		this->clear();
		for(int i=0; i<keys.size(); i++)
		{
			(*this)[keys[i]] = lsptr->GetLua<int>("Action/%s", keys[i].c_str());
		}
	}
	void LoadHeroAction(std::string path)
	{
		LuaCell_Sptr lsptr = LuaCell_Sptr( new LuaCell );
		lsptr->InputLuaFile(path.c_str());
		keys.clear();
		keys = lsptr->GetLuaTableKeys("Action");
		this->clear();
		for(int i=0; i<keys.size(); i++)
		{
			(*this)[keys[i]] = lsptr->GetLua<int>("Action/%s", keys[i].c_str());
		}
	}
private:
	strings keys;
};
//typedef LuaMap HeroAction;

//���n���򥻰ʧ@�w�q
struct HeroAction
{
	enum e
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

	        //�w�Ƨ���
	        BEFORE_ATTACK,
	        //����
	        ATTACKING,
	        //����
	        AFTER_ATTACK,
	        //�w�Ʋ׵���
	        BEFORE_SUPER_ATTACK,
	        //�׵���
	        SUPER_ATTACKING,
	        //���׵���
	        AFTER_SUPER_ATTACK,
	        //�w�Ƹ���
	        BEFORE_JUMP_ATTACK,
	        //����
	        JUMP_ATTACKING,
	        //������
	        AFTER_JUMP_ATTACK,
	        //�w�ƶ]��
	        BEFORE_RUN_ATTACK,
	        //�]��
	        RUN_ATTACKING,
	        //���]��
	        AFTER_RUN_ATTACK,
	        //�w�ƽĸ���
	        BEFORE_DASH_ATTACK,
	        //�ĸ���
	        DASH_ATTACKING,
	        //���ĸ���
	        AFTER_DASH_ATTACK,
	        //��½
	        FLIP,
	        //�u
	        ROllING,

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
	        //���A��i�J�����A���v��|�o��V�W���t��
	        JUMP,
	        //�ĸ�
	        DASH,
	        //��
	        CROUCH,
	        //����
	        INJURED,
	        //�˦b�a�W
	        LYING,
	        //�Ť��A��V��i���ܭ����V
	        IN_THE_AIR,
	        //�w�Ʃ��
	        BEFORE_SKILL,
	        //����
	        AFTER_SKILL,
	        //�Ť����ۡA��V��L�ġA�L���O���|�ۦa
	        AIR_SKILL,
	        //���u�e�i���ۡAZ��V�䦳��
	        X_AXIS_SKILL,
	        //���u�e�i���ۡAX��V�䦳��
	        Z_AXIS_SKILL,
	        //�a�����ۡA��V��L��
	        GROUND_SKILL,
	        //�a�����N���ʵ��ۡA�|��V�䦳��
	        FREE_SKILL,

	        //�S���ۡA��V��L�ġA�i�H�P�a�B�L���O
	        UNIQUE_SKILL,
	        //�򥻰ʧ@������
	        BASIC_ACTION_END
	};
};

const std::string HeroActionTable[] =
{
	"Standing",
	"Walking",
	"Running",
	"StopRunning",
	"HeavyWeaponWalk",
	"HeavyWeaponRun",
	"LightWeaponStandAttack",
	"LightWeaponJumpAttack",
	"LightWeaponRunAttack",
	"LightWeaponDashAttack",
	"LightWeaponThrow",
	"HeavyWeaponThrow",
	"LightWeaponJumpThrow",
	"HeavyWeaponJumpThrow",
	"Drink",
	"BeforeAttack",
	"Attacking",
	"AfterAttack",
	"BeforeSuperAttack",
	"SuperAttacking",
	"AfterSuperAttack",
	"BeforeJumpAttack",
	"JumpAttacking",
	"AfterJumpAttack",
	"BeforeRunAttack",
	"RunAttacking",
	"AfterRunAttack",
	"BeforeDashAttack",
	"DashAttacking",
	"AfterDashAttack",
	"Flip",
	"Rolling",
	"Defend",
	"DefendPunch",
	"DefendKick",
	"Catching",
	"Caught",
	"Falling",
	"Jump",
	"Dash",
	"Crouch",
	"Injured",
	"Lying",
	"InTheAir",
	"BeforeSkill",
	"AfterSkill",
	"AirSkill",
	"XAxisSkill",
	"ZAxisSkill",
	"GroundSkill",
	"UniqueSkill",
	"BasicActionEnd"
};