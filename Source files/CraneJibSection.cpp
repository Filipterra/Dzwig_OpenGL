
#include "CraneJibSection.h"

float CraneJibSection::linePartCounter = 0.0;
CraneJibSection::CraneJibSection(GLfloat height, unsigned int numberOfParts, const char* vertexPath, const char* fragmentPath, const char* colorFragmentPath, const char* verticesPartPath,
	const char* indicesPartPath, const char* verticesWheelPath, const char* indicesWheelPath, const char* verticesRailPath, const char* indicesRailPath,const char* verticesLinePartPath, const char* verticesLineEndPath, const char* indicesLineEndPath)
	:railPart(new CraneJibSectionRail*[numberOfParts]),linePart(new CraneJibSectionPart*[height*2]),numberOfRailParts(numberOfParts),lineLength((height - 1.0f)*2)
{

	for (unsigned int i = 0; i < NUMBEROFJIBPARTS; ++i)
		part[i] = new CraneJibSectionPart(vertexPath, colorFragmentPath, verticesPartPath, indicesPartPath, glm::vec4(1.0f, 0.5f, 0.2f, 1.0f));
	
	for (int i = 0; i < NUMBEROFJIBTOPWHEELS; ++i)
		topWheel[i] = new CraneJibSectionWheel(vertexPath, fragmentPath, verticesWheelPath, indicesWheelPath);

	for (int i = 0; i < NUMBEROFJIBBOTTOMWHEELS; ++i)
		bottomWheel[i] = new CraneJibSectionWheel(vertexPath, fragmentPath, verticesWheelPath, indicesWheelPath);

	float nextx = 1.0f;
	for (unsigned int i = 0; i < numberOfParts; ++i) {
		railPart[i] = new CraneJibSectionRail(vertexPath, fragmentPath, verticesRailPath, indicesRailPath);
		railPart[i]->trans.move(nextx++, height + 0.25f, 0.0f);
	}
	for (unsigned int i = 0; i <NUMBEROFLINEPARTS-1; ++i)
		linePart[i] = new CraneJibSectionPart(vertexPath, colorFragmentPath, verticesLinePartPath, indicesPartPath, glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

	linePart[NUMBEROFLINEPARTS - 1] = new CraneJibSectionPart(vertexPath, colorFragmentPath, verticesLineEndPath, indicesLineEndPath, glm::vec4(1.92f, 1.92f, 1.92f, 1.0f));

	part[0]->trans.scale(2.0f, 1.0f, 0.5f);
	part[0]->trans.move(0.0f, height + 0.24f - 0.05f, 0.05f);
	part[1]->trans.scale(2.0f, 1.0f, 0.5f);
	part[1]->trans.move(0.0f, height + 0.24f - 0.05f, -0.05f);
	int i = 2;
	for (int j = i; i < NUMBEROFJIBPARTS - 4; ++i)
	{
		part[i]->trans.rotate(glm::radians(90.0f), 0.0f, 1.0f, 0.0f);

		if (j == i)	part[i]->trans.scale(2.0f, 1.0f, 1.0f);
		if (j == i)part[i]->trans.move(-1.05f, height + 0.25f - 0.05f, 0.7f);
		if (j + 1 == i)part[i]->trans.scale(2.0f, 1.0f, 1.0f);
		if (j + 1 == i)part[i]->trans.move(-1.05f, height + 0.25f - 0.05f, 1.4f);
	}

	for (int j = i; j < NUMBEROFJIBPARTS; ++j)
	{
		part[j]->trans.rotate(glm::radians(90.0f), 0.0f, 0.0f, 1.0f);
		part[j]->trans.scale(0.5f, 1.0f, 1.0f);
		if (j == i)part[j]->trans.move(height, -0.65f, 0.30f);
		if (j == i + 1)part[j]->trans.move(height, -0.65f, -0.30f);
		if (j == i + 2)part[j]->trans.move(height, -1.35f, 0.30f);
		if (j == i + 3)part[j]->trans.move(height, -1.35f, -0.30f);
	}


	topWheel[0]->trans.move(0.7f + 0.00625f, height + 0.24f + 0.07f, 0.2f);
	topWheel[0]->setPosition(0.7f + 0.00625f, height + 0.24f + 0.07f,0.2f);
	topWheel[1]->trans.move(1.4f + 0.00625f, height + 0.24f + 0.07f, 0.2f);
	topWheel[2]->trans.move(0.7f + 0.00625f, height + 0.24f + 0.07f, -0.25f);
	topWheel[3]->trans.move(1.4f + 0.00625f, height + 0.24f + 0.07f, -0.25f);

	bottomWheel[0]->trans.scale(1.5f, 1.5f, 1.0f);
	bottomWheel[1]->trans.scale(1.5f, 1.5f, 1.0f);
	bottomWheel[0]->trans.move(0.90f, height + 0.1f, -0.025f);
	bottomWheel[1]->trans.move(1.20f, height + 0.1f, -0.025f);

	
	linePart[0]->trans.rotate(glm::radians(30.0f), 0.0f, 0.0f, 1.0f);
	linePart[1]->trans.rotate(glm::radians(-30.0f), 0.0f, 0.0f, 1.0f);
	linePart[0]->trans.move(3.225f, height - 1.5f, -0.025f);
	linePart[1]->trans.move(-1.429f, height - 0.45f, -0.025f);

	linePart[2]->trans.basicRotate(glm::radians(180.0f), 0.0f, 0.0f, 1.0f);
	linePart[2]->trans.move(0.015f, 0.5f, 0.0f);
	linePart[2]->trans.scale(1.0f, lineLength, 1.0f);
	linePart[2]->trans.move(1.039f, height - 0.35f - 0.5f, -0.025f);
	linePart[3]->trans.move(1.039f, 1.0f - 0.345f, -0.025f);
	//linePart[3]->trans.scale(4.0f, 4.0f, 4.0f);
	//float nextLinePartmove = 0.5;
	/*
	for (unsigned int i = 2; i < NUMBEROFLINEPARTS; ++i)
	{
		if (i == 2)
		{
			linePart[i]->trans.basicRotate(glm::radians(180.0f), 0.0f, 0.0f, 1.0f);
			linePart[i]->trans.move(0.015f, 0.5f, 0.0f);
			linePart[i]->trans.scale(1.0f, lineLength, 1.0f);
		}
		linePart[i]->trans.move(1.039f, height - 0.35f- nextLinePartmove, -0.025f);
		nextLinePartmove += 0.5;
	}
	*/
}


CraneJibSection::~CraneJibSection()
{
	for (unsigned int i = 0; i < NUMBEROFJIBPARTS; ++i) delete part[i];
	for (int i = 0; i < NUMBEROFJIBBOTTOMWHEELS; ++i)delete bottomWheel[i];
	for (int i = 0; i < NUMBEROFJIBTOPWHEELS; ++i)delete topWheel[i];
	for (unsigned int i = 0; i < numberOfRailParts; ++i) delete railPart[i];
	for (unsigned int i = 0; i < NUMBEROFLINEPARTS; ++i) delete linePart[i];
	//delete[] bottomWheel;
	//delete[] part;
//	delete[] topWheel;
	delete[] linePart;
	delete[] railPart;
}


void CraneJibSection::render(glm::mat4 view, float zoom)
{
	for (unsigned int i = 0; i < NUMBEROFJIBPARTS; ++i)
	{
		if (i >= NUMBEROFJIBPARTS - 4)part[i]->render(view, zoom);
		else
		{
			part[i]->render(view, zoom);
		}
	}
	for (unsigned int i = 0; i < NUMBEROFLINEPARTS; ++i)
	{
	if(i==0)linePart[i]->render(view, zoom);
	else if(i==1)linePart[i]->render(view, zoom);
	else	linePart[i]->render(view, zoom);
	}
	for (unsigned int i = 0; i < numberOfRailParts; ++i) railPart[i]->render(view, zoom);
	for (int i = 0; i < NUMBEROFJIBBOTTOMWHEELS; ++i)bottomWheel[i]->render(view, zoom);
	for (int i = 0; i < NUMBEROFJIBTOPWHEELS; ++i)topWheel[i]->render(view, zoom);
}

void CraneJibSection::rotate(float angle)
{
	for (unsigned int i = 0; i < NUMBEROFJIBPARTS; ++i)
	{
		if (i >= NUMBEROFJIBPARTS - 4)part[i]->rotate(angle, 1.0f, 0.0f, 0.0f);
		else
		{
			part[i]->rotate(angle, 0.0f, 1.0f, 0.0f);
		}
	}
	for (unsigned int i = 0; i < NUMBEROFLINEPARTS; ++i)
	{
		if (i == 0)linePart[i]->rotate(angle, 0.35f, 0.605f, 0.0f);
		else if (i == 1)linePart[i]->rotate(angle, -0.35f, 0.605f, 0.0f);
		else	linePart[i]->rotate(angle, 0.0f, 1.0f, 0.0f);
	}
	for (unsigned int i = 0; i < numberOfRailParts; ++i) railPart[i]->rotate(angle);
	for (int i = 0; i < NUMBEROFJIBBOTTOMWHEELS; ++i)bottomWheel[i]->rotate(angle);
	for (int i = 0; i < NUMBEROFJIBTOPWHEELS; ++i)topWheel[i]->rotate(angle);
}

void CraneJibSection::moveJibHorizontally(float movement)
{
	for (unsigned int i = 0; i < NUMBEROFJIBPARTS; ++i)
	{
		if(i==0 || i==1)part[i]->trans.move(movement, 0.0, 0.0);
		else if (i >= NUMBEROFJIBPARTS - 4)part[i]->trans.move(0.0,-movement,0.0);
		else
		{
			part[i]->trans.move(0.0, 0.0, movement);
		}
	}
	for (unsigned int i = 0; i <NUMBEROFLINEPARTS; ++i)
	{
		if (i == 0)linePart[i]->trans.move(1.43f*0.605f*movement,1.43f*(-0.35f)*movement, 0.0);
		else if (i == 1)linePart[i]->trans.move(1.43f*0.605f*movement, 1.43f*(0.35f)*movement, 0.0);
		else	linePart[i]->trans.move(movement, 0.0, 0.0);
	}
	for (int i = 0; i < NUMBEROFJIBBOTTOMWHEELS; ++i)bottomWheel[i]->trans.move(movement, 0.0, 0.0);
	for (int i = 0; i < NUMBEROFJIBTOPWHEELS; ++i)
	{	
		if(movement < 0.0f)topWheel[i]->trans.basicRotate(glm::radians(0.9f), 0.0f, 0.0f, 1.0f);
		if (movement > 0.0f)topWheel[i]->trans.basicRotate(glm::radians(0.9f), 0.0f, 0.0f, -1.0f);	
		topWheel[i]->trans.move(movement, 0.0, 0.0);
	}

}
void CraneJibSection::moveJibVertically(float movement)
{
	if ( movement == 0)return;
	for (int i = 0; i < NUMBEROFJIBBOTTOMWHEELS; ++i)
	{
		if (movement < 0.0f &&  linePartCounter>0.0f)
		{
			if(i%2==0)bottomWheel[i]->trans.basicRotate(glm::radians(0.9f), 0.0f, 0.0f, 1.0f);
			else  bottomWheel[i]->trans.basicRotate(glm::radians(0.9f), 0.0f, 0.0f, -1.0f);
		}
		else if (movement > 0.0f && linePartCounter < lineLength)
		{
			if (i % 2 == 1)bottomWheel[i]->trans.basicRotate(glm::radians(0.9f), 0.0f, 0.0f, 1.0f);
			else bottomWheel[i]->trans.basicRotate(glm::radians(0.9f), 0.0f, 0.0f, -1.0f);
		
		}
	}
	
	linePartCounter += movement;
	if (movement > 0.0f && lineLength!=linePartCounter)
	{			
			if (linePartCounter > lineLength)linePartCounter = lineLength; 
			if (linePartCounter < lineLength) linePart[3]->trans.move(0.0f, 4 * movement / lineLength, 0.0f);
	}
	else if (movement < 0.0f && linePartCounter!=0)
	{		
			if (linePartCounter < 0.0f) linePartCounter = 0.0f;
			if (linePartCounter > 0.0f) linePart[3]->trans.move(0.0f, 4 * movement / lineLength, 0.0f);			
	}
	linePart[2]->trans.resetScale();
	linePart[2]->trans.scale(1.0f, lineLength - linePartCounter, 1.0f);
}