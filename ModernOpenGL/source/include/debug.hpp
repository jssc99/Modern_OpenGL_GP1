#ifndef DEBUG_H
#define DEBUG_H

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <cstdarg>
#include <signal.h>
#include <Windows.h>

using std::cin; using std::cout;
using std::endl; using std::string;

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
//#define DEBUG_LOG(txt) OutputDebugStringA(__FILENAME__ << '(' << __LINE__ << "): " << txt);
#define DEBUG_LOG(txt, ...) DBLOut(txt, __VA_ARGS__);

#ifdef NDEBUG
#define ASSERT(x) if(!x) exit(EXIT_FAILURE);
#else
#define ASSERT(x) if(!x) DebugBreak();
#endif

namespace fs = std::filesystem;

class Log
{
public:
	Log();
	~Log();

	bool openFile(fs::path const& filePath, bool overrideFileWhenWriting);
	void print(const char* format, ...);

private:
	std::fstream logFile;
};

static void DBLOut(const char* txt, ...)
{
	va_list args;
	va_start(args, txt);

	char buffer[1024];
	vsprintf_s(buffer, txt, args);

	std::wostringstream out;
	out << __FILENAME__ << "(" << __LINE__ << "): ";
	out << buffer;

	OutputDebugStringW(out.str().c_str());

	cout << __FILENAME__ << "(" << __LINE__ << "): ";
	cout << buffer;

	va_end(args);
}
#endif