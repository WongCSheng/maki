
/*                                                                   includes
----------------------------------------------------------------------------- */
#include "Font.h"

#include <iostream>
#include "../Headers/STL_Header.h"
#include <ft2build.h>
#include <ext/matrix_clip_space.hpp>

#include "Engine/Shaders/ShaderLibrary.h"

#include FT_FREETYPE_H

/*--------------------------------------------------------------------------- */


/*  _________________________________________________________________________ */

unsigned int VAO, VBO;

std::map<char, Font::Character> Font::Characters{};
int Font::init()
{
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    Shaders->Font_Shader()->use();
    FT_Library ft;	//init the freetype library ft
    if (FT_Init_FreeType(&ft))
    {
        assert(ft != NULL);
        std::cout << "ERROR: Unable to init freetype library." << std::endl;

        return -1;
    }
    FT_Face face;	//load font as a face

    if (FT_New_Face(ft, "../fonts/kaorigel/KaoriGel.ttf", 0, &face))	//try to load KaoriGel font here
    {
        std::cout << "ERROR: KaoriGel not found!" << std::endl;
        return -1;
    }
    FT_Set_Pixel_Sizes(face, 0, 48);
    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
    {
        std::cout << "ERROR:FREETYPE: Failed to load Glyph" << std::endl;
        return -1;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        unsigned int font;
        glGenTextures(1, &font);
        glBindTexture(GL_TEXTURE_2D, font);
        std::cout << "font id is: " << font << std::endl;
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            font,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        Characters.insert(std::pair<char, Character>(c, character));
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    FT_Done_Face(face);
    FT_Done_FreeType(ft);


    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
    //glUniformMatrix4fv(glGetUniformLocation(GLApp::shdrpgms["font"].GetHandle(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    Shaders->Textured_Shader()->Send_Mat4("projection", projection);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return 1;
}


void Font::RenderText(ShaderLibrary& s, std::string text, float x, float y, float scale, glm::vec3 color)
{
    // activate corresponding render state	
    s.Font_Shader()->use();
    glm::mat3 mat_colours{
        {color.x, 0, 0},
        {0,color.y,0},
        {0,0,color.z}
    };
    float alpha = 0.6f;

    //s.Font_Shader()->Send_Mat4("textColor", mat_colours);
    glUniform3f(glGetUniformLocation(s.Font_Shader()->get_hdl(), "textColor"), color.x, color.y, color.z);
    glUniform1f(glGetUniformLocation(s.Font_Shader()->get_hdl(), "alpha"), alpha);
    //glUniform3f(glGetUniformLocation(s.GetHandle(), "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}