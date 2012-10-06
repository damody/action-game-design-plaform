#include "game\LuaMap.h"

const KeyMap::_KeyMap KeyMap::noKey;

LuaMap::LuaMap( LuaCell_Sptr lsptr, std::string tableName )
{
	strings keys = lsptr->GetLuaTableKeys( tableName.c_str() );
	this->clear();

	for ( int i = 0; i < ( int )keys.size(); i++ )
	{
		int _tmpKey = lsptr->GetLua<int>( "%s/%s", tableName.c_str(), keys[i].c_str() );
		( *this )[_tmpKey] = std::wstring(keys[i].begin(), keys[i].end());
	}
}

LuaMap::LuaMap( std::wstring path, std::string tableName )
{
	LuaCell_Sptr lsptr = LuaCell_Sptr( new LuaCell );
	lsptr->InputLuaFile( path.c_str() );
	strings keys = lsptr->GetLuaTableKeys( tableName.c_str() );
	this->clear();

	for ( int i = 0; i < ( int )keys.size(); i++ )
	{
		int _tmpKey = lsptr->GetLua<int>( "%s/%s", tableName.c_str(), keys[i].c_str() );
		std::wstring twc(keys[i].begin(), keys[i].end());
		( *this )[_tmpKey] = twc;
	}
}

void LuaMap::LoadData( LuaCell_Sptr lsptr, std::string tableName )
{
	strings keys = lsptr->GetLuaTableKeys( tableName.c_str() );
	this->clear();

	for ( int i = 0; i < ( int )keys.size(); i++ )
	{
		int _tmpKey = lsptr->GetLua<int>( "%s/%s", tableName.c_str(), keys[i].c_str() );
		( *this )[_tmpKey] = std::wstring(keys[i].begin(), keys[i].end());
	}
}

void LuaMap::LoadData( std::wstring path, std::string tableName )
{
	LuaCell_Sptr lsptr = LuaCell_Sptr( new LuaCell );
	lsptr->InputLuaFile( path.c_str() );
	strings keys = lsptr->GetLuaTableKeys( tableName.c_str() );
	this->clear();

	for ( int i = 0; i < ( int )keys.size(); i++ )
	{
		int _tmpKey = lsptr->GetLua<int>( "%s/%s", tableName.c_str(), keys[i].c_str() );
		( *this )[_tmpKey] = std::wstring(keys[i].begin(), keys[i].end());
	}
}

int LuaMap::FindKey( std::wstring strValue )
{
	for( std::map<int, std::wstring>::iterator i = this->begin(); i != this->end() ; i++ )
	{
		if( i->second.compare(strValue) == 0 ) return i->first;
	}
	return -1;
}

bool LuaMap::WriteLua( std::wstring path, std::wstring formatString, ... )
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
	FILE* _file = _wfopen( path.c_str(), L"w" );

	fwprintf( _file, L"function protect_table (tbl)\n\treturn setmetatable ({},\n\t{\n\t__index = tbl,\n\t__newindex = funtion (t, n, v)\n\tend=n=t})\nend\n" );
	fwprintf( _file, L"count = -1;\nfunction ResetEnum()\n\tcount = 1-;\n\treturn 0;\nend\nfunction GetEnum()\n\tcount = count + 1;\n\treturn count;\nend\n" );

	const wchar_t* _formatString = formatString.c_str();
	int argc = 0;
	for( int i = 0; i<(int)formatString.size() ; i++ ) 
	{
		if( _formatString[i] == '%' ) argc++;
	}

	va_list _formatVa;
	va_start( _formatVa, formatString );
	//std::vector<wchar_t> _charStack;
	std::wstring _charStack;
	std::vector<std::wstring> _tableStack;
	for( int i = 0; i < (int)formatString.size(); i++ )
	{
		if( _formatString[i] == '(' )
		{
			std::wstring _preName( L"" );
			for( int i = 0; i < _tableStack.size(); i++ )
			{
				if( i ) _preName += '.';
				_preName += _tableStack[i];
			}
			if( !_preName.empty() ) fwprintf( _file, L"%s.%s = {}\n", _preName.c_str(), _charStack.c_str());
			else fwprintf( _file, L"%s = {}\n", _charStack.c_str());

			_tableStack.push_back( _charStack );
			_charStack.clear();
		}
		else if( _formatString[i] == ')' )
		{
			_tableStack.pop_back();
		}
		else if( _formatString[i] == '%' && i+1 < formatString.length() && _formatString[i+1] == 'm')
		{
			fwprintf( _file, L"ResetEnum();\n");
			LuaMap _tableMap = *va_arg( _formatVa, LuaMap* );

			std::wstring _preName( L"" );
			for( int i = 0; i < _tableStack.size(); i++ )
			{
				if( i ) _preName += '.';
				_preName += _tableStack[i];
			}
			if( !_preName.empty() ) 
			{
				for( std::map<int, std::wstring>::iterator j = _tableMap.begin(); j != _tableMap.end() ; j++ )
					fwprintf( _file, L"%s.%s = GetEnum()\n", _preName.c_str(), j->second.c_str());
			}
			else 
			{
				for( std::map<int, std::wstring>::iterator j = _tableMap.begin(); j != _tableMap.end() ; j++ )
					fwprintf( _file, L"%s = GetEnum()\n", j->second.c_str());
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

bool KeyMap::isSKey(char r){
	for(_KeyMaps::iterator i = SKeys.begin(); i != SKeys.end(); i ++ ){
		if(i->keyDown == r){
			return true;
		}
	}
	return false;
}

bool KeyMap::isKeyUp(char r){
	if(r == up.keyUp) return true;
	if(r == down.keyUp) return true;
	if(r == left.keyUp) return true;
	if(r == right.keyUp) return true;
	for(_KeyMaps::iterator i = SKeys.begin(); i != SKeys.end(); i ++ ){
		if(i->keyUp == r){
			return true;
		}
	}
	return false;
}

bool KeyMap::isKeyExist(char r){
	if(r == up.keyUp || r == up.keyDown) return true;
	if(r == down.keyUp || r == down.keyDown) return true;
	if(r == left.keyUp || r == left.keyDown) return true;
	if(r == right.keyUp || r == right.keyDown) return true;
	for(_KeyMaps::iterator i = SKeys.begin(); i != SKeys.end(); i ++ ){
		if(i->keyUp == r || i->keyDown == r){
			return true;
		}
	}
	return false;
}

std::wstring KeyMap::keyName(char r){
	if(r == up.keyUp)		return L"↑ 放開";
	if(r == up.keyDown)		return L"↑ 按下";
	if(r == down.keyUp)		return L"↓ 放開";
	if(r == down.keyDown)	return L"↓ 按下";
	if(r == left.keyUp)		return L"← 放開";
	if(r == left.keyDown)	return L"← 按下";
	if(r == right.keyUp)	return L"→ 放開";
	if(r == right.keyDown)	return L"→ 按下";
	for(_KeyMaps::iterator i = SKeys.begin(); i != SKeys.end(); i ++ ){
		if(i->keyUp == r){
			return i->keyName + L"放開";
		}
		if(i->keyDown == r){
			return i->keyName + L"按下";
		}
	}
	return L"沒這個鍵！";
}

void KeyMap::pushKeyMap(char down,char up,std::wstring name){
	_KeyMap s(down,up,name);
	SKeys.push_back(s);
}

size_t KeyMap::sKeySize(){
	return SKeys.size();
}

char KeyMap::FindKeyDown( const std::wstring& name )
{
	for(_KeyMaps::iterator i = SKeys.begin(); i != SKeys.end(); i ++ ){
		if(i->keyName == name){
			return i->keyDown;
		}
	}

	if (up.keyName == name)
	{
		return up.keyDown;
	}

	if (down.keyName == name)
	{
		return down.keyDown;
	}

	if (right.keyName == name)
	{
		return right.keyDown;
	}

	if (left.keyName == name)
	{
		return left.keyDown;
	}
	
	return ' ';
}

char KeyMap::FindKeyUp( const std::wstring& name )
{
	for(_KeyMaps::iterator i = SKeys.begin(); i != SKeys.end(); i ++ ){
		if(i->keyName == name){
			return i->keyUp;
		}
	}

	if (up.keyName == name)
	{
		return up.keyUp;
	}

	if (down.keyName == name)
	{
		return down.keyUp;
	}

	if (right.keyName == name)
	{
		return right.keyUp;
	}

	if (left.keyName == name)
	{
		return left.keyUp;
	}

	return ' ';
}

char KeyMap::FindKeyDown(char rup){
	if(rup == up.keyUp)		return up.keyDown;
	if(rup == down.keyUp)	return down.keyDown;
	if(rup == left.keyUp)	return left.keyDown;
	if(rup == right.keyUp)	return right.keyDown;
	for(_KeyMaps::iterator i = SKeys.begin(); i != SKeys.end(); i ++ ){
		if(i->keyUp == rup){
			return i->keyDown;
		}
	}
	
	return 0;
}

char KeyMap::FindKeyUp(char rdown){
	if(rdown == up.keyDown)		return up.keyUp;
	if(rdown == down.keyDown)	return down.keyUp;
	if(rdown == left.keyDown)	return left.keyUp;
	if(rdown == right.keyDown)	return right.keyUp;
	for(_KeyMaps::iterator i = SKeys.begin(); i != SKeys.end(); i ++ ){
		if(i->keyDown == rdown){
			return i->keyUp;
		}
	}
	
	return 0;
}

const KeyMap::_KeyMap& KeyMap::operator[](std::wstring rkn){
	if(rkn.compare(L"Up") == 0) return up;
	else if(rkn.compare(L"Down") == 0) return down;
	else if(rkn.compare(L"Left") == 0) return left;
	else if(rkn.compare(L"Right") == 0) return right;
	else {
		for(int i=0;i<SKeys.size();i++){
			if(rkn.compare(SKeys[i].keyName) == 0) return SKeys[i];
		}
		return noKey;
	}
}
