cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(Game VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    add_compile_options(
            -Wall
    )
else()
    add_compile_options(
            -Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual
            -Wconversion -Wctor-dtor-privacy -Wenum-compare -Wfloat-equal
            -Wnon-virtual-dtor -Woverloaded-virtual -Wold-style-cast
            -Wredundant-decls -Wsign-conversion -Wsign-promo
    )
endif()

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

add_executable(${PROJECT_NAME} "src/main.cpp")
include_directories(
        ./packages/Corsac_Test/include
        ./packages/Corsac_Benchmark/include
        ./packages/Corsac_ECS/include
        ./packages/Corsac_STL/include
)