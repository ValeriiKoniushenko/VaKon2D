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

#include "Delegate.h"
#include "Gl.h"
#include "GladWrapper.h"
#include "Logger.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Timer.h"
#include "Vao.h"
#include "Vbo.h"
#include "Window.h"
#include "World.h"

#include <iostream>

void VaKon2D::start()
{
	initCore();

	Timer timer;
	timer.setFrequency(Timer::Unit(500));
	timer.setMode(Timer::Mode::Infinity);
	timer.setCallback([]() { std::cout << "hello world "; });
	GetWorld().addTimer(std::move(timer));

	GetWindow().viewport(0, 0, 800, 600);

	Shader vertex("assets/shaders/main-vertex.glsl", Gl::Shader::Type::Vertex);
	Shader fragment("assets/shaders/main-fragment.glsl", Gl::Shader::Type::Fragment);

	ShaderProgram program(fragment, vertex);
	program.use();

	const std::vector<float> vertices = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
	Vbo vbo(vertices);
	Vao vao(0, 3, Gl::Type::Float, false, 3 * sizeof(float), (void*) 0);

	while (!GetWindow().shouldClose())
	{
		GetWindow().clearColor(0.2f, 0.3f, 0.3f, 1.0f);	   // TODO: create class Color
		GetWindow().clear(GL_COLOR_BUFFER_BIT);			   // TODO: change to enum class

		program.use();
		vao.bind();
		Gl::drawArrays(GL_TRIANGLES, 0, 3);

		GetWindow().swapBuffers();
		GetWindow().pollEvent();

		GetWorld().update();
	}
}

void VaKon2D::initCore()
{
	// !!!!!! don't change an order !!!!!! -->
	Logger::initLogger();
	GlfwWrapper::initGlfw(3, 3);					// TODO: get versions from a config file
	GetWindow().create({800, 600}, "Game name");	// TODO: get size & title from a config file
	GladWrapper::initGlad();
	GetWorld().init();
	// <---------------------------------------
}

void VaKon2D::hello(int world)
{
	std::cout << "World: " << world << std::endl;
}
