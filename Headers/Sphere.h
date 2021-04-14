#pragma once
#include "custom_math.h"
class Sphere
{
public:
    cgm::vec3f center;
    float radius;
    cgm::vec3f color;
    int specular;
    float reflective;

    Sphere() : center(cgm::vec3f(0.0f)), radius(0.0f), color(cgm::vec3f(255.0f)), specular(1.0f) {}
    Sphere(const cgm::vec3f &sCenter, const cgm::vec3f &sColor, const float &sRadius, const int &sSpecular, const float &sReflective)
        : center(sCenter), color(sColor), radius(sRadius), specular(sSpecular), reflective(sReflective) {}
};

