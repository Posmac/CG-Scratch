#include <limits>
#include "Ray.h"

cg::Ray::Ray(Sphere &spheresPTR, Light &lightsPTR)
        : spheres(&spheresPTR), lights(&lightsPTR)
{

}
cg::Ray::~Ray()
{

}
cgm::vec3f cg::Ray::TraceRay(cgm::vec3f origin, cgm::vec3f direction, float min_t, float max_t, float depth)
{
    Intersection* intersection = ClosestIntersection(origin, direction, min_t, max_t);
    /*if(intersection == NULL)
        return backGroundColor;*/

    float closest_t = intersection->closest_t;
    Sphere *closestSphere = intersection->sphere;

    cgm::vec3f point = origin + closest_t * direction;
    cgm::vec3f normal = point - closestSphere->center;

    cgm::vec3f view = -1.0 * direction;
    cgm::vec3f lighting = ComputeLighting(point, normal, view, closestSphere->specular);
    cgm::vec3f localColor = lighting * closestSphere->color;

    if(closestSphere->reflective <= 0 || depth <= 0)
        return localColor;
    cgm::vec3f reflectedRay = ReflectRay(view, normal);
    cgm::vec3f reflectedColor = TraceRay(point, reflectedRay, 0.01f, std::numeric_limits<float>::infinity(), depth-1);

    return (1-closestSphere->reflective) * localColor + closestSphere->reflective * reflectedColor;
}
cgm::vec3f cg::Ray::ReflectRay(cgm::vec3f &v1, cgm::vec3f &n) \
{
    return 2 * v1.dot(n) * n - v1;
}
cg::Intersection * cg::Ray::ClosestIntersection(cgm::vec3f &origin, cgm::vec3f direction, float min_t, float max_t)
{
    /*float closest_t = std::numeric_limits<float>::infinity();
    Sphere *closestSphere = NULL;
    Intersection *intersection = NULL;

    for(int i = 0; i < spheresCount; i++)
    {
        cgm::vec2f ts = IntersectRaySphere(origin, direction, spheres[i]);
        if(ts.x < closest_t && min_t < ts.x && ts.x < max_t)
        {
            closest_t = ts.x;
            closestSphere = &spheres[i];
        }
        if(ts.y < closest_t && min_t < ts.y && ts.y < max_t)
        {
            closest_t = ts.y;
            closestSphere = &spheres[i];
        }
    }

    if(closestSphere != NULL)
    {
        intersection = new Intersection{ closestSphere, closest_t };
        return intersection;
    }

    return NULL;*/
}

cgm::vec2f cg::Ray::IntersectRaySphere(cgm::vec3f &origin, cgm::vec3f &direction, Sphere &sphere)
{
    cgm::vec3f OC = origin - sphere.center;

    float a = direction.dot(direction);
    float b = 2.0f * OC.dot(direction);
    float c = OC.dot(OC) - pow(sphere.radius, 2.0f);

    float discriminant = b * b - 4 * a * c;
    if(discriminant < 0)
        return cgm::vec2f(std::numeric_limits<float>::infinity());

    return cgm::vec2f ( (-b + sqrt(discriminant)) / (2 * a),
                        (-b - sqrt(discriminant)) / (2 * a));
}

cgm::vec3f cg::Ray::ComputeLighting(cgm::vec3f point, cgm::vec3f normal, cgm::vec3f &view, float specular)
{
    float intensity = 0.0f;

    /*for(int i = 0 ; i < spheresCount; i++)
    {
        Light light = lights[i];
        if(light.Type == AMBIENT)
            intensity += light.intensity;
        else
        {
            cgm::vec3f lDir;
            float t_max = 0.0f;

            if(light.Type == POINT)
            {
                lDir = light.position - point;
                t_max = 1.0f;
            }
            if(light.Type == DIRECTIONAL)
            {
                lDir = light.direction;
                t_max = std::numeric_limits<float>::infinity();
            }

            Intersection* blocker = ClosestIntersection(point, lDir, 0.01f, t_max);
            if(blocker)
                continue;

            lDir = lDir.normalize();
            normal = normal.normalize();

            float dp = normal.dot(lDir);
            if(dp > 0)
                intensity += light.intensity * dp;

            if(specular != -1)
            {
                cgm::vec3f reflVec = (2.0f * normal.dot(lDir)) * normal - lDir;

                reflVec = reflVec.normalize();
                view = view.normalize();

                float rp = reflVec.dot(view);
                if(rp > 0)
                    intensity += light.intensity * pow(rp, specular);

            }
        }
    }*/
    return intensity;
}