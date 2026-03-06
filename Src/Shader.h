#pragma once
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

class Shader : public QOpenGLShaderProgram
{
public:
	explicit Shader(QObject* parent = nullptr);

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);
	void CompileProgram();

	// Getter for uniform variable
	GLuint GetUniformModel() { return m_uniModel; }
	GLuint GetUniformView() { return m_uniView; }
	GLuint GetUniformProjection() { return m_uniProjection; }


private:
	QString ReadFile(const char* fileLocation);
	void CompileShader(const char* vertexCode, const char* fragmentCode);
	GLuint m_uniModel, m_uniView, m_uniProjection = 0;
	bool success;
};