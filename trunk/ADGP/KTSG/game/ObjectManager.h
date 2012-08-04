#pragma once
#include <string>
#include "game\Chee.h"
#include "game\Weapon.h"

class ObjectMG
{
private:
	Chees   m_Chees;
	Weapons m_Weapons;
public:
	ObjectMG(void);
	~ObjectMG(void);

	void Update(float dt);
	void UpdateDataToDraw();

	Chee** CreateChee(const std::string& chee, const Vector3& pos, const Vector3& vel, int num=1, int team=0);
	Weapon** CreateWeapon(const std::string& weapon, const Vector3& pos, int num=1, int team=0);
	void Delete(Chee_RawPtr chee);
	void Delete(Weapon_RawPtr weapon);
	void Delete(Chees::iterator it);
	void Delete(Weapons::iterator it);
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
};

