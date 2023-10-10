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

#include "Gl.h"
#include "GlfwWrapper.h"
#include "NotCopyableButMovable.h"
#include "stb_image.h"

#include <string>

class Image;

class Texture : public Utils::NotCopyableButMovable
{
public:
	explicit Texture(
		Gl::Texture::Target target = Gl::Texture::Target::Texture2D, bool shouldGenerate = false, bool shouldBind = false);

	~Texture() override;
	Texture(Texture&& other) noexcept;
	Texture& operator=(Texture&& other) noexcept;

	void bind() const;
	void unbind() const;
	void destroy();
	[[nodiscard]] bool wasGenerated() const;
	[[nodiscard]] GLuint data();
	void generateMipMap();

	[[nodiscard]] bool isDestroyAtEnd() const;
	void setIsDestroyAtEnd(bool is);

	void setImage(Image& image);
	[[nodiscard]] Image* getImage();

	void ignoreMipMapGeneration(bool ignore);
	void loadToGpu();

	void setMagAndMinFilter(Gl::Texture::MagFilter magFilter, Gl::Texture::MinFilter minFilter);

	void setMagFilter(Gl::Texture::MagFilter filter);
	[[nodiscard]] Gl::Texture::MagFilter getMagFilter() const;

	void setMinFilter(Gl::Texture::MinFilter filter);
	[[nodiscard]] Gl::Texture::MinFilter getMinFilter() const;

	[[nodiscard]] std::string getName() const;

private:
	void generate();

private:
	GLuint id_ = Gl::Texture::invalidId;
	Gl::Texture::Target target_ = Gl::Texture::Target::None;
	bool isDestroyAtEnd_ = true;
	Image* image_{};
	bool ignoreMipMap_ = false;
	Gl::Texture::MagFilter magFilter_ = Gl::Texture::MagFilter::None;
	Gl::Texture::MinFilter minFilter_ = Gl::Texture::MinFilter::None;
};