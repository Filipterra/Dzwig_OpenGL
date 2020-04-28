#include "CraneJibSectionPart.h"

CraneJibSectionPart::CraneJibSectionPart(const char* vertexPath, const char* fragmentPath, const char* verticesPath, const char* indicesPath, glm::vec4 color)
	:shader(vertexPath, fragmentPath), vertices(verticesPath, indicesPath), trans(shader), color(color)
{
	trans.perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
}

void CraneJibSectionPart::render(glm::mat4 view, float zoom)
{
	shader.use();
	trans.perspective(glm::radians(zoom), (float)800 / (float)600, 0.1f, 100.0f);
	trans.setView(view);
	trans.runAll();
	shader.setVec4("color", color);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	vertices.draw(true);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void CraneJibSectionPart::rotate(float angle, float x, float y, float z)
{
	trans.rotateAndRun(glm::radians(angle), x, y, z);
}