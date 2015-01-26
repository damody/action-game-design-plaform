#include <locale> 
#include <codecvt> 
#include "game\ObjectInfo.h"
#include "game\SmallFunction.h"

bool	ObjectInfo::CheckObjectDataVaild( LuaCell_Sptr luadata )
{
	return true;
}

void	ObjectInfo::LoadData( LuaCell_Sptr luadata )
{
	const char* tcp;	//temp char pointer
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> ucs2conv;	//用以將 UTF8 字串轉碼成 wchar 用的 UCS
	m_LuaCell	= luadata;
	tcp = luadata->GetLua<const char*>( "name" );		//str to wstr
	m_Name		= ucs2conv.from_bytes(tcp);
	m_MaxHP		= luadata->GetLua<int>( "hp" );
	m_Mess		= ( float )luadata->GetLua<int>( "mess" );
	m_Elasticity	= ( float )luadata->GetLua<double>( "elasticity" );
	m_Type		= ( ObjectType::e )luadata->GetLua<int>( "objecttype" );
	m_FlyingType	= ( FlyingType::e )luadata->GetLua<int>( "flyingtype" );

	// read picture file
	for ( int i = 1;; ++i )
	{
		if ( luadata->HasValue( "file/%d/path", i ) )
		{
			PictureData pd;
			tcp = luadata->GetLua<const char*>( "file/%d/path", i );	//str to wstr
			pd.m_Path	= ucs2conv.from_bytes(tcp);
			pd.m_AutoClip	= !!luadata->GetLua<int>( "file/%d/autoclip", i );
			pd.m_Width	= luadata->GetLua<int>( "file/%d/w", i );
			pd.m_Height	= luadata->GetLua<int>( "file/%d/h", i );
			pd.m_Row	= luadata->GetLua<int>( "file/%d/row", i );
			pd.m_Column	= luadata->GetLua<int>( "file/%d/col", i );
			//pd.m_TextureID  = g_TextureManager.AddTexture( pd.m_Path );
			m_PictureDatas.push_back( pd );
		}
		else
		{
			break;
		}
	}

	strings tac = luadata->GetLuaTableKeys( "frame" );
	wstrings actions;
	for(strings::iterator i = tac.begin(); i != tac.end(); i++ ){
		actions.push_back( std::wstring(i->begin(), i->end()) );
	}

	for ( int i = 0; i < ( int )actions.size(); ++i )
	{
		m_FramesMap[actions[i]] = FrameInfos();
	}

	for ( int i = 0; i < ( int )actions.size(); ++i )
	{
		for ( int frameCount = 0;; frameCount++ )
		{
			FrameInfo newData;
			const char* frameName	= tac[i].c_str();

			if ( !luadata->HasValue( "frame/%s/%d/pic_id", frameName, frameCount ) ) { break; }

			newData.m_FrameName	= actions[i];
			newData.m_FrameIndex = frameCount;
			newData.m_PictureID	= luadata->GetLua<int>( "frame/%s/%d/pic_id", frameName, frameCount );
			newData.m_PictureX	= luadata->GetLua<int>( "frame/%s/%d/pic_x", frameName, frameCount );
			newData.m_PictureY	= luadata->GetLua<int>( "frame/%s/%d/pic_y", frameName, frameCount );
			newData.m_HeroAction	= luadata->GetLua<int>( "frame/%s/%d/state", frameName, frameCount );
			newData.m_Wait		= luadata->GetLua<int>( "frame/%s/%d/wait", frameName, frameCount );
			tcp = luadata->GetLua<const char*>( "frame/%s/%d/next/1", frameName, frameCount );
			newData.m_NextFrameName	= ucs2conv.from_bytes(tcp);
			newData.m_NextFrameIndex = luadata->GetLua<int>( "frame/%s/%d/next/2", frameName, frameCount );
			newData.m_DVX		= ( float )luadata->GetLua<double>( "frame/%s/%d/dvx", frameName, frameCount );
			newData.m_DVY		= ( float )luadata->GetLua<double>( "frame/%s/%d/dvy", frameName, frameCount );
			newData.m_DVZ		= ( float )luadata->GetLua<double>( "frame/%s/%d/dvz", frameName, frameCount );
			newData.m_CenterX	= ( float )luadata->GetLua<double>( "frame/%s/%d/centerx", frameName, frameCount );
			newData.m_CenterY	= ( float )luadata->GetLua<double>( "frame/%s/%d/centery", frameName, frameCount );
			newData.m_ClearKeyQueue	= luadata->GetLua<int>( "frame/%s/%d/clear_key_queue", frameName, frameCount );

			for ( int hitCount = 1;; ++hitCount )
			{
				if ( luadata->HasValue( "frame/%s/%d/hit/%d/1", frameName, frameCount, hitCount ) )
				{
					HitData hitData;
					// get hit key action "d>a"
					hitData.m_KeyQueue	= luadata->GetLua<const char*>( "frame/%s/%d/hit/%d/1", frameName, frameCount, hitCount );
					// get action name "many_punch"
					tcp = luadata->GetLua<const char*>( "frame/%s/%d/hit/%d/2", frameName, frameCount, hitCount );
					hitData.m_FrameName	= ucs2conv.from_bytes(tcp);
					// get frame offset
					hitData.m_FrameOffset	= luadata->GetLua<int>( "frame/%s/%d/hit/%d/3", frameName, frameCount, hitCount );
					newData.m_HitDatas.push_back( hitData );
				}
				else
				{
					break;
				}
			}

			for ( int bloodCount = 1;; ++bloodCount )
			{
				if ( luadata->HasValue( "frame/%s/%d/blood/%d/size", frameName, frameCount, bloodCount ) )
				{
					BloodInfo	bloodInfo;
					bloodInfo.m_Scale	= ( float )luadata->GetLua<double>( "frame/%s/%d/blood/%d/size", frameName, frameCount, bloodCount );
					bloodInfo.m_Position.x	= ( float )luadata->GetLua<double>( "frame/%s/%d/blood/%d/x", frameName, frameCount, bloodCount );
					bloodInfo.m_Position.y	= ( float )luadata->GetLua<double>( "frame/%s/%d/blood/%d/y", frameName, frameCount, bloodCount );
					bloodInfo.m_EnableValue	= ( float )luadata->GetLua<double>( "frame/%s/%d/blood/%d/value", frameName, frameCount, bloodCount );
					newData.m_BloodInfos.push_back( bloodInfo );
				}
				else
				{
					break;
				}
			}

			for(int atkCount = 1;; ++atkCount)
			{
				if(luadata->HasValue("frame/%s/%d/attack/%d/kind", frameName, frameCount, atkCount))
				{
					Attack atk;
					atk.m_Kind  = luadata->GetLua<int>("frame/%s/%d/attack/%d/kind", frameName, frameCount, atkCount);
					atk.m_Effect    = luadata->GetLua<int>("frame/%s/%d/attack/%d/effect", frameName, frameCount, atkCount);
					atk.m_ZWidth    = (float)luadata->GetLua<double>("frame/%s/%d/attack/%d/zwidth", frameName, frameCount, atkCount);
					atk.m_DVX   = (float)luadata->GetLua<double>("frame/%s/%d/attack/%d/dvx", frameName, frameCount, atkCount);
					atk.m_DVY   = (float)luadata->GetLua<double>("frame/%s/%d/attack/%d/dvy", frameName, frameCount, atkCount);
					atk.m_DVZ   = (float)luadata->GetLua<double>("frame/%s/%d/attack/%d/dvz", frameName, frameCount, atkCount);
					atk.m_Fall  = luadata->GetLua<int>("frame/%s/%d/attack/%d/fall", frameName, frameCount, atkCount);
					atk.m_BreakDefend   = luadata->GetLua<int>("frame/%s/%d/attack/%d/breakDefend", frameName, frameCount, atkCount);
					atk.m_AttackRest    = luadata->GetLua<int>("frame/%s/%d/attack/%d/arest", frameName, frameCount, atkCount);
					atk.m_ReAttackRest  = luadata->GetLua<int>("frame/%s/%d/attack/%d/reAttackRest", frameName, frameCount, atkCount);
					atk.m_Injury    = luadata->GetLua<int>("frame/%s/%d/attack/%d/injury", frameName, frameCount, atkCount);
					atk.m_Strength  = luadata->GetLua<int>("frame/%s/%d/attack/%d/strength", frameName, frameCount, atkCount);

					for(int pointCount = 1;; ++pointCount)
					{
						if(luadata->HasValue("frame/%s/%d/attack/%d/points/%d/1",
							frameName, frameCount, atkCount, pointCount))
						{
							Vector2 vec2;
							vec2.x = (float)luadata->GetLua<double>("frame/%s/%d/attack/%d/points/%d/1",
								frameName, frameCount, atkCount, pointCount);
							vec2.y = (float)luadata->GetLua<double>("frame/%s/%d/attack/%d/points/%d/2",
								frameName, frameCount, atkCount, pointCount);
							atk.m_Area.AddPoint(vec2);
						}
						else
						{
							break;
						}
					}

					newData.m_Attacks.push_back(atk);
				}
				else
				{
					break;
				}
			}

			for ( int bodyCount = 1;; ++bodyCount )
			{
				if ( luadata->HasValue( "frame/%s/%d/body/%d/kind", frameName, frameCount, bodyCount ) )
				{
					Body body;
					body.m_Kind	= luadata->GetLua<int>( "frame/%s/%d/body/%d/kind", frameName, frameCount, bodyCount );
					body.m_ZWidth	= ( float )luadata->GetLua<double>( "frame/%s/%d/body/%d/zwidth", frameName, frameCount, bodyCount );

					for ( int pointCount = 1;; ++pointCount )
					{
						if ( luadata->HasValue( "frame/%s/%d/body/%d/points/%d/1",
						                        frameName, frameCount, bodyCount, pointCount ) )
						{
							Vector2 vec2;
							vec2.x = ( float )luadata->GetLua<double>( "frame/%s/%d/body/%d/points/%d/1",
							                frameName, frameCount, bodyCount, pointCount );
							vec2.y = ( float )luadata->GetLua<double>( "frame/%s/%d/body/%d/points/%d/2",
							                frameName, frameCount, bodyCount, pointCount );
							body.m_Area.AddPoint( vec2 );
						}
						else
						{
							break;
						}
					}

					newData.m_Bodys.push_back( body );
				}
				else
				{
					break;
				}
			}

			for ( int catchCount = 1;; ++catchCount )
			{
				if ( luadata->HasValue( "frame/%s/%d/catch/%d/kind", frameName, frameCount, catchCount ) )
				{
					CatchInfo catchInfo;
					catchInfo.m_Kind	= luadata->GetLua<int>( "frame/%s/%d/catch/%d/kind", frameName, frameCount, catchCount );
					catchInfo.m_ZWidth	= ( float )luadata->GetLua<double>( "frame/%s/%d/catch/%d/zwidth", frameName, frameCount, catchCount );
					catchInfo.m_CatchPosition.x = ( float )luadata->GetLua<double>( "frame/%s/%d/catch/%d/catchx", frameName, frameCount, catchCount );
					catchInfo.m_CatchPosition.y = ( float )luadata->GetLua<double>( "frame/%s/%d/catch/%d/catchy", frameName, frameCount, catchCount );
					catchInfo.m_CatchWhere	= ( CatchInfo::CatchPosition )luadata->GetLua<int>
					                          ( "frame/%s/%d/catch/%d/where", frameName, frameCount, catchCount );

					for ( int pointCount = 1;; ++pointCount )
					{
						if ( luadata->HasValue( "frame/%s/%d/catch/%d/points/%d/1",
						                        frameName, frameCount, catchCount, pointCount ) )
						{
							Vector2 vec2;
							vec2.x = ( float )luadata->GetLua<double>( "frame/%s/%d/catch/%d/points/%d/1",
							                frameName, frameCount, catchCount, pointCount );
							vec2.y = ( float )luadata->GetLua<double>( "frame/%s/%d/catch/%d/points/%d/2",
							                frameName, frameCount, catchCount, pointCount );
							catchInfo.m_Area.AddPoint( vec2 );
						}
						else
						{
							break;
						}
					}

					newData.m_Catchs.push_back( catchInfo );
				}
				else
				{
					break;
				}
			}

			m_FramesMap[actions[i]].push_back( newData );
		}
	}
}

void ObjectInfo::WriteLua(ObjectInfo* hero , std::wstring filePath)
{
	FILE* file = _wfopen(filePath.c_str() , L"w,ccs=UTF-8");
	wstrings frameTable;
	LuaMap am(L"Script/Action.lua", "Action");
	LuaMap om(L"Script/object.lua", "ObjectType");
	LuaMap fm(L"Script/object.lua", "FlyingType");

	//判斷結尾是否有.lua 沒有則加上
	if(!(filePath.size() >= 4 &&
		filePath[filePath.size() - 4] == '.' &&
		filePath[filePath.size() - 3] == 'l' &&
		filePath[filePath.size() - 2] == 'u' &&
		filePath[filePath.size() - 1] == 'a'))
	{
		filePath.resize(filePath.size() + 4);
		filePath[filePath.size() - 4] = '.';
		filePath[filePath.size() - 3] = 'l';
		filePath[filePath.size() - 2] = 'u';
		filePath[filePath.size() - 1] = 'a';
	}

	//-------------------------------------
	fwprintf(file, L"require(\"Script.effect\")\n");
	fwprintf(file, L"require(\"Script.object\")\n");
	fwprintf(file, L"\n");
	//-------------------------------------
	fwprintf(file, L"name\t= \"%ls\"\n", RevisePath(hero->m_Name).c_str());
	fwprintf(file, L"\n");
	//-------------------------------------
	fwprintf(file, L"file = {\n");

	for(int i = 0; i < (int)hero->m_PictureDatas.size(); i++)
	{
		std::wstring path = hero->m_PictureDatas[i].m_Path;
		bool autoclip = hero->m_PictureDatas[i].m_AutoClip;
		int w = hero->m_PictureDatas[i].m_Width;
		int h = hero->m_PictureDatas[i].m_Height;
		int row = hero->m_PictureDatas[i].m_Row;
		int col = hero->m_PictureDatas[i].m_Column;
		fwprintf(file, L"{path = \"%ls\", ", RevisePath(path).c_str());
		fwprintf(file, L"autoclip = %d, ", autoclip);
		fwprintf(file, L"w = %d, ", w);
		fwprintf(file, L"h = %d, ", h);
		fwprintf(file, L"row = %d, ", row);
		fwprintf(file, L"col = %d },\n", col);
	}

	fwprintf(file, L"}\n");
	fwprintf(file, L"\n");
	//-------------------------------------


}
