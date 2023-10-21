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

#include "InstancedWidget.h"

#include "Camera.h"
#include "Image.h"
#include "Mouse.h"
#include "Texture.h"
#include "Window.h"
#include "WorldVariables.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void InstancedWidget::draw(ShaderPack& shaderPack, Camera* camera /* = nullptr*/)
{
	if (!isPrepared)
	{
		prepare(shaderPack);
		if (!isPrepared)
		{
			throw std::runtime_error("The InstancedWidget is not prepared. Use InstancedWidget::prepare before InstancedWidget::draw to resolve it.");
		}
	}

	recalculateVerticiesData();

	auto& shaderProgram = shaderPack["instansed-widget"];
	vao_.bind();
	if (texture_)
	{
		texture_->bind();
	}
	else
	{
		Gl::Texture::bind(Gl::Texture::Target::Texture2D, 0);
	}

	glm::mat4 cameraMatrix = glm::mat4(1.0f);
	glm::vec2 windowSize = glm::vec2(static_cast<float>(GetWindow().getSize().width) / 2.f, static_cast<float>(GetWindow().getSize().height) / 2.f);
	if (camera)
	{
		cameraMatrix = camera->generateMatrix(windowSize);
	}

	shaderProgram.use();
	shaderProgram.uniform("uHasTexture", static_cast<bool>(texture_));
	shaderProgram.uniform("uCameraMatrix", false, cameraMatrix);
	shaderProgram.uniform(
		"uResolution", static_cast<float>(GetWindow().getSize().width), static_cast<float>(GetWindow().getSize().height));
	shaderProgram.uniform("uGamma", shaderProgram.lightning.gamma);
	shaderProgram.uniform("uBrightness", shaderProgram.lightning.brightness);
	shaderProgram.uniform("uContrast", shaderProgram.lightning.contrast);
	shaderProgram.uniform("uSaturation", shaderProgram.lightning.saturation);
	shaderProgram.uniform("uBorderColor", borderColor.r, borderColor.g, borderColor.b, borderColor.a);
	shaderProgram.uniform("uBorderWidth", borderWidth);
	shaderProgram.uniform("uIsDrawBorder", isDrawBorder_);
	if (texture_ && texture_->getImage())
	{
		shaderProgram.uniform("uAtlasSize", texture_->getImage()->getSize());
	}

	InstancedDrawAble::draw(shaderPack);
}

std::size_t InstancedWidget::getVerticesCount() const
{
	constexpr std::size_t countOfParts = 4;
	return templateVertices_.size() / countOfParts;
}

void InstancedWidget::setTexture(Texture& texture)
{
	isPrepared = false;
	texture_ = &texture;
	if (texture.getImage())
	{
		auto size = texture.getImage()->getSize();
		textureRect_.position = {};
		textureRect_.size = {size.x, size.y};
	}
}

Texture& InstancedWidget::getTexture()
{
	if (!texture_)
	{
		throw std::runtime_error("Impossible to get NULL texture");
	}
	return *texture_;
}

void InstancedWidget::prepare(ShaderPack& shader)
{
	shader["instansed-widget"].use();

	recalculateVerticiesData();

	if (!vao_.isGenerated())
	{
		vao_.generate();
	}
	vao_.bind();
	Gl::Vao::vertexAttribPointer(0, 2, Gl::Type::Float, false, 6 * sizeof(float), nullptr);
	Gl::Vao::enableVertexAttribArray(0);

	Gl::Vao::vertexAttribPointer(1, 2, Gl::Type::Float, false, 6 * sizeof(float), reinterpret_cast<const void*>(2 * sizeof(float)));
	Gl::Vao::enableVertexAttribArray(1);

	Gl::Vao::vertexAttribPointer(2, 2, Gl::Type::Float, false, 6 * sizeof(float), reinterpret_cast<const void*>(4 * sizeof(float)));
	Gl::Vao::enableVertexAttribArray(2);

	prepareInstancing();

	if (texture_)
	{
		texture_->bind();
		texture_->loadToGpu();
	}

	isPrepared = true;
}

void InstancedWidget::setSize(Utils::FSize2D newSize)
{
	isPrepared = false;
	size_ = newSize;
}

Utils::FSize2D InstancedWidget::getSize() const
{
	return size_;
}

void InstancedWidget::setScale(Utils::FSize2D newScale)
{
	isPrepared = false;
	scale_ = newScale;
}

Utils::FSize2D InstancedWidget::getScale() const
{
	return scale_;
}

void InstancedWidget::update()
{
	if (getRect().isCollision(GetWindow().getCamera()->toGlobalCoordinates(Mouse::getPosition(GetWindow()))))
	{
		onMouseHover.trigger();

		if (Mouse::isKeyPressed(Mouse::Key::Left))
		{
			onMouseLeftClick.trigger();
		}
		if (Mouse::isKeyPressed(Mouse::Key::Right))
		{
			onMouseRightClick.trigger();
		}
		if (Mouse::isKeyPressed(Mouse::Key::Middle))
		{
			onMouseMiddleClick.trigger();
		}
		try
		{
			if (get<double>(GetWorldVariables()["mouse-wheel-y"]) != 0.)
			{
				onMouseWheel.trigger(get<double>(GetWorldVariables()["mouse-wheel-y"]));
			}
		}
		catch (...)
		{
		}
		try
		{
			if (get<unsigned int>(GetWorldVariables()["inputted-text"]) != 0.)
			{
				onTextInput.trigger(get<unsigned int>(GetWorldVariables()["inputted-text"]));
			}
		}
		catch (...)
		{
		}

		wasHover_ = true;
	}
	else if (wasHover_)
	{
		onMouseUnHover.trigger();
		wasHover_ = false;
	}
}

Utils::FRect InstancedWidget::getRect() const
{
	return {position_, size_};
}

void InstancedWidget::setIsDrawBorder(bool isDraw)
{
	isDrawBorder_ = isDraw;
}

bool InstancedWidget::isDrawBorder() const
{
	return isDrawBorder_;
}

boost::property_tree::ptree InstancedWidget::toJson() const
{
	boost::property_tree::ptree ptree;
	ptree.put("component", getComponentName());
	ptree.put("verticies-count", templateVertices_.size());
	ptree.put("vbo", vbo_.getId());
	ptree.put("vao", vao_.getId());
	ptree.put("width", size_.width);
	ptree.put("height", size_.height);
	ptree.put("scale-width", scale_.width);
	ptree.put("scale-height", scale_.height);
	ptree.put("position-x", position_.x);
	ptree.put("position-y", position_.y);
	if (texture_)
	{
		boost::property_tree::ptree texture;
		texture.put("name", texture_->getName());
		texture.put("mag-filter", Gl::Texture::magFilterToString(texture_->getMagFilter()));
		texture.put("min-filter", Gl::Texture::minFilterToString(texture_->getMinFilter()));
		texture.put("width", texture_->getImage()->getWidth());
		texture.put("height", texture_->getImage()->getHeight());
		texture.put("channel", Image::channelToString(texture_->getImage()->getChannel()));
		texture.put("internal-channel", Gl::Texture::channelToString(texture_->getImage()->getInternalChannel()));

		ptree.add_child("texture", texture);
	}

	return ptree;
}

std::string InstancedWidget::getComponentName() const
{
	return componentName;
}

InstancedWidget::InstancedWidget(InstancedWidget&& other) noexcept
{
	isPrepared = false;
	*this = std::move(other);
}

InstancedWidget& InstancedWidget::operator=(InstancedWidget&& other) noexcept
{
	isPrepared = false;

	textureRect_ = other.textureRect_;
	texture_ = other.texture_;
	vbo_ = other.vbo_;
	vao_ = other.vao_;
	size_ = other.size_;
	scale_ = other.scale_;
	isDrawBorder_ = other.isDrawBorder_;
	wasHover_ = other.wasHover_;
	isPrepared = other.isPrepared;

	onMouseHover = std::move(other.onMouseHover);
	onMouseUnHover = std::move(other.onMouseUnHover);
	onMouseLeftClick = std::move(other.onMouseLeftClick);
	onMouseRightClick = std::move(other.onMouseRightClick);
	onMouseMiddleClick = std::move(other.onMouseMiddleClick);
	onMouseWheel = std::move(other.onMouseWheel);
	onTextInput = std::move(other.onTextInput);

	other.textureRect_ = {};
	other.isPrepared = false;
	other.texture_ = {};
	other.vbo_ = {};
	other.vao_ = {};
	other.size_ = {};
	other.scale_ = {};
	other.isDrawBorder_ = {};
	other.wasHover_ = {};
	other.isPrepared = {};

	return *this;
}

void InstancedWidget::setTextureRect(const Utils::Rect<int>& rect)
{
	textureRect_ = rect;
}

void InstancedWidget::calculateFitTextureSize()
{
	if (texture_ && texture_->getImage())
	{
		auto size = texture_->getImage()->getSize();
		size_.width = size.x;
		size_.height = size.y;
	}
}

void InstancedWidget::recalculateVerticiesData()
{
	if (!vbo_.isGenerated())
	{
		vbo_.generate();
	}

	std::vector<float> vertices = templateVertices_;
	vertices.at(7) *= size_.height * 2.f * scale_.height;	  // TODO: refactor it
	vertices.at(12) *= size_.width * 2.f * scale_.width;	  // TODO: refactor it
	vertices.at(18) *= size_.width * 2.f * scale_.width;	  // TODO: refactor it
	vertices.at(19) *= size_.height * 2.f * scale_.height;	  // TODO: refactor it

	vertices.at(3) *= textureRect_.size.height;
	vertices.at(14) *= textureRect_.size.width;
	vertices.at(15) *= textureRect_.size.height;
	vertices.at(20) *= textureRect_.size.width;

	vertices.at(4) = textureRect_.position.x;
	vertices.at(5) = textureRect_.position.y;
	vertices.at(10) = textureRect_.position.x;
	vertices.at(11) = textureRect_.position.y;
	vertices.at(16) = textureRect_.position.x;
	vertices.at(17) = textureRect_.position.y;
	vertices.at(22) = textureRect_.position.x;
	vertices.at(23) = textureRect_.position.y;

	vbo_.bind();
	vbo_.data(vertices);
}

const Texture& InstancedWidget::getTexture() const
{
	if (texture_)
	{
		throw std::runtime_error("Impossible to get NULL texture");
	}
	return *texture_;
}

void InstancedWidget::prepareInstancing()
{
	if (!vboInstancing_.isGenerated())
	{
		vboInstancing_.generate();
	}
	vboInstancing_.bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * transforms_.size(), transforms_.data(), GL_STATIC_DRAW);
	Gl::Vao::vertexAttribPointer(3, 2, Gl::Type::Float, false, sizeof(float) * 2, (void*)(0));
	glVertexAttribDivisor(3, 1);
	Gl::requireNoErrors();
}
