#pragma once

#include <glad/glad.h>

#include "Color.h"
#include "GLFW/glfw3.h"
#include "Texture.h"

#include "Point.h"
#include "Vector2.h"

namespace SML
{

class Window
{
public:
    Window(int width, int height);
    virtual ~Window() = default;

    void clear(const Color& color);
    void show();

    Point getWindowSize();

    bool shouldClose();

    GLFWwindow* getWindow() { return window; }

private:
    // static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    GLFWwindow* window;

    int mScreenWidth, mScreenHeight;
};

} // namespace SML
