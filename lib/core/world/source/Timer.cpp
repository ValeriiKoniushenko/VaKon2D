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

#include "Timer.h"

void Timer::setMode(Mode mode)
{
	mode_ = mode;
}

Timer::Mode Timer::getMode() const
{
	return mode_;
}

void Timer::setFrequency(Unit&& frequency)
{
	frequency_ = std::forward<Unit>(frequency);
}

const Timer::Unit& Timer::getFrequency() const
{
	return frequency_;
}

void Timer::setCallback(std::function<void()> callback)
{
	callback_ = callback;
}

void Timer::resetCallback()
{
	callback_ = nullptr;
}

void Timer::update()
{
	if (!callback_)
	{
		return;
	}

	if (mode_ == Mode::Finite && !wasCalled_)
	{
		if (std::chrono::duration_cast<Unit>(std::chrono::system_clock::now() - lastUpdate_) >= frequency_)
		{
			callback_();
			wasCalled_ = true;
		}
	}
	else if (mode_ == Mode::Infinity)
	{
		if (std::chrono::duration_cast<Unit>(std::chrono::system_clock::now() - lastUpdate_) >= frequency_)
		{
			callback_();
			lastUpdate_ = std::chrono::system_clock::now();
		}
	}
}

void Timer::start()
{
	lastUpdate_ = std::chrono::system_clock::now();
}

void Timer::reset()
{
	wasCalled_ = false;
}

Timer::Timer()
{
	id_ = ++lastGeneratedId;
}

unsigned long long Timer::getId() const
{
	return id_;
}

bool Timer::operator==(const Timer& other) const
{
	return id_ == other.id_;
}
