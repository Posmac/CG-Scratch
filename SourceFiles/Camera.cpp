#include "Camera.h"

cg::Camera::Camera(const cgm::vec3f &cPos, const cgm::Matrix4x4f &cRot)
    : cameraRotation(cRot), cameraPosition(cPos)
{}

cg::Camera::Camera(const cgm::vec3f &cPos)
    :cameraPosition(cPos)
{
    cameraRotation = cgm::Matrix4x4f (0.7070, 0.0f, -0.7071, 0.0f,
                                      0.0f, 1.0f, 0.0f, 0.0f,
                                      0.7071, 0.0f, 0.7071, 0.0f,
                                      0.0f, 0.0f, 0.0f, 1.0f);
}

cg::Camera::~Camera()
{

}
