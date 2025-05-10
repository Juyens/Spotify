#include "Menu.h"
#include "Console.h"
#include "KeyboardInput.h"
#include "Utils.h"

#include <iostream>

Menu::Menu(const std::string& title)
	: _title(title), _selectionTracker({0, -1}), _hasExitOption(false)
{
}

void Menu::addOption(const std::string& label, const std::function<void()>& callback)
{
	_options.addLast(Option({ label }, callback));
}

void Menu::addOptionBack(const std::string& label, const std::function<void()>& callback)
{
	_hasExitOption = true;
	addOption(label, callback);
}

void Menu::display()
{	
	std::string title = addSpaces(_title);

	std::string str(title.length(), char(196));

	Console::writeAt(0, 0, char(218) + str + char(191), FG::White | BG::Black);
	Console::writeAt(0, 1, char(179) + title + char(179), FG::White | BG::Black);
	Console::writeAt(0, 2, char(195) + str + char(217), FG::White | BG::Black);

	Console::writeAt(0, 3, std::string(1, char(179)), FG::White | BG::Black);

	if (_options.isEmpty())
	{
		Console::writeAt(0, 4, std::string(1, char(192)), FG::White | BG::Black);
		Console::writeAt(2, 4, "No options", FG::White | BG::Black);
		return;
	}

	updateSelection();

	for (uint i = 0; i < _options.size(); i++)
	{
		auto option = _options.getAtPosition(i);
		bool emptyText = option.getLabel().getText().empty();

		if (i != _options.size() - 1)
		{
			Console::writeAt(0, i + 4, std::string(1, char(195)), FG::White | BG::Black);
		}
		else
		{
			Console::writeAt(0, i + 4, std::string(1, char(192)), FG::White | BG::Black);
		}

		if (!emptyText)
		{
			Console::writeAt(2, i + 4, option.getLabel().getText(), option.getLabel().getColor());
		}
	}
}

void Menu::updateSelection()
{
	if (!_selectionTracker.hasChanged())
		return;

	if (_selectionTracker.getPrevious() != -1)
	{
		auto optionPrev = _options.getAtPosition(_selectionTracker.getPrevious());
		optionPrev.getLabel().setColor(FG::White | BG::Black);
		_options.updateAtPosition(optionPrev, _selectionTracker.getPrevious());
	}

	auto optionCurrent = _options.getAtPosition(_selectionTracker.getCurrent());
	optionCurrent.getLabel().setColor(FG::Black | BG::LightGreen);
	_options.updateAtPosition(optionCurrent, _selectionTracker.getCurrent());

	_selectionTracker.updatePrevious();
}

void Menu::selectOption()
{
	if (KeyboardInput::isKeyJustPressed(Key::ENTER))
	{
		if (_options.isEmpty())
			return;

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		Console::clearScreen();

		auto option = _options.getAtPosition(_selectionTracker.getCurrent());

		if (option.getCallback() != nullptr)
		{
			option.execute();
		}

		Console::clearScreen();
	}

	if (KeyboardInput::isKeyJustPressed(Key::ESC))
	{
		if (!_hasExitOption)
			return;

		auto option = _options.getLast();

		if (option.getCallback() != nullptr)
		{
			option.execute();
		}
	}

	if (KeyboardInput::isKeyJustPressed(Key::UP))
	{
		if (_selectionTracker.getCurrent() > 0)
		{
			_selectionTracker.updatePrevious();
			_selectionTracker.moveUp();
		}
	}

	if (KeyboardInput::isKeyJustPressed(Key::DOWN))
	{
		int len = _options.size();

		if (_selectionTracker.getCurrent() < len - 1)
		{
			_selectionTracker.updatePrevious();
			_selectionTracker.moveDown();
		}
	}
}

void Menu::restoreSelectionTracker()
{
	_selectionTracker.setCurrentIndex(0);
}

void Menu::run()
{
	display();
	selectOption();
}
