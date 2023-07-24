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

#include "Color.h"
#include "Shader.h"

#include <glm/gtc/type_ptr.hpp>

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
	OnAfterLink();
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

void ShaderProgram::OnAfterLink()
{
}

GLint ShaderProgram::getUniformLocation(const std::string& name)
{
	auto it = uniforms_.find(name);
	if (it == uniforms_.end())
	{
		const GLint location = Gl::Program::getUniformLocation(data_, name);
		uniforms_.insert({name, location});
		return location;
	}

	return it->second;
}

void ShaderProgram::uniform(const std::string& name, const GlColor& color)
{
	const GLint location = getUniformLocation(name);
	Gl::Program::uniform4f(location, color.r, color.g, color.b, color.a);
}

void ShaderProgram::uniform(const std::string& name, GLfloat v0)
{
	const GLint location = getUniformLocation(name);
	Gl::Program::uniform1f(location, v0);
}

void ShaderProgram::uniform(const std::string& name, GLfloat v0, GLfloat v1)
{
	const GLint location = getUniformLocation(name);
	Gl::Program::uniform2f(location, v0, v1);
}

void ShaderProgram::uniform(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2)
{
	const GLint location = getUniformLocation(name);
	Gl::Program::uniform3f(location, v0, v1, v2);
}

void ShaderProgram::uniform(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
	const GLint location = getUniformLocation(name);
	Gl::Program::uniform4f(location, v0, v1, v2, v3);
}

void ShaderProgram::uniform(const std::string& name, GLint v0)
{
	const GLint location = getUniformLocation(name);
	Gl::Program::uniform1i(location, v0);
}

void ShaderProgram::uniform(const std::string& name, GLint v0, GLint v1)
{
	const GLint location = getUniformLocation(name);
	Gl::Program::uniform2i(location, v0, v1);
}

void ShaderProgram::uniform(const std::string& name, GLint v0, GLint v1, GLint v2)
{
	const GLint location = getUniformLocation(name);
	Gl::Program::uniform3i(location, v0, v1, v2);
}

void ShaderProgram::uniform(const std::string& name, GLint v0, GLint v1, GLint v2, GLint v3)
{
	const GLint location = getUniformLocation(name);
	Gl::Program::uniform4i(location, v0, v1, v2, v3);
}

void ShaderProgram::uniform(const std::string& name, GLuint v0)
{
	const GLint location = getUniformLocation(name);
	Gl::Program::uniform1ui(location, v0);
}

void ShaderProgram::uniform(const std::string& name, GLuint v0, GLuint v1)
{
	const GLint location = getUniformLocation(name);
	Gl::Program::uniform2ui(location, v0, v1);
}

void ShaderProgram::uniform(const std::string& name, GLuint v0, GLuint v1, GLuint v2)
{
	const GLint location = getUniformLocation(name);
	Gl::Program::uniform3ui(location, v0, v1, v2);
}

void ShaderProgram::uniform(const std::string& name, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
	const GLint location = getUniformLocation(name);
	Gl::Program::uniform4ui(location, v0, v1, v2, v3);
}

void ShaderProgram::uniform(const std::string& name, bool transpose, const glm::mat2& value)
{
	const GLint location = getUniformLocation(name);
	Gl::Program::uniformMatrix2fv(location, 1, transpose, glm::value_ptr(value));
}

void ShaderProgram::uniform(const std::string& name, bool transpose, const glm::mat3& value)
{
	const GLint location = getUniformLocation(name);
	Gl::Program::uniformMatrix3fv(location, 1, transpose, glm::value_ptr(value));
}

void ShaderProgram::uniform(const std::string& name, bool transpose, const glm::mat4& value)
{
	const GLint location = getUniformLocation(name);
	Gl::Program::uniformMatrix4fv(location, 1, transpose, glm::value_ptr(value));
}

void ShaderProgram::uniform(const std::string& name, bool transpose, const glm::mat2x3& value)
{
	const GLint location = getUniformLocation(name);
	Gl::Program::uniformMatrix2x3fv(location, 1, transpose, glm::value_ptr(value));
}

void ShaderProgram::uniform(const std::string& name, bool transpose, const glm::mat3x2& value)
{
	const GLint location = getUniformLocation(name);
	Gl::Program::uniformMatrix3x2fv(location, 1, transpose, glm::value_ptr(value));
}

void ShaderProgram::uniform(const std::string& name, bool transpose, const glm::mat2x4& value)
{
	const GLint location = getUniformLocation(name);
	Gl::Program::uniformMatrix2x4fv(location, 1, transpose, glm::value_ptr(value));
}

void ShaderProgram::uniform(const std::string& name, bool transpose, const glm::mat4x2& value)
{
	const GLint location = getUniformLocation(name);
	Gl::Program::uniformMatrix4x2fv(location, 1, transpose, glm::value_ptr(value));
}

void ShaderProgram::uniform(const std::string& name, bool transpose, const glm::mat3x4& value)
{
	const GLint location = getUniformLocation(name);
	Gl::Program::uniformMatrix3x4fv(location, 1, transpose, glm::value_ptr(value));
}

void ShaderProgram::uniform(const std::string& name, bool transpose, const glm::mat4x3& value)
{
	const GLint location = getUniformLocation(name);
	Gl::Program::uniformMatrix4x3fv(location, 1, transpose, glm::value_ptr(value));
}

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept
{
	*this = std::move(other);
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept
{
	data_ = other.data_;
	wasLinked_ = other.wasLinked_;
	uniforms_ = std::move(other.uniforms_);

	other.data_ = Gl::Program::invalidId;
	other.wasLinked_ = false;
	other.uniforms_.clear();
	return *this;
}

bool ShaderProgram::isValid() const
{
	return data_ != Gl::Program::invalidId;
}
