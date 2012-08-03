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

	Chee* CreateChee(std::string chee,Vector3 pos,int num=1,int team=0);
	Weapon* CreateWeapon(std::string weapon,Vector3 pos,int num=1,int team=0);
	void Delete(Chee_RawPtr hero);
	void Delete(Weapons hero);
	void Clear();
	void ClearChee();
	void ClearWeapon();
	

	bool CheeEmpty();
	bool WeaponEmpty();
	Chees::iterator CheeVectorBegin();
	Chees::iterator CheeVectorEnd();
	Weapons::iterator WeaponVectorBegin();
	Weapons::iterator WeaponVectorEnd();

	Chee* GetClosestChee(Vector3 pos);
	Chee* GetClosestCheeFromFriend(Vector3 pos,int team);
	Chee* GetClosestCheeFromEnemy(Vector3 pos,int team);

	Weapon* GetClosestWeaponOnFloor(Vector3 pos);
	Weapon* GetClosestThrownWeaponFromFriend(Vector3 pos,int team);
	Weapon* GetClosestThrownWeaponFromEnemy(Vector3 pos,int team);
};

