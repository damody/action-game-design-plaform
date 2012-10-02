#include "StdGame.h"
#include "Background.h"
#include "global.h"

bool Background::CheckDataVaild( LuaCell_Sptr luadata )
{
	bool testOK = true;
	testOK &= luadata->HasValue( "name" );

	// read space bounding
	for ( int i = 1;; ++i )
	{
		if ( luadata->HasValue( "space_bounding/%d/xmin", i ) )
		{
			testOK &= luadata->HasValue( "space_bounding/%d/xmin", i );
			testOK &= luadata->HasValue( "space_bounding/%d/ymin", i );
			testOK &= luadata->HasValue( "space_bounding/%d/zmin", i );
			testOK &= luadata->HasValue( "space_bounding/%d/xmax", i );
			testOK &= luadata->HasValue( "space_bounding/%d/ymax", i );
			testOK &= luadata->HasValue( "space_bounding/%d/zmax", i );
		}
		else
		{
			break;
		}
	}

	if ( !testOK ) { return testOK; }

	// read ban bounding
	for ( int i = 1;; ++i )
	{
		if ( luadata->HasValue( "ban_bounding/%d/xmin", i ) )
		{
			testOK &= luadata->HasValue( "ban_bounding/%d/xmin", i );
			testOK &= luadata->HasValue( "ban_bounding/%d/ymin", i );
			testOK &= luadata->HasValue( "ban_bounding/%d/zmin", i );
			testOK &= luadata->HasValue( "ban_bounding/%d/xmax", i );
			testOK &= luadata->HasValue( "ban_bounding/%d/ymax", i );
			testOK &= luadata->HasValue( "ban_bounding/%d/zmax", i );
		}
		else
		{
			break;
		}
	}

	if ( !testOK ) { return testOK; }

	// read BGLayers
	for ( int i = 1;; ++i )
	{
		if ( luadata->HasValue( "layer/%d/picture_path", i ) )
		{
			testOK &= luadata->HasValue( "layer/%d/picture_path", i );
			testOK &= luadata->HasValue( "layer/%d/ground", i );
			testOK &= luadata->HasValue( "layer/%d/x", i );
			testOK &= luadata->HasValue( "layer/%d/y", i );
			testOK &= luadata->HasValue( "layer/%d/z", i );
			testOK &= luadata->HasValue( "layer/%d/w", i );
			testOK &= luadata->HasValue( "layer/%d/h", i );
			testOK &= luadata->HasValue( "layer/%d/loop_distance", i );
			testOK &= luadata->HasValue( "layer/%d/timeline", i );
			testOK &= luadata->HasValue( "layer/%d/time_start", i );
			testOK &= luadata->HasValue( "layer/%d/time_end", i );
		}
		else
		{
			break;
		}
	}

	if ( !testOK ) { return testOK; }

	// read color rect
	for ( int i = 1;; ++i )
	{
		if ( luadata->HasValue( "color_rect/%d/r", i ) )
		{
			testOK &= luadata->HasValue( "color_rect/%d/r", i );
			testOK &= luadata->HasValue( "color_rect/%d/g", i );
			testOK &= luadata->HasValue( "color_rect/%d/b", i );
			testOK &= luadata->HasValue( "color_rect/%d/a", i );
			testOK &= luadata->HasValue( "color_rect/%d/ground", i );
			testOK &= luadata->HasValue( "color_rect/%d/x", i );
			testOK &= luadata->HasValue( "color_rect/%d/y", i );
			testOK &= luadata->HasValue( "color_rect/%d/z", i );
			testOK &= luadata->HasValue( "color_rect/%d/w", i );
			testOK &= luadata->HasValue( "color_rect/%d/h", i );
		}
		else
		{
			break;
		}
	}

	if ( !testOK ) { return testOK; }

	// read ParallelLights
	for ( int i = 1;; ++i )
	{
		if ( luadata->HasValue( "parallel_light/%d/x", i ) )
		{
			testOK &= luadata->HasValue( "parallel_light/%d/x", i );
			testOK &= luadata->HasValue( "parallel_light/%d/y", i );
			testOK &= luadata->HasValue( "parallel_light/%d/z", i );
			testOK &= luadata->HasValue( "parallel_light/%d/light", i );
			testOK &= luadata->HasValue( "parallel_light/%d/timeline", i );
			testOK &= luadata->HasValue( "parallel_light/%d/time_start", i );
			testOK &= luadata->HasValue( "parallel_light/%d/time_end", i );
		}
		else
		{
			break;
		}
	}

	return testOK;
}

void Background::LoadData( LuaCell_Sptr luadata )
{
	m_LuaCell	= luadata;
	m_Name		= luadata->GetLua<const char*>( "name" );
	m_Width		= ( float )luadata->GetLua<double>( "width" );
	m_TimeLine	= luadata->GetLua<int>( "timeline" );
	m_Gravity	= ( float )luadata->GetLua<double>( "gravity" );
	m_Friction	= ( float )luadata->GetLua<double>( "friction" );

	// read space bounding
	for ( int i = 1;; ++i )
	{
		if ( luadata->HasValue( "space_bounding/%d/xmin", i ) )
		{
			AxisAlignedBox aabb;
			aabb.setMinimumX( ( float )luadata->GetLua<double>( "space_bounding/%d/xmin", i ) );
			aabb.setMinimumY( ( float )luadata->GetLua<double>( "space_bounding/%d/ymin", i ) );
			aabb.setMinimumZ( ( float )luadata->GetLua<double>( "space_bounding/%d/zmin", i ) );
			aabb.setMaximumX( ( float )luadata->GetLua<double>( "space_bounding/%d/xmax", i ) );
			aabb.setMaximumY( ( float )luadata->GetLua<double>( "space_bounding/%d/ymax", i ) );
			aabb.setMaximumZ( ( float )luadata->GetLua<double>( "space_bounding/%d/zmax", i ) );
			m_SpaceBounding.push_back( aabb );
		}
		else
		{
			break;
		}
	}

	// read ban bounding
	for ( int i = 1;; ++i )
	{
		if ( luadata->HasValue( "ban_bounding/%d/xmin", i ) )
		{
			AxisAlignedBox aabb;
			aabb.setMinimumX( ( float )luadata->GetLua<double>( "ban_bounding/%d/xmin", i ) );
			aabb.setMinimumY( ( float )luadata->GetLua<double>( "ban_bounding/%d/ymin", i ) );
			aabb.setMinimumZ( ( float )luadata->GetLua<double>( "ban_bounding/%d/zmin", i ) );
			aabb.setMaximumX( ( float )luadata->GetLua<double>( "ban_bounding/%d/xmax", i ) );
			aabb.setMaximumY( ( float )luadata->GetLua<double>( "ban_bounding/%d/ymax", i ) );
			aabb.setMaximumZ( ( float )luadata->GetLua<double>( "ban_bounding/%d/zmax", i ) );
			m_BanBounding.push_back( aabb );
		}
		else
		{
			break;
		}
	}

	// read BGLayers
	for ( int i = 1;; ++i )
	{
		if ( luadata->HasValue( "layer/%d/picture_path", i ) )
		{
			BGLayer bgl;
			bgl.m_PicturePath	= luadata->GetLua<const char*>( "layer/%d/picture_path", i );
			bgl.m_Rotation.x        = ( float )luadata->GetLua<double>( "layer/%d/rx", i );
			bgl.m_Rotation.y        = ( float )luadata->GetLua<double>( "layer/%d/ry", i );
			bgl.m_Rotation.z        = ( float )luadata->GetLua<double>( "layer/%d/rz", i );
			bgl.m_Position.x	= ( float )luadata->GetLua<double>( "layer/%d/x", i );
			bgl.m_Position.y	= ( float )luadata->GetLua<double>( "layer/%d/y", i );
			bgl.m_Position.z	= ( float )luadata->GetLua<double>( "layer/%d/z", i );
			bgl.m_Width		= ( float )luadata->GetLua<double>( "layer/%d/w", i );
			bgl.m_Height		= ( float )luadata->GetLua<double>( "layer/%d/h", i );
			bgl.m_LoopDistance	= ( float )luadata->GetLua<int>( "layer/%d/loop_distance", i );
			bgl.m_TimeLine		= luadata->GetLua<int>( "layer/%d/timeline", i );
			bgl.m_TimeStart		= luadata->GetLua<int>( "layer/%d/time_start", i );
			bgl.m_TimeEnd		= luadata->GetLua<int>( "layer/%d/time_end", i );
			bgl.m_PicID		= g_TextureManager.AddTexture( bgl.m_PicturePath );
			m_BGLayers.push_back( bgl );
		}
		else
		{
			break;
		}
	}

	// read color rect
	for ( int i = 1;; ++i )
	{
		if ( luadata->HasValue( "color_rect/%d/r", i ) )
		{
			ColorRect cr;
			cr.m_Color[0]	= ( float )luadata->GetLua<double>( "color_rect/%d/r", i );
			cr.m_Color[1]	= ( float )luadata->GetLua<double>( "color_rect/%d/g", i );
			cr.m_Color[2]	= ( float )luadata->GetLua<double>( "color_rect/%d/b", i );
			cr.m_Color[3]	= ( float )luadata->GetLua<double>( "color_rect/%d/a", i );
			cr.m_Rotation.x = ( float )luadata->GetLua<double>( "color_rect/%d/rx", i );
			cr.m_Rotation.y = ( float )luadata->GetLua<double>( "color_rect/%d/ry", i );
			cr.m_Rotation.z = ( float )luadata->GetLua<double>( "color_rect/%d/rz", i );
			cr.m_Position.x	= ( float )luadata->GetLua<double>( "color_rect/%d/x", i );
			cr.m_Position.y	= ( float )luadata->GetLua<double>( "color_rect/%d/y", i );
			cr.m_Position.z	= ( float )luadata->GetLua<double>( "color_rect/%d/z", i );
			cr.m_Width	= ( float )luadata->GetLua<double>( "color_rect/%d/w", i );
			cr.m_Height	= ( float )luadata->GetLua<double>( "color_rect/%d/h", i );
			m_ColorRects.push_back( cr );
		}
		else
		{
			break;
		}
	}

	// read ParallelLights
	for ( int i = 1;; ++i )
	{
		if ( luadata->HasValue( "parallel_light/%d/x", i ) )
		{
			ParallelLight pl;
			pl.m_Direction.x	= ( float )luadata->GetLua<double>( "parallel_light/%d/x", i );
			pl.m_Direction.y	= ( float )luadata->GetLua<double>( "parallel_light/%d/y", i );
			pl.m_Direction.z	= ( float )luadata->GetLua<double>( "parallel_light/%d/z", i );
			pl.m_LightStrength	= ( float )luadata->GetLua<double>( "parallel_light/%d/light", i );
			pl.m_TimeStart		= luadata->GetLua<int>( "parallel_light/%d/time_start", i );
			m_ParallelLights.push_back( pl );
		}
		else
		{
			break;
		}
	}

	for ( ParallelLights::iterator it = m_ParallelLights.begin(); it != m_ParallelLights.end(); it++ )
	{
		m_LightPath.m_Direction.AddPoint( ( float )it->m_TimeStart, it->m_Direction );
		m_LightPath.m_LightStrength.AddPoint( ( float )it->m_TimeStart, Vector3( it->m_LightStrength, 0.0f, 0.0f ) );
	}
}

void Background::Update( float dt )
{
	m_CurrentLight.m_Direction = m_LightPath.m_Direction.GetValue( ( float )( g_Time % m_TimeLine ) );
	m_CurrentLight.m_LightStrength = m_LightPath.m_LightStrength.GetValue( ( float )( g_Time % m_TimeLine ) ).x;
}

void Background::BuildPoint()
{
	m_CRVerteices.clear();
	float cut =(float) g_Camera->Offsidelength() * 0.19;

	for ( ColorRects::iterator it = m_ColorRects.begin(); it != m_ColorRects.end(); it++ )
	{
		int i = 0;

		for ( float w = it->m_Width; w > 0 ; w -= cut, i++ )
		{
			if ( g_Camera.get() )
			{
				CRVertex crv;
				crv.position.x = it->m_Position.x + i * cut;
				crv.position.y = it->m_Position.y;
				crv.position.z = it->m_Position.z;
				int offset = g_Camera->Offside( crv.position );

				if ( offset == 1 )
				{
					break;
				}
				else  if ( offset == -1 )
				{
					continue;
				}

				crv.rotation.x = it->m_Rotation.x;
				crv.rotation.y = it->m_Rotation.y;
				crv.rotation.z = it->m_Rotation.z;
				crv.size.x = ( w - cut > 0 ? cut : w );
				crv.size.y = it->m_Height;
				crv.color.x = it->m_Color.x;
				crv.color.y = it->m_Color.y;
				crv.color.z = it->m_Color.z;
				crv.color.w = it->m_Color.w;
				m_CRVerteices.push_back( crv );
			}
		}
	}

	m_BGVerteices.clear();
	m_DrawVertexGroups.clear();
	int vertexCount = 0, count = 0;

	for ( BGLayers::iterator it = m_BGLayers.begin(); it != m_BGLayers.end(); it++ )
	{
		if ( g_Time % it->m_TimeLine < it->m_TimeStart ) { continue; }

		if ( g_Time % it->m_TimeLine > it->m_TimeEnd ) { continue; }

		DrawVertexGroup dvg = {};
		dvg.texture = g_TextureManager.GetTexture( it->m_PicID );
		vertexCount = 0;
		dvg.StartVertexLocation = count;
		int d = 0;

		do
		{
			if ( g_Camera.get() )
			{
				BGVertex bgv;
				bgv.position.x = it->m_Position.x + d * it->m_LoopDistance;
				bgv.position.y = it->m_Position.y ;
				bgv.position.z = it->m_Position.z;

				if ( it->m_Width < g_Camera->Offsidelength() )
				{
					int offside = g_Camera->Offside( bgv.position );

					if ( offside == 1 )
					{
						break;
					}
					else if ( offside == -1 )
					{
						d++;

						if ( bgv.position.x = it->m_Position.x + d * it->m_LoopDistance > m_Width ) { break; }
						else { continue; }
					}
				}

				bgv.size.x     = it->m_Width  ;
				bgv.size.y     = it->m_Height ;
				bgv.rotation.x = it->m_Rotation.x;
				bgv.rotation.y = it->m_Rotation.y;
				bgv.rotation.z = it->m_Rotation.z;
				m_BGVerteices.push_back( bgv );
				++vertexCount;
				++count;
				d++;

				if ( bgv.position.x = it->m_Position.x + d * it->m_LoopDistance > m_Width )
				{
					break;
				}
			}
		}
		while ( it->m_LoopDistance > 0 );

		dvg.VertexCount = vertexCount;
		m_DrawVertexGroups.push_back( dvg );
	}
}



Vector3 Background::AlignmentSpace( const Vector3& pIn )
{
	Vector3 pOut  = pIn;
	float   error = 999999.9f;

	for ( AxisAlignedBoxs::iterator it = m_SpaceBounding.begin(); it != m_SpaceBounding.end() ; it++ )
	{
		bool inBox = true;
		Vector3 temp = pIn;
		Vector3 min = it->getMinimum();
		Vector3 max = it->getMaximum();

		if ( pIn.x < min.x )
		{
			inBox = false;
			temp.x = min.x;
		}
		else if ( pIn.x > max.x )
		{
			inBox = false;
			temp.x = max.x;
		}

		if ( pIn.y < min.y )
		{
			inBox = false;
			temp.y = min.y;
		}
		else if ( pIn.y > max.y )
		{
			inBox = false;
			temp.y = max.y;
		}

		if ( pIn.z < min.z )
		{
			inBox = false;
			temp.z = min.z;
		}
		else if ( pIn.z > max.z )
		{
			inBox = false;
			temp.z = max.z;
		}

		if ( inBox )
		{
			return pIn;
		}

		float t = pIn.distance( temp );

		if ( t < error )
		{
			error = t;
			pOut = temp;
		}
	}

	return pOut;
}

bool Background::InSpace( const Vector3& pIn )
{
	for ( AxisAlignedBoxs::iterator it = m_SpaceBounding.begin(); it != m_SpaceBounding.end() ; it++ )
	{
		bool inBox = true;
		Vector3 min = it->getMinimum();
		Vector3 max = it->getMaximum();

		if ( pIn.x < min.x || pIn.x > max.x )
		{
			inBox = false;
		}

		if ( pIn.y < min.y || pIn.y > max.y )
		{
			inBox = false;
		}

		if ( pIn.z < min.z || pIn.z > max.z )
		{
			inBox = false;
		}

		if ( inBox )
		{
			return true;
		}
	}

	return false;
}

bool Background::InBan( const Vector3& pIn )
{
	for ( AxisAlignedBoxs::iterator it = m_BanBounding.begin(); it != m_BanBounding.end() ; it++ )
	{
		bool inBox = true;
		Vector3 min = it->getMinimum();
		Vector3 max = it->getMaximum();

		if ( pIn.x > min.x && pIn.x < max.x
		                && pIn.y > min.y && pIn.y < max.y
		                && pIn.z > min.z && pIn.z < max.z
		   )
		{
			return true;
		}
	}

	return false;
}

Vector3 Background::AlignmentBan( const Vector3& pIn , const Vector3& p0 )
{
	if ( InBan( pIn ) )
	{
		if ( !InBan( Vector3( p0.x, pIn.y, pIn.z ) ) )
		{
			return Vector3( p0.x, pIn.y, pIn.z );
		}

		if ( !InBan( Vector3( pIn.x, pIn.y, p0.z ) ) )
		{
			return Vector3( pIn.x, pIn.y, p0.z );
		}

		if ( !InBan( Vector3( pIn.x, p0.y, pIn.z ) ) )
		{
			return Vector3( pIn.x, p0.y, pIn.z );
		}
	}

	return pIn;
}

float Background::Width()
{
	return m_Width;
}

float Background::Gravity()
{
	return m_Gravity;
}

ParallelLight Background::GetParallelLight()
{
	return m_CurrentLight;
}

AxisAlignedBoxs::iterator Background::InWhichBan( const Vector3& pIn )
{
	for ( AxisAlignedBoxs::iterator it = m_BanBounding.begin(); it != m_BanBounding.end() ; it++ )
	{
		if ( it->contains( pIn ) )
		{
			return it;
		}

		/*
		Vector3 min = it->getMinimum();
		Vector3 max = it->getMaximum();

		if(pIn.x >= min.x && pIn.x <= max.x
			&& pIn.y >= min.y && pIn.y <= max.y
			&& pIn.z >= min.z && pIn.z <= max.z
			){
				return it;
		}//*/
	}

	return m_BanBounding.end();
}

AxisAlignedBoxs::iterator Background::InWhichSpace( const Vector3& pIn )
{
	for ( AxisAlignedBoxs::iterator it = m_SpaceBounding.begin(); it != m_SpaceBounding.end() ; it++ )
	{
		Vector3 min = it->getMinimum();
		Vector3 max = it->getMaximum();

		if ( pIn.x > min.x && pIn.x < max.x && pIn.z > min.z && pIn.z < max.z )
		{
			return it;
		}
	}

	return m_SpaceBounding.end();
}

int Background::AboveSpaceBottom( const Vector3& pIn )
{
	for ( AxisAlignedBoxs::iterator it = m_SpaceBounding.begin(); it != m_SpaceBounding.end() ; it++ )
	{
		Vector3 min = it->getMinimum();
		Vector3 max = it->getMaximum();

		if ( pIn.x > min.x && pIn.x < max.x && pIn.z > min.z && pIn.z < max.z )
		{
			if ( pIn.y > min.y )
			{
				return 1;
			}
			else if ( pIn.y < min.y )
			{
				return -1;
			}
			else
			{
				return 0;
			}
		}
	}

	return 2;
}

int Background::AboveBanTop( const Vector3& pIn )
{
	for ( AxisAlignedBoxs::iterator it = m_BanBounding.begin(); it != m_BanBounding.end() ; it++ )
	{
		Vector3 min = it->getMinimum();
		Vector3 max = it->getMaximum();

		if ( pIn.x > min.x && pIn.x < max.x && pIn.z > min.z && pIn.z < max.z )
		{
			if ( pIn.y > max.y )
			{
				return 1;
			}
			else if ( pIn.y < max.y )
			{
				return -1;
			}
			else
			{
				return 0;
			}
		}
	}

	return 2;
}

int Background::AboveGround( const Vector3& pIn )
{
	int b = AboveBanTop( pIn ), p = AboveSpaceBottom( pIn );

	if ( b == -1 || p == -1 )
	{
		return -1;
	}
	else if ( b == 0 || p == 0 )
	{
		return 0;
	}
	else if ( b == 1 || p == 1 )
	{
		return 1;
	}
	else { return 2; }
}

bool Background::isOnGround( const Vector3& pIn , const Vector3& dp, Vector3* pOut )
{
	Vector3 fp = pIn;
	int n = 3;			//取樣數，必須大於或等於二
	int d;				//判斷結果

	for ( int i = 0; i < n; i++ )
	{
		fp += dp / ( float )n;
		d = AboveGround( fp );

		if ( d == -1 || d == 2 )
		{
			break;
		}
	}

	if ( d == 0 )
	{
		//地面
		if ( pOut != NULL )
		{
			*pOut = fp;
		}

		return true;
	}
	else if ( d == 1 )
	{
		//空中
		if ( pOut != NULL )
		{
			*pOut = fp;
		}

		return false;
	}
	else if ( d == -1 )
	{
		//地底
		AxisAlignedBoxs::iterator ib = InWhichBan( fp );
		AxisAlignedBoxs::iterator ip = InWhichSpace( fp );

		if ( ib != m_BanBounding.end() )
		{
			if ( pIn.y > ib->getMaximum().y )
			{
				fp.y = ib->getMaximum().y;

				if ( pOut != NULL )
				{
					*pOut = fp;
				}

				return true;
			}
			else
			{
				if ( pIn.x >= ib->getMaximum().x )
				{
					fp.x = ib->getMaximum().x;
				}
				else if ( pIn.x <= ib->getMinimum().x )
				{
					fp.x = ib->getMinimum().x;
				}
				else if ( pIn.z >= ib->getMaximum().z )
				{
					fp.z = ib->getMaximum().z;
				}
				else if ( pIn.z <= ib->getMinimum().z )
				{
					fp.z = ib->getMinimum().z;
				}

				if ( pOut != NULL )
				{
					*pOut = fp;
				}
			}
		}

		if ( ip != m_SpaceBounding.end() )
		{
			if ( fp.y <= ip->getMinimum().y )
			{
				fp.y = ip->getMinimum().y;

				if ( pOut != NULL )
				{
					*pOut = fp;
				}

				return true;
			}
			else
			{
				if ( fp.y > ip->getMaximum().y )
				{
					fp.y = ip->getMaximum().y;
				}

				if ( pOut != NULL )
				{
					*pOut = fp;
				}

				return false;
			}
		}
		else
		{
			printf( "error!\n" );
			system( "pause" );

			if ( pOut != NULL )
			{
				*pOut = fp - dp / ( float )n;
			}

			return false;
		}
	}
	else
	{
		//界外
		AxisAlignedBoxs::iterator ip = InWhichSpace( pIn );

		if ( fp.x >= ip->getMaximum().x )
		{
			fp.x = ip->getMaximum().x - 1.0f;
		}

		if ( fp.z >= ip->getMaximum().z )
		{
			fp.z = ip->getMaximum().z - 1.0f;
		}

		if ( fp.x <= ip->getMinimum().x )
		{
			fp.x = ip->getMinimum().x + 1.0f;
		}

		if ( fp.z <= ip->getMinimum().z )
		{
			fp.z = ip->getMinimum().z + 1.0f;
		}

		int d = AboveGround( fp );

		if ( d == 0 )
		{
			if ( pOut != NULL )
			{
				*pOut = fp;
			}

			return true;
		}
		else if ( d == 1 )
		{
			if ( pOut != NULL )
			{
				*pOut = fp;
			}

			return false;
		}
		else if ( d == -1 )
		{
			fp.y = ip->getMinimum().y;

			/*
			ip = InWhichBan(fp);
			if(ip != m_BanBounding.end()){

			}
			//*/
			if ( pOut != NULL )
			{
				*pOut = fp;
			}

			return true;
		}
		else
		{
			printf( "error2!\n" );
			system( "pause" );
		}
	}
}
