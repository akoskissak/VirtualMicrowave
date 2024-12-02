#include "text.h"
#include <iostream>

Text::Text(const std::string& fontPath, Shader* shaderProgram, int screenWidth, int screenHeight)
    : shaderProgram(shaderProgram), VBO(6 * 4 * sizeof(float))
{
    // Initialize FreeType library
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        throw std::runtime_error("Failed to initialize FreeType library");
    }

    // Load the font
    LoadCharacters(fontPath);
    FT_Done_FreeType(ft);

    // Configure VAO/VBO for text quads
    VAO.Bind();
    VBO.Bind();
    glBufferData(GL_ARRAY_BUFFER, 6 * 4 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
    VAO.LinkAttrib(VBO, 0, 4, GL_FLOAT, 4 * sizeof(float), (void*)0);
    VAO.Unbind();
    VBO.Unbind();

    // Create orthographic projection matrix
    for (int i = 0; i < 16; i++) ProjectionMatrix[i] = 0.0f;
    ProjectionMatrix[0] = 2.0f / screenWidth;
    ProjectionMatrix[5] = -2.0f / screenHeight;
    ProjectionMatrix[10] = -1.0f;
    ProjectionMatrix[12] = -1.0f;
    ProjectionMatrix[13] = 1.0f;
    ProjectionMatrix[15] = 1.0f;

    shaderProgram->Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID, "projection"), 1, GL_FALSE, ProjectionMatrix);
}

void Text::LoadCharacters(const std::string& fontPath) {
    FT_Library ft;
    FT_Face face;

    if (FT_Init_FreeType(&ft)) {
        throw std::runtime_error("Failed to initialize FreeType library");
    }
    if (FT_New_Face(ft, fontPath.c_str(), 0, &face)) {
        throw std::runtime_error("Failed to load font");
    }

    FT_Set_Pixel_Sizes(face, 0, 50);

    for (unsigned char c = 0; c < 128; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cerr << "Failed to load glyph: " << c << std::endl;
            continue;
        }


        Texture texture(face->glyph->bitmap, GL_TEXTURE_2D, GL_TEXTURE0);

        Character character = {
            texture,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            face->glyph->bitmap_left,
            face->glyph->bitmap_top,
            (GLuint)face->glyph->advance.x
        };
        Characters.insert(std::make_pair(c, character));
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void Text::RenderText(const std::string& text, float x, float y, float scale, float r, float g, float b) {
    shaderProgram->Activate();
    glUniform3f(glGetUniformLocation(shaderProgram->ID, "textColor"), r, g, b);

    VAO.Bind();

    for (char c : text) {
        Character ch = Characters[c];

        float xpos = x + ch.BearingX * scale;
        float ypos = y - (ch.Height - ch.BearingY) * scale;

        float w = ch.Width * scale;
        float h = ch.Height * scale;



        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos,     ypos,       0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 0.0f },

            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 0.0f },
            { xpos + w, ypos + h,   1.0f, 1.0f }
        };

        VBO.Bind();
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        glActiveTexture(GL_TEXTURE0);
        ch.Texture.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (ch.Advance >> 6) * scale;
    }

    VAO.Unbind();
    glBindTexture(GL_TEXTURE_2D, 0);
}
