#include "Mesh.h"

Mesh::Mesh()
{
	m_indexCount = 0;
}

void Mesh::CreateMesh(GLfloat* vertices, unsigned int* indices, unsigned int numVertices, unsigned int numOfIndices)
{
	m_indexCount = numOfIndices;
	m_vao = new QOpenGLVertexArrayObject();
	m_vao->create();
	m_vao->bind();

	m_ibo = new QOpenGLBuffer(QOpenGLBuffer::Type::IndexBuffer);
	m_ibo->create();
	m_ibo->bind();
	m_ibo->allocate(indices, sizeof(indices[0]) * numOfIndices);

	m_vbo = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
	m_vbo->create();
	m_vbo->bind();
	m_vbo->allocate(vertices, sizeof(vertices[0]) * numVertices);

	// Enable and fill the array holding vertices data
	// TODO this seems to annoy QMatrix4x4 projection;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);
	// Enable and fill the array holding the color data
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));

	m_vao->release();
}

void Mesh::RenderMesh()
{
	m_vao->bind();
	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr);
	m_vao->release();
}

void Mesh::ClearMesh()
{
}
