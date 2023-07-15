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

#include "Size.h"
#include "glm/glm.hpp"

#include <type_traits>

namespace Utils
{

template <Sizeable T>
struct Rect
{
	glm::vec2 position;
	Size2D<T> size;

	_NODISCARD glm::vec2 getLeftTopPoint() const
	{
		return { position.x, position.y };
	}

	_NODISCARD glm::vec2 getLeftBottomPoint() const
	{
		return { position.x, position.y + size.height };
	}

	_NODISCARD glm::vec2 getRightBottomPoint() const
	{
		return { position.x + size.width, position.y + size.height };
	}

	_NODISCARD glm::vec2 getRightTopPoint() const
	{
		return { position.x + size.width, position.y };
	}

	_NODISCARD bool isCollision(glm::vec2 point) const
	{
		if (point.x >= position.x && point.x <= position.x + size.width &&
			point.y >= position.y && point.y <= position.y + size.height)
		{
			return true;
		}

		return false;
	}

	_NODISCARD bool isCollision(const Rect<T> rect) const
	{
		if (isCollision(rect.getLeftBottomPoint()) || isCollision(rect.getLeftTopPoint()) ||
			isCollision(rect.getRightBottomPoint()) || isCollision(rect.getRightTopPoint()))
		{
			return true;
		}

		return false;
	}
};

using FRect = Rect<float>;
using IRect = Rect<int>;
using DRect = Rect<double>;

}	 // namespace Utils