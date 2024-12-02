#ifndef MICROWAVE_H
#define MICROWAVE_H

#include <GL/glew.h>    // Include GLEW first
#include <GLFW/glfw3.h>  // GLFW or other OpenGL-related libraries
#include <GL/gl.h> 
#include "door.h"
#include "main.h"

enum class MicrowaveState {
	Idle,       // Microwave is on but not running (e.g., waiting for user input)
	Cooking,    // Microwave is actively cooking
	Paused,     // Microwave cooking is paused
	Error,       // Microwave encountered an error (e.g., overheating or malfunction)
	Finished
};

enum ButtonType {
	Start,
	Stop,
	Reset
};

int numClick(GLFWwindow* window);
ButtonType checkButtonClick(GLFWwindow* window, MicrowaveState& microwaveState, DoorState doorState, std::string& timer);

#endif