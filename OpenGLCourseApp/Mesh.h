#pragma once

#include <GL/glew.h>

class Mesh
{
public:
	Mesh();
	~Mesh();

	void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void RenderMesh();
	void ClearMesh();

	inline GLuint GetVAO() { return VAO; }
	inline GLuint GetVBO() { return VBO; }
	inline GLuint GetIBO() { return IBO; }
	inline GLsizei GetIndexCount() { return indexCount;  }

private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;

};

