cmake_minimum_required(VERSION 3.16)
project(MagoArcano)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "main.cpp"
)

add_executable(MagoArcano ${SOURCES})

target_include_directories(MagoArcano PRIVATE headers)

target_link_libraries(MagoArcano
    sfml-graphics sfml-window sfml-system sfml-audio)