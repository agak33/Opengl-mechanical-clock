#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include <glm/gtc/matrix_transform.hpp>
#include <glew/include/GL/glew.h>
#include <glm/glm.hpp>

#include "lodepng.h"

/*
* Abstract class to define a 3D object.
*/
class Model
{
private:
	static GLuint readTexture(const char* filename);
public:
	int vertexCount;	// amount of vertex in vertex_position attribute
	glm::mat4 M;		// model matrix
	GLuint tex;			// handle to texture file
	GLuint spec;		// handle to specular file

	std::vector<glm::vec4> vertex_positions;	// positions of vertex
	std::vector<glm::vec2> vertex_texcoords;	// positions of vertex on the texture file
	std::vector<glm::vec4> vertex_normals;		// normal vectors
	glm::vec3 origin;							// model origin

	Model();
	Model(const std::string& object_file, const std::string& texture_file,
		  const std::string& specular_file, const glm::vec3& origin = glm::vec3(0.0f));

	~Model();

	virtual void update(const float& time) = 0 {}
};

