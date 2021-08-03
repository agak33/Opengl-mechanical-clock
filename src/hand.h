#pragma once
#include "model.h"

enum kind { SECOND, MINUTE, HOUR };

class Hand :
    public Model
{
public:
    int ticks_number;
    float rotation_speed;

    Hand(const int& kind, const std::string& object_file,
         const std::string& texture_file, const std::string& specular_file,
         const glm::vec3& origin);
    
    void update(const float& time);
};

