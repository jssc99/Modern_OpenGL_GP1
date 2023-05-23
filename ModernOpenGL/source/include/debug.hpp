#ifndef DEBUG_H
#define DEBUG_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <cstdarg>
#include <signal.h>
#include <Windows.h>

using std::cin; using std::cout;
using std::endl; using std::string;

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define DEBUG_LOG(txt, ...) DBLOut(__FILENAME__, __LINE__, txt, __VA_ARGS__);

#ifdef NDEBUG
#define ASSERT(x) if(!x) exit(EXIT_FAILURE);
#else
#define ASSERT(x) if(!x) DebugBreak();
#endif

namespace fs = std::filesystem;

class Log
{
public:
	Log() {};
	~Log() { if (logFile.is_open()) logFile.close(); };

	void openFile(fs::path const& filePath, bool overrideFileWhenWriting = false);
	void print(const char* format, ...);

private:
	std::fstream logFile;
};

static void DBLOut(const char* fileName = __FILENAME__, int lineNumb = __LINE__, const char* txt = "", ...)
{
	va_list args;
	va_start(args, txt);

	char buffer[1024];
	vsprintf_s(buffer, txt, args);

	std::wostringstream out;
	out << fileName << "(" << lineNumb << "): ";
	out << buffer << '\n';

	OutputDebugStringW(out.str().c_str());

	cout << fileName << "(" << lineNumb << "): ";
	cout << buffer << '\n';

	va_end(args);
}
#endif