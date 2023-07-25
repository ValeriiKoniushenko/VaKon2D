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

#include "UtilsFunctions.h"

#include <Windows.h>

#include <format>
#include <fstream>
#include <stdexcept>

namespace Utils
{

std::string jsonToString(const boost::property_tree::ptree& ptree)
{
	std::ostringstream oss;
	boost::property_tree::json_parser::write_json(oss, ptree);
	return oss.str();
}

std::string getFileContent(const std::filesystem::path& path)
{
	std::ifstream file(path);
	if (!file.is_open())
	{
		throw std::runtime_error(std::format("File: {} can't be opened", path.string()));
	}

	std::string buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	return buffer;
}

void setFileContent(const std::filesystem::path& path, const std::string& data)
{
	std::fstream file(path, std::ios::out);
	if (!file.is_open())
	{
		throw std::runtime_error(std::format("File: {} can't be opened", path.string()));
	}

	file.write(data.data(), data.size() * sizeof(std::string::value_type));

	file.close();
}

void setFileContent(const std::filesystem::path& path, void* p, size_t size)
{
	std::fstream file(path, std::ios::out | std::ios::binary);
	if (!file.is_open())
	{
		throw std::runtime_error(std::format("File: {} can't be opened", path.string()));
	}

	file.write(static_cast<char*>(p), size);

	file.close();
}

std::vector<ISize2D> getAllSupportedWndSizes()
{
	std::vector<ISize2D> data;
	DEVMODEA mode;
	mode.dmSize = sizeof(mode);

	for (DWORD i = 0; EnumDisplaySettings(nullptr, i, &mode); i++)
	{
		ISize2D tmp = {static_cast<int>(mode.dmPelsWidth), static_cast<int>(mode.dmPelsHeight)};

		if (i != 0)
		{
			if (data.back().height != tmp.height && data.back().width != tmp.width)
			{
				data.push_back(tmp);
			}
		}
		else
		{
			data.push_back(tmp);
		}
	}

	return data;
}

std::ifstream readFile(const std::filesystem::path& path)
{
	std::ifstream file(path);
	if (!file.is_open())
	{
		throw std::runtime_error(std::format("File: {} can't be opened", path.string()));
	}
	return file;
}

bool isEqual(float n1, float n2, float E)
{
	return fabs(n1 - n2) < E;
}

bool isZero(float n1, float E)
{
	return fabs(n1) < E;
}

}	 // namespace Utils