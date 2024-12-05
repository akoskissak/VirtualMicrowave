#version 330 core

layout (location = 0) in vec2 aPos;

layout (location = 1) in vec2 aTex;

out vec2 texCoord;

uniform float doorOpenFactor;

void main()
{
    vec2 position = aPos;

    // Animacija otvaranja vrata
    if (aPos.x > 0.0) {
        position.x = aPos.x - doorOpenFactor * 0.1;

        if (aPos.y > 0.0) {
                position.y = aPos.y + doorOpenFactor * 0.08;
            } else {
                position.y = aPos.y - doorOpenFactor * 0.1;
            }
        }

    gl_Position = vec4(position, 0.0, 1.0);

    texCoord = aTex;
}
