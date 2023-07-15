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

#include "Window.h"

#include "Gl.h"
#include "WorldVariables.h"
#include "Logger.h"

namespace
{

void KeyPressHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	GetWindow().onKeyPressed.trigger(key, scancode, action, mods);
}

void TextInputHandler(GLFWwindow* window, unsigned int scancode)
{
	GetWindow().onTextInput.trigger(scancode);
	GetWorldVariables().set("inputted-text", scancode);
}

void CursorEnterHandler(GLFWwindow* window, int entered)
{
	GetWindow().onCursorEntered.trigger(entered);
}

void MouseScrollHandler(GLFWwindow* window, double xOffset, double yOffset)
{
	GetWindow().onMouseWheel.trigger(xOffset, yOffset);
	GetWorldVariables().set("mouse-wheel-x", xOffset);
	GetWorldVariables().set("mouse-wheel-y", yOffset);
}

}	 // namespace

void Window::create(Utils::ISize2D size, const std::string& title)
{
	if (!(window = glfwCreateWindow(size.width, size.height, title.c_str(), NULL, NULL)))
	{
		glfwTerminate();
		throw std::runtime_error("Failed to create GLFW window");
	}
	size_ = size;
	title_ = title;

	spdlog::get("core")->info("The window was created");

	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, KeyPressHandler);
	glfwSetCharCallback(window, TextInputHandler);
	glfwSetCursorEnterCallback(window, CursorEnterHandler);
	glfwSetScrollCallback(window, MouseScrollHandler);
}

bool Window::shouldClose() const
{
	return glfwWindowShouldClose(window);
}

void Window::swapBuffers()
{
	glfwSwapBuffers(window);
}

void Window::pollEvent()
{
	glfwPollEvents();
}

void Window::clearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void Window::clear(int code)
{
	glClear(code);
}

void Window::viewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	Gl::viewport(x, y, width, height);
}

HWND Window::getHwnd()
{
	return glfwGetWin32Window(window);
}

Utils::ISize2D Window::getSize() const
{
	return size_;
}

Window& GetWindow()
{
	return Window::instance();
}
