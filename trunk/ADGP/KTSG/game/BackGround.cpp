#include "BackGround.h"
#include "global.h"


bool BackGround::CheckDataVaild( LuaCell_Sptr luadata )
{
	bool testOK = true;
	testOK &= luadata->HasValue("name");
	// read space bounding
	for (int i=1;;++i)
	{
		if (luadata->HasValue("space_bounding/%d/xmin", i))
		{
			testOK &= luadata->HasValue("space_bounding/%d/xmin", i);
			testOK &= luadata->HasValue("space_bounding/%d/ymin", i);
			testOK &= luadata->HasValue("space_bounding/%d/zmin", i);
			testOK &= luadata->HasValue("space_bounding/%d/xmax", i);
			testOK &= luadata->HasValue("space_bounding/%d/ymax", i);
			testOK &= luadata->HasValue("space_bounding/%d/zmax", i);
		}
		else
			break;
	}
	if (!testOK) return testOK;
	// read ban bounding
	for (int i=1;;++i)
	{
		if (luadata->HasValue("ban_bounding/%d/xmin", i))
		{
			testOK &= luadata->HasValue("ban_bounding/%d/xmin", i);
			testOK &= luadata->HasValue("ban_bounding/%d/ymin", i);
			testOK &= luadata->HasValue("ban_bounding/%d/zmin", i);
			testOK &= luadata->HasValue("ban_bounding/%d/xmax", i);
			testOK &= luadata->HasValue("ban_bounding/%d/ymax", i);
			testOK &= luadata->HasValue("ban_bounding/%d/zmax", i);
		}
		else
			break;
	}
	if (!testOK) return testOK;
	// read BGLayers
	for (int i=1;;++i)
	{
		if (luadata->HasValue("layer/%d/picture_path", i))
		{
			testOK &= luadata->HasValue("layer/%d/picture_path", i);
			testOK &= luadata->HasValue("layer/%d/ground", i);
			testOK &= luadata->HasValue("layer/%d/x", i);
			testOK &= luadata->HasValue("layer/%d/y", i);
			testOK &= luadata->HasValue("layer/%d/z", i);
			testOK &= luadata->HasValue("layer/%d/w", i);
			testOK &= luadata->HasValue("layer/%d/h", i);
			testOK &= luadata->HasValue("layer/%d/loop_distance", i);
			testOK &= luadata->HasValue("layer/%d/timeline", i);
			testOK &= luadata->HasValue("layer/%d/time_start", i);
			testOK &= luadata->HasValue("layer/%d/time_end", i);
		}
		else
			break;
	}
	if (!testOK) return testOK;
	// read color rect
	for (int i=1;;++i)
	{
		if (luadata->HasValue("color_rect/%d/r", i))
		{
			testOK &= luadata->HasValue("color_rect/%d/r", i);
			testOK &= luadata->HasValue("color_rect/%d/g", i);
			testOK &= luadata->HasValue("color_rect/%d/b", i);
			testOK &= luadata->HasValue("color_rect/%d/a", i);
			testOK &= luadata->HasValue("color_rect/%d/ground", i);
			testOK &= luadata->HasValue("color_rect/%d/x", i);
			testOK &= luadata->HasValue("color_rect/%d/y", i);
			testOK &= luadata->HasValue("color_rect/%d/z", i);
			testOK &= luadata->HasValue("color_rect/%d/w", i);
			testOK &= luadata->HasValue("color_rect/%d/h", i);
		}
		else
			break;
	}
	if (!testOK) return testOK;
	// read ParallelLights
	for (int i=1;;++i)
	{
		if (luadata->HasValue("parallel_light/%d/r", i))
		{
			testOK &= luadata->HasValue("parallel_light/%d/x", i);
			testOK &= luadata->HasValue("parallel_light/%d/y", i);
			testOK &= luadata->HasValue("parallel_light/%d/z", i);
			testOK &= luadata->HasValue("parallel_light/%d/light", i);
			testOK &= luadata->HasValue("parallel_light/%d/timeline", i);
			testOK &= luadata->HasValue("parallel_light/%d/time_start", i);
			testOK &= luadata->HasValue("parallel_light/%d/time_end", i);
		}
		else
			break;
	}
	return testOK;
}

void BackGround::LoadData( LuaCell_Sptr luadata )
{
	m_LuaCell	= luadata;
	m_Name		= luadata->GetLua<const char*>("name");
	m_Width		= (float)luadata->GetLua<double>("width");
	// read space bounding
	for (int i=1;;++i)
	{
		if (luadata->HasValue("space_bounding/%d/xmin", i))
		{
			AxisAlignedBox aabb;
			aabb.setMinimumX((float)luadata->GetLua<double>("space_bounding/%d/xmin", i));
			aabb.setMinimumY((float)luadata->GetLua<double>("space_bounding/%d/ymin", i));
			aabb.setMinimumZ((float)luadata->GetLua<double>("space_bounding/%d/zmin", i));
			aabb.setMaximumX((float)luadata->GetLua<double>("space_bounding/%d/xmax", i));
			aabb.setMaximumY((float)luadata->GetLua<double>("space_bounding/%d/ymax", i));
			aabb.setMaximumZ((float)luadata->GetLua<double>("space_bounding/%d/zmax", i));
			m_SpaceBounding.push_back(aabb);
		}
		else
			break;
	}
	// read ban bounding
	for (int i=1;;++i)
	{
		if (luadata->HasValue("ban_bounding/%d/xmin", i))
		{
			AxisAlignedBox aabb;
			aabb.setMinimumX((float)luadata->GetLua<double>("ban_bounding/%d/xmin", i));
			aabb.setMinimumY((float)luadata->GetLua<double>("ban_bounding/%d/ymin", i));
			aabb.setMinimumZ((float)luadata->GetLua<double>("ban_bounding/%d/zmin", i));
			aabb.setMaximumX((float)luadata->GetLua<double>("ban_bounding/%d/xmax", i));
			aabb.setMaximumY((float)luadata->GetLua<double>("ban_bounding/%d/ymax", i));
			aabb.setMaximumZ((float)luadata->GetLua<double>("ban_bounding/%d/zmax", i));
			m_BanBounding.push_back(aabb);
		}
		else
			break;
	}
	// read BGLayers
	for (int i=1;;++i)
	{
		if (luadata->HasValue("layer/%d/picture_path", i))
		{
			BGLayer bgl;
			bgl.m_PicturePath	= luadata->GetLua<const char*>("layer/%d/picture_path", i);
			bgl.m_IsGround		= !!luadata->GetLua<int>("layer/%d/ground", i);
			bgl.m_Position.x	= (float)luadata->GetLua<double>("layer/%d/x", i);
			bgl.m_Position.y	= (float)luadata->GetLua<double>("layer/%d/y", i);
			bgl.m_Position.z	= (float)luadata->GetLua<double>("layer/%d/z", i);
			bgl.m_Width		= (float)luadata->GetLua<double>("layer/%d/w", i);
			bgl.m_Height		= (float)luadata->GetLua<double>("layer/%d/h", i);
			bgl.m_LoopDistance	= luadata->GetLua<int>("layer/%d/loop_distance", i);
			bgl.m_TimeLine		= luadata->GetLua<int>("layer/%d/timeline", i);
			bgl.m_TimeStart		= luadata->GetLua<int>("layer/%d/time_start", i);
			bgl.m_TimeEnd		= luadata->GetLua<int>("layer/%d/time_end", i);
			bgl.m_PicID		= g_TextureManager.AddTexture(bgl.m_PicturePath);
			m_BGLayers.push_back(bgl);
		}
		else
			break;
	}
	// read color rect
	for (int i=1;;++i)
	{
		if (luadata->HasValue("color_rect/%d/r", i))
		{
			ColorRect cr;
			cr.m_Color[0]	= (float)luadata->GetLua<double>("color_rect/%d/r", i);
			cr.m_Color[1]	= (float)luadata->GetLua<double>("color_rect/%d/g", i);
			cr.m_Color[2]	= (float)luadata->GetLua<double>("color_rect/%d/b", i);
			cr.m_Color[3]	= (float)luadata->GetLua<double>("color_rect/%d/a", i);
			cr.m_IsGround	= !!luadata->GetLua<int>("color_rect/%d/ground", i);
			cr.m_Position.x	= (float)luadata->GetLua<double>("color_rect/%d/x", i);
			cr.m_Position.y	= (float)luadata->GetLua<double>("color_rect/%d/y", i);
			cr.m_Position.z	= (float)luadata->GetLua<double>("color_rect/%d/z", i);
			cr.m_Width	= (float)luadata->GetLua<double>("color_rect/%d/w", i);
			cr.m_Height	= (float)luadata->GetLua<double>("color_rect/%d/h", i);
			m_ColorRects.push_back(cr);
		}
		else
			break;
	}
	// read ParallelLights
	for (int i=1;;++i)
	{
		if (luadata->HasValue("parallel_light/%d/r", i))
		{
			ParallelLight pl;
			pl.m_Direction.x	= (float)luadata->GetLua<double>("parallel_light/%d/x", i);
			pl.m_Direction.y	= (float)luadata->GetLua<double>("parallel_light/%d/y", i);
			pl.m_Direction.z	= (float)luadata->GetLua<double>("parallel_light/%d/z", i);
			pl.m_LightStrength	= (float)luadata->GetLua<double>("parallel_light/%d/light", i);
			pl.m_TimeLine		= luadata->GetLua<int>("parallel_light/%d/timeline", i);
			pl.m_TimeStart		= luadata->GetLua<int>("parallel_light/%d/time_start", i);
			pl.m_TimeEnd		= luadata->GetLua<int>("parallel_light/%d/time_end", i);
			m_ParallelLights.push_back(pl);
		}
		else
			break;
	}
}

void BackGround::Update( float dt )
{
	m_TimeTik++;
	g_Time = m_TimeTik;
}

void BackGround::BuildPoint()
{
	m_BGVerteices.clear();
	m_DrawVertexGroups.clear();
	int vertexCount = 0, count = 0;
	for(BGLayers::iterator it=m_BGLayers.begin();it != m_BGLayers.end();it++)
	{
		if(m_TimeTik%it->m_TimeLine < it->m_TimeStart)continue;
		if(m_TimeTik%it->m_TimeLine > it->m_TimeEnd)  continue;
		DrawVertexGroup dvg = {};
		dvg.texture = g_TextureManager.GetTexture(it->m_PicID);
		vertexCount = 0;
		dvg.StartVertexLocation = count;
		int d=0;
		do 
		{
			BGVertex bgv;

			bgv.position.x = it->m_Position.x + d*it->m_LoopDistance;
			bgv.position.y = it->m_Position.y ;
			bgv.position.z = it->m_Position.z;
			bgv.size.x     = it->m_Width  ;
			bgv.size.y     = it->m_Height ;
			if(it->m_IsGround)
			{
				bgv.angle = 90;
			}
			else
			{
				bgv.angle = 0;
			}
			m_BGVerteices.push_back(bgv);
			++vertexCount;
			++count;
			d++;
			if(bgv.position.x = it->m_Position.x + d*it->m_LoopDistance > m_Width)
				break;

		} while (it->m_LoopDistance > 0);

		dvg.VertexCount = vertexCount;
		m_DrawVertexGroups.push_back(dvg);
	}
}

void BackGround::Init()
{
	m_TimeTik = 0;
}
