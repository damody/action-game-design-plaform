#include <auto_link_luajit.hpp>
#include <auto_link_luabind.hpp>
#include <luabind/luabind.hpp>
#include <iostream>
#include <string>
using std::cout;
using std::endl;

class TestClass
{
private:
	int m_num;
public:
	TestClass():m_num(0){};
	int Get()
	{
		return m_num;
	}
	inline void Set(int n)
	{
		m_num = n;
	}
};

typedef void (TestClass::*MFPTR)(int);
template <class T>
void RegisterLua(lua_State* L,MFPTR ptr)
{
	luabind::module(L)
		[
			luabind::class_<T>("Test")
			.def(luabind::constructor<>())
			.def("Set", ptr)
		];
}


int main()
{

	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	luabind::open(L);

	RegisterLua<TestClass>(L,&TestClass::Set);

	if (luaL_dofile(L, "test3.lua")) {
		cout << "We hit a little snug: " << lua_tostring(L, -1) << endl;// Print out the error message
	}


	TestClass *t = new TestClass();

	//call function
	try {
		cout<<"num = "<<t->Get()<<endl;
		luabind::call_function<int>(L, "test",t);
		cout<<"num = "<<t->Get()<<endl;
	}catch(luabind::error& e){
		std::cout << "Catch Exception: " << e.what() << std::endl;
	}


	lua_close(L);


	system("pause");
	return 0;
}