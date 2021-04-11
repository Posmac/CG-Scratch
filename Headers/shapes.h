#pragma once
namespace RT
{


    struct Sphere
    {
    public:
        //public members
        cgm::Vector3f Position; //at 0, 0, 0 bu default
        cgm::Vector3f Color; //white by default
        float radius; //1 by default
        float shininess;//1 by default

        Sphere() : Position(cgm::Vector3f(0.0f)), Color(cgm::Vector3f(255.0f)), radius(.0f), shininess(1.0f) {}
        Sphere(const cgm::Vector3f &p, const cgm::Vector3f &c, float r, float s)
            : Position(p), Color(c), radius(r), shininess(s) {}
    };

    enum LightType {AMBIENT = 0, DIRECTIONAL, POINT};

    struct LightSource
    {
    public:

        cgm::Vector3f Position;
        cgm::Vector3f  Direction;
        float Intensity;
        LightType Type;

        LightSource(const cgm::Vector3f LPos, const cgm::Vector3f LDir, float LInt, LightType LType)
            : Position(LPos), Direction(LDir), Intensity(LInt), Type(LType) {}
    };



}

