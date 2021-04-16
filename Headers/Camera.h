#ifndef CG_SCRATCH_CAMERA_H
#define CG_SCRATCH_CAMERA_H
#include "custom_math.h"
namespace cg
{
    class Camera
    {
    public:
        cgm::Matrix4x4f cameraRotation;
        cgm::vec3f cameraPosition;

        Camera(const cgm::vec3f &cPos,const cgm::Matrix4x4f &cRot);
        ~Camera();
    };
}
#endif //CG_SCRATCH_CAMERA_H
