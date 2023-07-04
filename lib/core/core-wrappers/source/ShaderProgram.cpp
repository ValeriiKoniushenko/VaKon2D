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

#include "ShaderProgram.h"

#include "Shader.h"

void ShaderProgram::create()
{
	data_ = Gl::Program::create();
}

void ShaderProgram::attachShader(Shader& shader)
{
	if (!wasCreated())
	{
		throw std::runtime_error("You can't attach a shader to the not created shader program. Create it and try again");
	}

	Gl::Program::attachShader(data_, shader.data());
	wasLinked_ = false;
}

bool ShaderProgram::wasCreated() const
{
	return data_ != Gl::Program::invalidId;
}

void ShaderProgram::link()
{
	Gl::Program::link(data_);
	wasLinked_ = true;
}

void ShaderProgram::use() const
{
	if (!wasLinked())
	{
		throw std::runtime_error("You can't use the not compiled shader program");
	}
	Gl::Program::use(data_);
}

ShaderProgram::ShaderProgram(bool shouldCreate)
{
	if (shouldCreate)
	{
		create();
	}
}

ShaderProgram::ShaderProgram(Shader& frag, Shader& vert) : ShaderProgram(true)
{
	attachShader(frag);
	attachShader(vert);
	link();
}

GLuint ShaderProgram::data()
{
	return data_;
}

bool ShaderProgram::wasLinked() const
{
	return wasLinked_;
}

void ShaderProgram::deleteProgram()
{
	Gl::Program::deleteProgram(data_);
	data_ = Gl::Program::invalidId;
}

void ShaderProgram::recreateAndLink(Shader& frag, Shader& vert)
{
	deleteProgram();
	create();
	attachShader(frag);
	attachShader(vert);
	link();
}
