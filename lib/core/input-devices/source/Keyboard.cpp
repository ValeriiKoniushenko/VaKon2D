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

#include "Keyboard.h"

#include <stdexcept>

Keyboard::Key Keyboard::stringToKey(const std::string& key)
{
	if (key == "None")
	{
		return Key::None;
	}
	else if (key == "A")
	{
		return Key::A;
	}
	else if (key == "B")
	{
		return Key::B;
	}
	else if (key == "C")
	{
		return Key::C;
	}
	else if (key == "D")
	{
		return Key::D;
	}
	else if (key == "E")
	{
		return Key::E;
	}
	else if (key == "F")
	{
		return Key::F;
	}
	else if (key == "G")
	{
		return Key::G;
	}
	else if (key == "H")
	{
		return Key::H;
	}
	else if (key == "I")
	{
		return Key::I;
	}
	else if (key == "J")
	{
		return Key::J;
	}
	else if (key == "K")
	{
		return Key::K;
	}
	else if (key == "L")
	{
		return Key::L;
	}
	else if (key == "M")
	{
		return Key::M;
	}
	else if (key == "N")
	{
		return Key::N;
	}
	else if (key == "O")
	{
		return Key::O;
	}
	else if (key == "P")
	{
		return Key::P;
	}
	else if (key == "Q")
	{
		return Key::Q;
	}
	else if (key == "R")
	{
		return Key::R;
	}
	else if (key == "S")
	{
		return Key::S;
	}
	else if (key == "T")
	{
		return Key::T;
	}
	else if (key == "U")
	{
		return Key::U;
	}
	else if (key == "V")
	{
		return Key::V;
	}
	else if (key == "W")
	{
		return Key::W;
	}
	else if (key == "X")
	{
		return Key::X;
	}
	else if (key == "Y")
	{
		return Key::Y;
	}
	else if (key == "Z")
	{
		return Key::Z;
	}
	else if (key == "Esc")
	{
		return Key::Esc;
	}
	else if (key == "Space")
	{
		return Key::Space;
	}
	else if (key == "PgDown")
	{
		return Key::PgDown;
	}
	else if (key == "PgUp")
	{
		return Key::PgUp;
	}
	else if (key == "End")
	{
		return Key::End;
	}
	else if (key == "Home")
	{
		return Key::Home;
	}
	else if (key == "Left")
	{
		return Key::Left;
	}
	else if (key == "Up")
	{
		return Key::Up;
	}
	else if (key == "Right")
	{
		return Key::Right;
	}
	else if (key == "Down")
	{
		return Key::Down;
	}
	else if (key == "Select")
	{
		return Key::Select;
	}
	else if (key == "Print")
	{
		return Key::Print;
	}
	else if (key == "Execute")
	{
		return Key::Execute;
	}
	else if (key == "Snapshot")
	{
		return Key::Snapshot;
	}
	else if (key == "Insert")
	{
		return Key::Insert;
	}
	else if (key == "Delete")
	{
		return Key::Delete;
	}
	else if (key == "Help")
	{
		return Key::Help;
	}
	else if (key == "Numpad0")
	{
		return Key::Numpad0;
	}
	else if (key == "Numpad1")
	{
		return Key::Numpad1;
	}
	else if (key == "Numpad2")
	{
		return Key::Numpad2;
	}
	else if (key == "Numpad3")
	{
		return Key::Numpad3;
	}
	else if (key == "Numpad4")
	{
		return Key::Numpad4;
	}
	else if (key == "Numpad5")
	{
		return Key::Numpad5;
	}
	else if (key == "Numpad6")
	{
		return Key::Numpad6;
	}
	else if (key == "Numpad7")
	{
		return Key::Numpad7;
	}
	else if (key == "Numpad8")
	{
		return Key::Numpad8;
	}
	else if (key == "Numpad9")
	{
		return Key::Numpad9;
	}
	else if (key == "Multiply")
	{
		return Key::Multiply;
	}
	else if (key == "Add")
	{
		return Key::Add;
	}
	else if (key == "Separator")
	{
		return Key::Separator;
	}
	else if (key == "Subtract")
	{
		return Key::Subtract;
	}
	else if (key == "Decimal")
	{
		return Key::Decimal;
	}
	else if (key == "Divide")
	{
		return Key::Divide;
	}
	else if (key == "F1")
	{
		return Key::F1;
	}
	else if (key == "F2")
	{
		return Key::F2;
	}
	else if (key == "F3")
	{
		return Key::F3;
	}
	else if (key == "F4")
	{
		return Key::F4;
	}
	else if (key == "F5")
	{
		return Key::F5;
	}
	else if (key == "F6")
	{
		return Key::F6;
	}
	else if (key == "F7")
	{
		return Key::F7;
	}
	else if (key == "F8")
	{
		return Key::F8;
	}
	else if (key == "F9")
	{
		return Key::F9;
	}
	else if (key == "F10")
	{
		return Key::F10;
	}
	else if (key == "F11")
	{
		return Key::F11;
	}
	else if (key == "F12")
	{
		return Key::F12;
	}
	else if (key == "F13")
	{
		return Key::F13;
	}
	else if (key == "F14")
	{
		return Key::F14;
	}
	else if (key == "F15")
	{
		return Key::F15;
	}
	else if (key == "F16")
	{
		return Key::F16;
	}
	else if (key == "F17")
	{
		return Key::F17;
	}
	else if (key == "F18")
	{
		return Key::F18;
	}
	else if (key == "F19")
	{
		return Key::F19;
	}
	else if (key == "F20")
	{
		return Key::F20;
	}
	else if (key == "F21")
	{
		return Key::F21;
	}
	else if (key == "F22")
	{
		return Key::F22;
	}
	else if (key == "F23")
	{
		return Key::F23;
	}
	else if (key == "F24")
	{
		return Key::F24;
	}
	else if (key == "LShift")
	{
		return Key::LShift;
	}
	else if (key == "RShift")
	{
		return Key::RShift;
	}
	else if (key == "LControl")
	{
		return Key::LControl;
	}
	else if (key == "RControl")
	{
		return Key::RControl;
	}
	else if (key == "LMenu")
	{
		return Key::LMenu;
	}
	else if (key == "RMenu")
	{
		return Key::RMenu;
	}
	else if (key == "Back")
	{
		return Key::Back;
	}
	else if (key == "Tab")
	{
		return Key::Tab;
	}

	throw std::runtime_error("Can't find such key as: " + key);

	return Key::None;
}

bool Keyboard::isKeyPressed(Key key)
{
	if (GetKeyState(static_cast<int>(key)) < 0)
	{
		return true;
	}
	return false;
}

bool Keyboard::isKeyReleased(Key key)
{
	if (GetKeyState(static_cast<int>(key)) > 0)
	{
		return true;
	}
	return false;
}
