#pragma once

#include "Color.h"

#include <string>

class Label
{
private:
	std::string _text;
	WORD _color;

public:
	Label(const std::string& text, WORD color = FG::White | BG::Black)
		: _text(text), _color(color)
	{
	}

	void setText(const std::string& text)
	{
		_text = text;
	}

	std::string getText()
	{
		return _text;
	}

	void setColor(WORD color)
	{
		_color = color;
	}

	WORD getColor()
	{
		return _color;
	}
};