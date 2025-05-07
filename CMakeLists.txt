cmake_minimum_required(VERSION 3.15)

project(indproj VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Project structure
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(SHADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders_h)
set(EXTERNAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external)

# Collect all source files recursively
file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.cpp ${SRC_DIR}/*.c)

# Define the library (change STATIC to SHARED if you want a shared library)
add_library(${PROJECT_NAME} STATIC ${SOURCES})

# Specify include directories for your library consumers
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${INC_DIR}>
        $<BUILD_INTERFACE:${SHADERS_DIR}>
        $<INSTALL_INTERFACE:include>
)

# Find required packages
find_package(OpenGL REQUIRED)

# Link dependencies (assume these are available in EXTERNAL_DIR or system)
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        OpenGL::GL
        glfw
        glm
        freetype
)

# Optionally add external dependencies as subdirectories
file(GLOB EXTERNAL_PROJECTS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${EXTERNAL_DIR}/*)
foreach(EXTERNAL_PROJECT ${EXTERNAL_PROJECTS})
    if(EXISTS ${EXTERNAL_DIR}/${EXTERNAL_PROJECT}/CMakeLists.txt)
        add_subdirectory(${EXTERNAL_DIR}/${EXTERNAL_PROJECT})
    endif()
endforeach()

# Optionally export the library target to make it accessible to parent projects
# (if used as a submodule via add_subdirectory)
# You can add export/install logic here if you want to support find_package(indproj)

# Copy compile_commands.json for development
if(CMAKE_EXPORT_COMPILE_COMMANDS)
    set(COMPILE_COMMANDS_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
    add_custom_target(
        CopyCompileCommands ALL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_BINARY_DIR}/compile_commands.json
            ${COMPILE_COMMANDS_OUTPUT_DIR}/compile_commands.json
    )
endif()
