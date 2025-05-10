#include "Option.h"
#include <iostream>

Option::Option() : _callback(nullptr), _label({"None"}) {}

Option::Option(const Label& label, const std::function<void()>& callback)
	: _callback(callback), _label(label)
{
}

Label& Option::getLabel()
{
	return _label;
}

void Option::setLabel(const Label& label)
{
	_label = label;
}

const std::function<void()>& Option::getCallback() const
{
	return _callback;
}

void Option::setCallback(const std::function<void()>& callback)
{
	_callback = callback;
}

void Option::execute()
{
	if (_callback)
	{
		_callback();
	}
}