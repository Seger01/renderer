#pragma once

#include "Rect.h"
#include "Texture.h"
#include <ft2build.h>
#include <iostream>
#include <string>
#include <vector>

#include FT_FREETYPE_H

#define CHAR_SET_SIZE 128

namespace SML
{

struct Character
{
    Texture texture;      // ID handle of the glyph texture
    Vector2 Size;         // Size of glyph
    Vector2 Bearing;      // Offset from baseline to left/top of glyph
    unsigned int Advance; // Horizontal offset to advance to next glyph
};

class Font
{
public:
    Font(const std::string& fontPath, int fontSize)
    {
        FT_Library ft;
        if (FT_Init_FreeType(&ft))
        {
            std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
            return;
        }

        FT_Face face;
        if (FT_New_Face(ft, fontPath.c_str(), 0, &face))
        {
            std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
            return;
        }

        FT_Set_Pixel_Sizes(face, 0, fontSize);

        // Load first 128 characters of ASCII set

        for (unsigned char c = 0; c < static_cast<unsigned char>(CHAR_SET_SIZE); c++)
        {
            // load character glyph
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }

            const std::vector<char> data(
                face->glyph->bitmap.buffer,
                face->glyph->bitmap.buffer + face->glyph->bitmap.width * face->glyph->bitmap.rows);

            Vector2 glyphSize(face->glyph->bitmap.width, face->glyph->bitmap.rows);

            charSet[c].texture = Texture(data, glyphSize);
            charSet[c].Size = glyphSize;
            charSet[c].Bearing = Vector2(face->glyph->bitmap_left, face->glyph->bitmap_top);
            charSet[c].Advance = static_cast<unsigned int>(face->glyph->advance.x);
        }

        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    }

    ~Font() {}

    Character charSet[CHAR_SET_SIZE];
};
} // namespace SML
