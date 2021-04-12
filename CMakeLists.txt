cmake_minimum_required(VERSION 3.17)
project(CG_Scratch)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Headers)
include_directories(SourceFiles)
include_directories(ImportedImages)
include_directories(Headers/glm)

add_executable(CG_Scratch
        GeneratedImages/output.ppm
        Headers/custom_math.h
        Headers/shapes.h
        ImportedImages/output.ppm
        SourceFiles/main.cpp
        )
