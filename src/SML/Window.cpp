#include "SML/Window.h"
#include <SML/glad/glad.h>

#include <GLFW/glfw3.h>

#include <SML/stb_image/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "SML/Point.h"
#include "SML/Vector2.h"

namespace SML
{

Window::Window(int width, int height) : mScreenWidth(width), mScreenHeight(height)
{
    if (!glfwInit())
    {
        std::cout << "GLFW failed to initialize" << std::endl;
        return;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(mScreenWidth, mScreenHeight, "FMLWindow", NULL, NULL);
    if (window == NULL)
    {
        const char* desc;
        int code = glfwGetError(&desc);
        std::cout << "Failed to create GLFW window (Error " << code << "): " << (desc ? desc : "unknown") << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    auto lambda = [](GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); };
    void (*funcPtr)(GLFWwindow*, int, int) = +lambda;
    glfwSetFramebufferSizeCallback(window, funcPtr);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

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

SML_Point Window::getWindowSize()
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return SML_Point(width, height);
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
