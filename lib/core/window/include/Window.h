// MIT License
//
// Copyright (c) 2023 Valerii Koniushenko
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include "Delegate.h"
#include "GlfwWrapper.h"
#include "Singleton.h"
#include "Size.h"

#include <Windows.h>

class Window : public Singleton<Window>
{
public:
	void create(Utils::ISize2D size, const std::string& title);
	_NODISCARD bool shouldClose() const;
	void swapBuffers();
	void pollEvent();
	void clearColor(float r, float g, float b, float a);
	void clear(int code);
	void viewport(GLint x, GLint y, GLsizei width, GLsizei height);
	_NODISCARD HWND getHwnd();
	Utils::ISize2D getSize() const;

	LambdaDelegate<void(int, int, int, int)> onKeyPressed;
	LambdaDelegate<void(unsigned int)> onTextInput;
	LambdaDelegate<void(int)> onCursorEntered;

protected:
	GLFWwindow* window{};
	Utils::ISize2D size_{};
	std::string title_;
};

Window& GetWindow();