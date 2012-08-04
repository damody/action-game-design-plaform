#pragma once
#include <string>
#include "game/Hero.h"

class HeroManager
{
private:
	Heroes m_Heroes;
public:
	HeroManager(void);
	~HeroManager(void);
	
	void Update(float dt);
	void UpdateDataToDraw();

	Hero* Create(const std::string& hero,const Vector3& pos,int team=0);
	void Delete(Hero_RawPtr hero);
	void Clear();
	void ClearDeadBody();//Undo

	bool Empty();
	int  AmountHeroes();
	int  AmountEnemy(int team);
	Heroes::iterator HeroVectorBegin();
	Heroes::iterator HeroVectorEnd();

	Hero* GetClosestHero(const Vector3& pos);
	Hero* GetClosestFriend(const Vector3& pos,int team);
	Hero* GetClosestEnemy(const Vector3& pos,int team);

};

