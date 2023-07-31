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

#include "LineText.h"

#include "Font.h"
#include "Window.h"
#include "boost/assert.hpp"
#include "spdlog/spdlog.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <utility>

Font* LineText::getFont() const
{
	return font_;
}

void LineText::setFont(Font& font)
{
	font_ = &font;
	updateCache();
}

const std::string& LineText::getText() const
{
	return text_;
}

void LineText::setText(const std::string& text)
{
	text_ = text;
	updateCache();
}

void LineText::updateCache()
{
	if (!font_)
	{
		return;
	}

	cache_.resize(text_.size());
	auto vert = cache_.begin();

	glm::vec2 position = position_;

	const float scale = fontSize_ / Font::defaultRenderSize * 2.f;
	const float offsetY = getHeightOfTheBiggestLetter();
	for (auto c : text_)
	{
		if (!font_)
		{
			spdlog::get("core")->warn("Can't render a text without font. The font wasn't found");
			break;
		}
		const Font::Character& ch = font_->getCharacter(c);

		const float xpos = position.x + static_cast<float>(ch.bearing.x) * scale;
		const float ypos = position.y - static_cast<float>(ch.size.y - ch.bearing.y) * scale - offsetY * scale;
		const float w = static_cast<float>(ch.size.x) * scale;
		const float h = static_cast<float>(ch.size.y) * scale;

		// clang-format off
		std::vector<float> vertices = {
            xpos + w, ypos,       1.0f, 1.0f,
            xpos + w, ypos + h,   1.0f, 0.0f,
            xpos,     ypos,       0.0f, 1.0f,
			xpos,     ypos + h,   0.0f, 0.0f,
		};
		// clang-format on

		*vert = std::move(vertices);
		position.x += static_cast<float>(ch.advance) * scale;
		++vert;
	}

	setSize({getTextWidth(), getFontSize()});

	BOOST_ASSERT_MSG(cache_.size() == text_.size(), "Invalid count of cache data");
}

void LineText::prepare(ShaderPack& shader)
{
	Widget::prepare(shader);
	shader["text"].use();

	vao_.generate();
	vao_.bind();

	vbo_.generate();
	vbo_.bind();
	vbo_.data(std::vector<float>(dataPerFrame), GL_DYNAMIC_DRAW);

	Gl::Vao::vertexAttribPointer(0, 2, Gl::Type::Float, false, 4 * sizeof(float), reinterpret_cast<void*>(0 * sizeof(float)));
	Gl::Vao::vertexAttribPointer(1, 2, Gl::Type::Float, false, 4 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));
}

void LineText::draw(ShaderPack& shaderPack)
{
	Widget::draw(shaderPack);

	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(position_ / glm::vec2(static_cast<float>(GetWindow().getSize().width) / 2.f,
															static_cast<float>(GetWindow().getSize().height) / 2.f),
									  0.f));
	trans = glm::rotate(trans, rotation_, glm::vec3(0.0f, 0.0f, 1.0f));
	trans[3][1] = -trans[3][1];

	auto& shader = shaderPack["text"];
	shader.use();
	shader.uniform(
		"uResolution", static_cast<float>(GetWindow().getSize().width), static_cast<float>(GetWindow().getSize().height));
	shader.uniform("uColor", toGlColor(color_));
	shader.uniform("uTransform", false, trans);

	Gl::Texture::active(0);
	vao_.bind();

	auto ch = text_.begin();
	auto vert = cache_.begin();

	while (ch != text_.end())
	{
		if (!font_)
		{
			spdlog::get("core")->warn("Can't draw without font");
			BOOST_ASSERT_MSG(false, "Can't draw without font");
			break;
		}

		const Font::Character& oneChar = font_->getCharacter(*ch);
		oneChar.texture.bind();
		vbo_.bind();
		Gl::Vbo::subData(GL_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(sizeof(float) * vert->size()), vert->data());

		Gl::drawArrays(GL_TRIANGLE_STRIP, 0, 4);

		++ch, ++vert;
	}
}

float LineText::getFontSize() const
{
	return fontSize_;
}

void LineText::setFontSize(float size)
{
	if (size < 0.f)
	{
		BOOST_ASSERT_MSG(false, "Font size can't be less than 0");
		spdlog::get("core")->warn("Font size can't be less than 0");
	}

	fontSize_ = size;
	updateCache();
}

LineText::LineText(Font& font, const std::string& text)
{
	setFont(font);
	setText(text);
}

float LineText::getHeightOfTheBiggestLetter()
{
	float maxSize = -fontSize_;
	for (auto ch : text_)
	{
		if (!font_)
		{
			spdlog::get("core")->warn("Can't get character without font");
			BOOST_ASSERT_MSG(false, "Can't get character without font");
			break;
		}

		const auto& oneChar = font_->getCharacter(ch);
		if (static_cast<float>(oneChar.size.y) > maxSize)
		{
			maxSize = static_cast<float>(oneChar.size.y);
		}
	}

	return maxSize;
}

float LineText::getTextWidth() const
{
	if (lastSavedText_ == text_)
	{
		return textWidth_;
	}

	textWidth_ = 0;
	const float scale = fontSize_ / Font::defaultRenderSize;

	for (auto ch : text_)
	{
		if (!font_)
		{
			spdlog::get("core")->warn("Can't get character without font");
			BOOST_ASSERT_MSG(false, "Can't get character without font");
			break;
		}

		const auto& oneChar = font_->getCharacter(ch);
		textWidth_ += static_cast<float>(oneChar.advance) * scale;
	}

	return textWidth_;
}

void LineText::setColor(const Color& color)
{
	color_ = color;
}

const Color& LineText::getColor() const
{
	return color_;
}

boost::property_tree::ptree LineText::toJson() const
{
	auto tree = Widget::toJson();

	boost::property_tree::ptree text;
	text.put("color", std::format("{} {} {} {}", color_.r, color_.g, color_.b, color_.a));
	text.put("text", text_);
	text.put("text-width", getTextWidth());
	text.put("font-size", fontSize_);
	text.put("vbo", vbo_.getId());
	text.put("vao", vao_.getId());
	if (font_)
	{
		boost::property_tree::ptree font;

		font.put("default-render-size", Font::defaultRenderSize);

		text.put_child("font", font);
	}
	tree.put_child("text", text);
	return tree;
}

std::string LineText::getComponentName() const
{
	return componentName;
}
