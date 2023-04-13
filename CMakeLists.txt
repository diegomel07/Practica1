cmake_minimum_required(VERSION 3.0)

# Set the project name
project(practica1)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)

# Add an executable
add_executable(practica1 Main.cpp helpers.cpp)

# Add the directory containing the header file to the include path
target_include_directories(practica1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Set the output directory for the executable
set_target_properties(practica1 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

