#pragma once

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>

// 
class Mesh : protected QOpenGLFunctions
{
public:
	Mesh();

	void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numVertices, unsigned int numOfIndices);
	void RenderMesh();
	void ClearMesh();

private:
	unsigned int m_indexCount;
	// The different buffer holding the mesh data
	// Destruction of data in the openGL server is handled by their destructor
	QOpenGLVertexArrayObject* m_vao = nullptr;
	QOpenGLBuffer* m_vbo, *m_ibo = nullptr;

	GLfloat* vertices = nullptr;
};