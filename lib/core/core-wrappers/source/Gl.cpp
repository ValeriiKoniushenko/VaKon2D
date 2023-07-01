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

#include "Gl.h"

void Gl::Vao::generate(GLsizei n, GLuint* arrays)
{
	if (isBind())
	{
		throw std::runtime_error("You can not to generate new VAO buffer with a bound VAO. Reset VAO and try again.");
	}

	glGenVertexArrays(n, arrays);
}

void Gl::Vao::bind(GLuint array)
{
	if (isBind())
	{
		throw std::runtime_error(
			"You try to bind a VAO again. The best way is to unbind a VAO after the last using or shader setting up.");
	}

	glBindVertexArray(array);

	Gl::Vao::id_ = array;
}

void Gl::Vao::reset()
{
	glBindVertexArray(::Vao::invalidId);

	Gl::Vao::id_ = ::Vao::invalidId;
}

bool Gl::Vao::isBind()
{
	return Gl::Vao::id_ != ::Vao::invalidId;
}

void Gl::Vbo::generate(GLsizei n, GLuint* arrays)
{
	glGenBuffers(n, arrays);
}

void Gl::Vbo::bind(GLenum target, GLuint buffer)
{
	glBindBuffer(target, buffer);

	Gl::Vbo::id_ = buffer;
}

void Gl::Vbo::reset(GLenum target)
{
	glBindBuffer(target, 0u);

	Gl::Vbo::id_ = ::Vbo::invalidId;
}

bool Gl::Vbo::isBind()
{
	return Gl::Vbo::id_ != ::Vbo::invalidId;
}

void Gl::Vbo::data(GLenum target, GLsizeiptr size, const void* data, GLenum usage)
{
	if (!isBind())
	{
		throw std::runtime_error("Impossible to put data to unbound VBO.");
	}

	glBufferData(target, size, data, usage);
}

void Gl::Vbo::subData(GLenum target, GLintptr offset, GLsizeiptr size, const void* data)
{
	if (!Gl::Vao::isBind())
	{
		throw std::runtime_error("You try to set up a shader using a zero VAO. Try to bind a VAO and try again.");
	}

	if (!isBind())
	{
		throw std::runtime_error("Impossible to put data to unbound VBO.");
	}

	glBufferSubData(target, offset, size, data);
}

void Gl::enableVertexAttribArray(GLuint index)
{
	if (!Gl::Vao::isBind())
	{
		throw std::runtime_error("You try to set up a shader using a zero VAO. Try to bind a VAO and try again.");
	}

	glEnableVertexAttribArray(index);
}

void Gl::disableVertexAttribArray(GLuint index)
{
	if (!Gl::Vao::isBind())
	{
		throw std::runtime_error("You try to set up a shader using a zero VAO. Try to bind a VAO and try again.");
	}

	glDisableVertexAttribArray(index);
}

void Gl::vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
{
	if (!Gl::Vao::isBind())
	{
		throw std::runtime_error("You try to set up a shader using a zero VAO. Try to bind a VAO and try again.");
	}

	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}