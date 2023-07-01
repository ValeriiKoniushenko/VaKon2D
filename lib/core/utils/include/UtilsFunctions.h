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

#include "Size.h"

#include <filesystem>
#include <string>
#include <vector>

namespace Utils
{

_NODISCARD std::string getFileContent(const std::filesystem::path& path);
void setFileContent(const std::filesystem::path& path, const std::string& data);
void setFileContent(const std::filesystem::path& path, void* p, size_t size);
_NODISCARD std::vector<ISize2D> getAllSupportedWndSizes();
_NODISCARD std::ifstream readFile(const std::filesystem::path& path);
_NODISCARD bool isEqual(float n1, float n2, float E = std::numeric_limits<float>::epsilon());
_NODISCARD bool isZero(float n, float E = std::numeric_limits<float>::epsilon());

}	 // namespace Utils
