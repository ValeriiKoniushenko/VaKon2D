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

#include "GlfwWrapper.h"

#include <vector>

class Vbo
{
public:
	inline static const GLuint invalidId = 0;

	Vbo() = default;
	virtual ~Vbo();

	Vbo(bool shouldGenerate, bool shouldBind);
	explicit Vbo(const std::vector<float>& data, GLenum usage = GL_STATIC_DRAW);

	Vbo(const Vbo&) = default;
	Vbo(Vbo&& Other);
	Vbo& operator=(const Vbo&) = default;
	Vbo& operator=(Vbo&& Other);

	void generate();
	void bind();
	void unbind();
	void destroy();
	_NODISCARD bool isGenerated() const;
	_NODISCARD bool isBind() const;

	void data(const std::vector<float>& vertices, GLenum usage = GL_STATIC_DRAW);

private:
	bool isBind_ = false;
	GLuint id_ = Vbo::invalidId;
};