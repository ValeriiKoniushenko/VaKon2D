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

#include <chrono>
#include <functional>

class Timer : public Utils::CopyableAndMoveable
{
public:
	Timer();

	bool operator==(const Timer& other) const;

	using Unit = std::chrono::milliseconds;

	enum class Mode : __int8
	{
		Infinity,
		Finite
	};

	void setMode(Mode mode);
	[[nodiscard]] Mode getMode() const;

	void setFrequency(Unit&& frequency);
	[[nodiscard]] const Unit& getFrequency() const;

	void setCallback(std::function<void()> callback);
	void resetCallback();

	void update();

	void start();
	void reset();

	[[nodiscard]] unsigned long long getId() const;

private:
	Mode mode_ = Mode::Finite;
	Unit frequency_ = Unit(1);
	std::chrono::system_clock::time_point lastUpdate_;
	std::function<void()> callback_;
	bool wasCalled_ = false;
	unsigned long long id_ = 0;
	inline static unsigned long long lastGeneratedId = 0;
};