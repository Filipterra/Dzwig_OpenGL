#include "CraneVerticalSection.h"

CraneVerticalSection::CraneVerticalSection(unsigned int numberOfParts, const char* vertexPath, const char* fragmentPath, const char* verticesPath, const char* indicesPath)
	:part(new CraneVerticalSectionPart*[numberOfParts]), numberOfParts(numberOfParts)
{
	GLfloat nexty = 1.0f;
	for (unsigned int i = 0; i < numberOfParts; ++i) {
		part[i] = new CraneVerticalSectionPart(vertexPath, fragmentPath, verticesPath, indicesPath);

		if(i != 0) part[i]->trans.move(0.0f, nexty++, 0.0f);
	}
}

CraneVerticalSection::~CraneVerticalSection()
{
	for (unsigned int i = 0; i < numberOfParts; ++i) delete part[i];
	delete[] part;
}


void CraneVerticalSection::render(glm::mat4 view, float zoom)
{
	for (unsigned int i = 0; i < numberOfParts; ++i) part[i]->render(view, zoom);
}

unsigned int CraneVerticalSection::partsNumber() {
	return numberOfParts;
}