cmake_minimum_required(VERSION 3.31)
project(a4c)

set(CMAKE_CXX_STANDARD 20)

add_executable(a4c main.cpp)

target_include_directories(a4c PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(a4c PRIVATE ws2_32)