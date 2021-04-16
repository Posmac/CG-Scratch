#ifndef CG_SCRATCH_SCENE_H
#define CG_SCRATCH_SCENE_H

#include <iostream>
#include <vector>
#include "Sphere.h"
#include "Light.h"
#include "Canvas.h"
#include "Camera.h"
#include "Ray.h"

namespace cg
{
    enum RenderType {RAYTRACING, RASTERIZATION};
    class Scene
    {
    public:

        std::vector<Sphere> _sceneSpheres;
        std::vector<Light> _sceneLights;

        Scene();
        ~Scene();
        void AddObjectToScene(const Sphere &sphere);
        void AddObjectsToScene(const Sphere *sphere, int size);
        void AddLightToScene(const Light &light);
        void AddLightsToScene(const Light *light, int size);
        void DrawScene(cg::Canvas &canvas,cg::Camera &camera,cg::Ray &ray , const float depth);
    };
}


#endif //CG_SCRATCH_SCENE_H
