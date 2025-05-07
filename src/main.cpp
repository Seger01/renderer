#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image/stb_image.h>

#include <iostream>
#include <string>
#include <thread>

#include "Color.h"
#include "Font.h"
#include "Rect.h"
#include "Renderer.h"
#include "Texture.h"
#include "Time.h"
#include "Window.h"

#include "ft2build.h"
#include FT_FREETYPE_H

unsigned int loadTexture(std::string fileName);

// settings
unsigned int Screen_width = 800;
unsigned int Screen_height = 600;

// Camera camera;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

struct RGB
{
    int r, g, b;
};

RGB hueToRGB(float hue)
{
    float s = 1.0f, v = 1.0f; // Assume full saturation and brightness
    float c = s * v;          // Chroma
    float x = c * (1 - fabs(fmod(hue / 60.0, 2) - 1));
    float m = v - c;

    float r, g, b;
    if (hue >= 0 && hue < 60)
    {
        r = c, g = x, b = 0;
    }
    else if (hue < 120)
    {
        r = x, g = c, b = 0;
    }
    else if (hue < 180)
    {
        r = 0, g = c, b = x;
    }
    else if (hue < 240)
    {
        r = 0, g = x, b = c;
    }
    else if (hue < 300)
    {
        r = x, g = 0, b = c;
    }
    else
    {
        r = c, g = 0, b = x;
    }

    return RGB{static_cast<int>((r + m) * 255), static_cast<int>((g + m) * 255), static_cast<int>((b + m) * 255)};
}

int main()
{
    SML::Window window(Screen_width, Screen_height);

    SML::Renderer renderer(window);
    // FMLTexture matrixTexture("resources/matrix.jpg");
    SML::Texture matrixTexture("resources/DinoSprites.png");

    SML::Font font("resources/fonts/joystixmonospace.otf", 48);

    SML::Time::initialize();
    // render loop
    // -----------
    while (!window.shouldClose())
    {
        SML::Time::update();
        // input
        // -----
        // processInput(window);

        renderer.clear(SML::Color(100, 100, 100));

        renderer.setViewport(SML::Rect(200, 200, 10000, 10000));

        renderer.drawRect(100, 100, 200, 200, SML::Color(0, 255, 0, 255), true, 0);
        renderer.drawRect(100, 300, 200, 200, SML::Color(0, 0, 255), false, int(SML::Time::ticks / 10 * 2400) % 360,
                          SML::Point(400, 400));
        renderer.drawRect(300, 100, 200, 200, SML::Color(255, 255, 0), false, int(SML::Time::ticks / 10 * 800) % 360,
                          SML::Point(0, 0));

        renderer.setViewport(SML::Rect());

        renderer.drawRect(300, 300, 200, 200, SML::Color(255, 0, 255, 150), false,
                          int(SML::Time::ticks / 10 * 500) % 360, SML::Point(0, 0));

        RGB hue = hueToRGB(int(SML::Time::ticks / 10 * 1000) % 360);
        renderer.drawTexture(matrixTexture, SML::Rect(), 600, 600, 200, 200, false, false,
                             int(SML::Time::ticks / 10 * 1000) % 360, SML::Color(hue.r, hue.g, hue.b, 255));

        renderer.drawCircle(300, 300, 400, SML::Color(hue.r, hue.g, hue.b), false,
                            400 - (int(SML::Time::ticks / 10 * 1000) % 400));

        // renderer.drawChar(font.charSet['a'], 'a', 100, 100, 1.0f, SML::Color(255,
        // 255, 255)); renderer.renderText(font, "He", 100, 100, 1.0f,
        // SML::Color(255, 255, 255));
        std::string text = "Hello World! GGGG";
        std::string actualText = text.substr(0, int(SML::Time::ticks / 10 * 20) % text.length());
        renderer.renderText(font, actualText, 100, (int(SML::Time::ticks / 10 * 2000) % 800), 1.0f,
                            SML::Color(hue.r, hue.g, hue.b));

        renderer.show();
        glfwPollEvents();

        // wait 16ms to simulate 60fps
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    //
    // if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    //     camera.ProcessKeyboard(Camera_Movement::FORWARD,
    //     (float)own::Time::deltaTime);
    // if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    //     camera.ProcessKeyboard(Camera_Movement::LEFT,
    //     (float)own::Time::deltaTime);
    // if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    //     camera.ProcessKeyboard(Camera_Movement::BACKWARD,
    //     (float)own::Time::deltaTime);
    // if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    //     camera.ProcessKeyboard(Camera_Movement::RIGHT,
    //     (float)own::Time::deltaTime);
    //
    // if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    //     camera.ProcessKeyboard(Camera_Movement::UP,
    //     (float)own::Time::deltaTime);
    // if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    //     camera.ProcessKeyboard(Camera_Movement::DOWN,
    //     (float)own::Time::deltaTime);
    //
    // if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    // {
    //     lightPos.x += 1.0f * own::Time::deltaTime;
    // }
    // if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    // {
    //     lightPos.x -= 1.0f * own::Time::deltaTime;
    // }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    // static float lastX = xpos, lastY = ypos;
    //
    // float xoffset = xpos - lastX;
    // float yoffset = lastY - ypos; // reversed since y-coordinates range from
    // bottom to top lastX = xpos; lastY = ypos;
    //
    // const float sensitivity = 0.1f;
    // xoffset *= sensitivity;
    // yoffset *= sensitivity;
    //
    // camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) { /*  camera.ProcessMouseScroll(yoffset);  */ }

// unsigned int loadTexture(std::string filePath)
// {
//
//     unsigned int textureID;
//     glGenTextures(1, &textureID);
//
//     int width, height, nrComponents;
//     unsigned char* data = stbi_load(filePath.c_str(), &width, &height,
//     &nrComponents, 0); if (data)
//     {
//         GLenum format;
//         if (nrComponents == 1)
//             format = GL_RED;
//         else if (nrComponents == 3)
//             format = GL_RGB;
//         else if (nrComponents == 4)
//             format = GL_RGBA;
//
//         glBindTexture(GL_TEXTURE_2D, textureID);
//         glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
//         GL_UNSIGNED_BYTE, data); glGenerateMipmap(GL_TEXTURE_2D);
//
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
//         GL_LINEAR_MIPMAP_LINEAR); glTexParameteri(GL_TEXTURE_2D,
//         GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//         stbi_image_free(data);
//     }
//     else
//     {
//         std::cout << "Texture failed to load at path: " << filePath <<
//         std::endl; stbi_image_free(data);
//     }
//
//     return textureID;
// }
