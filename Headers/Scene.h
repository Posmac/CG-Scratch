#ifndef CG_SCRATCH_SCENE_H
#define CG_SCRATCH_SCENE_H

#include <iostream>
#include <vector>
#include "Sphere.h"
#include "Light.h"

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
        void DrawScene(const char* name, const RenderType renderType) const;
    };
}


#endif //CG_SCRATCH_SCENE_H
