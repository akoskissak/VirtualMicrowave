#ifndef MAIN_H
#define MAIN_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "door.h"
#include "microwave.h"

// Mouse position structure
struct MousePosition {
    float x;
    float y;
};
extern MousePosition mousePos;

// Window dimensions
extern int windowWidth;
extern int windowHeight;

// Aspect ratios and scale factors
extern float microwaveAspect;
extern float plateAspect;
extern float foodAspect;
extern float scale;
extern float microwaveWidth;
extern float microwaveHeight;
extern float plateWidth;
extern float plateHeight;
extern float foodWidth;
extern float foodHeight;
extern float doorWidth;
extern float doorHeight;
extern float insideWidth;
extern float insideHeight;

// Microwave, Plate, Food, Door, and Inside vertices
extern GLfloat microwaveVertices[];
extern GLfloat plateVertices[];
extern GLfloat foodVertices[];
extern GLfloat doorVertices[];
extern GLfloat insideVertices[];

// Indices for elements
extern GLuint microwaveIndices[];
extern GLuint plateIndices[];
extern GLuint foodIndices[];
extern GLuint doorIndices[];
extern GLuint insideIndices[];

// Function declarations
void mouseCallback(GLFWwindow* window, double mouseX, double mouseY);
void generateCircleVertices(float circle[], int numSegments, float centerX, float centerY, float r);
void updateLampTexture(MicrowaveState state, Texture& lampOn, Texture& lampOff);

#endif // MAIN_H