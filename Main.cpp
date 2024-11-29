#include "main.h"

int windowWidth = 1800;  // Width of your window
int windowHeight = 900; // Height of your window

float microwaveAspect = 653.0f / 376.0f;
float plateAspect = 1280.0f / 640.0f;
float foodAspect = 531.0f / 400.0f;

float scale = 1.8f;
float microwaveWidth = 0.81625f * scale;
float microwaveHeight = 0.83556f * scale;

float plateWidth = microwaveWidth * 0.4f;
float plateHeight = plateWidth / plateAspect;

float foodWidth = plateWidth * 0.8f;
float foodHeight = foodWidth / foodAspect;

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

GLfloat glassVertices[] = {
	// X						Y					 R		G     B     U     V
	-doorWidth / 3 - 0.15f, -doorHeight / 3 + 0.1f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // Bottom-left
	-doorWidth / 3 - 0.15f,  doorHeight / 3 + 0.1f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // Top-left
	 doorWidth / 3 - 0.15f,  doorHeight / 3 + 0.1f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // Top-right
	 doorWidth / 3 - 0.15f, -doorHeight / 3 + 0.1f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f  // Bottom-right
};

GLfloat backgroundVertices[] = {
	// X    Y      R     G     B     U     V
	-1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // Bottom-left
	-1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // Top-left
	 1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // Top-right
	 1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f // Bottom-right
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

GLuint glassIndices[] = {
	0, 1, 2, 0, 2, 3   // Glass
};

GLuint backgroundIndices[] = {
	0, 1, 2, 0, 2, 3   // Background
};

MousePosition mousePos = { 0.0f, 0.0f };

// Mouse callback function
void mouseCallback(GLFWwindow* window, double mouseX, double mouseY) {
	// Convert to normalized device coordinates (NDC)
	mousePos.x = (2.0f * mouseX) / windowWidth - 1.0f;
	mousePos.y = 1.0f - (2.0f * mouseY) / windowHeight;

	// Print the normalized coordinates
	std::cout << "Mouse X: " << mousePos.x << ", Mouse Y: " << mousePos.y << std::endl;
}

int main() {
	const int numSegments = 50;  // Number of segments (e.g., 50)
	float r = 0.1f;              // Radius of the circle
	float centerX = -0.38f;      // Center X0
	float centerY = 0.3f;        // Center Y0

	float ri = 0.03f;
	float centerXi = 0.63f;
	float centerYi = -0.3f;

	float lamp[(numSegments + 2) * 2];  // Total points: center + perimeter
	float indic[(numSegments + 2) * 2]; // Total points: center + perimeter
	generateCircleVertices(lamp, numSegments, centerX, centerY, r);
	generateCircleVertices(indic, numSegments, centerXi, centerYi, ri);

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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader shaderProgram("default.vert", "default.frag");
	Shader doorShader("door.vert", "door.frag");
	Shader indicatorShader("indicator.vert", "indicator.frag");
	Shader glassShader("glass.vert", "glass.frag");

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

	VBO lampVBO(lamp, sizeof(lamp));
	lampVAO.LinkAttrib(lampVBO, 0, 2, GL_FLOAT, 2 * sizeof(float), (void*)0);
	lampVAO.Unbind();
	lampVBO.Unbind();

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

	// Indicator VAO, VBO
	VAO indicatorVAO;
	indicatorVAO.Bind();

	VBO indicatorVBO(indic, sizeof(indic));
	indicatorVAO.LinkAttrib(indicatorVBO, 0, 2, GL_FLOAT, 2 * sizeof(float), (void*)0);
	indicatorVAO.Unbind();
	indicatorVBO.Unbind();

	VAO glassVAO;
	glassVAO.Bind();

	VBO glassVBO(glassVertices, sizeof(glassVertices));
	EBO glassEBO(glassIndices, sizeof(glassIndices));
	glassVAO.LinkAttrib(glassVBO, 0, 2, GL_FLOAT, 7 * sizeof(float), (void*)0);
	glassVAO.Unbind();
	glassVBO.Unbind();
	glassEBO.Unbind();

	VAO backgroundVAO;
	backgroundVAO.Bind();

	VBO backgroundVBO(backgroundVertices, sizeof(backgroundVertices));
	EBO backgroundEBO(backgroundIndices, sizeof(backgroundIndices));
	backgroundVAO.LinkAttrib(backgroundVBO, 0, 2, GL_FLOAT, 7 * sizeof(float), (void*)0);
	backgroundVAO.LinkAttrib(backgroundVBO, 1, 3, GL_FLOAT, 7 * sizeof(float), (void*)(2 * sizeof(float)));
	backgroundVAO.LinkAttrib(backgroundVBO, 2, 2, GL_FLOAT, 7 * sizeof(float), (void*)(5 * sizeof(float)));
	backgroundVAO.Unbind();
	backgroundVBO.Unbind();
	backgroundEBO.Unbind();


	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
	GLuint doorOpenFactorLocation = glGetUniformLocation(doorShader.ID, "doorOpenFactor");
	GLuint indicatorTimeLoc = glGetUniformLocation(indicatorShader.ID, "time");
	GLboolean isGlassOnLoc = glGetUniformLocation(glassShader.ID, "isGlassOn");

	// Texture
	
	Texture microwave("microwave.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	microwave.texUnit(shaderProgram, "tex0", 0);

	Texture plate("plate.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	plate.texUnit(shaderProgram, "tex1", 1);

	Texture food("food.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	food.texUnit(shaderProgram, "tex2", 2);

	Texture lampOn("lamp.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	lampOn.texUnit(shaderProgram, "tex3", 3);

	Texture lampOff("lampoff.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	lampOff.texUnit(shaderProgram, "tex3", 3);

	Texture door("door.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	door.texUnit(shaderProgram, "tex4", 4);

	Texture inside("inside.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	inside.texUnit(shaderProgram, "tex5", 5);

	Texture background("background.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	background.texUnit(shaderProgram, "tex6", 6);


	glfwSetCursorPosCallback(window, mouseCallback);

	MicrowaveState microwaveState = MicrowaveState::Idle;

	static float doorOpenFactor = 0.0f;
	DoorState doorState = DoorState::Closed;
	static float doorAnimationTime = 0.0f;

	// Variables to control frame rate
	const double TARGET_FPS = 60.0;
	const double TARGET_FRAME_TIME = 1.0 / TARGET_FPS;  // ~16.67 ms per frame

	double lastFrameTime = 0.0;  // Store the time of the last frame
	double currentFrameTime = 0.0;
	double deltaTime = 0.0;  // Store the time difference between frames

	float indicatorTime = 0.0f;

	static bool wasGlassOn = true;
	static bool isGlassOn = true;
	// Main while loop
	while (!glfwWindowShouldClose(window)) {
		// Get the current time
		currentFrameTime = glfwGetTime();
		deltaTime = currentFrameTime - lastFrameTime;
		// If enough time has passed to render a new frame
		if (deltaTime >= TARGET_FRAME_TIME) {
			// Update the last frame time
			lastFrameTime = currentFrameTime;


			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			
			shaderProgram.Activate();

			numClick(window);
			checkButtonClick(window, microwaveState, doorState);
			
			glUniform1f(uniID, 0.5f);

			background.Bind();
			backgroundVAO.Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
			
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

			updateLampTexture(microwaveState, lampOn, lampOff);
			lampVAO.Bind();
			glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(lamp) / (2 * sizeof(float)));

			glassShader.Activate();

			bool isGKeyPressed = glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS;
			if (isGKeyPressed && !wasGlassOn) {
				isGlassOn = !isGlassOn;
			}
			glUniform1i(isGlassOnLoc, isGlassOn ? 1 : 0);
			wasGlassOn = isGKeyPressed;

			glassVAO.Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

			// Draw Door (bind the door texture)
			doorShader.Activate();

			doorClick(window, doorState, doorAnimationTime, microwaveState);
			doorOpenFactor = doorOpeningAndClosing(window, doorOpenFactor, doorState, doorAnimationTime, microwaveState);

			glUniform1f(doorOpenFactorLocation, doorOpenFactor);
			door.Bind();
			doorVAO.Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
			
			indicatorShader.Activate();
			glUniform1f(indicatorTimeLoc, indicatorTime);
			if (microwaveState == MicrowaveState::Cooking)
				indicatorTime += 0.1f;
			else
				indicatorTime = 1.0f;
			indicatorVAO.Bind();
			glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(indic) / (2 * sizeof(float)));

			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(window, true);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		else {
			glfwWaitEventsTimeout(TARGET_FRAME_TIME - deltaTime);
		}

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
	insideVAO.Delete();
	insideVBO.Delete();
	glassVAO.Delete();
	glassVBO.Delete();
	glassEBO.Delete();
	backgroundVAO.Delete();
	backgroundVBO.Delete();
	backgroundEBO.Delete();
	microwave.Delete();
	plate.Delete();
	food.Delete();
	lampOn.Delete();
	lampOff.Delete();
	door.Delete();
	shaderProgram.Delete();
	doorShader.Delete();
	indicatorShader.Delete();
	glassShader.Delete();

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


void updateLampTexture(MicrowaveState state, Texture& lampOn, Texture& lampOff) {
	if (state == MicrowaveState::Cooking) {
		lampOn.Bind();
	}
	else {
		lampOff.Bind();
	}
}

