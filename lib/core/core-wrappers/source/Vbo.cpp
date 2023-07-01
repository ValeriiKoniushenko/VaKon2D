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

#include "Vbo.h"

#include "Gl.h"

Vbo::Vbo(bool shouldGenerate, bool shouldBind)
{
	if (shouldGenerate)
	{
		generate();
	}
	if (shouldBind)
	{
		bind();
	}
}

Vbo::Vbo(Vbo&& other)
{
	*this = std::move(other);
}

Vbo& Vbo::operator=(Vbo&& other)
{
	id_ = other.id_;
	isBind_ = other.isBind_;

	other.isBind_ = false;
	other.id_ = Vbo::invalidId;

	return *this;
}

Vbo::~Vbo()
{
	destroy();
}

void Vbo::generate()
{
	if (isEmpty())
	{
		glGenBuffers(1, &id_);
		if (isEmpty())
		{
			throw std::runtime_error("VBO can't be generate by not defined reasons");
		}
	}
}

void Vbo::bind()
{
	if (isEmpty())
	{
		throw std::runtime_error("VBO is empty. Try to regenerate and try again.");
	}

	Gl::Vbo::bind(GL_ARRAY_BUFFER, id_);
	isBind_ = true;
}

void Vbo::bind(GLuint id)
{
	Gl::Vbo::bind(GL_ARRAY_BUFFER, id);
}

void Vbo::unbind()
{
	if (!isEmpty())
	{
		throw std::runtime_error("VBO is empty. Try to regenerate and try again.");
	}

	Gl::Vbo::reset(GL_ARRAY_BUFFER);
	isBind_ = false;
}

void Vbo::destroy()
{
	glDeleteBuffers(1, &id_);
	id_ = invalidId;
}

bool Vbo::isEmpty() const
{
	return id_ == invalidId;
}

bool Vbo::isBind() const
{
	return isBind_;
}

void Vbo::setData(const std::vector<float>& data, GLenum usage)
{
	if (isEmpty())
	{
		throw std::runtime_error("VBO is empty. Try to regenerate and try again.");
	}

	if (!isBind())
	{
		throw std::runtime_error("You try to put data to unbinded VBO. Bind it and try again");
	}

	Gl::Vbo::data(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(), GL_STATIC_DRAW);
}