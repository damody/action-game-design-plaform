#pragma once
#include <string>
#include "game\Chee.h"
#include "game\Weapon.h"

class ObjectMG
{
public: 
	struct CTrash
	{
		Chees::iterator m_Trash;
		int m_Time;
	};
	typedef std::vector<CTrash> CTrashCan;

	struct WTrash
	{
		Weapons::iterator m_Trash;
		int m_Time;
	};
	typedef std::vector<WTrash> WTrashCan;
private:
	Chees   m_Chees;
	Weapons m_Weapons;

	CTrashCan m_CTrashCan;
	WTrashCan m_WTrashCan;
public:
	ObjectMG(void);
	~ObjectMG(void);

	void Update(float dt);
	void UpdateDataToDraw();

	Chee** CreateChee(const std::string& chee, const Vector3& pos, const Vector3& vel, int num=1, int team=0);
	Weapon** CreateWeapon(const std::string& weapon, const Vector3& pos, int num=1, int team=0);
	void Distory(Chee_RawPtr chee,int time=0);
	void Distory(Weapon_RawPtr weapon,int time=0);
	void Distory(Chees::iterator it,int time=0);
	void Distory(Weapons::iterator it,int time=0);
	void Clear();
	void ClearChee();
	void ClearWeapon();
	
	bool CheeEmpty();
	bool WeaponEmpty();
	int  AmountChee();
	int  AmountWeapons();
	Chees::iterator CheeVectorBegin();
	Chees::iterator CheeVectorEnd();
	Weapons::iterator WeaponVectorBegin();
	Weapons::iterator WeaponVectorEnd();

	Chee* GetClosestChee(const Vector3& pos);
	Chee* GetClosestCheeFromFriend(const Vector3& pos,int team);
	Chee* GetClosestCheeFromEnemy(const Vector3& pos,int team);

	Weapon* GetClosestWeaponOnFloor(const Vector3& pos);//Undo
	Weapon* GetClosestThrownWeaponFromFriend(const Vector3& pos,int team);//Undo
	Weapon* GetClosestThrownWeaponFromEnemy(const Vector3& pos,int team);//Undo

protected:
	void CleanTrashCan();
	bool InCTrashCan(Chee_RawPtr chee);
	bool InWTrashCan(Weapon_RawPtr weapon);
};

