#include "SML/Texture.h"

#include <SML/glad/glad.h>

#include <SML/stb_image/stb_image.h>
#include <iostream>

namespace SML
{

Texture::Texture() : loaded(false), mTextureID(0) {}

Texture::Texture(const std::string& filePath) : mFilePath(filePath), loaded(false), mTextureID(0) { loadTexture(); }

Texture::Texture(const std::vector<char>& data, const Vector2& size) : mSize(size), loaded(false), mTextureID(0)
{
    // (as before)
    std::cout << "Loading texture from data..." << std::endl;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, size.x, size.y, 0, GL_RED, GL_UNSIGNED_BYTE, data.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    loaded = true;
}

Texture::~Texture() { freeTexture(); }

void Texture::freeTexture()
{
    if (loaded && mTextureID != 0)
    {
        glDeleteTextures(1, &mTextureID);
        mTextureID = 0;
        loaded = false;
    }
}

// Copy constructor (deep copy)
Texture::Texture(const Texture& other) : mSize(other.mSize), mFilePath(other.mFilePath), loaded(false), mTextureID(0)
{
    if (other.loaded)
    {
        std::cout << "DEEP COPY VERY WRONG" << std::endl;
    }
}

// Copy assignment (deep copy)
Texture& Texture::operator=(const Texture& other)
{
    if (this == &other)
        return *this; // self-assignment check
    freeTexture();
    mSize = other.mSize;
    mFilePath = other.mFilePath;
    loaded = false;
    mTextureID = 0;
    if (other.loaded)
    {
        if (!other.mFilePath.empty())
        {
            loadTexture();
        }
    }
    return *this;
}

// Move constructor
Texture::Texture(Texture&& other) noexcept
    : mTextureID(other.mTextureID), mSize(std::move(other.mSize)), mFilePath(std::move(other.mFilePath)),
      loaded(other.loaded)
{
    other.mTextureID = 0;
    other.loaded = false;
}

// Move assignment
Texture& Texture::operator=(Texture&& other) noexcept
{
    if (this == &other)
        return *this;
    freeTexture();
    mTextureID = other.mTextureID;
    mSize = std::move(other.mSize);
    mFilePath = std::move(other.mFilePath);
    loaded = other.loaded;

    other.mTextureID = 0;
    other.loaded = false;
    return *this;
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
