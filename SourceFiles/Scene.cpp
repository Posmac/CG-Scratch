#include <limits>
#include "Scene.h"

cg::Scene::Scene()
{

}

cg::Scene::~Scene()
{

}

void cg::Scene::AddLightToScene(const Light &light) const
{
    _sceneLights.push_back(light);
}

void cg::Scene::AddObjectToScene(const Sphere &sphere) const
{
    _sceneSpheres.push_back(sphere);
}

void cg::Scene::DrawScene(cg::Canvas &canvas,cg::Camera &camera,cg::Ray &ray, const float depth) const
{
    for(int x = -canvas.canvas_weight/2; x < canvas.canvas_weight/2; x++)
    {
        for(int y = -canvas.canvas_height/2; y < canvas.canvas_height/2; y++)
        {
            cgm::vec3f direction = canvas.CanvasToViewPort(x,y);
            direction = camera.cameraRotation.mulDirectionMatrix(direction);
            cgm::vec3f color = ray.TraceRay(camera.cameraPosition, direction.normalize(), 1, std::numeric_limits<float>::infinity(), depth);
            color = canvas.ClampColor(color);
            canvas.PutPixel(x,y, color);
        }
    }
}
