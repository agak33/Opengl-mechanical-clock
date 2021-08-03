#pragma once
#define _USE_MATH_DEFINES

#include <glfw/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

class Light
{
public:
	glm::vec4 light_pos;
	glm::vec3 direction;
	float speed;
	float margin_x, margin_y, margin_z;

	Light();

	Light(const glm::vec4& light_pos, const float& speed,
		  const glm::vec3& direction);

	void update(const float& dt);
};

