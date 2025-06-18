#pragma once

#include "Font.h"
#include "glad/glad.h"

#include "Color.h"
#include "Point.h"
#include "Shader.h"
#include "SimpleQuad.h"
#include "Texture.h"
#include "TexturedQuad.h"
#include "UnfilledBox.h"

#include "SML/FrameBuffer.h"

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
    void show() const;

    void drawChar(const Character& character, int x, int y, float scale, const Color& color);

    void renderText(const Font& font, const std::string& text, int x, int y, float scale, const Color& color);
    void drawTexture(const Texture& texture, const Rect& source, int x, int y, int width, int height,
                     bool flipX = false, bool flipY = false, float rotation = 0.0f,
                     const Color& colorFilter = Color(255, 255, 255, 255),
                     const SML_Point& rotationalCenter = SML_Point(INT_MAX, INT_MAX));
    void drawRect(int x, int y, int width, int height, const Color& color, bool fill = true, float rotation = 0.0f,
                  const SML_Point& rotationalCenter = SML_Point(INT_MAX, INT_MAX));
    void drawCircle(int x, int y, int radius, const Color& color, bool fill = true, int lineWidth = 1);

    void setViewport(const Rect& rect);

    Rect getViewport();
    SML_Point getViewportSize();
    SML_Point calculateTextSize(const Font& font, const std::string& text) const;

private:
    Window& window;

    Shader fontShader;
    Shader texturedQuadShader;
    Shader rectShader;
    Shader circleShader;
    Shader frameBufferShader;

    TexturedQuad texturedQuad;
    UnfilledBox unfilledBox;
    SimpleQuad simpleQuad;

    FrameBuffer frameBuffer;
};

} // namespace SML
