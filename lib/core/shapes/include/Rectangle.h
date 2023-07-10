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

#include "DrawAble.h"
#include "Size.h"
#include "Vao.h"
#include "Vbo.h"

#include <vector>

class Texture;

class Rectangle : public DrawAble
{
public:
	void draw(ShaderProgram& shaderProgram) override;
	_NODISCARD std::size_t getVerticesCount() const override;

	void setTexture(Texture& texture);
	_NODISCARD Texture& getTexture();

	void setSize(Utils::FSize2D newSize);
	_NODISCARD Utils::FSize2D getSize() const;

	void setScale(Utils::FSize2D newScale);
	_NODISCARD Utils::FSize2D getScale() const;

	void prepare();

private:
	// clang-format off
	inline static const std::vector<float> templateVertices_ = {
		 0.f, 0.f,  0.f, 1.f,
		 0.f,-1.f,  0.f, 0.f,
		 1.f, 0.f,  1.f, 1.f,
		 1.f,-1.f,  1.f, 0.f,
	};
	// clang-format on
	Texture* texture_{};
	Vbo vbo_;
	Vao vao_;
	Utils::FSize2D size_ = {.width = 500.f, .height = 500.f};
	Utils::FSize2D scale_ = {.width = 1.f, .height = 1.f};
};