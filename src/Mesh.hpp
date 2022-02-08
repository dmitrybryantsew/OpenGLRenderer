#pragma once
#include "stdafx.hpp"
#include <GL/glew.h>


class Mesh
{
public:
	Mesh();
	void CreateMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void RenderMesh();
	~Mesh();
private:
	GLuint VAO, VBO, IBO, indexCount;
};