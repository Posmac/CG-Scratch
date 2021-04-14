#include <limits>
#include <iostream>
#include <fstream>
#include "custom_math.h"
#include "Sphere.h"
#include "Light.h"

#define CANVAS_W 512
#define CANVAS_H 512
#define RECURSION_DEPTH 3

int viewPortSize = 1;
int projectionPlane = 1;
cgm::vec3f cameraPosition(3.0f, 0.0f, 1.0f);
cgm::vec3f backGroundColor(0.0f);
const int spheresCount = 4;
const int lightCount = 3;
float rotationAngle = 60;
cgm::Matrix4x4f cameraRotation (0.7070, 0.0f, -0.7071, 0.0f,
                                0.0f, 1.0f, 0.0f, 0.0f,
                                0.7071, 0.0f, 0.7071, 0.0f,
                                0.0f, 0.0f, 0.0f, 1.0f);

Sphere spheres[spheresCount] = {
        Sphere(cgm::vec3f(0.0f, -1.0f, 3.0f), cgm::vec3f(255.0f, 0.0f, 0.0f), 1.0f, 500, 0.2f),
        Sphere(cgm::vec3f(2.0f,  0.0f, 4.0f), cgm::vec3f(0.0f,   0.0f, 255.0f), 1.0f, 500, 0.3f),
        Sphere(cgm::vec3f(-2.0f, 0.0f, 4.0f), cgm::vec3f(0.0f, 255.0f, 0.0f), 1.0f, 10, 0.4f),
        Sphere(cgm::vec3f(0.0f, -5001.0f, 0.0f), cgm::vec3f(255.0f, 255.0f, 0.0f), 5000.0f, 1000, 0.5f),
};

Light lights[lightCount] = {
        Light(cgm::vec3f(), cgm::vec3f(), 0.2f, AMBIENT),
        Light(cgm::vec3f(2.0f, 1.0f, 0.0f), cgm::vec3f(), 0.6f, POINT),
        Light(cgm::vec3f(), cgm::vec3f(1.0f, 4.0f, 4.0f), 0.2f, DIRECTIONAL)
};

cgm::vec3f *canvasBuffer = new cgm::vec3f[CANVAS_W * CANVAS_H];

struct Intersection
{
    Sphere *sphere;
    float closest_t;
};


cgm::vec3f CanvasToViewPort(int x,int y)
{
    return cgm::vec3f( x * viewPortSize/(float) CANVAS_W,
                       y * viewPortSize/(float) CANVAS_H,
                       projectionPlane);
}

cgm::vec2f IntersectRaySphere(cgm::vec3f &origin, cgm::vec3f &direction, Sphere &sphere)
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

Intersection* ClosestIntersection(cgm::vec3f &origin, cgm::vec3f  direction,float min_t, float max_t)
{
    float closest_t = std::numeric_limits<float>::infinity();
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

    return NULL;
}
cgm::vec3f ReflectRay(cgm::vec3f &v1,cgm::vec3f &n)
{
    return 2 * v1.dot(n) * n - v1;
}
cgm::vec3f ComputeLighting(cgm::vec3f point, cgm::vec3f normal, cgm::vec3f &view, float specular)
{
    float intensity = 0.0f;

    for(int i = 0 ; i < spheresCount; i++)
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
    }
    return intensity;
}



cgm::vec3f TraceRay(cgm::vec3f origin, cgm::vec3f direction, float min_t, float max_t, float depth)
{
    Intersection* intersection = ClosestIntersection(origin, direction, min_t, max_t);
    if(intersection == NULL)
        return backGroundColor;

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

void PutPixel(int x, int y,cgm::vec3f color)
{
    x = CANVAS_W/2 + x;
    y = CANVAS_H/2 - y - 1;

    if(x < 0 || x >= CANVAS_W || y < 0 || y > CANVAS_H)
        return;
    int number = x * CANVAS_W + y;
    canvasBuffer[number].x  = color.x;
    canvasBuffer[number].y  = color.y;
    canvasBuffer[number].z  = color.z;
}
cgm::vec3f ClampColor(cgm::vec3f color)
{
    return
    {
        std::min(255.0f, std::max(0.0f, color.x)),
        std::min(255.0f, std::max(0.0f, color.y)),
        std::min(255.0f, std::max(0.0f, color.z))
    };
}
int main()
{
    //std::cout << cameraRotation << "\n";
    for(int x = -CANVAS_W/2; x < CANVAS_W/2; x++)
    {
        for(int y = -CANVAS_H/2; y < CANVAS_H/2; y++)
        {
            cgm::vec3f direction = CanvasToViewPort(x,y);
            direction = cameraRotation.mulDirectionMatrix(direction);
            cgm::vec3f color = TraceRay(cameraPosition, direction.normalize(), 1, std::numeric_limits<float>::infinity(), RECURSION_DEPTH);
            color = ClampColor(color);
            PutPixel(x,y, color);
        }
    }

    std::ofstream ofs;
    ofs.open("./output.ppm");
    ofs << "P3\n" << CANVAS_W << " " << CANVAS_H << "\n255\n";

    for(int x = 0; x < CANVAS_W; x++)
    {
        for(int y = 0; y < CANVAS_H; y ++)
        {
            ofs << canvasBuffer[y * CANVAS_W + x].x << " "
                << canvasBuffer[y * CANVAS_W + x].y << " "
                << canvasBuffer[y * CANVAS_W + x].z << "\n";
        }
    }

    ofs.close();
    std::cout << "DONE" << "\n";
    return 0;
}
