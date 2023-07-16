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

#include "Delegate.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Updateable.h"

#include <chrono>
#include <string>

template <class KeyT>
class InputAction : public Updateable
{
private:
	enum class State
	{
		None,
		Pressed
	};

public:
	using TimeT = std::chrono::milliseconds;

	explicit InputAction(const std::string& name, KeyT key) : name_(name), key_(key)
	{
	}

	_NODISCARD const std::string& getName() const
	{
		return name_;
	}

	void setName(const std::string& newName)
	{
		name_ = newName;
	}

	void setFrequency(TimeT value)
	{
		frequency_ = value;
	}

	_NODISCARD TimeT getFrequency() const
	{
		return frequency_;
	}

	void update()
	{
		if (isKeyPressed())
		{
			if (lastState_ != State::Pressed || isRepeatable_)
			{
				if (std::chrono::duration_cast<TimeT>(std::chrono::system_clock::now() - lastUpdate_) >= frequency_)
				{
					onAction.trigger();
					lastUpdate_ = std::chrono::system_clock::now();
					lastState_ = State::Pressed;
				}
			}
		}
		else
		{
			lastState_ = State::None;
		}
	}

	void setKey(Keyboard::Key key)
	{
		key_ = key;
	}

	_NODISCARD Keyboard::Key getKey() const
	{
		return key_;
	}

	_NODISCARD bool getIsRepeatable() const
	{
		return isRepeatable_;
	}

	void setIsRepeatable(bool isRepeatable)
	{
		isRepeatable_ = isRepeatable;
	}

	LambdaMulticastDelegate<void()> onAction;

protected:
	_NODISCARD virtual bool isKeyPressed() const = 0;

protected:
	std::string name_;
	KeyT key_{};
	TimeT frequency_ = TimeT(50);
	std::chrono::system_clock::time_point lastUpdate_{};
	State lastState_ = State::None;
	bool isRepeatable_ = true;
};

class KeyboardInputAction : public InputAction<Keyboard::Key>
{
public:
	explicit KeyboardInputAction(const std::string& name, Keyboard::Key key);

protected:
	_NODISCARD bool isKeyPressed() const override;
};

class MouseInputAction : public InputAction<Mouse::Key>
{
public:
	explicit MouseInputAction(const std::string& name, Mouse::Key key);

protected:
	_NODISCARD bool isKeyPressed() const override;
};