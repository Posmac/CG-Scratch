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
        //public constructors
        Sphere() : Position(cgm::Vector3f(0.0f)), Color(cgm::Vector3f(255.0f)), radius(.0f) {}
        Sphere(const cgm::Vector3f &p, const cgm::Vector3f &c, float r)
            : Position(p), Color(c), radius(r) {}
    };


}

