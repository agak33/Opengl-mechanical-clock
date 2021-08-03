﻿#include "shaderprogram.h"
#include <iostream>

char* ShaderProgram::readFile(const char* fileName) {
	int filesize;
	FILE* plik;
	char* result;

	#pragma warning(suppress : 4996)
	plik = fopen(fileName, "rb");
	if (plik != NULL) {
		fseek(plik, 0, SEEK_END);
		filesize = ftell(plik);
		fseek(plik, 0, SEEK_SET);
		result = new char[filesize + 1];
		#pragma warning(suppress : 6386)
		int readsize = fread(result, 1, filesize, plik);
		result[filesize] = 0;
		fclose(plik);

		return result;
	}
	return NULL;
}

/**
* @param shaderType: GL_VERTEX_SHADER, GL_GEOMETRY_SHADER or GL_FRAGMENT_SHADER
*/
GLuint ShaderProgram::loadShader(GLenum shaderType, const char* fileName) {
	GLuint shader = glCreateShader(shaderType);
	const GLchar* shaderSource = readFile(fileName);
	glShaderSource(shader, 1, &shaderSource, NULL);

	// Compiling
	glCompileShader(shader);
	delete []shaderSource;

	// Get the compilation error log and display it
	int infologLength = 0;
	int charsWritten  = 0;
	char *infoLog;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH,&infologLength);

	if (infologLength > 1) {
		infoLog = new char[infologLength];
		glGetShaderInfoLog(shader, infologLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
		delete []infoLog;
	}
	return shader;
}

ShaderProgram::ShaderProgram(const char* vertexShaderFile,const char* geometryShaderFile,const char* fragmentShaderFile) {
	printf("Loading vertex shader...\n");
	vertexShader = loadShader(GL_VERTEX_SHADER, vertexShaderFile);

	// Load geometry shader
	if (geometryShaderFile != NULL) {
		printf("Loading geometry shader...\n");
		geometryShader = loadShader(GL_GEOMETRY_SHADER, geometryShaderFile);
	} else {
		geometryShader = 0;
	}

	// Load fragment shader
	printf("Loading fragment shader...\n");
	fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentShaderFile);

	// Generate shader program handle
	shaderProgram = glCreateProgram();

	// Attach shaders, link program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	if (geometryShaderFile != NULL) glAttachShader(shaderProgram, geometryShader);
	glLinkProgram(shaderProgram);

	// Get the linking error log and distplay it
	int infologLength = 0;
	int charsWritten  = 0;
	char* infoLog;

	glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH,&infologLength);

	if (infologLength > 1)
	{
		infoLog = new char[infologLength];
		glGetProgramInfoLog(shaderProgram, infologLength, &charsWritten, infoLog);
		printf("%s\n", infoLog);
		delete[] infoLog;
	}

	printf("Shader program created \n");
}

ShaderProgram::~ShaderProgram() {
	// Detach shaders
	glDetachShader(shaderProgram, vertexShader);
	if (geometryShader != 0) glDetachShader(shaderProgram, geometryShader);
	glDetachShader(shaderProgram, fragmentShader);

	// Delete shaders
	glDeleteShader(vertexShader);
	if (geometryShader != 0) glDeleteShader(geometryShader);
	glDeleteShader(fragmentShader);

	// Delete program
	glDeleteProgram(shaderProgram);
}

void ShaderProgram::use() {
	glUseProgram(shaderProgram);
}

GLuint ShaderProgram::u(const char* variableName) {
	return glGetUniformLocation(shaderProgram,variableName);
}

GLuint ShaderProgram::a(const char* variableName) {
	return glGetAttribLocation(shaderProgram,variableName);
}
