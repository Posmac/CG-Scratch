#include <iostream>
#include <fstream>
#include <istream>
#include <iostream>
#include <string>
#include "math.h"
#include "shapes.h"
//#include "Headers/shapes.h"

struct QuadraticEquationCoefficients
{
public:
    float t1;
    float t2;
    QuadraticEquationCoefficients(): t1(0), t2(0) {};
    ~QuadraticEquationCoefficients() {};
};


//Scene setup
float viewPortSize = 1.0f;
float projectionPlaneDistance = 1.0f;
cgm::Vector3f cameraPosition (0.0f, 0.0f, 0.0f);
cgm::Vector3f backGroundColor (255.0f);
const int canvas_width = 512;
const int canvas_height = 512;
const int spheresCount = 4;
const int sourceLightCount = 3;

RT::Sphere spheres[spheresCount] = {
                            RT::Sphere(cgm::Vector3f(0.0f, -5001.0f, 0.0f), cgm::Vector3f(255.0f, 0.0f, 255.0f), 5000.0f, 1000.0f),
                            RT::Sphere(cgm::Vector3f(0.0f,  -0.5f, 3.0f), cgm::Vector3f(255.0f, 0.0f, 0.0f), 1.0f, 500.0f),
                            RT::Sphere(cgm::Vector3f(-2.0f,  0.0f, 4.0f), cgm::Vector3f(0.0f,  255.0f, 0.0f), 1.0f, 10.0f),
                            RT::Sphere(cgm::Vector3f(2.0f,  0.0f, 4.0f), cgm::Vector3f(0.0f, 0.0f, 255.0f), 1.0f, 150.0f)
                                    };
RT::LightSource lightSources[sourceLightCount] = {
                                   RT::LightSource(cgm::Vector3f(0.0f), cgm::Vector3f(0.0f), 0.2f, RT::AMBIENT),
                                   RT::LightSource(cgm::Vector3f(2.0f, 1.0f, 0.0f), cgm::Vector3f(0.0f), 1.6f, RT::POINT),
                                   RT::LightSource(cgm::Vector3f(0.0f), cgm::Vector3f(1.0f, 4.0f, 4.0f), 0.2f, RT::DIRECTIONAL)
                                 };

cgm::Vector3<float> *canvasBuffer = new cgm::Vector3<float>[canvas_height * canvas_width];

//Utility fucntions
cgm::Vector3f CanvasToViewPort(const cgm::Vector3f &p)
{
    cgm::Vector3f result = cgm::Vector3f(p.x * (float)viewPortSize / canvas_width,
                                         p.y * (float)viewPortSize / canvas_height,
                                         projectionPlaneDistance);
    return result;
}



QuadraticEquationCoefficients IntersectRaySphere(cgm::Vector3f &origin, cgm::Vector3f &direction, RT::Sphere &sphere)
{
    cgm::Vector3f OC = (origin - sphere.Position);

    //return struct for 2 coefficients
    QuadraticEquationCoefficients k;

    //coefficients for a^2 + 2*b + c = 0 equation
    float a = direction.dot(direction);
    float b = 2 * OC.dot(direction);
    float c = OC.dot(OC) - sphere.radius * sphere.radius;

    //solving it
    float discriminant = b*b - 4*a*c;

    if(discriminant < 0)
    {
       k.t1 = LONG_MAX;
       k.t2 = k.t1;
       return k;
    }

    //finding coefficients
    float t1 = (-b + sqrt(discriminant) / (2*a));
    float t2 = (-b - sqrt(discriminant) / (2*a));
    k.t1 = t1;
    k.t2 = t2;
    return k;
}

cgm::Vector3f TraceRay(cgm::Vector3f origin , cgm::Vector3f direction, const float min_t, const float max_t)
{
    float closest_t = LONG_MAX;
    RT::Sphere closestSphere;

    for(int i = 0; i < spheresCount; i++)
    {
        QuadraticEquationCoefficients coeff = IntersectRaySphere(origin, direction, spheres[i]);
        if(coeff.t1 < closest_t && min_t < coeff.t1 && coeff.t1 < max_t)
        {
            closest_t = coeff.t1;
            closestSphere = spheres[i];
        }
        if(coeff.t2 < closest_t && min_t < coeff.t2 && coeff.t2 < max_t)
        {
            closest_t = coeff.t1;
            closestSphere = spheres[i];
        }
    }
    if(closestSphere.radius == 0)
            return backGroundColor;
    return closestSphere.Color;
}

void PutPixel(float x, float y, cgm::Vector3f color)
{
    x = canvas_width/2 + x;
    y = canvas_height/2 - y;

    if(x < 0 || x > canvas_width || y < 0 || y > canvas_height)
        return;

    int number = x * canvas_width + y;
    canvasBuffer[number-1].x  = color.x;
    canvasBuffer[number-1].y  = color.y;
    canvasBuffer[number-1].z  = color.z;
}
cgm::Vector3f ClampColor(cgm::Vector3f &c)
{
    //int ir = static_cast<int>(255.999 * c.x/255.0f);
    //int ig = static_cast<int>(255.999 * c.y/255.0f);
    //int ib = static_cast<int>(255.999 * c.z/255.0f);
    return cgm::Vector3f(c.x,c.y,c.z);
}
int main()
{
    //main loop
    for(int i = -canvas_width/2; i < canvas_width/2; i++)
    {
        for(int j = -canvas_height/2; j < canvas_height/2; j++)
        {
            cgm::Vector3f direction = CanvasToViewPort(cgm::Vector3f( i, j, 0.0f));
            cgm::Vector3f color = TraceRay(cameraPosition, direction, 1, LONG_MAX);
            //std::cout << color << "\n";
            //color = ClampColor(color);
            PutPixel(i,j, color);
        }
    }

    std::ofstream ofs;
    ofs.open("./output.ppm");
    ofs << "P3\n" << canvas_width << " " << canvas_height << "\n255\n";
    for(int i = 0; i < canvas_height; i++)
    {
        for(int j = 0; j < canvas_width; j ++)
        {
            ofs << canvasBuffer[j * canvas_width + i].x << " "
                << canvasBuffer[j * canvas_width + i].y << " "
                << canvasBuffer[j * canvas_width + i].z << "\n";
        }
    }
    ofs.close();

    std::cout << "DONE" << "\n";


    delete [] canvasBuffer;
    return 0;
}
