#pragma once
#include "log-level.h"
#include <string>

struct LogMessage
{
	LogLevel level;
	std::string message;
	const char* fileName = nullptr;
	decltype(__LINE__) lineNumber = 0;
};
