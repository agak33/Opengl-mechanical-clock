#pragma once
#define SHADERPROGRAM_H
#include <GL/glew.h>

/*
* Class to create an object that defines a shader program.
*/

class ShaderProgram {
private:
	// attributes
	GLuint shaderProgram;					// Handle to shader program
	GLuint vertexShader;					// Handle to vertex shader
	GLuint geometryShader;					// Handle to geometry shader
	GLuint fragmentShader;					// Handle to fragment shader

	// methods
	char* readFile(const char* fileName);	// Reads file into a char array
	GLuint loadShader(GLenum shaderType,	// Loads and compiles shader, returns handle to it
					  const char* fileName);
public:
	ShaderProgram(const char* vertexShaderFile, 
				  const char* geometryShaderFile, 
				  const char* fragmentShaderFile);
	~ShaderProgram();

	void use();							// Enables the use of a shader
	GLuint u(const char* variableName); // Gets the slot number associated with given homogeneous variable name
	GLuint a(const char* variableName); // Gets the slot number associated with given attribute name
};
