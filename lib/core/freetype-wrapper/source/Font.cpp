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

#include "Texture.h"
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

		Texture texture(Gl::Texture::Target::Texture2D, true, true);
		Gl::Texture::texImage2D(Gl::Texture::Target::Texture2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0,
			GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

		Gl::Texture::setWrapS(Gl::Texture::Wrap::Clamp2Border);
		Gl::Texture::setWrapT(Gl::Texture::Wrap::Clamp2Border);
		Gl::Texture::setMinFilter(Gl::Texture::MinFilter::Linear);
		Gl::Texture::setMagFilter(Gl::Texture::MagFilter::Linear);

		Character character = {std::move(texture), glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top), static_cast<unsigned int>(face->glyph->advance.x) >> 6};
		characters_.emplace(c, std::move(character));
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

Font::Font(std::filesystem::path path)
{
	loadFromFile(std::move(path));
}
