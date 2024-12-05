#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTex;

out vec2 texCoord;

uniform float scale;

void main()
{
    gl_Position = vec4(aPos * scale, 0.0, 1.0);
    texCoord = aTex;
}