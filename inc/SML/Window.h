#pragma once

#include <SML/glad/glad.h>

#include "GLFW/glfw3.h"
#include "SML/Color.h"
#include "SML/Texture.h"

#include "SML/Point.h"
#include "SML/Vector2.h"

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
