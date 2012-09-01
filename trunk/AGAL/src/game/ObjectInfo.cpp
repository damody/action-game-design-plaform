#include "StdAGAL.h"
#include "game\ObjectInfo.h"

bool	ObjectInfo::CheckObjectDataVaild(LuaCell_Sptr luadata)
{
	return true;
}

void	ObjectInfo::LoadObjectData(LuaCell_Sptr luadata)
{
	m_LuaCell	= luadata;
	m_Name		= luadata->GetLua<const char*>("name");
	m_MaxHP		= luadata->GetLua<int>("hp");
	m_Mess		= (float)luadata->GetLua<int>("mess");
	m_Elasticity	= (float)luadata->GetLua<double>("elasticity");
	m_Type		= (ObjectType::e)luadata->GetLua<int>("objecttype");
	m_FlyingType	= (FlyingType::e)luadata->GetLua<int>("flyingtype");
	
	// read picture file
	for (int i=1;;++i)
	{
		if (luadata->HasValue("file/%d/path", i))
		{
			PictureData pd;
			pd.m_Path	= luadata->GetLua<const char*>("file/%d/path", i);
			pd.m_AutoClip	= !!luadata->GetLua<int>("file/%d/autoclip", i);
			pd.m_Width	= luadata->GetLua<int>("file/%d/w", i);
			pd.m_Height	= luadata->GetLua<int>("file/%d/h", i);
			pd.m_Row	= luadata->GetLua<int>("file/%d/row", i);
			pd.m_Column	= luadata->GetLua<int>("file/%d/col", i);
			//pd.m_TextureID  = g_TextureManager.AddTexture(pd.m_Path);
			m_PictureDatas.push_back(pd);
		}
		else
			break;
	}

	strings actions;
	actions = luadata->GetLuaTableKeys("frame");
	for (int i=0;i<(int)actions.size();++i)
	{
		m_FramesMap[actions[i]] = FrameInfos();
	}
	for (int i=0;i<(int)actions.size();++i)
	{
		for (int frameCount=0;;frameCount++)
		{
			FrameInfo newData;
			const char* frameName	= actions[i].c_str();
			if (!luadata->HasValue("frame/%s/%d/pic_id", frameName, frameCount)) break;
			newData.m_FrameName	= frameName;
			newData.m_PictureID	= luadata->GetLua<int>("frame/%s/%d/pic_id", frameName, frameCount);
			newData.m_PictureX	= luadata->GetLua<int>("frame/%s/%d/pic_x", frameName, frameCount);
			newData.m_PictureY	= luadata->GetLua<int>("frame/%s/%d/pic_y", frameName, frameCount);
			newData.m_HeroAction	= (HeroAction::e)luadata->GetLua<int>("frame/%s/%d/state", frameName, frameCount);
			newData.m_Wait		= luadata->GetLua<int>("frame/%s/%d/wait", frameName, frameCount);
			newData.m_NextFrameName	= luadata->GetLua<const char*>("frame/%s/%d/next/1", frameName, frameCount);
			newData.m_NextFrameIndex= luadata->GetLua<int>("frame/%s/%d/next/2", frameName, frameCount);
			newData.m_DVX		= (float)luadata->GetLua<double>("frame/%s/%d/dvx", frameName, frameCount);
			newData.m_DVY		= (float)luadata->GetLua<double>("frame/%s/%d/dvy", frameName, frameCount);
			newData.m_DVZ		= (float)luadata->GetLua<double>("frame/%s/%d/dvz", frameName, frameCount);
			newData.m_CenterX	= (float)luadata->GetLua<double>("frame/%s/%d/centerx", frameName, frameCount);
			newData.m_CenterY	= (float)luadata->GetLua<double>("frame/%s/%d/centery", frameName, frameCount);
			newData.m_ClearKeyQueue	= luadata->GetLua<int>("frame/%s/%d/clear_key_queue", frameName, frameCount);
			for (int hitCount=1;;++hitCount)
			{
				if (luadata->HasValue("frame/%s/%d/hit/%d/1", frameName, frameCount, hitCount))
				{
					HitData hitData;
					// get hit key action "d>a" 
					hitData.m_KeyQueue	= luadata->GetLua<const char*>("frame/%s/%d/hit/%d/1", frameName, frameCount, hitCount);
					// get action name "many_punch"
					hitData.m_FrameName	= luadata->GetLua<const char*>("frame/%s/%d/hit/%d/2", frameName, frameCount, hitCount);
					// get frame offset
					hitData.m_FrameOffset	= luadata->GetLua<int>("frame/%s/%d/hit/%d/3", frameName, frameCount, hitCount);
					newData.m_HitDatas.push_back(hitData);
				}
				else
					break;
			}
			for (int bloodCount=1;;++bloodCount)
			{
				if (luadata->HasValue("frame/%s/%d/blood/%d/size", frameName, frameCount, bloodCount))
				{
					BloodInfo	bloodInfo;
					bloodInfo.m_Scale	= (float)luadata->GetLua<double>("frame/%s/%d/blood/%d/size", frameName, frameCount, bloodCount);
					bloodInfo.m_Position.x	= (float)luadata->GetLua<double>("frame/%s/%d/blood/%d/x", frameName, frameCount, bloodCount);
					bloodInfo.m_Position.y	= (float)luadata->GetLua<double>("frame/%s/%d/blood/%d/y", frameName, frameCount, bloodCount);
					bloodInfo.m_EnableValue	= (float)luadata->GetLua<double>("frame/%s/%d/blood/%d/value", frameName, frameCount, bloodCount);
					newData.m_BloodInfos.push_back(bloodInfo);
				}
				else
					break;
			}
			for (int bodyCount=1;;++bodyCount)
			{
				if (luadata->HasValue("frame/%s/%d/body/%d/kind", frameName, frameCount, bodyCount))
				{
					Body body;
					body.m_Kind	= luadata->GetLua<int>("frame/%s/%d/body/%d/kind", frameName, frameCount, bodyCount);
					body.m_ZWidth	= (float)luadata->GetLua<double>("frame/%s/%d/body/%d/zwidth", frameName, frameCount, bodyCount);
					for (int pointCount=1;;++pointCount)
					{
						if (luadata->HasValue("frame/%s/%d/body/%d/points/%d/1",
							frameName, frameCount, bodyCount, pointCount))
						{
							Vector2 vec2;
							vec2.x = (float)luadata->GetLua<double>("frame/%s/%d/body/%d/points/%d/1", 
								frameName, frameCount, bodyCount, pointCount);
							vec2.y = (float)luadata->GetLua<double>("frame/%s/%d/body/%d/points/%d/2", 
								frameName, frameCount, bodyCount, pointCount);
							body.m_Area.AddPoint(vec2);
						}
						else
							break;
					}
					newData.m_Bodys.push_back(body);
				}
				else
					break;
			}
			for (int catchCount=1;;++catchCount)
			{
				if (luadata->HasValue("frame/%s/%d/catch/%d/kind", frameName, frameCount, catchCount))
				{
					CatchInfo catchInfo;
					catchInfo.m_Kind	= luadata->GetLua<int>("frame/%s/%d/catch/%d/kind", frameName, frameCount, catchCount);
					catchInfo.m_ZWidth	= (float)luadata->GetLua<double>("frame/%s/%d/catch/%d/zwidth", frameName, frameCount, catchCount);
					catchInfo.m_CatchPosition.x = (float)luadata->GetLua<double>("frame/%s/%d/catch/%d/catchx", frameName, frameCount, catchCount);
					catchInfo.m_CatchPosition.y = (float)luadata->GetLua<double>("frame/%s/%d/catch/%d/catchy", frameName, frameCount, catchCount);
					catchInfo.m_CatchWhere	= (CatchInfo::CatchPosition)luadata->GetLua<int>
								("frame/%s/%d/catch/%d/where", frameName, frameCount, catchCount);
					for (int pointCount=1;;++pointCount)
					{
						if (luadata->HasValue("frame/%s/%d/catch/%d/points/%d/1",
							frameName, frameCount, catchCount, pointCount))
						{
							Vector2 vec2;
							vec2.x = (float)luadata->GetLua<double>("frame/%s/%d/catch/%d/points/%d/1", 
								frameName, frameCount, catchCount, pointCount);
							vec2.y = (float)luadata->GetLua<double>("frame/%s/%d/catch/%d/points/%d/2", 
								frameName, frameCount, catchCount, pointCount);
							catchInfo.m_Area.AddPoint(vec2);
						}
						else
							break;
					}
					newData.m_Catchs.push_back(catchInfo);
				}
				else
					break;
			}
			m_FramesMap[actions[i]].push_back(newData);
		}
	}
}
