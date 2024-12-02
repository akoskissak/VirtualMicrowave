#include "door.h"
#include "main.h"
#include <GLFW/glfw3.h>  // Make sure GLFW is included here

void doorClick(GLFWwindow* window, DoorState& doorState, float& doorAnimationTime, MicrowaveState &microwaveState) {
    // Rectangle vertices (normalized coordinates in OpenGL space)
    float rectX1 = 0.47f, rectX2 = 0.68f, rectY1 = -0.44f, rectY2 = -0.6f;

    // Get mouse position in window coordinates
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    // Convert mouse coordinates to normalized device coordinates (NDC)
    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    float normMouseX = (2.0f * mouseX) / windowWidth - 1.0f;
    float normMouseY = 1.0f - (2.0f * mouseY) / windowHeight;

    // Check if the click is inside the rectangle
    if (isInsideRectangle(normMouseX, normMouseY, rectX1, rectX2, rectY1, rectY2)) {
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            if (doorState == DoorState::Closed) {
                doorState = DoorState::Opening;
                if (microwaveState == MicrowaveState::Cooking)
                    microwaveState = MicrowaveState::Paused;
                if (microwaveState == MicrowaveState::Finished)
                    microwaveState = MicrowaveState::Idle;
                doorAnimationTime = 0.0f;  // Reset animation time when opening starts
            }
        }
    }
}

bool isInsideRectangle(float x, float y, float rectX1, float rectX2, float rectY1, float rectY2) {
    // Check if the mouse coordinates are inside the rectangle
    return (x >= rectX1 && x <= rectX2 && y >= rectY2 && y <= rectY1);
}

float doorOpeningAndClosing(GLFWwindow* window, float doorOpenFactor, DoorState& doorState, float& doorAnimationTime, MicrowaveState &microwaveState) {
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS && doorState == DoorState::Closed) {
        doorState = DoorState::Opening;
		if (microwaveState == MicrowaveState::Cooking)
			microwaveState = MicrowaveState::Paused;
        if (microwaveState == MicrowaveState::Finished)
            microwaveState = MicrowaveState::Idle;
        doorAnimationTime = 0.0f;  // Reset animation time when opening starts
    }
    else if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS && doorState == DoorState::Open) {
        doorState = DoorState::Closing;
        doorAnimationTime = 0.0f;  // Reset animation time when closing starts
    }

    if (doorState == DoorState::Opening) {
        doorAnimationTime += 0.2f;
        doorOpenFactor = doorAnimationTime;

        if (doorOpenFactor >= 1.0f) {
            doorOpenFactor = 1.0f;
            doorState = DoorState::Open;
        }
    }
    else if (doorState == DoorState::Closing) {
        doorAnimationTime += 0.2f;
        doorOpenFactor = 1.0f - doorAnimationTime;

        if (doorOpenFactor <= 0.0f) {
            doorOpenFactor = 0.0f;
            doorState = DoorState::Closed;
        }
    }

    return doorOpenFactor;
}
