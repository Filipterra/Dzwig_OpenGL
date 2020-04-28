#include "CraneHorizontalSectionPart.h"

CraneHorizontalSectionPart::CraneHorizontalSectionPart(const char* vertexPath, const char* fragmentPath, const char* verticesPath, const char* indicesPath)
	:shader(vertexPath, fragmentPath), vertices(verticesPath, indicesPath), trans(shader)
{
	trans.perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
}

CraneHorizontalSectionPart::~CraneHorizontalSectionPart() {}

void CraneHorizontalSectionPart::render(glm::mat4 view, float zoom)
{
	shader.use();
	trans.runAll();
	trans.perspective(glm::radians(zoom), (float)800 / (float)600, 0.1f, 100.0f);
	trans.setView(view);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	vertices.draw(true);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void CraneHorizontalSectionPart::rotate(float angle)
{
	trans.rotateAndRun(glm::radians(angle), 0.0f, 1.0f, 0.0f);
}