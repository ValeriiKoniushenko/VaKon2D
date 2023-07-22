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

#include <functional>
#include <utility>
#include <vector>

template <class T, class CallbackT>
class Delegate : public Utils::CopyableAndMoveable
{
public:
	template <class... TArgs>
	void trigger(TArgs&&... args)
	{
		if (callback_ && objP)
		{
			std::invoke(callback_, objP, std::forward<TArgs>(args)...);
		}
	}

	void subscribe(T* obj, CallbackT&& callback)
	{
		callback_ = std::forward<CallbackT>(callback);
		objP = obj;
	}

	void reset()
	{
		callback_ = {};
		objP = {};
	}

private:
	CallbackT callback_{};
	T* objP{};
};

template <class F>
class LambdaDelegate : public Utils::CopyableAndMoveable
{
public:
	using CallbackT = std::function<F>;

	template <class... TArgs>
	void trigger(TArgs&&... args)
	{
		if (callback_)
		{
			std::invoke(callback_, std::forward<TArgs>(args)...);
		}
	}

	void subscribe(CallbackT&& callback)
	{
		callback_ = std::forward<CallbackT>(callback);
	}

	void reset()
	{
		callback_ = {};
	}

private:
	CallbackT callback_{};
};

template <class F>
class LambdaMulticastDelegate : public Utils::CopyableAndMoveable
{
public:
	using CallbackT = std::function<F>;

	template <class... TArgs>
	void trigger(TArgs&&... args)
	{
		for (auto& callback : callbacks_)
		{
			std::invoke(callback, std::forward<TArgs>(args)...);
		}
	}

	void subscribe(CallbackT&& callback)
	{
		callbacks_.emplace_back(std::forward<CallbackT>(callback));
	}

	void reset()
	{
		callbacks_.clear();
	}

private:
	std::vector<CallbackT> callbacks_{};
};