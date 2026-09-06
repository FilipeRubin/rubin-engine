#include <logging/sink/console-logger-sink.h>
#include <iostream>

static inline constexpr std::string LogLevelAsString(const LogLevel& logLevel);
static inline constexpr std::string SummarizeFileName(const char* fileName);
static inline void SetConsoleLevelColor(LogLevel color);

void ConsoleLoggerSink::Write(const LogMessage& logMessage)
{
	SetConsoleLevelColor(logMessage.level);
	std::string level = LogLevelAsString(logMessage.level);
	std::string fileName = SummarizeFileName(logMessage.fileName);
	if (logMessage.fileName == nullptr)
		std::cout << '[' << level << "] " << logMessage.message << '\n';
	else if (logMessage.lineNumber == 0U)
		std::cout << '[' << level << "] " << logMessage.message << " (" << fileName << ")\n";
	else
		std::cout << '[' << level << "] " << logMessage.message << " (" << fileName << ':' << logMessage.lineNumber << ")\n";
}

constexpr std::string LogLevelAsString(const LogLevel& logLevel)
{
	switch (logLevel)
	{
	case LogLevel::TRACE:
		return "Trace";
	case LogLevel::DEBUG:
		return "Debug";
	case LogLevel::INFO:
		return "Info";
	case LogLevel::WARNING:
		return "Warning";
	case LogLevel::ERROR:
		return "Error";
	case LogLevel::FATAL:
		return "Fatal";
	}
	return "Unkown(" + std::to_string((int)logLevel) + ")";
}

inline constexpr std::string SummarizeFileName(const char* fileName)
{
	constexpr const char* roots[]
	{
		"\\src\\",
		"/src/",
		"\\include\\",
		"/include/"
	};

	for (const char* const& root : roots)
	{
		const char* summarizedFileName = std::strstr(fileName, root);
		if (summarizedFileName != nullptr)
		{
			return summarizedFileName + std::strlen(root);
		}
	}

	return fileName;
}

inline void SetConsoleLevelColor(LogLevel color)
{
#ifdef _WIN32
	switch (color)
	{
	case LogLevel::TRACE:
	case LogLevel::DEBUG:
	case LogLevel::INFO:
		std::cout << "\033[0m";
		break;
	case LogLevel::WARNING:
		std::cout << "\033[33m";
		break;
	case LogLevel::ERROR:
	case LogLevel::FATAL:
		std::cout << "\033[31m";
		break;
	}
#endif
}
