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

#include "Vao.h"

#include "Gl.h"

Vao::Vao(bool isGenerate, bool isBind)
{
	if (isGenerate)
	{
		generate();
	}
	if (isBind)
	{
		bind();
	}
}

Vao::Vao(Vao&& other)
{
	*this = std::move(other);
}

Vao& Vao::operator=(Vao&& other)
{
	id_ = other.id_;
	isBind_ = other.isBind_;

	other.id_ = Vao::invalidId;
	other.isBind_ = false;

	return *this;
}

Vao::~Vao()
{
	destroy();
}

void Vao::generate()
{
	if (isEmpty())
	{
		Gl::Vao::generate(1, &id_);
		if (isEmpty())
		{
			throw std::runtime_error("Vao can't be generate by not defined reasons");
		}
	}
}

void Vao::bind()
{
	if (isEmpty())
	{
		throw std::runtime_error("The VAO is invalid");
	}

	Gl::Vao::bind(id_);
	isBind_ = true;
}

void Vao::bind(GLuint id)
{
	Gl::Vao::bind(id);
}

void Vao::unbind()
{
	if (isEmpty())
	{
		throw std::runtime_error("The VBO has unbound");
	}

	Gl::Vao::reset();
	isBind_ = false;
}

void Vao::destroy()
{
	if (!isEmpty())
	{
		glDeleteVertexArrays(1, &id_);
	}

	id_ = invalidId;
	isBind_ = false;
}

bool Vao::isEmpty() const
{
	return id_ == invalidId;
}

bool Vao::isBind() const
{
	return isBind_;
}
