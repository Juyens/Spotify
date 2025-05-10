#include "Key.h"

#include <Windows.h>
#include <array>

class KeyboardInput
{
private:
	static std::array<Key, 36> keys;
	static std::array<bool, 36> wasDown;
	static std::array<bool, 36> justPressed;
	static std::array<int, 36> keyHoldTime;
	static bool ignoreInput;
	static const int HOLD_THRESHOLD = 500;

public:
	static void update();
	static bool isKeyJustPressed(Key key);
	static void setIgnoreInput(bool ignore);
};