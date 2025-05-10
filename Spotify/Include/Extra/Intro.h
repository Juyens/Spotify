#pragma once

#include "Console.h"

#include <chrono>
#include <thread>
#include <array>

class Intro
{
private:
	static void drawBorder();
	static void drawLogo();
	static void drawMessage(int y, const std::string& msg, WORD attributes = FG::White | BG::Black);

public:
	static void showIntro(ConsoleSize size);
};
