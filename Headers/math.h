#ifndef CUSTOM_MATH
#define CUSTOM_MATH

#include <cmath>

namespace MATH
{
    template<typename T>
    class Vector3
    {
    public:
        T x, y, z;
        Vector3 () : x(0), y(0), z(0) {}
        Vector3 (T v) : x(v), y(v), z(v) {}
        Vector3 (T v1, T v2, T v3) : x(v1), y(v2), z(v3) {}
    };

    typedef Vector3<float> Vector3f;
}
#endif // CUSTOM_MATH

