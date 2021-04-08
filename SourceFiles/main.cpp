#include <iostream>
#include "math.h"

int main()
{
    MATH::Vector3f vec(2.0f);
    std::cout << vec << std::endl;

    std::cout << vec.lenght() <<  vec.normalize() <<std::endl;
    return 0;
}
