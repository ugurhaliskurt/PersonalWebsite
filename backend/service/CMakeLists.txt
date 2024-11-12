project(BasicService)

set(INCLUDE_DIRECTORIES
	include
)

set(SYSTEM_INCLUDE_DIRECTORIES
)

FILE(GLOB_RECURSE SRC_LIST src/*.cpp)
add_library(${PROJECT_NAME}_lib ${SRC_LIST})

target_link_libraries(${PROJECT_NAME}_lib
    communication
    pthread
    database
    -lcurl
)
# Add executable
add_executable(${PROJECT_NAME} main.cpp )

# Link libraries
target_link_libraries(${PROJECT_NAME}
    ${PROJECT_NAME}_lib
)