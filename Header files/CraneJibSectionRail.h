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

class CraneJibSectionRail
{

		Shader shader;
		VertexData3D vertices;

	public:
		Transform trans;

		CraneJibSectionRail(const char* vertexPath, const char* fragmentPath, const char* verticesPath, const char* indicesPath);

		void render(glm::mat4 view, float zoom);
		void rotate(float angle);	
};

