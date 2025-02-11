cmake_minimum_required(VERSION 3.10)
project(untitled13)

set(CMAKE_CXX_STANDARD 11)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Add FreeGLUT include and library directories
include_directories(C:/Users/Infotech/Desktop/CodeB/freeglut-MinGW-3/freeglut/include)
link_directories(C:/Users/Infotech/Desktop/CodeB/freeglut-MinGW-3/freeglut/lib/x64)

# Add stb include directory
include_directories(${CMAKE_SOURCE_DIR}/stb)  # Assuming the 'stb' folder is in the root of your project
include_directories(C:/Users/Infotech/CLionProjects/untitled13/stb_new)

# Add the executable and source files
add_executable(untitled13 Task2.cpp)

# Link OpenGL and FreeGLUT libraries
target_link_libraries(untitled13 ${OPENGL_LIBRARIES} freeglut)
