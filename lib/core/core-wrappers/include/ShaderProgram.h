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

#include "Gl.h"
#include "NotCopyableButMovable.h"
#include "glm/glm.hpp"

#include <unordered_map>

struct GlColor;

class Shader;

class ShaderProgram : public Utils::NotCopyableButMovable {
public:
    explicit ShaderProgram(bool shouldCreate);

    ShaderProgram(Shader &frag, Shader &vert);

    ShaderProgram(ShaderProgram &&other) noexcept;

    ShaderProgram &operator=(ShaderProgram &&other) noexcept;

    void recreateAndLink(Shader &frag, Shader &vert);

    void create();

    void attachShader(Shader &shader);

    void link();

    void use() const;

    _NODISCARD bool wasCreated() const;

    _NODISCARD GLuint data();

    _NODISCARD bool wasLinked() const;

    void deleteProgram();

    virtual void OnAfterLink();

    _NODISCARD GLint getUniformLocation(const std::string &name);

    _NODISCARD bool isValid() const;

    void uniform(const std::string &name, const glm::ivec2 &color);

    void uniform(const std::string &name, const glm::vec2 &color);

    void uniform(const std::string &name, const GlColor &color);

    void uniform(const std::string &name, GLfloat v0);

    void uniform(const std::string &name, GLfloat v0, GLfloat v1);

    void uniform(const std::string &name, GLfloat v0, GLfloat v1, GLfloat v2);

    void uniform(const std::string &name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

    void uniform(const std::string &name, GLint v0);

    void uniform(const std::string &name, GLint v0, GLint v1);

    void uniform(const std::string &name, GLint v0, GLint v1, GLint v2);

    void uniform(const std::string &name, GLint v0, GLint v1, GLint v2, GLint v3);

    void uniform(const std::string &name, GLuint v0);

    void uniform(const std::string &name, GLuint v0, GLuint v1);

    void uniform(const std::string &name, GLuint v0, GLuint v1, GLuint v2);

    void uniform(const std::string &name, GLuint v0, GLuint v1, GLuint v2, GLuint v3);

    void uniform(const std::string &name, bool transpose, const glm::mat2 &value);

    void uniform(const std::string &name, bool transpose, const glm::mat3 &value);

    void uniform(const std::string &name, bool transpose, const glm::mat4 &value);

    void uniform(const std::string &name, bool transpose, const glm::mat2x3 &value);

    void uniform(const std::string &name, bool transpose, const glm::mat3x2 &value);

    void uniform(const std::string &name, bool transpose, const glm::mat2x4 &value);

    void uniform(const std::string &name, bool transpose, const glm::mat4x2 &value);

    void uniform(const std::string &name, bool transpose, const glm::mat3x4 &value);

    void uniform(const std::string &name, bool transpose, const glm::mat4x3 &value);

private:
    GLuint data_ = Gl::Program::invalidId;
    bool wasLinked_ = false;
    std::unordered_map<std::string, GLint> uniforms_;
};