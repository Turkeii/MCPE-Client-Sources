#pragma once
#include <cstdarg>

#ifndef NDEBUG
	#define Logf(...) Logger::logf(__VA_ARGS__)
#else
	#define Logf(...)
#endif

namespace Logger {
	
	extern void init();
	extern void logf(const char* Format, ...);
	extern void log(const char* Text);

}