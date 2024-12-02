#include "microwave.h"
#include "main.h"
#include <GLFW/glfw3.h>

int numClick(GLFWwindow* window) {
	struct Rectangle {
		float x1, x2, y1, y2;
		int digit;
	};

	Rectangle rectangles[] = {
		{0.48f, 0.53f, 0.43f, 0.34f, 1}, // NUM 1
		{0.53f, 0.62f, 0.43f, 0.34f, 2}, // NUM 2
		{0.62f, 0.68f, 0.43f, 0.34f, 3}, // NUM 3
		{0.48f, 0.53f, 0.34f, 0.25f, 4}, // NUM 4
		{0.53f, 0.62f, 0.34f, 0.25f, 5}, // NUM 5
		{0.62f, 0.68f, 0.34f, 0.25f, 6}, // NUM 6
		{0.48f, 0.53f, 0.25f, 0.15f, 7}, // NUM 7
		{0.53f, 0.62f, 0.25f, 0.15f, 8}, // NUM 8
		{0.62f, 0.68f, 0.25f, 0.15f, 9}, // NUM 9
		{0.54f, 0.61f, 0.15f, 0.06f, 0}	 // NUM 0
	};

	static bool wasMousePressed = false;
	for (const auto& rect : rectangles) {
		if (isInsideRectangle(mousePos.x, mousePos.y, rect.x1, rect.x2, rect.y1, rect.y2)) {
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !wasMousePressed) {
				std::cout << "NUM " << rect.digit << " clicked!" << std::endl;
				wasMousePressed = true;
				return rect.digit;
			}
			else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
				wasMousePressed = false;
			}
		}
	}
	return -1;
}

ButtonType checkButtonClick(GLFWwindow* window, MicrowaveState& microwaveState, DoorState doorState, std::string& timer) {
	struct Button {
		float x1, x2, y1, y2;
		ButtonType type;
	};

	Button buttons[] = {
		{0.48f, 0.54f, 0.15f, 0.06f, ButtonType::Stop}, // Stop Button
		{0.61f, 0.68f, 0.15f, 0.06f, ButtonType::Start},  // Start Button
		{0.53f, 0.615f, 0.03f, -0.03f, ButtonType::Reset}  // Reset Button
	};

	static bool wasMousePressed = false;

	for (const auto& button : buttons) {
		if (isInsideRectangle(mousePos.x, mousePos.y, button.x1, button.x2, button.y1, button.y2)) {
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !wasMousePressed) {
				if (button.type == ButtonType::Start && doorState == DoorState::Closed && timer != "00:00")
					microwaveState = MicrowaveState::Cooking;
				else if (button.type == ButtonType::Stop)
					microwaveState = MicrowaveState::Paused;
				else if (button.type == ButtonType::Reset) {
					microwaveState = MicrowaveState::Idle;
					timer = "00:00";
				}
					
				std::cout << "BUTTON " << button.type << " clicked! 0 - start, 1 - stop, 2 - reset" << std::endl;
				wasMousePressed = true;
				return button.type;
			}
		}
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		wasMousePressed = false;
	}
}