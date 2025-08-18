#pragma once

#include <iostream>
#include <vector>

namespace SML
{

class FrameBuffer
{
public:
    FrameBuffer(unsigned int screenWidth, unsigned int screenHeight)
        : FBO(0), texture(0), width(screenWidth), height(screenHeight)
    {
        createFramebuffer(width, height);
    }

    ~FrameBuffer()
    {
        glDeleteFramebuffers(1, &FBO);
        glDeleteTextures(1, &texture);
    }

    void resize(unsigned int newWidth, unsigned int newHeight)
    {
        if (width == newWidth && height == newHeight)
            return;

        width = newWidth;
        height = newHeight;

        glDeleteFramebuffers(1, &FBO);
        glDeleteTextures(1, &texture);

        createFramebuffer(width, height);
    }

    void bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glViewport(0, 0, width, height);
    }

    void unbind(unsigned int windowWidth, unsigned int windowHeight) const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, windowWidth, windowHeight);
    }

    unsigned int getTexture() const { return texture; }

    unsigned int getFBO() const { return FBO; }

    unsigned int getWidth() const { return width; }

    unsigned int getHeight() const { return height; }

private:
    void createFramebuffer(unsigned int w, unsigned int h)
    {
        glGenFramebuffers(1, &FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
        }
        else
        {
            // std::cout << "Framebuffer created successfully!" << std::endl;
            // std::cout << "Size : " << w << ", " << h << std::endl;
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    unsigned int FBO, texture;
    unsigned int width, height;
};

} // namespace SML
