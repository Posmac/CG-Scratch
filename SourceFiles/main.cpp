#include <iostream>
#include "math.h"

int main()
{
    MATH::Vector3f vec(2.0f, 0.95f, 0.1f);
    std::cout << vec << std::endl;
    MATH::Vector3f vec2 (2.0, 1.3, 0.24);
    MATH::Vector3f cross = vec.cross(vec2);
    float dot = vec.dot(vec2);
    std::cout << cross << std::endl;
    std::cout << dot << std::endl;
    vec.normalize();
    vec2.normalize();
    std::cout << vec << "\n" << vec2 << std::endl;
    dot = vec.dot(vec2);
    std::cout << dot << std::endl;

    MATH::Vector3f difference = vec - vec2;
    std::cout << difference << std::endl;
    return 0;
}
