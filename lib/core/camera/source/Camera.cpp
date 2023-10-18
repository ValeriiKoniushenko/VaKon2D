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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

void Camera::setSize(const Utils::ISize2D& size)
{
	size_ = size;
	GetWindow().viewport(0,0, size.width, size.height);
}

const Utils::ISize2D& Camera::getSize() const
{
	return size_;
}

void Camera::setPosition(const glm::vec2& position)
{
	position_ = position;
}

void Camera::move(const glm::vec2& offset)
{
	position_ += offset * tick_;
}

const glm::vec2& Camera::getPosition() const
{
	return position_;
}

void Camera::update()
{
}

void Camera::zoom(float factor)
{
	zoomFactor_ += factor * tick_ * zoomFactor_;
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

void Camera::setOrigin(glm::vec2 origin)
{
	origin_ = origin;
}

glm::vec2 Camera::getOrigin() const
{
	return origin_;
}

glm::mat4 Camera::generateMatrix(glm::vec2 windowSize) const
{
	auto matrix = glm::mat4(1.0);

	glm::vec2 cameraPosition = glm::vec2(position_.x, position_.y);
	cameraPosition = cameraPosition / windowSize;
	cameraPosition.x = -cameraPosition.x;

	glm::vec2 cameraOriginPosition = origin_;
	cameraOriginPosition = cameraOriginPosition / windowSize;
	cameraOriginPosition.y = -cameraOriginPosition.y;

	matrix = glm::translate(matrix, glm::vec3(cameraPosition, 0.f));
	matrix = glm::scale(matrix, glm::vec3(zoomFactor_, zoomFactor_, 1.f));
	matrix = glm::translate(matrix, glm::vec3(cameraOriginPosition, 0.f));

	return matrix;
}

glm::vec2 Camera::toGlobalCoordinates(glm::vec2 point) const
{
	point += position_;
	point += -origin_;
	point /= zoomFactor_;
	return point;
}

void Camera::setTick(float tick)
{
	tick_ = tick;
}
