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

#include "ShaderProgram.h"

#include <functional>

class CustomShaderProgram : public ShaderProgram
{
public:
	explicit CustomShaderProgram(const std::string& name);
	CustomShaderProgram(const std::string& name, bool shouldCreate);
	CustomShaderProgram(
		const std::string& name, const std::filesystem::path& pathToVertex, const std::filesystem::path& pathToFragment);
	CustomShaderProgram(const std::string& name, Shader& frag, Shader& vert);

	void OnAfterLink() override;

	struct Lightning
	{
		float gamma = 2.2f;
		float brightness = 0.05f;
		float contrast = 1.2f;
		float saturation = 1.f;
	} lightning;

	bool operator==(const CustomShaderProgram& csp) const;

	[[nodiscard]] const std::string& getName() const;

private:
	const std::string name_;
};