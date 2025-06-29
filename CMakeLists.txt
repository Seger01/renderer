cmake_minimum_required(VERSION 3.15)

# Project name and version
project(renderer VERSION 1.0 LANGUAGES C CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Enable generation of compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define paths
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(EXTERNAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external)
set(SHADER_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders_h)

# Include directories
include_directories(${INC_DIR} ${SHADER_INC_DIR})
# Collect all source files recursively
file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.cpp ${SRC_DIR}/*.c)

# Set the output directory for the library/executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Detect if included as a subproject
if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    # Top-level project: build as executable
    add_executable(${PROJECT_NAME} ${SOURCES})
    target_include_directories(${PROJECT_NAME}
        PUBLIC ${INC_DIR}
    )
else()
    # Submodule: build as library
    add_library(${PROJECT_NAME} STATIC ${SOURCES})
    target_include_directories(${PROJECT_NAME}
        PUBLIC ${INC_DIR}
    )
endif()

file(GLOB EXTERNAL_PROJECTS RELATIVE ${EXTERNAL_DIR} ${EXTERNAL_DIR}/*)
foreach(dep ${EXTERNAL_PROJECTS})
    if(EXISTS ${EXTERNAL_DIR}/${dep}/CMakeLists.txt)
      add_subdirectory(
        ${EXTERNAL_DIR}/${dep}
        ${CMAKE_BINARY_DIR}/renderer_build/${dep}
      )
    endif()
endforeach()

# Find OpenGL
find_package(OpenGL REQUIRED)

# Link external libraries
target_link_libraries(${PROJECT_NAME} PUBLIC glfw OpenGL::GL glm freetype)

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
