#include "model.h"

Model::Model() {
	this->vertexCount = 0;
	this->M = glm::mat4(1.0f);
	this->tex = -1, this->spec = -1;
	this->origin = glm::vec3(.0f);
}

Model::Model(const std::string& object_file	 , const std::string& texture_file,
			 const std::string& specular_file, const glm::vec3& origin) 
{
	this->vertexCount = 0;
	this->M = glm::mat4(1.0f);
	this->origin = origin;

	std::fstream file;
	file.open(object_file, std::ios::in);
	if (!file.good()) {
		std::cout << "File error: failed to open " << object_file << std::endl;
		this->tex  = -1;
		this->spec = -1;		
		return;
	}
	// -----------------------------------------------------------------------------------

	glm::vec4 coordinates;
	std::vector<glm::fvec4> temp_vertex_normals;
	std::vector<glm::fvec4> temp_vertex_positions;

	glm::vec2 texture;
	std::vector<glm::fvec2> temp_vertex_texcoords;

	std::string str;
	while (std::getline(file, str)) {
		std::stringstream line;
		line.str(str);
		line >> str;

		if (str == "v") {
			line >> coordinates.x >> coordinates.y >> coordinates.z;
			coordinates.w = 1;
			temp_vertex_positions.push_back(coordinates);
		}
		else if (str == "vt") {
			line >> texture.x >> texture.y;
			temp_vertex_texcoords.push_back(texture);
		}
		else if (str == "vn") {
			line >> coordinates.x >> coordinates.y >> coordinates.z;
			coordinates.w = 0;
			temp_vertex_normals.push_back(coordinates);
		}
		else if (str == "f") {
			unsigned int vertex_number;
			int n = 0;

			while (line >> vertex_number) {
				if (n == 0) {
					this->vertex_positions.push_back(temp_vertex_positions[vertex_number - 1]);
				}
				else if (n == 1) {
					this->vertex_texcoords.push_back(temp_vertex_texcoords[vertex_number - 1]);
				}
				else if (n == 2) {
					this->vertex_normals.push_back(temp_vertex_normals[vertex_number - 1]);
				}

				while (line.peek() == '/') {
					line.ignore(1);
					++n;
				}
				if (line.peek() == ' ') {
					line.ignore(1);
					n = 0;
				}
			}
		}
	}

	file.close();
	std::cout << "Object file " << object_file << " has been loaded." << std::endl;
	this->vertexCount = vertex_positions.size();
	// -----------------------------------------------------------------------------------

	this->tex  = readTexture(texture_file.c_str());
	this->spec = readTexture(specular_file.c_str());
	std::cout << "Textures have been loaded." << std::endl;
}

Model::~Model() {}

GLuint Model::readTexture(const char* filename) {
	GLuint tex;
	glActiveTexture(GL_TEXTURE0);

	std::vector<unsigned char> image;
	unsigned width, height;

	unsigned error = lodepng::decode(image, width, height, filename);

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return tex;
}
