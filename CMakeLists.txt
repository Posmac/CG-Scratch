cmake_minimum_required(VERSION 3.17)
project(CG_Scratch)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Headers)
include_directories(SourceFiles)
include_directories(ImportedImages)

add_executable(CG_Scratch
        GeneratedImages/output.ppm
        Headers/math.h
        Headers/shapes.h
        ImportedImages/output.ppm
        SourceFiles/main.cpp
        Shapes.h)
