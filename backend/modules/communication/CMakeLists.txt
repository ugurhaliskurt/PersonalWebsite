cmake_minimum_required(VERSION 3.12)
project(communication)

set(INCLUDE_DIRECTORIES
	include
)

set(SYSTEM_INCLUDE_DIRECTORIES
)

set(LINK_LIBRARIES
    -lpistache
)



FILE(GLOB_RECURSE SRC_LIST src/*.cpp)
add_library(${PROJECT_NAME} ${SRC_LIST})

target_include_directories(${PROJECT_NAME} PUBLIC  ${INCLUDE_DIRECTORIES})

target_link_libraries(${PROJECT_NAME}
    ${LINK_LIBRARIES}
)