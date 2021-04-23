cmake_minimum_required(VERSION 3.17)
project(CG_Scratch)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Headers)
include_directories(Headers/glm)
include_directories(SourceFiles)
include_directories(ImportedImages)

add_executable(CG_Scratch
        Headers/custom_math.h
        Headers/Sphere.h
        SourceFiles/main.cpp
        Headers/Light.h
        Headers/Scene.h
        SourceFiles/Scene.cpp
        SourceFiles/Canvas.cpp
        Headers/Canvas.h
        Headers/Camera.h
        SourceFiles/Camera.cpp
        Headers/Ray.h
        SourceFiles/Ray.cpp)
