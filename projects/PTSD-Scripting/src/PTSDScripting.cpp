#include <iostream>
#include "PTSDScripting.h"
#include "lua.hpp"
#include <sol/sol.hpp>

namespace PTSD {
	void Scripting::init() {
		std::cout << "Initializing lua scripting system\n";
		
		sol::state lua;
		lua.open_libraries(sol::lib::base);

		lua.script("print('Lua initialized correctly and working!')");
	}
}