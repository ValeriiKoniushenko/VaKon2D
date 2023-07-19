#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aCv;

out vec2 ioCv;

uniform mat4 uTransform;
uniform vec2 uResolution;

void main()
{
    ioCv = aCv;
    gl_Position = uTransform * vec4(aPos / uResolution, 0.0, 1.0);
}