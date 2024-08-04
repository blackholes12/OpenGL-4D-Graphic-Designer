#pragma once
//#include<iostream>
//#include<GL/glew.h>
//#include<GLFW/glfw3.h>
//#include<glm.hpp>
//#include<vec3.hpp>
//#include<mat4x4.hpp>
//#include<gtc\matrix_transform.hpp>
//#include"EnumLists.h"
//#include"mod.h"

enum direction4Dection { FORWARD = 0, BACKWARD, LEFT, RIGHT, UP, DOWN,ANA,KATA };

class Camera
{
private:
	
	GLfloat walkSpeed;
	GLfloat runningSpeed;
	GLfloat flySpeed;
	GLfloat jumpSpeed;
	GLfloat sensitivity;
	glm::vec4 direction4D;
	alg::rotor4 rotation4D;

	const glm::mat4 get_view_mat4D()
	{
		this->angle_to_rotor4(this->rotateAngle4D);
		this->viewMat4D = to_matrix(this->rotation4D);
		return this->viewMat4D;
	}

	void set_rotation4D(alg::bivec4 rotateAngle4D)
	{
		this->rotateAngle4D = rotateAngle4D;
		this->angle_to_rotor4(this->rotateAngle4D);
	}

	void angle_to_rotor4(alg::bivec4 rotateAngle4D)
	{
		this->rotation4D = update(alg::rotor4(), alg::bivec4(0.f, 0.f, 0.f, glm::radians(rotateAngle4D.yz), 0.f, 0.f));
		this->rotation4D = update(this->rotation4D, alg::bivec4(0.f, glm::radians(rotateAngle4D.xz), 0.f, 0.f, 0.f, 0.f));
		this->rotation4D = update(this->rotation4D, alg::bivec4(0.f, 0.f, 0.f, 0.f, 0.f, glm::radians(rotateAngle4D.zw)));
		this->rotation4D = update(this->rotation4D, alg::bivec4(0.f, 0.f, glm::radians(rotateAngle4D.xw), 0.f, 0.f, 0.f));
		this->rotation4D = update(this->rotation4D, alg::bivec4(glm::radians(rotateAngle4D.xy), 0.f, 0.f, 0.f, 0.f, 0.f));
		this->rotation4D = update(this->rotation4D, alg::bivec4(0.f, 0.f, 0.f, 0.f, glm::radians(rotateAngle4D.yw), 0.f));	
	}

	const glm::vec4 get_right4D()
	{
		return glm::vec4(1.f, 0.f, 0.f, 0.f) * viewMat4D;
	}

	const glm::vec4 get_forward4D()
	{
		return glm::vec4(0.f, 0.f, -1.f, 0.f) * viewMat4D;
	}
	const glm::vec4 get_w_dir()
	{
		return glm::vec4(0.f, 0.f, 0.f, 1.f) * viewMat4D;
	}

public:
	glm::vec4 position4D;
	alg::bivec4 rotateAngle4D;
	glm::mat4 viewMat4D;
	glm::mat4 projectionMat;
	float fov;
	float aspect;
	float nearPlane;
	glm::vec4 forward4D; 
	glm::vec4 wDir;
	glm::vec4 right4D;
	glm::vec4 frontPosition4D;
	glm::vec3 limitedVelocity4D;
	bool isGround;
	bool isRuning;
	bool isCrouch;
	Camera(const float fov, const float nearPlane, const float aspect)
	{
		this->viewMat4D = glm::mat4(1.f);
		this->update_perspective_mat(fov, aspect, nearPlane);
		this->walkSpeed = 4.3f;
		this->runningSpeed = 5.6f;
		this->flySpeed = 10.7f;
		this->jumpSpeed = 4.5f;//3.21f;
		this->sensitivity = 0.0745f;
		this->rotateAngle4D = alg::bivec4();
		this->viewMat4D = get_view_mat4D();
		this->forward4D = get_forward4D();
		this->wDir = get_w_dir();
		this->right4D = get_right4D();
		this->isGround = false;
		this->isRuning = false;
		this->isCrouch = false;
	}

	~Camera() {}

	//Accessors
	void update_camera(RigidBody4D* player,const float dt)
	{
		this->viewMat4D = get_view_mat4D();
		this->forward4D = get_forward4D();
		this->wDir = get_w_dir();
		this->right4D = get_right4D();
		if (!player->isGravity)
		{
			player->velocity4D -= 2.f*player->velocity4D * dt;
		}
	}

	void set_camera_position4D(RigidBody4D* player)
	{
		this->position4D = player->position4D;
		this->position4D.y += player->scale4D.z/2.f-0.13f;
		this->frontPosition4D = this->position4D + 2.f * this->forward4D;
	}

	void put(RigidBody4D* player, glm::vec4 direction4D,const float dt)
	{
		GLfloat moveSpeed;
		if (player->isGravity)
		{
			if (this->isRuning)
			{
				moveSpeed = this->runningSpeed;
			}
			else
			{
				moveSpeed = this->walkSpeed;
			}
			//player->forceSystems4D.push_back(new ForceSystem4D(800000.f * dt * normalize(glm::vec4(this->direction4D.x, 0.f, this->direction4D.z, this->direction4D.w)), glm::vec4(0.f)));
			//if (length(player->velocity4D) < 0.02f)
			//{
			//	//player->position4D.x += this->direction4D.x * 60.f * dt * dt;
			//	//player->position4D.z += this->direction4D.z * 60.f * dt * dt;
			//	//player->position4D.w += this->direction4D.w * 60.f * dt * dt;
			//	player->velocity4D.x += this->direction4D.x * 1200.f * dt;
			//	player->velocity4D.z += this->direction4D.z * 1200.f * dt;
			//	player->velocity4D.w += this->direction4D.w * 1200.f * dt;
			//}
			//else
			
			player->velocity4D.x += this->direction4D.x * 60.f * dt;
			player->velocity4D.z += this->direction4D.z * 60.f * dt;
			player->velocity4D.w += this->direction4D.w * 60.f * dt;

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
			if (this->isRuning)
			{
				moveSpeed = 1.5f * this->flySpeed;
			}
			else
			{
				moveSpeed = this->flySpeed;
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
		case 0:set_rotation4D(alg::bivec4(0.f, this->rotateAngle4D.xz, 90.f, this->rotateAngle4D.yz,0.f,0.f));break;
		case 1:set_rotation4D(alg::bivec4(0.f, this->rotateAngle4D.xz, 0.f, this->rotateAngle4D.yz, 90.f, 0.f));break;
		case 2:set_rotation4D(alg::bivec4(0.f, this->rotateAngle4D.xz, 0.f, this->rotateAngle4D.yz, 0.f, 90.f));break;
		case 3:set_rotation4D(alg::bivec4(0.f, this->rotateAngle4D.xz, 0.f, this->rotateAngle4D.yz, 0.f, 0.f));break;
		default:break;
		}
	}

	//Functions
	void move(const float dt,const int direction4Dection,RigidBody4D* player)
	{
		//Update position4Dition vector
		//if (this->isGround || !player->isGravity)
		//{
			player->isSleep = false;
			switch (direction4Dection)
			{
			case FORWARD:
				if (abs(this->rotateAngle4D.yz) >= glm::radians(90.f))
				{
					this->direction4D = glm::vec4(0.f, this->rotateAngle4D.yz / 10000.f, -1.f, 0.f) * viewMat4D;
				}
				else
				{
					this->direction4D = glm::vec4(0.f, 0.f, -1.f, 0.f) * viewMat4D;
				}
				this->direction4D = normalize(glm::vec4(this->direction4D.x, 0.f, this->direction4D.z, this->direction4D.w));
				this->put(player, this->direction4D, dt);
				break;
			case BACKWARD:
				if (abs(this->rotateAngle4D.yz) >= glm::radians(90.f))
				{
					this->direction4D = glm::vec4(0.f, -this->rotateAngle4D.yz / 10000.f, 1.f, 0) * viewMat4D;
				}
				else
				{
					this->direction4D = glm::vec4(0.f, 0.f, 1.f, 0.f) * viewMat4D;
				}
				this->direction4D = normalize(glm::vec4(this->direction4D.x, 0.f, this->direction4D.z, this->direction4D.w));
				this->put(player, this->direction4D, dt);
				break;
			case LEFT:
				this->direction4D = glm::vec4(-1.f, 0.f, 0.f, 0.f) * viewMat4D;
				//this->direction4D = normalize(glm::vec4(this->direction4D.x, 0.f, this->direction4D.z, this->direction4D.w));
				this->put(player, this->direction4D, dt);
				break;
			case RIGHT:
				this->direction4D = glm::vec4(1.f, 0.f, 0.f, 0.f) * viewMat4D;
				//this->direction4D = normalize(glm::vec4(this->direction4D.x, 0.f, this->direction4D.z, this->direction4D.w));
				this->put(player, this->direction4D, dt);
				break;
			case ANA:
				if (abs(this->rotateAngle4D.yw) >= glm::radians(90.f))
				{
					this->direction4D = glm::vec4(0.f, this->rotateAngle4D.yz / 10000.f, 0.f, -1.f) * viewMat4D;
					this->direction4D = normalize(glm::vec4(this->direction4D.x, 0.f, this->direction4D.z, this->direction4D.w));
				}
				else
				{
					this->direction4D = glm::vec4(0.f, 0.f, 0.f, -1.f) * viewMat4D;
				}
				this->put(player, this->direction4D, dt);
				break;
			case KATA:
				if (abs(this->rotateAngle4D.yw) >= glm::radians(90.f))
				{
					this->direction4D = glm::vec4(0.f, -this->rotateAngle4D.yz / 10000.f, 0.f, 1.f) * viewMat4D;
					this->direction4D = normalize(glm::vec4(this->direction4D.x, 0.f, this->direction4D.z, this->direction4D.w));
				}
				else
				{
					this->direction4D = glm::vec4(0.f, 0.f, 0.f, 1.f) * viewMat4D;
				}
				this->put(player, this->direction4D, dt);
				break;
			default:
				break;
			}
		//}
	}
	void jump(const float dt, const int direction4Dection, RigidBody4D* player)
	{
		player->isSleep = false;
		switch (direction4Dection)
		{
		case DOWN:
			player->velocity4D.y -= 9.8f * dt;
			break;
		case UP:
			if (!player->isGravity)
			{
				player->velocity4D.y += this->flySpeed * dt;
			}
			if (player->isGravity)
			{
				if (this->isGround)
				{
					player->velocity4D.y = this->jumpSpeed;
				}
			}
			break;
		default:
			break;
		}
	}
	void update_mouse_input(const float dt, const double offsetX, const double offsetY)
	{
		//Update rotation
		this->rotateAngle4D.yz -= static_cast<GLfloat>(offsetY) * this->sensitivity;
		this->rotateAngle4D.yz = clamp(this->rotateAngle4D.yz, -90.f, 90.f);
		this->rotateAngle4D.xz -= static_cast<GLfloat>(offsetX) * this->sensitivity;
		if (this->rotateAngle4D.xz < -360.f)
		{
			this->rotateAngle4D.xz += 360.f;
		}
		else if (this->rotateAngle4D.xz > 360.f)
		{
			this->rotateAngle4D.xz -= 360.f;
		}
	}
	void update_mouse_input2(const float dt, const double offsetX2, const double offsetY2)
	{
		//Update rotation2
		this->rotateAngle4D.xw -= static_cast<GLfloat>(offsetX2) * this->sensitivity;
		if (this->rotateAngle4D.xw < -360.f)
		{
			this->rotateAngle4D.xw += 360.f;
		}
		else if (this->rotateAngle4D.xw > 360.f)
		{
			this->rotateAngle4D.xw -= 360.f;
		}
		this->rotateAngle4D.zw += static_cast<GLfloat>(offsetY2) * this->sensitivity;
		if (this->rotateAngle4D.zw < -360.f)
		{
			this->rotateAngle4D.zw += 360.f;
		}
		else if (this->rotateAngle4D.zw > 360.f)
		{
			this->rotateAngle4D.zw -= 360.f;
		}
	}
	void update_perspective_mat(const float fov,const float aspect,const float nearPlane)
	{
		this->fov = fov;
		this->aspect = aspect;
		this->nearPlane = nearPlane;
		this->projectionMat = glm::tweakedInfinitePerspective(glm::radians(fov), aspect, nearPlane);
	}
};