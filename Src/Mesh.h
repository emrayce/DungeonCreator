#pragma once

#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>
#include <QQuaternion>

// 
class Mesh : protected QOpenGLFunctions
{
public:
	Mesh();

	void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numVertices, unsigned int numOfIndices);
	void RenderMesh();
	void ClearMesh();

	QMatrix4x4 GetModelMatrice();
	void SetModelMatrice(const QMatrix4x4 matrice);
	void Translate(const QVector3D vec);
	void Rotate(const QQuaternion quaternion);

private:
	unsigned int m_indexCount;
	// The different buffer holding the mesh data
	// Destruction of data in the openGL server is handled by their destructor
	QOpenGLVertexArrayObject* m_vao = nullptr;
	QOpenGLBuffer* m_vbo = nullptr, *m_ibo = nullptr;
	QMatrix4x4 m_model;

	GLfloat* vertices = nullptr;
};