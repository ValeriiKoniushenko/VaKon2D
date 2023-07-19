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

#include <iostream>
#include <map>

/// Holds all state information relevant to a character as loaded using FreeType
struct Character
{
	unsigned int TextureID;	   // ID handle of the glyph texture
	glm::ivec2 Size;		   // Size of glyph
	glm::ivec2 Bearing;		   // Offset from baseline to left/top of glyph
	unsigned int Advance;	   // Horizontal offset to advance to next glyph
};

std::map<GLchar, Character> Characters;
unsigned int VAO, VBO;

void RenderText(ShaderProgram& shader, std::string text, float x, float y, float scale, glm::vec3 color)
{
	// activate corresponding render state
	shader.use();
	shader.uniform(
		"uResolution", static_cast<float>(GetWindow().getSize().width), static_cast<float>(GetWindow().getSize().height));
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	// iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];

		float xpos = x + ch.Bearing.x * scale;
		float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		float w = ch.Size.x * scale;
		float h = ch.Size.y * scale;
		// update VBO for each character
		float vertices[6][4] = {{xpos, ypos + h, 0.0f, 0.0f}, {xpos, ypos, 0.0f, 1.0f}, {xpos + w, ypos, 1.0f, 1.0f},

			{xpos, ypos + h, 0.0f, 0.0f}, {xpos + w, ypos, 1.0f, 1.0f}, {xpos + w, ypos + h, 1.0f, 0.0f}};
		// render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);	// be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale;	   // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64
										   // to get amount of pixels))
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

	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		return;
	}

	FT_Face face;
	if (FT_New_Face(ft, "assets/fonts/Roboto-Medium.ttf", 0, &face))
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		return;
	}
	else
	{
		// set size to load glyphs as
		FT_Set_Pixel_Sizes(face, 0, 48);

		// disable byte-alignment restriction
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// load first 128 characters of ASCII set
		for (unsigned char c = 0; c < 128; c++)
		{
			// Load character glyph
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}
			// generate texture
			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer);
			// set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// now store character for later use
			Character character = {texture, glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top), static_cast<unsigned int>(face->glyph->advance.x)};
			Characters.insert(std::pair<char, Character>(c, character));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!GetWindow().shouldClose())
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		RenderText(textProgram, "This is sample text", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
		RenderText(textProgram, "(C) LearnOpenGL.com", 540.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));

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
	// <---------------------------------------
}