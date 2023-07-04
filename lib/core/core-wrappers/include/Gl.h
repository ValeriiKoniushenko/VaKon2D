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

#include "GlfwWrapper.h"

#include <filesystem>

class Gl
{
public:
	enum class Type
	{
		Float = GL_FLOAT,
		Double = GL_DOUBLE,
		Byte = GL_BYTE,
		UByte = GL_UNSIGNED_BYTE,
		Short = GL_SHORT,
		UShort = GL_UNSIGNED_SHORT,
		Int = GL_INT,
		UInt = GL_UNSIGNED_INT,
		Fixed = GL_FIXED
	};

public:
	Gl() = delete;

	static void requireNoErrors();
	static void debugTraces();

	class Vao
	{
	public:
		inline static const GLuint invalidId = 0;

		static void generate(GLsizei n, GLuint* arrays);
		static void bind(GLuint array);
		static void reset();
		static bool isBind();
		static void vertexAttribPointer(
			GLuint index, GLint size, Gl::Type type, bool normalized, GLsizei stride, const void* pointer);
		static void enableVertexAttribArray(GLuint index);
		static void disableVertexAttribArray(GLuint index);

	private:
		inline static GLuint id_ = invalidId;
	};

	class Vbo
	{
	public:
		inline static const GLuint invalidId = 0;

		static void generate(GLsizei n, GLuint* arrays);
		static void bind(GLenum target, GLuint buffer);
		static void reset(GLenum target);
		static bool isBind();
		static void data(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
		static void subData(GLenum target, GLintptr offset, GLsizeiptr size, const void* data);

	public:
		inline static GLuint id_ = invalidId;
	};

	class Shader
	{
	public:
		inline static const GLuint invalidId = 0;

		enum class Type
		{
			Fragment = GL_FRAGMENT_SHADER,
			Geometry = GL_GEOMETRY_SHADER,
			Vertex = GL_VERTEX_SHADER
		};
		_NODISCARD static GLuint create(Type type);
		_NODISCARD static GLuint createAndLoadShaderFromFile(const std::filesystem::path& path, Type type);
		_NODISCARD static GLint getShaderiv(GLuint shader, GLenum pname);
		_NODISCARD static std::string getShaderInfoLog(GLuint shader);
		static void deleteShader(GLuint shader);
		static void compile(GLuint shader);
		static void source(GLuint shader, const char* sources);

	private:
		inline static GLuint id_ = invalidId;
	};

	class Program
	{
	public:
		inline static const GLuint invalidId = 0;

		_NODISCARD static GLint getProgramiv(GLuint program, GLenum pname);
		_NODISCARD static GLuint create();
		static void attachShader(GLuint program, GLuint shader);
		static void link(GLuint program);
		_NODISCARD static std::string getProgramInfoLog(GLuint program);
		static void use(GLuint program);
		static void deleteProgram(GLuint program);
	};

	static void viewport(GLint x, GLint y, GLsizei width, GLsizei height);
	static void drawArrays(GLenum mode, GLint first, GLsizei count);
};
