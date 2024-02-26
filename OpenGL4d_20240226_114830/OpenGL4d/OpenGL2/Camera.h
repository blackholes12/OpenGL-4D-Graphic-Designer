#pragma once
#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm.hpp>
#include<vec3.hpp>
#include<mat4x4.hpp>
#include<gtc\matrix_transform.hpp>
#include"EnumLists.h"
#include"mod.h"

enum direction4Dection { FORWARD = 0, BACKWARD, LEFT, RIGHT, UP, DOWN,ANA,KATA };

class Camera
{
private:
	
	GLfloat maxMovementSpeed;
	GLfloat jumpSpeed;
	GLfloat sensitivity;
	glm::vec4 direction4D;
	alg::rotor4 rotation4D;

	const glm::mat4 get_view_mat4D()
	{
		this->angle_to_rotor4(this->Rotate_Angle4D);
		this->viewMat4D = to_matrix(this->rotation4D);
		return this->viewMat4D;
	}

	void set_rotation4D(alg::bivec4 Rotate_Angle4D)
	{
		this->Rotate_Angle4D = Rotate_Angle4D;
		this->angle_to_rotor4(this->Rotate_Angle4D);
	}

	void angle_to_rotor4(alg::bivec4 Rotate_Angle4D)
	{
		this->rotation4D = update(alg::rotor4(), alg::bivec4(0, 0, 0, glm::radians(Rotate_Angle4D.yz), 0, 0));
		this->rotation4D = update(this->rotation4D, alg::bivec4(0, glm::radians(Rotate_Angle4D.xz), 0, 0, 0, 0));
		this->rotation4D = update(this->rotation4D, alg::bivec4(0, 0, 0, 0, 0, glm::radians(Rotate_Angle4D.zw)));
		this->rotation4D = update(this->rotation4D, alg::bivec4(0, 0, glm::radians(Rotate_Angle4D.xw), 0, 0, 0));
		this->rotation4D = update(this->rotation4D, alg::bivec4(glm::radians(Rotate_Angle4D.xy), 0, 0, 0, 0, 0));
		this->rotation4D = update(this->rotation4D, alg::bivec4(0, 0, 0, 0, glm::radians(Rotate_Angle4D.yw), 0));	
	}

	const glm::vec4 get_right4D()
	{
		return glm::vec4(1, 0, 0, 0) * viewMat4D;
	}

	const glm::vec4 get_forward4D()
	{
		return glm::vec4(0, 0, -1, 0) * viewMat4D;
	}
	const glm::vec4 get_w_dir()
	{
		return glm::vec4(0, 0, 0, 1) * viewMat4D;
	}

public:
	glm::vec4 position4D;
	alg::bivec4 Rotate_Angle4D;
	glm::mat4 viewMat4D, projectionMat;
	glm::vec4 forward4D, wDir,right4D,frontPosition4D;
	glm::vec3 limitedVelocity4D;
	bool isRuning;
	Camera()
	{
		this->viewMat4D = glm::mat4(1.f);
		this->maxMovementSpeed = 4.f;
		this->jumpSpeed = 4.46f;//3.21f;
		this->sensitivity = 1.f/400.f;
		this->Rotate_Angle4D = alg::bivec4();
		this->isRuning = false;
		//x:bodyw,y:eyeh,z:steph,w:headh
	}

	~Camera() {}

	//Accessors
	void update_camera(const float dt, RigidBody4D* player)
	{
		this->viewMat4D = get_view_mat4D();
		this->forward4D = get_forward4D();
		this->wDir = get_w_dir();
		this->right4D = get_right4D();
		//this->Pcameraposition4D = this->cameraposition4D;
		if (!player->isGravity)
		{
			player->velocity4D -= player->velocity4D * dt;
		}
		this->position4D = player->position4D;
		this->position4D.y += 0.5f;
		this->frontPosition4D = this->position4D + 2.f * this->forward4D;
	}

	void put(const float dt, glm::vec4 direction4D, RigidBody4D* player)
	{
		GLfloat moveSpeed;
		if (player->isGravity)
		{
			if (!this->isRuning)
			{
				moveSpeed = this->maxMovementSpeed;
			}
			else
			{
				moveSpeed = 1.5f*this->maxMovementSpeed;
			}
			player->velocity4D.x += this->direction4D.x * 40.f * dt;
			player->velocity4D.z += this->direction4D.z * 40.f * dt;
			player->velocity4D.w += this->direction4D.w * 40.f * dt;
			this->limitedVelocity4D = glm::vec3(player->velocity4D.x, player->velocity4D.z, player->velocity4D.w);
			if (length(this->limitedVelocity4D) > moveSpeed) {
				this->limitedVelocity4D = moveSpeed * normalize(this->limitedVelocity4D);
				player->velocity4D.x = this->limitedVelocity4D.x;
				player->velocity4D.z = this->limitedVelocity4D.y;
				player->velocity4D.w = this->limitedVelocity4D.z;
			}
		}
		else
		{
			if (!this->isRuning)
			{
				moveSpeed = 1.5f*this->maxMovementSpeed;
			}
			else
			{
				moveSpeed = 2.f*this->maxMovementSpeed;
			}
			player->velocity4D.x += this->direction4D.x * moveSpeed * dt;
			player->velocity4D.z += this->direction4D.z * moveSpeed * dt;
			player->velocity4D.w += this->direction4D.w * moveSpeed * dt;
			this->limitedVelocity4D = glm::vec3(player->velocity4D.x, player->velocity4D.z, player->velocity4D.w);
			if (length(this->limitedVelocity4D) > moveSpeed) {
				this->limitedVelocity4D = moveSpeed * normalize(this->limitedVelocity4D);
				player->velocity4D.x = this->limitedVelocity4D.x;
				player->velocity4D.z = this->limitedVelocity4D.y;
				player->velocity4D.w = this->limitedVelocity4D.z;
			}
		}
	}

	void fit_direction(const int direction)
	{
		switch (direction)
		{
		case 0:
			set_rotation4D(alg::bivec4(0.f, this->Rotate_Angle4D.xz, 90.f, this->Rotate_Angle4D.yz,0.f,0.f));
			break;
		case 1:
			set_rotation4D(alg::bivec4(0.f, this->Rotate_Angle4D.xz, 0.f, this->Rotate_Angle4D.yz, 90.f, 0.f));
			break;
		case 2:
			set_rotation4D(alg::bivec4(0.f, this->Rotate_Angle4D.xz, 0.f, this->Rotate_Angle4D.yz, 0.f, 90.f));
			break;
		case 3:
			set_rotation4D(alg::bivec4(0.f, this->Rotate_Angle4D.xz, 0.f, this->Rotate_Angle4D.yz, 0.f, 0.f));
			break;
		default:
			break;
		}
	}

	//Functions
	void move(const float dt,const int direction4Dection,RigidBody4D* player)
	{
		//Update position4Dition vector
		switch (direction4Dection)
		{
		case FORWARD:
			if (abs(this->Rotate_Angle4D.yz) >= glm::radians(90.f))
			{
				this->direction4D = glm::vec4(0, this->Rotate_Angle4D.yz / 10000.f, -1, 0) * viewMat4D;
			}
			else
			{
				this->direction4D = glm::vec4(0, 0, -1, 0) * viewMat4D;
			}
			this->direction4D = normalize(glm::vec4(this->direction4D.x, 0, this->direction4D.z, this->direction4D.w));
			this->put(dt,this->direction4D, player);
			break;
		case BACKWARD:
			if (abs(this->Rotate_Angle4D.yz) >= glm::radians(90.f))
			{
				this->direction4D = glm::vec4(0, -this->Rotate_Angle4D.yz / 10000.f, 1, 0) * viewMat4D;
			}
			else
			{
				this->direction4D = glm::vec4(0, 0, 1, 0) * viewMat4D;
			}
			this->direction4D = normalize(glm::vec4(this->direction4D.x, 0, this->direction4D.z, this->direction4D.w));
			this->put(dt,this->direction4D, player);
			break;
		case LEFT:
			this->direction4D = glm::vec4(-1, 0, 0, 0) * viewMat4D;
			this->direction4D = normalize(glm::vec4(this->direction4D.x, 0, this->direction4D.z, this->direction4D.w));
			this->put(dt,this->direction4D, player);
			break;
		case RIGHT:
			this->direction4D = glm::vec4(1, 0, 0, 0) * viewMat4D;
			this->direction4D = normalize(glm::vec4(this->direction4D.x, 0, this->direction4D.z, this->direction4D.w));
			this->put(dt,this->direction4D, player);
			break;
		case ANA:
			if (abs(this->Rotate_Angle4D.yw) >= glm::radians(90.f))
			{
				this->direction4D = glm::vec4(0, this->Rotate_Angle4D.yz / 10000.f, 0, -1) * viewMat4D;
			}
			else
			{
				this->direction4D = glm::vec4(0, 0, 0, -1) * viewMat4D;
			}
			this->direction4D = normalize(glm::vec4(this->direction4D.x, 0, this->direction4D.z, this->direction4D.w));
			this->put(dt,this->direction4D, player);
			break;
		case KATA:
			if (abs(this->Rotate_Angle4D.yw) >= glm::radians(90.f))
			{
				this->direction4D = glm::vec4(0, -this->Rotate_Angle4D.yz / 10000.f, 0, 1) * viewMat4D;
			}
			else
			{
				this->direction4D = glm::vec4(0, 0, 0, 1) * viewMat4D;
			}
			this->direction4D = normalize(glm::vec4(this->direction4D.x, 0, this->direction4D.z, this->direction4D.w));
			this->put(dt,this->direction4D, player);
			break;
		default:
			break;
		}
	}
	void jump(const float& dt, const int direction4Dection,bool isGround, RigidBody4D* player)
	{
		switch (direction4Dection)
		{
		case DOWN:
			player->velocity4D.y -= 9.8f * dt;
			break;
		case UP:
			if (!player->isGravity)
			{
				player->velocity4D.y += 2.3f * dt;
			}
			if (player->isGravity)
			{
				if (isGround)
				{
					player->velocity4D.y = this->jumpSpeed;
				}
			}
			break;
		default:
			break;
		}
	}
	void update_mouse_input(const float& dt, const double& offsetX, const double& offsetY)
	{
		//Update rotation
		this->Rotate_Angle4D.yz -= glm::degrees(static_cast<GLfloat>(offsetY) * this->sensitivity);
		this->Rotate_Angle4D.xz -= glm::degrees(static_cast<GLfloat>(offsetX) * this->sensitivity);
		this->Rotate_Angle4D.yz = clamp(this->Rotate_Angle4D.yz, -90.f, 90.f);
	}
	void update_mouse_input2(const float& dt, const double& offsetX2, const double& offsetY2)
	{
		//Update rotation2
		this->Rotate_Angle4D.xw -= glm::degrees(static_cast<GLfloat>(offsetX2) * this->sensitivity);
		this->Rotate_Angle4D.zw += glm::degrees(static_cast<GLfloat>(offsetY2) * this->sensitivity);
	}
	void update_perspective_mat(const float fov,const float screenRate,const float nearPlane, std::vector<Shader*> shaders)
	{
		this->projectionMat = glm::tweakedInfinitePerspective(fov, screenRate, nearPlane);
		shaders[OBJ]->use();
		shaders[OBJ]->setMat4fv(this->projectionMat, "projectionMat");
		shaders[SKY_BOXD4]->use();
		shaders[SKY_BOXD4]->setMat4fv(this->projectionMat, "projectionMat");
		shaders[WALLD4]->use();
		shaders[WALLD4]->setMat4fv(this->projectionMat, "projectionMat");
		shaders[DEMOD4]->use();
		shaders[DEMOD4]->setMat4fv(this->projectionMat, "projectionMat");
		shaders[EMITD4]->use();
		shaders[EMITD4]->setMat4fv(this->projectionMat, "projectionMat");
		shaders[TERRAIND4]->use();
		shaders[TERRAIND4]->setMat4fv(this->projectionMat, "projectionMat");
		shaders[WATERD4]->use();
		shaders[WATERD4]->setMat4fv(this->projectionMat, "projectionMat");
		shaders[PARTICLE4D]->use();
		shaders[PARTICLE4D]->setMat4fv(this->projectionMat, "projectionMat");
		shaders[COORDNATE4D]->use();
		shaders[COORDNATE4D]->setMat4fv(this->projectionMat, "projectionMat");
		shaders[TRAIL4D]->use();
		shaders[TRAIL4D]->setMat4fv(this->projectionMat, "projectionMat");
		shaders[JOINT_LINE4D]->use();
		shaders[JOINT_LINE4D]->setMat4fv(this->projectionMat, "projectionMat");
		shaders[FRAME4D]->use();
		shaders[FRAME4D]->setMat4fv(this->projectionMat, "projectionMat");
		shaders[LIGHT_FRAME4D]->use();
		shaders[LIGHT_FRAME4D]->setMat4fv(this->projectionMat, "projectionMat");
	}
};