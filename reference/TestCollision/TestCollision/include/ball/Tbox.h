#ifndef _TBOX_H_
#define _TBOX_H_
#include "math/Polygon2D.h"
#include "math/Vector3.h"


class Tbox
{
public:
	
	Vector3 m_Position;
	Vector3 m_Direction;
	Vector3 m_Scale;
	Vector3 m_Color;
	Polygon2D     m_Polygon2D;
public:
	Tbox();
	Tbox(Vector3 pos);
	void Update(float Gtime);
	void OnCollisionEnter();
	inline float Random()
	{
		int res;
		res = rand()%1000;
		return (float)res/1000.0;
	}
	void RandomReset();
};

typedef std::vector<Tbox*> Tboxs;

#endif // _TBOX_H_