#include "Object.h"
#include "global.h"

#define SCALE 3.0f


//* 碰撞判定用函示
Polygon2Ds GetObjectBodys(const Object& r)
{
	Polygon2Ds d;

	for(Bodys::iterator ib = r.m_FrameInfo->m_Bodys.begin(); ib != r.m_FrameInfo->m_Bodys.end(); ib++)
	{
		Polygon2D s;

		if(!ib->m_Area.Points().empty())
		{
			for(auto iv = ib->m_Area.Points().begin(); iv != ib->m_Area.Points().end(); iv++)
			{
				if(r.m_FaceSide)     //面向右邊
				{
					s.AddPoint(r.m_Position.x - (r.m_CenterX - iv->x()) * SCALE, r.m_Position.y + (r.m_CenterY + iv->y()) * SCALE);
				}
				else                //面向左邊
				{
					s.AddPoint(r.m_Position.x + (r.m_CenterX - iv->x()) * SCALE, r.m_Position.y + (r.m_CenterY + iv->y()) * SCALE);
				}
			}
		}

		s.SetZPoint(r.m_Position.z);
		s.SetZRange(ib->m_ZWidth);
		d.push_back(s);
	}

	return d;
}

Polygon2Ds GetObjectAttacks(const Object& r)
{
	Polygon2Ds d;

	for(Attacks::iterator ib = r.m_FrameInfo->m_Attacks.begin(); ib != r.m_FrameInfo->m_Attacks.end(); ib++)
	{
		Polygon2D s;

		for(auto iv = ib->m_Area.Points().begin(); iv != ib->m_Area.Points().end(); iv++)
		{
			if(r.m_FaceSide)     //面向右邊
			{
				s.AddPoint(r.m_Position.x - (r.m_CenterX - iv->x()) * SCALE, r.m_Position.y + (r.m_CenterY + iv->y()) * SCALE);
			}
			else                //面向左邊
			{
				s.AddPoint(r.m_Position.x + (r.m_CenterX - iv->x()) * SCALE, r.m_Position.y + (r.m_CenterY + iv->y()) * SCALE);
			}
		}

		s.SetZPoint(r.m_Position.z);
		s.SetZRange(ib->m_ZWidth);
		d.push_back(s);
	}

	return d;
}

Polygon2Ds GetObjectCatches(const Object& r)
{
	Polygon2Ds d;

	for(CatchInfos::iterator ib = r.m_FrameInfo->m_Catchs.begin(); ib != r.m_FrameInfo->m_Catchs.end(); ib++)
	{
		Polygon2D s;

		for(auto iv = ib->m_Area.Points().begin(); iv != ib->m_Area.Points().end(); iv++)
		{
			if(r.m_FaceSide)     //面向右邊
			{
				s.AddPoint(r.m_Position.x - (r.m_CenterX - iv->x()) * SCALE, r.m_Position.y + (r.m_CenterY + iv->y()) * SCALE);
			}
			else                //面向左邊
			{
				s.AddPoint(r.m_Position.x + (r.m_CenterX - iv->x()) * SCALE, r.m_Position.y + (r.m_CenterY + iv->y()) * SCALE);
			}
		}

		s.SetZPoint(r.m_Position.z);
		s.SetZRange(ib->m_ZWidth);
		d.push_back(s);
	}

	return d;
}
Object::Object(void)
{
}

Object::Object(std::wstring obj):
    m_ObjectName(obj), m_Position(Vector3(0, 0, 0)), m_Vel(Vector3(0, 0, 0)), m_Team(0), m_FaceSide(true), m_FrameID(0), m_Texture(0), m_PicID(0), m_PicW(0), m_PicH(0), m_PicX(0), m_PicY(0)
{
    m_ObjectInfo = g_ObjectInfoManager.GetObjectInfo(m_ObjectName);

    if(m_ObjectInfo.get())
    {
        this->Init();
    }
    else
    {
        std::wcout << L"Cannot find " << obj << std::endl;
    }
}


Object::~Object(void)
{
}

void Object::Init()
{
    m_Angle = 0;
    m_HP = m_ObjectInfo->m_MaxHP;
    m_Frame = L"default";
    m_FrameID = 0;
    FrameInfo* f = &m_ObjectInfo->m_FramesMap[m_Frame][m_FrameID];
	m_FrameInfo = f;
    m_PicID = f->m_PictureID;
    m_PicX = f->m_PictureX;
    m_PicY = f->m_PictureY;
    m_PicW = m_ObjectInfo->m_PictureDatas[m_PicID].m_Column;
    m_PicH = m_ObjectInfo->m_PictureDatas[m_PicID].m_Row;
    m_Texture = m_ObjectInfo->m_PictureDatas[m_PicID].m_TextureID;
    m_Action = f->m_HeroAction;
    m_TimeTik = f->m_Wait;
    m_CenterX = f->m_CenterX;
    m_CenterY = f->m_CenterY;
}


void Object::NextFrame()
{
    FrameInfo* f = &m_ObjectInfo->m_FramesMap[m_Frame][m_FrameID];
	m_FrameInfo = f;
    m_Frame = f->m_NextFrameName;
    m_FrameID = f->m_NextFrameIndex;
    f = &m_ObjectInfo->m_FramesMap[m_Frame][m_FrameID];
    m_PicID = f->m_PictureID;
    m_PicX = f->m_PictureX;
    m_PicY = f->m_PictureY;
    m_PicW = m_ObjectInfo->m_PictureDatas[m_PicID].m_Column;
    m_PicH = m_ObjectInfo->m_PictureDatas[m_PicID].m_Row;
    m_Texture = m_ObjectInfo->m_PictureDatas[m_PicID].m_TextureID;
    m_Action = f->m_HeroAction;
    m_TimeTik = f->m_Wait;
    m_CenterX = f->m_CenterX;
    m_CenterY = f->m_CenterY;

    if(m_FaceSide)
    {
        m_Vel.x += f->m_DVX;
        m_Vel.y += f->m_DVY;
        m_Vel.z += f->m_DVZ;
    }
    else
    {
        m_Vel.x -= f->m_DVX;
        m_Vel.y -= f->m_DVY;
        m_Vel.z -= f->m_DVZ;
    }
}

void Object::Update(float dt)
{
    if(m_TimeTik <= 0)
    {
        NextFrame();
    }
    else
    {
        m_TimeTik--;
    }

    /*if (m_Vel.x < 0)
    {
        m_FaceSide = false;
    }else{
        m_FaceSide = true;
    }//*/

    // 更新位置
    m_Position += m_Vel;

    // 判斷如果超出場景就移除物件
    Background* nowbg = g_BackgroundManager.GetCurrentBackground();
    if(nowbg != NULL)
    {
        // 如果不是開放上下空間的場地就修正位置
        if(!nowbg->IsOpenUpDownBounding())
        {
            nowbg->FixUpDownBounding(m_Position, m_Vel);
        }
        if(!nowbg->InSpace(m_Position))
        {
            g_ObjectManager.Destory(this, 6);
        }
    }
}

void Object::UpdateDataToDraw()
{
    float scale = 3.0f;
    m_Pic.position.x = m_Position.x;
    m_Pic.position.y = m_Position.y;
    m_Pic.position.z = m_Position.z;
    m_Pic.center.x = m_CenterX * scale;
    m_Pic.center.y = m_CenterY * scale;
    m_Pic.angle = m_Angle;
    m_Pic.size.x = (float)m_ObjectInfo->m_PictureDatas[m_PicID].m_Width * scale;
    m_Pic.size.y = (float)m_ObjectInfo->m_PictureDatas[m_PicID].m_Height * scale;
    m_Pic.picpos.x = (float)m_PicX;
    m_Pic.picpos.y = (float)m_PicY;
    m_Pic.picpos.z = (float)m_PicH;
    m_Pic.picpos.w = (float)m_PicW;
    m_Pic.faceside = (float)(m_FaceSide ? 1 : -1);
}

void Object::SetTeam(int index)
{
    m_Team = index;
}

void Object::SetPosition(Vector3 p)
{
    m_Position = p;
}

void Object::Translation(Vector3 t)
{
    m_Position += t;
}

void Object::SetVelocity(Vector3 v)
{
    m_Vel = v;
}

void Object::AddVelocity(Vector3 v)
{
    m_Vel += v;
}


int Object::GetTextureID()
{
    return m_Texture;
}

Texture_Sptr Object::GetTexture()
{
    return g_TextureManager.GetTexture(m_Texture);
}

ClipVertex Object::GetPic()
{
    return m_Pic;
}

Vector3 Object::Position()
{
    return m_Position;
}

ObjectType::e Object::ObjectType()
{
    return m_ObjectInfo->m_Type;
}

PolygonVerteices Object::GetPolygonLineVerteices() const
{
    PolygonVerteices pvs;
    PolygonVertex pv;
    Polygon2Ds bodys = GetObjectBodys(*this);
    pv.color.x = 0.0;
    pv.color.y = 0.0;
    pv.color.z = 1.0;
    pv.color.w = 0.5;

    for(Polygon2Ds::iterator it = bodys.begin(); it != bodys.end(); it++)
    {
        auto points = it->Points();

        for(unsigned int i = 0; i < points.size(); i++)
        {
            pv.position.x = points[i].x();
            pv.position.y = points[i].y();
            pv.position.z = it->GetZPoint() - it->GetZRange() / 2;
            pvs.push_back(pv);
            pv.position.z = it->GetZPoint() + it->GetZRange() / 2;
            pvs.push_back(pv);
        }

        pv.position.z = it->GetZPoint() + it->GetZRange() / 2;

        for(unsigned int i = 0; i < points.size(); i++)
        {
            pv.position.x = points[i].x();
            pv.position.y = points[i].y();
            pvs.push_back(pv);
            pv.position.x = points[(i + 1) % points.size()].x();
            pv.position.y = points[(i + 1) % points.size()].y();
            pvs.push_back(pv);
        }
    }
	

	Polygon2Ds atks = GetObjectAttacks(*this);
	pv.color.x = 1.0;
	pv.color.y = 0.0;
	pv.color.z = 0.0;
	pv.color.w = 0.5;

	for(Polygon2Ds::iterator it = atks.begin(); it != atks.end(); it++)
	{
		auto points = it->Points();

		for(unsigned int i = 0; i < points.size(); i++)
		{
			pv.position.x = points[i].x();
			pv.position.y = points[i].y();
			pv.position.z = it->GetZPoint() - it->GetZRange() / 2;
			pvs.push_back(pv);
			pv.position.z = it->GetZPoint() + it->GetZRange() / 2;
			pvs.push_back(pv);
		}

		pv.position.z = it->GetZPoint() + it->GetZRange() / 2;

		for(unsigned int i = 0; i < points.size(); i++)
		{
			pv.position.x = points[i].x();
			pv.position.y = points[i].y();
			pvs.push_back(pv);
			pv.position.x = points[(i + 1) % points.size()].x();
			pv.position.y = points[(i + 1) % points.size()].y();
			pvs.push_back(pv);
		}
	}

	Polygon2Ds catches = GetObjectCatches(*this);
	pv.color.x = 0.0;
	pv.color.y = 1.0;
	pv.color.z = 0.0;
	pv.color.w = 0.5;

	for(Polygon2Ds::iterator it = catches.begin(); it != catches.end(); it++)
	{
		auto points = it->Points();

		for(unsigned int i = 0; i < points.size(); i++)
		{
			pv.position.x = points[i].x();
			pv.position.y = points[i].y();
			pv.position.z = it->GetZPoint() - it->GetZRange() / 2;
			pvs.push_back(pv);
			pv.position.z = it->GetZPoint() + it->GetZRange() / 2;
			pvs.push_back(pv);
		}

		pv.position.z = it->GetZPoint() + it->GetZRange() / 2;

		for(unsigned int i = 0; i < points.size(); i++)
		{
			pv.position.x = points[i].x();
			pv.position.y = points[i].y();
			pvs.push_back(pv);
			pv.position.x = points[(i + 1) % points.size()].x();
			pv.position.y = points[(i + 1) % points.size()].y();
			pvs.push_back(pv);
		}
	}

    return pvs;
}

PolygonVerteices Object::GetPolygonVerteices() const
{
	PolygonVerteices pvs;
	PolygonVertex pv;
	Polygon2Ds bodys = GetObjectBodys(*this);
	pv.color.x = 0.0;
	pv.color.y = 0.0;
	pv.color.z = 1.0;
	pv.color.w = 0.5;

	for(Polygon2Ds::iterator it = bodys.begin(); it != bodys.end(); it++)
	{
		auto points = it->Points();
		pv.position.z = it->GetZPoint() - it->GetZRange() / 2;

		for(unsigned int i = 1; i + 1 < points.size(); i++)
		{
			pv.position.x = points[0].x();
			pv.position.y = points[0].y();
			pvs.push_back(pv);
			pv.position.x = points[i].x();
			pv.position.y = points[i].y();
			pvs.push_back(pv);
			pv.position.x = points[i + 1].x();
			pv.position.y = points[i + 1].y();
			pvs.push_back(pv);
		}
	}

	Polygon2Ds  atks = GetObjectAttacks(*this);
	pv.color.x = 1.0;
	pv.color.y = 0.0;
	pv.color.z = 0.0;
	pv.color.w = 0.5;

	for(Polygon2Ds::iterator it = atks.begin(); it != atks.end(); it++)
	{
		auto points = it->Points();
		pv.position.z = it->GetZPoint() - it->GetZRange() / 2;

		for(unsigned int i = 1; i + 1 < points.size(); i++)
		{
			pv.position.x = points[0].x();
			pv.position.y = points[0].y();
			pvs.push_back(pv);
			pv.position.x = points[i].x();
			pv.position.y = points[i].y();
			pvs.push_back(pv);
			pv.position.x = points[i + 1].x();
			pv.position.y = points[i + 1].y();
			pvs.push_back(pv);
		}
	}

	Polygon2Ds  catches = GetObjectCatches(*this);
	pv.color.x = 0.0;
	pv.color.y = 1.0;
	pv.color.z = 0.0;
	pv.color.w = 0.5;

	for(Polygon2Ds::iterator it = catches.begin(); it != catches.end(); it++)
	{
		auto points = it->Points();
		pv.position.z = it->GetZPoint() - it->GetZRange() / 2;

		for(unsigned int i = 1; i + 1 < points.size(); i++)
		{
			pv.position.x = points[0].x();
			pv.position.y = points[0].y();
			pvs.push_back(pv);
			pv.position.x = points[i].x();
			pv.position.y = points[i].y();
			pvs.push_back(pv);
			pv.position.x = points[i + 1].x();
			pv.position.y = points[i + 1].y();
			pvs.push_back(pv);
		}
	}

	return pvs;
}

bool SortObject(Object_RawPtr a, Object_RawPtr b)
{
    return a->GetTextureID() < b->GetTextureID();
}


