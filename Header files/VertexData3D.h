#pragma once

#define GLEW_STATIC // to mark that we use static library

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class VertexData3D
{
public:
	GLuint EBO = 0, VBO = 0, VAO = 0;

	GLfloat *vertices;
	GLuint numberOfVertices;
	GLuint numberOfVerticesx3;

	GLuint *indices;
	GLuint numberOfIndices;	
	GLuint numberOfIndicesx3;

public:
	VertexData3D(const char* vertexPath, const char* fragmentPath);
	~VertexData3D();

	void draw(bool unbind = true);
};

