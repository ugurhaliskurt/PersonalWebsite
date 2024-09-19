cmake_minimum_required(VERSION 3.10)
project(BasicService)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(modules)
add_subdirectory(service)
# Optionally set some additional compile flags
set_target_properties(${PROJECT_NAME} PROPERTIES
    COMPILE_FLAGS "-Wall -Wextra"
)