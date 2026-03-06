#include "Shader.h"
#include <iostream>
#include <fstream>

Shader::Shader(QObject* parent)
	: QOpenGLShaderProgram(parent)
{
	m_uniModel = 0;
	m_uniView = 0;
	m_uniProjection = 0;
}

void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode)
{
	CompileShader(vertexCode, fragmentCode);
}


void Shader::CreateFromFiles(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	QString vertexString = ReadFile(vertexShaderPath);
	QString fragmentString = ReadFile(fragmentShaderPath);

	CompileShader(qPrintable(vertexString), qPrintable(fragmentString));
}

void Shader::CompileShader(const char* vertexCode, const char* fragmentCode)
{
	success = addShaderFromSourceCode(QOpenGLShader::Vertex, vertexCode);
	if (!success)
	{
		std::cout << "Couldn't add vertex shader!" << qPrintable(log()) << std::endl;
	}
	success = addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentCode);
	if (!success)
	{
		std::cout << "Couldn't add fragment shader!" << qPrintable(log()) << std::endl;
	}

	CompileProgram();
}

void Shader::CompileProgram()
{
	bindAttributeLocation("posAttr", 0);
	bindAttributeLocation("colAttr", 1);
	
	success = link();
	if (!success)
	{
		std::cout << "Error while linking shader program! " << qPrintable(log()) << std::endl;
	}
	success = bind();
	if (!success)
	{
		printf("Error while binding shader program!");
	}

	// Get location/id of shaders uniform variable 
	m_uniModel = uniformLocation("model");
	m_uniView  = uniformLocation("view");
	m_uniProjection = uniformLocation("projection");
}

QString Shader::ReadFile(const char* fileLocation)
{
	QString content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open())
	{
		qDebug() << "Failed to read " << fileLocation << "! File doesn't exist.";
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}