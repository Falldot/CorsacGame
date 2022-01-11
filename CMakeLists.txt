cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(Game VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

add_subdirectory(./packages/SDL)
add_executable(${PROJECT_NAME} "src/main.cpp")
target_link_libraries(${PROJECT_NAME} SDL2main SDL2)
include_directories(
        ./packages/Corsac_Test/include
        ./packages/Corsac_Benchmark/include
        ./packages/Corsac_ECS/include
        ./packages/Corsac_STL/include
        ./packages/SDL/include
)