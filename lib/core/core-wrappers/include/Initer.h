
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

#include "FreeTypeLibrary.h"
#include "GladWrapper.h"
#include "GlfwWrapper.h"
#include "Logger.h"
#include "NotCopyableAndNotMovable.h"
#include "Size.h"
#include "Window.h"
#include "World.h"

#include <glm/glm.hpp>

class Initer : public Utils::NotCopyableAndNotMovable
{
public:
	Initer() = delete;

	struct Data
	{
		glm::ivec2 glfwVersion;	   // major & minor
		Utils::ISize2D windowSize;
		std::string title;
	};

	static inline void init(const Data& data)
	{
		Logger::initLogger();
		GlfwWrapper::initGlfw(data.glfwVersion.x, data.glfwVersion.y);
		GetWindow().create({data.windowSize.width, data.windowSize.height}, data.title);

		GladWrapper::initGlad();
		GetWorld().init();
		GetFreeTypeLibrary().init();
	}
};