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

#include "Font.h"

#include "spdlog/spdlog.h"

void Font::loadFromFile(std::filesystem::path path)
{
	if (GetFreeTypeLibrary().generateFace(path, 0, face))
	{
		throw std::runtime_error("Failed to load a font");
	}

	fontName_ = path.stem().string();

	FT_Set_Pixel_Sizes(face, 0, defaultRenderSize);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	spdlog::get("core")->info("Start generating of the glyphs for the font: " + fontName_);
	for (int c = 0; c < 128; ++c)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			spdlog::get("core")->warn("Failed to load Glyph");
			continue;
		}

		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		Gl::Texture::setMinFilter(Gl::Texture::MinFilter::Linear);
		Gl::Texture::setMagFilter(Gl::Texture::MagFilter::Linear);
		
		Character character = {texture, glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top), static_cast<unsigned int>(face->glyph->advance.x)};
		characters_.emplace(c, character);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Font::destroy()
{
	FT_Done_Face(face);
}

Font::~Font()
{
	destroy();
}

const Font::Character& Font::getCharacter(GLchar ch) const
{
	return characters_.at(ch);
}
