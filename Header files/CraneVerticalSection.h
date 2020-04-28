#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CraneVerticalSectionPart.h"

class CraneVerticalSection
{
	CraneVerticalSectionPart **part;
	unsigned int numberOfParts;

public:
	CraneVerticalSection(unsigned int numberOfParts, \
		const char* vertexPath, const char* fragmentPath, const char* verticesPath, const char* indicesPath);
	~CraneVerticalSection();

	unsigned int partsNumber();

	void render(glm::mat4 view, float zoom);
};

