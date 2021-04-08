#ifndef CUSTOM_MATH
#define CUSTOM_MATH

#include <cmath>

namespace MATH
{
    template<typename T>
    class Vector3
    {
    public:
        //members
        T x, y, z;
        //constructors
        Vector3 () : x(0), y(0), z(0) {}
        Vector3 (T v) : x(v), y(v), z(v) {}
        Vector3 (T v1, T v2, T v3) : x(v1), y(v2), z(v3) {}


        //overloaded operators
        Vector3 &operator * (const T &v)
        {
            x *= v, y*= v, z*= v;
            return *this;
        }

        Vector3 &operator + (const Vector3<T> &v)
        {
            x += v.x, y += v.y, z += v.z; return *this;
        }

        Vector3 &operator - (const Vector3<T> &v)
        {
            x -= v.x, y -= v.y, z-=v.z; return *this;
        }

        Vector3 &operator / (const T &v)
        {
            x /= v, y /= v, z /= v; return *this;
        }

        const T& operator [] (uint8_t i) const { return (&x)[i]; }
        T& operator [] (uint8_t i) { return (&x)[i]; }

        Vector3 &operator *= (const T &v)
        {
            x *= v, y *= v, z *= v; return *this;
        }

        Vector3 &operator /= (const T &v)
        {
            x /= v, y /= v, z /= v; return *this;
        }

        friend std::ostream& operator << (std::ostream &s, const Vector3<T> &v)
        {
            return s << "[" << v.x << " " << v.y << " " << v.z << "]";
        }

        //calculations
        T norm() const
        {
            return x * x + y * y + z * z;
        }

        T lenght()
        {
            return sqrt(norm());
        }

        Vector3& normalize()
        {
            T n = norm();
            if (n > 0)
            {
                T factor = 1 / lenght();
                x *= factor, y *= factor, z *= factor;
            }
            return *this;
        }
    };

    typedef Vector3<float> Vector3f;
}
#endif // CUSTOM_MATH

