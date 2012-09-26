#pragma once
#include <string>
#include <map>
#include "Lua/LuaCell.h"

class LuaMap : public std::map<int, std::string>
{
public:
	LuaMap() {}
	LuaMap( LuaCell_Sptr lsptr, std::string tableName )
	{
		strings keys = lsptr->GetLuaTableKeys( tableName.c_str() );
		this->clear();

		for ( int i = 0; i < ( int )keys.size(); i++ )
		{
			int _tmpKey = lsptr->GetLua<int>( "%s/%s", tableName.c_str(), keys[i].c_str() );
			( *this )[_tmpKey] = keys[i];
		}
	}
	LuaMap( std::string path, std::string tableName )
	{
		LuaCell_Sptr lsptr = LuaCell_Sptr( new LuaCell );
		lsptr->InputLuaFile( path.c_str() );
		strings keys = lsptr->GetLuaTableKeys( tableName.c_str() );
		this->clear();

		for ( int i = 0; i < ( int )keys.size(); i++ )
		{
			int _tmpKey = lsptr->GetLua<int>( "%s/%s", tableName.c_str(), keys[i].c_str() );
			( *this )[_tmpKey] = keys[i];
		}
	}
	~LuaMap() {}

	void LoadData( LuaCell_Sptr lsptr, std::string tableName )
	{
		strings keys = lsptr->GetLuaTableKeys( tableName.c_str() );
		this->clear();

		for ( int i = 0; i < ( int )keys.size(); i++ )
		{
			int _tmpKey = lsptr->GetLua<int>( "%s/%s", tableName.c_str(), keys[i].c_str() );
			( *this )[_tmpKey] = keys[i];
		}
	}
	void LoadData( std::string path, std::string tableName )
	{
		LuaCell_Sptr lsptr = LuaCell_Sptr( new LuaCell );
		lsptr->InputLuaFile( path.c_str() );
		strings keys = lsptr->GetLuaTableKeys( tableName.c_str() );
		this->clear();

		for ( int i = 0; i < ( int )keys.size(); i++ )
		{
			int _tmpKey = lsptr->GetLua<int>( "%s/%s", tableName.c_str(), keys[i].c_str() );
			( *this )[_tmpKey] = keys[i];
		}
	}

	int FindKey( std::string strValue )
	{
		for( std::map<int, std::string>::iterator i = this->begin(); i != this->end() ; i++ )
		{
			if( ! strcmp( i->second.c_str(), strValue.c_str() ) ) return i->first;
		}
		return -1;
	}

	static bool WriteLua ( std::string path, std::string formatString, ... )
	{
		//
		if ( !( path.size() >= 4 &&
			path[path.size() - 4] == '.' &&
			path[path.size() - 3] == 'l' &&
			path[path.size() - 2] == 'u' &&
			path[path.size() - 1] == 'a' ) )
		{
			path.resize( path.size() + 4 );
			path[path.size() - 4] = '.';
			path[path.size() - 3] = 'l';
			path[path.size() - 2] = 'u';
			path[path.size() - 1] = 'a';
		}
		FILE* _file = fopen( path.c_str(), "w" );

		fprintf( _file, "function protect_table (tbl)\n\treturn setmetatable ({},\n\t{\n\t__index = tbl,\n\t__newindex = funtion (t, n, v)\n\tend=n=t})\nend\n" );
		fprintf( _file, "count = -1;\nfunction GetEnum()\n\tcount = count + 1;\n\treturn count;\nend\n" );

		const char* _formatString = formatString.c_str();
		int argc = 0;
		for( int i = 0; i<(int)formatString.size() ; i++ ) 
		{
			if( _formatString[i] == '%' ) argc++;
		}

		va_list _formatVa;
		va_start( _formatVa, formatString );
		std::vector<char> _charStack;
		std::vector<std::string> _tableStack;
		for( int i = 0; i < (int)formatString.size(); i++ )
		{
			if( _formatString[i] == '(' )
			{
				char* _str = ( char* )malloc( sizeof( char )*( _charStack.size()+1 ) );
				strcpy( _str, &_charStack[0] );
				_str[_charStack.size()] = '\0';

				std::string _preName( "" );
				for( int i = 0; i < _tableStack.size(); i++ )
				{
					if( i ) _preName += '.';
					_preName += _tableStack[i];
				}
				if( strcmp( _preName.c_str() , "" )) fprintf( _file, "%s.%s = {}\n", _preName.c_str(), _str);
				else fprintf( _file, "%s = {}\n", _str);

				_tableStack.push_back( std::string( _str ) );
				_charStack.clear();
				//free( _str );
			}
			else if( _formatString[i] == ')' )
			{
				_tableStack.pop_back();
			}
			else if( _formatString[i] == '%' && i+1 < formatString.length() && _formatString[i+1] == 'm')
			{
				fprintf( _file, "count = -1;\n");
				LuaMap _tableMap = *va_arg( _formatVa, LuaMap* );
				
				std::string _preName( "" );
				for( int i = 0; i < _tableStack.size(); i++ )
				{
					if( i ) _preName += '.';
					_preName += _tableStack[i];
				}
				if( strcmp( _preName.c_str() , "" )) 
				{
					for( std::map<int, std::string>::iterator j = _tableMap.begin(); j != _tableMap.end() ; j++ )
					fprintf( _file, "%s.%s = GetEnum()\n", _preName.c_str(), j->second.c_str());
				}
				else 
				{
					for( std::map<int, std::string>::iterator j = _tableMap.begin(); j != _tableMap.end() ; j++ )
					fprintf( _file, "%s = GetEnum()\n", j->second.c_str());
				}

				i++;
			}
			else
			{
				_charStack.push_back( _formatString[i] );
			}
		}

		va_end( _formatVa );
		fclose( _file );
		return TRUE;
	}
};
//typedef LuaMap HeroAction;

const std::string HeroActionTable[] =
{
	"Standing",
	"Walking",
	"Running",
	"StopRunning",
	"HeavyWeaponWalk",
	"HeavyWeaponRun",
	"LightWeaponStandAttack",
	"LightWeaponJumpAttack",
	"LightWeaponRunAttack",
	"LightWeaponDashAttack",
	"LightWeaponThrow",
	"HeavyWeaponThrow",
	"LightWeaponJumpThrow",
	"HeavyWeaponJumpThrow",
	"Drink",
	"BeforeAttack",
	"Attacking",
	"AfterAttack",
	"BeforeSuperAttack",
	"SuperAttacking",
	"AfterSuperAttack",
	"BeforeJumpAttack",
	"JumpAttacking",
	"AfterJumpAttack",
	"BeforeRunAttack",
	"RunAttacking",
	"AfterRunAttack",
	"BeforeDashAttack",
	"DashAttacking",
	"AfterDashAttack",
	"Flip",
	"Rolling",
	"Defend",
	"DefendPunch",
	"DefendKick",
	"Catching",
	"Caught",
	"Falling",
	"Jump",
	"Dash",
	"Crouch",
	"Injured",
	"Lying",
	"InTheAir",
	"BeforeSkill",
	"AfterSkill",
	"AirSkill",
	"XAxisSkill",
	"ZAxisSkill",
	"GroundSkill",
	"UniqueSkill",
	"BasicActionEnd"
};