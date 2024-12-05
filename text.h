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
    int Width;
    int Height;
    int BearingX;
    int BearingY;
    GLuint Advance;
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
    float ProjectionMatrix[16];
};

#endif // TEXT_H