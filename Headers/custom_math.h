#ifndef CUSTOM_MATH
#define CUSTOM_MATH

#include <cmath>
#include <ostream>

namespace cgm
{
    template<typename T>
    class vec2
    {
    public:
        //initialize vector elements
        T x,y;

        //constructors
        vec2(): x(0), y(0) {}

        vec2(T v): x(v), y(v) {}

        vec2(T e1, T e2): x(e1), y(e2) {}

        vec2(const vec2<T> &v): x(v.x), y(v.y) {}


        ///overloaded operators

        //arithemical with return value
        vec2 operator + (const vec2<T> &v)
        { return vec2(x + v.x, y + v.y); }

        vec2 operator - (const vec2<T> &v)
        { return vec2(x - v.x, y - v.y); }

        vec2 operator * (const T r)
        { return vec2(x * r, y * r);}

        vec2 operator / (const T r)
        { return vec2(x - r, y - r);}

        vec2 operator * (const vec2<T> &v)
        { return vec2 (x*v.x, y * v.y); }

        vec2 operator / (const vec2<T> &v)
        { return vec2 (x / v.x, y / v.y); }

        //arithmetical with vec2 own
        vec2& operator *= (const T &r)
        { x *= r, y *= r; return *this; }

        vec2 operator /= (const T &r)
        { x /= r, y /= r; return *this; }

        vec2& operator = (const vec2<T> &v)
        { x = v.x, y = v.y ; return *this; }

        //friend
        friend vec2 operator * (const T &r, const vec2<T> &v)
        { return  vec2(v.x * r, v.y * r); }

        friend vec2 operator / (const T &r, const vec2<T> &v)
        { return vec2(v.x / r, v.y / r); }

        //streaming
        friend std::ostream& operator << (std::ostream &s, const vec2<T> &v)
        {return s << "[" << v.x << " , " << v.y << "]" << "\n"; }

        //functions
        T norm() {return x * x + y * y; }

        T length() {return sqrt(norm()); }

        T dot(const vec2<T> &v) {return x*v.x + y*v.y; }

        vec2 normalize()
        {
            T n = norm();
            if(n > 0)
            {
                T factor = 1.0f / length();
                T xx = x * factor;
                T yy = y * factor;
                return vec2(xx,yy);
            }
            return *this;
        }
    };

    //define vector2
    typedef vec2<float> vec2f;
    typedef vec2<int> vec2i;
    typedef vec2<unsigned char> vec2c;


    template<typename T>
    class vec3
    {
    public:
        //elements
        T x,y,z;

        //constructors
        vec3() : x(0), y(0), z(0) {}

        vec3(T r) : x(r), y(r), z(r) {}

        vec3(T e1, T e2, T e3) : x(e1), y(e2), z(e3) {}

        vec3(const vec2<T> &v) : x(v.x), y(v.y), z(0) {}

        vec3(const vec3<T> &v) : x(v.x) , y(v.y), z(v.z) {}


        ///overloaded operators

        //simple arithmetic
        vec3 operator + (const vec3<T> &v)
        { return vec3(x + v.x, y + v.y, z + v.z); }

        vec3 operator - (const vec3<T> &v)
        { return vec3(x - v.x, y - v.y, z - v.z); }

        vec3 operator * (const T &r)
        { return vec3(x * r, y * r, z * r); }

        vec3 operator / (const T &r)
        { return vec3(x / r, y / r, z / r); }

        vec3 operator * (const vec3<T> &v)
        { return vec3(x * v.x, y * v.y, z * v.z); }

        vec3 operator / (const vec3<T> &v)
        { return vec3(x / v.x, y / v.y, z / v.z); }


        //arithmetical with vec3 own
        vec3& operator *= (const T &r)
        { x *= r, y *= r, z *= r; return *this; }

        vec3& operator /= (const T &r)
        { x /= r, y /= r, z /= r; return *this; }

        //friend
        friend vec3 operator * (const T &r, const vec3<T> &v)
        {return vec3(v.x * r, v.y * r, v.z * r);}

        friend vec3 operator / (const T &r, const vec3<T> &v)
        {return vec3(v.x / r, v.y / r, v.z / r);}

        //streaming
        friend std::ostream& operator << (std::ostream &s, const vec3<T> &v)
        { return s << "[" << v.x << " , " << v.y << " , " << v.z << "]" << "\n"; }

        //functions
        T norm() {return x * x + y * y + z * z; }

        T length() {return sqrt(norm()); }

        T dot(const vec3<T> &v) {return x * v.x + y * v.y + z * v.z; }

        vec3 normalize()
        {
            T n = norm();
            if(n > 0)
            {
                T factor = 1.0f / length();
                T xx = x * factor;
                T yy = y * factor;
                T zz = z * factor;
                return vec3(xx, yy,zz);
            }
            return vec3(x,y,z);
        }

        vec3 cross(const vec3<T> &v)
        {
            T xx = y * v.z - z * v.y;
            T yy = z * v.x - x * v.z;
            T zz = x * v.y - y * v.x;
            return vec3(xx, yy, zz);
        }
    };

    //define vec3
    typedef vec3<float> vec3f;
    typedef vec3<int> vec3i;
    typedef vec3<unsigned char> vec3c;
}
#endif // CUSTOM_MATH

