#pragma once

#include "math\Vector3.h"
#include "path\HSplineCurve.h"

struct OffsetControl
{
	int Group;
	Vector3 Direction;
	bool Enable;
	bool Loop;
	bool EnableSmooth;
	HsplineCurve Intensity;
	float StartTime;
	float LifeTime; 
	float Frequency;  // Hz
	bool AutoDestory;

	OffsetControl():StartTime(0),Enable(true){}
	void Init(){StartTime=0;Enable=true;}
};
typedef std::vector<OffsetControl> OffsetControls;

class OffsetCalculate
{
public:
	OffsetCalculate(void);
	~OffsetCalculate(void);
	
	const Vector3& GetOffset() {return m_Offset;}
	int Add(int Group, Vector3 Direction, float Frequency, double Intensity, float LifeTime, bool EnableDiminuendo = false, bool EnableCrescendo = false, bool Loop = true, bool EnableSmooth = true, bool AutoDestory = true );
	void Remove( int Group );
	void Pause() {m_Enable = false;}
	void Pause( int Group );
	void Resume() {m_Enable = true;}
	void Resume( int Group );
	void Stop( int Group ) ;
	void Update( float deltaTime );
protected:
	virtual void Calculate( OffsetControl& SC, float deltaTime ) = 0;
protected:
	Vector3 m_Offset;
	bool	m_Enable;
	OffsetControls m_OffsetControls;
};

