#pragma once

typedef unsigned int GLuint;
typedef int GLint;
typedef int GLsizei;
typedef float GLfloat;

class AMesh
{
public:
	AMesh();
	~AMesh();

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

