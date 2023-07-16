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

#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Image::Image(std::filesystem::path&& path)
{
	init_();
	if (!path.empty())
	{
		loadImage(std::forward<std::filesystem::path>(path));
	}
}

Image::~Image()
{
	clear();
}

Image::Image(Image&& obj) noexcept
{
	init_();
	*this = std::move(obj);
}

Image& Image::operator=(Image&& obj)
{
	clear();
	this->data_ = obj.data_;
	this->width_ = obj.width_;
	this->height_ = obj.height_;
	this->channel_ = obj.channel_;
	obj.init_();
	return *this;
}

void Image::init_()
{
	data_ = nullptr;
	width_ = height_ = 0;
	channel_ = Channel::None;
}

int Image::getWidth() const
{
	if (isEmpty())
	{
		throw std::runtime_error("Image wasn't loaded. You can't take a width without a photo");
	}

	return width_;
}

int Image::getHeight() const
{
	if (isEmpty())
	{
		throw std::runtime_error("Image wasn't loaded. You can't take a height without a photo");
	}

	return height_;
}

glm::ivec2 Image::getSize() const
{
	if (isEmpty())
	{
		throw std::runtime_error("Image wasn't loaded. You can't take a height without a photo");
	}

	return glm::ivec2(width_, height_);
}

Image::Channel Image::getChannel() const
{
	if (isEmpty())
	{
		throw std::runtime_error("Image wasn't loaded. You can't take a channels without a photo");
	}

	return channel_;
}

unsigned char* Image::data()
{
	if (isEmpty())
	{
		throw std::runtime_error("The image wasn't loaded");
	}

	return data_;
}

const unsigned char* Image::data() const
{
	if (isEmpty())
	{
		throw std::runtime_error("The mage wasn't loaded");
	}

	return data_;
}

void Image::loadImage(std::filesystem::path&& path, bool isFlipVertically)
{
	clear();
	stbi_set_flip_vertically_on_load(isFlipVertically);
	int channel = 0;
	data_ = stbi_load(path.string().c_str(), &width_, &height_, &channel, 0);
	if (isEmpty())
	{
		throw std::runtime_error("The mage wasn't loaded: impossible to find the image by this path or undefined error");
	}

	channel_ = static_cast<Channel>(channel);
	name_ = path.stem().string();
}

void Image::clear()
{
	if (data_)
	{
		stbi_image_free(data_);
		data_ = nullptr;
	}
	width_ = height_ = 0;
	channel_ = Channel::None;
}

bool Image::isEmpty() const
{
	return data_ == nullptr;
}

GLenum Image::convertChannelToGlChannel(Image::Channel channel)
{
	switch (channel)
	{
		case Channel::RGB:
			return GL_RGB;
		case Channel::RGBA:
			return GL_RGBA;
		default:
			throw std::runtime_error("OpenGL does not such type of the channel or was passed an invalid type of the channel");
	}

	return {};
}

void Image::loadToGpu()
{
	Gl::Texture::texImage2D(Gl::Texture::Target::Texture2D, 0, static_cast<GLenum>(internalChannel_), width_, height_, 0,
		convertChannelToGlChannel(channel_), GL_UNSIGNED_BYTE, data_);
}

void Image::setInternalChannel(Gl::Texture::Channel channel)
{
	internalChannel_ = channel;
}

Gl::Texture::Channel Image::getInternalChannel() const
{
	return internalChannel_;
}

std::string Image::getName() const
{
	return name_;
}

std::string Image::channelToString(Image::Channel channel)
{
	if (channel == Channel::RGB)
		return "RGB";
	else if (channel == Channel::Grey)
		return "Grey";
	else if (channel == Channel::GreyA)
		return "GreyA";
	else if (channel == Channel::RGBA)
		return "RGBA";

	return "none";
}
