#pragma once

#include "Vector2.h"
#include <cstdint>
#include <string>
#include <vector>

namespace SML
{

class Texture
{
public:
    Texture();
    Texture(const std::string& filePath);
    Texture(const std::vector<char>& data, const Vector2& size);

    // Rule of Five
    Texture(const Texture& other);                // Copy constructor
    Texture& operator=(const Texture& other);     // Copy assignment
    Texture(Texture&& other) noexcept;            // Move constructor
    Texture& operator=(Texture&& other) noexcept; // Move assignment

    ~Texture();

    void activate() const;

    unsigned int getTextureID() const;
    Vector2 getSize() const;

private:
    void loadTexture();
    void freeTexture();

private:
    bool loaded;

    unsigned int mTextureID;

    std::string mFilePath;
    Vector2 mSize;
};

} // namespace SML
