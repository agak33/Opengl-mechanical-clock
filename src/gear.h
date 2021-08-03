#pragma once
#define _USE_MATH_DEFINES

#include "model.h"
#include <math.h>

class Gear :
    public Model
{
public:
    float speed, angle;

    Gear();
    Gear(const bool& left_direction, const float& pitch_num, const std::string& object_file,
         const std::string& texture_file, const std::string& specular_file, const glm::vec3& origin);
    ~Gear();

    void update(const float& time);
};

