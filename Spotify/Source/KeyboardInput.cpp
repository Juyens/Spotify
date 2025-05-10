#include "KeyboardInput.h"

std::array<bool, 36> KeyboardInput::wasDown = {};
std::array<bool, 36> KeyboardInput::justPressed = {};
std::array<Key, 36> KeyboardInput::keys =
{
Key::ESC, Key::ENTER, Key::SPACE, Key::UP, Key::DOWN, Key::LEFT, Key::RIGHT, Key::A, Key::B,
Key::C, Key::D, Key::E, Key::F, Key::G, Key::H, Key::I, Key::J, Key::K, Key::L, Key::M, Key::N,
Key::O, Key::P, Key::Q, Key::R, Key::S, Key::T, Key::U, Key::V, Key::W, Key::X, Key::Y, Key::Z
};

std::array<int, 36> KeyboardInput::keyHoldTime = {};
bool KeyboardInput::ignoreInput = false;

void KeyboardInput::update()
{
	if (ignoreInput)
		return;

	for (size_t i = 0; i < keys.size(); ++i)
	{
		bool isDown = (GetAsyncKeyState(static_cast<int>(keys[i])) & 0x8000) != 0;
		justPressed[i] = isDown && !wasDown[i];
		wasDown[i] = isDown;
	}
}

bool KeyboardInput::isKeyJustPressed(Key key)
{
	auto it = std::find(keys.begin(), keys.end(), key);
	if (it != keys.end())
	{
		size_t i = std::distance(keys.begin(), it);
		return justPressed[i];
	}
	return false;
}

void KeyboardInput::setIgnoreInput(bool ignore)
{
	ignoreInput = ignore;
}