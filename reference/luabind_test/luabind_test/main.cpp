//繼承範例
#include <auto_link_luajit.hpp>
#include <luabind/luabind.hpp>
#include <iostream>
using std::cout;
using std::endl;


class Foo {
public:
	// The Constructor
	// @self	the reference to our Lua instance so we may reference to our Lua object in C++
	//		and call the Lua class methods via luabind::call_member<void>(m_Self, "function");
	// @name	an arbitrary test value, to identify our objects
	Foo(luabind::object self, const char* name) : m_Self(self), m_Name(name) {
		// Declare ourselves openly!
		std::cout << m_Name << " created." << std::endl;
	}

	// The Destructor
	~Foo(void) {
		// Declare to the world that we no longer exist
		std::cout << m_Name << " destroyed." << std::endl;
	}

	// This method will be overridden in Lua
	void Think() {
		std::cout << m_Name << " is thinking." << std::endl;	// Output something generic
	}

	// This method will enable us to reference to another object, and alter it's values
	// @target	the reference to another Foo object
	void Kill(luabind::object target) {
		// Check if our target is a valid object
		if (target && luabind::type(target) != LUA_TNIL) {
			// Convert the luabind::object into our own class type
			// notice the pointer form so we'll get just that, rather than a copy
			Foo* target_foo = luabind::object_cast<Foo*>(target);
			std::cout << m_Name << " attacks " << target_foo->m_Name << "!" << std::endl;

			// Lets alter the target's properties
			target_foo->m_Name = "Dead";
		}
	}

	// Class attributes
	luabind::object m_Self;		// Reference to our own Lua object
	std::string m_Name;		// Our object's name
};
/*
int main()
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	luabind::open(L);
	
	luabind::disable_super_deprecation();
	luabind::module(L)
	[
		luabind::class_<Foo>("Foo")
		.def(luabind::constructor<luabind::object, const char*>())
		.def("Think", &Foo::Think)
		.def("Kill", &Foo::Kill)
		.def_readwrite("name", &Foo::m_Name)
	];

	if (luaL_dofile(L, "test2.lua")) {
		cout << "We hit a little snug: " << lua_tostring(L, -1) << endl;// Print out the error message
	}
	

	
	//call function
// 	try {
// 		std::cout << "Result: " 
// 		<<luabind::call_function<int>(L, "f", 2)//多個參數就是(L, "f", 2,a,b,...)
// 		<<std::endl;
// 	}catch(luabind::error& e){
// 		std::cout << "Catch Exception: " << e.what() << std::endl;
// 	}
	

	lua_close(L);

	system("pause");
	return 0;
}
*/