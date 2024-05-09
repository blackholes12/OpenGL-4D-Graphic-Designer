#pragma once

#include<iostream>
#include<vector>

#include"Vertex.h"
#include"Primitives.h"
#include"Primitives4D.h"
#include"Shader.h"
#include"Texture.h"
class Coordinate4D {
    unsigned int VBO, VAO, sizeOfLineVertices4D; 
    float arrowHeight = 0.2f, arrowWidth = 0.2f / sqrt(7.f), arrowLength = 0.5f;
public:
    Coordinate4D() {
        glLineWidth(1.9f);
       
     
        LineVertex4D lineVertices4D[] = {
            glm::vec4(0.f),glm::vec3(1.f,0.f,0.f),glm::vec4(1.f,0.f,0.f,0.f),glm::vec3(1.f,0.f,0.f),
            glm::vec4(0.f),glm::vec3(0.f,1.f,0.f),glm::vec4(0.f,1.f,0.f,0.f),glm::vec3(0.f,1.f,0.f),
            glm::vec4(0.f),glm::vec3(0.f,0.f,1.f),glm::vec4(0.f,0.f,1.f,0.f),glm::vec3(0.f,0.f,1.f),
            glm::vec4(0.f),glm::vec3(0.5f,0.f,1.f),glm::vec4(0.f,0.f,0.f,1.f),glm::vec3(0.5f,0.f,1.f),
        };
        this->sizeOfLineVertices4D = sizeof(lineVertices4D);
        

        glCreateVertexArrays(1, &this->VAO);
        glBindVertexArray(this->VAO);

        glGenBuffers(1, &this->VBO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, this->sizeOfLineVertices4D, lineVertices4D, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(LineVertex4D), (GLvoid*)offsetof(LineVertex4D, pos4D));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(LineVertex4D), (GLvoid*)offsetof(LineVertex4D, color));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);

    }

    void render(Shader* shader) {
        shader->use();
        glBindVertexArray(this->VAO);
        glDrawArrays(GL_LINES, 0, this->sizeOfLineVertices4D);
    }

    ~Coordinate4D() {

        glDeleteVertexArrays(1, &this->VAO);
        glDeleteBuffers(1, &this->VBO);
    }
};

class Trail4D {
    unsigned int VBO, VAO;
    float time;
    glm::vec4 pPos4D;
    unsigned int steps;
    LineVertex4D* lineVertices4D;
public:
    Trail4D() {
        glCreateVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
        this->time = 0.f;
        this->steps=0;
        this->pPos4D = glm::vec4(0.f);
        this->lineVertices4D = new LineVertex4D[2400];
    }

    void update_trail4D(glm::vec4 position4D,bool isStatic,const float dt,float curTime) {
        this->time += dt;
       
        if (this->time > 0.025f) {
            if (length(position4D - this->pPos4D) >= 0.03f)
            {
                this->lineVertices4D[0].pos4D = position4D;
                this->lineVertices4D[0].color = glm::vec3(curTime / 2.f, curTime, 2.f * curTime);

                for (int i = this->steps; i > 0; i--)
                {
                    this->lineVertices4D[i] = this->lineVertices4D[i-1];
                }
                if (curTime - this->lineVertices4D[this->steps].color.y < 30.f)
                {
                    this->steps += 1;
                }

                //std::cout << "this->VAO=" << this->VAO << "\n";
                //std::cout << "this->VBO=" << this->VBO << "\n";

                glBindVertexArray(this->VAO);
                glDeleteBuffers(1, &this->VBO);
                glGenBuffers(1, &this->VBO);
                glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
                glBufferData(GL_ARRAY_BUFFER, sizeof(LineVertex4D) * this->steps, this->lineVertices4D, GL_STATIC_DRAW);
                glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(LineVertex4D), (GLvoid*)offsetof(LineVertex4D, pos4D));
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(LineVertex4D), (GLvoid*)offsetof(LineVertex4D, color));
                glEnableVertexAttribArray(1);
                glBindVertexArray(0);

                this->pPos4D = position4D;
            }
            if (isStatic)
            {
                float timeDifferece(curTime - this->lineVertices4D[0].color.y);
                if (timeDifferece != 0.f)
                {
                    for (int i(0); i < this->steps; i++)
                    {
                        this->lineVertices4D[i].color += glm::vec3(timeDifferece / 2.f, timeDifferece, 2.f * timeDifferece);
                    }
                }
                //std::cout << "isStatic, timeDifferece=" << timeDifferece << "\n";
            }
        this->time = 0.f;
        }
    }

    void render(Shader* shader) {
        shader->use();
        glBindVertexArray(this->VAO);
        glDrawArrays(GL_LINE_STRIP, 0, this->steps);
    }

    void reset_to_void()
    {
        this->time = 0.f;
        this->steps = 0;
        this->pPos4D = glm::vec4(0.f);
    }

    ~Trail4D() {
        glDeleteVertexArrays(1, &this->VAO);
        glDeleteBuffers(1, &this->VBO);
        delete[] this->lineVertices4D;
        this->lineVertices4D = nullptr;
    }
};

class JointLine4D {
    unsigned int VBO, VAO, sizeOfLineVertices4D;

public:
    JointLine4D() {
        glCreateVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
    }

    void update_joint_line4D(glm::vec4 position4D1, glm::vec4 position4D2) {
        LineVertex4D lineVertices4D[2] = { position4D1,glm::vec3(0.f),position4D2,glm::vec3(0.f)};
        this->sizeOfLineVertices4D = sizeof(lineVertices4D);
        glBindVertexArray(this->VAO);
        glDeleteBuffers(1, &this->VBO);
        glGenBuffers(1, &this->VBO);
        //std::cout << "this->VBO: " << this->VBO << "\n";
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, this->sizeOfLineVertices4D, lineVertices4D, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(LineVertex4D), (GLvoid*)offsetof(LineVertex4D, pos4D));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(LineVertex4D), (GLvoid*)offsetof(LineVertex4D, color));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }

    void render(Shader* shader) {
        shader->use();
        glBindVertexArray(this->VAO);
        glDrawArrays(GL_LINES, 0, this->sizeOfLineVertices4D);
    }

    ~JointLine4D() {

        glDeleteVertexArrays(1, &this->VAO);
        glDeleteBuffers(1, &this->VBO);
    }
};