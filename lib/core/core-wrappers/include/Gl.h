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
#include "JsonPrintable.h"

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
		friend class Gl;
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

	private:
		inline static GLuint id_ = invalidId;
		friend class Gl;
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
		friend class Gl;
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
		_NODISCARD static GLint getUniformLocation(GLuint program, const std::string& name);

		static void uniform1f(GLint location, GLfloat v0);
		static void uniform2f(GLint location, GLfloat v0, GLfloat v1);
		static void uniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
		static void uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
		static void uniform1i(GLint location, GLint v0);
		static void uniform2i(GLint location, GLint v0, GLint v1);
		static void uniform3i(GLint location, GLint v0, GLint v1, GLint v2);
		static void uniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
		static void uniform1ui(GLint location, GLuint v0);
		static void uniform2ui(GLint location, GLuint v0, GLuint v1);
		static void uniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2);
		static void uniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
		static void uniform1fv(GLint location, GLsizei count, const GLfloat* value);
		static void uniform2fv(GLint location, GLsizei count, const GLfloat* value);
		static void uniform3fv(GLint location, GLsizei count, const GLfloat* value);
		static void uniform4fv(GLint location, GLsizei count, const GLfloat* value);
		static void uniform1iv(GLint location, GLsizei count, const GLint* value);
		static void uniform2iv(GLint location, GLsizei count, const GLint* value);
		static void uniform3iv(GLint location, GLsizei count, const GLint* value);
		static void uniform4iv(GLint location, GLsizei count, const GLint* value);
		static void uniform1uiv(GLint location, GLsizei count, const GLuint* value);
		static void uniform2uiv(GLint location, GLsizei count, const GLuint* value);
		static void uniform3uiv(GLint location, GLsizei count, const GLuint* value);
		static void uniform4uiv(GLint location, GLsizei count, const GLuint* value);
		static void uniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
		static void uniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
		static void uniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
		static void uniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
		static void uniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
		static void uniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
		static void uniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
		static void uniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
		static void uniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);

	private:
		inline static GLuint usedShaderProgram = invalidId;
		friend class Gl;
	};

	class Texture
	{
	public:
		inline static const GLuint invalidId = 0;

		enum class Target
		{
			None,
			Texture2D = GL_TEXTURE_2D,
			CubeMapPositiveX = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
			CubeMapNegativeX = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
			CubeMapPositiveY = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
			CubeMapNegativeY = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
			CubeMapPositiveZ = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
			CubeMapNegativeZ = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
			CubeMap = GL_TEXTURE_CUBE_MAP
		};

		enum class MagFilter
		{
			None,
			Linear = GL_LINEAR,
			Nearest = GL_NEAREST,
		};

		enum class MinFilter
		{
			None,
			Linear = GL_LINEAR,
			Nearest = GL_NEAREST,
			NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,
			LinearMipmapNearest = GL_LINEAR_MIPMAP_NEAREST,
			NearestMipmapLinear = GL_NEAREST_MIPMAP_LINEAR,
			LinearMipmapLinear = GL_LINEAR_MIPMAP_LINEAR
		};

		enum class Wrap
		{
			None,
			Clamp2Edge = GL_CLAMP_TO_EDGE,
			Clamp2Border = GL_CLAMP_TO_BORDER,
			MirroredRepeat = GL_MIRRORED_REPEAT,
			Repeat = GL_REPEAT,
			MirrorClamp2Edge = GL_MIRROR_CLAMP_TO_EDGE
		};

		enum class Channel
		{
			SRGB = GL_SRGB,
			RGB = GL_RGB,
			RGBA = GL_RGBA,
			SRGBA = GL_SRGB_ALPHA
		};

		_NODISCARD static std::string channelToString(Channel channel);

		_NODISCARD static MagFilter stringToMagFilter(const std::string& filter);
		_NODISCARD static MinFilter stringToMinFilter(const std::string& filter);
		_NODISCARD static std::string magFilterToString(MagFilter filter);
		_NODISCARD static std::string minFilterToString(MinFilter filter);

		static void setMinFilter(MinFilter filter, Target target = Target::Texture2D);
		static void setMagFilter(MagFilter filter, Target target = Target::Texture2D);
		static void setWrapS(Wrap wrap, Target target = Target::Texture2D);
		static void setWrapT(Wrap wrap, Target target = Target::Texture2D);
		static void setWrapR(Wrap wrap, Target target = Target::Texture2D);
		static void active(GLenum num);
		_NODISCARD static size_t getMaxCountActiveTextures();
		_NODISCARD static GLuint generate();
		static void bind(Target target, GLuint texture);
		static void texImage2D(Target target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border,
			GLenum format, GLenum type, const void* pixels);
		static void generateMipmap(Target target);
		static void deleteTexture(GLuint texture);

	private:
		friend class Gl;
		inline static GLuint boundTexture = invalidId;
	};

	struct State : public JsonPrintable
	{
		GLuint boundVbo = Vbo::invalidId;
		GLuint boundVao = Vao::invalidId;
		GLuint boundTexture = Texture::invalidId;
		GLuint boundShader = Shader::invalidId;
		GLuint boundProgram = Program::invalidId;

		boost::property_tree::ptree toJson() const override;
	};

	static State getState();

	static void viewport(GLint x, GLint y, GLsizei width, GLsizei height);
	static void drawArrays(GLenum mode, GLint first, GLsizei count);
};
