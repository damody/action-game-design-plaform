#include "game\HeroInfo.h"
#include "..\..\..\AGDP\ConvStr.h"

std::wstring RevisePath( std::wstring path ); //修正路徑"\\"問題

HeroInfo::HeroInfo(): m_Name(), m_MaxHP( 500 ), m_MaxMP( 500 )
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

void HeroInfo::LoadData( LuaCell_Sptr luadata )
{
	m_LuaCell	= luadata;

	const char* tchars = luadata->GetLua<const char*>( "name" );
	m_Name		= std::wstring(tchars, tchars + strlen(tchars));
	
	tchars = luadata->GetLua<const char*>( "head" );
	m_Headpic	= std::wstring(tchars, tchars + strlen(tchars));

	//g_TextureManager.AddTexture(m_Headpic);
	tchars = luadata->GetLua<const char*>( "small" );
	m_Smallpic	= std::wstring(tchars, tchars + strlen(tchars));
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
			const char *tpath = luadata->GetLua<const char*>( "file/%d/path", i );
			pd.m_Path	= std::wstring(tpath, tpath + strlen(tpath));
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
		if ( luadata->HasValue( "air_crouch_map/%d/1", i ) )
		{
			CrouchData cd;
			int action = luadata->GetLua<int>( "air_crouch_map/%d/1", i );
			// get action name "many_punch"
			tchars = luadata->GetLua<const char*>( "air_crouch_map/%d/2", i );
			cd.m_FrameName	= std::wstring(tchars, tchars + strlen(tchars));
			// get frame offset
			cd.m_FrameOffset = luadata->GetLua<int>( "air_crouch_map/%d/3", i );
			m_CrouchMap[action] = cd;
		}
		else
		{
			break;
		}
	}

	strings tac = luadata->GetLuaTableKeys( "frame" );
	wstrings actions;
	for(strings::iterator i = tac.begin(); i != tac.end(); i++){
		actions.push_back( std::wstring( i->begin(), i->end() ) );
	}

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
			std::string tcs = std::string(actions[i].begin(), actions[i].end());
			const char* frameName	= tcs.c_str();
			const char *tmp;

			if ( !luadata->HasValue( "frame/%s/%d/pic_id", frameName, frameCount ) ) { break; }

			newData.m_FrameName	= actions[i];
			newData.m_FrameIndex = frameCount;
			newData.m_PictureID	= luadata->GetLua<int>( "frame/%s/%d/pic_id", frameName, frameCount );
			newData.m_PictureX	= luadata->GetLua<int>( "frame/%s/%d/pic_x", frameName, frameCount );
			newData.m_PictureY	= luadata->GetLua<int>( "frame/%s/%d/pic_y", frameName, frameCount );
			newData.m_HeroAction	= luadata->GetLua<int>( "frame/%s/%d/state", frameName, frameCount );
			newData.m_Wait		= luadata->GetLua<int>( "frame/%s/%d/wait", frameName, frameCount );
			tmp = luadata->GetLua<const char*>( "frame/%s/%d/next/1", frameName, frameCount );
			newData.m_NextFrameName	= std::wstring(tmp, tmp + strlen(tmp));
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
				tchars = luadata->GetLua<const char*>( "frame/%s/%d/consume/backFrame", frameName, frameCount );
				newData.m_Consume.m_NotEnoughFrameName = std::wstring(tchars, tchars + strlen(tchars));
				newData.m_Consume.m_NotEnoughFrame = luadata->GetLua<int>( "frame/%s/%d/consume/backFrameID", frameName, frameCount );
			}

			for ( int hitCount = 1;; ++hitCount )
			{
				if ( luadata->HasValue( "frame/%s/%d/hit/%d/1", frameName, frameCount, hitCount ) )
				{
					HitData hitData;
					const char *thit;
					// get hit key action "d>a"
					hitData.m_KeyQueue	= luadata->GetLua<const char*>( "frame/%s/%d/hit/%d/1", frameName, frameCount, hitCount );
					// get action name "many_punch"
					thit = luadata->GetLua<const char*>( "frame/%s/%d/hit/%d/2", frameName, frameCount, hitCount );
					hitData.m_FrameName	= std::wstring( thit, thit + strlen(thit) );
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
					atk.m_BreakDefend	= luadata->GetLua<int>( "frame/%s/%d/attack/%d/breakDefend", frameName, frameCount, atkCount );
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
					catchInfo.m_Strong = luadata->GetLua<int>( "frame/%s/%d/catch/%d/strong", frameName, frameCount, catchCount );
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
					const char* tcs = luadata->GetLua<const char*>( "frame/%s/%d/newobjects/%d/name", frameName, frameCount, objCount );
					obj.name = std ::wstring(tcs, tcs + strlen(tcs));
					obj.amount = luadata->GetLua<int>( "frame/%s/%d/newobjects/%d/amount", frameName, frameCount, objCount );
					obj.x = ( float )luadata->GetLua<double>( "frame/%s/%d/newobjects/%d/x", frameName, frameCount, objCount );
					obj.y = ( float )luadata->GetLua<double>( "frame/%s/%d/newobjects/%d/y", frameName, frameCount, objCount );
					obj.facing = luadata->GetLua<int>( "frame/%s/%d/newobjects/%d/facing", frameName, frameCount, objCount );
					tcs = luadata->GetLua<const char*>( "frame/%s/%d/newobjects/%d/frame", frameName, frameCount, objCount );
					obj.frame = std::wstring(tcs, tcs + strlen(tcs));
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
				const char* t= luadata->GetLua<const char*>( "frame/%s/%d/sound", frameName, frameCount );
				newData.m_sound = std::wstring( t, t + strlen(t) );
			}

			fFrame->push_back( newData );
		}
	}
	//holyk
	//Load Hero Function Lua path
	if ( luadata->HasValue( "heroFunctionLuaPath" ) )
	{
		tchars = luadata->GetLua<const char*>( "heroFunctionLuaPath" );
		m_HeroFunctionLuaPath = std::wstring(tchars, tchars + strlen(tchars));
	}
	else
	{
		m_HeroFunctionLuaPath = L"Script\\Hero\\HeroFunction.lua";
	}
	
}

void HeroInfo::WriteLua( HeroInfo* hero , std::wstring filePath )
{
	FILE* file = _wfopen(  filePath.c_str() , L"w" );
	wstrings frameTable;
	LuaMap am(L"Script/Action.lua", "Action");

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

	//-------------------------------------
	fwprintf( file, L"require\t\"Script/effect\"\n" );
	fwprintf( file, L"require\t\"Script/action\"\n" );
	fwprintf( file, L"\n" );
	//-------------------------------------
	fwprintf( file, L"name\t= \"%s\"\n", RevisePath( hero->m_Name ).c_str() );
	fwprintf( file, L"head\t= \"%s\"\n", RevisePath( hero->m_Headpic ).c_str() );
	fwprintf( file, L"small\t= \"%s\"\n", RevisePath( hero->m_Smallpic ).c_str() );
	fwprintf( file, L"\n" );
	//-------------------------------------
	fwprintf( file, L"file = {\n" );

	for ( int i = 0; i < ( int )hero->m_PictureDatas.size(); i++ )
	{
		std::wstring path = hero->m_PictureDatas[i].m_Path;
		bool autoclip = hero->m_PictureDatas[i].m_AutoClip;
		int w = hero->m_PictureDatas[i].m_Width;
		int h = hero->m_PictureDatas[i].m_Height;
		int row = hero->m_PictureDatas[i].m_Row;
		int col = hero->m_PictureDatas[i].m_Column;
		fwprintf( file, L"{path = \"%s\", ", RevisePath( path ).c_str() );
		fwprintf( file, L"autoclip = %d, ", autoclip );
		fwprintf( file, L"w = %d, ", w );
		fwprintf( file, L"h = %d, ", h );
		fwprintf( file, L"row = %d, ", row );
		fwprintf( file, L"col = %d },\n", col );
	}

	fwprintf( file, L"}\n" );
	fwprintf( file, L"\n" );
	//-------------------------------------
	fwprintf( file, L"walking_speed        = %f\n", hero->m_WalkingSpeed );
	fwprintf( file, L"walking_speedz       = %f\n", hero->m_WalkingSpeedZ );
	fwprintf( file, L"running_speed        = %f\n", hero->m_RunningSpeed );
	fwprintf( file, L"running_speedz       = %f\n", hero->m_RunningSpeedZ );
	fwprintf( file, L"heavy_walking_speed  = %f\n", hero->m_HeavyWalkingSpeed );
	fwprintf( file, L"heavy_walking_speedz = %f\n", hero->m_HeavyWalkingSpeedZ );
	fwprintf( file, L"heavy_running_speed  = %f\n", hero->m_HeavyRunningSpeed );
	fwprintf( file, L"heavy_running_speedz = %f\n", hero->m_HeavyRunningSpeedZ );
	fwprintf( file, L"jump_height          = %f\n", hero->m_JumpHeight );
	fwprintf( file, L"jump_distance        = %f\n", hero->m_JumpDistance );
	fwprintf( file, L"jump_distancez       = %f\n", hero->m_JumpDistanceZ );
	fwprintf( file, L"dash_height          = %f\n", hero->m_DashHeight );
	fwprintf( file, L"dash_distance        = %f\n", hero->m_DashDistance );
	fwprintf( file, L"dash_distancez       = %f\n", hero->m_DashDistanceZ );
	fwprintf( file, L"rowing_height        = %f\n", hero->m_RowingHeight );
	fwprintf( file, L"rowing_distance      = %f\n", hero->m_RowingDistance );
	fwprintf( file, L"\n" );
	//-------------------------------------
	fwprintf(file,L"air_crouch_map = {\n");
	//*
	for(CrouchMap::iterator icm = hero->m_CrouchMap.begin(); icm != hero->m_CrouchMap.end(); icm ++){
		fwprintf(file, L"{Action.%s, \"%s\", %d},\n", am[icm->first].c_str(), icm->second.m_FrameName.c_str(), icm->second.m_FrameOffset);
	}//*/
	fwprintf(file, L"}\n\n");
	//-------------------------------------
	fwprintf( file, L"frame = \n" );
	fwprintf( file, L"{\n" );

	for ( FramesMap::iterator iter = hero->m_FramesMap.begin(); iter != hero->m_FramesMap.end() ; ++iter )
	{
		frameTable.push_back( iter->first );
		fwprintf( file, L"\t%s = {},\n", iter->first.c_str() );
	}

	fwprintf( file, L"}\n" );
	fwprintf( file, L"\n" );

	//-------------------------------------
	for ( int tableCount = 0; ( int )tableCount < frameTable.size(); tableCount++ )
	{
		std::wstring tableName = frameTable[tableCount];

		for ( int frameCount = 0; ( int )frameCount < hero->m_FramesMap[tableName].size(); frameCount++ )
		{
			FrameInfo* frameInfo = &hero->m_FramesMap[tableName][frameCount];
			fwprintf( file, L"frame.%s[%d] =\n", frameTable[tableCount].c_str(), frameCount );
			fwprintf( file, L"{\n\t" );
			//----pic_id----
			fwprintf( file, L"pic_id = %d, ", frameInfo->m_PictureID );
			//----pic_x----
			fwprintf( file, L"pic_x = %d, ", frameInfo->m_PictureX );
			//----pic_y----
			fwprintf( file, L"pic_y = %d, ", frameInfo->m_PictureY );
			//----state----
			fwprintf( file, L"state = Action.%s, ", am[frameInfo->m_HeroAction].c_str());//HeroActionTable[frameInfo->m_HeroAction].c_str() );
			//----wait----
			fwprintf( file, L"wait = %d, ", frameInfo->m_Wait );
			//----next----
			fwprintf( file, L"next = { \"%s\", %d}, ", frameInfo->m_NextFrameName.c_str(), frameInfo->m_NextFrameIndex );
			fwprintf( file, L"\n\t" );
			//----dvx----
			fwprintf( file, L"dvx = %g, ", frameInfo->m_DVX );
			//----dvy----
			fwprintf( file, L"dvy = %g, ", frameInfo->m_DVY );
			//----dvz----
			fwprintf( file, L"dvz = %g, ", frameInfo->m_DVZ );
			//----centerx----
			fwprintf( file, L"centerx = %g, ", frameInfo->m_CenterX );
			//----centery----
			fwprintf( file, L"centery = %g, ", frameInfo->m_CenterY );
			//----clear_key_queue----
			fwprintf( file, L"clear_key_queue = %d, ", frameInfo->m_ClearKeyQueue );
			fwprintf( file, L"\n" );

			//----consume----
			fwprintf(file, L"\tconsume = { ");
			fwprintf(file, L"rule = %d, ", frameInfo->m_Consume.m_JumpRule);
			fwprintf(file, L"HP = %d, ", frameInfo->m_Consume.m_HP);
			fwprintf(file, L"MP = %d, ", frameInfo->m_Consume.m_MP);
			fwprintf(file, L"backFrame = \"%s\", ", frameInfo->m_Consume.m_NotEnoughFrameName.c_str());
			fwprintf(file, L"backFrameID = %d, ", frameInfo->m_Consume.m_NotEnoughFrame);
			fwprintf(file, L"},\n");

			//----Bodys----
			if ( !frameInfo->m_Bodys.empty() )
			{
				fwprintf( file, L"\tbody = {\n" );

				for ( Bodys::iterator bodyIter = frameInfo->m_Bodys.begin(); bodyIter != frameInfo->m_Bodys.end(); ++bodyIter )
				{
					const auto vec2sTemp = bodyIter->m_Area.Points();
					fwprintf( file, L"\t\t{" );
					fwprintf( file, L"kind = %d, ", bodyIter->m_Kind );
					fwprintf( file, L"points = { " );

					for ( int i = 0; i < ( int )vec2sTemp.size(); i++ )
					{
						fwprintf( file, L"{%g,%g}, ", vec2sTemp[i].x(), vec2sTemp[i].y() );
					}

					fwprintf( file, L"}, " );
					fwprintf( file, L"zwidth = %g", bodyIter->m_ZWidth );
					fwprintf( file, L"},\n" );
				}

				fwprintf( file, L"\t},\n" );
			}

			//----Attacks----
			if ( !frameInfo->m_Attacks.empty() )
			{
				fwprintf( file, L"\tattack = {\n" );

				for ( Attacks::iterator attackIter = frameInfo->m_Attacks.begin(); attackIter != frameInfo->m_Attacks.end(); ++attackIter )
				{
					const auto vec2sTemp = attackIter->m_Area.Points();
					fwprintf( file, L"\t\t{\n\t\t" );
					fwprintf( file, L"kind = %d, ", attackIter->m_Kind );
					fwprintf( file, L"effect = Effect.%s,", effectTable[attackIter->m_Effect].c_str() );
					fwprintf( file, L"\n\t\t" );
					fwprintf( file, L"points = { " );

					for ( int i = 0; i < ( int )vec2sTemp.size(); i++ )
					{
						fwprintf( file, L"{%g,%g}, ", vec2sTemp[i].x(), vec2sTemp[i].y() );
					}

					fwprintf( file, L"}, " );
					fwprintf( file, L"zwidth = %g,", attackIter->m_ZWidth );
					fwprintf( file, L"\n\t\t" );
					fwprintf( file, L"dvx = %g, ", attackIter->m_DVX );
					fwprintf( file, L"dvy = %g, ", attackIter->m_DVY );
					fwprintf( file, L"dvz = %g, ", attackIter->m_DVZ );
					fwprintf( file, L"fall = %d, ", attackIter->m_Fall );
					fwprintf( file, L"breakDefend = %d, ", attackIter->m_BreakDefend );
					fwprintf( file, L"\n\t\t" );
					fwprintf( file, L"arest = %d, ", attackIter->m_AttackRest );
					fwprintf( file, L"reAttackRest = %d, ", attackIter->m_ReAttackRest );
					fwprintf( file, L"injury = %d, ", attackIter->m_Injury );
					fwprintf( file, L"strength = %d, ", attackIter->m_Strength );
					fwprintf( file, L"\n\t\t},\n" );
				}

				fwprintf( file, L"\t},\n" );
			}

			//----HitDatas----
			if ( !frameInfo->m_HitDatas.empty() )
			{
				fprintf( file, "\thit = { " );

				for ( HitDatas::iterator hitIter = frameInfo->m_HitDatas.begin(); hitIter != frameInfo->m_HitDatas.end(); ++hitIter )
				{
					fwprintf( file, L"{" );
					fwprintf( file, L"\"%s\", ", std::wstring(hitIter->m_KeyQueue.begin(), hitIter->m_KeyQueue.end()).c_str() );
					fwprintf( file, L"\"%s\", ", hitIter->m_FrameName.c_str() );
					fwprintf( file, L"%d ", hitIter->m_FrameOffset );
					fwprintf( file, L"}, " );
				}

				fwprintf( file, L"},\n" );
			}

			//----CatchInfos----
			if ( !frameInfo->m_Catchs.empty() )
			{
				fwprintf( file, L"\tcatch = {\n" );

				for ( CatchInfos::iterator catchIter = frameInfo->m_Catchs.begin(); catchIter != frameInfo->m_Catchs.end(); ++catchIter )
				{
					const auto vec2sTemp = catchIter->m_Area.Points();
					fwprintf( file, L"\t\t{\n\t\t" );
					fwprintf( file, L"kind = %d, ", catchIter->m_Kind );
					fwprintf( file, L"strong = %d, ", catchIter->m_Strong );
					fwprintf( file, L"catchx = %g, ", catchIter->m_CatchPosition.x );
					fwprintf( file, L"catchy = %g, ", catchIter->m_CatchPosition.y );
					fwprintf( file, L"where = Body.%s, ", CatchPositionTable[catchIter->m_CatchWhere].c_str() );
					fwprintf( file, L"\n\t\t" );
					fwprintf( file, L"points = { " );

					for ( int i = 0; i < ( int )vec2sTemp.size(); i++ )
					{
						fwprintf( file, L"{%g,%g}, ", vec2sTemp[i].x(), vec2sTemp[i].y() );
					}

					fwprintf( file, L"}, " );
					fwprintf( file, L"zwidth = %g", catchIter->m_ZWidth );
					fwprintf( file, L"\n" );
					fwprintf( file, L"\t\t},\n" );
				}

				fwprintf( file, L"\t},\n" );
			}

			//----BeCatchs----
			/*To do*/
			//----BloodInfos----
			if ( !frameInfo->m_BloodInfos.empty() )
			{
				fprintf( file, "\tblood = {\n" );

				for ( BloodInfos::iterator bloodIter = frameInfo->m_BloodInfos.begin(); bloodIter != frameInfo->m_BloodInfos.end(); ++bloodIter )
				{
					fwprintf( file, L"\t\t{ " );
					fwprintf( file, L"scale = %g, ", bloodIter->m_Scale );
					fwprintf( file, L"x = %g, ", bloodIter->m_Position.x );
					fwprintf( file, L"y = %g, ", bloodIter->m_Position.y );
					fwprintf( file, L"value = %g, ", bloodIter->m_EnableValue );
					fwprintf( file, L"},\n" );
				}

				fwprintf( file, L"\t},\n" );
			}

			//----Creations----
			if ( !frameInfo->m_Creations.empty() )
			{
				fwprintf( file, L"\tnewobjects = {\n" );

				for ( Creations::iterator objIter = frameInfo->m_Creations.begin(); objIter != frameInfo->m_Creations.end(); ++objIter )
				{
					fwprintf( file, L"\t\t{\n\t\t" );
					fwprintf( file, L"name = \"%s\", ", objIter->name.c_str() );
					fwprintf( file, L"amount = %d, ", objIter->amount );
					fwprintf( file, L"x = %g, ", objIter->x );
					fwprintf( file, L"y = %g, ", objIter->y );
					fwprintf( file, L"facing = %d, ", objIter->facing );
					fwprintf( file, L"\n\t\t" );
					fwprintf( file, L"frame = \"%s\", ", objIter->frame.c_str() );
					fwprintf( file, L"frameID = %d, ", objIter->frameID );
					fwprintf( file, L"hp = %d, ", objIter->HP );
					/*AI保留*///fprintf(file, "ai\t=\t%d,\t",objIter->AI);
					fwprintf( file, L"dvx = %g, ", objIter->v0.x );
					fwprintf( file, L"dvy = %g, ", objIter->v0.y );
					fwprintf( file, L"dvz = %g, ", objIter->v0.z );
					fwprintf( file, L"\n\t\t},\n" );
				}

				fwprintf( file, L"\t},\n" );
			}

			//----sound----
			if ( !frameInfo->m_sound.empty() )
			{
				fwprintf( file, L"\tsound = \"%s\",\n", RevisePath(frameInfo->m_sound).c_str() );
			}

			fwprintf( file, L"}\n" );
			fwprintf( file, L"\n" );
		}
	}

	fclose( file );
}

std::wstring RevisePath( std::wstring path ) //修正路徑"\\"問題
{
	int idx = 0;
	int temp = 0;

	while ( true )
	{
		int idx = path.find( L"\\", temp );

		if ( idx == -1 )
		{
			break;
		}

		path.insert( idx, L"\\" );
		temp = idx + 2;
	}

	return path;
}