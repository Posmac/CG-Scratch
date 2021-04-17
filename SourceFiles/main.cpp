#include "Scene.h"

#define CANVAS_W 256
#define CANVAS_H 256
#define RECURSION_DEPTH 6

cgm::vec3f *canvasBuffer = new cgm::vec3f[CANVAS_W * CANVAS_H];

void PutPixel(float x, float y, cgm::vec3f color)
{
    x = CANVAS_W/2 + floor(x);
    y = CANVAS_H/2 - floor(y) - 1;

    if(x < 0 || x >= CANVAS_W || y < 0 || y >= CANVAS_H)
        return;
    int number = x * CANVAS_W + y;
    canvasBuffer[number].x  = color.x;
    canvasBuffer[number].y  = color.y;
    canvasBuffer[number].z  = color.z;
}

std::vector<float>& Interpolate(float i0,float d0, float i1, float d1)
{
    std::vector<float> *values = new std::vector<float>;
    if(i0 == i1)
    {
        values->push_back(d0);
        return *values;
    }
    float a = (d1 - d0) / (i1 - i0);
    float d = d0;
    for(auto i = i0; i < i1; i++)
    {
        values->push_back(d);
        d += a;
    }
    return *values;
}
void DrawLine(cgm::vec3f &p0, cgm::vec3f &p1, cgm::vec3f &color)
{
    float dx = p1.x - p0.x;
    float dy = p1.y - p0.y;
    if(std::abs(dx) > std::abs(dy))
    {
        if(dx < 0)
        {
            cgm::vec3f tmp = p0;
            p0 = p1;
            p1 = tmp;
        }
        std::vector<float> ys = Interpolate(p0.x, p0.y, p1.x, p1.y);
        for(int x = p0.x ; x <= p1.x; x++)
        {
            PutPixel(x, ys[x - p0.x], color);
        }
    }
    else
    {
        if(dy < 0)
        {
            cgm::vec3f tmp = p0;
            p0 = p1;
            p1 = tmp;
        }
        std::vector<float> xs = Interpolate(p0.y, p0.x, p1.y, p1.x);
        for(int y = p0.y ; y <= p1.y; y++)
        {
            PutPixel(xs[y - p0.y], y, color);
        }
    }
}

int main()
{
    for(int i = 0; i < CANVAS_H*CANVAS_W; i++)
        canvasBuffer[i] = cgm::vec3f(255.0f);
    /*cgm::vec3f cameraPosition(3.0f, 0.0f, 1.0f);
    cg::Camera camera(cameraPosition);

    cg::Canvas canvas(CANVAS_W, CANVAS_H, 1, 1);

    cg::Scene mainScene;
    mainScene.AddObjectToScene(Sphere(cgm::vec3f(0.0f, -1.0f, 3.0f),
                                      cgm::vec3f(255.0f, 0.0f, 0.0f), 1.0f, 500, 0.2f));
    mainScene.AddObjectToScene(Sphere(cgm::vec3f(2.0f,  0.0f, 4.0f),
                                      cgm::vec3f(0.0f,   0.0f, 255.0f), 1.0f, 500, 0.3f));
    mainScene.AddObjectToScene(Sphere(cgm::vec3f(-2.0f, 0.0f, 4.0f),
                                      cgm::vec3f(0.0f, 255.0f, 0.0f), 1.0f, 10, 0.4f));
    mainScene.AddObjectToScene(Sphere(cgm::vec3f(0.0f, -5001.0f, 0.0f),
                                      cgm::vec3f(255.0f, 255.0f, 0.0f), 5000.0f, 1000, 0.5f));

    mainScene.AddLightToScene(Light(cgm::vec3f(), cgm::vec3f(), 0.2f, AMBIENT));
    mainScene.AddLightToScene(Light(cgm::vec3f(2.0f, 1.0f, 0.0f), cgm::vec3f(), 0.6f, POINT));
    mainScene.AddLightToScene( Light(cgm::vec3f(), cgm::vec3f(1.0f, 4.0f, 4.0f), 0.2f, DIRECTIONAL));

    cg::Ray ray(mainScene._sceneSpheres, mainScene._sceneLights, &camera.cameraPosition);

    mainScene.DrawScene(canvas, camera, ray, RECURSION_DEPTH);

    canvas.GenerateImage("FinalImage");*/
    cgm::vec3f p1(-200.0f, -100.0f, 0.0f);
    cgm::vec3f p2(240.0f, 120.0f, 0.0f);
    cgm::vec3f p3(-50.0f, -200.0f, 0.0f);
    cgm::vec3f p4(60.0f, 240.0f, 0.0f);
    cgm::vec3f color(0.0f);

    DrawLine(p1, p2, color);
    DrawLine(p3, p4, color);

    std::ofstream ofs;
    ofs.open("./Raster.ppm");
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
    std::cout << "DONE " << "\n";

    return 0;
}
