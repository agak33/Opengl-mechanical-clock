#pragma once
#define _USE_MATH_DEFINES

#include "model.h"
#include <math.h>

class Pendulum :
    public Model
{
private:
    float angle;
public:
    Pendulum();

    Pendulum(const float& max_yaw, const std::string& object_file, 
             const std::string& texture_file,const std::string& specular_file, 
             const glm::vec3& origin);

    void update(const float& time);
};

