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
#include "boost/assert.hpp"

void Gl::requireNoErrors()
{
	switch (glGetError())
	{
		case GL_INVALID_ENUM:
			BOOST_ASSERT_MSG(false, "Set when an enumeration parameter is not legal");
		case GL_INVALID_VALUE:
			BOOST_ASSERT_MSG(false, "Set when a value parameter is not legal");
		case GL_INVALID_OPERATION:
			BOOST_ASSERT_MSG(false, "Set when the state for a command is not legal for its given parameters");
		case GL_STACK_OVERFLOW:
			BOOST_ASSERT_MSG(false, "Set when a stack pushing operation causes a stack overflow");
		case GL_STACK_UNDERFLOW:
			BOOST_ASSERT_MSG(false, "Set when a stack popping operation occurs while the stack is at its lowest point");
		case GL_OUT_OF_MEMORY:
			BOOST_ASSERT_MSG(false, "Set when a memory allocation operation cannot allocate (enough) memory");
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			BOOST_ASSERT_MSG(false, "Set when reading or writing to a framebuffer that is not complete");
	}
}

void Gl::debugTraces()
{
	Gl::requireNoErrors();
}

void Gl::Vao::generate(GLsizei n, GLuint* arrays)
{
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

	enableVertexAttribArray(index);
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
	return value;
}

std::string Gl::Shader::getShaderInfoLog(GLuint shader)
{
	constexpr std::size_t logLength = 1024;
	char infoLog[logLength];
	glGetShaderInfoLog(shader, logLength, nullptr, infoLog);
	return {infoLog};
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
	return {infoLog};
}

void Gl::Program::use(GLuint program)
{
	glUseProgram(program);
	usedShaderProgram = program;
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::deleteProgram(GLuint program)
{
	glDeleteProgram(program);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

GLint Gl::Program::getUniformLocation(GLuint program, const std::string& basicString)
{
	const GLint location = glGetUniformLocation(program, basicString.c_str());
	if (location == -1)
	{
		throw std::runtime_error("Invalid uniform name: " + basicString);
	}
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
	return location;
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

Gl::State Gl::getState()
{
	Gl::State state;
	state.boundVbo = Gl::Vbo::id_;
	state.boundVao = Gl::Vao::id_;
	state.boundTexture = Gl::Texture::boundTexture;
	state.boundShader = Gl::Shader::id_;
	state.boundProgram = Gl::Program::usedShaderProgram;

	return state;
}

std::string Gl::Texture::channelToString(Channel channel)
{
	if (channel == Channel::SRGB)
	{
		return "SRGB";
	}
	else if (channel == Channel::RGB)
	{
		return "RGB";
	}
	else if (channel == Channel::RGBA)
	{
		return "RGBA";
	}
	else if (channel == Channel::SRGBA)
	{
		return "SRGBA";
	}

	return "";
}

Gl::Texture::MagFilter Gl::Texture::stringToMagFilter(const std::string& filter)
{
	if (filter == "None")
	{
		return MagFilter::None;
	}
	else if (filter == "Linear")
	{
		return MagFilter::Linear;
	}
	else if (filter == "Nearest")
	{
		return MagFilter::Nearest;
	}

	return MagFilter::None;
}

Gl::Texture::MinFilter Gl::Texture::stringToMinFilter(const std::string& filter)
{
	if (filter == "None")
	{
		return MinFilter::None;
	}
	else if (filter == "Linear")
	{
		return MinFilter::Linear;
	}
	else if (filter == "Nearest")
	{
		return MinFilter::Nearest;
	}
	else if (filter == "NearestMipmapNearest")
	{
		return MinFilter::NearestMipmapNearest;
	}
	else if (filter == "LinearMipmapNearest")
	{
		return MinFilter::LinearMipmapNearest;
	}
	else if (filter == "NearestMipmapLinear")
	{
		return MinFilter::NearestMipmapLinear;
	}
	else if (filter == "LinearMipmapLinear")
	{
		return MinFilter::LinearMipmapLinear;
	}

	return MinFilter::None;
}

std::string Gl::Texture::magFilterToString(MagFilter filter)
{
	if (filter == MagFilter::Linear)
	{
		return "Linear";
	}
	else if (filter == MagFilter::Nearest)
	{
		return "Nearest";
	}
	return "None";
}

std::string Gl::Texture::minFilterToString(MinFilter filter)
{
	if (filter == MinFilter::Nearest)
	{
		return "Nearest";
	}
	else if (filter == MinFilter::Linear)
	{
		return "Linear";
	}
	else if (filter == MinFilter::NearestMipmapNearest)
	{
		return "NearestMipmapNearest";
	}
	else if (filter == MinFilter::LinearMipmapNearest)
	{
		return "LinearMipmapNearest";
	}
	else if (filter == MinFilter::NearestMipmapLinear)
	{
		return "NearestMipmapLinear";
	}
	else if (filter == MinFilter::LinearMipmapLinear)
	{
		return "LinearMipmapLinear";
	}

	return "None";
}

void Gl::Texture::setMinFilter(MinFilter filter, Target target)
{
	if (filter == MinFilter::None)
	{
		throw std::runtime_error("Min filter is none. Try to use correct filter value.");
	}
	if (target == Target::None)
	{
		throw std::runtime_error("Target is none. Try to use correct target value.");
	}

	glTexParameteri(static_cast<GLenum>(target), GL_TEXTURE_MIN_FILTER, static_cast<GLint>(filter));
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Texture::setMagFilter(MagFilter filter, Target target)
{
	if (filter == MagFilter::None)
	{
		throw std::runtime_error("Mag filter is none. Try to use correct filter value.");
	}
	if (target == Target::None)
	{
		throw std::runtime_error("Target is none. Try to use correct target value.");
	}

	glTexParameteri(static_cast<GLenum>(target), GL_TEXTURE_MAG_FILTER, static_cast<GLint>(filter));
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Texture::setWrapS(Wrap wrap, Target target)
{
	if (wrap == Wrap::None)
	{
		throw std::runtime_error("Wrap is none. Try to use correct wrap value.");
	}
	if (target == Target::None)
	{
		throw std::runtime_error("Target is none. Try to use correct target value.");
	}

	glTexParameteri(static_cast<GLenum>(target), GL_TEXTURE_WRAP_S, static_cast<GLint>(wrap));
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Texture::setWrapT(Wrap wrap, Target target)
{
	if (wrap == Wrap::None)
	{
		throw std::runtime_error("Wrap is none. Try to use correct wrap value.");
	}
	if (target == Target::None)
	{
		throw std::runtime_error("Target is none. Try to use correct target value.");
	}

	glTexParameteri(static_cast<GLenum>(target), GL_TEXTURE_WRAP_T, static_cast<GLint>(wrap));
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Texture::setWrapR(Wrap wrap, Target target)
{
	if (wrap == Wrap::None)
	{
		throw std::runtime_error("Wrap is none. Try to use correct wrap value.");
	}
	if (target == Target::None)
	{
		throw std::runtime_error("Target is none. Try to use correct target value.");
	}

	glTexParameteri(static_cast<GLenum>(target), GL_TEXTURE_WRAP_R, static_cast<GLint>(wrap));
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Texture::active(GLenum num)
{
	static const size_t maxCountActiveTextures = Texture::getMaxCountActiveTextures();
	using namespace std::string_literals;
	if (num >= maxCountActiveTextures)
	{
		throw std::runtime_error(
			"Your device does not support such count of textures. Impossible to active "s + std::to_string(num) + "th texture.");
	}

	glActiveTexture(GL_TEXTURE0 + num);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

size_t Gl::Texture::getMaxCountActiveTextures()
{
	int total_units{};
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &total_units);
	return static_cast<size_t>(total_units);
}

GLuint Gl::Texture::generate()
{
	GLuint id;
	glGenTextures(1, &id);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
	return id;
}

void Gl::Texture::bind(Gl::Texture::Target target, GLuint texture)
{
	glBindTexture(static_cast<GLenum>(target), texture);
	boundTexture = texture;
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Texture::texImage2D(Target target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border,
	GLenum format, GLenum type, const void* pixels)
{
	glTexImage2D(static_cast<GLenum>(target), level, internalformat, width, height, border, format, type, pixels);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Texture::generateMipmap(Gl::Texture::Target target)
{
	glGenerateMipmap(static_cast<GLenum>(target));
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Texture::deleteTexture(GLuint texture)
{
	glDeleteTextures(1, &texture);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniform1f(GLint location, GLfloat v0)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniform1f(location, v0);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniform2f(GLint location, GLfloat v0, GLfloat v1)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniform2f(location, v0, v1);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniform3f(location, v0, v1, v2);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniform4f(location, v0, v1, v2, v3);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniform1i(GLint location, GLint v0)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniform1i(location, v0);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniform2i(GLint location, GLint v0, GLint v1)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniform2i(location, v0, v1);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniform3i(GLint location, GLint v0, GLint v1, GLint v2)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniform3i(location, v0, v1, v2);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniform4i(location, v0, v1, v2, v3);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniform1ui(GLint location, GLuint v0)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniform1ui(location, v0);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniform2ui(GLint location, GLuint v0, GLuint v1)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniform2ui(location, v0, v1);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniform3ui(location, v0, v1, v2);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniform4ui(location, v0, v1, v2, v3);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniform1fv(GLint location, GLsizei count, const GLfloat* value)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniform1fv(location, count, value);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniform2fv(GLint location, GLsizei count, const GLfloat* value)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniform2fv(location, count, value);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniform3fv(GLint location, GLsizei count, const GLfloat* value)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniform3fv(location, count, value);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniform4fv(GLint location, GLsizei count, const GLfloat* value)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniform4fv(location, count, value);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniform1iv(GLint location, GLsizei count, const GLint* value)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniform1iv(location, count, value);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniform2iv(GLint location, GLsizei count, const GLint* value)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniform2iv(location, count, value);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniform3iv(GLint location, GLsizei count, const GLint* value)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniform3iv(location, count, value);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniform4iv(GLint location, GLsizei count, const GLint* value)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniform4iv(location, count, value);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniform1uiv(GLint location, GLsizei count, const GLuint* value)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniform1uiv(location, count, value);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniform2uiv(GLint location, GLsizei count, const GLuint* value)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniform2uiv(location, count, value);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniform3uiv(GLint location, GLsizei count, const GLuint* value)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniform3uiv(location, count, value);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniform4uiv(GLint location, GLsizei count, const GLuint* value)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniform4uiv(location, count, value);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniformMatrix2fv(location, count, transpose, value);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniformMatrix3fv(location, count, transpose, value);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniformMatrix4fv(location, count, transpose, value);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniformMatrix2x3fv(location, count, transpose, value);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniformMatrix3x2fv(location, count, transpose, value);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniformMatrix2x4fv(location, count, transpose, value);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniformMatrix4x2fv(location, count, transpose, value);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniformMatrix3x4fv(location, count, transpose, value);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

void Gl::Program::uniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
	if (usedShaderProgram == invalidId)
	{
		throw std::runtime_error("You can't set uniform without using the shader program");
	}
	glUniformMatrix4x3fv(location, count, transpose, value);
#ifdef OPENGL_DEBUG
	Gl::debugTraces();
#endif
}

boost::property_tree::ptree Gl::State::toJson() const
{
	boost::property_tree::ptree ptree;
	ptree.put("bound-vao", boundVao);
	ptree.put("bound-vbo", boundVbo);
	ptree.put("bound-texture", boundTexture);
	ptree.put("bound-shader", boundShader);
	ptree.put("bound-program", boundProgram);

	return ptree;
}
