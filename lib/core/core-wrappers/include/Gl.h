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
#include "Vao.h"
#include "Vbo.h"

class Gl
{
public:
	Gl() = delete;

	class Vao
	{
	public:
		static void generate(GLsizei n, GLuint* arrays);
		static void bind(GLuint array);
		static void reset();
		static bool isBind();

	private:
		inline static GLuint id_ = ::Vao::invalidId;
	};

	class Vbo
	{
	public:
		static void generate(GLsizei n, GLuint* arrays);
		static void bind(GLenum target, GLuint buffer);
		static void reset(GLenum target);
		static bool isBind();
		static void data(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
		static void subData(GLenum target, GLintptr offset, GLsizeiptr size, const void* data);

	private:
		inline static GLuint id_ = ::Vbo::invalidId;
	};

	static void enableVertexAttribArray(GLuint index);
	static void disableVertexAttribArray(GLuint index);
	static void vertexAttribPointer(
		GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
};