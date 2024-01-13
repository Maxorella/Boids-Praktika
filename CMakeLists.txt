cmake_minimum_required(VERSION 3.0)

project(Boids VERSION 0.1)
include_directories("include")
add_executable(Boids main.cpp car.cpp data.cpp fieldb.cpp input.cpp model.cpp output.cpp pigeon.cpp
        Food.cpp obstacle.cpp
)
