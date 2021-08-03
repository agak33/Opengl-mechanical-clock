#include "pendulum.h"

Pendulum::Pendulum() : Model() {
    this->angle = 0;
}

Pendulum::Pendulum(const float& max_yaw, const std::string& object_file, 
                   const std::string& texture_file, const std::string& specular_file, 
                   const glm::vec3& origin) : Model(object_file, texture_file, specular_file, origin) {
    this->angle = 0;
}

void Pendulum::update(const float& time) {
    this->angle = 25.0f * (float)sin(std::fmod(time / 2.0f, 1) * 2.0f * M_PI);

    this->M = glm::mat4(1.0f);
    this->M = glm::translate(this->M, this->origin);
    this->M = glm::rotate(this->M, glm::radians(this->angle), glm::vec3(.0f, .0f, 1.0f));
    this->M = glm::translate(this->M, -this->origin);
}
