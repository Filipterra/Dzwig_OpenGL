#include "VertexData3D.h"

VertexData3D::VertexData3D(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode;
	std::string indicesCode;
	std::ifstream vShaderFile;
	std::ifstream iShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	iShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexPath);
		iShaderFile.open(fragmentPath);
		std::stringstream vStream, iStream;
		// read file's buffer contents into streams
		vStream << vShaderFile.rdbuf();
		iStream << iShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		iShaderFile.close();

		vStream >> numberOfVertices;
		iStream >> numberOfIndices;

		numberOfVerticesx3 = numberOfVertices * 3;
		numberOfIndicesx3 = numberOfIndices * 3;

		vertices = new GLfloat[numberOfVerticesx3];
		indices = new GLuint[numberOfIndicesx3];

#ifdef _DEBUG
		unsigned int v3 = 0, i3 = 0;
		std::cout << "Vertices (" << vertexPath << "):" << std::endl;
#endif

		for (GLuint i = 0; i < numberOfVerticesx3; ++i) {
			vStream >> vertices[i];
#ifdef _DEBUG
			std::cout << vertices[i] << " ";
			if (++v3 % 3 == 0) std::cout << std::endl;
#endif
		}

#ifdef _DEBUG
		std::cout << "Indices (" << fragmentPath << "):" << std::endl;
#endif

		for (GLuint i = 0; i < numberOfIndicesx3; ++i) {
			iStream >> indices[i];
#ifdef _DEBUG
			std::cout << indices[i] << " ";
			if (++i3 % 3 == 0) std::cout << std::endl;
#endif
		}
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::VERTICES::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
		// Bind
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numberOfVerticesx3, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * numberOfIndicesx3, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
		// Unbind
	glBindVertexArray(0);
}

VertexData3D::~VertexData3D()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void VertexData3D::draw(bool unbind)
{	
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, numberOfIndicesx3, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	if(unbind) glBindVertexArray(0);
}
