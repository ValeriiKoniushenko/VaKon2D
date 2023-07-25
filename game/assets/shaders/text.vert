#version 330 core

layout (location = 0) in vec2 aVertex;
layout (location = 1) in vec2 aUv;

out vec2 TexCoords;

uniform vec2 uResolution;
uniform mat4 uTransform;

void main()
{
    TexCoords = aUv;
    gl_Position = uTransform * vec4(aVertex / uResolution, 0.0, 1.0);
}