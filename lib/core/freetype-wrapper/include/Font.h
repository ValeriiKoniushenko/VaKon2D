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

#include "FreeTypeLibrary.h"
#include "Gl.h"
#include "Texture.h"
#include "glm/glm.hpp"

#include <filesystem>
#include <unordered_map>

class Font
{
public:
	struct Character
	{
		Texture texture;		 // ID handle of the glyph texture
		glm::ivec2 Size;		 // Size of glyph
		glm::ivec2 Bearing;		 // Offset from baseline to left/top of glyph
		unsigned int Advance;	 // Horizontal offset to advance to next glyph
	};

	inline static constexpr float defaultRenderSize = 500.f;

	~Font();
	void loadFromFile(std::filesystem::path path);
	void destroy();
	_NODISCARD const Character& getCharacter(GLchar ch) const;

private:
	std::unordered_map<GLchar, Character> characters_;
	FT_Face face;
	std::string fontName_;
};