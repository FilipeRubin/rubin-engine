#pragma once

#ifndef LOG_ENABLED
	#define LOG_ENABLED 1
#endif

#if LOG_ENABLED
	#include <logging/logger.h>
	#define LOG_TRACE(message) Logger::Log({LogLevel::TRACE, message, __FILE__, __LINE__})
	#define LOG_DEBUG(message) Logger::Log({LogLevel::DEBUG, message, __FILE__, __LINE__})
	#define LOG_INFO(message) Logger::Log({LogLevel::INFO, message, __FILE__, __LINE__})
	#define LOG_WARNING(message) Logger::Log({LogLevel::WARNING, message, __FILE__, __LINE__})
	#define LOG_ERROR(message) Logger::Log({LogLevel::ERROR, message, __FILE__, __LINE__})
	#define LOG_FATAL(message) Logger::Log({LogLevel::FATAL, message, __FILE__, __LINE__})
#else
	#define LOG_TRACE(message) ((void)0)
	#define LOG_DEBUG(message) ((void)0)
	#define LOG_INFO(message) ((void)0)
	#define LOG_WARNING(message) ((void)0)
	#define LOG_ERROR(message) ((void)0)
	#define LOG_FATAL(message) ((void)0)
#endif
