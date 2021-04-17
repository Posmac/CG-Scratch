#ifndef CG_SCRATCH_CANVAS_H
#define CG_SCRATCH_CANVAS_H
#include "custom_math.h"
#include <iostream>
#include <fstream>
#include <string>

namespace cg
{
    class Canvas
    {
    public:
        int canvas_weight;
        int canvas_height;
        int viewPortSize;
        int projectionPlane;

        cgm::vec3f *canvasBuffer = new cgm::vec3f[canvas_weight * canvas_height];

        Canvas(const int &w, const int &h, const int &vSize, const int &pDistance);
        ~Canvas();
        cgm::vec3f CanvasToViewPort(int x, int y) ;
        void PutPixel(int x, int y, const cgm::vec3f &color) const;
        cgm::vec3f ClampColor(const cgm::vec3f color);
        void GenerateImage(const char* name) const;
    };
}
#endif //CG_SCRATCH_CANVAS_H
