#pragma once

#define NOMINMAX

#include "List.h"
#include "Option.h"
#include "SelectionTracker.h"

#include <string>

class Menu
{
private:
	std::string _title;
	SelectionTracker _selectionTracker;
	List<Option> _options;
	bool _hasExitOption;

public:
	Menu(const std::string& title = "untitled");

	void addOption(const std::string& label, const std::function<void()>& callback);
	void addOptionBack(const std::string& label, const std::function<void()>& callback);
	virtual void display();
	void updateSelection();
	void selectOption();
	void restoreSelectionTracker();
	void run();
};