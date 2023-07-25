#include "Mouse.h"

#include "Window.h"

#include <Windows.h>

#include <stdexcept>

glm::ivec2 Mouse::getPosition()
{
	POINT p{};
	GetCursorPos(&p);
	return glm::ivec2(static_cast<int>(p.x), static_cast<int>(p.y));
}

glm::ivec2 Mouse::getPosition(Window& wnd)
{
	POINT p{};
	GetCursorPos(&p);
	ScreenToClient(wnd.getHwnd(), &p);
	return glm::ivec2(static_cast<int>(p.x), static_cast<int>(p.y));
}

bool Mouse::isKeyPressed(Key key)
{
	if (GetKeyState(static_cast<int>(key)) < 0)
	{
		return true;
	}
	return false;
}

bool Mouse::isKeyReleased(Key key)
{
	if (GetKeyState(static_cast<int>(key)) > 0)
	{
		return true;
	}
	return false;
}

void Mouse::update(Window& wnd)
{
	auto currentPosition = getPosition(wnd);

	if (mouseMoveDeltaCallback_)
	{
		glm::fvec2 delta = currentPosition - lastPosition_;
		delta /= mouseSensitivity_;
		mouseMoveDeltaCallback_(delta);
	}

	lastPosition_ = currentPosition;
}

void Mouse::setMouseMoveDeltaCallback(std::function<void(glm::fvec2 pos)> callback)
{
	mouseMoveDeltaCallback_ = callback;
}

void Mouse::resetMouseMoveDeltaCallback()
{
	mouseMoveDeltaCallback_ = nullptr;
}

void Mouse::setMouseSensitivity(float sensitivity)
{
	if (sensitivity <= 0.f)
	{
		throw std::runtime_error("The mouse sensitivity can't be less of equal of 0");
	}

	mouseSensitivity_ = sensitivity;
}

void Mouse::showCursor()
{
	ShowCursor(true);
}

void Mouse::hideCursor()
{
	ShowCursor(false);
}
