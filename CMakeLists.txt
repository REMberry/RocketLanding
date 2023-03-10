cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(RocketLanding)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} src)

add_executable(RocketLanding src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/rocket.cpp src/entity.cpp src/ground.cpp src/helperFunctions.cpp)

string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)

target_link_libraries(RocketLanding ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

file(COPY res DESTINATION ${CMAKE_BINARY_DIR})
