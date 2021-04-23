#include "Scene.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define CANVAS_W 512
#define CANVAS_H 512
#define RECURSION_DEPTH 6
#define RST
//colors
glm::vec3 red(255.0f, 0.0f, 0.0f);
glm::vec3 green(0.0, 255.0f, 0.0f);
glm::vec3 blue(0.0f, 0.0f, 255.0f);
glm::vec3 yellow(255.0f, 255.0f, 0.0f);
glm::vec3 purple(255.0f, 0.0f, 255.0f);
glm::vec3 cyan(0.0f, 255.0f, 255.0f);
glm::vec3 black (0.0f);
glm::vec3 white (255.0f);



float viewPortSize = 1;
float projectionPlaneDistance = 1;

glm::vec3 *canvasBuffer = new glm::vec3[CANVAS_W * CANVAS_H];

class Vertex
{
public:
    glm::vec3 Position;
    glm::vec3 Color;
    float shadingCoefficient;
    Vertex() : Position(glm::vec3(0.0f)),
                        Color(glm::vec3(0.0f)), shadingCoefficient(0.0f) {};

    Vertex(const glm::vec3 &vPosition, const float h, const glm::vec3 col)
        : Position(vPosition), shadingCoefficient(h), Color(col) {};
};

class Triangle
{
public:
    int vertexIndices[3];
    Triangle(const int &v1, const int &v2, const int &v3 )
    {
        vertexIndices[0] = v1;
        vertexIndices[1] = v2;
        vertexIndices[2] = v3;
    }
};


class Model
{
public:
    std::vector<Vertex> *vertices;
    std::vector<Triangle> *triangles;
    Model(std::vector<Vertex> &verts, std::vector<Triangle> &tris)
        : vertices(&verts), triangles(&tris){};
};

class Camera
{
public:
    glm::vec3 Position;
    float Orientation;
    Camera(const glm::vec3 &pos, float orient)
        : Position(pos), Orientation(orient)  {};
};

glm::vec3 ViewportToCanvas(glm::vec3 &v)
{
    return glm::vec3(v.x*CANVAS_W/viewPortSize, v.y*CANVAS_H/viewPortSize, v.z);
}

glm::vec3 ProjectVertex(glm::vec3 &v)
{
    glm::vec3 temp = glm::vec3(v.x*projectionPlaneDistance/v.z, v.y*projectionPlaneDistance/v.z, v.z);
    return ViewportToCanvas(temp);
}

template<typename T>
void Swap(T *p0, T *p1)
{
    T tmp = *p0;
    *p0 = *p1;
    *p1 = tmp;
}

void PutPixel(float x, float y, glm::vec3 color)
{
    x = CANVAS_W/2 + floor(x);
    y = CANVAS_H/2 - floor(y) - 1;

    if(x < 0 || x >= CANVAS_W || y < 0 || y >= CANVAS_H)
        return;
    int number = x * CANVAS_W + y;
    canvasBuffer[number].x  = color.x;
    canvasBuffer[number].y  = color.y;
    canvasBuffer[number].z  = color.z;
}
void GenerateImage()
{
    std::ofstream ofs;
    ofs.open("./Raster.ppm");
    ofs.clear();
    ofs << "P3\n" << CANVAS_W << " " << CANVAS_H << "\n255\n";

    for(int x = 0; x < CANVAS_W; x++)
    {
        for(int y = 0; y < CANVAS_H; y ++)
        {
            ofs << canvasBuffer[y * CANVAS_W + x].x << " "
                << canvasBuffer[y * CANVAS_W + x].y << " "
                << canvasBuffer[y * CANVAS_W + x].z << "\n";
        }
    }

    ofs.close();
    std::cout << "DONE " << "\n";

}
std::vector<float>& Interpolate(float i0,float d0, float i1, float d1)
{
    std::vector<float> *values = new std::vector<float>;
    if(i0 == i1)
    {
        values->push_back(d0);
        return *values;
    }
    float a = (d1 - d0) / (i1 - i0);
    float d = d0;
    for(auto i = i0; i < i1; i++)
    {
        values->push_back(d);
        d += a;
    }
    return *values;
}
void DrawLine(glm::vec3 &p0, glm::vec3 &p1, glm::vec3 &color)
{
    glm::vec3 v0(p0);
    glm::vec3 v1(p1);

    float dx = v1.x - v0.x;
    float dy = v1.y - v0.y;
    if(std::abs(dx) > std::abs(dy))
    {
        if(dx < 0)
            Swap(&v0, &v1);

        std::vector<float> ys = Interpolate(v0.x, v0.y, v1.x, v1.y);
        for(int x = v0.x ; x <= v1.x; x++)
        {
            int yy = std::max(0.0f, std::floor(x - v0.x));
            if(yy >= ys.size()-1)
                yy = ys.size()-1;
            PutPixel(x, ys[yy], color);
        }
    }
    else
    {
        if(dy < 0)
            Swap(&v0, &v1);

        std::vector<float> xs = Interpolate(v0.y, v0.x, v1.y, v1.x);
        for(int y = v0.y ; y <= v1.y; y++)
        {
            int xx = std::max(0.0f, std::floor(y-v0.y));
            if(xx >= xs.size()-1)
                xx = xs.size()-1;
            PutPixel(xs[xx], y, color);
        }
    }
    //return normal swapping
    if(dx < 0 || dy < 0)
        Swap(&v0, &v1);
}



void DrawWireFrameTriangle(glm::vec3 &p0, glm::vec3 &p1, glm::vec3 &p2, glm::vec3 &color)
{
    DrawLine(p0, p1, color);
    DrawLine(p1, p2, color);
    DrawLine(p0, p2, color);
}

void DrawShadedTriangle(Vertex &v0, Vertex &v1, Vertex &v2, glm::vec3 &color)
{
    if(v1.Position.y < v0.Position.y) { Swap(&v0, &v1); }
    if(v2.Position.y < v0.Position.y) { Swap(&v0, &v2); }
    if(v2.Position.y < v1.Position.y) { Swap(&v2, &v1); }

    std::vector<float> x01 = Interpolate(v0.Position.y, v0.Position.x, v1.Position.y, v1.Position.x);
    std::vector<float> h01 = Interpolate(v0.Position.y, v0.shadingCoefficient, v1.Position.y, v1.shadingCoefficient);

    std::vector<float> x12 = Interpolate(v1.Position.y, v1.Position.x, v2.Position.y, v2.Position.x);
    std::vector<float> h12 = Interpolate(v1.Position.y, v1.shadingCoefficient, v2.Position.y, v2.shadingCoefficient);

    std::vector<float> x02 = Interpolate(v0.Position.y, v0.Position.x, v2.Position.y, v2.Position.x);
    std::vector<float> h02 = Interpolate(v0.Position.y, v0.shadingCoefficient, v2.Position.y, v2.shadingCoefficient);

    std::vector<float> x012(x01);
    std::vector<float> h012(h01);

    for(int i = 0 ; i < x12.size(); i++)
    {
        x012.push_back(x12[i]);
        h012.push_back(h12[i]);
    }

    std::vector<float> x_left, x_right;
    std::vector<float> h_left, h_right;
    float m = x02.size()/2;
    if(x02[m] < x012[m])
    {
        x_left = x02; x_right = x012;
        h_left = h02; h_right = h012;
    }
    else
    {
        x_left = x012; x_right = x02;
        h_left = h012; h_right = h02;
    }

    for(int y = v0.Position.y; y < v2.Position.y; y++)
    {
        float xl = x_left[y - v0.Position.y];
        float xr = x_right[y - v0.Position.y];

        std::vector<float> h_segment = Interpolate(xl, h_left[y - v0.Position.y], xr, h_right[y - v0.Position.y]);
        for(int x = xl; x <= xr; x++)
        {
            PutPixel(x, y, h_segment[x-xl] * color);
        }
    }

}

void DrawFilledTriangle(glm::vec3 &p0, glm::vec3 &p1, glm::vec3 &p2, glm::vec3 &color)
{
    if(p1.y < p0.y) { Swap(&p1, &p0); }
    if(p2.y < p0.y) { Swap(&p2, &p0); }
    if(p2.y < p1.y) { Swap(&p2, &p1); }

    std::vector<float> x01 = Interpolate(p0.y, p0.x, p1.y, p1.x);
    std::vector<float> x12 = Interpolate(p1.y, p1.x, p2.y, p2.x);
    std::vector<float> x02 = Interpolate(p0.y, p0.x, p2.y, p2.x);

    std::vector<float> x012(x01);
    for(int i = 0; i < x12.size(); i++)
        x012.push_back(x12[i]);

    std::vector<float> x_left, x_right;
    int m = x02.size()/2;
    if(x02[m] < x012[m])
    {
        x_left = x02;
        x_right = x012;
    }
    else
    {
        x_left = x012;
        x_right = x02;
    }
    for(int y = p0.y; y <= p2.y; y++)
    {
        for(int x = x_left[y-p0.y]; x <= x_right[y - p0.y]; x++)
        {
            PutPixel(x,y, color);
        }
    }
}


void RenderModel(Model &model)
{
    std::vector<glm::vec3> projected;
    for(int i = 0; i < model.vertices->size(); i++)
    {
        projected.push_back(ProjectVertex((*model.vertices)[i].Position));
    }

    for(int i = 0; i < model.triangles->size(); i++)
    {
        Triangle tr = (*model.triangles)[i];
        DrawWireFrameTriangle(projected[tr.vertexIndices[0]],projected[tr.vertexIndices[1]],
            projected[tr.vertexIndices[2]], (*model.vertices)[tr.vertexIndices[0]].Color);
    }
}


int main()
{
    for(int i = 0; i < CANVAS_H*CANVAS_W; i++)
        canvasBuffer[i] = glm::vec3(255.0f);

#ifdef RT //Raytraces
    glm::vec3 cameraPosition(3.0f, 0.0f, 1.0f);
    cg::Camera camera(cameraPosition);

    cg::Canvas canvas(CANVAS_W, CANVAS_H, 1, 1);

    cg::Scene mainScene;
    mainScene.AddObjectToScene(Sphere(glm::vec3(0.0f, -1.0f, 3.0f),
                                      glm::vec3(255.0f, 0.0f, 0.0f), 1.0f, 500, 0.2f));
    mainScene.AddObjectToScene(Sphere(glm::vec3(2.0f,  0.0f, 4.0f),
                                      glm::vec3(0.0f,   0.0f, 255.0f), 1.0f, 500, 0.3f));
    mainScene.AddObjectToScene(Sphere(glm::vec3(-2.0f, 0.0f, 4.0f),
                                      glm::vec3(0.0f, 255.0f, 0.0f), 1.0f, 10, 0.4f));
    mainScene.AddObjectToScene(Sphere(glm::vec3(0.0f, -5001.0f, 0.0f),
                                      glm::vec3(255.0f, 255.0f, 0.0f), 5000.0f, 1000, 0.5f));

    mainScene.AddLightToScene(Light(glm::vec3(), glm::vec3(), 0.2f, AMBIENT));
    mainScene.AddLightToScene(Light(glm::vec3(2.0f, 1.0f, 0.0f), glm::vec3(), 0.6f, POINT));
    mainScene.AddLightToScene( Light(glm::vec3(), glm::vec3(1.0f, 4.0f, 4.0f), 0.2f, DIRECTIONAL));

    cg::Ray ray(mainScene._sceneSpheres, mainScene._sceneLights, &camera.cameraPosition);

    mainScene.DrawScene(canvas, camera, ray, RECURSION_DEPTH);

    canvas.GenerateImage("FinalImage");
#endif //RT

#ifdef RST //Rasterizer
    std::vector<Vertex> vertices = std::vector<Vertex>
    {
            Vertex(glm::vec3(1.0f,1.0f,1.0f), 1.0f, red),
            Vertex(glm::vec3(-1.0f,1.0f,1.0f), 1.0f, green),
            Vertex(glm::vec3(-1.0f,-1.0f,1.0f), 1.0f, blue),
            Vertex(glm::vec3(1.0f,-1.0f,1.0f), 1.0f, black),
            Vertex(glm::vec3(1.0f,1.0f,-1.0f), 1.0f, cyan),
            Vertex(glm::vec3(-1.0f,1.0f,-1.0f), 1.0f, purple),
            Vertex(glm::vec3(-1.0f,-1.0f,-1.0f), 1.0f, yellow),
            Vertex(glm::vec3(1.0f,-1.0f,-1.0f), 1.0f, white),
    };

   std::vector<Triangle> triangles = std::vector<Triangle>
   {
            Triangle(0, 1, 2),
            Triangle(0, 2, 3),
            Triangle(4, 0, 3),
            Triangle(4, 3, 7),
            Triangle(5, 4, 7),
            Triangle(5, 7, 6),
            Triangle(1, 5, 6),
            Triangle(1, 6, 2),
            Triangle(4, 5, 1),
            Triangle(4, 1, 0),
            Triangle(2, 6, 7),
            Triangle(2, 7, 3),
   };

    Model cube(vertices, triangles);
    Camera camera(glm::vec3(-3.0f, 1.0f, 2.0f), 00.0f);
    glm::mat4x4 view (1.0f);
    glm::mat4x4 translation (1.0f);

    view = glm::rotate(view, glm::radians(camera.Orientation), glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::transpose(view);

    translation = glm::translate(translation, camera.Position * -1.0f);
    translation =  glm::transpose(translation);

    view = view * translation;

    glm::mat4x4 model = glm::mat4x4 (1.0f);
    model = glm::mat4x4 (1.0f);
    model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 7.0f));
    model = glm::scale(model, glm::vec3(0.75f));

    model = view * model;

    std::vector<Vertex> transformedVertex(vertices);
    for(int i = 0; i < vertices.size(); i++)
    {
        glm::vec4 v4(vertices[i].Position, 1.0f);
        transformedVertex[i].Position = model*v4;
    }
    cube.vertices = &transformedVertex;
    RenderModel(cube);


    model = glm::mat4x4 (1.0f);
    model = glm::translate(model, glm::vec3(1.25f, 2.5f, 7.5f));
    model = glm::rotate(model,  glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.0f));

    model = view * model;

    transformedVertex.clear();
    transformedVertex = std::vector<Vertex>(vertices);
    for(int i = 0; i < vertices.size(); i++)
    {
        glm::vec4 v4(vertices[i].Position, 1.0f);
        transformedVertex[i].Position = model*v4;
    }
    cube.vertices = &transformedVertex;
    RenderModel(cube);

#endif //RST

#ifdef TestCube //For tests, will be cleaned after book completing
    glm::vec3 vA(-2.0f, -0.5f, 5.0f);
    glm::vec3 vB(-2.0f, 0.5f, 5.0f);
    glm::vec3 vC(-1.0f, 0.5f, 5.0f);
    glm::vec3 vD(-1.0f, -0.5f, 5.0f);

    glm::vec3 vAb(-2.0f, -0.5f, 6.0f);
    glm::vec3 vBb(-2.0f, 0.5f, 6.0f);
    glm::vec3 vCb(-1.0f, 0.5f, 6.0f);
    glm::vec3 vDb(-1.0f, -0.5f, 6.0f);

    vA = ProjectVertex(vA);
    vB = ProjectVertex(vB);
    vC = ProjectVertex(vC);
    vD = ProjectVertex(vD);

    vAb = ProjectVertex(vAb);
    vBb = ProjectVertex(vBb);
    vCb = ProjectVertex(vCb);
    vDb = ProjectVertex(vDb);

    DrawLine(vA, vB, red);
    DrawLine(vB, vC, red);
    DrawLine(vC, vD, red);
    DrawLine(vD, vA, red);

    DrawLine(vAb, vBb, blue);
    DrawLine(vBb, vCb, blue);
    DrawLine(vCb, vDb, blue);
    DrawLine(vDb, vAb, blue);

    DrawLine(vAb, vA, green);
    DrawLine(vBb, vB, green);
    DrawLine(vCb, vC, green);
    DrawLine(vDb, vD, green);
#endif
    GenerateImage();
    return 0;
}
