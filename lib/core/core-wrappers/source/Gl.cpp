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

void Gl::requireNoErrors()
{
	switch (glGetError())
	{
		case GL_INVALID_ENUM:
			throw std::runtime_error("GL_INVALID_ENUM: Set when an enumeration parameter is not legal");
		case GL_INVALID_VALUE:
			throw std::runtime_error("GL_INVALID_VALUE: Set when a value parameter is not legal");
		case GL_INVALID_OPERATION:
			throw std::runtime_error(
				"GL_INVALID_OPERATION: Set when the state for a command is not legal for its given parameters");
		case GL_STACK_OVERFLOW:
			throw std::runtime_error("GL_STACK_OVERFLOW: Set when a stack pushing operation causes a stack overflow");
		case GL_STACK_UNDERFLOW:
			throw std::runtime_error(
				"GL_STACK_UNDERFLOW: Set when a stack popping operation occurs while the stack is at its lowest point");
		case GL_OUT_OF_MEMORY:
			throw std::runtime_error("GL_OUT_OF_MEMORY: Set when a memory allocation operation cannot allocate (enough) memory");
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			throw std::runtime_error(
				"GL_INVALID_FRAMEBUFFER_OPERATION: Set when reading or writing to a framebuffer that is not complete");
	}
}

void Gl::debugTraces()
{
	Gl::requireNoErrors();
}

void Gl::Vao::generate(GLsizei n, GLuint* arrays)
{
	if (isBind())
	{
		throw std::runtime_error("You can not to generate new VAO buffer with a bound VAO. Reset VAO and try again.");
	}

	glGenVertexArrays(n, arrays);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Vao::bind(GLuint array)
{
	glBindVertexArray(array);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif

	Gl::Vao::id_ = array;
}

void Gl::Vao::reset()
{
	glBindVertexArray(invalidId);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif

	Gl::Vao::id_ = invalidId;
}

bool Gl::Vao::isBind()
{
	return Gl::Vao::id_ != invalidId;
}

void Gl::Vbo::generate(GLsizei n, GLuint* arrays)
{
	glGenBuffers(n, arrays);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Vbo::bind(GLenum target, GLuint buffer)
{
	glBindBuffer(target, buffer);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif

	Gl::Vbo::id_ = buffer;
}

void Gl::Vbo::reset(GLenum target)
{
	glBindBuffer(target, 0u);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif

	Gl::Vbo::id_ = invalidId;
}

bool Gl::Vbo::isBind()
{
	return Gl::Vbo::id_ != invalidId;
}

void Gl::Vbo::data(GLenum target, GLsizeiptr size, const void* data, GLenum usage)
{
	if (!isBind())
	{
		throw std::runtime_error("Impossible to put data to unbound VBO.");
	}

	glBufferData(target, size, data, usage);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
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
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Vao::enableVertexAttribArray(GLuint index)
{
	if (!Gl::Vao::isBind())
	{
		throw std::runtime_error("You try to set up a shader using a zero VAO. Try to bind a VAO and try again.");
	}

	glEnableVertexAttribArray(index);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Vao::disableVertexAttribArray(GLuint index)
{
	if (!Gl::Vao::isBind())
	{
		throw std::runtime_error("You try to set up a shader using a zero VAO. Try to bind a VAO and try again.");
	}

	glDisableVertexAttribArray(index);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Vao::vertexAttribPointer(GLuint index, GLint size, Gl::Type type, bool normalized, GLsizei stride, const void* pointer)
{
	if (!Gl::Vao::isBind())
	{
		throw std::runtime_error("You try to set up a shader using a zero VAO. Try to bind a VAO and try again.");
	}

	glVertexAttribPointer(index, size, static_cast<GLenum>(type), normalized, stride, pointer);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

GLuint Gl::Shader::createAndLoadShaderFromFile(const std::filesystem::path& path, Gl::Shader::Type type)
{
	const std::string shaderSources = Utils::getFileContent(path);
	GLuint shader = create(type);
	source(shader, shaderSources.c_str());
	return shader;
}

GLuint Gl::Shader::create(Gl::Shader::Type type)
{
	GLuint shader = glCreateShader(static_cast<GLenum>(type));

	if (shader == 0)
	{
		throw std::runtime_error("The shader can't be created by undefined reason.");
	}
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif

	return shader;
}

GLint Gl::Shader::getShaderiv(GLuint shader, GLenum pname)
{
	int value{};
	glGetShaderiv(shader, pname, &value);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
	return value;
}

std::string Gl::Shader::getShaderInfoLog(GLuint shader)
{
	constexpr std::size_t logLength = 1024;
	char infoLog[logLength];
	glGetShaderInfoLog(shader, logLength, nullptr, infoLog);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
	return std::string(infoLog);
}

void Gl::Shader::deleteShader(GLuint shader)
{
	glDeleteShader(shader);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Shader::compile(GLuint shader)
{
	glCompileShader(shader);

	if (!getShaderiv(shader, GL_COMPILE_STATUS))
	{
		throw std::runtime_error("Shader - compilation failed.\nDetails: " + getShaderInfoLog(shader));
	}
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Shader::source(GLuint shader, const char* sources)
{
	glShaderSource(shader, 1, &sources, nullptr);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

GLuint Gl::Program::create()
{
	const GLuint program = glCreateProgram();
	if (program == 0)
	{
		throw std::runtime_error("The shader program couldn't be created by undefined reasons");
	}
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif

	return program;
}

void Gl::Program::attachShader(GLuint program, GLuint shader)
{
	glAttachShader(program, shader);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::link(GLuint program)
{
	glLinkProgram(program);

	if (!getProgramiv(program, GL_LINK_STATUS))
	{
		throw std::runtime_error("Shader program compilation was failed.\nDetails: " + getProgramInfoLog(program));
	}
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

GLint Gl::Program::getProgramiv(GLuint program, GLenum pname)
{
	int status{};
	glGetProgramiv(program, pname, &status);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
	return status;
}

std::string Gl::Program::getProgramInfoLog(GLuint program)
{
	constexpr std::size_t logLength = 1024;
	char infoLog[logLength];
	glGetProgramInfoLog(program, logLength, nullptr, infoLog);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
	return std::string(infoLog);
}

void Gl::Program::use(GLuint program)
{
	glUseProgram(program);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::viewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
	glViewport(x, y, width, height);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::drawArrays(GLenum mode, GLint first, GLsizei count)
{
	glDrawArrays(mode, first, count);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}
