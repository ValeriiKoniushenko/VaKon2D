#version 330 core

layout (location = 0) in vec2 aVertex;
layout (location = 1) in vec2 aCv;

out vec2 ioCv;

uniform vec2 uResolution;
uniform mat4 uTransform;

void main()
{
    ioCv = aCv;
    gl_Position = uTransform * vec4(aVertex / uResolution, 0.0, 1.0);
}