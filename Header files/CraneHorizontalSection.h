#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CraneHorizontalSectionPart.h"
#include "CraneHorizontalSectionBase.h"


class CraneHorizontalSection
{
	CraneHorizontalSectionBase counterweight; //przeciwwaga dzwigu
	CraneHorizontalSectionPart atachment; //czesc miedzy srodkiem a przeciwwaga
	CraneHorizontalSectionBase base; //podstawa ramienia
	CraneHorizontalSectionBase cabin; //kabina operatora
	CraneHorizontalSectionPart **part; //tablica segmentow ramienia
	CraneHorizontalSectionPart middlePart; //czesc ramienia nad pionem
	CraneHorizontalSectionPart end; //zakonczenie ramienia
	unsigned int numberOfParts;

public:
	CraneHorizontalSection(float height, unsigned int numberOfParts,
		const char* vertexPath, const char* fragmentPath, const char* colorFragmentPath, const char* partVerticesPath, const char* partIndicesPath,
		const char* baseVerticesPath, const char* baseIndicesPath, const char* endVerticesPath, const char* endIndicesPath,
		const char* midVerticesPath, const char* midIndicesPath, const char* cabinVerticesPath, const char* cabinIndicesPath,
		const char* atachVerticesPath, const char* atachIndicesPath, const char* weightVerticesPath, const char* weightIndicesPath);
	~CraneHorizontalSection();

	unsigned int partsNumber();

	void render(glm::mat4 view, float zoom);
	void rotate(float angle);
};