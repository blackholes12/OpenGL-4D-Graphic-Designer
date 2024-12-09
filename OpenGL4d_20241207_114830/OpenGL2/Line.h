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
    LineVertex4D* lineVertices4D;
    //float arrowHeight = 0.2f, arrowWidth = 0.2f / sqrt(7.f), arrowLength = 0.5f;
public:
    Coordinate4D() {
        glLineWidth(1.9f);
       
        this->lineVertices4D = new LineVertex4D[8];
        this->lineVertices4D[0] = { glm::vec4(0.f),glm::vec3(1.f,0.f,0.f) }, this->lineVertices4D[1] = { glm::vec4(1.f,0.f,0.f,0.f),glm::vec3(1.f,0.f,0.f) },
        this->lineVertices4D[2] = { glm::vec4(0.f),glm::vec3(0.f,1.f,0.f) }, this->lineVertices4D[3] = { glm::vec4(0.f,1.f,0.f,0.f),glm::vec3(0.f,1.f,0.f) },
        this->lineVertices4D[4] = { glm::vec4(0.f),glm::vec3(0.f,0.f,1.f) }, this->lineVertices4D[5] = { glm::vec4(0.f,0.f,1.f,0.f),glm::vec3(0.f,0.f,1.f) },
        this->lineVertices4D[6] = { glm::vec4(0.f),glm::vec3(0.5f,0.f,1.f)}, this->lineVertices4D[7] = { glm::vec4(0.f,0.f,0.f,1.f),glm::vec3(0.5f,0.f,1.f)};
        this->sizeOfLineVertices4D = sizeof(LineVertex4D)*sizeof(this->lineVertices4D);
        

        glCreateVertexArrays(1, &this->VAO);
        glBindVertexArray(this->VAO);

        glGenBuffers(1, &this->VBO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, this->sizeOfLineVertices4D, this->lineVertices4D, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(LineVertex4D), (GLvoid*)offsetof(LineVertex4D, pos4D));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(LineVertex4D), (GLvoid*)offsetof(LineVertex4D, color));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);

    }

    //void update(glm::vec4 cameraFor,int type)
    //{
    //    if (type == 1)
    //    {
    //        this->lineVertices4D[3].pos4D = normalize(glm::vec4(cameraFor.x,0.f, cameraFor.z, cameraFor.w));
    //        glBindVertexArray(this->VAO);
    //        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    //        glBufferData(GL_ARRAY_BUFFER, this->sizeOfLineVertices4D, this->lineVertices4D, GL_STATIC_DRAW);
    //
    //        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(LineVertex4D), (GLvoid*)offsetof(LineVertex4D, pos4D));
    //        glEnableVertexAttribArray(0);
    //        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(LineVertex4D), (GLvoid*)offsetof(LineVertex4D, color));
    //        glEnableVertexAttribArray(1);
    //
    //        glBindVertexArray(0);
    //    }
    //}

    void render(Shader* shader) {
        shader->use();
        glBindVertexArray(this->VAO);
        glDrawArrays(GL_LINES, 0, this->sizeOfLineVertices4D / sizeof(LineVertex4D));
    }

    ~Coordinate4D() {
        this->lineVertices4D=nullptr,delete this->lineVertices4D;
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
    float recordTime;
public:
    Trail4D() {
        glCreateVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
        this->steps=0;
        this->pPos4D = glm::vec4(0.f);
        this->lineVertices4D = new LineVertex4D[2400];
        this->recordTime = 0.f;
    }

    void update_trail4D(glm::vec4 position4D,bool isStatic,const float dt,float curTime) {
        if (isStatic)
        {
            for (unsigned int i(0); i < this->steps; i++)
            {
                this->lineVertices4D[i].color += glm::vec3(dt / 2.f, dt, 2.f * dt);
            }
            //std::cout << "isStatic, timeDifferece=" << timeDifferece << "\n";
        }
        else
        {
            this->recordTime = curTime;
            if (alg::length(position4D - this->pPos4D) >= 0.06f)
            {
                this->lineVertices4D[0].pos4D = position4D;
                this->lineVertices4D[0].color = glm::vec3(curTime / 2.f, curTime, 2.f * curTime);

                for (unsigned int i(this->steps); i > 0; i--)
                {
                    this->lineVertices4D[i] = this->lineVertices4D[i - 1];
                }
                if (curTime - this->lineVertices4D[this->steps].color.y < 30.f)
                {
                    this->steps++;
                }

                glBindVertexArray(this->VAO);
                glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
                glBufferData(GL_ARRAY_BUFFER, sizeof(LineVertex4D) * this->steps, this->lineVertices4D, GL_STATIC_DRAW);
                glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(LineVertex4D), (GLvoid*)offsetof(LineVertex4D, pos4D));
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(LineVertex4D), (GLvoid*)offsetof(LineVertex4D, color));
                glEnableVertexAttribArray(1);
                glBindVertexArray(0);
                this->pPos4D = position4D;
            }
            else
            {
                this->lineVertices4D[0].pos4D = position4D;
                glBindVertexArray(this->VAO);
                glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
                glBufferData(GL_ARRAY_BUFFER, sizeof(LineVertex4D) * this->steps, this->lineVertices4D, GL_STATIC_DRAW);
                glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(LineVertex4D), (GLvoid*)offsetof(LineVertex4D, pos4D));
                glEnableVertexAttribArray(0);
                glBindVertexArray(0);
            }
        }
    }

    void render(Shader* shader) {
        shader->use();
        shader->set1f(this->recordTime, "iTime");
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
        this->lineVertices4D = nullptr, delete[] this->lineVertices4D;
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
        //glDeleteBuffers(1, &this->VBO);
        //glGenBuffers(1, &this->VBO);
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
        glDrawArrays(GL_LINES, 0, this->sizeOfLineVertices4D/ sizeof(LineVertex4D));
    }

    ~JointLine4D() {

        glDeleteVertexArrays(1, &this->VAO);
        glDeleteBuffers(1, &this->VBO);
    }
};