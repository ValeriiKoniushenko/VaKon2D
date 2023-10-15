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

#include "Camera.h"
#include "Window.h"

void Camera::setSize(const Utils::ISize2D& size)
{
	size_ = size;
}

const Utils::ISize2D& Camera::getSize() const
{
	return size_;
}

void Camera::setPosition(const glm::ivec2& position)
{
	position_ = position;
}

void Camera::move(const glm::ivec2& offset)
{
	position_ += offset;
}

const glm::ivec2& Camera::getPosition() const
{
	return position_;
}

void Camera::update()
{
}

void Camera::zoom(float factor)
{
	zoomFactor_ += factor;
	if (zoomFactor_ <= 0.001)
		zoomFactor_ = 0.001;
}

void Camera::setZoom(float factor)
{
	zoomFactor_ = factor;
}

float Camera::getZoom() const
{
	return zoomFactor_;
}
