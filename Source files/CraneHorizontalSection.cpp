#include "CraneHorizontalSection.h"

CraneHorizontalSection::CraneHorizontalSection(float height, unsigned int numberOfParts, const char* vertexPath, const char* fragmentPath, const char* colorFragmentPath,
	const char* partVerticesPath, const char* partIndicesPath, const char* baseVerticesPath, const char* baseIndicesPath, const char* endVerticesPath, const char* endIndicesPath,
	const char* midVerticesPath, const char* midIndicesPath, const char* cabinVerticesPath, const char* cabinIndicesPath, const char* atachVerticesPath, const char* atachIndicesPath,
	const char* weightVerticesPath, const char* weightIndicesPath):part(new CraneHorizontalSectionPart*[numberOfParts]),
	numberOfParts(numberOfParts), base(vertexPath, colorFragmentPath, baseVerticesPath, baseIndicesPath, glm::vec4(1.0f, 0.5f, 0.2f, 1.0f)),
	end(vertexPath, fragmentPath, endVerticesPath, endIndicesPath), middlePart(vertexPath, fragmentPath, midVerticesPath, midIndicesPath),
	cabin(vertexPath, colorFragmentPath, cabinVerticesPath, cabinIndicesPath, glm::vec4(0.76f, 0.76f, 0.76f, 1.0f)), atachment(vertexPath, fragmentPath, atachVerticesPath, atachIndicesPath),
	counterweight(vertexPath, colorFragmentPath, weightVerticesPath, weightIndicesPath, glm::vec4(0.76f, 0.76f, 0.76f, 1.0f))
{
	counterweight.trans.move(-1.5f, height, 0.0f);
	atachment.trans.move(-1.0f, height + 0.25f, 0.0f);
	base.trans.move(0.0f, height, 0.0f);
	cabin.trans.move(0.0f, height, -1.0f);
	GLfloat nextx = 1.0f;
	for (unsigned int i = 0; i < numberOfParts; ++i) {
		part[i] = new CraneHorizontalSectionPart(vertexPath, fragmentPath, partVerticesPath, partIndicesPath);
		part[i]->trans.move(nextx++, height + 0.25f, 0.0f);
	}
	end.trans.move(nextx, height + 0.25f, 0.0f);
	middlePart.trans.move(0.0f, height + 0.25f, 0.0f);
}

CraneHorizontalSection::~CraneHorizontalSection()
{
	for (unsigned int i = 0; i < numberOfParts; ++i) delete part[i];
	delete[] part;
}


void CraneHorizontalSection::render(glm::mat4 view, float zoom)
{
	counterweight.render(view, zoom);
	atachment.render(view, zoom);
	base.render(view, zoom);
	cabin.render(view, zoom);
	middlePart.render(view, zoom);
	for (unsigned int i = 0; i < numberOfParts; ++i) part[i]->render(view, zoom);
	end.render(view, zoom);
}

unsigned int CraneHorizontalSection::partsNumber() { return numberOfParts; }

void CraneHorizontalSection::rotate(float angle)
{
	counterweight.rotate(angle);
	atachment.rotate(angle);
	base.rotate(angle);
	cabin.rotate(angle);
	middlePart.rotate(angle);
	for (unsigned int i = 0; i < numberOfParts; ++i) part[i]->rotate(angle);
	end.rotate(angle);
}