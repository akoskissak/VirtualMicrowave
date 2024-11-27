#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

out vec3 color;
out vec2 texCoord;

uniform float doorOpenFactor;

void main()
{
    vec2 position = aPos;

    // Door opening logic
    if (aPos.x > 0.0) {  // Right side of the door (positive x-axis)
        position.x = aPos.x - doorOpenFactor * 0.1;

        if (aPos.y > 0.0) {
                position.y = aPos.y + doorOpenFactor * 0.08; // Move slightly upwards
            } else {
                position.y = aPos.y - doorOpenFactor * 0.1; // Move slightly downwards
            }
        }

    gl_Position = vec4(position, 0.0, 1.0);
    color = aColor;
    texCoord = aTex;
}
