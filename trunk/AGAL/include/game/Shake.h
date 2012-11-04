#ifndef _SHAKE_H_
#define _SHAKE_H_
#pragma once

#include "math\Vector3.h"

struct ShakeControl
{
	int Group;
	Vector3 Direction;
	bool Enable;
	bool Loop;
	bool EnableSmooth;
	bool EnableDiminuendo; // º¥±j need LifeCycle != 0
	bool EnableCrescendo; // º¥®z need LifeCycle != 0
	float StartTime;
	float LifeCycle; 
	float Frequency;  // Hz
	float AutoDestory;
};

typedef std::vector<ShakeControl> ShakeControls;

class Shake
{
public:
	Shake(void);
	~Shake(void);
	const Vector3& GetOffset() {return m_Offset;}
	int Add(int Group, Vector3 Direction, float Frequency, bool Loop = true, bool EnableDiminuendo = false, bool EnableCrescendo = false, float LifeCycle = 0.0f, bool EnableSmooth = true, float AutoDestory = 0.0f );
	void Remove( int Group );
	void Pause() {m_EnableShake = false;}
	void Pause( int Group );
	void Resume() {m_EnableShake = true;}
	void Resume( int Group );
	void Stop( int Group ) ;
	void Update( float deltaTime );
protected:
	void MakeShake( ShakeControl& SC, float deltaTime );
private:
	Vector3 m_Offset;
	bool m_EnableShake;
	ShakeControls m_ShakeControls;
};

#endif // _SHAKE_H_