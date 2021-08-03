#pragma once

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>


class Camera
{
public:
	glm::vec3 obs_position;		// observer's position
	glm::vec3 obs_point;		// observer's point of observation
	glm::vec3 obs_direction;	// direction of observation
	glm::mat4 V;				// view matrix

	float pitch, yaw;

	Camera();
	~Camera();

	void updateCamera(	const float& dt,
						const float& speed_x,
						const float& speed_z,
						const float& offsetX,
						const float& offsetY);
};

