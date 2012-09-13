#include "Tbox.h"

Tbox::Tbox()
{
	this->m_Scale = Vector3(0.1, 0.1, 0.0);
	this->m_Position = Vector3(-1.0, -1.0, 0.0);
	this->m_Direction = Vector3(rand()%100*0.005, rand()%100*0.005, 0.0);
	this->m_Color = Vector3(1.0, 0.0, 0.0);
/*
	this->m_Polygon2D.AddPoint(Vector2( m_Scale.x, m_Scale.y));
	this->m_Polygon2D.AddPoint(Vector2(-m_Scale.x, m_Scale.y));
	this->m_Polygon2D.AddPoint(Vector2(-m_Scale.x,-m_Scale.y));
	this->m_Polygon2D.AddPoint(Vector2( m_Scale.x,-m_Scale.y));
	this->m_Polygon2D.Offset(m_Position);*/
	RandomReset();
}

Tbox::Tbox( Vector3 pos )
{
	this->m_Scale = Vector3(0.6, 0.6, 0.0);
	this->m_Position = pos;
	this->m_Color = Vector3(0.0, 0.0, 1.0);
// 	this->m_Polygon2D.AddPoint(Vector2( m_Scale.x, m_Scale.y));
// 	this->m_Polygon2D.AddPoint(Vector2(-m_Scale.x, m_Scale.y));
// 	this->m_Polygon2D.AddPoint(Vector2(-m_Scale.x,-m_Scale.y));
// 	this->m_Polygon2D.AddPoint(Vector2( m_Scale.x,-m_Scale.y));
	RandomReset();
}

void Tbox::Update( float Gtime )
{
	m_Color = Vector3(1.0, 0.0, 0.0);
	Vector3 t_Vector3 = m_Direction * Gtime;
	m_Position += t_Vector3;
	m_Polygon2D.Offset(t_Vector3);
	
	if(m_Position.x > 1.0 && m_Direction.x > 0) m_Direction.x *= -1.0;
	else if(m_Position.x <-1.0 && m_Direction.x < 0) m_Direction.x *= -1.0;
	if(m_Position.y > 1.0 && m_Direction.y > 0) m_Direction.y *= -1.0;
	else if(m_Position.y <-1.0 && m_Direction.y < 0) m_Direction.y *= -1.0;
}

void Tbox::OnCollisionEnter()
{
	this->m_Color = Vector3(0.0, 1.0, 0.0);
}

void Tbox::RandomReset()
{
	this->m_Polygon2D.Clear();
	//this->m_Scale = Vector3(0.4, 0.4, 0.0);
	//this->m_Position = Vector3::ZERO;
	//this->m_Color = Vector3(0.0, 0.0, 1.0);
	int count = rand()%10+3;
	std::vector<float> RandomAngle;
	std::vector<float> RandomRadius;
	for(int i = 0; i < count; i++)
	{
		RandomAngle.push_back( float(rand()%360)*3.14/180.0 );
		RandomRadius.push_back( m_Scale.x*Random() );
	}
	std::sort(RandomAngle.begin(), RandomAngle.end());
	for(int i = 0; i < count; i++)
	{
		float t_x = sin(RandomAngle[i])*RandomRadius[i];
		float t_y = cos(RandomAngle[i])*RandomRadius[i];
		this->m_Polygon2D.AddPoint(Vector2(t_x, t_y));
		//this->m_Polygon2D.AddPoint(Vector2(2*m_Scale.x*Random()-m_Scale.x, 2*m_Scale.y*Random()-m_Scale.y));
	}
	this->m_Polygon2D.Offset(m_Position);
	this->m_Polygon2D.CheckBuildEdges();
}


