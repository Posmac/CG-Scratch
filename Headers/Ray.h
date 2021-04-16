#ifndef CG_SCRATCH_RAY_H
#define CG_SCRATCH_RAY_H
#include "custom_math.h"
#include "Sphere.h"
#include "Light.h"

namespace cg
{
    class Intersection
    {
    public:
        Sphere *sphere;
        float closest_t;
    };

    class Ray
    {
    public:
        Sphere *spheres;
        Light *lights;

        Ray(Sphere &spheresPTR, Light &lightsPTR);
        ~Ray();
        cgm::vec3f TraceRay(cgm::vec3f origin, cgm::vec3f direction, float min_t, float max_t, float depth);
        cgm::vec3f ReflectRay(cgm::vec3f &v1,cgm::vec3f &n);
        cgm::vec2f IntersectRaySphere(cgm::vec3f &origin, cgm::vec3f &direction, Sphere &sphere);
        Intersection* ClosestIntersection(cgm::vec3f &origin, cgm::vec3f  direction,float min_t, float max_t);
        cgm::vec3f ComputeLighting(cgm::vec3f point, cgm::vec3f normal, cgm::vec3f &view, float specular);
    };
}
#endif //CG_SCRATCH_RAY_H
