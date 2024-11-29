#ifndef DOOR_H
#define DOOR_H

#include <GL/glew.h>    // Include GLEW first
#include <GLFW/glfw3.h>  // GLFW or other OpenGL-related libraries
#include <GL/gl.h> 

enum class MicrowaveState;

enum class DoorState {
    Closed = 0,
    Opening = 1,
    Open = 2,
    Closing = 3
};

// Function declarations
void doorClick(GLFWwindow* window, DoorState& doorState, float& doorAnimationTime, MicrowaveState &microwaveState);
bool isInsideRectangle(float x, float y, float rectX1, float rectX2, float rectY1, float rectY2);
float doorOpeningAndClosing(GLFWwindow* window, float doorOpenFactor, DoorState& doorState, float& doorAnimationTime, MicrowaveState &microwaveState);

#endif

