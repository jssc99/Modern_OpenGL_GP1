#ifndef DEBUG_H
#define DEBUG_H

#include <fstream>
#include <iostream>
#include <filesystem>
#include <cstdarg>
#include <signal.h>

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define DEBUG_LOG(txt) std::cout << __TIMESTAMP__ << ":" << __FILENAME__ << '(' << __LINE__ << "): " << txt << std::endl;

#ifdef NDEBUG
#define ASSERT(x) if(!x) exit(EXIT_FAILURE);
#else
#define ASSERT(x) if(!x) __debugbreak();
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
#endif