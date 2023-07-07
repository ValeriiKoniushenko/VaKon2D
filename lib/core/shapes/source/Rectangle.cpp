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

#include "ShaderProgram.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Rectangle::draw(ShaderProgram& shaderProgram)
{
	if (texture_)
	{
		texture_->bind();
	}
	vao_.bind();

	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, position_);
	trans = glm::rotate(trans, rotation_, glm::vec3(0.0f, 0.0f, 1.0f));

	shaderProgram.use();
	shaderProgram.uniformMatrix4fv("uTransform", false, trans);

	DrawAble::draw(shaderProgram);
}

std::size_t Rectangle::getVerticesCount() const
{
	constexpr std::size_t countOfParts = 4;
	return vertices.size() / countOfParts;
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
	vbo_.generate();
	vbo_.bind();
	vbo_.data(vertices);

	vao_.generate();
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
