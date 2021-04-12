#include <iostream>
#include "custom_math.h"

int main()
{
    //testing
    cgm::vec2f a(3.0);
    cgm::vec2f b(2.0);
    cgm::vec2f c(0.0f);
    c = a * b;

    c = c.normalize();

    std::cout << a << " " << b << " " << c;


    return 0;
}
