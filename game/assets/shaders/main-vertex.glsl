#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aCv;

out vec2 ioCv;

void main()
{
    ioCv = aCv;
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
}