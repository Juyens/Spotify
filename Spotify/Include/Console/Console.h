#pragma once

#include "Color.h"

#include <Windows.h>
#include <iostream>
#include <string>
#include <exception>
#include <vector>


// --------------------------------------------------------------------------------------- //
#define THROW_IF_FAILED(cond, msg) \
    if (cond) \
	{ \
		DWORD errorCode = GetLastError(); \
		throw std::runtime_error(std::string(msg) + " >> Error code: " + std::to_string(errorCode)); \
	}
// --------------------------------------------------------------------------------------- //

struct ConsoleSize
{
	int width;
	int height;

	ConsoleSize(int w = 0, int h = 0)
		: width(w), height(h)
	{
	}
};

class Console
{
private:
	static inline HANDLE _hConsole{ GetStdHandle(STD_OUTPUT_HANDLE) };

	// ------------------------------------- //
	static void setCursorVisibility(bool visible);

public:
	static void resizeConsole(ConsoleSize size);
	static void clearScreen();
	static void moveCursor(int x, int y);
	static void hideCursor();
	static void showCursor();
	static ConsoleSize getSize();
	static void writeAt(int x, int y, const std::string& text, FG fg);
	static void writeAt(int x, int y, const std::string& text, WORD wr = FG::White | BG::Black);
	static void setTitle(const std::string& title);
};