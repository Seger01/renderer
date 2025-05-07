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
    virtual ~Texture() = default;

    void activate() const;

    unsigned int getTextureID() const;
    Vector2 getSize() const;

private:
    void loadTexture();

private:
    bool loaded;

    unsigned int mTextureID;

    std::string mFilePath;
    Vector2 mSize;
};

} // namespace SML
