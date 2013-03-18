#pragma once
#include <string>
#include "game\Object.h"

class ObjectManager
{
public:
	struct Trash
	{
		Object* m_Trash;
		int m_Time;
	};
	typedef std::vector<Trash> TrashCan;

private:
	Objects   m_Objects;

	TrashCan m_TrashCan;
public:
	ObjectManager( void );
	~ObjectManager( void );

	Objects GetChees();
	Objects GetObjects();

	void Update( float dt );
	void UpdateDataToDraw();

	Objects CreateObject( const std::wstring& obj, const Vector3& pos, const Vector3& vel, int num = 1, int team = 0 );

	void Destory( Object* obj, int time = 0 );
	void Clear();

	bool ObjectEmpty();
	int  Amount();
	int  AmountChee();
	
	Objects::iterator ObjectVectorBegin();
	Objects::iterator ObjectVectorEnd();

	Object* GetClosestChee( const Vector3& pos );
	Object* GetClosestCheeFromFriend( const Vector3& pos, int team );
	Object* GetClosestCheeFromEnemy( const Vector3& pos, int team );

	Object_Sptr GetClosestWeaponOnFloor( const Vector3& pos ); //Undo
	Object_Sptr GetClosestThrownWeaponFromFriend( const Vector3& pos, int team ); //Undo
	Object_Sptr GetClosestThrownWeaponFromEnemy( const Vector3& pos, int team ); //Undo

protected:
	void CleanTrashCan();
	bool InTrashCan( Object*  obj );
	Objects::iterator GetObjectIt( Object*  obj );
};

