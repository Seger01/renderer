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

Window::Window(int width, int height) : mScreenWidth(width), mScreenHeight(height), mouseX(0.0f), mouseY(0.0f)
{

    if (!glfwInit())
    {
        std::cout << "GLFW failed to initialize" << std::endl;
        return;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

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

    // Set user pointer for callbacks
    glfwSetWindowUserPointer(window, this);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    // Key events
    glfwSetKeyCallback(window,
                       [](GLFWwindow* win, int key, int scancode, int action, int mods)
                       {
                           auto self = static_cast<Window*>(glfwGetWindowUserPointer(win));
                           if (self)
                               self->onKey(key, scancode, action, mods);
                       });

    // Mouse button events
    glfwSetMouseButtonCallback(window,
                               [](GLFWwindow* win, int button, int action, int mods)
                               {
                                   auto self = static_cast<Window*>(glfwGetWindowUserPointer(win));
                                   if (self)
                                       self->onMouseButton(button, action, mods);
                               });

    // Cursor position (mouse movement)
    glfwSetCursorPosCallback(window,
                             [](GLFWwindow* win, double xpos, double ypos)
                             {
                                 auto self = static_cast<Window*>(glfwGetWindowUserPointer(win));
                                 if (self)
                                     self->onCursorPos(xpos, ypos);
                             });

    // Scroll events
    glfwSetScrollCallback(window,
                          [](GLFWwindow* win, double xoffset, double yoffset)
                          {
                              auto self = static_cast<Window*>(glfwGetWindowUserPointer(win));
                              if (self)
                                  self->onScroll(xoffset, yoffset);
                          });

    // Character input
    glfwSetCharCallback(window,
                        [](GLFWwindow* win, unsigned int codepoint)
                        {
                            auto self = static_cast<Window*>(glfwGetWindowUserPointer(win));
                            if (self)
                                self->onChar(codepoint);
                        });

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    stbi_set_flip_vertically_on_load(true);
}

Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
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

void Window::updateEvents()
{
    // reset key press and release states
    for (int i = 0; i < 512; ++i)
    {
        if (keyPresses[i])
            keyPresses[i] = false; // Reset after processing
        if (keyReleases[i])
            keyReleases[i] = false; // Reset after processing
    }
    for (int i = 0; i < 8; i++)
    {
        if (mouseButtonDown[i])
            mouseButtonDown[i] = false; // Reset after processing
        if (mouseButtonUp[i])
            mouseButtonUp[i] = false; // Reset after processing
    }

    glfwPollEvents();
}

bool* Window::getKeyPresses()
{
    // Return the current key press states
    return keyPresses;
}

bool* Window::getKeyReleases()
{
    // Return the current key release states
    return keyReleases;
}

Vector2 Window::getMousePosition() { return Vector2(mouseX, mouseY); }

bool* Window::getMouseButtonsStates()
{
    // Return the current mouse button states
    return mouseButtonDown;
}

bool Window::getLeftMouseButtonDown() { return mouseButtonDown[GLFW_MOUSE_BUTTON_LEFT]; }

bool Window::getLeftMouseButtonUp() { return mouseButtonUp[GLFW_MOUSE_BUTTON_LEFT]; }

bool Window::getRightMouseButtonDown() { return mouseButtonDown[GLFW_MOUSE_BUTTON_RIGHT]; }

bool Window::getRightMouseButtonUp() { return mouseButtonUp[GLFW_MOUSE_BUTTON_RIGHT]; }

bool Window::getMiddleMouseButtonDown() { return mouseButtonDown[GLFW_MOUSE_BUTTON_MIDDLE]; }

bool Window::getMiddleMouseButtonUp() { return mouseButtonUp[GLFW_MOUSE_BUTTON_MIDDLE]; }

void Window::onKey(int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        // std::cout << "Key pressed: " << key << std::endl;
        keyPresses[key] = true; // Mark key as pressed
    }
    else if (action == GLFW_RELEASE)
    {
        // std::cout << "Key released: " << key << std::endl;
        keyReleases[key] = true; // Mark key as released
    }
    else if (action == GLFW_REPEAT)
    {
        // std::cout << "Key repeated: " << key << std::endl;
    }
}

void Window::onMouseButton(int button, int action, int mods)
{
    // std::cout << "[MouseButton] button=" << button << " action=" << action << " mods=" << mods << std::endl;
    if (action == GLFW_PRESS)
    {
        mouseButtonDown[button] = true; // Mark mouse button as pressed
    }
    else if (action == GLFW_RELEASE)
    {
        mouseButtonUp[button] = true; // Mark mouse button as released
    }
}

void Window::onCursorPos(double xpos, double ypos)
{
    mouseX = static_cast<float>(xpos);
    mouseY = static_cast<float>(ypos);
    // std::cout << "[CursorPos] x=" << xpos << " y=" << ypos << std::endl;
}

void Window::onScroll(double xoffset, double yoffset)
{
    // std::cout << "[Scroll] xoffset=" << xoffset << " yoffset=" << yoffset << std::endl;
}

void Window::onChar(unsigned int codepoint) { /*  std::cout << "[Char] codepoint=" << codepoint << std::endl;  */ }

} // namespace SML
