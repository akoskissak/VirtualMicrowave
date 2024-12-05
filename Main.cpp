#include "main.h"
#include <ft2build.h>


#include FT_FREETYPE_H

using namespace irrklang;

int windowWidth = 1800;
int windowHeight = 900;

float plateAspect = 1280.0f / 640.0f;
float foodAspect = 531.0f / 400.0f;

float scale = 1.8f;
// proporcijski odnosi
float microwaveWidth = 0.81625f * scale;
float microwaveHeight = 0.83556f * scale;

float plateWidth = microwaveWidth * 0.4f;
float plateHeight = plateWidth / plateAspect;

float foodWidth = plateWidth * 0.8f;
float foodHeight = foodWidth / foodAspect;

// Microwave rectangle vertices
GLfloat microwaveVertices[] = {
	// X                           Y            U     V
	-microwaveWidth / 2, -microwaveHeight / 2, 0.0f, 0.0f,
	-microwaveWidth / 2,  microwaveHeight / 2, 0.0f, 1.0f,
	 microwaveWidth / 2,  microwaveHeight / 2, 1.0f, 1.0f,
	 microwaveWidth / 2, -microwaveHeight / 2, 1.0f, 0.0f
};

// Plate rectangle vertices
GLfloat plateVertices[] = {
	// X                           Y                   U     V
	-plateWidth / 2 - .15f, -plateHeight / 2 - 0.25f, 0.0f, 0.0f,
	-plateWidth / 2 - .15f,  plateHeight / 2 - 0.25f, 0.0f, 1.0f,
	 plateWidth / 2 - .15f,  plateHeight / 2 - 0.25f, 1.0f, 1.0f,
	 plateWidth / 2 - .15f, -plateHeight / 2 - 0.25f, 1.0f, 0.0f
};

// Food rectangle vertices
GLfloat foodVertices[] = {
	// X                           Y                 U     V
	-foodWidth / 2 - .18f, -foodHeight / 2 - 0.18f, 0.0f, 0.0f,
	-foodWidth / 2 - .18f,  foodHeight / 2 - 0.18f, 0.0f, 1.0f,
	 foodWidth / 2 - .18f,  foodHeight / 2 - 0.18f, 1.0f, 1.0f,
	 foodWidth / 2 - .18f, -foodHeight / 2 - 0.18f, 1.0f, 0.0f
};

float doorWidth = microwaveWidth;
float doorHeight = microwaveHeight;

// Microwave Door vertices
GLfloat doorVertices[] = {
	// X                     Y         U     V
	-doorWidth / 2 + 0.0005f, -doorHeight / 2,  0.0f, 0.0f,
	-doorWidth / 2 + 0.0005f,  doorHeight / 2,  0.0f, 1.0f,
	 doorWidth / 2 + 0.0005f,  doorHeight / 2,  1.0f, 1.0f,
	 doorWidth / 2 + 0.0005f, -doorHeight / 2,  1.0f, 0.0f
};

float insideWidth = doorWidth;
float insideHeight = doorHeight;

// Microwave Inside vertices
GLfloat insideVertices[] = {
	// X                      Y            U     V
	-insideWidth / 2, -insideHeight / 2, 0.0f, 0.0f,
	-insideWidth / 2,  insideHeight / 2, 0.0f, 1.0f,
	 insideWidth / 2,  insideHeight / 2, 1.0f, 1.0f,
	 insideWidth / 2, -insideHeight / 2, 1.0f, 0.0f
};

// Glass vertices
GLfloat glassVertices[] = {
	// X						       Y		
	-doorWidth / 3 - 0.15f, -doorHeight / 3 + 0.1f,
	-doorWidth / 3 - 0.15f,  doorHeight / 3 + 0.1f,
	 doorWidth / 3 - 0.15f,  doorHeight / 3 + 0.1f,
	 doorWidth / 3 - 0.15f, -doorHeight / 3 + 0.1f
};

GLfloat backgroundVertices[] = {
	// X     Y      U     V
	-1.0f, -1.0f, 0.0f, 0.0f,
	-1.0f,  1.0f, 0.0f, 1.0f,
	 1.0f,  1.0f, 1.0f, 1.0f,
	 1.0f, -1.0f, 1.0f, 0.0f
};

GLfloat blackbackgroundVertices[] = {
	// X     Y   
	-1.0f, -1.0f,
	-1.0f,  1.0f,
	 1.0f,  1.0f,
	 1.0f, -1.0f,
};

GLuint indices[] = {
	0, 1, 2, 0, 2, 3
};

MousePosition mousePos = { 0.0f, 0.0f };

void mouseCallback(GLFWwindow* window, double mouseX, double mouseY) {
	// konvertovanje u normalizovane koordinate
	mousePos.x = (2.0f * mouseX) / windowWidth - 1.0f;
	mousePos.y = 1.0f - (2.0f * mouseY) / windowHeight;

	//std::cout << "Mouse X: " << mousePos.x << ", Mouse Y: " << mousePos.y << std::endl;
}

int main() {
	if (!glfwInit()) // !0 == 1; glfwInit inicijalizuje GLFW i vrati 1 ako je inicijalizovana uspjesno, a 0 ako nije
	{
		std::cout << "GLFW Biblioteka se nije ucitala! :(\n";
		return 1;
	}

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);

	// centar monitora
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


	ISoundEngine* soundEngine = irrklang::createIrrKlangDevice();
	if (!soundEngine) {
		std::cerr << "Could not initialize sound engine" << std::endl;
		return -1;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	const int numSegments = 50;
	float r = 0.05f;
	float centerX = -0.38f;
	float centerY = 0.3f;

	float ri = 0.03f;
	float centerXi = 0.63f;
	float centerYi = -0.3f;

	float lamp[(numSegments + 2) * 2];
	float indic[(numSegments + 2) * 2];
	generateCircleVertices(lamp, numSegments, centerX, centerY, r);
	generateCircleVertices(indic, numSegments, centerXi, centerYi, ri);

	Shader shaderProgram("default.vert", "default.frag");
	Shader doorShader("door.vert", "door.frag");
	Shader indicatorShader("indicator.vert", "indicator.frag");
	Shader glassShader("glass.vert", "glass.frag");
	Shader textShader("text.vert", "text.frag");
	Shader smokeShader("smoke.vert", "smoke.frag");
	Shader blackShader("black.vert", "black.frag");

	VAO microwaveVAO;
	microwaveVAO.Bind();

	EBO sharedEBO(indices, sizeof(indices));
	sharedEBO.Bind();

	VBO microwaveVBO(microwaveVertices, sizeof(microwaveVertices));
	microwaveVAO.LinkAttrib(microwaveVBO, 0, 2, GL_FLOAT, 4 * sizeof(float), (void*)0);
	microwaveVAO.LinkAttrib(microwaveVBO, 1, 2, GL_FLOAT, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	microwaveVAO.Unbind();
	microwaveVBO.Unbind();

	VAO plateVAO;
	plateVAO.Bind();

	sharedEBO.Bind();

	VBO plateVBO(plateVertices, sizeof(plateVertices));
	plateVAO.LinkAttrib(plateVBO, 0, 2, GL_FLOAT, 4 * sizeof(float), (void*)0);
	plateVAO.LinkAttrib(plateVBO, 1, 2, GL_FLOAT, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	plateVAO.Unbind();
	plateVBO.Unbind();

	VAO foodVAO;
	foodVAO.Bind();

	sharedEBO.Bind();

	VBO foodVBO(foodVertices, sizeof(foodVertices));
	foodVAO.LinkAttrib(foodVBO, 0, 2, GL_FLOAT, 4 * sizeof(float), (void*)0);
	foodVAO.LinkAttrib(foodVBO, 1, 2, GL_FLOAT, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	foodVAO.Unbind();
	foodVBO.Unbind();

	VAO lampVAO;
	lampVAO.Bind();

	VBO lampVBO(lamp, sizeof(lamp));
	lampVAO.LinkAttrib(lampVBO, 0, 2, GL_FLOAT, 2 * sizeof(float), (void*)0);
	lampVAO.Unbind();
	lampVBO.Unbind();

	VAO doorVAO;
	doorVAO.Bind();

	sharedEBO.Bind();

	VBO doorVBO(doorVertices, sizeof(doorVertices));
	doorVAO.LinkAttrib(doorVBO, 0, 2, GL_FLOAT, 4 * sizeof(float), (void*)0);
	doorVAO.LinkAttrib(doorVBO, 1, 2, GL_FLOAT, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	doorVAO.Unbind();
	doorVBO.Unbind();

	VAO insideVAO;
	insideVAO.Bind();

	sharedEBO.Bind();

	VBO insideVBO(insideVertices, sizeof(insideVertices));
	insideVAO.LinkAttrib(insideVBO, 0, 2, GL_FLOAT, 4 * sizeof(float), (void*)0);
	insideVAO.LinkAttrib(insideVBO, 1, 2, GL_FLOAT, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	insideVAO.Unbind();
	insideVBO.Unbind();

	VAO indicatorVAO;
	indicatorVAO.Bind();

	VBO indicatorVBO(indic, sizeof(indic));
	indicatorVAO.LinkAttrib(indicatorVBO, 0, 2, GL_FLOAT, 2 * sizeof(float), (void*)0);
	indicatorVAO.Unbind();
	indicatorVBO.Unbind();

	VAO glassVAO;
	glassVAO.Bind();

	sharedEBO.Bind();

	VBO glassVBO(glassVertices, sizeof(glassVertices));
	glassVAO.LinkAttrib(glassVBO, 0, 2, GL_FLOAT, 2 * sizeof(float), (void*)0);
	glassVAO.Unbind();
	glassVBO.Unbind();

	VAO backgroundVAO;
	backgroundVAO.Bind();

	sharedEBO.Bind();

	VBO backgroundVBO(backgroundVertices, sizeof(backgroundVertices));
	backgroundVAO.LinkAttrib(backgroundVBO, 0, 2, GL_FLOAT, 4 * sizeof(float), (void*)0);
	backgroundVAO.LinkAttrib(backgroundVBO, 1, 2, GL_FLOAT, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	backgroundVAO.Unbind();
	backgroundVBO.Unbind();


	VAO textVAO;
	textVAO.Bind();

	VBO textVBO(sizeof(float) * 6 * 4);
	textVAO.LinkAttrib(textVBO, 0, 4, GL_FLOAT, 4 * sizeof(float), (void*)0);
	textVAO.Unbind();
	textVBO.Unbind();

	VAO smokeVAO;
	smokeVAO.Bind();

	sharedEBO.Bind();
	VBO smokeVBO(backgroundVertices, sizeof(backgroundVertices));
	smokeVAO.LinkAttrib(smokeVBO, 0, 2, GL_FLOAT, 4 * sizeof(float), (void*)0);
	smokeVAO.LinkAttrib(smokeVBO, 1, 2, GL_FLOAT, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	smokeVAO.Unbind();
	smokeVBO.Unbind();

	VAO blackVAO;
	blackVAO.Bind();


	sharedEBO.Bind();

	VBO blackVBO(blackbackgroundVertices, sizeof(blackbackgroundVertices));
	blackVAO.LinkAttrib(blackVBO, 0, 2, GL_FLOAT, 2 * sizeof(float), (void*)0);
	blackVAO.Unbind();
	blackVBO.Unbind();
	sharedEBO.Unbind();

	GLuint doorOpenFactorLocation = glGetUniformLocation(doorShader.ID, "doorOpenFactor");
	GLuint indicatorTimeLoc = glGetUniformLocation(indicatorShader.ID, "time");
	GLboolean isGlassOnLoc = glGetUniformLocation(glassShader.ID, "isGlassOn");
	GLfloat smokeScaleLoc = glGetUniformLocation(smokeShader.ID, "scale");
	GLfloat smokeOpacityLoc = glGetUniformLocation(smokeShader.ID, "opacity");
	GLfloat lightIntensityLoc = glGetUniformLocation(blackShader.ID, "lightning");

	// Texture
	Texture background("background.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	background.texUnit(shaderProgram, "tex0", 0);

	Texture microwave("microwave.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	Texture plate("plate.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	Texture plateCook("plateCook.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	Texture food("food.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	Texture foodCook("foodCook.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	Texture lampOn("lamp.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	Texture lampOff("lampoff.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	Texture door("door.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	door.texUnit(doorShader, "tex0", 0);

	Texture inside("inside.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	Texture insideOn("insideOn.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

	Texture smoke("smoke1.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	smoke.texUnit(smokeShader, "tex0", 0);


	Text textRenderer("fonts/digital-7.ttf", &textShader, windowWidth, windowHeight);
	Text index("fonts/digital-7.ttf", &textShader, windowWidth, windowHeight);

	glfwSetCursorPosCallback(window, mouseCallback);

	MicrowaveState microwaveState = MicrowaveState::Idle;

	MicrowaveState previousState = MicrowaveState::Idle;

	static float doorOpenFactor = 0.0f;
	DoorState doorState = DoorState::Closed;
	static float doorAnimationTime = 0.0f;


	const double TARGET_FPS = 60.0;
	const double TARGET_FRAME_TIME = 1.0 / TARGET_FPS;

	double lastFrameTime = 0.0;
	double currentFrameTime = 0.0;
	double deltaTime = 0.0;

	float indicatorTime = 0.0f;

	static bool wasGlassOn = true;
	static bool isGlassOn = true;

	// Pokvarenje mikrotalasne
	static bool wasXKeyPressed = false;
	float light_intensity = 0.0f;
	static bool isMicrowaveBroken = false;

	static bool wasSKeyPressed = false;
	static bool repairMicrowave = false;
	float smoke_scale = 0.7f;   // Početna skala
	float smoke_opacity = 0.0f; // Početna opacitet

	std::string timer = "00:00";
	float lastTime = 0.0f;


	while (!glfwWindowShouldClose(window)) {

		currentFrameTime = glfwGetTime();
		deltaTime = currentFrameTime - lastFrameTime;

		if (deltaTime >= TARGET_FRAME_TIME) {

			lastFrameTime = currentFrameTime;

			glClear(GL_COLOR_BUFFER_BIT);

			// Provera da li je stanje mikrotalasne promenjeno
			if (microwaveState != previousState) {
				if (microwaveState == MicrowaveState::Cooking) {
					soundEngine->play2D("media/cooking.wav", true);
				}
				else if (microwaveState == MicrowaveState::Finished) {
					soundEngine->stopAllSounds();
					soundEngine->play2D("media/bell.wav", false);
				}
				else if (previousState == MicrowaveState::Error) {
					smoke_scale = 0.7f;
					smoke_opacity = 0.0f;
				}
				else {
					soundEngine->stopAllSounds();
				}
				previousState = microwaveState;
			}


			shaderProgram.Activate();

			// Draw Background
			background.Bind();
			backgroundVAO.Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

			// Renderovanje dima
			if (isMicrowaveBroken) {
				smokeShader.Activate();
				glUniform1f(smokeScaleLoc, smoke_scale);
				glUniform1f(smokeOpacityLoc, smoke_opacity);
				smoke.Bind();
				smokeVAO.Bind();
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
			}
			shaderProgram.Activate();
			// Draw Microwave
			microwave.Bind();
			microwaveVAO.Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

			// Draw Inside
			updateTexture(microwaveState, insideOn, inside);
			insideVAO.Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

			// Draw Plate
			updateTexture(microwaveState, plateCook, plate);
			plateVAO.Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

			// Draw Food
			updateTexture(microwaveState, foodCook, food);
			foodVAO.Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

			// Draw Lamp
			updateTexture(microwaveState, lampOn, lampOff);
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

			// Draw Door
			doorShader.Activate();

			doorClick(window, doorState, doorAnimationTime, microwaveState, soundEngine);
			doorOpenFactor = doorOpeningAndClosing(window, doorOpenFactor, doorState, doorAnimationTime, microwaveState, soundEngine);

			glUniform1f(doorOpenFactorLocation, doorOpenFactor);
			door.Bind();
			doorVAO.Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
			
			indicatorShader.Activate();
			glUniform1f(indicatorTimeLoc, indicatorTime);
			if (microwaveState == MicrowaveState::Cooking)
				indicatorTime += 0.1f;
			else if (microwaveState == MicrowaveState::Finished)
				indicatorTime = -1.0f;
			else
				indicatorTime = 1.0f;
			indicatorVAO.Bind();
			glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(indic) / (2 * sizeof(float)));


			if (microwaveState == MicrowaveState::Cooking) {
				if (currentFrameTime - lastTime >= 1.0f) {
					if (updateTimer(timer)) {	// kraj
						microwaveState = MicrowaveState::Finished;
					}
					lastTime = currentFrameTime;
				}
			}
			checkButtonClick(window, microwaveState, doorState, timer);

			int pressedNumber = numClick(window, soundEngine);
			if (pressedNumber != -1 && (microwaveState == MicrowaveState::Finished || microwaveState ==  MicrowaveState::Idle || microwaveState == MicrowaveState::Paused)) {
				updateTimer(timer, pressedNumber);
			}

			textRenderer.RenderText(timer, 1360.0f, 200.0f, 1.2f, 0.5f, 0.7f, 1.0f);

			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
				index.RenderText("Kiss Akos RA11 2021", 20.0f, 820.0f, 1.0f, 0.0f, 0.1f, 0.1f);

			// detektovanje da li je pritisnut taster X
			bool isXKeyPressed = glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS;
			if (isXKeyPressed && !wasXKeyPressed) {
				isMicrowaveBroken = true;
				// da ne bi mogli da klikcemo x i da se cuje boom
				if (microwaveState != MicrowaveState::Error) {
					soundEngine->play2D("media/boom.wav", false);
				}
			}
			wasXKeyPressed = isXKeyPressed;

			// detektovanje da li je pritisnut taster S
			bool isSKeyPressed = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
			if (isSKeyPressed && !wasSKeyPressed) {
				if(microwaveState == MicrowaveState::Error)
					repairMicrowave = true;
			}
			wasSKeyPressed = isSKeyPressed;

			if (repairMicrowave) {
				if (light_intensity >= 0.0f) {
					light_intensity -= 0.006f;
				}
				else
				{
					isMicrowaveBroken = false;
					microwaveState = MicrowaveState::Idle;
					repairMicrowave = false;
					timer = "00:00";
				}
			}
			else if (isMicrowaveBroken) {
				if (light_intensity < 0.8f) {
					light_intensity += 0.006f;
				}
				if (light_intensity > 0.79f) {
					microwaveState = MicrowaveState::Error;
				}
			}


			float error_flash = sin(glfwGetTime() * 5.0f); // Treperi sa periodom 0.2s
			if (error_flash > 0.0f && microwaveState == MicrowaveState::Error) {
				timer = "";
				textRenderer.RenderText("ERROR", 1360.0f, 200.0f, 1.2f, 0.5f, 0.7f, 1.0f); // Prikazivanje treperenja
			}

			/////////////
			blackShader.Activate();
			glUniform1f(lightIntensityLoc, light_intensity);


			blackVAO.Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

			if (repairMicrowave) {
				if (smoke_scale > 0.7f)
					smoke_scale -= 0.002f; // Smanji dim
				if (smoke_opacity > 0.0f)
					smoke_opacity -= 0.01f;
			}
			else if (isMicrowaveBroken) {
				if(smoke_scale < 1.4f)
					smoke_scale += 0.002f; // Povećavaj dim
				if (smoke_opacity < 1.0f) {
					smoke_opacity += 0.01f; // Smanji opacitet dima
				}
			}

			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(window, true);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		else {
			glfwWaitEventsTimeout(TARGET_FRAME_TIME - deltaTime);
		}
	}

	soundEngine->drop();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void generateCircleVertices(float circle[], int numSegments, float centerX, float centerY, float r) {
	circle[0] = centerX;
	circle[1] = centerY;

	for (int i = 0; i <= numSegments; i++) {
		float angle = (i * 360.0f / numSegments) * (3.141592 / 180); // Konvertovanje u radijan
		circle[2 + 2 * i] = centerX + r * cos(angle);
		circle[2 + 2 * i + 1] = centerY + r * sin(angle);
	}
}

void updateTexture(MicrowaveState state, Texture& on, Texture& off) {
	if (state == MicrowaveState::Cooking) {
		on.Bind();
	}
	else {
		off.Bind();
	}
}

void updateTimer(std::string& timer, int number) {
	if (number >= 0 && number <= 9) {
		timer[0] = timer[1];
		timer[1] = timer[3];
		timer[3] = timer[4];
		timer[4] = '0' + number;
	}
}

// Function to decrease the timer
bool updateTimer(std::string& timer) {
	// Convert string "MM:SS" to minutes and seconds
	int minutes = std::stoi(timer.substr(0, 2));
	int seconds = std::stoi(timer.substr(3, 2));

	// Decrease the time
	if (seconds > 0) {
		seconds--;
	}
	else if (minutes > 0) {
		minutes--;
		seconds = 59;
	}

	// Format the updated time back to "MM:SS"
	timer = (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);
	if (timer == "00:00")
		return true;
	return false;
}

// Function to render the time in 00:00 format
std::string formatTime(int remainingSeconds) {
	int minutes = remainingSeconds / 60;
	int seconds = remainingSeconds % 60;
	return (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);
}