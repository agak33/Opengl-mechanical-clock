#include "gear.h"

Gear::Gear() {
    this->speed = 0, this->angle = 0;
}

Gear::Gear( const bool& left_direction, const float& pitch_num, const std::string& object_file,
            const std::string& texture_file, const std::string& specular_file,
            const glm::vec3& origin) : Model(object_file, texture_file, specular_file, origin) {

    this->speed = 360 / pitch_num;
    this->angle = 0;

    if (left_direction) this->speed = -this->speed;
}

Gear::~Gear(){}

void Gear::update(const float& time) {
    float a = (float)sin(std::fmod(time, 1) * 2.0f * M_PI - 1.5f * M_PI);
    if (a > 0) {
        this->angle += this->speed * 0.08f * a;
    }

    this->M = glm::mat4(1.0f);
    this->M = glm::translate(this->M, this->origin);
    this->M = glm::rotate(this->M, glm::radians(this->angle), glm::vec3(.0f, .0f, 1.0f));
    this->M = glm::translate(this->M, -this->origin);
}
