#include <src/auto_link_luajit.hpp>
#include <luabind/luabind.hpp>
#include <iostream>
using namespace std;
using namespace luabind;


class testlua
{
public:
	testlua(std::string s):m_str(s){};
	void myprint()
	{
		cout << m_str << endl;
	}
	void setstr(std::string s){ m_str = s;};
private:
	std::string m_str;
};


int main()
{
	lua_State *L = luaL_newstate();
	luabind::open(L);


	module(L)
		[  
			class_<testlua>("testlua")
			.def(constructor<const std::string>())
			.def("myprint",&testlua::myprint)
			.def("setstr", &testlua::setstr)
		];


	luaL_dofile(L,"test.lua");
	lua_close(L);

	system("pause");
	return 0;
}
