
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

#include "FreeTypeLibrary.h"

void FreeTypeLibrary::init()
{
	if (FT_Init_FreeType(&ft))
	{
		throw std::runtime_error("Couldn't initialize freetype library");
	}
}

void FreeTypeLibrary::destroy()
{
	FT_Done_FreeType(ft);
}

bool FreeTypeLibrary::generateFace(const std::filesystem::path& path, FT_Long faceIndex, FT_Face& face)
{
	return FT_New_Face(ft, path.string().c_str(), faceIndex, &face);
}

FreeTypeLibrary::~FreeTypeLibrary()
{
	destroy();
}

FreeTypeLibrary& GetFreeTypeLibrary()
{
	return FreeTypeLibrary::instance();
}
