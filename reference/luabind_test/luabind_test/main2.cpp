//call member範例
#include <auto_link_luabind.hpp>
#include <luabind/luabind.hpp>
#include <luabind/object.hpp>
#include <iostream>
using std::cout;
using std::endl;
class TestClass
{
public:
	TestClass(int a)
	{
		this->a = a;
	}
	TestClass(luabind::object b, int a)
	{
		this->a = a;

		// get our lua-derived object instance for record
		m_self = b;
	}
	int get() const
	{
		return a;
	}
	void set(int a)
	{
		this->a = a;
	}
	// retrieve the interface to the derived lua object instance
	luabind::object getSelf()
	{
		return m_self;
	}

	// this would be called by the SceneManager
	void Tick()
	{
		luabind::call_member<int>(m_self, "Tick");
	}

private:
	int a;

	luabind::object m_self;
};

int Cpassthrough(luabind::object b)
{
	TestClass *C;

	C = luabind::object_cast<TestClass*>(b);
	C->set(2);

	luabind::call_member<int>(b, "member_func");

	

	return false;
}
int main()
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	luabind::open(L);
	
	luabind::disable_super_deprecation();
	luabind::module(L)
		[
			luabind::class_<TestClass>("Test")
			.def(luabind::constructor<luabind::object, int>())
			.def("get", &TestClass::get)
			.def("set", &TestClass::set)
			.def("getSelf", &TestClass::getSelf),
			luabind::def("Cpassthrough", &Cpassthrough)
		];

 	if (luaL_dofile(L, "test.lua")) {
 		cout << "We hit a little snug: " << lua_tostring(L, -1) << endl;// Print out the error message
 	}
	

	
	//call function
	try {
		//luabind::call_function<int>(L, "main");
		TestClass *C = new TestClass(543);
		luabind::call_function<int>(L, "tt",C);
		std::cout << "C = " << C->get() <<std::endl;
// 		std::cout << "Result: " 
// 		<<luabind::call_function<int>(L, "f", 2)//多個參數就是(L, "f", 2,a,b,...)
// 		<<std::endl;
	}catch(luabind::error& e){
		std::cout << "Catch Exception: " << e.what() << std::endl;
	}


	lua_close(L);

	system("pause");
	return 0;
}
