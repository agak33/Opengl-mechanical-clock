#include "light.h"
#include <iostream>

Light::Light() {
	this->light_pos = glm::vec4(.0f);
	this->direction = glm::vec3(.0f);
	this->speed = 0;
	this->margin_x = 0, this->margin_y = 0, this->margin_z = 0;
}

Light::Light(const glm::vec4& light_pos, const float& speed,
			 const glm::vec3& direction) {
	this->light_pos = light_pos;
	this->speed = speed;
	this->direction = direction;

	this->margin_x = abs(light_pos.x);
	this->margin_y = abs(light_pos.y);
	this->margin_z = abs(light_pos.z);
}

void Light::update(const float& dt) {
	this->light_pos.x += dt * this->speed * this->direction.x;
	this->light_pos.y += dt * this->speed * this->direction.y;
	this->light_pos.z += dt * this->speed * this->direction.z;


	if (this->light_pos.x >= this->margin_x && this->direction.x != 0) {
		this->light_pos.x = this->margin_x;
		this->direction.x = -1;
	}
	else if (this->light_pos.x <= -this->margin_x && this->direction.x != 0) {
		this->light_pos.x = -this->margin_x;
		this->direction.x = 1;
	}


	if (this->light_pos.y >= this->margin_y && this->direction.y != 0) {
		this->light_pos.y = this->margin_y;
		this->direction.y = -1;
	}
	else if (this->light_pos.y <= -this->margin_y && this->direction.y != 0) {
		this->light_pos.y = -this->margin_y;
		this->direction.y = 1;
	}


	if (this->light_pos.z >= this->margin_z && this->direction.z != 0) {
		this->light_pos.z = this->margin_z;
		this->direction.z = -1;
	}
	else if (this->light_pos.z <= -this->margin_z && this->direction.z != 0) {
		this->light_pos.z = -this->margin_z;
		this->direction.z = 1;
	}
}
