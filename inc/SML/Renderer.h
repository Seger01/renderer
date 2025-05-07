#pragma once

#include "Font.h"
#include "glad/glad.h"

#include "Color.h"
#include "Point.h"
#include "Shader.h"
#include "Texture.h"
#include "TexturedQuad.h"
#include "UnfilledBox.h"

namespace SML
{

class Window;
class Rect;

class Renderer
{
public:
    Renderer(Window& window);
    virtual ~Renderer() = default;

    void clear(const Color& color);
    void show();

    void drawChar(const Character& character, int x, int y, float scale, const Color& color);

    void renderText(const Font& font, const std::string& text, int x, int y, float scale, const Color& color);
    void drawTexture(const Texture& texture, const Rect& source, int x, int y, int width, int height,
                     bool flipX = false, bool flipY = false, float rotation = 0.0f,
                     const Color& colorFilter = Color(255, 255, 255, 255),
                     const Point& rotationalCenter = Point(INT_MAX, INT_MAX));
    void drawRect(int x, int y, int width, int height, const Color& color, bool fill = true, float rotation = 0.0f,
                  const Point& rotationalCenter = Point(INT_MAX, INT_MAX));
    void drawCircle(int x, int y, int radius, const Color& color, bool fill = true, int lineWidth = 1);

    void setViewport(const Rect& rect);

    Rect getViewport();
    Point getViewportSize();

private:
    Window& window;

    Shader fontShader;
    Shader texturedQuadShader;
    Shader rectShader;
    Shader circleShader;

    TexturedQuad texturedQuad;
    UnfilledBox unfilledBox;
};

} // namespace SML
