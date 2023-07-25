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

#include "CustomShaderProgram.h"
#include "GladWrapper.h"
#include "Image.h"
#include "InputAction.h"
#include "Keyboard.h"
#include "Logger.h"
#include "Shader.h"
#include "Texture.h"
#include "UpdateableCollector.h"
#include "Widget.h"
#include "WidgetReflector.h"
#include "Window.h"
#include "World.h"
#include "WorldVariables.h"
#include "ft2build.h"
#include FT_FREETYPE_H
#include "Font.h"
#include "FreeTypeLibrary.h"
#include "LineText.h"
#include "ShaderPack.h"
#include "UtilsFunctions.h"

#include <iostream>

void VaKon2D::start()
{
	initCore();

	GetWindow().viewport(0, 0, 800, 600);

	ShaderPack shaderPack;
	shaderPack.loadShaders("text", "assets/shaders/text.vert", "assets/shaders/text.frag");
	shaderPack.loadShaders("widget", "assets/shaders/widget.vert", "assets/shaders/widget.frag");

	Texture texture(Gl::Texture::Target::Texture2D, true, true);
	Image image("assets/textures/apple.png");
	image.setInternalChannel(Gl::Texture::Channel::SRGBA);
	texture.setImage(image);
	texture.setMagAndMinFilter(Gl::Texture::MagFilter::Linear, Gl::Texture::MinFilter::LinearMipmapLinear);

	Font font("assets/fonts/Roboto-Medium.ttf");
	LineText text(font, "Hello world");
	text.setTexture(texture);
	text.prepare(shaderPack);

	KeyboardInputAction iaWidgetReflector("WidgetReflector", Keyboard::Key::F1);
	iaWidgetReflector.setFrequency(KeyboardInputAction::TimeT(100));
	iaWidgetReflector.setIsRepeatable(false);
	iaWidgetReflector.onAction.subscribe([]() { getWidgetReflector().toggle(); });

	while (!GetWindow().shouldClose())
	{
		GetWindow().clearColor({0.2f, 0.3f, 0.3f});
		GetWindow().clear(GL_COLOR_BUFFER_BIT);

		text.draw(shaderPack);

		getUpdateableCollector().updateAll();
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
	GetWorld().init();
	GetFreeTypeLibrary().init();
	// <---------------------------------------
}