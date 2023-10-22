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
#include "Image.h"
#include "Rect.h"
#include "ShaderPack.h"
#include "Texture.h"
#include "Widget.h"
#include "glm/glm.hpp"

#include <stdexcept>
#include <chrono>

template<class WidgetT = Widget>
class StopMotionAnimation : public IAnimation
{
public:
	void draw(ShaderPack& shaderPack, Camera* camera = nullptr) override;
	void start() override;
	void stop() override;
	void pause() override;

	void setupAnimation(const Utils::IRect& firstFrame, const Utils::IRect& lastFrame, WidgetT& widget);
	void setupAnimation(WidgetT& widget);
	void setFrameGap(const std::size_t& ms);
	[[nodiscard]] std::size_t getFrameGap() const;
	[[nodiscard]] std::size_t getFramesCount() const;

private:
	WidgetT* widget_ = nullptr;

	std::size_t frameGap_{ 500 };	// ms

	std::chrono::system_clock::time_point lastAnimatingFrame;

	glm::ivec2 startPosition_{};
	glm::ivec2 endPosition_{};
	glm::ivec2 offsetPosition_{};
	glm::ivec2 currentOffsetPosition_{};
	std::size_t framesCount_{};
	Utils::ISize2D textureSize_{};
	Utils::IRect frameSize_{};
	std::size_t currentFrame_{};

	bool isSingleShot = false;

	enum class PingPongDirection
	{
		ToEnd,
		ToStart
	};
	PingPongDirection direction_ = PingPongDirection::ToEnd;
};

namespace
{

enum class Direction
{
	None,
	Vertical,
	Horizontal
};

Direction determineDirection(const Utils::IRect& firstFrame, const Utils::IRect& lastFrame)
{
	if (firstFrame.position.x != lastFrame.position.x && firstFrame.position.y == lastFrame.position.y)
	{
		return Direction::Horizontal;
	}

	if (firstFrame.position.x == lastFrame.position.x && firstFrame.position.y != lastFrame.position.y)
	{
		return Direction::Vertical;
	}

	return Direction::None;
}

}	 // namespace

template<class WidgetT>
void StopMotionAnimation<WidgetT>::setupAnimation(const Utils::IRect& firstFrame, const Utils::IRect& lastFrame, WidgetT& widget)
{
	if (firstFrame.size != lastFrame.size)
	{
		throw std::runtime_error("You can't setup the animation with different texture sizes.");
	}

	widget_ = &widget;

	startPosition_ = firstFrame.position;
	endPosition_ = lastFrame.position;

	textureSize_ = firstFrame.size;

	switch (determineDirection(firstFrame, lastFrame))
	{
		case Direction::Horizontal:
		{
			framesCount_ = static_cast<std::size_t>((lastFrame.position.x - firstFrame.position.x) / firstFrame.size.width);
			offsetPosition_ = glm::ivec2((lastFrame.position.x - firstFrame.position.x) / framesCount_, firstFrame.position.y);
			break;
		}
		case Direction::Vertical:
		{
			framesCount_ = static_cast<std::size_t>((lastFrame.position.y - firstFrame.position.y) / firstFrame.size.height);
			offsetPosition_ = glm::ivec2(firstFrame.position.x, (lastFrame.position.y - firstFrame.position.y) / framesCount_);
			break;
		}
		case Direction::None:
		{
			throw std::runtime_error("Can't determine the direction of the animation. Maybe it's going by diagonal.");
		}
	}

	++framesCount_;
}

template<class WidgetT>
void StopMotionAnimation<WidgetT>::setupAnimation(WidgetT& widget)
{
	Utils::IRect firstFrame;
	Utils::IRect lastFrame;

	firstFrame.position = { 0.f, 0.f };
	if (widget.getSize().width < widget.getSize().height)
	{
		firstFrame.size = { static_cast<int>(widget.getSize().width), static_cast<int>(widget.getSize().width) };
		lastFrame.size = { static_cast<int>(widget.getSize().width), static_cast<int>(widget.getSize().width) };
	}
	else
	{
		firstFrame.size = { static_cast<int>(widget.getSize().height), static_cast<int>(widget.getSize().height) };
		lastFrame.size = { static_cast<int>(widget.getSize().height), static_cast<int>(widget.getSize().height) };
	}

	if (widget.getTexture().getImage()->getSize().x < widget.getTexture().getImage()->getSize().y)
	{
		lastFrame.position = { 0.f, widget.getTexture().getImage()->getSize().y - lastFrame.size.height };
	}
	else
	{
		lastFrame.position = { widget.getTexture().getImage()->getSize().x - lastFrame.size.width, 0.f };
	}

	setupAnimation(firstFrame, lastFrame, widget);
}

template<class WidgetT>
std::size_t StopMotionAnimation<WidgetT>::getFramesCount() const
{
	return framesCount_;
}

template<class WidgetT>
void StopMotionAnimation<WidgetT>::draw(ShaderPack& shaderPack, Camera* camera/* = nullptr*/)
{
	if (!widget_ || state_ == State::Stopped)
	{
		return;
	}

	if (state_ != State::Paused)
	{
		switch (mode_)
		{
			case Mode::PingPong:
			{
				const auto cooldown = (std::chrono::system_clock::now() - lastAnimatingFrame).count() / 10'000ll;
				if (cooldown >= frameGap_)
				{
					if (direction_ == PingPongDirection::ToEnd)
					{
						currentOffsetPosition_ += offsetPosition_;
						++currentFrame_;
					}
					else if (direction_ == PingPongDirection::ToStart)
					{
						currentOffsetPosition_ -= offsetPosition_;
						--currentFrame_;
					}

					if (currentFrame_ >= framesCount_)
					{
						if (direction_ == PingPongDirection::ToEnd)
						{
							currentOffsetPosition_ = endPosition_;
							currentFrame_ = framesCount_ - 1;
							direction_ = PingPongDirection::ToStart;
						}
						else if (direction_ == PingPongDirection::ToStart)
						{
							currentOffsetPosition_ = startPosition_;
							currentFrame_ = 0;
							direction_ = PingPongDirection::ToEnd;
						}
					}

					widget_->setTextureRect(Utils::IRect{currentOffsetPosition_, textureSize_});

					lastAnimatingFrame = std::chrono::system_clock::now();
				}
				break;
			}
			case Mode::Repeating:
			{
				const auto cooldown = (std::chrono::system_clock::now() - lastAnimatingFrame).count() / 10'000ll;
				if (cooldown >= frameGap_)
				{
					if (currentFrame_ >= framesCount_ - 1)
					{
						currentOffsetPosition_ = startPosition_;
						currentFrame_ = 0;
					}

					currentOffsetPosition_ += offsetPosition_;

					++currentFrame_;

					widget_->setTextureRect(Utils::IRect{currentOffsetPosition_, textureSize_});

					lastAnimatingFrame = std::chrono::system_clock::now();
				}
				break;
			}
			case Mode::SingleShot:
			{
				const auto cooldown = (std::chrono::system_clock::now() - lastAnimatingFrame).count() / 10'000ll;
				if (cooldown >= frameGap_)
				{
					if (currentFrame_ >= framesCount_ - 1)
					{
						currentOffsetPosition_ = endPosition_;
						widget_->setTextureRect(Utils::IRect{currentOffsetPosition_, textureSize_});
						currentFrame_ = framesCount_;
						break;
					}

					currentOffsetPosition_ += offsetPosition_;

					++currentFrame_;

					widget_->setTextureRect(Utils::IRect{currentOffsetPosition_, textureSize_});

					lastAnimatingFrame = std::chrono::system_clock::now();
				}
				break;
			}
		}
	}
	widget_->draw(shaderPack, camera);
}

template<class WidgetT>
void StopMotionAnimation<WidgetT>::start()
{
	state_ = State::Running;
}

template<class WidgetT>
void StopMotionAnimation<WidgetT>::stop()
{
	currentOffsetPosition_ = startPosition_;
	state_ = State::Stopped;
}

template<class WidgetT>
void StopMotionAnimation<WidgetT>::pause()
{
	state_ = State::Paused;
}

template<class WidgetT>
void StopMotionAnimation<WidgetT>::setFrameGap(const std::size_t& ms)
{
	frameGap_ = ms;
}

template<class WidgetT>
std::size_t StopMotionAnimation<WidgetT>::getFrameGap() const
{
	return frameGap_;
}