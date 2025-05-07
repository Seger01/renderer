cmake_minimum_required(VERSION 3.15)

# Project name and version
project(indproj VERSION 1.0 LANGUAGES C CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Enable generation of compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define paths
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_SOURCE_DIR}/inc)
set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/external)

# Include directories
include_directories(${INC_DIR})

# add the /shaders directory to the include path
include_directories(${CMAKE_SOURCE_DIR}/shaders_h)

# Collect all source files recursively
file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.cpp ${SRC_DIR}/*.c)

# Set the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include and build external libraries
file(GLOB EXTERNAL_PROJECTS ${EXTERNAL_DIR}/*)
foreach(EXTERNAL_PROJECT ${EXTERNAL_PROJECTS})
    if(EXISTS ${EXTERNAL_PROJECT}/CMakeLists.txt)
        add_subdirectory(${EXTERNAL_PROJECT})
    endif()
endforeach()

# Find OpenGL
find_package(OpenGL REQUIRED)

# Link external libraries
target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL glm freetype)

if(CMAKE_EXPORT_COMPILE_COMMANDS)
    set(COMPILE_COMMANDS_OUTPUT_DIR "${CMAKE_SOURCE_DIR}")
    # file(MAKE_DIRECTORY ${COMPILE_COMMANDS_OUTPUT_DIR})

    add_custom_target(
        CopyCompileCommands ALL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_BINARY_DIR}/compile_commands.json
            ${COMPILE_COMMANDS_OUTPUT_DIR}/compile_commands.json
        # COMMENT "Copying compile_commands.json to ${COMPILE_COMMANDS_OUTPUT_DIR}"
    )
endif()
