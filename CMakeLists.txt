cmake_minimum_required(VERSION 3.10)
project(ShootPart)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)

add_executable(shoot-part main.cpp)
target_link_libraries(shoot-part sfml-graphics sfml-window sfml-system)
