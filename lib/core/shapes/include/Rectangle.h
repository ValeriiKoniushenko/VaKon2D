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

	void prepare();

private:
	// clang-format off
	const std::vector<float> vertices = {
		0.f,   0.f,    0.f, 0.f,
		500.f, 0.f,    1.f, 0.f,
		0.f,   500.f,  0.f, 1.f,
		500.f, 500.f,  1.f, 1.f,
	};
	// clang-format on

	Texture* texture_{};
	Vbo vbo_;
	Vao vao_;
};