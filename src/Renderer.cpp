#include "Renderer.h"

#include <glad/glad.h>

#include "Font.h"
#include "GLFW/glfw3.h"

#include "Window.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image/stb_image.h>

#include <string>

#include "Color.h"
#include "Rect.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "Window.h"

namespace SML
{
// : texturedQuadShader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl"),
//   rectShader("shaders/colored_rect/vertex_shader.glsl", "shaders/colored_rect/fragment_shader.glsl"),
//   circleShader("shaders/circle/vertex_shader.glsl", "shaders/circle/fragment_shader.glsl"),
//   fontShader("shaders/font_shader/vertex_shader.glsl", "shaders/font_shader/fragment_shader.glsl"), window(window)

Renderer::Renderer(Window& window) : window(window)
{
    const std::string texturedQuadVertexShader =
#include "vertex_shader.h"
        ;
    const std::string texturedQuadFragmentShader =
#include "fragment_shader.h"
        ;
    const std::string rectVertexShader =
#include "colored_rect/vertex_shader.h"
        ;
    const std::string rectFragmentShader =
#include "colored_rect/fragment_shader.h"
        ;
    const std::string circleVertexShader =
#include "circle/vertex_shader.h"
        ;
    const std::string circleFragmentShader =
#include "circle/fragment_shader.h"
        ;
    const std::string fontVertexShader =
#include "font_shader/vertex_shader.h"
        ;
    const std::string fontFragmentShader =
#include "font_shader/fragment_shader.h"
        ;

    texturedQuadShader = Shader(texturedQuadVertexShader, texturedQuadFragmentShader);
    rectShader = Shader(rectVertexShader, rectFragmentShader);
    circleShader = Shader(circleVertexShader, circleFragmentShader);
    fontShader = Shader(fontVertexShader, fontFragmentShader);

    texturedQuadShader.use();
    texturedQuadShader.setInt("texture1", 0);

    glDisable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::clear(const Color& color)
{
    glClearColor(color.normalize().r, color.normalize().g, color.normalize().b, color.normalize().a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::show() { glfwSwapBuffers(window.getWindow()); }

void Renderer::drawChar(const Character& character, int x, int y, float scale, const Color& color) {}

void Renderer::renderText(const Font& font, const std::string& text, int x, int y, float scale, const Color& color)
{
    texturedQuad.bindVAO();
    fontShader.use();
    fontShader.setInt("texture1", 0);

    Point viewportSize = getViewportSize();

    glm::mat4 projection = glm::ortho(0.0f, (float)viewportSize.x, (float)viewportSize.y, 0.0f, -1.0f, 1.0f);

    fontShader.setMat4("projection", projection);
    fontShader.setVec4("textColor",
                       glm::vec4(color.normalize().r, color.normalize().g, color.normalize().b, color.normalize().a));

    // Render glyph texture over quad
    for (const char& c : text)
    {
        const Character& ch = font.charSet[c];
        ch.texture.activate();

        glm::mat4 model = glm::mat4(1.0f);

        model = glm::translate(model, glm::vec3(x, y, 0.0f));
        int width = ch.Size.x * scale;
        int height = ch.Size.y * scale;

        model = glm::scale(model, glm::vec3(width, height, 1.0f));

        fontShader.setMat4("model", model);

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;

        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (ch.Advance >> 6) * scale; // * scale
    }
}

void Renderer::drawTexture(const Texture& texture, const Rect& source, int x, int y, int width, int height, bool flipX,
                           bool flipY, float rotation, const Color& colorFilter, const Point& rotationalCenter)
{
    texturedQuad.bindVAO();
    texture.activate();
    texturedQuadShader.use();
    texturedQuadShader.setInt("texture1", 0);

    Point viewportSize = getViewportSize();

    glm::mat4 projection = glm::ortho(0.0f, (float)viewportSize.x, (float)viewportSize.y, 0.0f, -1.0f, 1.0f);
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(x, y, 0.0f));

    // account for rotational center if given
    if (rotationalCenter.x != INT_MAX && rotationalCenter.y != INT_MAX)
        model =
            glm::translate(model, glm::vec3(rotationalCenter.x - (width / 2), rotationalCenter.y - (height / 2), 0.0f));

    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));

    // Reverse the rotational center translation
    if (rotationalCenter.x != INT_MAX && rotationalCenter.y != INT_MAX)
        model = glm::translate(
            model, glm::vec3(-(rotationalCenter.x - (width / 2)), -(rotationalCenter.y - (height / 2)), 0.0f));

    model = glm::scale(model, glm::vec3(width, height, 1.0f));

    texturedQuadShader.setMat4("model", model);
    texturedQuadShader.setMat4("projection", projection);

    if (source.w == 0 && source.h == 0)
    {
        texturedQuadShader.setVec4("source", glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
    }
    else
    {
        texturedQuadShader.setVec4(
            "source", glm::vec4(((float)source.x) / texture.getSize().x, ((float)source.y - 1) / texture.getSize().y,
                                (float)source.w / texture.getSize().x, (float)source.h / texture.getSize().y));
    }

    texturedQuadShader.setInt("flipX", flipX ? -1 : 1);
    texturedQuadShader.setInt("flipY", flipY ? 1 : -1);
    texturedQuadShader.setVec4("colorFilter", glm::vec4(colorFilter.normalize().r, colorFilter.normalize().g,
                                                        colorFilter.normalize().b, colorFilter.normalize().a));

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::drawRect(int x, int y, int width, int height, const Color& color, bool fill, float rotation,
                        const Point& rotationalCenter)
{
    if (fill)
        texturedQuad.bindVAO();
    else
        unfilledBox.bindVAO();

    Point viewportSize = getViewportSize();

    rectShader.use();

    glm::mat4 projection =
        glm::ortho(0.0f, static_cast<float>(viewportSize.x), static_cast<float>(viewportSize.y), 0.0f, -1.0f, 1.0f);
    glm::mat4 model = glm::mat4(1.0f);

    // Step 1: Translate to the rectangle's position
    model = glm::translate(model, glm::vec3(x, y, 0.0f));

    if (rotationalCenter.x != INT_MAX && rotationalCenter.y != INT_MAX)
        model =
            glm::translate(model, glm::vec3(rotationalCenter.x - (width / 2), rotationalCenter.y - (height / 2), 0.0f));

    // Step 3: Apply rotation around the z-axis
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));

    if (rotationalCenter.x != INT_MAX && rotationalCenter.y != INT_MAX)
        model = glm::translate(
            model, glm::vec3(-(rotationalCenter.x - (width / 2)), -(rotationalCenter.y - (height / 2)), 0.0f));

    // Step 5: Scale the rectangle to its proper size
    model = glm::scale(model, glm::vec3(width, height, 1.0f));

    // Set shader uniforms
    rectShader.setMat4("model", model);
    rectShader.setMat4("projection", projection);
    rectShader.setVec4("color",
                       glm::vec4(color.normalize().r, color.normalize().g, color.normalize().b, color.normalize().a));

    if (fill)
        glDrawArrays(GL_TRIANGLES, 0, 6);
    else
        glDrawArrays(GL_LINE_LOOP, 0, 4);
}

void Renderer::drawCircle(int x, int y, int radius, const Color& color, bool fill, int lineWidth)
{
    texturedQuad.bindVAO();

    Point viewportSize = getViewportSize();

    circleShader.use();

    glm::mat4 projection =
        glm::ortho(0.0f, static_cast<float>(viewportSize.x), static_cast<float>(viewportSize.y), 0.0f, -1.0f, 1.0f);
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(x, y, 0.0f));

    model = glm::scale(model, glm::vec3(radius, radius, 1.0f));

    // Set shader uniforms
    circleShader.setMat4("model", model);
    circleShader.setMat4("projection", projection);
    if (fill)
        circleShader.setFloat("innerRadius", 0.0f);
    else
        circleShader.setFloat("innerRadius", float(radius - lineWidth) / radius / 2);

    circleShader.setVec4("color",
                         glm::vec4(color.normalize().r, color.normalize().g, color.normalize().b, color.normalize().a));

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::setViewport(const Rect& rect)
{
    if (rect.w == 0 || rect.h == 0)
    {
        glViewport(0, 0, window.getWindowSize().x, window.getWindowSize().y);
        return;
    }

    glViewport(rect.x, window.getWindowSize().y - rect.y - rect.h, rect.w, rect.h);
}

Rect Renderer::getViewport()
{
    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    return Rect(viewport[0], viewport[1], viewport[2], viewport[3]);
}

Point Renderer::getViewportSize()
{
    Rect viewport = getViewport();
    return Point(viewport.w, viewport.h);
}

} // namespace SML
