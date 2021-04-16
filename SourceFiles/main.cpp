#include "Scene.h"

#define CANVAS_W 512
#define CANVAS_H 512
#define RECURSION_DEPTH 6


void PutPixel(float x, float y, cgm::vec3f color)
{
    x = CANVAS_W/2 + floor(x);
    y = CANVAS_H/2 - floor(y) - 1;

    if(x < 0 || x >= CANVAS_W || y < 0 || y <= CANVAS_H)
        return;
    int number = y * CANVAS_W + x;

}

int main()
{
    cgm::vec3f cameraPosition(3.0f, 0.0f, 1.0f);
    cg::Camera camera(cameraPosition);

    cg::Canvas canvas(CANVAS_W, CANVAS_H, 1, 1);

    cg::Scene mainScene;
    mainScene.AddObjectToScene(Sphere(cgm::vec3f(0.0f, -1.0f, 3.0f),
                                      cgm::vec3f(255.0f, 0.0f, 0.0f), 1.0f, 500, 0.2f));
    mainScene.AddObjectToScene(Sphere(cgm::vec3f(2.0f,  0.0f, 4.0f),
                                      cgm::vec3f(0.0f,   0.0f, 255.0f), 1.0f, 500, 0.3f));
    mainScene.AddObjectToScene(Sphere(cgm::vec3f(-2.0f, 0.0f, 4.0f),
                                      cgm::vec3f(0.0f, 255.0f, 0.0f), 1.0f, 10, 0.4f));
    mainScene.AddObjectToScene(Sphere(cgm::vec3f(0.0f, -5001.0f, 0.0f),
                                      cgm::vec3f(255.0f, 255.0f, 0.0f), 5000.0f, 1000, 0.5f));

    mainScene.AddLightToScene(Light(cgm::vec3f(), cgm::vec3f(), 0.2f, AMBIENT));
    mainScene.AddLightToScene(Light(cgm::vec3f(2.0f, 1.0f, 0.0f), cgm::vec3f(), 0.6f, POINT));
    mainScene.AddLightToScene( Light(cgm::vec3f(), cgm::vec3f(1.0f, 4.0f, 4.0f), 0.2f, DIRECTIONAL));

    cg::Ray ray(mainScene._sceneSpheres, mainScene._sceneLights, &camera.cameraPosition);

    mainScene.DrawScene(canvas, camera, ray, RECURSION_DEPTH);

    canvas.GenerateImage("FinalImage");

    return 0;
}
