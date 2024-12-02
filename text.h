#ifndef TEXT_H
#define TEXT_H

#include <map>
#include <string>
#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"

struct Character {
    Texture Texture;
    int Width;            // Width of glyph
    int Height;           // Height of glyph
    int BearingX;         // Offset from baseline to left of glyph
    int BearingY;         // Offset from baseline to top of glyph
    GLuint Advance;       // Horizontal offset to advance to next glyph
};

class Text {
public:
    std::map<char, Character> Characters;
    Shader* shaderProgram;
    VAO VAO;
    VBO VBO;

    Text(const std::string& fontPath, Shader* shaderProgram, int screenWidth, int screenHeight);
    void RenderText(const std::string& text, float x, float y, float scale, float r, float g, float b);

private:
    void LoadCharacters(const std::string& fontPath);
    float ProjectionMatrix[16]; // Simple orthographic projection matrix
};

#endif // TEXT_H