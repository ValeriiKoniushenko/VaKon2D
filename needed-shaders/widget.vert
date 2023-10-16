#version 450 core

layout (location = 0) in vec2 aVertex;
layout (location = 1) in vec2 aCv;
layout (location = 2) in vec2 aTextRectSize;

out vec2 ioCv;
out vec2 ioTextRectSize;

uniform mat4 uCameraMatrix;
uniform mat4 uTransform;
uniform vec2 uAtlasSize;
uniform vec2 uResolution;

void main()
{
    ioCv = aCv / uAtlasSize;
    ioTextRectSize = aTextRectSize / uAtlasSize;

    vec4 offset = vec4(1.0f, -1.0f, 0.f, 0.f);
    gl_Position = uCameraMatrix * uTransform * vec4(aVertex / uResolution, 0.0, 1.0) - offset;
}