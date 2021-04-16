#include "Canvas.h"

cg::Canvas::Canvas(const int &w, const int &h, const int &vSize, const int &pDistance)
    : canvas_weight(w), canvas_height(h), projectionPlane(pDistance), viewPortSize(vSize)
{

}
cg::Canvas::~Canvas()
{

}
cgm::vec3f cg::Canvas::CanvasToViewPort(int x, int y)
{
    return cgm::vec3f( x * viewPortSize/(float) canvas_weight,
                       y * viewPortSize/(float) canvas_height,
                       projectionPlane);
}
cgm::vec3f cg::Canvas::ClampColor(const cgm::vec3f color)
{
    return
    {
        std::min(255.0f, std::max(0.0f, color.x)),
        std::min(255.0f, std::max(0.0f, color.y)),
        std::min(255.0f, std::max(0.0f, color.z))
    };
}

void cg::Canvas::GenerateImage(const char* name) const
{
    std::ofstream ofs;
    ofs.open("./" + std::string(name) +  ".ppm");
    ofs << "P3\n" << canvas_weight << " " << canvas_height << "\n255\n";

    for(int x = 0; x < canvas_weight; x++)
    {
        for(int y = 0; y < canvas_height; y ++)
        {
            ofs << canvasBuffer[y * canvas_weight + x].x << " "
                << canvasBuffer[y * canvas_weight + x].y << " "
                << canvasBuffer[y * canvas_weight + x].z << "\n";
        }
    }

    ofs.close();
    std::cout << "DONE" << "\n";
}
void cg::Canvas::PutPixel(int x, int y, const cgm::vec3f &color) const
{
    x = canvas_weight/2 + x;
    y = canvas_height/2 - y - 1;

    if(x < 0 || x >= canvas_weight || y < 0 || y > canvas_height)
        return;
    int number = x * canvas_weight + y;
    canvasBuffer[number].x  = color.x;
    canvasBuffer[number].y  = color.y;
    canvasBuffer[number].z  = color.z;
}