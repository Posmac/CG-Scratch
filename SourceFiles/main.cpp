#include <iostream>
#include <fstream>
#include <istream>
#include <iostream>
#include "math.h"
#include "Shapes.h"

struct QuadraticEcuaqionCoefficients
{
public:
    float t1;
    float t2;
    QuadraticEcuaqionCoefficients(): t1(0), t2(0) {};
    ~QuadraticEcuaqionCoefficients() {};

};


//Scene setup
float viewPortSize = 1.0f;
float projectionPlaneDistance = 1.0f;
cgm::Vector3f cameraPosition (0.0f);
cgm::Vector3f backGroundColor (255.0f);
const int canvas_width = 1024;
const int canvas_height = 1024;

 RT::Sphere spheres[3] = { RT::Sphere(cgm::Vector3f(0.0f, -1.0f, 3.0f), cgm::Vector3f(255.0f, 0.0f, 0.0f), 1.0f),
                              RT::Sphere(cgm::Vector3f(2.0f,  1.0f, 4.0f), cgm::Vector3f(0.0f,  255.0f, 0.0f), 1.0f),
                              RT::Sphere(cgm::Vector3f(-2.0f,  1.0f, 4.0f), cgm::Vector3f(0.0f, 0.0f, 255.0f), 1.0f)};
cgm::Vector3<float> *canvasBuffer = new cgm::Vector3<float>[canvas_height * canvas_width];


//Utility fucntions
cgm::Vector3f CanvasToViewPort(const cgm::Vector3f &p)
{
    return cgm::Vector3f(p.x * viewPortSize / canvas_width,
                         p.y * viewPortSize / canvas_height,
                         projectionPlaneDistance);
}



QuadraticEcuaqionCoefficients IntersectRaySphere(cgm::Vector3f &origin, cgm::Vector3f &direction, RT::Sphere &sphere)
{
    cgm::Vector3f OC = (origin - sphere.Position);

    //return struct for 2 coefficients
    QuadraticEcuaqionCoefficients k;

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

    for(uint32_t i = 0; i < 3; i++)
    {
        QuadraticEcuaqionCoefficients coeff = IntersectRaySphere(origin, direction, spheres[i]);
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
    //there to complete
    int number = x * canvas_width + y;
    canvasBuffer[number-1].x  = color.x;
    canvasBuffer[number-1].y  = color.y;
    canvasBuffer[number-1].z  = color.z;
    /*std::cout << canvasBuffer[b * canvas_height + a].x << "  "
              << canvasBuffer[b * canvas_height + a].y << "  "
              << canvasBuffer[b * canvas_height + a].z << std::endl;*/
    //std::cout << x << " " << y << "  " << x * canvas_width + y << std::endl;
}

int main()
{
    //main loop
    for(int i = -canvas_width/2; i < canvas_width/2; i++)
    {
        for(int j = -canvas_height/2; j < canvas_height/2; j++)
        {
            cgm::Vector3f direction = CanvasToViewPort(cgm::Vector3f( (float)i, (float)j, 0.0f));
            cgm::Vector3f color = TraceRay(cameraPosition, direction, 1, LONG_MAX);
            PutPixel(i,j,color);
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
    delete [] canvasBuffer;
    return 0;
}
