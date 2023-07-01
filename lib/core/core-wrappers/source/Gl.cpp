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

#include "Gl.h"

#include "UtilsFunctions.h"

void Gl::Vao::generate(GLsizei n, GLuint* arrays)
{
	if (isBind())
	{
		throw std::runtime_error("You can not to generate new VAO buffer with a bound VAO. Reset VAO and try again.");
	}

	glGenVertexArrays(n, arrays);
}

void Gl::Vao::bind(GLuint array)
{
	if (isBind())
	{
		throw std::runtime_error(
			"You try to bind a VAO again. The best way is to unbind a VAO after the last using or shader setting up.");
	}

	glBindVertexArray(array);

	Gl::Vao::id_ = array;
}

void Gl::Vao::reset()
{
	glBindVertexArray(::Vao::invalidId);

	Gl::Vao::id_ = ::Vao::invalidId;
}

bool Gl::Vao::isBind()
{
	return Gl::Vao::id_ != ::Vao::invalidId;
}

void Gl::Vbo::generate(GLsizei n, GLuint* arrays)
{
	glGenBuffers(n, arrays);
}

void Gl::Vbo::bind(GLenum target, GLuint buffer)
{
	glBindBuffer(target, buffer);

	Gl::Vbo::id_ = buffer;
}

void Gl::Vbo::reset(GLenum target)
{
	glBindBuffer(target, 0u);

	Gl::Vbo::id_ = ::Vbo::invalidId;
}

bool Gl::Vbo::isBind()
{
	return Gl::Vbo::id_ != ::Vbo::invalidId;
}

void Gl::Vbo::data(GLenum target, GLsizeiptr size, const void* data, GLenum usage)
{
	if (!isBind())
	{
		throw std::runtime_error("Impossible to put data to unbound VBO.");
	}

	glBufferData(target, size, data, usage);
}

void Gl::Vbo::subData(GLenum target, GLintptr offset, GLsizeiptr size, const void* data)
{
	if (!Gl::Vao::isBind())
	{
		throw std::runtime_error("You try to set up a shader using a zero VAO. Try to bind a VAO and try again.");
	}

	if (!isBind())
	{
		throw std::runtime_error("Impossible to put data to unbound VBO.");
	}

	glBufferSubData(target, offset, size, data);
}

void Gl::enableVertexAttribArray(GLuint index)
{
	if (!Gl::Vao::isBind())
	{
		throw std::runtime_error("You try to set up a shader using a zero VAO. Try to bind a VAO and try again.");
	}

	glEnableVertexAttribArray(index);
}

void Gl::disableVertexAttribArray(GLuint index)
{
	if (!Gl::Vao::isBind())
	{
		throw std::runtime_error("You try to set up a shader using a zero VAO. Try to bind a VAO and try again.");
	}

	glDisableVertexAttribArray(index);
}

void Gl::vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
{
	if (!Gl::Vao::isBind())
	{
		throw std::runtime_error("You try to set up a shader using a zero VAO. Try to bind a VAO and try again.");
	}

	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

GLuint Gl::Shader::createAndLoadShaderFromFile(const std::filesystem::path& path, Gl::Shader::Type type)
{
	const std::string shaderSources = Utils::getFileContent(path);
	const char* shaderSourcesP = shaderSources.c_str();

	GLuint shader = create(type);

	glShaderSource(shader, 1, &shaderSourcesP, nullptr);
	return shader;
}

GLuint Gl::Shader::create(Gl::Shader::Type type)
{
	GLuint shader = glCreateShader(static_cast<GLenum>(type));

	if (shader == 0)
	{
		throw std::runtime_error("The shader can't be created by undefined reason.");
	}

	return shader;
}

GLint Gl::Shader::getShaderiv(GLuint shader, GLenum pname)
{
	int value{};
	glGetShaderiv(shader, pname, &value);
	return value;
}

std::string Gl::Shader::getShaderInfoLog(GLuint shader)
{
	constexpr std::size_t logLength = 1024;
	char infoLog[logLength];
	glGetShaderInfoLog(shader, logLength, nullptr, infoLog);
	return std::string(infoLog);
}

void Gl::Shader::deleteShader(GLuint shader)
{
	glDeleteShader(shader);
}

void Gl::Shader::compile(GLuint shader)
{
	glCompileShader(shader);

	if (!getShaderiv(shader, GL_COMPILE_STATUS))
	{
		throw std::runtime_error("Shader - compilation failed.\nDetails: " + getShaderInfoLog(shader));
	}
}

GLuint Gl::Program::create()
{
	const GLuint program = glCreateProgram();
	if (program == 0)
	{
		throw std::runtime_error("The shader program couldn't be created by undefined reasons");
	}

	return program;
}

void Gl::Program::attachShader(GLuint program, GLuint shader)
{
	glAttachShader(program, shader);
}

void Gl::Program::link(GLuint program)
{
	glLinkProgram(program);

	if (!getProgramiv(program, GL_LINK_STATUS))
	{
		throw std::runtime_error("Shader program compilation was failed.\nDetails: " + getProgramInfoLog(program));
	}
}

GLint Gl::Program::getProgramiv(GLuint program, GLenum pname)
{
	int status{};
	glGetProgramiv(program, pname, &status);
	return status;
}

std::string Gl::Program::getProgramInfoLog(GLuint program)
{
	constexpr std::size_t logLength = 1024;
	char infoLog[logLength];
	glGetProgramInfoLog(program, logLength, nullptr, infoLog);
	return std::string(infoLog);
}