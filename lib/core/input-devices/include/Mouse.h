#pragma once
#include "Windows.h"
#include "glm.hpp"

#include <functional>

class Window;

class Mouse
{
public:
	enum class Key
	{
		Left = VK_LBUTTON,
		Right = VK_RBUTTON,
		Center = VK_MBUTTON
	};

	Mouse() = delete;

	static glm::ivec2 getPosition();
	static glm::ivec2 getPosition(Window& wnd);

	static bool isKeyPressed(Key key);
	static bool isKeyReleased(Key key);

	static void update(Window& wnd);

	static void setMouseMoveDeltaCallback(std::function<void(glm::fvec2)> callback);
	static void resetMouseMoveDeltaCallback();

	static void setMouseSensitivity(float sensitivity);

	static void showCursor();
	static void hideCursor();

private:
	inline static float mouseSensitivity_ = 350.f;
	inline static glm::ivec2 lastPosition_;
	inline static std::function<void(glm::fvec2 pos)> mouseMoveDeltaCallback_;
};