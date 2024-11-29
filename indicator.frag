#version 330 core

out vec4 FragColor;

uniform float time;

void main() {
    float intensity = 0.5 - 0.5 * sin(time * 1.7);

    // Set the color: black when off, blue when on
    FragColor = vec4(0.0, 0.0, intensity - 0.1, 1.0);
}