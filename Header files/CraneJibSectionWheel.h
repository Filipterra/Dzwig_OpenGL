#pragma once

#define GLEW_STATIC // to mark that we use static library
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "VertexData3D.h"
#include "Transform.h"
class CraneJibSectionWheel
{
	Shader shader;
	VertexData3D vertices;
	float x, y,z;
public:
	Transform trans;
	CraneJibSectionWheel(const char* vertexPath, const char* fragmentPath, const char* verticesPath, const char* indicesPath);

	void render(glm::mat4 view, float zoom);
	void rotate(float angle);
	void setPosition(float xPos,float yPos,float zPos);
	float getX();
	float getY();
	float getZ();
};
