#include "Window.h"
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image/stb_image.h>

#include <iostream>

#include "Point.h"
#include "Vector2.h"

namespace SML
{

Window::Window(int width, int height) : mScreenWidth(width), mScreenHeight(height)
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    window = glfwCreateWindow(mScreenWidth, mScreenHeight, "FMLWindow", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    auto lambda = [](GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); };
    void (*funcPtr)(GLFWwindow*, int, int) = +lambda; // The `+` forces a function pointer conversion
    glfwSetFramebufferSizeCallback(window, funcPtr);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    stbi_set_flip_vertically_on_load(true);
}

void Window::clear(const Color& color)
{
    glClearColor(color.normalize().r, color.normalize().g, color.normalize().b, color.normalize().a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::show() { glfwSwapBuffers(window); }

Point Window::getWindowSize()
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return Point(width, height);
}

bool Window::shouldClose() { return glfwWindowShouldClose(window); }

// static void FMLWindow::framebuffer_size_callback(GLFWwindow* window, int width, int height)
// {
//     mScreenWidth = width;
//     mScreenHeight = height;
//
//     glViewport(0, 0, width, height);
// }

} // namespace SML
