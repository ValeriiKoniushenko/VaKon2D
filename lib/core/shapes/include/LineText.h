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

#include "Color.h"
#include "CopyableAndMoveable.h"
#include "ShaderPack.h"
#include "Vao.h"
#include "Vbo.h"
#include "Widget.h"
#include "glm/glm.hpp"

#include <string>

class Font;

class LineText : public Widget
{
public:
	LineText(ShaderPack& shaderPack);
	LineText(Font& font, const std::string& text);
	LineText() = default;
	~LineText() = default;
	LineText(const LineText& other);
	LineText(LineText&& other);
	LineText& operator=(const LineText& other);
	LineText& operator=(LineText&& other);

	_NODISCARD Font* getFont() const;
	void setFont(Font& font);

	_NODISCARD const std::string& getText() const;
	void setText(const std::string& text);

	_NODISCARD float getTextWidth() const;
	_NODISCARD float getFontSize() const;
	void setFontSize(float size);

	void setColor(const Color& color);
	_NODISCARD const Color& getColor() const;

	void prepare(ShaderPack& shader) override;

	void draw(ShaderPack& shader) override;

	_NODISCARD boost::property_tree::ptree toJson() const override;
	_NODISCARD std::string getComponentName() const override;

private:
	void updateCache();
	float getHeightOfTheBiggestLetter();

	inline static constexpr std::size_t dataPerFrame = 16;

private:
	Color color_;
	Font* font_;
	std::string text_;
	std::string lastSavedText_;
	mutable float textWidth_ = -1.f;
	Vbo vbo_;
	Vao vao_;
	float fontSize_ = 24.f;
	std::vector<std::vector<float>> cache_;
};