#include "GLFWWindow.h"

float GLFWWindow::jibHorizontalPosition = 0.0f;
Camera camera = Camera();

void GLFWWindow::windowHints() {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_FOCUSED, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // without deprecated functions
	glfwWindowHint(GLFW_SAMPLES, 4);
}

GLFWWindow::GLFWWindow()
{
	if (initAndCreateWindow()) throw "Window cannot be initialized.";
	
	sectionVertical = new CraneVerticalSection(numberOfVerticalParts, 
		"Shaders\\ShaderVertexHorizontal.txt", "Shaders\\SimpleShaderFragment.txt", "Vertices\\VerticalCranePartVert.txt", "Indices\\VerticalCranePartInd.txt");
	sectionHorizontal = new CraneHorizontalSection(sectionVertical->partsNumber(), numberOfHorizontalParts, "Shaders\\ShaderVertexHorizontal.txt",
		"Shaders\\SimpleShaderFragment.txt", "Shaders\\ColorShaderFragment.txt", "Vertices\\HorizontalCranePartVert.txt", "Indices\\HorizontalCranePartInd.txt",
		"Vertices\\HorizontalCraneBaseVert.txt", "Indices\\HorizontalCraneBaseInd.txt", "Vertices\\HorizontalCraneEndVert.txt", "Indices\\HorizontalCraneEndInd.txt",
		"Vertices\\HorizontalCraneMidVert.txt", "Indices\\HorizontalCraneMidInd.txt", "Vertices\\HorizontalCraneCabinVert.txt", "Indices\\HorizontalCraneCabinInd.txt",
		"Vertices\\HorizontalCraneAtachVert.txt", "Indices\\HorizontalCraneAtachInd.txt", "Vertices\\HorizontalCraneWeightVert.txt", "Indices\\HorizontalCraneWeightInd.txt");
	sectionJib = new CraneJibSection(GLfloat(sectionVertical->partsNumber()), numberOfHorizontalParts,"Shaders\\ShaderVertexHorizontal.txt", "Shaders\\SimpleShaderFragment.txt",
		"Shaders\\ColorShaderFragment.txt","Vertices\\JibCranePartVert.txt", "Indices\\JibCranePartInd.txt","Vertices\\JibCraneWheelVert.txt","Indices\\JibCraneWheelInd.txt",
		"Vertices\\JibCraneRailVert.txt","Indices\\JibCraneRailInd.txt","Vertices\\JibCraneLinePartVert.txt","Vertices\\JibCraneLineEndVert.txt","Indices\\JibCraneLineEndInd.txt");
}
GLFWWindow::~GLFWWindow()
{
	delete sectionVertical;
	delete sectionHorizontal;
	delete sectionJib;
	glfwTerminate();
}

void GLFWWindow::processInput(GLFWwindow* window)
{
	float rotationSpeed = 10.0f;
	float jibHorizonstalSpeed = 1.0f;
	float jibVerticalSpeed = 3.5f;

	if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)	glfwSetWindowShouldClose(window, GL_TRUE);

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) rotate(rotationSpeed * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) rotate(-rotationSpeed * deltaTime);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) moveJibHorizontally(jibHorizonstalSpeed * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) moveJibHorizontally(-jibHorizonstalSpeed * deltaTime);
		
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) moveJibVertically(jibVerticalSpeed * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) moveJibVertically(-jibVerticalSpeed * deltaTime);
	

	if (glfwGetKey(window, GLFW_KEY_UP)) camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_DOWN)) camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_RIGHT)) camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT)) camera.ProcessKeyboard(LEFT, deltaTime);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) { camera.ProcessMouseScroll(yoffset);
std::cout << camera.getZoom() << std::endl;
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

bool GLFWWindow::mainLoop() {
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		processInput(window);
		mouse_callback(window);

		// Clear the colorbuffer
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		sectionVertical->render(camera.getViewMatrix(), camera.getZoom());
		sectionHorizontal->render(camera.getViewMatrix(), camera.getZoom());
		sectionJib->render(camera.getViewMatrix(), camera.getZoom());
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	return false;
}

bool GLFWWindow::initAndCreateWindow() {
	if (glfwInit() != GL_TRUE)
	{
		std::cout << "GLFW initialization failed" << std::endl;
		return true;
	}

	windowHints();

	glEnable(GL_MULTISAMPLE);
	window = glfwCreateWindow(WIDTH, HEIGHT, windowName, nullptr, nullptr);
	if (window == nullptr) return true;

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	//glew
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) return true;
	glViewport(0, 0, WIDTH, HEIGHT);

	glEnable(GL_DEPTH_TEST);

	return false;
}

GLuint GLFWWindow::getWidth(){	return WIDTH;}

GLuint GLFWWindow::getHeight(){	return HEIGHT;}

void GLFWWindow::rotate(float angle)
{
	sectionHorizontal->rotate(angle);
	sectionJib->rotate(angle);
}

void GLFWWindow::moveJibHorizontally(float movement)
{
	if (jibHorizontalPosition + movement<0.0f || jibHorizontalPosition + movement>float(numberOfHorizontalParts) - 1.1f || movement==0)return;
	sectionJib->moveJibHorizontally(movement);
	jibHorizontalPosition += movement;
}

void GLFWWindow::moveJibVertically(float movement){	sectionJib->moveJibVertically(movement);}

void GLFWWindow::mouse_callback(GLFWwindow* window)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	camera.ProcessMouseMovement(xoffset, yoffset);
}