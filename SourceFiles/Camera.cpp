#include "Camera.h"

cg::Camera::Camera(const cgm::vec3f &cPos, const cgm::Matrix4x4f &cRot)
    : cameraRotation(cRot), cameraPosition(cPos)
{

}
cg::Camera::~Camera()
{

}
