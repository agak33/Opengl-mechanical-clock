#include "camera.h"


Camera::Camera() {
	this->obs_position	= glm::vec3(0.0f, 1.0f, 6.0f);
	this->obs_direction = glm::vec3(0.0f, 0.0f, -1.0f);
	this->obs_point		= this->obs_position + this->obs_direction;

	this->V = glm::lookAt(	this->obs_position,				// observer's position
							this->obs_point,				// observer's point of observation
							glm::vec3(0.0f, 1.0f, 0.0f));	// vector up 
	this->yaw = -90.0f;
	this->pitch = 0.0f;
}

Camera::~Camera() {}

void Camera::updateCamera(	const float& dt,
							const float& speed_x,
							const float& speed_z,
							const float& offsetX,
							const float& offsetY) 
{
	this->yaw	+= offsetX;
	this->pitch += offsetY;

	if (this->pitch > 90)		this->pitch =  90;
	else if (this->pitch < -90) this->pitch = -90;

	this->obs_position.x += dt * speed_x;
	this->obs_position.z += dt * speed_z;

	this->obs_direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->obs_direction.y = sin(glm::radians(this->pitch));
	this->obs_direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

	this->obs_point = this->obs_direction + this->obs_position;

	this->V = glm::lookAt(	this->obs_position,
							this->obs_point,
							glm::vec3(0.0f, 1.0f, 0.0f));
}
