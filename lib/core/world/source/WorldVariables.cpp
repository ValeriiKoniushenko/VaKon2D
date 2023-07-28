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

#include "WorldVariables.h"

void WorldVariables::set(const std::string& key, const VariantT& value)
{
	auto it = data_.find(key);
	if (it == data_.end())
	{
		data_.emplace(key, value);
	}
	else
	{
		it->second = value;
	}
}

const WorldVariables::VariantT& WorldVariables::get(const std::string& key) const
{
	auto it = data_.find(key);
	if (it == data_.end())
	{
		throw std::runtime_error("WorldVariables: no such key: " + key);
	}

	return it->second;
}

WorldVariables::VariantT& WorldVariables::get(const std::string& key)
{
	auto it = data_.find(key);
	if (it == data_.end())
	{
		data_.emplace(key, VariantT{});
		it = data_.find(key);
	}

	return it->second;
}

const WorldVariables::VariantT& WorldVariables::operator[](const std::string& key) const
{
	return get(key);
}

WorldVariables::VariantT& WorldVariables::operator[](const std::string& key)
{
	return get(key);
}

void WorldVariables::forceClear(const std::vector<std::string>& keys)
{
	for (auto& key : keys)
	{
		if (auto it = data_.find(key); it != data_.end())
		{
			it->second = {};
		}
	}
}

WorldVariables& GetWorldVariables()
{
	return WorldVariables::instance();
}
