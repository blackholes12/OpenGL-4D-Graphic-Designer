#pragma once
#include <map>
#include <ft2build.h>
#include <locale.h>
#include <cstdlib>
#include FT_FREETYPE_H

static int imax(int x, int y)
{
    return x > y ? x : y;
}

static int imin(int x, int y)
{
    return x < y ? x : y;
}

static int iabs(int x)
{
    return x > 0 ? x : -x;
}

struct Character {
    GLubyte* bytes;
    glm::ivec2 size;
    glm::ivec2 bearing;
    GLuint     advance;
};

static GLubyte checkImage3D0[128][128][128];

static char checkText[256];
static wchar_t wcheckText[256];
static bool isOpenDropDown = false;
static glm::ivec2 displacementOffset2d = glm::ivec2(0);
static bool isDisplaced = false;
static bool isMuskOf = false;
static glm::ivec2 scrollViewOffset2d = glm::ivec2(0);
static glm::ivec2 scrollViewSize2d = glm::ivec2(10000);

static bool is_overlap(glm::ivec2 offset1, glm::ivec2 size1, glm::ivec2 offset2, glm::ivec2 size2)
{
    return offset1.x + size1.x > offset2.x && offset1.y + size1.y > offset2.y && offset2.x + size2.x > offset1.x && offset2.y + size2.y > offset1.y;
}

static void get_overlap_zone(glm::ivec2* targetOffset, glm::ivec2* targetSize, glm::ivec2 offset1, glm::ivec2 size1, glm::ivec2 offset2, glm::ivec2 size2)
{
    *targetOffset = glm::ivec2(imax(offset1.x, offset2.x), imax(offset1.y, offset2.y));
    *targetSize = glm::ivec2(imin(offset1.x + size1.x, offset2.x + size2.x) - targetOffset->x, imin(offset1.y + size1.y, offset2.y + size2.y) - targetOffset->y);
}

class Text2D
{
    GLuint textureID;
    GLuint VAO, VBO;
    std::map<wchar_t, Character> characters;
    FT_Library ft;
    std::vector<FT_Face> faces;
public:
    wchar_t text[256];
    glm::ivec2 offset;
    glm::ivec2 size;
    int scale;
    int fontSize;
    glm::vec4 color;
    int arrangeType;
    bool isBold;
    Text2D(const wchar_t* text, int xOffset, int yOffset, int scale, int fontSize, glm::vec4 color, int arrangeType, bool isBold)
    {
        for (unsigned int i(0); text[i] != 0; i++)this->text[i] = text[i];
        this->offset = glm::ivec2(xOffset, yOffset);
        this->scale = scale;
        this->fontSize = fontSize;
        this->color = color;
        this->arrangeType = arrangeType;
        this->isBold = isBold;

        const char* filePathNames[4];
        if (this->isBold)filePathNames[0] = "resourcefile/fonts/arialbd.ttf", filePathNames[1] = "resourcefile/fonts/simsun.ttc", filePathNames[2] = "resourcefile/fonts/malgun.ttf", filePathNames[3] = "resourcefile/fonts/arial-unicode-ms.ttf";
        else filePathNames[0] = "resourcefile/fonts/arial.ttf", filePathNames[1] = "resourcefile/fonts/simsun.ttc", filePathNames[2] = "resourcefile/fonts/malgun.ttf", filePathNames[3] = "resourcefile/fonts/arial-unicode-ms.ttf";
        for (size_t i(0); i < 4; i++)
        {
            FT_Face face;
            if (FT_Init_FreeType(&this->ft))
                std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
            if (FT_New_Face(this->ft, filePathNames[i], 0, &face))
                std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
            FT_Set_Pixel_Sizes(face, 0, fontSize);
            FT_Select_Charmap(face, ft_encoding_unicode);
            this->faces.push_back(face);
        }
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        //setlocale(LC_ALL, "chs");

        this->size = glm::ivec2(0, fontSize);
        FT_Face face = this->faces[0];
        for (unsigned int i(0); text[i] != 0; i++)
        {
            unsigned int faceIndex(0);
            for (faceIndex = 0; faceIndex < 3; faceIndex++) { if (FT_Get_Char_Index(this->faces[faceIndex], text[i]) != 0)break; }
            face = this->faces[faceIndex];
            if (FT_Load_Char(face, text[i], FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            //std::cout<<face->bbox.yMax-face->bbox.yMin<<'\n';
            this->size.x += face->glyph->bitmap_left + (face->glyph->advance.x >> 6);
            Character character;
            GLubyte* bytes = new GLubyte[face->glyph->bitmap.width * face->glyph->bitmap.rows];
            for (int y(0); y < face->glyph->bitmap.rows; y++)
            {
                for (int x(0); x < face->glyph->bitmap.width; x++)
                {
                    unsigned int index(x + face->glyph->bitmap.width * y);
                    bytes[index] = (GLubyte)(face->glyph->bitmap.buffer[x + face->glyph->bitmap.width * y]);
                }
            }
            character.bytes = bytes;
            character.size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
            character.bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
            character.advance = face->glyph->advance.x;
            this->characters.insert({ text[i], character });
        }
        int finalOffsetX = face->glyph->bitmap.width - face->glyph->bitmap_left;
        //std::cout << size.x << '\n';
        float vertices[6][4] = {
                { -finalOffsetX, 0.f,    0.0f, 0.0f },
                { -finalOffsetX, -this->fontSize / 3 - this->size.y,       0.0f, 1.0f },
                { this->size.x + finalOffsetX, -this->fontSize / 3 - this->size.y,    1.0f, 1.0f },

                { -finalOffsetX, 0.f,    0.0f, 0.0f },
                { this->size.x + finalOffsetX, -this->fontSize / 3 - this->size.y,    1.0f, 1.0f },
                { this->size.x + finalOffsetX, 0.f, 1.0f, 0.0f }
        };

        // generate texture
        glGenTextures(1, &this->textureID);
        glBindTexture(GL_TEXTURE_2D, this->textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, this->size.x + 2 * finalOffsetX, this->size.y + this->fontSize / 3, 0, GL_RED, GL_UNSIGNED_BYTE, checkImage3D0);

        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int x(finalOffsetX);
        int y(0);
        for (unsigned int i(0); text[i] != 0; i++)
        {
            Character character = this->characters[text[i]];

            x += character.bearing.x;
            y = this->size.y - character.bearing.y;

            glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, character.size.x, character.size.y, GL_RED, GL_UNSIGNED_BYTE, character.bytes);
            // now advance cursors for next glyph
            x += character.advance >> 6; // bitshithis->ft by 6 to get value in pixels (1/64th times 2^6 = 64)
        }

        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
        glBindVertexArray(this->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, vertices, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void update0(const wchar_t* text)
    {
        for (unsigned int i(0); this->text[i] != 0; i++)this->text[i] = 0;
        for (unsigned int i(0); text[i] != 0; i++)
        {
            auto it = this->characters.find(text[i]);
            if (it == this->characters.end())
            {
                FT_Face face;
                unsigned int faceIndex(0);
                for (faceIndex = 0; faceIndex < 3; faceIndex++) { if (FT_Get_Char_Index(this->faces[faceIndex], text[i]) != 0)break; }
                face = this->faces[faceIndex];
                if (FT_Load_Char(face, text[i], FT_LOAD_RENDER))
                {
                    std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                    continue;
                }
                //std::cout<<face->bbox.yMax-face->bbox.yMin<<'\n';
                this->size.x += face->glyph->bitmap_left + (face->glyph->advance.x >> 6);
                Character character;
                GLubyte* bytes = new GLubyte[face->glyph->bitmap.width * face->glyph->bitmap.rows];
                for (int y(0); y < face->glyph->bitmap.rows; y++)
                {
                    for (int x(0); x < face->glyph->bitmap.width; x++)
                    {
                        unsigned int index(x + face->glyph->bitmap.width * y);
                        bytes[index] = (GLubyte)(face->glyph->bitmap.buffer[x + face->glyph->bitmap.width * y]);
                    }
                }
                character.bytes = bytes;
                character.size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
                character.bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
                character.advance = face->glyph->advance.x;
                this->characters.insert({ text[i], character });
            }
        }
        this->size = glm::ivec2(0, this->fontSize);
        Character character(this->characters[0]);
        for (unsigned int i(0); text[i] != 0; i++)
        {
            this->text[i] = text[i];
            character = this->characters[text[i]];
            this->size.x += character.bearing.x + (character.advance >> 6);
        }
        int finalOffsetX = character.size.x - character.bearing.x;
        //std::cout << size.x << '\n';
        float vertices[6][4] = {
                { -finalOffsetX, 0.f,    0.0f, 0.0f },
                { -finalOffsetX, -this->fontSize / 3 - this->size.y,       0.0f, 1.0f },
                { this->size.x + finalOffsetX, -this->fontSize / 3 - this->size.y,    1.0f, 1.0f },

                { -finalOffsetX, 0.f,    0.0f, 0.0f },
                { this->size.x + finalOffsetX, -this->fontSize / 3 - this->size.y,    1.0f, 1.0f },
                { this->size.x + finalOffsetX, 0.f, 1.0f, 0.0f }
        };

        glBindTexture(GL_TEXTURE_2D, this->textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, imax(this->size.x + 2 * finalOffsetX, 4), this->size.y + this->fontSize / 3, 0, GL_RED, GL_UNSIGNED_BYTE, checkImage3D0);

        int x(finalOffsetX);
        int y(0);
        for (unsigned int i(0); text[i] != 0; i++)
        {
            character = this->characters[text[i]];
            x += character.bearing.x;
            y = size.y - character.bearing.y;

            glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, character.size.x, character.size.y, GL_RED, GL_UNSIGNED_BYTE, character.bytes);
            // now advance cursors for next glyph
            x += character.advance >> 6; // bitshithis->ft by 6 to get value in pixels (1/64th times 2^6 = 64)
        }
        glBindVertexArray(this->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void update(const char* text)
    {
        for (unsigned int i(0); wcheckText[i] != 0; i++)wcheckText[i] = 0;
        for (unsigned int i(0); text[i] != 0; i++)wcheckText[i] = text[i];
        this->update0(wcheckText);
    }

    void update(const wchar_t* text)
    {
        for (unsigned int i(0); wcheckText[i] != 0; i++)wcheckText[i] = 0;
        for (unsigned int i(0); text[i] != 0; i++)wcheckText[i] = text[i];
        this->update0(wcheckText);
    }

    void update(const unsigned int* text)
    {
        for (unsigned int i(0); wcheckText[i] != 0; i++)wcheckText[i] = 0;
        for (unsigned int i(0); text[i] != 0; i++)wcheckText[i] = text[i];
        this->update0(wcheckText);
    }

    GLuint get_character_bearing_x(unsigned int index)
    {
        Character character(this->characters[this->text[index]]);
        return character.bearing.x;
    }

    GLuint get_character_advance(unsigned int index)
    {
        Character character(this->characters[this->text[index]]);
        return character.advance >> 6;
    }

    GLuint get_character_space(unsigned int index)
    {
        Character character(this->characters[this->text[index]]);
        return character.bearing.x + (character.advance >> 6);
    }

    void render(Shader& s)
    {
        // Activate the appropriate rendering state
        s.use();
        s.set_vec4f(this->color, "textColor");
        if (this->arrangeType == 0)s.set_vec2i(this->offset + glm::ivec2(-(this->size.x * this->scale) / 2, 0), "offset");
        else if (this->arrangeType == 1)s.set_vec2i(this->offset, "offset");
        s.set1i(this->scale, "scale");
        glActiveTexture(GL_TEXTURE0);
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, this->textureID);
        glBindVertexArray(this->VAO);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    ~Text2D()
    {
        // destroy FreeType once we're finished
        for (size_t i(0); i < this->faces.size(); i++)FT_Done_Face(this->faces[i]);
        FT_Done_FreeType(this->ft);
        for (std::pair<unsigned int, Character> charcter : this->characters)delete charcter.second.bytes;
        glDeleteTextures(1, &this->textureID);
        glDeleteVertexArrays(1, &this->VAO);
        glDeleteBuffers(1, &this->VBO);
    }
};

class Paragraph2D
{
    GLuint textureID;
    GLuint VAO, VBO;
    FT_Library ft;
    std::vector<FT_Face> faces;
    std::map<wchar_t, Character> characters;
public:
    wchar_t text[256];
    glm::ivec2 offset;
    glm::ivec2 size;
    int scale;
    int fontSize;
    glm::vec4 color;
    bool isBold;
    Paragraph2D(const wchar_t* text, int xOffset, int yOffset, int scale, int fontSize, int sizeX, int sizeY, glm::vec4 color, bool isBold)
    {
        for (unsigned int i(0); text != 0; i++)this->text[i] = text[i];
        this->offset = glm::ivec2(xOffset, yOffset);
        this->scale = scale;
        this->fontSize = fontSize;
        this->size = glm::ivec2(sizeX, sizeY);
        this->color = color;
        this->isBold = isBold;

        const char* filePathNames[2];
        if (this->isBold)filePathNames[0] = "resourcefile/fonts/arialbd.ttf", filePathNames[1] = "resourcefile/fonts/simsun.ttc";
        else filePathNames[0] = "resourcefile/fonts/arial.ttf", filePathNames[1] = "resourcefile/fonts/simsun.ttc";
        for (size_t i(0); i < 2; i++)
        {
            FT_Face face;
            if (FT_Init_FreeType(&this->ft))
                std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
            if (FT_New_Face(this->ft, filePathNames[i], 0, &face))
                std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
            FT_Set_Pixel_Sizes(face, 0, fontSize);
            FT_Select_Charmap(face, ft_encoding_unicode);
            this->faces.push_back(face);
        }
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        //setlocale(LC_ALL, "chs");
        FT_Face face = this->faces[0];
        for (int i(0); text[i] != 0; i++)
        {
            unsigned int faceIndex(0);
            for (unsigned int index = 0; index < 2; index++) { faceIndex = index;  if (FT_Get_Char_Index(this->faces[index], text[i]) != 0)break; }
            face = this->faces[faceIndex];
            if (FT_Load_Char(face, text[i], FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            Character character;
            GLubyte* bytes = new GLubyte[face->glyph->bitmap.width * face->glyph->bitmap.rows];
            for (int y(0); y < face->glyph->bitmap.rows; y++)
            {
                for (int x(0); x < face->glyph->bitmap.width; x++)
                {
                    unsigned int index(x + face->glyph->bitmap.width * y);
                    bytes[index] = (GLubyte)(face->glyph->bitmap.buffer[x + face->glyph->bitmap.width * y]);
                }
            }
            character.bytes = bytes;
            character.size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
            character.bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
            character.advance = face->glyph->advance.x;
            this->characters.insert({ text[i], character });
        }
        int finalOffsetX = face->glyph->bitmap.width - face->glyph->bitmap_left;
        //std::cout << size.x << '\n';
        float vertices[6][4] = {
                { -finalOffsetX, 0.f,    0.0f, 0.0f },
                { -finalOffsetX, -this->size.y,       0.0f, 1.0f },
                { this->size.x - finalOffsetX, -this->size.y,    1.0f, 1.0f },

                { -finalOffsetX, 0.f,    0.0f, 0.0f },
                { this->size.x - finalOffsetX, -this->size.y,    1.0f, 1.0f },
                { this->size.x - finalOffsetX, 0.f, 1.0f, 0.0f }
        };

        // generate texture
        glGenTextures(1, &this->textureID);
        glBindTexture(GL_TEXTURE_2D, this->textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, this->size.x, this->size.y, 0, GL_RED, GL_UNSIGNED_BYTE, checkImage3D0);

        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int x(finalOffsetX);
        int y(0);
        for (int i(0); text[i] != 0; i++)
        {
            Character character = this->characters[text[i]];

            int xPos = x + character.bearing.x;
            if (xPos + character.size.x + finalOffsetX > this->size.x)
            {
                x = finalOffsetX;
                xPos = x + character.bearing.x;
                y += 3 * this->fontSize / 2;
            }
            int yPos = y + this->fontSize - character.bearing.y;

            glTexSubImage2D(GL_TEXTURE_2D, 0, xPos, yPos, character.size.x, character.size.y, GL_RED, GL_UNSIGNED_BYTE, character.bytes);
            // now advance cursors for next glyph
            x += character.advance >> 6; // bitshithis->ft by 6 to get value in pixels (1/64th times 2^6 = 64)
        }

        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
        glBindVertexArray(this->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, vertices, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void update0(const wchar_t* text)
    {
        for (unsigned int i(0); this->text[i] != 0; i++)this->text[i] = 0;
        for (unsigned int i(0); text[i] != 0; i++)
        {
            auto it = this->characters.find(text[i]);
            if (it == this->characters.end())
            {
                FT_Face face;
                unsigned int faceIndex(0);
                for (unsigned int index = 0; index < 2; index++) { faceIndex = index;  if (FT_Get_Char_Index(this->faces[index], text[i]) != 0)break; }
                face = this->faces[faceIndex];
                if (FT_Load_Char(face, text[i], FT_LOAD_RENDER))
                {
                    std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                    continue;
                }
                //std::cout<<face->bbox.yMax-face->bbox.yMin<<'\n';
                this->size.x += face->glyph->bitmap_left + (face->glyph->advance.x >> 6);
                Character character;
                GLubyte* bytes = new GLubyte[face->glyph->bitmap.width * face->glyph->bitmap.rows];
                for (int y(0); y < face->glyph->bitmap.rows; y++)
                {
                    for (int x(0); x < face->glyph->bitmap.width; x++)
                    {
                        unsigned int index(x + face->glyph->bitmap.width * y);
                        bytes[index] = (GLubyte)(face->glyph->bitmap.buffer[x + face->glyph->bitmap.width * y]);
                    }
                }
                character.bytes = bytes;
                character.size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
                character.bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
                character.advance = face->glyph->advance.x;
                this->characters.insert({ text[i], character });
            }
        }
        Character character;
        for (unsigned int i(0); text[i] != 0; i++)
        {
            this->text[i] = text[i];
            character = this->characters[text[i]];
            //this->size.x += character.bearing.x + (character.advance >> 6);
        }
        int finalOffsetX = character.size.x - character.bearing.x;
        //std::cout << size.x << '\n';
        float vertices[6][4] = {
                { -finalOffsetX, 0.f,    0.0f, 0.0f },
                { -finalOffsetX, -this->size.y,       0.0f, 1.0f },
                { this->size.x - finalOffsetX, -this->size.y,    1.0f, 1.0f },

                { -finalOffsetX, 0.f,    0.0f, 0.0f },
                { this->size.x - finalOffsetX, -this->size.y,    1.0f, 1.0f },
                { this->size.x - finalOffsetX, 0.f, 1.0f, 0.0f }
        };

        glBindTexture(GL_TEXTURE_2D, this->textureID);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, this->size.x, this->size.y, GL_RED, GL_UNSIGNED_BYTE, checkImage3D0);

        int x(finalOffsetX);
        int y(0);
        for (unsigned int i(0); text[i] != 0; i++)
        {
            character = this->characters[text[i]];

            int xPos = x + character.bearing.x;
            if (xPos + character.size.x + finalOffsetX > this->size.x)
            {
                x = finalOffsetX;
                xPos = x + character.bearing.x;
                y += 3 * this->fontSize / 2;
            }
            int yPos = y + this->fontSize - character.bearing.y;

            glTexSubImage2D(GL_TEXTURE_2D, 0, xPos, yPos, character.size.x, character.size.y, GL_RED, GL_UNSIGNED_BYTE, character.bytes);
            // now advance cursors for next glyph
            x += character.advance >> 6; // bitshithis->ft by 6 to get value in pixels (1/64th times 2^6 = 64)
        }

        glBindVertexArray(this->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void update(const char* text)
    {
        for (unsigned int i(0); wcheckText[i] != 0; i++)wcheckText[i] = 0;
        for (unsigned int i(0); text[i] != 0; i++)wcheckText[i] = text[i];
        this->update0(wcheckText);
    }

    void update(const wchar_t* text)
    {
        for (unsigned int i(0); wcheckText[i] != 0; i++)wcheckText[i] = 0;
        for (unsigned int i(0); text[i] != 0; i++)wcheckText[i] = text[i];
        this->update0(wcheckText);
    }

    void update(const unsigned int* text)
    {
        for (unsigned int i(0); wcheckText[i] != 0; i++)wcheckText[i] = 0;
        for (unsigned int i(0); text[i] != 0; i++)wcheckText[i] = text[i];
        this->update0(wcheckText);
    }

    void render(Shader& s)
    {
        // Activate the appropriate rendering state
        s.use();
        s.set_vec4f(this->color, "textColor");
        s.set_vec2i(this->offset, "offset");
        s.set1i(this->scale, "scale");
        glActiveTexture(GL_TEXTURE0);
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, this->textureID);
        glBindVertexArray(this->VAO);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    ~Paragraph2D()
    {
        // destroy FreeType once we're finished
        for (size_t i(0); i < this->faces.size(); i++)FT_Done_Face(this->faces[i]);
        FT_Done_FreeType(this->ft);
        for (std::pair<unsigned int, Character> charcter : this->characters)delete charcter.second.bytes;
        glDeleteTextures(1, &this->textureID);
        glDeleteVertexArrays(1, &this->VAO);
        glDeleteBuffers(1, &this->VBO);
    }
};

class Rectangle2D
{
    GLuint VAO, VBO;
public:
    glm::ivec2 offset;
    glm::ivec2 size;
    int cornerRadious;
    int borderLineThickness;
    int textureId;
    glm::vec4 color;
    glm::vec4 borderColor;
    Rectangle2D(int xOffset, int yOffset, int sizeX, int sizeY, int cornerRadious, int borderLineThickness, int textureId, glm::vec4 color, glm::vec4 borderColor)
    {
        this->offset = glm::ivec2(xOffset, yOffset);
        this->size = glm::ivec2(sizeX, sizeY);
        this->cornerRadious = cornerRadious;
        this->borderLineThickness = borderLineThickness;
        this->textureId = textureId;
        this->color = color;
        this->borderColor = borderColor;

        float vertices[6][4] = {
               { 0.f, 0.f,             0.0f, 0.0f },
               { 0.f, -1.f,          0.0f, 1.0f },
               { 1.f, -1.f, 1.0f, 1.0f },

               { 0.f, 0.f,             0.0f, 0.0f },
               { 1.f, -1.f, 1.0f, 1.0f },
               { 1.f, 0.f,    1.0f, 0.0f }
        };

        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
        glBindVertexArray(this->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, vertices, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void render(Shader& s)
    {
        // Activate the appropriate rendering state
        s.use();
        s.set1i(this->cornerRadious, "cornerRadious");
        s.set1i(this->borderLineThickness, "borderLineThickness");
        s.set1i(this->textureId >= 0, "isUseTexture");
        if (this->textureId >= 0)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, this->textureId);
        }
        s.set_vec4f(this->color, "color");
        s.set_vec4f(this->borderColor, "borderColor");
        s.set_vec2i(this->size, "size");
        s.set_vec2i(this->offset, "offset");
        glBindVertexArray(this->VAO);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    ~Rectangle2D()
    {
        glDeleteVertexArrays(1, &this->VAO);
        glDeleteBuffers(1, &this->VBO);
    }
};

class ImageTextPair2D
{
public:
    Text2D* text2d;
    Rectangle2D* image2d;
    glm::ivec2 offset;
    int space;

    ImageTextPair2D(Text2D* text2d, Rectangle2D* image2d, glm::ivec2 offset, int space)
    {
        this->text2d = text2d;
        this->image2d = image2d;
        this->offset = offset;
        this->space = space;
    }

    glm::ivec2 getSize()
    {
        return glm::ivec2((this->image2d == nullptr ? 0 : this->image2d->size.x + this->space) + (this->text2d == nullptr ? 0 : this->text2d->size.x), (this->image2d == nullptr ? (this->text2d == nullptr ? 0 : 4 * this->text2d->size.y / 3) : this->image2d->size.y));
    }

    void render(Shader& textShader, Shader& rectangleShader)
    {
        if (this->image2d != nullptr)
        {
            this->image2d->offset = this->offset;
            this->image2d->render(rectangleShader);
        }
        if (this->text2d != nullptr)
        {
            this->text2d->offset = glm::ivec2((this->image2d == nullptr ? this->offset.x : this->offset.x + this->image2d->size.x + this->space), this->image2d == nullptr ? this->offset.y : this->offset.y + (this->image2d->size.y - 4 * this->text2d->size.y / 3) / 2);
            this->text2d->render(textShader);
        }
    }

    ~ImageTextPair2D()
    {
        delete this->text2d;
        delete this->image2d;
    }
};

class Lable2D
{
public:
    Rectangle2D* rectangle2d;
    Text2D* text2d;
    float recordTime;
    bool isUse;
    bool isDisplayed;
    Lable2D(Rectangle2D* rectangle2d, Text2D* text2d)
    {
        this->rectangle2d = rectangle2d;
        this->text2d = text2d;
        this->recordTime = 0.f;
        this->isUse = false;
        this->isDisplayed = false;
    }

    void interact(int mousePosX, int mousePosY, bool isOnRelease, bool isPress)
    {
        if (this->recordTime != 0.f)this->rectangle2d->offset = glm::ivec2(mousePosX + 20, mousePosY + 20);
    }

    void render(Shader& textShader, Shader& rectangleShader, const float dt)
    {
        if (this->isUse)
        {
            this->recordTime += dt;
            if (this->isDisplayed)this->recordTime = 1.125f;
            if (this->recordTime > 1.125f)this->recordTime = 1.125f, this->isDisplayed = true;
        }
        else
        {
            if (this->recordTime > 1.f)this->recordTime -= dt;
            else this->recordTime = 0.f, this->isDisplayed = false;
        }
        if (this->recordTime > 1.f)
        {

            float alpha(glm::min(1.f, 8.f * (this->recordTime - 1.f)));
            this->rectangle2d->color.w = this->rectangle2d->borderColor.w = alpha;
            this->rectangle2d->size.x = this->text2d->size.x + 20;
            this->rectangle2d->render(rectangleShader);
            this->text2d->color.w = alpha;
            this->text2d->offset = glm::ivec2(this->rectangle2d->offset.x + 10, (this->rectangle2d->size.y - 4 * this->text2d->size.y / 3) / 2 + this->rectangle2d->offset.y);
            this->text2d->render(textShader);
        }
    }

    ~Lable2D()
    {
        delete this->rectangle2d;
        delete this->text2d;
    }
};

static Lable2D* tip2d;

class Button2D
{
public:
    ImageTextPair2D* imageTextPair2d;
    Rectangle2D* rectangle2d;
    glm::vec4 regularColor;
    glm::vec4 contactColor;
    glm::vec4 clickColor;
    glm::vec4 regularBorderColor;
    glm::vec4 contactBorderColor;
    glm::vec4 clickBorderColor;
    int arrangeType;
    int space;
    bool isContact;
    bool isClick;
    bool isResponse;
    const wchar_t* tipText;
    Button2D(ImageTextPair2D* imageTextPair2d, Rectangle2D* rectangle2d, glm::vec4 contactColor, glm::vec4 clickColor, glm::vec4 contactBorderColor, glm::vec4 clickBorderColor, int arrangeType, int space, const wchar_t* tipText)
    {
        this->imageTextPair2d = imageTextPair2d;
        this->rectangle2d = rectangle2d;
        this->regularColor = rectangle2d->color;
        this->contactColor = contactColor;
        this->clickColor = clickColor;
        this->regularBorderColor = rectangle2d->borderColor;
        this->contactBorderColor = contactBorderColor;
        this->clickBorderColor = clickBorderColor;
        this->arrangeType = arrangeType;
        this->space = space;
        this->isContact = false;
        this->isClick = false;
        this->isResponse = false;
        this->tipText = tipText;
    }

    void interact(int mousePosX, int mousePosY, bool isOnRelease, bool isPress)
    {
        mousePosX -= this->rectangle2d->offset.x;
        mousePosY -= this->rectangle2d->offset.y;
        this->isContact =
            mousePosX >= 0 && mousePosX <= this->rectangle2d->size.x &&
            mousePosY >= 0 && mousePosY <= this->rectangle2d->size.y;
        if (this->isContact && !isOpenDropDown)
        {
            this->isClick = isPress;
            tip2d->isUse = true;
            if (tip2d->text2d->text != this->tipText)tip2d->text2d->update(this->tipText);
            this->isResponse = isOnRelease;
        }
        else
        {
            this->isContact = false;
            this->isClick = false;
            this->isResponse = false;
        }
    }

    void render(Shader& textShader, Shader& rectangleShader)
    {
        if (this->isContact)
        {
            if (this->isClick)
            {
                this->rectangle2d->color = this->clickColor;
                this->rectangle2d->borderColor = this->clickBorderColor;
            }
            else
            {
                this->rectangle2d->color = this->contactColor;
                this->rectangle2d->borderColor = this->contactBorderColor;
            }
        }
        else
        {
            this->rectangle2d->color = this->regularColor;
            this->rectangle2d->borderColor = this->regularBorderColor;
        }
        this->rectangle2d->render(*&rectangleShader);
        if (this->arrangeType == 0)this->imageTextPair2d->offset = this->rectangle2d->offset + (this->rectangle2d->size - this->imageTextPair2d->getSize()) / 2;
        else if (this->arrangeType == 1)this->imageTextPair2d->offset = this->rectangle2d->offset + glm::ivec2(this->space, (this->rectangle2d->size.y - this->imageTextPair2d->getSize().y) / 2);
        this->imageTextPair2d->render(*&textShader, *&rectangleShader);
    }

    ~Button2D()
    {
        delete this->rectangle2d;
        delete this->imageTextPair2d;
    }
};

class Checkbox2D
{
public:
    Text2D* name;
    Button2D* box;
    int space;
    bool value;
    Checkbox2D(Text2D* name, Button2D* box, int space)
    {
        this->name = name;
        this->box = box;
        this->space = space;
    }
    void interact(int mousePosX, int mousePosY, bool isOnRelease, bool isPress)
    {
        this->box->interact(mousePosX, mousePosY, isOnRelease, isPress);
    }

    void link_to_bool(bool* targetValue)
    {
        if (this->box->isResponse)
        {
            this->value = !this->value;
            *targetValue = this->value;
        }
        else
        {
            this->value = *targetValue;
        }
    }

    void render(Shader& textShader, Shader& rectangleShader)
    {
        this->name->render(textShader);
        if (this->value)this->box->imageTextPair2d->image2d->color.w = 1.f;
        else this->box->imageTextPair2d->image2d->color.w = 0.f;
        this->box->rectangle2d->offset = glm::ivec2(this->name->offset.x + this->space, this->name->offset.y + (4 * this->name->size.y / 3 - this->box->rectangle2d->size.y) / 2);
        this->box->render(textShader, rectangleShader);
    }

    ~Checkbox2D()
    {
        delete this->name;
        delete this->box;
    }
};

class InputText2D
{
public:
    Rectangle2D* inputBar;
    Text2D* targetText;
    Rectangle2D* block;
    Rectangle2D* cursorLine;
    int space;
    int offsetX;
    int selectPosition1;
    int selectPosition2;
    bool isSelect;
    bool isContact;
    bool isClick;
    bool isFirstClick;
    float recordTime;
    const wchar_t* tipText;
    InputText2D(Rectangle2D* inputBar, Text2D* targetText, Rectangle2D* block, Rectangle2D* cursorLine, int space, const wchar_t* tipText)
    {
        this->inputBar = inputBar;
        this->targetText = targetText;
        this->block = block;
        this->cursorLine = cursorLine;
        this->space = space;
        this->offsetX = 0;
        this->selectPosition1 = 0;
        this->selectPosition2 = 0;
        this->isSelect = false;
        this->isContact = false;
        this->isClick = false;
        this->isFirstClick = false;
        this->recordTime = 0.f;
        this->tipText = tipText;
    }

    unsigned int get_length_of_text()
    {
        unsigned int lengthOfText(0);
        for (unsigned int i(0); this->targetText->text[i] != 0; i++)
        {
            lengthOfText = i;
        }
        lengthOfText++;
        return lengthOfText;
    }

    unsigned int get_select_position(int offsetX)
    {
        int offsetX2(0);
        unsigned int lengthOfText(0);
        for (lengthOfText = 0; this->targetText->text[lengthOfText] != 0; lengthOfText++)
        {
            int width(this->targetText->get_character_space(lengthOfText));
            offsetX2 += width;
            if (offsetX2 - (int)this->targetText->get_character_advance(lengthOfText) / 2 > offsetX)return lengthOfText;
        }
        return lengthOfText;
    }

    int get_select_offset_x(unsigned int selectPosition)
    {
        int offsetX2(0);
        for (unsigned int i(0); i < selectPosition; i++)
        {
            offsetX2 += this->targetText->get_character_space(i);
        }
        return offsetX2;
    }

    void update_offset_x(int selectPosition)
    {
        int excessLeft(get_select_offset_x(selectPosition) + this->offsetX);
        int excessRight(get_select_offset_x(selectPosition) + this->offsetX + 2 * this->space - this->inputBar->size.x);
        if (excessRight > 0)this->offsetX -= excessRight;
        else if (excessLeft < 0) { if (selectPosition == 0) { this->offsetX = 0; } else { this->offsetX -= excessLeft; } }
    }

    void interact(int mousePosX, int mousePosY, bool isOnRelease, bool isPress, bool isOnPress)
    {
        mousePosX -= this->inputBar->offset.x;
        mousePosY -= this->inputBar->offset.y;
        this->isContact =
            mousePosX >= 0 && mousePosX <= this->inputBar->size.x &&
            mousePosY >= 0 && mousePosY <= this->inputBar->size.y;
        if (this->isContact) { tip2d->isUse = true; if (tip2d->text2d->text != this->tipText)tip2d->text2d->update(this->tipText); }
        if (isOnPress)
        {
            if (this->isContact)
            {
                if (this->isClick) this->selectPosition1 = this->selectPosition2 = get_select_position(mousePosX - this->space - this->offsetX);
                else this->selectPosition1 = 0, this->selectPosition2 = get_length_of_text(), this->isFirstClick = true;
                this->isClick = true;
                this->isSelect = true;
            }
            else
            {
                this->isClick = false;
                this->offsetX = 0;
            }
        }
        if (isOnRelease)
        {
            this->isSelect = false;
            this->isFirstClick = false;
        }
        if (this->isSelect)
        {
            if (!this->isFirstClick)this->selectPosition2 = get_select_position(mousePosX - this->space - this->offsetX);
            this->update_offset_x(this->selectPosition2);
            this->recordTime = 0.f;
        }
    }

    void erase_text(wchar_t index, unsigned int count)
    {
        for (unsigned int i(index); this->targetText->text[i] != 0; i++)
        {
            this->targetText->text[i] = this->targetText->text[i + count];
        }
        this->recordTime = 0.f;
    }

    void add_text(wchar_t c, unsigned int index)
    {
        for (unsigned int i(imin(get_length_of_text(), 254)); i > index; i--)
        {
            this->targetText->text[i] = this->targetText->text[i - 1];
        }
        this->targetText->text[index] = c;
        this->recordTime = 0.f;
    }

    void input_text(wchar_t c)
    {
        if (this->selectPosition1 != this->selectPosition2)
        {
            this->erase_text(imin(this->selectPosition1, this->selectPosition2), iabs(this->selectPosition2 - this->selectPosition1));
            update_offset_x(imin(this->selectPosition1, this->selectPosition2));
        }
        this->selectPosition1 = this->selectPosition2 = imin(this->selectPosition1, this->selectPosition2);
        if (this->selectPosition1 < 255)
        {
            add_text(c, this->selectPosition1);
            this->selectPosition1 = this->selectPosition2 = this->selectPosition1 + 1;
        }
        this->targetText->update(this->targetText->text);
        this->update_offset_x(this->selectPosition2);
    }

    void delete_text(bool isDrawBack)
    {
        if (this->selectPosition1 == this->selectPosition2)
        {
            if (isDrawBack)
            {
                if (this->selectPosition1 > 0)this->erase_text(imax(this->selectPosition1 - 1, 0), 1);
                this->selectPosition1 = this->selectPosition2 = imax(this->selectPosition1 - 1, 0);
            }
        }
        else
        {
            this->erase_text(imin(this->selectPosition1, this->selectPosition2), iabs(this->selectPosition2 - this->selectPosition1));
            this->selectPosition1 = this->selectPosition2 = imin(this->selectPosition1, this->selectPosition2);
        }
        this->targetText->update(this->targetText->text);
        this->update_offset_x(this->selectPosition2);
    }

    void move_cursor(bool isRight)
    {
        if (this->selectPosition1 == this->selectPosition2)
        {
            if (isRight)
            {
                if (this->targetText->text[this->selectPosition1] != 0)this->selectPosition1 = this->selectPosition2 = this->selectPosition1 + 1;
            }
            else
            {
                this->selectPosition1 = this->selectPosition2 = imax(this->selectPosition1 - 1, 0);
            }
        }
        else
        {
            this->selectPosition1 = this->selectPosition2;
        }
        this->update_offset_x(this->selectPosition2);
        this->recordTime = 0.f;
    }

    void render(Shader& textShader, Shader& rectangleShader, const float dt)
    {
        glm::ivec2 displacementOffset2d2(displacementOffset2d);
        bool isDisplaced2(isDisplaced);
        bool isMuskOf2(isMuskOf);
        glm::ivec2 scrollViewOffset2d2(scrollViewOffset2d);
        glm::ivec2 scrollViewSize2d2(scrollViewSize2d);
        displacementOffset2d = displacementOffset2d + glm::ivec2(this->inputBar->offset.x + this->offsetX, this->inputBar->offset.y);
        isDisplaced = true;
        isMuskOf = true;
        get_overlap_zone(&scrollViewOffset2d, &scrollViewSize2d, scrollViewOffset2d, scrollViewSize2d, displacementOffset2d2 + this->inputBar->offset, this->inputBar->size);
        this->inputBar->render(rectangleShader);
        rectangleShader.use();
        rectangleShader.set1i(isDisplaced, "isDisplaced");
        rectangleShader.set1i(isMuskOf, "isMaskOf");
        rectangleShader.set_vec2i(displacementOffset2d, "displacementOffset");
        rectangleShader.set_vec2i(scrollViewOffset2d, "scrollViewOffset");
        rectangleShader.set_vec2i(scrollViewSize2d, "scrollViewSize");
        textShader.use();
        textShader.set1i(isDisplaced, "isDisplaced");
        textShader.set1i(isMuskOf, "isMaskOf");
        textShader.set_vec2i(displacementOffset2d, "displacementOffset");
        textShader.set_vec2i(scrollViewOffset2d, "scrollViewOffset");
        textShader.set_vec2i(scrollViewSize2d, "scrollViewSize");
        this->targetText->offset = glm::ivec2(this->space, (this->inputBar->size.y - 4 * this->targetText->size.y / 3) / 2);
        this->targetText->render(textShader);
        if (this->isClick)
        {
            this->block->offset = glm::ivec2(this->space + get_select_offset_x(imin(this->selectPosition1, this->selectPosition2)), 0);
            this->block->size.x = get_select_offset_x(imax(this->selectPosition1, this->selectPosition2)) - get_select_offset_x(imin(this->selectPosition1, this->selectPosition2));
            this->block->render(rectangleShader);
            this->recordTime += dt;
            if (glm::fract(this->recordTime) < 0.5f)
            {
                this->cursorLine->offset = glm::ivec2(this->space + get_select_offset_x(this->selectPosition2)-1, 0);
                this->cursorLine->render(rectangleShader);
            }
        }
        displacementOffset2d = displacementOffset2d2;
        isDisplaced = isDisplaced2;
        isMuskOf = isMuskOf2;
        scrollViewOffset2d = scrollViewOffset2d2;
        scrollViewSize2d = scrollViewSize2d2;
        rectangleShader.use();
        rectangleShader.set1i(isDisplaced, "isDisplaced");
        rectangleShader.set1i(isMuskOf, "isMaskOf");
        rectangleShader.set_vec2i(displacementOffset2d, "displacementOffset");
        rectangleShader.set_vec2i(scrollViewOffset2d, "scrollViewOffset");
        rectangleShader.set_vec2i(scrollViewSize2d, "scrollViewSize");
        textShader.use();
        textShader.set1i(isDisplaced, "isDisplaced");
        textShader.set1i(isMuskOf, "isMaskOf");
        textShader.set_vec2i(displacementOffset2d, "displacementOffset");
        textShader.set_vec2i(scrollViewOffset2d, "scrollViewOffset");
        textShader.set_vec2i(scrollViewSize2d, "scrollViewSize");
    }

    ~InputText2D()
    {
        delete this->inputBar;
        delete this->targetText;
        delete this->block;
        delete this->cursorLine;
    }
};

class Slider2D
{
public:
    Text2D* name;
    Rectangle2D* bar;
    Rectangle2D* target;
    InputText2D* inputText;
    float value;
    float minValue;
    float maxValue;
    int type;
    bool isContact;
    bool isClick;
    const wchar_t* tipText;
    Slider2D(Text2D* name, Rectangle2D* bar, Rectangle2D* target, InputText2D* inputText, float minValue, float maxValue, int type, const wchar_t* tipText)
    {
        this->name = name;
        this->bar = bar;
        this->target = target;
        this->inputText = inputText;
        this->value = 0;
        this->minValue = minValue;
        this->maxValue = maxValue;
        this->type = type;
        this->isContact = false;
        this->isClick = false;
        this->tipText = tipText;
    }
    void interact(int mousePosX, int mousePosY, bool isOnRelease, bool isPress, bool isOnPress)
    {
        this->inputText->interact(mousePosX, mousePosY, isOnRelease, isPress, isOnPress);
        if (this->isContact) { tip2d->isUse = true; if (tip2d->text2d->text != this->tipText)tip2d->text2d->update(this->tipText); }
        if (!(this->bar == nullptr || this->target == nullptr))
        {
            mousePosX -= this->bar->offset.x;
            mousePosY -= this->target->offset.y;
            this->isContact =
                mousePosX >= 0 && mousePosX <= this->bar->size.x &&
                mousePosY >= 0 && mousePosY <= this->target->size.y;
            if (this->isContact)
            {
                this->isClick = isPress;
            }
            if (isOnRelease)
            {
                this->isClick = false;
            }
            if (this->isClick)
            {
                this->value = glm::mix(this->minValue, this->maxValue, glm::clamp((float)mousePosX / (float)this->bar->size.x, 0.f, 1.f));
            }
        }
        if (this->inputText->isClick)
        {
            for (unsigned int i(0); checkText[i] != 0; i++)
            {
                checkText[i] = 0;
            }
            for (unsigned int i(0); this->inputText->targetText->text[i] != 0; i++)
            {
                checkText[i] = this->inputText->targetText->text[i];
            }
            if (this->type == 0)this->value = glm::clamp(float(atof(checkText)), this->minValue, this->maxValue);
            else if (this->type == 1)this->value = glm::clamp(float(atoi(checkText)), this->minValue, this->maxValue);
        }
    }

    void link_to_float(float* targetValue)
    {
        if (this->isClick || this->inputText->isClick)*targetValue = this->value;
        else this->value = *targetValue;
        char ss[256];
        if (this->type == 0)sprintf(ss, "%f", *targetValue);
        else if (this->type == 1)sprintf(ss, "%i", (int)*targetValue);
        if (!this->inputText->isClick)this->inputText->targetText->update(ss);
    }

    void link_to_int(int* targetValue)
    {
        if (this->isClick || this->inputText->isClick)*targetValue = this->value;
        else this->value = *targetValue;
        char ss[256];
        if (this->type == 0)sprintf(ss, "%f", *targetValue);
        else if (this->type == 1)sprintf(ss, "%i", (int)*targetValue);
        if (!this->inputText->isClick)this->inputText->targetText->update(ss);
    }

    void link_to_uint(unsigned int* targetValue)
    {
        if (this->isClick || this->inputText->isClick)*targetValue = this->value;
        else this->value = *targetValue;
        char ss[256];
        if (this->type == 0)sprintf(ss, "%f", *targetValue);
        else if (this->type == 1)sprintf(ss, "%i", (int)*targetValue);
        if (!this->inputText->isClick)this->inputText->targetText->update(ss);
    }

    void render(Shader& textShader, Shader& rectangleShader, const float dt)
    {
        this->name->render(textShader);
        if (this->bar == nullptr || this->target == nullptr)
        {
            this->inputText->inputBar->offset = glm::ivec2(this->name->offset.x + this->name->size.x + 100, this->name->offset.y + (4 * this->name->size.y / 3 - this->inputText->inputBar->size.y) / 2);
        }
        else
        {
            this->bar->offset = glm::ivec2(this->name->offset.x + 100, this->name->offset.y + (4 * this->name->size.y / 3 - this->bar->size.y) / 2);
            this->bar->render(rectangleShader);
            this->target->offset = glm::ivec2(this->bar->offset.x - this->target->size.x / 2 + (int)((this->value - this->minValue) / (this->maxValue - this->minValue) * (float)this->bar->size.x), this->bar->offset.y + (this->bar->size.y - this->target->size.y) / 2);
            this->target->render(rectangleShader);
            this->inputText->inputBar->offset = glm::ivec2(this->bar->offset.x + this->bar->size.x + 10, this->bar->offset.y + (this->bar->size.y - this->inputText->inputBar->size.y) / 2);
        }
        this->inputText->render(textShader, rectangleShader, dt);
    }
    ~Slider2D()
    {
        delete this->name;
        delete this->bar;
        delete this->target;
        delete this->inputText;
    }
};

class DropDown2D
{
public:
    Text2D* name;
    Button2D* target;
    Rectangle2D* listBox;
    Button2D* listButton;
    std::vector<const wchar_t*> lists;
    bool isUse;
    int contactIndex;
    int clickIndex;
    int space;
    DropDown2D(Text2D* name, Button2D* target, Rectangle2D* listBox, Button2D* listButton, std::vector<const wchar_t*> lists, int index, int space)
    {
        this->name = name;
        this->target = target;
        this->listBox = listBox;
        this->listButton = listButton;
        this->lists = lists;
        this->isUse = false;
        this->contactIndex = -1;
        this->clickIndex = -1;
        this->space = space;
        this->target->imageTextPair2d->text2d->update(lists[index]);
    }

    void interact1(int mousePosX, int mousePosY, bool isOnRelease, bool isPress)
    {
        bool isOpenDropDown2(false);
        if ((this->isUse && isOpenDropDown))isOpenDropDown = false, isOpenDropDown2 = true;
        this->target->interact(mousePosX, mousePosY, isOnRelease, isPress);
        if ((this->isUse && isOpenDropDown2))isOpenDropDown = true;
        if (!this->target->isContact && isPress)this->isUse = false;
        else if (this->target->isResponse)this->isUse = !this->isUse;
    }

    void interact2(int mousePosX, int mousePosY, bool isOnRelease, bool isPress)
    {
        this->contactIndex = -1;
        this->clickIndex = -1;
        if (this->isUse) {
            glm::ivec2 listsPos(glm::ivec2(this->target->rectangle2d->offset.x, this->target->rectangle2d->offset.y + this->target->rectangle2d->size.y));
            for (size_t i(0); i < this->lists.size(); i++)
            {
                this->listButton->rectangle2d->offset = listsPos;
                this->listButton->interact(mousePosX, mousePosY, isOnRelease, isPress);
                if (this->listButton->isContact)this->contactIndex = i;
                if (this->listButton->isClick) { this->clickIndex = i; this->target->imageTextPair2d->text2d->update(lists[i]); }
                listsPos.y += this->listButton->rectangle2d->size.y;
            }
            mousePosX -= listsPos.x;
            mousePosY -= listsPos.y;
            if (mousePosX >= 0 && mousePosX <= this->listButton->rectangle2d->size.x &&
                mousePosY >= -(int)this->lists.size() * this->listButton->rectangle2d->size.y && mousePosY <= 0)isOpenDropDown = true;
        }
    }

    void render1(Shader& textShader, Shader& rectangleShader)
    {
        this->name->render(textShader);
        this->target->rectangle2d->offset = glm::ivec2(this->name->offset.x + this->space, this->name->offset.y + (4 * this->name->size.y / 3 - this->target->rectangle2d->size.y) / 2);
        this->target->render(textShader, rectangleShader);
    }

    void render2(Shader& textShader, Shader& rectangleShader)
    {
        if (this->isUse)
        {
            bool isMuskOf2(isMuskOf);
            isMuskOf = false;
            rectangleShader.use();
            rectangleShader.set1i(isMuskOf, "isMaskOf");
            textShader.use();
            textShader.set1i(isMuskOf, "isMaskOf");
            glm::ivec2 listsPos(glm::ivec2(this->target->rectangle2d->offset.x, this->target->rectangle2d->offset.y + this->target->rectangle2d->size.y));
            this->listBox->offset = listsPos;
            this->listBox->size = glm::ivec2(this->listButton->rectangle2d->size.x, this->lists.size() * this->listButton->rectangle2d->size.y);
            this->listBox->render(rectangleShader);
            for (size_t i(0); i < this->lists.size(); i++)
            {
                this->listButton->rectangle2d->offset = listsPos;
                this->listButton->imageTextPair2d->text2d->update(lists[i]);
                this->listButton->isContact = this->contactIndex == i;
                this->listButton->render(textShader, rectangleShader);
                listsPos.y += this->listButton->rectangle2d->size.y;
            }
            isMuskOf = isMuskOf2;
            rectangleShader.use();
            rectangleShader.set1i(isMuskOf, "isMaskOf");
            textShader.use();
            textShader.set1i(isMuskOf, "isMaskOf");
        }
    }

    ~DropDown2D()
    {
        delete this->name;
        delete this->target;
        delete this->listBox;
        delete this->listButton;
    }
};

class List2D
{
public:
    List2D()
    {

    }
    ~List2D()
    {

    }
};

class ScrollView2D
{
public:
    Rectangle2D* rectangle2d;
    Rectangle2D* sliderBackGround2d;
    Button2D* slider2d;
    Button2D* buttonTop2d;
    Button2D* buttonBottom2d;
    glm::ivec2 offset2d;
    glm::ivec2 size2d;
    int firstMousePosY;
    int firstOffsetY;
    bool isContact;
    bool isClick;
    bool isMoveUp;
    bool isMoveDown;
    glm::ivec2 displacementOffset2d2;
    bool isDisplaced2;
    bool isMuskOf2;
    glm::ivec2 scrollViewOffset2d2;
    glm::ivec2 scrollViewSize2d2;
    std::vector<Text2D*> texts2d;
    std::vector<Paragraph2D*> paragraphs2d;
    std::vector<Rectangle2D*> rectangles2d;
    std::vector<Button2D*> buttons2d;
    std::vector<Checkbox2D*> checkboxs2d;
    std::vector<Slider2D*> sliders2d;
    std::vector<DropDown2D*> drapdown2d;
    std::vector<InputText2D*> inputtexts2d;
    ScrollView2D(
        Rectangle2D* rectangle2d,
        Rectangle2D* sliderBackGround2d,
        Button2D* slider2d,
        Button2D* buttonTop2d,
        Button2D* buttonBottom2d,
        glm::ivec2 size2d,
        std::vector<Text2D*> texts2d,
        std::vector<Paragraph2D*> paragraphs2d,
        std::vector<Rectangle2D*> rectangles2d,
        std::vector<Button2D*> buttons2d,
        std::vector<Checkbox2D*> checkboxs2d,
        std::vector<Slider2D*> sliders2d,
        std::vector<DropDown2D*> drapdown2d,
        std::vector<InputText2D*> inputtexts2d)
    {
        this->rectangle2d = rectangle2d;
        this->sliderBackGround2d = sliderBackGround2d;
        this->slider2d = slider2d;
        this->buttonTop2d = buttonTop2d;
        this->buttonBottom2d = buttonBottom2d;
        this->offset2d = glm::ivec2(0);
        this->size2d = size2d;
        this->firstMousePosY = 0;
        this->firstOffsetY = 0;
        this->isContact = false;
        this->isClick = false;
        this->isMoveUp = false;
        this->isMoveDown = false;
        this->displacementOffset2d2 = glm::ivec2(0);
        this->isDisplaced2 = false;
        this->isMuskOf2 = false;
        this->scrollViewOffset2d2 = glm::ivec2(0);
        this->scrollViewSize2d2 = glm::ivec2(0);
        this->texts2d = texts2d;
        this->paragraphs2d = paragraphs2d;
        this->rectangles2d = rectangles2d;
        this->buttons2d = buttons2d;
        this->checkboxs2d = checkboxs2d;
        this->sliders2d = sliders2d;
        this->drapdown2d = drapdown2d;
        this->inputtexts2d = inputtexts2d;
    }

    void scroll(int scrollWheelAction)
    {
        if (this->size2d.y > this->rectangle2d->size.y)
        {
            if (this->isContact)
            {
                this->offset2d.y += 60 * scrollWheelAction;
                if (this->offset2d.y > 0)this->offset2d.y = 0;
                else if (this->offset2d.y < rectangle2d->size.y - this->size2d.y)this->offset2d.y = rectangle2d->size.y - this->size2d.y;
            }
        }
    }

    void interact1(int mousePosX, int mousePosY, bool isOnRelease, bool isPress, bool isOnPress, bool isMouseButton)
    {
        if (this->size2d.y > this->rectangle2d->size.y)
        {

            bool isMove(false);
            this->slider2d->interact(mousePosX, mousePosY, isOnRelease, isPress);
            this->buttonTop2d->interact(mousePosX, mousePosY, isOnRelease, isPress);
            if (this->buttonTop2d->isClick && isMouseButton) { if (!this->isMoveUp && !this->isMoveDown)this->offset2d.y += 20; isMove = true; }
            this->buttonBottom2d->interact(mousePosX, mousePosY, isOnRelease, isPress);
            if (this->buttonBottom2d->isClick && isMouseButton) { if (!this->isMoveUp && !this->isMoveDown)this->offset2d.y -= 20; isMove = true; }
            if (this->slider2d->isContact)
            {
                if (isOnPress)
                {
                    this->firstMousePosY = mousePosY;
                    this->firstOffsetY = this->offset2d.y;
                    this->isClick = true;
                }
            }
            if (!isOpenDropDown)
            {
                if (!this->slider2d->isContact && !isMove)
                {
                    if (isMouseButton)
                    {
                        if (mousePosX >= this->sliderBackGround2d->offset.x && mousePosX <= this->sliderBackGround2d->offset.x + this->sliderBackGround2d->size.x &&
                            mousePosY >= this->sliderBackGround2d->offset.y && mousePosY <= this->sliderBackGround2d->offset.y + this->sliderBackGround2d->size.y)
                        {
                            if (mousePosY < this->slider2d->rectangle2d->offset.y)
                            {
                                if (isOnPress)this->isMoveUp = true;
                                if (this->isMoveUp)this->offset2d.y += this->rectangle2d->size.y, isMove = true;
                            }
                            else if (mousePosY > this->slider2d->rectangle2d->offset.y + this->slider2d->rectangle2d->size.y)
                            {
                                if (isOnPress)this->isMoveDown = true;
                                if (this->isMoveDown)this->offset2d.y -= this->rectangle2d->size.y, isMove = true;
                            }
                        }
                    }
                }
                if (this->isClick && !isMove)
                {
                    int mouseOffsetY(mousePosY - this->firstMousePosY);
                    this->offset2d.y = this->firstOffsetY - this->size2d.y * mouseOffsetY / (this->rectangle2d->size.y - 48);
                }
            }
            if (this->offset2d.y > 0)this->offset2d.y = 0;
            else if (this->offset2d.y < rectangle2d->size.y - this->size2d.y)this->offset2d.y = rectangle2d->size.y - this->size2d.y;
            this->slider2d->rectangle2d->size.y = this->rectangle2d->size.y * (this->rectangle2d->size.y - 48) / this->size2d.y;
            this->slider2d->rectangle2d->offset = glm::ivec2(this->rectangle2d->offset.x + this->rectangle2d->size.x - this->slider2d->rectangle2d->size.x, this->rectangle2d->offset.y + 24 - (this->rectangle2d->size.y - 48) * this->offset2d.y / this->size2d.y);
        }
        else
        {
            this->offset2d.y = 0;
        }
        mousePosX -= this->rectangle2d->offset.x;
        mousePosY -= this->rectangle2d->offset.y;
        this->isContact =
            mousePosX >= 0 && mousePosX <= this->rectangle2d->size.x &&
            mousePosY >= 0 && mousePosY <= this->rectangle2d->size.y;
        mousePosX -= offset2d.x;
        mousePosY -= offset2d.y;
        for (Button2D* button2d : this->buttons2d)if (is_overlap(-this->offset2d, this->rectangle2d->size, button2d->rectangle2d->offset, button2d->rectangle2d->size)) { if (this->isContact)button2d->interact(mousePosX, mousePosY, isOnRelease, isPress); button2d->isContact = button2d->isContact && this->isContact; }
        for (Checkbox2D* checkbox2d : this->checkboxs2d)if (is_overlap(-this->offset2d, this->rectangle2d->size, checkbox2d->box->rectangle2d->offset, checkbox2d->box->rectangle2d->size)) { if (this->isContact)checkbox2d->interact(mousePosX, mousePosY, isOnRelease, isPress); checkbox2d->box->isContact = checkbox2d->box->isContact && this->isContact; }
        for (InputText2D* inputtext2d : this->inputtexts2d)if (is_overlap(-this->offset2d, this->rectangle2d->size, inputtext2d->inputBar->offset, inputtext2d->inputBar->size)) { if (this->isContact || inputtext2d->isClick)inputtext2d->interact(mousePosX, mousePosY, isOnRelease, isPress, isOnPress); }
        for (Slider2D* slider2d : this->sliders2d)if (is_overlap(-this->offset2d, this->rectangle2d->size, slider2d->target->offset, slider2d->target->size))if (this->isContact || slider2d->isClick) { slider2d->interact(mousePosX, mousePosY, isOnRelease, isPress, isOnPress); }
        for (DropDown2D* dropdown2d : this->drapdown2d)if (is_overlap(-this->offset2d, this->rectangle2d->size, dropdown2d->target->rectangle2d->offset, dropdown2d->target->rectangle2d->size)) { if (this->isContact || dropdown2d->isUse)dropdown2d->interact1(mousePosX, mousePosY, isOnRelease, isPress); dropdown2d->target->isContact = dropdown2d->target->isContact && this->isContact; }
        if (isOnPress)
        {
            if (!this->isContact)
            {
                for (Button2D* button2d : this->buttons2d)button2d->isClick = false;
                for (Checkbox2D* checkbox2d : this->checkboxs2d)checkbox2d->box->isClick = false;
                for (InputText2D* inputtext2d : this->inputtexts2d)inputtext2d->isClick = false, inputtext2d->offsetX = 0;
                for (Slider2D* slider2d : this->sliders2d)slider2d->isClick = false;
                for (DropDown2D* dropdown2d : this->drapdown2d)dropdown2d->isUse = false;
            }
            else
            {
                for (Button2D* button2d : this->buttons2d)if (!is_overlap(-this->offset2d, this->rectangle2d->size, button2d->rectangle2d->offset, button2d->rectangle2d->size)) { button2d->interact(mousePosX, mousePosY, isOnRelease, isPress); button2d->isContact = false; }
                for (Checkbox2D* checkbox2d : this->checkboxs2d)if (!is_overlap(-this->offset2d, this->rectangle2d->size, checkbox2d->box->rectangle2d->offset, checkbox2d->box->rectangle2d->size)) { checkbox2d->interact(mousePosX, mousePosY, isOnRelease, isPress); checkbox2d->box->isContact = false; }
                for (InputText2D* inputtext2d : this->inputtexts2d)if (!is_overlap(-this->offset2d, this->rectangle2d->size, inputtext2d->inputBar->offset, inputtext2d->inputBar->size)) { inputtext2d->isClick = false; }
                for (Slider2D* slider2d : this->sliders2d)if (!is_overlap(-this->offset2d, this->rectangle2d->size, slider2d->target->offset, slider2d->target->size)) { slider2d->isClick = false; }
                for (DropDown2D* dropdown2d : this->drapdown2d)if (!is_overlap(-this->offset2d, this->rectangle2d->size, dropdown2d->target->rectangle2d->offset, dropdown2d->target->rectangle2d->size)) { dropdown2d->isUse = false; }
            }
        }
        if (isOnRelease)
        {
            this->isMoveUp = this->isMoveDown = this->isClick = false;
        }
    }

    void interact2(int mousePosX, int mousePosY, bool isOnRelease, bool isPress, bool isOnPress, bool isMouseButton)
    {
        mousePosX -= this->rectangle2d->offset.x + offset2d.x;
        mousePosY -= this->rectangle2d->offset.y + offset2d.y;
        for (DropDown2D* dropdown2d : this->drapdown2d)if (is_overlap(-this->offset2d, this->rectangle2d->size, dropdown2d->target->rectangle2d->offset, dropdown2d->target->rectangle2d->size))if (this->isContact || dropdown2d->isUse)dropdown2d->interact2(mousePosX, mousePosY, isOnRelease, isPress);
    }

    void render1(Shader& textShader, Shader& rectangleShader, const float dt)
    {
        this->rectangle2d->render(rectangleShader);
        if (this->size2d.y > this->rectangle2d->size.y)
        {
            this->sliderBackGround2d->render(rectangleShader);
            this->slider2d->isContact = this->slider2d->isContact || this->isClick;
            this->slider2d->isClick = this->isClick;
            this->slider2d->render(textShader, rectangleShader);
            this->buttonTop2d->render(textShader, rectangleShader);
            this->buttonBottom2d->render(textShader, rectangleShader);
        }
        this->displacementOffset2d2 = displacementOffset2d;
        this->isDisplaced2 = isDisplaced;
        this->isMuskOf2 = isMuskOf;
        this->scrollViewOffset2d2 = scrollViewOffset2d;
        this->scrollViewSize2d2 = scrollViewSize2d;
        displacementOffset2d += this->rectangle2d->offset + this->offset2d;
        isDisplaced = true;
        isMuskOf = true;
        scrollViewOffset2d += this->rectangle2d->offset;
        scrollViewSize2d = this->rectangle2d->size;
        rectangleShader.use();
        rectangleShader.set1i(isDisplaced, "isDisplaced");
        rectangleShader.set1i(isMuskOf, "isMaskOf");
        rectangleShader.set_vec2i(displacementOffset2d, "displacementOffset");
        rectangleShader.set_vec2i(scrollViewOffset2d, "scrollViewOffset");
        rectangleShader.set_vec2i(scrollViewSize2d, "scrollViewSize");
        textShader.use();
        textShader.set1i(isDisplaced, "isDisplaced");
        textShader.set1i(isMuskOf, "isMaskOf");
        textShader.set_vec2i(displacementOffset2d, "displacementOffset");
        textShader.set_vec2i(scrollViewOffset2d, "scrollViewOffset");
        textShader.set_vec2i(scrollViewSize2d, "scrollViewSize");
        for (Rectangle2D* rectangle2d : this->rectangles2d)if (is_overlap(-this->offset2d, this->rectangle2d->size, rectangle2d->offset, rectangle2d->size))rectangle2d->render(rectangleShader);
        for (Button2D* button2d : this->buttons2d)if (is_overlap(-this->offset2d, this->rectangle2d->size, button2d->rectangle2d->offset, button2d->rectangle2d->size))button2d->render(textShader, rectangleShader);
        for (Checkbox2D* checkbox2d : this->checkboxs2d)if (is_overlap(-this->offset2d, this->rectangle2d->size, checkbox2d->box->rectangle2d->offset, checkbox2d->box->rectangle2d->size))checkbox2d->render(textShader, rectangleShader);
        for (Slider2D* slider2d : this->sliders2d)if (is_overlap(-this->offset2d, this->rectangle2d->size, slider2d->target->offset, slider2d->target->size))slider2d->render(textShader, rectangleShader, dt);
        for (Text2D* text2d : this->texts2d)if (is_overlap(-this->offset2d, this->rectangle2d->size, text2d->offset, glm::ivec2(text2d->size.x, 4 * text2d->size.y / 3)))text2d->render(textShader);
        for (Paragraph2D* paragraph2d : this->paragraphs2d)if (is_overlap(-this->offset2d, this->rectangle2d->size, rectangle2d->offset, rectangle2d->size))paragraph2d->render(textShader);
        for (DropDown2D* dropdown2d : this->drapdown2d)if (is_overlap(-this->offset2d, this->rectangle2d->size, dropdown2d->target->rectangle2d->offset, dropdown2d->target->rectangle2d->size))dropdown2d->render1(textShader, rectangleShader);
        for (InputText2D* inputtext2d : this->inputtexts2d)if (is_overlap(-this->offset2d, this->rectangle2d->size, inputtext2d->inputBar->offset, inputtext2d->inputBar->size))inputtext2d->render(textShader, rectangleShader, dt);
    }
    void render2(Shader& textShader, Shader& rectangleShader, const float dt)
    {
        for (DropDown2D* dropdown2d : this->drapdown2d)if (is_overlap(-this->offset2d, this->rectangle2d->size, dropdown2d->target->rectangle2d->offset, dropdown2d->target->rectangle2d->size))dropdown2d->render2(textShader, rectangleShader);
        displacementOffset2d = this->displacementOffset2d2;
        isDisplaced = this->isDisplaced2;
        isMuskOf = this->isMuskOf2;
        scrollViewOffset2d = this->scrollViewOffset2d2;
        scrollViewSize2d = this->scrollViewSize2d2;
        rectangleShader.use();
        rectangleShader.set1i(isDisplaced, "isDisplaced");
        rectangleShader.set1i(isMuskOf, "isMaskOf");
        rectangleShader.set_vec2i(displacementOffset2d, "displacementOffset");
        rectangleShader.set_vec2i(scrollViewOffset2d, "scrollViewOffset");
        rectangleShader.set_vec2i(scrollViewSize2d, "scrollViewSize");
        textShader.use();
        textShader.set1i(isDisplaced, "isDisplaced");
        textShader.set1i(isMuskOf, "isMaskOf");
        textShader.set_vec2i(displacementOffset2d, "displacementOffset");
        textShader.set_vec2i(scrollViewOffset2d, "scrollViewOffset");
        textShader.set_vec2i(scrollViewSize2d, "scrollViewSize");
    }
    ~ScrollView2D()
    {
        delete this->rectangle2d;
        delete this->sliderBackGround2d;
        delete this->slider2d;
        delete this->buttonTop2d;
        delete this->buttonBottom2d;
        for (Text2D* i : this->texts2d)delete i;
        for (Paragraph2D* i : this->paragraphs2d)delete i;
        for (Rectangle2D* i : this->rectangles2d)delete i;
        for (Button2D* i : this->buttons2d)delete i;
        for (Checkbox2D* i : this->checkboxs2d)delete i;
        for (Slider2D* i : this->sliders2d)delete i;
        for (DropDown2D* i : this->drapdown2d)delete i;
        for (InputText2D* i : this->inputtexts2d)delete i;
    }
};
class LoadBar2D
{
public:
    ImageTextPair2D* bar2d;
    Rectangle2D* filledArea;
    float value;
    LoadBar2D(ImageTextPair2D* bar2d, Rectangle2D* filledArea)
    {
        this->bar2d = bar2d;
        this->filledArea = filledArea;
        this->value = 0.f;
    }

    void update(float targetValue, char* text)
    {
        this->value = targetValue;
        this->filledArea->size.x = this->value * this->bar2d->image2d->size.x;
        this->bar2d->text2d->update(text);
    }

    void render(Shader& textShader, Shader& rectangleShader)
    {
        this->bar2d->render(textShader, rectangleShader);
        this->filledArea->offset = this->bar2d->offset;
        this->filledArea->render(rectangleShader);
    }
    ~LoadBar2D()
    {
        delete this->bar2d;
        delete this->filledArea;
    }
};

//void window_focus_callback(GLFWwindow* window, int focused)
//{
//    std::cout << focused << '\n';
//}
//
//void set_callback(GLFWwindow* window)
//{
//    glfwSetWindowFocusCallback(window, window_focus_callback);
//}

class Page2D
{
public:
    std::vector<Text2D*> texts2d;
    std::vector<Paragraph2D*> paragraphs2d;
    std::vector<Rectangle2D*> rectangles2d;
    std::vector<Button2D*> buttons2d;
    std::vector<Checkbox2D*> checkboxs2d;
    std::vector<Slider2D*> sliders2d;
    std::vector<DropDown2D*> drapdown2d;
    std::vector<InputText2D*> inputtexts2d;
    std::vector <ScrollView2D*> scrollView2d;
    Page2D(
        std::vector<Text2D*> texts2d,
        std::vector<Paragraph2D*> paragraphs2d,
        std::vector<Rectangle2D*> rectangles2d,
        std::vector<Button2D*> buttons2d,
        std::vector<Checkbox2D*> checkboxs2d,
        std::vector<Slider2D*> sliders2d,
        std::vector<DropDown2D*> drapdown2d,
        std::vector<InputText2D*> inputtexts2d,
        std::vector<ScrollView2D*> scrollView2d)
    {
        this->texts2d = texts2d;
        this->paragraphs2d = paragraphs2d;
        this->rectangles2d = rectangles2d;
        this->buttons2d = buttons2d;
        this->checkboxs2d = checkboxs2d;
        this->sliders2d = sliders2d;
        this->drapdown2d = drapdown2d;
        this->inputtexts2d = inputtexts2d;
        this->scrollView2d = scrollView2d;
    }

    void interact1(int mousePosX, int mousePosY, bool isOnRelease, bool isPress, bool isOnPress, bool isMouseButton)
    {
        for (Button2D* button2d : this->buttons2d)button2d->interact(mousePosX, mousePosY, isOnRelease, isPress);
        for (Checkbox2D* checkbox2d : this->checkboxs2d)checkbox2d->interact(mousePosX, mousePosY, isOnRelease, isPress);
        for (InputText2D* inputtext2d : this->inputtexts2d)inputtext2d->interact(mousePosX, mousePosY, isOnRelease, isPress, isOnPress);
        for (Slider2D* slider2d : this->sliders2d)slider2d->interact(mousePosX, mousePosY, isOnRelease, isPress, isOnPress);
        for (DropDown2D* dropdown2d : this->drapdown2d)dropdown2d->interact1(mousePosX, mousePosY, isOnRelease, isPress);
        for (ScrollView2D* scrollView2d : this->scrollView2d)scrollView2d->interact1(mousePosX, mousePosY, isOnRelease, isPress, isOnPress, isMouseButton);
    }

    void interact2(int mousePosX, int mousePosY, bool isOnRelease, bool isPress, bool isOnPress, bool isMouseButton)
    {
        for (DropDown2D* dropdown2d : this->drapdown2d)dropdown2d->interact2(mousePosX, mousePosY, isOnRelease, isPress);
        for (ScrollView2D* scrollView2d : this->scrollView2d)scrollView2d->interact2(mousePosX, mousePosY, isOnRelease, isPress, isOnPress, isMouseButton);
    }

    void input_text(wchar_t c)
    {
        for (InputText2D* inputtext2d : this->inputtexts2d)if (inputtext2d->isClick)inputtext2d->input_text(c);
        for (Slider2D* slider2d : this->sliders2d)if (slider2d->inputText->isClick)slider2d->inputText->input_text(c);
        for (ScrollView2D* scrollView2d : this->scrollView2d) {
            for (InputText2D* inputtext2d : scrollView2d->inputtexts2d)if (inputtext2d->isClick)inputtext2d->input_text(c);
            for (Slider2D* slider2d : scrollView2d->sliders2d)if (slider2d->inputText->isClick)slider2d->inputText->input_text(c);
        }
    }

    void delete_text(bool isDrawBack)
    {
        for (InputText2D* inputtext2d : this->inputtexts2d)if (inputtext2d->isClick)inputtext2d->delete_text(isDrawBack);
        for (Slider2D* slider2d : this->sliders2d)if (slider2d->inputText->isClick)slider2d->inputText->delete_text(isDrawBack);
        for (ScrollView2D* scrollView2d : this->scrollView2d) {
            for (InputText2D* inputtext2d : scrollView2d->inputtexts2d)if (inputtext2d->isClick)inputtext2d->delete_text(isDrawBack);
            for (Slider2D* slider2d : scrollView2d->sliders2d)if (slider2d->inputText->isClick)slider2d->inputText->delete_text(isDrawBack);
        }
    }

    void move_cursor(bool isRight)
    {
        for (InputText2D* inputtext2d : this->inputtexts2d)if (inputtext2d->isClick)inputtext2d->move_cursor(isRight);
        for (Slider2D* slider2d : this->sliders2d)if (slider2d->inputText->isClick)slider2d->inputText->move_cursor(isRight);
        for (ScrollView2D* scrollView2d : this->scrollView2d) {
            for (InputText2D* inputtext2d : scrollView2d->inputtexts2d)if (inputtext2d->isClick)inputtext2d->move_cursor(isRight);
            for (Slider2D* slider2d : scrollView2d->sliders2d)if (slider2d->inputText->isClick)slider2d->inputText->move_cursor(isRight);
        }
    }

    void scroll(int scrollWheelAction)
    {
        for (ScrollView2D* scrollView2d : this->scrollView2d)scrollView2d->scroll(scrollWheelAction);
    }

    void render1(Shader& textShader, Shader& rectangleShader, const float dt)
    {
        for (Rectangle2D* rectangle2d : this->rectangles2d)rectangle2d->render(rectangleShader);
        for (Button2D* button2d : this->buttons2d)button2d->render(textShader, rectangleShader);
        for (Checkbox2D* checkbox2d : this->checkboxs2d)checkbox2d->render(textShader, rectangleShader);
        for (Slider2D* slider2d : this->sliders2d)slider2d->render(textShader, rectangleShader, dt);
        for (Text2D* text2d : this->texts2d)text2d->render(textShader);
        for (Paragraph2D* paragraph2d : this->paragraphs2d)paragraph2d->render(textShader);
        for (DropDown2D* dropdown2d : this->drapdown2d)dropdown2d->render1(textShader, rectangleShader);
        for (InputText2D* inputtext2d : this->inputtexts2d)inputtext2d->render(textShader, rectangleShader, dt);
        for (ScrollView2D* scrollView2d : this->scrollView2d)scrollView2d->render1(textShader, rectangleShader, dt);
    }

    void render2(Shader& textShader, Shader& rectangleShader, const float dt)
    {
        for (DropDown2D* dropdown2d : this->drapdown2d)dropdown2d->render2(textShader, rectangleShader);
        for (ScrollView2D* scrollView2d : this->scrollView2d)scrollView2d->render2(textShader, rectangleShader, dt);
    }

    ~Page2D()
    {
        for (Text2D* i : this->texts2d)delete i;
        for (Paragraph2D* i : this->paragraphs2d)delete i;
        for (Rectangle2D* i : this->rectangles2d)delete i;
        for (Button2D* i : this->buttons2d)delete i;
        for (Checkbox2D* i : this->checkboxs2d)delete i;
        for (Slider2D* i : this->sliders2d)delete i;
        for (DropDown2D* i : this->drapdown2d)delete i;
        for (InputText2D* i : this->inputtexts2d)delete i;
        for (ScrollView2D* i : this->scrollView2d)delete i;
    }
};

class Pages2D
{
public:
    std::vector<Page2D*> pages2D;
    size_t index;
    Pages2D(std::vector<Page2D*> pages2D)
    {
        this->pages2D = pages2D;
        this->index = 0;
    }

    void interact1(int mousePosX, int mousePosY, bool isOnRelease, bool isPress, bool isOnPress, bool isMouseButton)
    {
        this->pages2D[this->index]->interact1(mousePosX, mousePosY, isOnRelease, isPress, isOnPress, isMouseButton);
    }

    void interact2(int mousePosX, int mousePosY, bool isOnRelease, bool isPress, bool isOnPress, bool isMouseButton)
    {
        this->pages2D[this->index]->interact2(mousePosX, mousePosY, isOnRelease, isPress, isOnPress, isMouseButton);
    }

    void input_text(wchar_t c)
    {
        this->pages2D[this->index]->input_text(c);
    }

    void delete_text(bool isDrawBack)
    {
        this->pages2D[this->index]->delete_text(isDrawBack);
    }

    void move_cursor(bool isRight)
    {
        this->pages2D[this->index]->move_cursor(isRight);
    }

    void scroll(int scrollWheelAction)
    {
        this->pages2D[this->index]->scroll(scrollWheelAction);
    }

    void render1(Shader& textShader, Shader& rectangleShader, const float dt)
    {
        this->pages2D[this->index]->render1(textShader, rectangleShader, dt);
    }

    void render2(Shader& textShader, Shader& rectangleShader, const float dt)
    {
        this->pages2D[this->index]->render2(textShader, rectangleShader, dt);
    }

    ~Pages2D()
    {
        for (Page2D* i : this->pages2D)delete i;
    }
};

class Canvas2D
{
    int arrangeType;
    float recordTime;
    bool isClick;
    int mousePosX;
    int mousePosY;
    bool isOnRelease;
    bool isPress;
    bool isOnPress;
    bool isMouseButton;
public:
    std::vector<Text2D*> texts2d;
    std::vector<Paragraph2D*> paragraphs2d;
    std::vector<Rectangle2D*> rectangles2d;
    std::vector<Button2D*> buttons2d;
    std::vector<Checkbox2D*> checkboxs2d;
    std::vector<Slider2D*> sliders2d;
    std::vector<DropDown2D*> drapdown2d;
    std::vector<InputText2D*> inputtexts2d;
    std::vector <ScrollView2D*> scrollView2d;
    std::vector< Pages2D*> pages2d;
    Canvas2D(std::vector<Text2D*> texts2d,
        std::vector<Paragraph2D*> paragraphs2d,
        std::vector<Rectangle2D*> rectangles2d,
        std::vector<Button2D*> buttons2d,
        std::vector<Checkbox2D*> checkboxs2d,
        std::vector<Slider2D*> sliders2d,
        std::vector<DropDown2D*> drapdown2d,
        std::vector<InputText2D*> inputtexts2d,
        std::vector <ScrollView2D*> scrollView2d,
        std::vector< Pages2D*> pages2d,
        int arrangeType)
    {
        this->texts2d = texts2d;
        this->paragraphs2d = paragraphs2d;
        this->rectangles2d = rectangles2d;
        this->buttons2d = buttons2d;
        this->checkboxs2d = checkboxs2d;
        this->sliders2d = sliders2d;
        this->drapdown2d = drapdown2d;
        this->inputtexts2d = inputtexts2d;
        this->scrollView2d = scrollView2d;
        this->pages2d = pages2d;
        this->arrangeType = arrangeType;
        this->recordTime = recordTime;
        this->isClick = false;
    }

    //void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    //{
    //    std::cout << this->texts2d.size() << '\n';
    //};
    //
    //void set_callback2(GLFWwindow* window)
    //{
    //    glfwSetKeyCallback(window, key_callback);
    //}

    void interact1()
    {
        tip2d->isUse = false;
        for (Button2D* button2d : this->buttons2d)button2d->interact(this->mousePosX, this->mousePosY, this->isOnRelease, this->isPress);
        for (Checkbox2D* checkbox2d : this->checkboxs2d)checkbox2d->interact(this->mousePosX, this->mousePosY, this->isOnRelease, this->isPress);
        for (InputText2D* inputtext2d : this->inputtexts2d)inputtext2d->interact(this->mousePosX, this->mousePosY, this->isOnRelease, this->isPress, this->isOnPress);
        for (Slider2D* slider2d : this->sliders2d)slider2d->interact(this->mousePosX, this->mousePosY, this->isOnRelease, this->isPress, this->isOnPress);
        for (DropDown2D* dropdown2d : this->drapdown2d)dropdown2d->interact1(this->mousePosX, this->mousePosY, this->isOnRelease, this->isPress);
        for (ScrollView2D* scrollView2d : this->scrollView2d)scrollView2d->interact1(this->mousePosX, this->mousePosY, this->isOnRelease, this->isPress, this->isOnPress, this->isMouseButton);
        for (Pages2D* pages2d : this->pages2d)pages2d->interact1(this->mousePosX, this->mousePosY, this->isOnRelease, this->isPress, this->isOnPress, this->isMouseButton);
        tip2d->interact(this->mousePosX, this->mousePosY, this->isOnRelease, this->isPress);
    }

    void interact2(int framebufferWidth, int framebufferHeight, float ratio, int mousePosX, int mousePosY, const float dt, Input* input, GLFWwindow* window)
    {
        isOpenDropDown = false;
        //set_callback2(window);
        if (this->arrangeType == 0)mousePosX -= (framebufferWidth - 1920.f / ratio) / 2.f;
        mousePosX *= ratio, mousePosY *= ratio;
        this->mousePosX = mousePosX;
        this->mousePosY = mousePosY;
        this->isOnRelease = input->getMouseOnRelease(window, GLFW_MOUSE_BUTTON_1);
        this->isPress = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS;
        this->isOnPress = input->getMouseOnPress(window, GLFW_MOUSE_BUTTON_1);
        if (this->isPress)this->recordTime += dt, this->isClick = !this->isClick;
        else this->recordTime = 0.f;
        this->isMouseButton = this->isOnPress || (this->recordTime > 0.5f && this->isClick);
        for (DropDown2D* dropdown2d : this->drapdown2d)dropdown2d->interact2(mousePosX, mousePosY, this->isOnRelease, this->isPress);
        for (ScrollView2D* scrollView2d : this->scrollView2d)scrollView2d->interact2(mousePosX, mousePosY, this->isOnRelease, this->isPress, this->isOnPress, this->isMouseButton);
        for (Pages2D* pages2d : this->pages2d)pages2d->interact2(this->mousePosX, this->mousePosY, this->isOnRelease, this->isPress, this->isOnPress, this->isMouseButton);
    }

    void input_text(wchar_t c)
    {
        for (InputText2D* inputtext2d : this->inputtexts2d)if (inputtext2d->isClick)inputtext2d->input_text(c);
        for (Slider2D* slider2d : this->sliders2d)if (slider2d->inputText->isClick)slider2d->inputText->input_text(c);
        for (ScrollView2D* scrollView2d : this->scrollView2d) {
            for (InputText2D* inputtext2d : scrollView2d->inputtexts2d)if (inputtext2d->isClick)inputtext2d->input_text(c);
            for (Slider2D* slider2d : scrollView2d->sliders2d)if (slider2d->inputText->isClick)slider2d->inputText->input_text(c);
        }
        for (Pages2D* pages2d : this->pages2d)pages2d->input_text(c);
    }

    void delete_text(bool isDrawBack)
    {
        for (InputText2D* inputtext2d : this->inputtexts2d)if (inputtext2d->isClick)inputtext2d->delete_text(isDrawBack);
        for (Slider2D* slider2d : this->sliders2d)if (slider2d->inputText->isClick)slider2d->inputText->delete_text(isDrawBack);
        for (ScrollView2D* scrollView2d : this->scrollView2d) {
            for (InputText2D* inputtext2d : scrollView2d->inputtexts2d)if (inputtext2d->isClick)inputtext2d->delete_text(isDrawBack);
            for (Slider2D* slider2d : scrollView2d->sliders2d)if (slider2d->inputText->isClick)slider2d->inputText->delete_text(isDrawBack);
        }
        for (Pages2D* pages2d : this->pages2d)pages2d->delete_text(isDrawBack);
    }

    void move_cursor(bool isRight)
    {
        for (InputText2D* inputtext2d : this->inputtexts2d)if (inputtext2d->isClick)inputtext2d->move_cursor(isRight);
        for (Slider2D* slider2d : this->sliders2d)if (slider2d->inputText->isClick)slider2d->inputText->move_cursor(isRight);
        for (ScrollView2D* scrollView2d : this->scrollView2d) {
            for (InputText2D* inputtext2d : scrollView2d->inputtexts2d)if (inputtext2d->isClick)inputtext2d->move_cursor(isRight);
            for (Slider2D* slider2d : scrollView2d->sliders2d)if (slider2d->inputText->isClick)slider2d->inputText->move_cursor(isRight);
        }
        for (Pages2D* pages2d : this->pages2d)pages2d->move_cursor(isRight);
    }

    void scroll(int scrollWheelAction)
    {
        for (ScrollView2D* scrollView2d : this->scrollView2d)scrollView2d->scroll(scrollWheelAction);
        for (Pages2D* pages2d : this->pages2d)pages2d->scroll(scrollWheelAction);
    }

    void render(int framebufferWidth, int framebufferHeight, float ratio, Shader& textShader, Shader& rectangleShader, const float dt)
    {
        int offsetX(0);
        if (this->arrangeType == 0)offsetX = (int)(((float)framebufferWidth * ratio - 1920.f) / 2.f);
        else if (this->arrangeType == 1)offsetX = 0;
        textShader.use();
        textShader.set1i(offsetX, "canvasOffsetX");
        rectangleShader.use();
        rectangleShader.set1i(offsetX, "canvasOffsetX");
        for (Rectangle2D* rectangle2d : this->rectangles2d)rectangle2d->render(rectangleShader);
        for (Button2D* button2d : this->buttons2d)button2d->render(textShader, rectangleShader);
        for (Checkbox2D* checkbox2d : this->checkboxs2d)checkbox2d->render(textShader, rectangleShader);
        for (Slider2D* slider2d : this->sliders2d)slider2d->render(textShader, rectangleShader, dt);
        for (Text2D* text2d : this->texts2d)text2d->render(textShader);
        for (Paragraph2D* paragraph2d : this->paragraphs2d)paragraph2d->render(textShader);
        for (DropDown2D* dropdown2d : this->drapdown2d)dropdown2d->render1(textShader, rectangleShader);
        for (InputText2D* inputtext2d : this->inputtexts2d)inputtext2d->render(textShader, rectangleShader, dt);
        for (ScrollView2D* scrollView2d : this->scrollView2d)scrollView2d->render1(textShader, rectangleShader, dt);
        for (Pages2D* pages2d : this->pages2d)pages2d->render1(textShader, rectangleShader, dt);
        for (Pages2D* pages2d : this->pages2d)pages2d->render2(textShader, rectangleShader, dt);
        for (ScrollView2D* scrollView2d : this->scrollView2d)scrollView2d->render2(textShader, rectangleShader, dt);
        for (DropDown2D* dropdown2d : this->drapdown2d)dropdown2d->render2(textShader, rectangleShader);
        tip2d->render(textShader, rectangleShader, dt);
    }

    ~Canvas2D()
    {
        for (Text2D* i : this->texts2d)delete i;
        for (Paragraph2D* i : this->paragraphs2d)delete i;
        for (Rectangle2D* i : this->rectangles2d)delete i;
        for (Button2D* i : this->buttons2d)delete i;
        for (Checkbox2D* i : this->checkboxs2d)delete i;
        for (Slider2D* i : this->sliders2d)delete i;
        for (DropDown2D* i : this->drapdown2d)delete i;
        for (InputText2D* i : this->inputtexts2d)delete i;
        for (ScrollView2D* i : this->scrollView2d)delete i;
        for (Pages2D* i : this->pages2d)delete i;
    }
};