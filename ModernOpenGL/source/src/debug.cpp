#include "../include/debug.hpp"

void Log::openFile(fs::path const& filePath, bool overrideFileWhenWriting)
{
	if (logFile.is_open())
	{
		DEBUG_LOG("Closing already open log file");
		logFile.close();
	}

	if (overrideFileWhenWriting)
		logFile.open(filePath, std::ofstream::out | std::ofstream::trunc);
	else
		logFile.open(filePath, std::ofstream::out | std::ofstream::app);

	ASSERT(logFile.is_open());
}

void Log::print(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	char buffer[1024];
	vsprintf_s(buffer, format, args);

	if (logFile.is_open())
		logFile << buffer;
	cout << buffer;

	va_end(args);
}