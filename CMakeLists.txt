cmake_minimum_required(VERSION 3.5)

project(pipe-example)

set(CMAKE_CXX_STANDARD 11)

# Compile the helper functions into a static library
add_library(helpers STATIC helpers.cpp )
target_include_directories(helpers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Compile the menu program
add_executable(menu menu.cpp)
target_link_libraries(menu PRIVATE helpers)
target_include_directories(menu PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Compile the reader program
add_executable(search search.cpp)
target_link_libraries(search PRIVATE helpers)
target_include_directories(search PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
