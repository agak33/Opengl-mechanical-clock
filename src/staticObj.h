#pragma once
#include "model.h"

/*
* Class to create static object, without any animation.
* Inherits constructor from Model class.
*/

class StaticObj :
    public Model
{
    using Model::Model;
    void update(const float& time);
};

