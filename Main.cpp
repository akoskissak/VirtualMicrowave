#include <iostream>
#include <fstream>
#include <sstream>

//Biblioteke OpenGL-a
#include <GL/glew.h>   //Omogucava laksu upotrebu OpenGL naredbi
#include <GLFW/glfw3.h>//Olaksava pravljenje i otvaranje prozora (konteksta) sa OpenGL sadrzajem
#include<stb/stb_image.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Texture.h"

int windowWidth = 1600;  // Width of your window
int windowHeight = 900; // Height of your window

float microwaveAspect = 653.0f / 376.0f;
float plateAspect = 1280.0f / 640.0f;
float foodAspect = 531.0f / 400.0f;

float scale = 1.6f;
float microwaveWidth = 0.81625f * scale;
float microwaveHeight = 0.83556f * scale;

float plateWidth = microwaveWidth * 0.4f;
float plateHeight = plateWidth / plateAspect;

float foodWidth = plateWidth * 0.8f;
float foodHeight = foodWidth / foodAspect;

// scale factor

// Microwave rectangle vertices
GLfloat microwaveVertices[] = {
	// X         Y            R     G     B     U     V
	-microwaveWidth / 2, -microwaveHeight / 2, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-microwaveWidth / 2,  microwaveHeight / 2, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 microwaveWidth / 2,  microwaveHeight / 2, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 microwaveWidth / 2, -microwaveHeight / 2, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f
};

// Plate rectangle vertices
GLfloat plateVertices[] = {
	-plateWidth / 2 - .15f, -plateHeight / 2 - 0.1f,    1.0f, 1.0f, 1.0f,    0.0f, 0.0f, // Bottom-left
	-plateWidth / 2 - .15f,  plateHeight / 2 - 0.1f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, // Top-left
	 plateWidth / 2 - .15f,  plateHeight / 2 - 0.1f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, // Top-right
	 plateWidth / 2 - .15f, -plateHeight / 2 - 0.1f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f  // Bottom-right
};

// Food rectangle vertices
GLfloat foodVertices[] = {
	-foodWidth / 2 - .18f, -foodHeight / 2 - 0.005f,    1.0f, 1.0f, 1.0f,    0.0f, 0.0f, // Bottom-left
	-foodWidth / 2 - .18f,  foodHeight / 2 - 0.005f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, // Top-left
	 foodWidth / 2 - .18f,  foodHeight / 2 - 0.005f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, // Top-right
	 foodWidth / 2 - .18f, -foodHeight / 2 - 0.005f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f  // Bottom-right
};

float doorWidth = microwaveWidth;
float doorHeight = microwaveHeight;

// Microwave Door vertices
GLfloat doorVertices[] = {
	// X         Y            R     G     B     U     V
	-doorWidth / 2, -doorHeight / 2,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // Bottom-left
	-doorWidth / 2,  doorHeight / 2,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // Top-left
	 doorWidth / 2,  doorHeight / 2,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // Top-right
	 doorWidth / 2, -doorHeight / 2,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f  // Bottom-right
};

float insideWidth = doorWidth;
float insideHeight = doorHeight;

// Microwave Inside vertices
GLfloat insideVertices[] = {
	// X         Y            R     G     B     U     V
	-insideWidth / 2, -insideHeight / 2,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // Bottom-left
	-insideWidth / 2,  insideHeight / 2,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // Top-left
	 insideWidth / 2,  insideHeight / 2,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // Top-right
	 insideWidth / 2, -insideHeight / 2,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f  // Bottom-right
};


GLuint microwaveIndices[] = {
	0, 1, 2, 0, 2, 3 // Microwave
};

GLuint plateIndices[] = {
	0, 1, 2, 0, 2, 3 // Plate
};

GLuint foodIndices[] = {
	0, 1, 2, 0, 2, 3 // Food
};

GLuint doorIndices[] = {
	0, 1, 2, 0, 2, 3   // Door
};

GLuint insideIndices[] = {
	0, 1, 2, 0, 2, 3   // Inside
};

void centerWindow(GLFWwindow* window);

// Mouse callback function
void mouseCallback(GLFWwindow* window, double mouseX, double mouseY) {
	// Convert to normalized OpenGL coordinates
	float normalizedX = (mouseX / windowWidth) * 2.0f - 1.0f;
	float normalizedY = 1.0f - (mouseY / windowHeight) * 2.0f;

	// Print the normalized coordinates
	std::cout << "Mouse X: " << normalizedX << ", Mouse Y: " << normalizedY << std::endl;
}

// Function to generate circle vertices
void generateCircleVertices(float circle[], int numSegments, float centerX, float centerY, float r);
float doorOpeningAndClosing(GLFWwindow* window, float doorOpenFactor);

int main() {
	const int numSegments = 50;  // Number of segments (e.g., 50)
	float r = 0.1f;              // Radius of the circle
	float centerX = -0.38f;      // Center X0
	float centerY = 0.3f;        // Center Y0

	// Create an array to hold circle vertices
	float circle[(numSegments + 2) * 2];  // Total points: center + perimeter

	// Generate circle vertices
	generateCircleVertices(circle, numSegments, centerX, centerY, r);




	if (!glfwInit()) // !0 == 1; glfwInit inicijalizuje GLFW i vrati 1 ako je inicijalizovana uspjesno, a 0 ako nije
	{
		std::cout << "GLFW Biblioteka se nije ucitala! :(\n";
		return 1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);

	int xPos = (videoMode->width - windowWidth) / 2;
	int yPos = (videoMode->height - windowHeight) / 2;

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Microwave", NULL, NULL);
	// Center the window


	if (window == NULL) //Ako prozor nije napravljen
	{
		std::cout << "Prozor nije napravljen! :(\n";
		glfwTerminate(); //Gasi GLFW
		return 2; //Vrati kod za gresku
	}

	glfwSetWindowPos(window, xPos, yPos);

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) //Slicno kao glfwInit. GLEW_OK je predefinisani izlazni kod za uspjesnu inicijalizaciju sadrzan unutar biblioteke
	{
		std::cout << "GLEW nije mogao da se ucita! :'(\n";
		return 3;
	}

	Shader shaderProgram("default.vert", "default.frag");
	Shader doorShader("door.vert", "door.frag");


	// Microwave VAO, VBO, EBO
	VAO microwaveVAO;
	microwaveVAO.Bind();

	VBO microwaveVBO(microwaveVertices, sizeof(microwaveVertices));
	EBO microwaveEBO(microwaveIndices, sizeof(microwaveIndices));
	microwaveVAO.LinkAttrib(microwaveVBO, 0, 2, GL_FLOAT, 7 * sizeof(float), (void*)0);
	microwaveVAO.LinkAttrib(microwaveVBO, 1, 3, GL_FLOAT, 7 * sizeof(float), (void*)(2 * sizeof(float)));
	microwaveVAO.LinkAttrib(microwaveVBO, 2, 2, GL_FLOAT, 7 * sizeof(float), (void*)(5 * sizeof(float)));
	microwaveVAO.Unbind();
	microwaveVBO.Unbind();
	microwaveEBO.Unbind();

	// Plate VAO, VBO, EBO
	VAO plateVAO;
	plateVAO.Bind();

	VBO plateVBO(plateVertices, sizeof(plateVertices));
	EBO plateEBO(plateIndices, sizeof(plateIndices));
	plateVAO.LinkAttrib(plateVBO, 0, 2, GL_FLOAT, 7 * sizeof(float), (void*)0);
	plateVAO.LinkAttrib(plateVBO, 1, 3, GL_FLOAT, 7 * sizeof(float), (void*)(2 * sizeof(float)));
	plateVAO.LinkAttrib(plateVBO, 2, 2, GL_FLOAT, 7 * sizeof(float), (void*)(5 * sizeof(float)));
	plateVAO.Unbind();
	plateVBO.Unbind();
	plateEBO.Unbind();

	// Food VAO, VBO, EBO
	VAO foodVAO;
	foodVAO.Bind();

	VBO foodVBO(foodVertices, sizeof(foodVertices));
	EBO foodEBO(foodIndices, sizeof(foodIndices));
	foodVAO.LinkAttrib(foodVBO, 0, 2, GL_FLOAT, 7 * sizeof(float), (void*)0);
	foodVAO.LinkAttrib(foodVBO, 1, 3, GL_FLOAT, 7 * sizeof(float), (void*)(2 * sizeof(float)));
	foodVAO.LinkAttrib(foodVBO, 2, 2, GL_FLOAT, 7 * sizeof(float), (void*)(5 * sizeof(float)));
	foodVAO.Unbind();
	foodVBO.Unbind();
	foodEBO.Unbind();

	// Lamp VAO, VBO, EBO
	VAO lampVAO;
	lampVAO.Bind();

	VBO lampVBO(circle, sizeof(circle));
	lampVAO.LinkAttrib(lampVBO, 0, 2, GL_FLOAT, 2 * sizeof(float), (void*)0);
	lampVAO.Unbind();
	lampVAO.Unbind();

	// Door VAO, VBO, EBO
	VAO doorVAO;
	doorVAO.Bind();

	VBO doorVBO(doorVertices, sizeof(doorVertices));
	EBO doorEBO(doorIndices, sizeof(doorIndices));
	doorVAO.LinkAttrib(doorVBO, 0, 2, GL_FLOAT, 7 * sizeof(float), (void*)0);
	doorVAO.LinkAttrib(doorVBO, 1, 3, GL_FLOAT, 7 * sizeof(float), (void*)(2 * sizeof(float)));
	doorVAO.LinkAttrib(doorVBO, 2, 2, GL_FLOAT, 7 * sizeof(float), (void*)(5 * sizeof(float)));
	doorVAO.Unbind();
	doorVBO.Unbind();
	doorEBO.Unbind();

	// Inside VAO, VBO, EBO
	VAO insideVAO;
	insideVAO.Bind();

	VBO insideVBO(insideVertices, sizeof(insideVertices));
	EBO insideEBO(insideIndices, sizeof(insideIndices));
	insideVAO.LinkAttrib(insideVBO, 0, 2, GL_FLOAT, 7 * sizeof(float), (void*)0);
	insideVAO.LinkAttrib(insideVBO, 1, 3, GL_FLOAT, 7 * sizeof(float), (void*)(2 * sizeof(float)));
	insideVAO.LinkAttrib(insideVBO, 2, 2, GL_FLOAT, 7 * sizeof(float), (void*)(5 * sizeof(float)));
	insideVAO.Unbind();
	insideVBO.Unbind();
	insideEBO.Unbind();


	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
	GLuint doorOpenFactorLocation = glGetUniformLocation(doorShader.ID, "doorOpenFactor");


	// Texture
	
	Texture microwave("microwave.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	microwave.texUnit(shaderProgram, "tex0", 0);

	Texture plate("plate.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	plate.texUnit(shaderProgram, "tex1", 1);

	Texture food("food.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	food.texUnit(shaderProgram, "tex2", 2);

	Texture lamp("lamp.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	lamp.texUnit(shaderProgram, "tex3", 3);

	Texture door("door.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	door.texUnit(shaderProgram, "tex4", 4);

	Texture inside("inside.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	inside.texUnit(shaderProgram, "tex5", 5);

	glfwSetCursorPosCallback(window, mouseCallback);


	static float doorOpenFactor = 0.0f;
	// Main while loop
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();

		glUniform1f(uniID, 0.5f);

		// Draw Microwave (bind the microwave texture)
		microwave.Bind();
		microwaveVAO.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// Draw Inside (bind the inside texture)
		inside.Bind();
		insideVAO.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// Draw Plate (bind the plate texture)
		plate.Bind();
		plateVAO.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// Draw Food (bind the food texture)
		food.Bind();
		foodVAO.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		// Draw Lamp (bind the lamp texture)
		lamp.Bind();
		lampVAO.Bind();
		glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(circle) / (2 * sizeof(float)));


		doorShader.Activate();

		doorOpenFactor = doorOpeningAndClosing(window, doorOpenFactor);

		glUniform1f(doorOpenFactorLocation, doorOpenFactor);
		// Draw Door (bind the door texture)
		door.Bind();
		doorVAO.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);



		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	microwaveVAO.Delete();
	microwaveVBO.Delete();
	microwaveEBO.Delete();
	plateVAO.Delete();
	plateVBO.Delete();
	plateEBO.Delete();
	foodVAO.Delete();
	foodVBO.Delete();
	foodEBO.Delete();
	lampVAO.Delete();
	lampVBO.Delete();
	doorVAO.Delete();
	doorVBO.Delete();
	doorEBO.Delete();
	microwave.Delete();
	plate.Delete();
	food.Delete();
	lamp.Delete();
	door.Delete();
	shaderProgram.Delete();
	doorShader.Delete();


	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void generateCircleVertices(float circle[], int numSegments, float centerX, float centerY, float r) {
	circle[0] = centerX;  // Center X
	circle[1] = centerY;  // Center Y

	for (int i = 0; i <= numSegments; i++) {
		float angle = (i * 360.0f / numSegments) * (3.141592 / 180); // Convert to radians
		circle[2 + 2 * i] = centerX + r * cos(angle);       // Xi = centerX + r * cos(angle)
		circle[2 + 2 * i + 1] = centerY + r * sin(angle);   // Yi = centerY + r * sin(angle)
	}
}

float doorOpeningAndClosing(GLFWwindow* window, float doorOpenFactor) {
	// 0 = closed, 1 = opening, 2 = open, 3 = closing
	static int doorState = 0;  // True when opening, false when closing

	static float doorAnimationTime = 0.0f;  // Time for smooth animation

	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS && doorState == 0) {
		doorState = 1;
		doorAnimationTime = 0.0f;  // Reset animation time when opening starts
	}
	else if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS && doorState == 2) {
		doorState = 3;
		doorAnimationTime = 0.0f;  // Reset animation time when opening starts
	}

	if (doorState == 1) {
		doorAnimationTime += 0.01f;
		doorOpenFactor = doorAnimationTime;

		if (doorOpenFactor >= 1.0f) {
			doorOpenFactor = 1.0f;
			doorState = 2;
		}
	}
	else if (doorState == 3) {
		doorAnimationTime += 0.01f;
		doorOpenFactor = 1.0f - doorAnimationTime;

		if (doorOpenFactor <= 0.0f) {
			doorOpenFactor = 0.0f;
			doorState = 0;
		}
	}

	return doorOpenFactor;
}