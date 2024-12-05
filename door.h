#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h> 
#include "irrklang/irrKlang.h"
#include "main.h"

enum class MicrowaveState;

enum class DoorState {
    Closed = 0,
    Opening = 1,
    Open = 2,
    Closing = 3
};

// Function declarations
void doorClick(GLFWwindow* window, DoorState& doorState, float& doorAnimationTime, MicrowaveState &microwaveState, irrklang::ISoundEngine* soundEngine);
bool isInsideRectangle(float x, float y, float rectX1, float rectX2, float rectY1, float rectY2);
float doorOpeningAndClosing(GLFWwindow* window, float doorOpenFactor, DoorState& doorState, float& doorAnimationTime, MicrowaveState &microwaveState, irrklang::ISoundEngine* soundEngine);