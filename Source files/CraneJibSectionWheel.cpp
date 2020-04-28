#include "CraneJibSectionWheel.h"



CraneJibSectionWheel::CraneJibSectionWheel(const char* vertexPath, const char* fragmentPath, const char* verticesPath, const char* indicesPath)
	:shader(vertexPath, fragmentPath), vertices(verticesPath, indicesPath), trans(shader)
{
	trans.perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
}

void CraneJibSectionWheel::render(glm::mat4 view, float zoom)
{

	shader.use();
	trans.perspective(glm::radians(zoom), (float)800 / (float)600, 0.1f, 100.0f);
	trans.setView(view);
	trans.runAll();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	vertices.draw(true);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void CraneJibSectionWheel::rotate(float angle)
{
	trans.rotateAndRun(glm::radians(angle), 0.0f, 1.0f, 0.0f);
}

void CraneJibSectionWheel::setPosition(float xPos, float yPos,float zPos)
{
	x = xPos;
	y = yPos;
	z = zPos;
}

float CraneJibSectionWheel::getX()
{
	return x;
}

float CraneJibSectionWheel::getY()
{
	return y;
}
float CraneJibSectionWheel::getZ()
{
	return z;
}