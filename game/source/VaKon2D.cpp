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

#include "VaKon2D.h"

#include "Gl.h"
#include "GladWrapper.h"
#include "Logger.h"
#include "Vao.h"
#include "Window.h"

void VaKon2D::start()
{
	initCore();

	Gl::viewport(0, 0, 800, 600);

	auto vertexShader = Gl::Shader::createAndLoadShaderFromFile("assets/shaders/main-vertex.glsl", Gl::Shader::Type::Vertex);
	Gl::Shader::compile(vertexShader);

	auto fragmentShader = Gl::Shader::createAndLoadShaderFromFile("assets/shaders/main-fragment.glsl", Gl::Shader::Type::Fragment);
	Gl::Shader::compile(fragmentShader);

	unsigned int shaderProgram = Gl::Program::create();

	Gl::Program::attachShader(shaderProgram, vertexShader);
	Gl::Program::attachShader(shaderProgram, fragmentShader);

	Gl::Program::link(shaderProgram);
	Gl::Program::use(shaderProgram);

	Gl::Shader::deleteShader(fragmentShader);
	if (!Gl::Shader::getShaderiv(fragmentShader, GL_DELETE_STATUS))
	{
		throw std::runtime_error(
			"Fragment shader - deletion was failed.\nDetails: " + std::string(Gl::Shader::getShaderInfoLog(fragmentShader)));
	}

	Gl::Shader::deleteShader(vertexShader);
	if (!Gl::Shader::getShaderiv(vertexShader, GL_DELETE_STATUS))
	{
		throw std::runtime_error(
			"Vertex shader - deletion was failed.\nDetails: " + std::string(Gl::Shader::getShaderInfoLog(fragmentShader)));
	}

	float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
	unsigned int VBO;
	Gl::Vbo::generate(1, &VBO);
	Gl::Vbo::bind(GL_ARRAY_BUFFER, VBO);
	Gl::Vbo::data(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	Vao vao(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);

	while (!GetWindow().shouldClose())
	{
		GetWindow().clearColor(0.2f, 0.3f, 0.3f, 1.0f);	   // TODO: create class Color
		GetWindow().clear(GL_COLOR_BUFFER_BIT);			   // TODO: change to enum class

		Gl::Program::use(shaderProgram);
		vao.bind();
		Gl::drawArrays(GL_TRIANGLES, 0, 3);

		GetWindow().swapBuffers();
		GetWindow().pollEvent();
	}
}

void VaKon2D::initCore()
{
	// !!!!!! don't change an order !!!!!! -->
	Logger::initLogger();
	GlfwWrapper::initGlfw(3, 3);					// TODO: get versions from a config file
	GetWindow().create({800, 600}, "Game name");	// TODO: get size & title from a config file
	GladWrapper::initGlad();
	// <---------------------------------------
}
