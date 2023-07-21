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

#include "CustomShaderProgram.h"

#include "Shader.h"
#include "Window.h"

void CustomShaderProgram::OnAfterLink()
{
	ShaderProgram::OnAfterLink();

	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glEnable(GL_FRAMEBUFFER_SRGB);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

CustomShaderProgram::CustomShaderProgram(bool shouldCreate) : ShaderProgram(shouldCreate)
{
}

CustomShaderProgram::CustomShaderProgram(Shader& frag, Shader& vert) : ShaderProgram(frag, vert)
{
}

CustomShaderProgram::CustomShaderProgram(std::filesystem::path pathToVertex, std::filesystem::path pathToFragment)
	: ShaderProgram(true)
{
	Shader frag(pathToVertex, Gl::Shader::Type::Vertex);
	Shader vert(pathToFragment, Gl::Shader::Type::Fragment);
	attachShader(frag);
	attachShader(vert);
	link();
	use();
}
