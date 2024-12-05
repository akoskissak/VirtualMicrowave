#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <iostream>
#include "irrklang/irrKlang.h"

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "door.h"
#include "microwave.h"
#include "text.h"

enum class MicrowaveState;

struct MousePosition {
    float x;
    float y;
};

extern MousePosition mousePos;

void mouseCallback(GLFWwindow* window, double mouseX, double mouseY);
void generateCircleVertices(float circle[], int numSegments, float centerX, float centerY, float r);
void updateTexture(MicrowaveState state, Texture& on, Texture& off);
void updateTimer(std::string& timer, int number);
bool updateTimer(std::string& timer);