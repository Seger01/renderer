#include <SML/glad/glad.h>

#include <GLFW/glfw3.h>
#include <SML/stb_image/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <thread>

#include "SML/Color.h"
#include "SML/Font.h"
#include "SML/Rect.h"
#include "SML/Renderer.h"
#include "SML/Texture.h"
#include "SML/Time.h"
#include "SML/Window.h"

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
    SML::Texture dinoTexture("resources/DinoSprites.png");
    SML::Texture UITexture("resources/ui_images.png");
    // SpriteDef buttonSpriteDef = {"UI/ui_images.png", Rect{145, 81, 46, 14}, 46, 14};

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
        window.updateEvents();

        renderer.clear(SML::Color(200, 200, 0));

        renderer.drawRect(100, 100, 200, 200, SML::Color(0, 255, 0), true, 0);
        renderer.drawRect(100, 300, 200, 200, SML::Color(0, 0, 255), false, int(SML::Time::ticks / 10 * 2400) % 360,
                          SML::SML_Point(400, 400));
        renderer.drawRect(300, 100, 200, 200, SML::Color(255, 255, 0), false, int(SML::Time::ticks / 10 * 800) % 360,
                          SML::SML_Point(0, 0));

        renderer.setViewport(SML::Rect());

        renderer.drawRect(300, 300, 200, 200, SML::Color(255, 0, 255, 150), false,
                          int(SML::Time::ticks / 10 * 500) % 360, SML::SML_Point(0, 0));

        RGB hue = hueToRGB(int(SML::Time::ticks / 10 * 1000) % 360);
        // renderer.drawTexture(dinoTexture, SML::Rect(0, 0, 40, 40), 600, 600, 200, 200, false, false);
        // renderer.drawTexture(dinoTexture, SML::Rect(0, 0, 40, 40), 600, 600, 200, 200, false, false,
        //                      int(SML::Time::ticks / 10 * 1000) % 360, SML::Color(hue.r, hue.g, hue.b, 255));

        renderer.drawTexture(UITexture, SML::Rect(145, 81, 46, 14), 100, 100, 460, 140, false, false, 0);

        renderer.drawCircle(300, 300, 200, SML::Color(hue.r, hue.g, hue.b), false,
                            200 - (int(SML::Time::ticks / 10 * 1000) % 200));

        // renderer.drawChar(font.charSet['a'], 'a', 100, 100, 1.0f, SML::Color(255,
        // 255, 255)); renderer.renderText(font, "He", 100, 100, 1.0f,
        // SML::Color(255, 255, 255));
        std::string text = "Hello World! GGGG";
        std::string actualText = text.substr(0, int(SML::Time::ticks / 10 * 20) % text.length());
        renderer.renderText(font, actualText, 100, (int(SML::Time::ticks / 10 * 2000) % 800), 1.0f,
                            SML::Color(hue.r, hue.g, hue.b));

        renderer.show();

        bool* presses = window.getKeyPresses();

        for (int i = 0; i < 512; ++i)
        {
            // if (presses[i])
            // {
            //     std::cout << "Key Pressed: " << i << std::endl;
            // }
        }

        // wait 16ms to simulate 60fps
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    return 0;
}
