#pragma once
#define GLEW_STATIC // to mark that we use static library
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "CraneVerticalSection.h"
#include "CraneHorizontalSection.h"
#include "CraneJibSection.h"

class GLFWWindow
{
	CraneVerticalSection* sectionVertical;
	CraneHorizontalSection* sectionHorizontal;
	CraneJibSection *sectionJib;

	GLuint WIDTH = 800;
	GLuint HEIGHT = 600;
	GLuint numberOfVerticalParts = 5;
	GLuint numberOfHorizontalParts = 5;

	const char* windowName = "Crane project";

	//Crane movement variable
	static float jibHorizontalPosition;

	// timing
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	GLFWwindow* window;
	float lastX = WIDTH / 2.0f;
	float lastY = HEIGHT / 2.0f;
	bool firstMouse = true;
	
	bool initAndCreateWindow();
	void windowHints();
public:
	GLFWWindow();
	~GLFWWindow();
	bool mainLoop();

	GLuint getWidth();
	GLuint getHeight();
	void rotate(float angle);
	void moveJibHorizontally(float movement);
	void moveJibVertically(float movement);
	void processInput(GLFWwindow* window);
	void mouse_callback(GLFWwindow* window);
};

