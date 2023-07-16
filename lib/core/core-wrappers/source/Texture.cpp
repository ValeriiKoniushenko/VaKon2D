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

#include "Image.h"

Texture::Texture(Gl::Texture::Target target, bool shouldGenerate, bool shouldBind) : target_(target)
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

	Gl::Texture::bind(target_, id_);
	if (minFilter_ != Gl::Texture::MinFilter::None)
	{
		Gl::Texture::setMinFilter(minFilter_, target_);
	}
	if (magFilter_ != Gl::Texture::MagFilter::None)
	{
		Gl::Texture::setMagFilter(magFilter_, target_);
	}
}

void Texture::unbind() const
{
	if (!wasGenerated())
	{
		throw std::runtime_error("You should generate a texture before unbinding");
	}

	Gl::Texture::bind(target_, Gl::Texture::invalidId);
}

void Texture::destroy()
{
	Gl::Texture::deleteTexture(id_);
	id_ = Gl::Texture::invalidId;
	target_ = Gl::Texture::Target::None;
	isDestroyAtEnd_ = true;
}

bool Texture::wasGenerated() const
{
	return id_ != Gl::Texture::invalidId;
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
	id_ = Gl::Texture::generate();
}

void Texture::generateMipMap()
{
	if (!ignoreMipMap_)
	{
		Gl::Texture::generateMipmap(target_);
	}
}

void Texture::setImage(Image& image)
{
	image_ = &image;
}

Image* Texture::getImage()
{
	return image_;
}

void Texture::ignoreMipMapGeneration(bool ignore)
{
	ignoreMipMap_ = ignore;
}

void Texture::loadToGpu()
{
	image_->loadToGpu();
	generateMipMap();
	Gl::Texture::setMinFilter(minFilter_, target_);
	Gl::Texture::setMagFilter(magFilter_, target_);
}

void Texture::setMagFilter(Gl::Texture::MagFilter filter)
{
	magFilter_ = filter;
}

Gl::Texture::MagFilter Texture::getMagFilter() const
{
	return magFilter_;
}

void Texture::setMinFilter(Gl::Texture::MinFilter filter)
{
	minFilter_ = filter;
}

Gl::Texture::MinFilter Texture::getMinFilter() const
{
	return minFilter_;
}

void Texture::setMagAndMinFilter(Gl::Texture::MagFilter magFilter, Gl::Texture::MinFilter minFilter)
{
	setMagFilter(magFilter);
	setMinFilter(minFilter);
}

std::string Texture::getName() const
{
	if (image_)
	{
		return image_->getName();
	}
	return "";
}
