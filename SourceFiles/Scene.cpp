#include <limits>
#include "Scene.h"

cg::Scene::Scene()
{

}

cg::Scene::~Scene()
{

}

void cg::Scene::AddLightToScene(const Light &light)
{
    _sceneLights.push_back(light);
}

void cg::Scene::AddObjectToScene(const Sphere &sphere)
{
    _sceneSpheres.push_back(sphere);
}

void cg::Scene::AddObjectsToScene(const Sphere *sphere, int size)
{
    for(int i = 0; i < size; i++)
    {
        _sceneSpheres.push_back(sphere[i]);
    }
}
void cg::Scene::AddLightsToScene(const Light *light, int size)
{
    for(int i = 0; i < size; i++)
    {
        _sceneLights.push_back(light[i]);
    }
}

void cg::Scene::DrawScene(cg::Canvas &canvas,cg::Camera &camera,cg::Ray &ray, const float depth)
{
    for(int x = -canvas.canvas_weight/2; x < canvas.canvas_weight/2; x++)
    {
        for(int y = -canvas.canvas_height/2; y < canvas.canvas_height/2; y++)
        {
            cgm::vec3f direction = canvas.CanvasToViewPort(x,y);
            direction = camera.cameraRotation.mulDirectionMatrix(direction);
            cgm::vec3f color = ray.TraceRay(camera.cameraPosition, direction.normalize(),
                                            1, std::numeric_limits<float>::infinity(), depth);
            color = canvas.ClampColor(color);
            canvas.PutPixel(x,y, color);
        }
    }
}
