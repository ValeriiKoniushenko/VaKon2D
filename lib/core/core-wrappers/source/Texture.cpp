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

#include "Texture.h"

Texture::Texture(Gl::Texture::Target target) : target_(target)
{
	generate();
	bind();
}

Texture::~Texture()
{
	if (isDestroyAtEnd_)
	{
		destroy();
	}
}

void Texture::bind() const
{
	if (!wasGenerated())
	{
		throw std::runtime_error("You should generate a texture before binding");
	}

	glBindTexture(static_cast<GLenum>(target_), id_);
}

void Texture::unbind() const
{
	if (!wasGenerated())
	{
		throw std::runtime_error("You should generate a texture before unbinding");
	}

	glBindTexture(static_cast<GLenum>(target_), 0);
}

void Texture::destroy()
{
	glDeleteTextures(1, &id_);
	id_ = Gl::Texture::invalidId;
	target_ = Gl::Texture::Target::None;
	isDestroyAtEnd_ = true;
}

bool Texture::wasGenerated() const
{
	return id_ == Gl::Texture::invalidId;
}

GLuint Texture::data()
{
	return id_;
}

bool Texture::isDestroyAtEnd() const
{
	return isDestroyAtEnd_;
}

void Texture::setIsDestroyAtEnd(bool is)
{
	isDestroyAtEnd_ = is;
}

void Texture::generate()
{
	glGenTextures(1, &id_);
}
