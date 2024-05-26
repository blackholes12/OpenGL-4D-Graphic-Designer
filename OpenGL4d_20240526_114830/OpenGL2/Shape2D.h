#pragma once

//#include<iostream>
//#include<vector>

//#include"Vertex.h"
//#include"Primitives.h"
//#include"Primitives4D.h"
//#include"Shader.h"
//#include"Texture.h"

class Rectangle2D
{
    unsigned int VBO, VAO, nrOfVertices2D;
public:
    unsigned textureIndex;
    Rectangle2D(unsigned textureIndex) {
        this->textureIndex = textureIndex;
        Vertex2D Vertexs2D[] = {
            glm::vec2(-1.f,1.f),glm::vec2(0.f,1.f),glm::vec2(-1.f,-1.f),glm::vec2(0.f,0.f),glm::vec2(1.f,-1.f),glm::vec2(1.f,0.f),
            glm::vec2(-1.f,1.f),glm::vec2(0.f,1.f),glm::vec2(1.f,-1.f),glm::vec2(1.f,0.f),glm::vec2(1.f,1.f),glm::vec2(1.f,1.f)
        };
        this->nrOfVertices2D = sizeof(Vertexs2D);
        glCreateVertexArrays(1, &this->VAO);
        glBindVertexArray(this->VAO);
        glGenBuffers(1, &this->VBO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, this->nrOfVertices2D, Vertexs2D, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (GLvoid*)offsetof(Vertex2D, position2D));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (GLvoid*)offsetof(Vertex2D, texcoord));
        glEnableVertexAttribArray(1);
        glBindVertexArray(0);
    }

    void render(Texture* texture,Shader* shader) {
        texture->bind(0);
        shader->use();
        shader->set1i(0, "tex2D");
        glBindVertexArray(this->VAO);
        glDrawArrays(GL_TRIANGLES, 0, this->nrOfVertices2D);
    }

    ~Rectangle2D() {
        glDeleteVertexArrays(1, &this->VAO);
        glDeleteBuffers(1, &this->VBO);
    }
};