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
#include "Vao.h"
#include "Vbo.h"
#include "Widget.h"
#include "WidgetReflector.h"
#include "Window.h"
#include "World.h"
#include "WorldVariables.h"
#include "ft2build.h"
#include FT_FREETYPE_H
#include "Font.h"
#include "FreeTypeLibrary.h"

#include <iostream>
#include <map>

/// Holds all state information relevant to a character as loaded using FreeType

unsigned int VAO;

void RenderText(Font& font, ShaderProgram& shader, std::string text, float x, float y, float size, glm::vec3 color, Vbo& vbo, Vao& vao)
{
	shader.use();
	shader.uniform(
		"uResolution", static_cast<float>(GetWindow().getSize().width), static_cast<float>(GetWindow().getSize().height));
	glActiveTexture(GL_TEXTURE0);
	vao.bind();

	const float scale = size / Font::defaultRenderSize * 2.f;
	for (auto c = text.begin(); c != text.end(); c++)
	{
		Font::Character ch = font.getCharacter(*c);

		float xpos = x + ch.Bearing.x * scale;
		float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		float w = ch.Size.x * scale;
		float h = ch.Size.y * scale;

		// clang-format off
		float vertices[24] = {
			xpos, ypos + h, 0.0f, 0.0f,
			xpos, ypos, 0.0f, 1.0f,
			xpos + w, ypos, 1.0f, 1.0f,
			xpos, ypos + h, 0.0f, 0.0f,
			xpos + w, ypos, 1.0f, 1.0,
			xpos + w, ypos + h, 1.0f, 0.0f
		};
		// clang-format on

		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		vbo.bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);	// be sure to use glBufferSubData and not glBufferData
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		x += (ch.Advance >> 6) * scale;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void VaKon2D::start()
{
	initCore();

	GetWindow().viewport(0, 0, 800, 600);

	CustomShaderProgram textProgram(true);
	{
		Shader vertex("assets/shaders/text.vert", Gl::Shader::Type::Vertex);
		Shader fragment("assets/shaders/text.frag", Gl::Shader::Type::Fragment);
		textProgram.attachShader(vertex);
		textProgram.attachShader(fragment);
	}
	textProgram.link();
	textProgram.use();

	Font font;
	font.loadFromFile("assets/fonts/Roboto-Medium.ttf");

	Vao vao(true, true);
	Vbo vbo(true, true);
	vbo.data(std::vector<float>(24), GL_DYNAMIC_DRAW);
	Gl::Vao::vertexAttribPointer(0, 2, Gl::Type::Float, false, 4 * sizeof(float), reinterpret_cast<void*>(0 * sizeof(float)));
	Gl::Vao::vertexAttribPointer(1, 2, Gl::Type::Float, false, 4 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));

	while (!GetWindow().shouldClose())
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		RenderText(font, textProgram, "This is sample text", 25.0f, -25.0f, 32.f, glm::vec3(0.5, 0.8f, 0.2f), vbo, vao);
		RenderText(font, textProgram, "(C) LearnOpenGL.com", 20.0f, 20.0f, 16.f, glm::vec3(0.3, 0.7f, 0.9f), vbo, vao);

		GetWindow().swapBuffers();
		GetWindow().pollEvent();
	}
	/*CustomShaderProgram program(true);
	{
		Shader vertex("assets/shaders/main-vertex.glsl", Gl::Shader::Type::Vertex);
		Shader fragment("assets/shaders/main-fragment.glsl", Gl::Shader::Type::Fragment);
		program.attachShader(vertex);
		program.attachShader(fragment);
	}
	program.link();
	program.use();

	Texture texture(Gl::Texture::Target::Texture2D, true, true);
	Image image("assets/textures/apple.png");
	image.setInternalChannel(Gl::Texture::Channel::SRGBA);
	texture.setImage(image);
	texture.setMagAndMinFilter(Gl::Texture::MagFilter::Linear, Gl::Texture::MinFilter::LinearMipmapLinear);

	Widget widget;
	widget.setTexture(texture);
	widget.prepare();

	KeyboardInputAction iaWidgetReflector("WidgetReflector", Keyboard::Key::F1);
	iaWidgetReflector.setFrequency(KeyboardInputAction::TimeT(100));
	iaWidgetReflector.onAction.subscribe([]() { getWidgetReflector().toggle(); });

	textProgram.use();
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		throw std::runtime_error("FreeType: Could not init FreeType Library");
	}

	FT_Face face;
	if (FT_New_Face(ft, "assets/fonts/Roboto-Medium.ttf", 0, &face))
	{
		throw std::runtime_error("FreeType: Failed to load font");
	}

	FT_Set_Pixel_Sizes(face, 0, 500);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
	{
		throw std::runtime_error("FreeType: Failed to load Glyph");
	}

	Texture charTexture(Gl::Texture::Target::Texture2D, true, true);
	Gl::Texture::texImage2D(Gl::Texture::Target::Texture2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0,
		GL_RED, GL_UNSIGNED_INT, face->glyph->bitmap.buffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	Vao charVao(true, true);
	Vbo charVbo(true, true);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) (2 * sizeof(float)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!GetWindow().shouldClose())
	{
		GetWindow().clearColor(0.2f, 0.3f, 0.3f, 1.0f);	   // TODO: create class Color
		GetWindow().clear(GL_COLOR_BUFFER_BIT);			   // TODO: change to enum class

		widget.draw(program);

		textProgram.use();
		textProgram.uniform(
			"uResolution", static_cast<float>(GetWindow().getSize().width), static_cast<float>(GetWindow().getSize().height));
		glActiveTexture(GL_TEXTURE0);
		charVao.bind();
		float xpos = -100;
		float ypos = 0;

		float w = face->glyph->bitmap.width;
		float h = face->glyph->bitmap.rows;
		// update VBO for each character
		// clang-format off
		float vertices[6][4] = {
			{xpos, ypos + h, 0.0f, 0.0f},
			{xpos, ypos, 0.0f, 1.0f},
			{xpos + w, ypos, 1.0f, 1.0f},
			{xpos, ypos + h, 0.0f, 0.0f},
			{xpos + w, ypos, 1.0f, 1.0f},
			{xpos + w, ypos + h, 1.0f, 0.0f}
		};
		// clang-format on

		charTexture.bind();
		charVbo.bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		GetWindow().swapBuffers();
		GetWorldVariables().forceClear({"mouse-wheel-x", "mouse-wheel-y", "inputted-text"});
		GetWindow().pollEvent();

		GetWorld().update();
		getUpdateableCollector().updateAll();
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);*/
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