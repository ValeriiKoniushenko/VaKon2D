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

#include "TextBox.h"

#include "Font.h"
#include "LineText.h"
#include "Logger.h"
#include "ShaderPack.h"

#include <boost/algorithm/string.hpp>

std::string TextBox::getComponentName() const {
    return componentName;
}

void TextBox::setText(const std::string &text) {
    if (!font_) {
        spdlog::get("core")->critical("Can't set text without a font");
        BOOST_ASSERT_MSG(font_, "Can't set text without a font");
        return;
    }

    std::vector<std::string> strings;
    boost::split(strings, text, boost::is_any_of("\n"));

    rows_.resize(strings.size());

    float maxWidth = 0;
    std::size_t i = 0;
    for (auto &lineText: rows_) {
        lineText.setText(strings[i]);
        lineText.setFont(*font_);
        if (lineText.getTextWidth() > maxWidth) {
            maxWidth = lineText.getTextWidth();
        }

        if (i != 0) {
            lineText.move({0.f, lineText.getTextHeight()});
        }
        ++i;
    }

    if (!rows_.empty()) {
        setSize({maxWidth, rows_.front().getTextHeight() * rows_.size()});
    }
}

void TextBox::setFont(Font &font) {
    font_ = &font;
    for (auto &lineText: rows_) {
        lineText.setFont(font);
    }
}

void TextBox::prepare(ShaderPack &shader) {
    Widget::prepare(shader);

    for (auto &lineText: rows_) {
        lineText.prepare(shader);
    }
}

void TextBox::draw(ShaderPack &shaderProgram, Camera* camera) {
    Widget::draw(shaderProgram);

    for (auto &lineText: rows_) {
        lineText.draw(shaderProgram);
    }
}
