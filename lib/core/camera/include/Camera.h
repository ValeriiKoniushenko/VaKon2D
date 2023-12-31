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

#include "CopyableAndMoveable.h"
#include "Size.h"
#include "glm/glm.hpp"
#include "Updateable.h"

class Camera : public Utils::CopyableAndMoveable, public Updateable
{
public:
	void setSize(const Utils::ISize2D& size);
	[[nodiscard]] const Utils::ISize2D& getSize() const;

	void setPosition(const glm::vec2& position);
	void move(const glm::vec2& offset);
	[[nodiscard]] const glm::vec2& getPosition() const;

	void update() override;

	void zoom(float factor);
	void setZoom(float factor);
	[[nodiscard]] float getZoom() const;

	void setOrigin(glm::vec2 origin);
	[[nodiscard]] glm::vec2 getOrigin() const;

	[[nodiscard]] glm::vec2 toGlobalCoordinates(glm::vec2 point) const;

	[[nodiscard]] glm::mat4 generateMatrix(glm::vec2 windowSize) const;

	void setTick(float tick);

private:
	Utils::ISize2D size_;
	glm::vec2 position_{};
	float zoomFactor_ = 0.098f;
	glm::vec2 origin_ = {};
	float tick_{1.f};
};