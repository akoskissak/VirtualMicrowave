#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h> 
#include "door.h"
#include "main.h"

enum class DoorState;

enum class MicrowaveState {
	Idle,
	Cooking,
	Paused,
	Error,
	Finished
};

enum ButtonType {
	Start,
	Stop,
	Reset
};

int numClick(GLFWwindow* window, irrklang::ISoundEngine* soundEngine);
ButtonType checkButtonClick(GLFWwindow* window, MicrowaveState& microwaveState, DoorState doorState, std::string& timer);