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

#include "DrawAble.h"

#include "Gl.h"

void DrawAble::draw(CustomShaderProgram& shaderProgram)
{
	Gl::drawArrays(GL_TRIANGLE_STRIP, 0, getVerticesCount());
}

std::size_t DrawAble::getVerticesCount() const
{
	return 0;
}

void DrawAble::setPosition(const glm::vec2& newPosition)
{
	position_ = newPosition;
}

void DrawAble::move(const glm::vec2& offset)
{
	position_ += offset;
}

const glm::vec2& DrawAble::getPosition() const
{
	return position_;
}

void DrawAble::setRotation(float newRotation)
{
	rotation_ = newRotation;
}

void DrawAble::rotate(float offset)
{
	rotation_ += offset;
}

float DrawAble::getRotation() const
{
	return rotation_;
}
