#include "Console.h"

void Console::setCursorVisibility(bool visible)
{
	CONSOLE_CURSOR_INFO cursorInfo;

	THROW_IF_FAILED(!GetConsoleCursorInfo(_hConsole, &cursorInfo),
					"Failed to get console cursor info");

	cursorInfo.bVisible = visible;

	THROW_IF_FAILED(!SetConsoleCursorInfo(_hConsole, &cursorInfo),
					"Failed to set console cursor info");
}

// ---------------------------------------------------------------------------------------- //

void Console::resizeConsole(ConsoleSize size)
{
	const int charWidth = 8;
	const int charHeight = 16;

	int windowWidth = size.width * charWidth;
	int windowHeight = size.height * charHeight;

	MoveWindow(GetConsoleWindow(), 100, 100, windowWidth, windowHeight - 8, TRUE);
}

void Console::clearScreen()
{
	ConsoleSize size = getSize();

	DWORD dwSize = size.width * size.height;
	DWORD written;

	THROW_IF_FAILED(!FillConsoleOutputCharacterW(_hConsole, ' ', dwSize, { 0, 0 }, &written),
					"Failed to fill console output character");

	THROW_IF_FAILED(!FillConsoleOutputAttribute(_hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, dwSize, { 0, 0 }, &written),
					"Failed to fill console output attribute");

	THROW_IF_FAILED(!SetConsoleCursorPosition(_hConsole, { 0, 0 }),
					"Failed to set console cursor position");

	moveCursor(0, 0);
}

void Console::moveCursor(int x, int y)
{
	COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };

	THROW_IF_FAILED(!SetConsoleCursorPosition(_hConsole, coord),
					"Failed to move console cursor");
}

void Console::hideCursor()
{
	setCursorVisibility(false);
}

void Console::showCursor()
{
	setCursorVisibility(true);
}

ConsoleSize Console::getSize()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	THROW_IF_FAILED(!GetConsoleScreenBufferInfo(_hConsole, &csbi),
					"Failed to get console screen buffer info");

	SHORT width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	SHORT height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	return { width, height };
}

void Console::writeAt(int x, int y, const std::string& text, FG fg)
{
	WORD wr = static_cast<WORD>(fg);
	writeAt(x, y, text, wr);
}

void Console::writeAt(int x, int y, const std::string& text, WORD wr)
{
	std::vector<CHAR_INFO> buffer(text.size());

	for (size_t i = 0; i < text.size(); ++i)
	{
		buffer[i].Char.AsciiChar = text[i];
		buffer[i].Attributes = wr;
	}

	COORD dwSize = { static_cast<SHORT>(text.size()), 1 };
	SMALL_RECT writeRegion = { static_cast<SHORT>(x), static_cast<SHORT>(y),
							   static_cast<SHORT>(x + text.size() - 1), static_cast<SHORT>(y) };

	THROW_IF_FAILED(!WriteConsoleOutputA(_hConsole, buffer.data(), dwSize, { 0, 0 }, &writeRegion),
					"Failed to write text with color to console buffer");

	WORD defaultColor = static_cast<WORD>(FG::White) | (static_cast<WORD>(BG::Black) << 4);
	THROW_IF_FAILED(!SetConsoleTextAttribute(_hConsole, defaultColor),
					"Failed to reset default text and background color");
}

void Console::setTitle(const std::string& title)
{
	THROW_IF_FAILED(!SetConsoleTitleA(title.c_str()),
					"Failed to set console title");
}