#include "game\HeroInfo.h"
#include "..\..\..\AGDP\ConvStr.h"

HeroInfo::HeroInfo(): m_Name(), m_MaxHP( 500 ), m_MaxMP( 500 ),
	m_WalkingSpeed( 0 ),
	m_WalkingSpeedZ( 0 ),
	m_RunningSpeed( 0 ),
	m_RunningSpeedZ( 0 ),
	m_HeavyWalkingSpeed( 0 ),
	m_HeavyWalkingSpeedZ( 0 ),
	m_HeavyRunningSpeed( 0 ),
	m_HeavyRunningSpeedZ( 0 ),
	m_JumpHeight( 0 ),
	m_JumpDistance( 0 ),
	m_JumpDistanceZ( 0 ),
	m_DashHeight( 0 ),
	m_DashDistance( 0 ),
	m_DashDistanceZ( 0 ),
	m_RowingHeight( 0 ),
	m_RowingDistance( 0 )
{
}

bool HeroInfo::CheckHeroDataVaild( LuaCell_Sptr luadata )
{
	bool testOK = true;
	testOK &= luadata->HasValue( "name" );
	testOK &= luadata->HasValue( "head" );
	testOK &= luadata->HasValue( "small" );
	testOK &= luadata->HasValue( "file" );
	testOK &= luadata->HasValue( "walking_speed" );
	testOK &= luadata->HasValue( "walking_speedz" );
	testOK &= luadata->HasValue( "running_speed" );
	testOK &= luadata->HasValue( "running_speedz" );
	testOK &= luadata->HasValue( "heavy_walking_speed" );
	testOK &= luadata->HasValue( "heavy_walking_speedz" );
	testOK &= luadata->HasValue( "heavy_running_speed" );
	testOK &= luadata->HasValue( "heavy_running_speedz" );
	testOK &= luadata->HasValue( "jump_height" );
	testOK &= luadata->HasValue( "jump_distance" );
	testOK &= luadata->HasValue( "jump_distancez" );
	testOK &= luadata->HasValue( "dash_height" );
	testOK &= luadata->HasValue( "dash_distance" );
	testOK &= luadata->HasValue( "dash_distancez" );
	testOK &= luadata->HasValue( "rowing_height" );
	testOK &= luadata->HasValue( "rowing_distance" );
	testOK &= luadata->HasValue( "frame/default" );
	testOK &= luadata->HasValue( "frame/standing" );
	testOK &= luadata->HasValue( "frame/walking" );

	if ( !testOK ) { return false; }

	for ( int i = 1;; ++i )
	{
		testOK &= luadata->HasValue( "file/%d/path", i );
		testOK &= luadata->HasValue( "file/%d/autoclip", i );
		testOK &= luadata->HasValue( "file/%d/w", i );
		testOK &= luadata->HasValue( "file/%d/h", i );
		testOK &= luadata->HasValue( "file/%d/row", i );
		testOK &= luadata->HasValue( "file/%d/col", i );

		if ( 1 == i && !testOK )
		{
			return false;
		}
		else
		{
			testOK = true;
			break;
		}
	}

	strings actions;
	actions = luadata->GetLuaTableKeys( "frame" );

	for ( int i = 0; i < ( int )actions.size(); ++i )
	{
		for ( int frames = 1;; frames++ )
		{
			const char* frameName	= actions[i].c_str();
			testOK &= luadata->HasValue( "frame/%s/%d/pic_id", frameName, frames );
			testOK &= luadata->HasValue( "frame/%s/%d/pic_x", frameName, frames );
			testOK &= luadata->HasValue( "frame/%s/%d/pic_y", frameName, frames );
			testOK &= luadata->HasValue( "frame/%s/%d/state", frameName, frames );
			testOK &= luadata->HasValue( "frame/%s/%d/wait", frameName, frames );
			testOK &= luadata->HasValue( "frame/%s/%d/next", frameName, frames );
			testOK &= luadata->HasValue( "frame/%s/%d/dvx", frameName, frames );
			testOK &= luadata->HasValue( "frame/%s/%d/dvy", frameName, frames );
			testOK &= luadata->HasValue( "frame/%s/%d/dvz", frameName, frames );
			testOK &= luadata->HasValue( "frame/%s/%d/centerx", frameName, frames );
			testOK &= luadata->HasValue( "frame/%s/%d/centery", frameName, frames );
			testOK &= luadata->HasValue( "frame/%s/%d/clear_key_queue", frameName, frames );
			testOK &= luadata->HasValue( "frame/%s/%d/hit", frameName, frames );
			testOK &= luadata->HasValue( "frame/%s/%d/blood", frameName, frames );
		}
	}

	return testOK;
}

void HeroInfo::LoadHeroData( LuaCell_Sptr luadata )
{
	m_LuaCell	= luadata;
	m_Name		= luadata->GetLua<const char*>( "name" );
	m_Headpic	= luadata->GetLua<const char*>( "head" );
	//g_TextureManager.AddTexture(m_Headpic);
	m_Smallpic	= luadata->GetLua<const char*>( "small" );
	//g_TextureManager.AddTexture(m_Smallpic);
	m_WalkingSpeed	= ( float )luadata->GetLua<double>( "walking_speed" );
	m_WalkingSpeedZ	= ( float )luadata->GetLua<double>( "walking_speedz" );
	m_RunningSpeed	= ( float )luadata->GetLua<double>( "running_speed" );
	m_RunningSpeedZ	= ( float )luadata->GetLua<double>( "running_speedz" );
	m_HeavyWalkingSpeed	= ( float )luadata->GetLua<double>( "heavy_walking_speed" );
	m_HeavyWalkingSpeedZ	= ( float )luadata->GetLua<double>( "heavy_walking_speedz" );
	m_HeavyRunningSpeed	= ( float )luadata->GetLua<double>( "heavy_running_speed" );
	m_HeavyRunningSpeedZ	= ( float )luadata->GetLua<double>( "heavy_running_speedz" );
	m_JumpHeight	= ( float )luadata->GetLua<double>( "jump_height" );
	m_JumpDistance	= ( float )luadata->GetLua<double>( "jump_distance" );
	m_JumpDistanceZ	= ( float )luadata->GetLua<double>( "jump_distancez" );
	m_DashHeight	= ( float )luadata->GetLua<double>( "dash_height" );
	m_DashDistance	= ( float )luadata->GetLua<double>( "dash_distance" );
	m_DashDistanceZ	= ( float )luadata->GetLua<double>( "dash_distancez" );
	m_RowingHeight	= ( float )luadata->GetLua<double>( "rowing_height" );
	m_RowingDistance = ( float )luadata->GetLua<double>( "rowing_distance" );

	// read picture file
	for ( int i = 1;; ++i )
	{
		if ( luadata->HasValue( "file/%d/path", i ) )
		{
			PictureData pd;
			pd.m_Path	= luadata->GetLua<const char*>( "file/%d/path", i );
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

	for ( int i = 1;; ++i )
	{
		if ( luadata->HasValue( "action_key_map/%d/1", i ) )
		{
			int action = luadata->GetLua<int>( "action_key_map/%d/1", i );
			HitDatas hds;

			for ( int hitCount = 1;; ++hitCount )
			{
				if ( luadata->HasValue( "action_key_map/%d/map/%d/1", i, hitCount ) )
				{
					HitData hitData;
					// get hit key action "d>a"
					hitData.m_KeyQueue	= luadata->GetLua<const char*>( "action_key_map/%d/map/%d/1", i, hitCount );
					// get action name "many_punch"
					hitData.m_FrameName	= luadata->GetLua<const char*>( "action_key_map/%d/map/%d/2", i, hitCount );
					// get frame offset
					hitData.m_FrameOffset	= luadata->GetLua<int>( "action_key_map/%d/map/%d/3", i, hitCount );
					hds.push_back( hitData );
				}
				else
				{
					break;
				}
			}

			m_ActionKeyMap[action] = hds;
		}
		else
		{
			break;
		}
	}

	for ( int i = 1;; ++i )
	{
		if ( luadata->HasValue( "air_crouch_map/%d/1", i ) )
		{
			CrouchData cd;
			int action = luadata->GetLua<int>( "air_crouch_map/%d/1", i );
			// get action name "many_punch"
			cd.m_FrameName	= luadata->GetLua<const char*>( "air_crouch_map/%d/2", i );
			// get frame offset
			cd.m_FrameOffset = luadata->GetLua<int>( "air_crouch_map/%d/3", i );
			m_CrouchMap[action] = cd;
		}
		else
		{
			break;
		}
	}

	strings actions;
	actions = luadata->GetLuaTableKeys( "frame" );

	for ( int i = 0; i < ( int )actions.size(); ++i )
	{
		m_FramesMap[actions[i]] = FrameInfos();
	}

	for ( int i = 0; i < ( int )actions.size(); ++i )
	{
		FrameInfos* fFrame = &m_FramesMap[actions[i]];

		for ( int frameCount = 0;; frameCount++ )
		{
			FrameInfo newData = {};
			const char* frameName	= actions[i].c_str();

			if ( !luadata->HasValue( "frame/%s/%d/pic_id", frameName, frameCount ) ) { break; }

			newData.m_FrameName	= frameName;
			newData.m_PictureID	= luadata->GetLua<int>( "frame/%s/%d/pic_id", frameName, frameCount );
			newData.m_PictureX	= luadata->GetLua<int>( "frame/%s/%d/pic_x", frameName, frameCount );
			newData.m_PictureY	= luadata->GetLua<int>( "frame/%s/%d/pic_y", frameName, frameCount );
			newData.m_HeroAction	= ( HeroAction::e )luadata->GetLua<int>( "frame/%s/%d/state", frameName, frameCount );
			newData.m_Wait		= luadata->GetLua<int>( "frame/%s/%d/wait", frameName, frameCount );
			newData.m_NextFrameName	= luadata->GetLua<const char*>( "frame/%s/%d/next/1", frameName, frameCount );
			newData.m_NextFrameIndex = luadata->GetLua<int>( "frame/%s/%d/next/2", frameName, frameCount );
			newData.m_DVX		= ( float )luadata->GetLua<double>( "frame/%s/%d/dvx", frameName, frameCount );
			newData.m_DVY		= ( float )luadata->GetLua<double>( "frame/%s/%d/dvy", frameName, frameCount );
			newData.m_DVZ		= ( float )luadata->GetLua<double>( "frame/%s/%d/dvz", frameName, frameCount );
			newData.m_CenterX	= ( float )luadata->GetLua<double>( "frame/%s/%d/centerx", frameName, frameCount );
			newData.m_CenterY	= ( float )luadata->GetLua<double>( "frame/%s/%d/centery", frameName, frameCount );
			newData.m_ClearKeyQueue	= luadata->GetLua<int>( "frame/%s/%d/clear_key_queue", frameName, frameCount );

			if ( luadata->HasValue( "frame/%s/%d/consume/rule", frameName, frameCount ) )
			{
				newData.m_Consume.m_JumpRule = luadata->GetLua<int>( "frame/%s/%d/consume/rule", frameName, frameCount );
				newData.m_Consume.m_HP = luadata->GetLua<int>( "frame/%s/%d/consume/HP", frameName, frameCount );
				newData.m_Consume.m_MP = luadata->GetLua<int>( "frame/%s/%d/consume/MP", frameName, frameCount );
				newData.m_Consume.m_NotEnoughFrameName = luadata->GetLua<const char*>( "frame/%s/%d/consume/backFrame", frameName, frameCount );
				newData.m_Consume.m_NotEnoughFrame = luadata->GetLua<int>( "frame/%s/%d/consume/backFrameID", frameName, frameCount );
			}

			for ( int hitCount = 1;; ++hitCount )
			{
				if ( luadata->HasValue( "frame/%s/%d/hit/%d/1", frameName, frameCount, hitCount ) )
				{
					HitData hitData;
					// get hit key action "d>a"
					hitData.m_KeyQueue	= luadata->GetLua<const char*>( "frame/%s/%d/hit/%d/1", frameName, frameCount, hitCount );
					// get action name "many_punch"
					hitData.m_FrameName	= luadata->GetLua<const char*>( "frame/%s/%d/hit/%d/2", frameName, frameCount, hitCount );
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

			for ( int atkCount = 1;; ++atkCount )
			{
				if ( luadata->HasValue( "frame/%s/%d/attack/%d/kind", frameName, frameCount, atkCount ) )
				{
					Attack atk;
					atk.m_Kind	= luadata->GetLua<int>( "frame/%s/%d/attack/%d/kind", frameName, frameCount, atkCount );
					atk.m_Effect	= luadata->GetLua<int>( "frame/%s/%d/attack/%d/effect", frameName, frameCount, atkCount );
					atk.m_ZWidth	= ( float )luadata->GetLua<double>( "frame/%s/%d/attack/%d/zwidth", frameName, frameCount, atkCount );
					atk.m_DVX	= ( float )luadata->GetLua<double>( "frame/%s/%d/attack/%d/dvx", frameName, frameCount, atkCount );
					atk.m_DVY	= ( float )luadata->GetLua<double>( "frame/%s/%d/attack/%d/dvy", frameName, frameCount, atkCount );
					atk.m_DVZ	= ( float )luadata->GetLua<double>( "frame/%s/%d/attack/%d/dvz", frameName, frameCount, atkCount );
					atk.m_Fall	= luadata->GetLua<int>( "frame/%s/%d/attack/%d/fall", frameName, frameCount, atkCount );
					atk.m_AttackRest	= luadata->GetLua<int>( "frame/%s/%d/attack/%d/arest", frameName, frameCount, atkCount );
					atk.m_ReAttackRest	= luadata->GetLua<int>( "frame/%s/%d/attack/%d/reAttackRest", frameName, frameCount, atkCount );
					atk.m_Injury	= luadata->GetLua<int>( "frame/%s/%d/attack/%d/injury", frameName, frameCount, atkCount );
					atk.m_Strength	= luadata->GetLua<int>( "frame/%s/%d/attack/%d/strength", frameName, frameCount, atkCount );

					for ( int pointCount = 1;; ++pointCount )
					{
						if ( luadata->HasValue( "frame/%s/%d/attack/%d/points/%d/1",
						                        frameName, frameCount, atkCount, pointCount ) )
						{
							Vector2 vec2;
							vec2.x = ( float )luadata->GetLua<double>( "frame/%s/%d/attack/%d/points/%d/1",
							                frameName, frameCount, atkCount, pointCount );
							vec2.y = ( float )luadata->GetLua<double>( "frame/%s/%d/attack/%d/points/%d/2",
							                frameName, frameCount, atkCount, pointCount );
							atk.m_Area.AddPoint( vec2 );
						}
						else
						{
							break;
						}
					}

					newData.m_Attacks.push_back( atk );
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

			for ( int objCount = 1;; ++objCount )
			{
				if ( luadata->HasValue( "frame/%s/%d/newobjects/%d/name", frameName, frameCount, objCount ) )
				{
					Creation obj;
					obj.name = luadata->GetLua<const char*>( "frame/%s/%d/newobjects/%d/name", frameName, frameCount, objCount );
					obj.amount = luadata->GetLua<int>( "frame/%s/%d/newobjects/%d/amount", frameName, frameCount, objCount );
					obj.x = ( float )luadata->GetLua<double>( "frame/%s/%d/newobjects/%d/x", frameName, frameCount, objCount );
					obj.y = ( float )luadata->GetLua<double>( "frame/%s/%d/newobjects/%d/y", frameName, frameCount, objCount );
					obj.facing = luadata->GetLua<int>( "frame/%s/%d/newobjects/%d/facing", frameName, frameCount, objCount );
					obj.frame = luadata->GetLua<const char*>( "frame/%s/%d/newobjects/%d/frame", frameName, frameCount, objCount );
					obj.frameID = luadata->GetLua<int>( "frame/%s/%d/newobjects/%d/frameID", frameName, frameCount, objCount );
					obj.HP = luadata->GetLua<int>( "frame/%s/%d/newobjects/%d/hp", frameName, frameCount, objCount );
					obj.v0.x = ( float )luadata->GetLua<double>( "frame/%s/%d/newobjects/%d/dvx", frameName, frameCount, objCount );
					obj.v0.y = ( float )luadata->GetLua<double>( "frame/%s/%d/newobjects/%d/dvy", frameName, frameCount, objCount );
					obj.v0.z = ( float )luadata->GetLua<double>( "frame/%s/%d/newobjects/%d/dvz", frameName, frameCount, objCount );
					//ai
					newData.m_Creations.push_back( obj );
				}
				else
				{
					break;
				}
			}//*/

			if ( luadata->HasValue( "frame/%s/%d/sound", frameName, frameCount ) )
			{
				newData.m_sound = luadata->GetLua<const char*>( "frame/%s/%d/sound", frameName, frameCount );
			}

			fFrame->push_back( newData );
		}
	}
}

void HeroInfo::WriteLua( HeroInfo* hero , std::wstring filePath )
{
	//判斷結尾是否有.lua 沒有則加上
	if ( !( filePath.size() >= 4 &&
	                filePath[filePath.size() - 4] == '.' &&
	                filePath[filePath.size() - 3] == 'l' &&
	                filePath[filePath.size() - 2] == 'u' &&
	                filePath[filePath.size() - 1] == 'a' ) )
	{
		filePath.resize( filePath.size() + 4 );
		filePath[filePath.size() - 4] = '.';
		filePath[filePath.size() - 3] = 'l';
		filePath[filePath.size() - 2] = 'u';
		filePath[filePath.size() - 1] = 'a';
	}

	FILE* file = fopen( ConvStr::GetStr( filePath ).c_str(), "w" );
	fprintf( file, "require\t\"effect\"\n" );
	fprintf( file, "require\t\"action\"\n" );
	fprintf( file, "\n" );
	fprintf( file, "name\t=\t\"%s\"\n", hero->m_Name.c_str() );
	fprintf( file, "head\t=\t\"%s\"\n", hero->m_Headpic.c_str() );
	fprintf( file, "small\t=\t\"%s\"\n", hero->m_Smallpic.c_str() );
	fprintf( file, "\n" );
	fprintf( file, "file = {\n" );

	for ( int i = 0; i < hero->m_PictureDatas.size(); i++ )
	{
		std::string path = hero->m_PictureDatas[i].m_Path;
		bool autoclip = hero->m_PictureDatas[i].m_AutoClip;
		int w = hero->m_PictureDatas[i].m_Width;
		int h = hero->m_PictureDatas[i].m_Height;
		int row = hero->m_PictureDatas[i].m_Row;
		int col = hero->m_PictureDatas[i].m_Column;
		fprintf( file, "{path\t=\t\"%s\",\t", path.c_str() );
		fprintf( file, "autoclip\t=\t%d,\t", autoclip );
		fprintf( file, "w\t=\t%d,\t", w );
		fprintf( file, "h\t=\t%d,\t", h );
		fprintf( file, "row\t=\t%d,\t", row );
		fprintf( file, "col\t=\t%d,\t},\n", col );
	}

	fprintf( file, "}\n" );
	fprintf( file, "\n" );
	fprintf( file, "walking_speed\t=\t%f\n", hero->m_WalkingSpeed );
	fprintf( file, "walking_speedz\t=\t%f\n", hero->m_WalkingSpeedZ );
	fprintf( file, "running_speed\t=\t%f\n", hero->m_RunningSpeed );
	fprintf( file, "running_speedz\t=\t%f\n", hero->m_RunningSpeedZ );
	fprintf( file, "heavy_walking_speed\t=\t%f\n", hero->m_HeavyWalkingSpeed );
	fprintf( file, "heavy_walking_speedz\t=\t%f\n", hero->m_HeavyWalkingSpeedZ );
	fprintf( file, "heavy_running_speed\t=\t%f\n", hero->m_HeavyRunningSpeed );
	fprintf( file, "heavy_running_speedz\t=\t%f\n", hero->m_HeavyRunningSpeedZ );
	fprintf( file, "jump_height\t=\t%f\n", hero->m_JumpHeight );
	fprintf( file, "jump_distance\t=\t%f\n", hero->m_JumpDistance );
	fprintf( file, "jump_distancez\t=\t%f\n", hero->m_JumpDistanceZ );
	fprintf( file, "dash_height\t=\t%f\n", hero->m_DashHeight );
	fprintf( file, "dash_distance\t=\t%f\n", hero->m_DashDistance );
	fprintf( file, "dash_distancez\t=\t%f\n", hero->m_DashDistanceZ );
	fprintf( file, "rowing_height\t=\t%f\n", hero->m_RowingHeight );
	fprintf( file, "rowing_distance\t=\t%f\n", hero->m_RowingDistance );
	fclose( file );
}