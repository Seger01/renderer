#include "Texture.h"

#include <glad/glad.h>

#include <iostream>
#include <stb_image/stb_image.h>

namespace SML
{
Texture::Texture() : loaded(false) {}

Texture::Texture(const std::string& filePath) : mFilePath(filePath), loaded(false) { loadTexture(); }

Texture::Texture(const std::vector<char>& data, const Vector2& size) : mSize(size), loaded(false)
{
    // generate texture
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    unsigned int textureID;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, size.x, size.y, 0, GL_RED, GL_UNSIGNED_BYTE, data.data());
    // set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // glBindTexture(GL_TEXTURE_2D, textureID);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
    // glGenerateMipmap(GL_TEXTURE_2D);
    //
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //
    mTextureID = textureID;
    loaded = true;
}

void Texture::activate() const
{
    if (!loaded)
    {
        std::cerr << "Texture not loaded yet!" << std::endl;
        return;
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTextureID);

    // set pixelart settings
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

unsigned int Texture::getTextureID() const
{
    if (!loaded)
    {
        std::cerr << "Texture not loaded yet!" << std::endl;
        return 0;
    }

    return mTextureID;
}

Vector2 Texture::getSize() const
{
    if (!loaded)
    {
        std::cerr << "Texture not loaded yet!" << std::endl;
        return Vector2(0, 0);
    }

    return mSize;
}

void Texture::loadTexture()
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(mFilePath.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);

        mSize = Vector2(width, height);

        mTextureID = textureID;

        loaded = true;
    }
    else
    {
        std::cout << "Texture failed to load at path: " << mFilePath << std::endl;
        stbi_image_free(data);
    }
}

} // namespace SML
