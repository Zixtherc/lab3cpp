cmake_minimum_required(VERSION 3.25)
project(ProgrammingProject3 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ProgrammingProject3 src/main.cpp src/work.cpp)

if (MSVC)
    target_compile_options(ProgrammingProject3 PRIVATE /utf-8 /W4)
else()
    find_package(Threads REQUIRED)
    target_link_libraries(ProgrammingProject3 PRIVATE Threads::Threads)
    target_compile_options(ProgrammingProject3 PRIVATE -Wall -Wextra)
endif()
