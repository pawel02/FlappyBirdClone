#pragma once
#include <iostream>

//basic logging system
#ifdef IS_DEBUG == 1
#define WARNING(...) std::cout << __VA_ARGS__ << "\n"; __debugbreak()
#define FAIL(message) std::cout << message << "\n"; __debugbreak()
#else
#define WARNING(message)
#define FAIL(message) std::cout << message << "\n"
#endif