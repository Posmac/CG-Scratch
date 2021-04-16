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

void cg::Scene::DrawScene(const char *name, const RenderType renderType) const
{

}
