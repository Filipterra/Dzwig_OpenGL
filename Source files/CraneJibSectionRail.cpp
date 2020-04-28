#include "CraneJibSectionRail.h"

CraneJibSectionRail::CraneJibSectionRail(const char* vertexPath, const char* fragmentPath, const char* verticesPath, const char* indicesPath)
	:shader(vertexPath, fragmentPath), vertices(verticesPath, indicesPath), trans(shader)
{
	trans.translate(0.0f, -3.7f, -10.0f);
	trans.perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
}

void CraneJibSectionRail::render(glm::mat4 view, float zoom)
{
	shader.use();
	trans.perspective(glm::radians(zoom), (float)800 / (float)600, 0.1f, 100.0f);
	trans.setView(view);
	trans.runAll();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	vertices.draw(true);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void CraneJibSectionRail::rotate(float angle)
{
	trans.rotateAndRun(glm::radians(angle), 0.0f, 1.0f, 0.0f);
}