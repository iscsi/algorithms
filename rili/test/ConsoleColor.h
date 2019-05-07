//Copyleft Vincent Godin
//https://www.codeproject.com/Articles/16431/Add-color-to-your-std-cout

#pragma once
#include <iostream>

#if defined(WIN32)
#include <windows.h>

inline bool isGitlabCi()
{
	static bool result = GetEnvironmentVariableA("GITLAB_CI", nullptr, 0) != 0;
	return result;
}

inline bool isPowerShell()
{
	static bool result = true;
	return result;
}

inline void setAttributes(unsigned int attributes)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdout, attributes);
}

inline void writeConsole(const char* value)
{
	DWORD written = 0;
	WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), value, lstrlenA(value), &written, nullptr);
}
#endif

inline std::ostream& blue(std::ostream &s)
{
#if defined(WIN32)
	setAttributes(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	if (isGitlabCi())
		writeConsole("\x1b[94m");
#endif
	return s;
}

inline std::ostream& red(std::ostream &s)
{
#if defined(WIN32)
	setAttributes(FOREGROUND_RED | FOREGROUND_INTENSITY);
	if (isGitlabCi())
		writeConsole("\x1b[91m");
#endif
	return s;
}

inline std::ostream& green(std::ostream &s)
{
#if defined(WIN32)
	setAttributes(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	if (isGitlabCi())
		writeConsole("\x1b[92m");
#endif
	return s;
}

inline std::ostream& yellow(std::ostream &s)
{
#if defined(WIN32)
	setAttributes(FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	if (isGitlabCi())
		writeConsole("\x1b[93m");
#endif
	return s;
}

inline std::ostream& white(std::ostream &s)
{
#if defined(WIN32)
	setAttributes(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	if (isGitlabCi())
		writeConsole("\x1b[97m");
#endif
	return s;
}

inline std::ostream& reset(std::ostream &s)
{
#if defined(WIN32)
	setAttributes(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	if (isGitlabCi())
		writeConsole("\x1b[0m");
#endif
	return s;
}