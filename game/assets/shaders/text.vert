#version 330 core
layout (location = 0) in vec2 aVertex;// <vec2 pos, vec2 tex>
layout (location = 1) in vec2 aUv;// <vec2 pos, vec2 tex>

out vec2 TexCoords;

uniform vec2 uResolution;

void main()
{
    gl_Position = vec4(aVertex / uResolution, 0.0, 1.0);
    TexCoords = aUv;
}