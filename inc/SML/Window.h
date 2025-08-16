#pragma once

#include <functional>

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
    ~Window();

    void clear(const Color& color);
    void show();

    SML_Point getWindowSize();

    bool shouldClose();

    GLFWwindow* getWindow() { return window; }

    void updateEvents();

    bool* getKeyPresses();
    bool* getKeyReleases();

    bool* getMouseButtonsStates();

    Vector2 getMousePosition();

    bool getLeftMouseButtonDown();
    bool getLeftMouseButtonUp();
    bool getRightMouseButtonDown();
    bool getRightMouseButtonUp();
    bool getMiddleMouseButtonDown();
    bool getMiddleMouseButtonUp();

    // General keyboard event (press/release/repeat)
    void onKey(int key, int scancode, int action, int mods);

    // General mouse button event (press/release)
    void onMouseButton(int button, int action, int mods);

    // General mouse move event
    void onCursorPos(double xpos, double ypos);

    // General mouse scroll event
    void onScroll(double xoffset, double yoffset);

    // General character input (for text)
    void onChar(unsigned int codepoint);

private:
    GLFWwindow* window;

    int mScreenWidth, mScreenHeight;

    float mouseX, mouseY;
    bool keyPresses[512] = {0};
    bool keyReleases[512] = {0};
    bool mouseButtonDown[8] = {0};
    bool mouseButtonUp[8] = {0};
};

} // namespace SML
