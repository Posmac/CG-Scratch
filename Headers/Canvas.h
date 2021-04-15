#ifndef CG_SCRATCH_CANVAS_H
#define CG_SCRATCH_CANVAS_H
#include "custom_math.h"
#include <iostream>
namespace cg
{
    class Canvas
    {
    public:
        int canvas_weight;
        int canvas_height;

        Canvas(const int &w, const int &h);
        ~Canvas();
        cgm::vec3f CanvasToViewPort(int x, int y) ;
        void PutPixel(int x, int y, const cgm::vec3f &color) const;
        cgm::vec3f ClampColor(const cgm::vec3f color);
        void GenerateImage() const;
    };
}
#endif //CG_SCRATCH_CANVAS_H
