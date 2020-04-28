#include "CraneHorizontalSectionBase.h"

CraneHorizontalSectionBase::CraneHorizontalSectionBase(const char* vertexPath, const char* fragmentPath, const char* verticesPath, const char* indicesPath, glm::vec4 color)
	:shader(vertexPath, fragmentPath), vertices(verticesPath, indicesPath), trans(shader), color(color)
{
	trans.perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
}

CraneHorizontalSectionBase::~CraneHorizontalSectionBase() {}

void CraneHorizontalSectionBase::render(glm::mat4 view, float zoom)
{
	shader.use();
	shader.setVec4("color", color);
	trans.perspective(glm::radians(zoom), (float)800 / (float)600, 0.1f, 100.0f);
	trans.setView(view);
	trans.runAll();
	vertices.draw(true);
}

void CraneHorizontalSectionBase::rotate(float angle)
{
	trans.rotateAndRun(glm::radians(angle), 0.0f, 1.0f, 0.0f);
}

