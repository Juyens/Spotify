#pragma once

#include "Label.h"

#include <functional>
#include <string>

class Option
{
private:
	Label _label;
	std::function<void()> _callback;

public:
	Option();
	Option(const Label& label, const std::function<void()>& callback);

	Label& getLabel();
	void setLabel(const Label& label);

	const std::function<void()>& getCallback() const;
	void setCallback(const std::function<void()>& callback);

	void execute();
};