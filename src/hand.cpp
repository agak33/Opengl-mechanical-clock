#include "hand.h"

Hand::Hand(const int& kind, const std::string& object_file, 
           const std::string& texture_file, const std::string& specular_file, 
           const glm::vec3& origin) : Model(object_file, texture_file, specular_file, origin) {

    if (kind == SECOND) {
        this->rotation_speed = -6.0f;
    }
    else if (kind == MINUTE) {
        this->rotation_speed = -0.1f;
    }
    else if (kind == HOUR) {
        this->rotation_speed = -0.1f / 60.0f;
    }
    else {
        std::cout << "Warning: kind of the clock hand was not specified." << std::endl;
        this->rotation_speed = 0.0f;
    }
    this->ticks_number = 0;
}

void Hand::update(const float& time) {
    this->ticks_number = (int)time;
    this->M = glm::mat4x4(1.0f);
    this->M = glm::translate(this->M, this->origin);
    this->M = glm::rotate(this->M, glm::radians(this->rotation_speed * this->ticks_number), glm::vec3(.0f, .0f, 1.0f));
    this->M = glm::translate(this->M, -this->origin);
}
