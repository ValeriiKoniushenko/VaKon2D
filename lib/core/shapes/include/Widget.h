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

#include "Delegate.h"
#include "DrawAble.h"
#include "JsonPrintable.h"
#include "Keyboard.h"
#include "Rect.h"
#include "Size.h"
#include "Updateable.h"
#include "Vao.h"
#include "Vbo.h"

#include <vector>

class Texture;

class Widget : public DrawAble, public JsonPrintable, public Updateable
{
public:
	inline static constexpr glm::vec4 borderColor = {1.f, 1.f, 0.f, 1.f};
	inline static constexpr float borderWidth = 0.05f;
	inline static constexpr const char* componentName = "widget";

	Widget();
	~Widget();

	void draw(ShaderPack& shaderProgram) override;
	_NODISCARD std::size_t getVerticesCount() const override;

	void setTexture(Texture& texture);
	_NODISCARD Texture& getTexture();

	void setSize(Utils::FSize2D newSize);
	_NODISCARD Utils::FSize2D getSize() const;

	void setScale(Utils::FSize2D newScale);
	_NODISCARD Utils::FSize2D getScale() const;

	_NODISCARD Utils::FRect getRect() const;

	void setIsDrawBorder(bool isDraw);
	_NODISCARD bool isDrawBorder() const;

	virtual void prepare(ShaderPack& shader);

	void update() override;

	_NODISCARD virtual std::string getComponentName() const;

	LambdaMulticastDelegate<void()> onMouseHover;
	LambdaMulticastDelegate<void()> onMouseUnHover;
	LambdaMulticastDelegate<void()> onMouseLeftClick;
	LambdaMulticastDelegate<void()> onMouseRightClick;
	LambdaMulticastDelegate<void()> onMouseMiddleClick;
	LambdaMulticastDelegate<void(double)> onMouseWheel;
	LambdaMulticastDelegate<void(unsigned int)> onTextInput;

	_NODISCARD boost::property_tree::ptree toJson() const override;

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
	Utils::FSize2D size_ = {.width = 100.f, .height = 100.f};
	Utils::FSize2D scale_ = {.width = 1.f, .height = 1.f};
	bool isDrawBorder_ = false;
	bool wasHover_ = false;
};