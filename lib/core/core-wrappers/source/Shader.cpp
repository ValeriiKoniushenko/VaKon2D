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

#include "Shader.h"

#include "UtilsFunctions.h"

Shader::Shader(Gl::Shader::Type type, bool shouldCreate /* = true*/)
{
	setType(type);
	if (shouldCreate)
	{
		create();
	}
}

Shader::Shader(const std::filesystem::path& path, Gl::Shader::Type type) : Shader(type, true)
{
	loadFromFile(path);
	compile();
}

void Shader::create()
{
	data_ = Gl::Shader::create(type_);
}

void Shader::loadFromFile(const std::filesystem::path& path)
{
	setSource(source_ = Utils::getFileContent(path));
}

void Shader::setType(Gl::Shader::Type type)
{
	type_ = type;
}

Gl::Shader::Type Shader::getType() const
{
	return type_;
}

void Shader::compile() const
{
	Gl::Shader::compile(data_);
}

const std::string& Shader::getSource()
{
	return source_;
}

void Shader::deleteShader()
{
	Gl::Shader::deleteShader(data_);
	if (!Gl::Shader::getShaderiv(data_, GL_DELETE_STATUS))
	{
		throw std::runtime_error("Shader deletion was failed.\nDetails: " + std::string(Gl::Shader::getShaderInfoLog(data_)));
	}

	data_ = Gl::Shader::invalidId;
	source_.clear();
}

GLuint Shader::data()
{
	return data_;
}

Shader::~Shader()
{
	deleteShader();
}

void Shader::setSource(const std::string& source)
{
	source_ = source;
	Gl::Shader::source(data_, source_.c_str());
}
