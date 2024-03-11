cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 11)
project(Boids VERSION 0.1)
include_directories("src/include")
set(EXECUTABLE_OUTPUT_PATH "src")

add_executable(boids src/main.cpp src/car.cpp src/data.cpp src/fieldb.cpp src/input.cpp
        src/model.cpp src/output.cpp src/pigeon.cpp
        src/Food.cpp src/obstacle.cpp
)
