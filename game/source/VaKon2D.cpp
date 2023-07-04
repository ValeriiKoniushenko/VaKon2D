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
#include "Image.h"
#include "Keyboard.h"
#include "Logger.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Vao.h"
#include "Vbo.h"
#include "Window.h"
#include "World.h"

#include <iostream>

void VaKon2D::start()
{
	initCore();

	GetWindow().viewport(0, 0, 800, 600);

	ShaderProgram program(true);
	{
		Shader vertex("assets/shaders/main-vertex.glsl", Gl::Shader::Type::Vertex);
		Shader fragment("assets/shaders/main-fragment.glsl", Gl::Shader::Type::Fragment);
		program.attachShader(vertex);
		program.attachShader(fragment);
	}

	program.link();
	program.use();

	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// clang-format off
	const std::vector<float> vertices = {
	    0.f, 0.f,  0.f, 0.f,
	    1.f, 1.f,  1.f, 1.f,
	    0.f, 1.f,  0.f, 1.f,

	    0.f, 0.f,  0.f, 0.f,
	    1.f, 0.f,  1.f, 0.f,
	    1.f, 1.f,  1.f, 1.f,
	};
	// clang-format on

	Vbo vbo(vertices);
	Vao vao(true, true);
	Gl::Vao::vertexAttribPointer(0, 2, Gl::Type::Float, false, 4 * sizeof(float), (void*) 0);
	Gl::Vao::enableVertexAttribArray(0);

	Gl::Vao::vertexAttribPointer(1, 2, Gl::Type::Float, false, 4 * sizeof(float), reinterpret_cast<const void*>(2 * sizeof(float)));
	Gl::Vao::enableVertexAttribArray(1);

	GLuint texture = Gl::Texture::generate();
	Gl::Texture::bind(Gl::Texture::Target::Texture2D, texture);
	Gl::Texture::setWrapS(Gl::Texture::Wrap::Clamp2Edge);
	Gl::Texture::setWrapT(Gl::Texture::Wrap::Clamp2Edge);
	Gl::Texture::setMinFilter(Gl::Texture::MinFilter::LinearMipmapLinear);
	Gl::Texture::setMagFilter(Gl::Texture::MagFilter::Linear);

	Image image("assets/textures/apple.png");
	image.loadToGpu();
	Gl::Texture::generateMipmap(Gl::Texture::Target::Texture2D);

	while (!GetWindow().shouldClose())
	{
		GetWindow().clearColor(0.2f, 0.3f, 0.3f, 1.0f);	   // TODO: create class Color
		GetWindow().clear(GL_COLOR_BUFFER_BIT);			   // TODO: change to enum class

		program.use();
		glBindTexture(GL_TEXTURE_2D, texture);
		vao.bind();
		Gl::drawArrays(GL_TRIANGLES, 0, 6);

		if (Keyboard::isKeyPressed(Keyboard::Key::F5))
		{
			Shader vertex("assets/shaders/main-vertex.glsl", Gl::Shader::Type::Vertex);
			Shader fragment("assets/shaders/main-fragment.glsl", Gl::Shader::Type::Fragment);
			program.recreateAndLink(vertex, fragment);
			program.use();
		}

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
