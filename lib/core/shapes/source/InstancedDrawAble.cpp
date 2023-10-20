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

#include "InstancedDrawAble.h"
#include "Camera.h"

#include "Gl.h"

void InstancedDrawAble::draw(ShaderPack& shaderPack, Camera* camera/* = nullptr*/)
{
	Gl::drawArraysInstanced(GL_TRIANGLE_STRIP, 0, getVerticesCount(), transforms_.size());
}

std::size_t InstancedDrawAble::getVerticesCount() const
{
	return 0;
}

void InstancedDrawAble::setPosition(const glm::vec2& newPosition)
{
	position_ = newPosition;
}

void InstancedDrawAble::move(const glm::vec2& offset)
{
	position_ += offset;
}

const glm::vec2& InstancedDrawAble::getPosition() const
{
	return position_;
}

void InstancedDrawAble::setRotation(float newRotation)
{
	rotation_ = newRotation;
}

void InstancedDrawAble::rotate(float offset)
{
	rotation_ += offset;
}

float InstancedDrawAble::getRotation() const
{
	return rotation_;
}

std::vector<glm::vec2>& InstancedDrawAble::getTransforms()
{
	return transforms_;
}

const std::vector<glm::vec2>& InstancedDrawAble::getTransforms() const
{
	return transforms_;
}
