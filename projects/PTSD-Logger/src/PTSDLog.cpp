#include <iostream>
#include "PTSDLog.h"
#include "spdlog/spdlog.h"

namespace PTSD {
	int Log::Init() {
		std::cout << "Log system initialized\n";
		spdlog::info("spdlog working!\n");
		
		return 0;
	}
}