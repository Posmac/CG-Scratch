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
    std::vector<Sphere> _sceneSpheres;
    std::vector<Light> _sceneLights;

    enum RenderType {RAYTRACING, RASTERIZATION};

    class Scene
    {
    public:
        Scene();
        ~Scene();
        void AddObjectToScene(const Sphere &sphere) const;
        void AddLightToScene(const Light &light) const;
        void DrawScene(cg::Canvas &canvas,cg::Camera &camera,cg::Ray &ray , const float depth) const;
    };
}


#endif //CG_SCRATCH_SCENE_H
