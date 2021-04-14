#ifndef CUSTOM_MATH
#define CUSTOM_MATH

#include <cmath>
#include <ostream>

namespace cgm {
    template<typename T>
    class vec2 {
    public:
        //initialize vector elements
        T x, y;

        //constructors
        vec2() : x(0), y(0) {}

        vec2(T v) : x(v), y(v) {}

        vec2(T e1, T e2) : x(e1), y(e2) {}

        vec2(const vec2<T> &v) : x(v.x), y(v.y) {}


        ///overloaded operators

        //arithemical with return value
        vec2 operator+(const vec2<T> &v) { return vec2(x + v.x, y + v.y); }

        vec2 operator-(const vec2<T> &v) { return vec2(x - v.x, y - v.y); }

        vec2 operator*(const T r) { return vec2(x * r, y * r); }

        vec2 operator/(const T r) { return vec2(x - r, y - r); }

        vec2 operator*(const vec2<T> &v) { return vec2(x * v.x, y * v.y); }

        vec2 operator/(const vec2<T> &v) { return vec2(x / v.x, y / v.y); }

        //arithmetical with vec2 own
        vec2 &operator*=(const T &r) {
            x *= r, y *= r;
            return *this;
        }

        vec2 operator/=(const T &r) {
            x /= r, y /= r;
            return *this;
        }

        vec2 &operator=(const vec2<T> &v) {
            x = v.x, y = v.y;
            return *this;
        }

        //accessors
        const T *operator[](uint8_t i) const { return (&x)[i]; };

        T &operator[](uint8_t i) { return (&x)[i]; };

        //friend
        friend vec2 operator*(const T &r, const vec2<T> &v) { return vec2(v.x * r, v.y * r); }

        friend vec2 operator/(const T &r, const vec2<T> &v) { return vec2(v.x / r, v.y / r); }

        //streaming
        friend std::ostream &operator<<(std::ostream &s, const vec2<T> &v) {
            return s << "[" << v.x << " , " << v.y << "]" << "\n";
        }

        //functions
        T norm() { return x * x + y * y; }

        T length() { return sqrt(norm()); }

        T dot(const vec2<T> &v) { return x * v.x + y * v.y; }

        vec2 normalize() {
            T n = norm();
            if (n > 0) {
                T factor = 1.0f / length();
                T xx = x * factor;
                T yy = y * factor;
                return vec2(xx, yy);
            }
            return *this;
        }
    };

    //define vector2
    typedef vec2<float> vec2f;
    typedef vec2<int> vec2i;
    typedef vec2<unsigned char> vec2c;


    template<typename T>
    class vec3 {
    public:
        //elements
        T x, y, z;

        //constructors
        vec3() : x(0), y(0), z(0) {}

        vec3(T r) : x(r), y(r), z(r) {}

        vec3(T e1, T e2, T e3) : x(e1), y(e2), z(e3) {}

        vec3(const vec2<T> &v) : x(v.x), y(v.y), z(0) {}

        vec3(const vec3<T> &v) : x(v.x), y(v.y), z(v.z) {}


        ///overloaded operators

        //simple arithmetic
        vec3 operator+(const vec3<T> &v) { return vec3(x + v.x, y + v.y, z + v.z); }

        vec3 operator-(const vec3<T> &v) { return vec3(x - v.x, y - v.y, z - v.z); }

        vec3 operator*(const T &r) { return vec3(x * r, y * r, z * r); }

        vec3 operator/(const T &r) { return vec3(x / r, y / r, z / r); }

        vec3 operator*(const vec3<T> &v) { return vec3(x * v.x, y * v.y, z * v.z); }

        vec3 operator/(const vec3<T> &v) { return vec3(x / v.x, y / v.y, z / v.z); }


        //arithmetical with vec3 own
        vec3 &operator*=(const T &r) {
            x *= r, y *= r, z *= r;
            return *this;
        }

        vec3 &operator/=(const T &r) {
            x /= r, y /= r, z /= r;
            return *this;
        }

        //friend
        friend vec3 operator*(const T &r, const vec3<T> &v) { return vec3(v.x * r, v.y * r, v.z * r); }

        friend vec3 operator/(const T &r, const vec3<T> &v) { return vec3(v.x / r, v.y / r, v.z / r); }

        //streaming
        friend std::ostream &operator<<(std::ostream &s, const vec3<T> &v) {
            return s << "[" << v.x << " , " << v.y << " , " << v.z << "]" << "\n";
        }

        //accessors
        const T *operator[](uint8_t i) const { return (&x)[i]; };

        T &operator[](uint8_t i) { return (&x)[i]; };

        //functions
        T norm() { return x * x + y * y + z * z; }

        T length() { return sqrt(norm()); }

        T dot(const vec3<T> &v) { return x * v.x + y * v.y + z * v.z; }

        vec3 normalize() {
            T n = norm();
            if (n > 0) {
                T factor = 1.0f / length();
                T xx = x * factor;
                T yy = y * factor;
                T zz = z * factor;
                return vec3(xx, yy, zz);
            }
            return vec3(x, y, z);
        }

        vec3 cross(const vec3<T> &v) {
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


    template<typename T>
    class Matrix4x4 {
    public:
        //elements
        T e[4][4] = {{1, 0, 0, 0},
                     {0, 1, 0, 0},
                     {0, 0, 1, 0},
                     {0, 0, 0, 1}};

        //constructors
        Matrix4x4() {}

        Matrix4x4(T a) {
            e[0][0] = a, e[0][1] = 0, e[0][2] = 0, e[0][3] = 0,
            e[1][0] = 0, e[1][1] = a, e[1][2] = 0, e[1][3] = 0,
            e[2][0] = 0, e[2][1] = 0, e[2][2] = a, e[2][3] = 0,
            e[3][0] = 0, e[3][1] = 0, e[3][2] = 0, e[3][3] = a;
        }

        Matrix4x4(T e1, T e2, T e3, T e4,
                  T e5, T e6, T e7, T e8,
                  T e9, T e10, T e11, T e12,
                  T e13, T e14, T e15, T e16) {
            e[0][0] = e1, e[0][1] = e2, e[0][2] = e3, e[0][3] = e4,
            e[1][0] = e5, e[1][1] = e6, e[1][2] = e7, e[1][3] = e8,
            e[2][0] = e9, e[2][1] = e10, e[2][2] = e11, e[2][3] = e12,
            e[3][0] = e13, e[3][1] = e14, e[3][2] = e15, e[3][3] = e16;
        }

        //accessors
        const T* operator[](uint8_t i) const { return e[i]; };

        T& operator[](uint8_t i) { return e[i]; };

        //operation with matrices

        Matrix4x4 operator*(const Matrix4x4 &s) const {
            Matrix4x4 tmp;
            return tmp;
        }

        //multiplication //transposed //inverse

        //vector matrix multiplication
        template<typename S>
        vec3<S> mulVectorMatrix(const vec3<S> &src) const
        {
            vec3<S> result;

            S a, b, c, w;

            a = src[0] * e[0][0] + src[1] * e[1][0] + src[2] * e[2][0] + e[3][0];
            b = src[0] * e[0][1] + src[1] * e[1][1] + src[2] * e[2][1] + e[3][1];
            c = src[0] * e[0][2] + src[1] * e[1][2] + src[2] * e[2][2] + e[3][2];
            w = src[0] * e[0][3] + src[1] * e[1][3] + src[2] * e[2][3] + e[3][3];

            result.x = a / w;
            result.y = b / w;
            result.z = c / w;

            return result;
        }


        template<typename S>
        vec3<S> mulDirectionMatrix(vec3<S> &src) const
        {
            vec3<S> result;
            S a, b, c;

            a = src[0] * e[0][0] + src[1] * e[1][0] + src[2 ] * e[2][0];
            b = src[0] * e[0][1] + src[1] * e[1][1] + src[2] * e[2][1];
            c = src[0] * e[0][2] + src[1] * e[1][2] + src[2] * e[2][2];

            result.x = a;
            result.y = b;
            result.z = c;

            return result;
        }

    };

    typedef Matrix4x4<float> Matrix4x4f;
}

#endif // CUSTOM_MATH

