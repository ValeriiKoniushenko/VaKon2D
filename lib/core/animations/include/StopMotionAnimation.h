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

#include "IAnimation.h"
#include "Rect.h"
#include "glm/glm.hpp"

#include <chrono>

class Widget;

class StopMotionAnimation : public IAnimation
{
public:
	void singleShot() override;
	void draw(ShaderPack& shaderPack) override;
	void start() override;
	void stop() override;
	void pause() override;

	void setupAnimation(const Utils::IRect& firstFrame, const Utils::IRect& lastFrame, Widget& widget);
	void setFrameGap(const std::size_t& ms);
	[[nodiscard]] std::size_t getFrameGap() const;

	[[nodiscard]] std::size_t getFramesCount() const;

private:
	Widget* widget_ = nullptr;

	std::size_t frameGap_{};	// ms

	std::chrono::system_clock::time_point lastAnimatingFrame;

	glm::ivec2 startPosition_{};
	glm::ivec2 endPosition_{};
	glm::ivec2 offsetPosition_{};
	glm::ivec2 currentOffsetPosition_{};
	std::size_t framesCount_{};
	Utils::ISize2D textureSize_{};
	Utils::IRect frameSize_{};
	std::size_t currentFrame_{};
};