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

#include "Singleton.h"
#include "Size.h"
#include "glm/glm.hpp"

#include <unordered_map>
#include <variant>

class WorldVariables : public Singleton<WorldVariables>
{
public:
	using VariantT = std::variant<int, unsigned int, float, double, glm::vec2, glm::vec3, glm::vec4, glm::mat3, glm::mat4,
		Utils::FSize2D, const char*>;

	void set(const std::string& key, const VariantT& value);
	_NODISCARD const VariantT& get(const std::string& key) const;
	_NODISCARD VariantT& get(const std::string& key);

	_NODISCARD const VariantT& operator[](const std::string& key) const;
	_NODISCARD VariantT& operator[](const std::string& key);

	void forceClear(std::vector<std::string> keys);

private:
	std::unordered_map<std::string, VariantT> data_;
};

WorldVariables& GetWorldVariables();