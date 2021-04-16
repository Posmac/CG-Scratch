#include "custom_math.h"
#include "Canvas.h"
#include "Camera.h"
#include "Ray.h"
#include "Scene.h"
#define CANVAS_W 512
#define CANVAS_H 512
#define RECURSION_DEPTH 6

cgm::vec3f cameraPosition(3.0f, 0.0f, 1.0f);
cgm::vec3f backGroundColor(0.0f);
const int spheresCount = 4;
const int lightCount = 3;
cgm::Matrix4x4f cameraRotation (0.7070, 0.0f, -0.7071, 0.0f,
                                0.0f, 1.0f, 0.0f, 0.0f,
                                0.7071, 0.0f, 0.7071, 0.0f,
                                0.0f, 0.0f, 0.0f, 1.0f);

Sphere spheres[spheresCount] = {
        Sphere(cgm::vec3f(0.0f, -1.0f, 3.0f), cgm::vec3f(255.0f, 0.0f, 0.0f), 1.0f, 500, 0.2f),
        Sphere(cgm::vec3f(2.0f,  0.0f, 4.0f), cgm::vec3f(0.0f,   0.0f, 255.0f), 1.0f, 500, 0.3f),
        Sphere(cgm::vec3f(-2.0f, 0.0f, 4.0f), cgm::vec3f(0.0f, 255.0f, 0.0f), 1.0f, 10, 0.4f),
        Sphere(cgm::vec3f(0.0f, -5001.0f, 0.0f), cgm::vec3f(255.0f, 255.0f, 0.0f), 5000.0f, 1000, 0.5f),
};

Light lights[lightCount] = {
        Light(cgm::vec3f(), cgm::vec3f(), 0.2f, AMBIENT),
        Light(cgm::vec3f(2.0f, 1.0f, 0.0f), cgm::vec3f(), 0.6f, POINT),
        Light(cgm::vec3f(), cgm::vec3f(1.0f, 4.0f, 4.0f), 0.2f, DIRECTIONAL)
};

int main()
{
    cg::Camera camera(cameraPosition, cameraRotation);
    cg::Canvas canvas(CANVAS_W, CANVAS_H, 1, 1);
    cg::Scene mainScene;
    mainScene.AddLightsToScene(&lights[0], lightCount);
    mainScene.AddObjectsToScene(&spheres[0], spheresCount);
    cg::Ray ray(mainScene._sceneSpheres, mainScene._sceneLights, &backGroundColor);
    mainScene.DrawScene(canvas, camera, ray, RECURSION_DEPTH);
    canvas.GenerateImage("FinalImage");
    return 0;
}
