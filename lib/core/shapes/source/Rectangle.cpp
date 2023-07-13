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

#include "Rectangle.h"

#include "CustomShaderProgram.h"
#include "Texture.h"
#include "Window.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Rectangle::draw(CustomShaderProgram& shaderProgram)
{
	if (texture_)
	{
		texture_->bind();
	}
	vao_.bind();

	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(position_, 0.f));
	trans = glm::rotate(trans, rotation_, glm::vec3(0.0f, 0.0f, 1.0f));

	shaderProgram.use();
	shaderProgram.uniform("uTransform", false, trans);
	shaderProgram.uniform(
		"uResolution", static_cast<float>(GetWindow().getSize().width), static_cast<float>(GetWindow().getSize().height));
	shaderProgram.uniform("uGamma", shaderProgram.lightning.gamma);
	shaderProgram.uniform("uBrightness", shaderProgram.lightning.brightness);
	shaderProgram.uniform("uContrast", shaderProgram.lightning.contrast);
	shaderProgram.uniform("uSaturation", shaderProgram.lightning.saturation);
	
	DrawAble::draw(shaderProgram);
}

std::size_t Rectangle::getVerticesCount() const
{
	constexpr std::size_t countOfParts = 4;
	return templateVertices_.size() / countOfParts;
}

void Rectangle::setTexture(Texture& texture)
{
	texture_ = &texture;
}

Texture& Rectangle::getTexture()
{
	return *texture_;
}

void Rectangle::prepare()
{
	if (!vbo_.isGenerated())
	{
		vbo_.generate();
	}

	std::vector<float> vertices = templateVertices_;
	vertices.at(5) *= size_.height * scale_.height;
	vertices.at(8) *= size_.width * scale_.width;
	vertices.at(12) *= size_.width * scale_.width;
	vertices.at(13) *= size_.height * scale_.height;

	vbo_.bind();
	vbo_.data(vertices);

	if (!vao_.isGenerated())
	{
		vao_.generate();
	}
	vao_.bind();
	Gl::Vao::vertexAttribPointer(0, 2, Gl::Type::Float, false, 4 * sizeof(float), (void*) 0);
	Gl::Vao::enableVertexAttribArray(0);

	Gl::Vao::vertexAttribPointer(1, 2, Gl::Type::Float, false, 4 * sizeof(float), reinterpret_cast<const void*>(2 * sizeof(float)));
	Gl::Vao::enableVertexAttribArray(1);

	if (texture_)
	{
		texture_->loadToGpu();
	}
}

void Rectangle::setSize(Utils::FSize2D newSize)
{
	size_ = newSize;
}

Utils::FSize2D Rectangle::getSize() const
{
	return size_;
}

void Rectangle::setScale(Utils::FSize2D newScale)
{
	scale_ = newScale;
}

Utils::FSize2D Rectangle::getScale() const
{
	return scale_;
}
