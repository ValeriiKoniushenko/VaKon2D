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

#include <utility>

LineText::LineText(const LineText& other)
{
	*this = other;
}

LineText::LineText(LineText&& other)
{
	*this = std::move(other);
}

LineText& LineText::operator=(const LineText& other)
{
}

LineText& LineText::operator=(LineText&& other)
{
}

Font* LineText::getFont() const
{
	return font_;
}

void LineText::setFont(Font& font)
{
	font_ = &font;
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

const glm::vec2& LineText::getPosition() const
{
	return position_;
}

void LineText::setPosition(const glm::vec2& position)
{
	position_ = position;
}

void LineText::updateCache()
{
	cache_.resize(text_.size());
	auto vert = cache_.begin();

	glm::vec2 position = position_;

	const float scale = fontSize_ / Font::defaultRenderSize * 2.f;
	for (auto c = text_.begin(); c != text_.end(); ++c)
	{
		if (!font_)
		{
			spdlog::get("core")->warn("Can't render a text without font. The font wasn't found");
			break;
		}
		const Font::Character& ch = font_->getCharacter(*c);

		const float xpos = position.x + static_cast<float>(ch.bearing.x) * scale;
		const float ypos = position.y - static_cast<float>(ch.size.y - ch.bearing.y) * scale;
		const float w = ch.size.x * scale;
		const float h = ch.size.y * scale;

		// clang-format off
		std::vector<float> vertices = {
            xpos + w, ypos,       1.0f, 1.0f,
            xpos + w, ypos + h,   1.0f, 0.0f,
            xpos,     ypos,       0.0f, 1.0f,
			xpos,     ypos + h,   0.0f, 0.0f,
		};
		// clang-format on

		*vert = std::move(vertices);
		position.x += ch.advance * scale;
		++vert;
	}

	BOOST_ASSERT_MSG(cache_.size() == text_.size(), "Invalid count of cache data");
}

void LineText::prepare()
{
	vao_.generate();
	vao_.bind();

	vbo_.generate();
	vbo_.bind();
	vbo_.data(std::vector<float>(dataPerFrame), GL_DYNAMIC_DRAW);

	Gl::Vao::vertexAttribPointer(0, 2, Gl::Type::Float, false, 4 * sizeof(float), reinterpret_cast<void*>(0 * sizeof(float)));
	Gl::Vao::vertexAttribPointer(1, 2, Gl::Type::Float, false, 4 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));
}

LineText::LineText(bool autoPrepare)
{
	if (autoPrepare)
	{
		prepare();
	}
}

void LineText::draw(CustomShaderProgram& shader)
{
	shader.use();
	shader.uniform(
		"uResolution", static_cast<float>(GetWindow().getSize().width), static_cast<float>(GetWindow().getSize().height));
	Gl::Texture::active(0);
	vao_.bind();

	glm::vec2 position = position_;

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
		Gl::Vbo::subData(GL_ARRAY_BUFFER, 0, sizeof(float) * vert->size(), vert->data());

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
}

LineText::LineText(Font& font, const std::string& text)
{
	prepare();
	setFont(font);
	setText(text);
}
