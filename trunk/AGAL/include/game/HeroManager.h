#pragma once
#include <string>
#include "game/Hero.h"

class HeroManager
{
public: 
	struct Trash
	{
		Heroes::iterator m_Trash;
		int m_Time;
	};
	typedef std::vector<Trash> TrashCan;
private:
	Heroes m_Heroes;
	TrashCan m_TrashCan;
public:
	HeroManager(void);
	~HeroManager(void);
	
	void Update(float dt);
	void UpdateDataToDraw();

	Hero* Create(const std::string& hero,const Vector3& pos,int team=0);
	void Distory(Heroes::iterator it,int time=0);
	void Distory(Hero_RawPtr hero,int time=0);
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

protected:
	void CleanTrash();
	bool InTrashCan(Hero_RawPtr hero);
};

