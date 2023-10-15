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
	inline static constexpr const char* componentName = "line-text";

	LineText(Font& font, const std::string& text);
	LineText() = default;
	~LineText() override = default;
	LineText(LineText&& other) = default;
	LineText& operator=(LineText&& other) = default;

	[[nodiscard]] Font* getFont() const;
	void setFont(Font& font);

	[[nodiscard]] const std::string& getText() const;
	void setText(const std::string& text);

	[[nodiscard]] float getTextWidth() const;
	[[nodiscard]] float getTextHeight() const;
	[[nodiscard]] float getFontSize() const;
	void setFontSize(float size);

	void setColor(const Color& color);
	[[nodiscard]] const Color& getColor() const;

	void prepare(ShaderPack& shader) override;

	void draw(ShaderPack& shader, Camera* camera = nullptr) override;

	[[nodiscard]] boost::property_tree::ptree toJson() const override;
	[[nodiscard]] std::string getComponentName() const override;

private:
	void updateCache();
	float getHeightOfTheBiggestLetter();

	inline static constexpr std::size_t dataPerFrame = 16;

private:
	Color color_;
	Font* font_ = nullptr;
	std::string text_;
	std::string lastSavedText_;
	mutable float textWidth_ = -1.f;
	mutable float textHeight_ = -1.f;
	Vbo vbo_;
	Vao vao_;
	float fontSize_ = 24.f;
	std::vector<std::vector<float>> cache_;
};