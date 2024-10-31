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

	const glm::mat4 get_view_mat4D()
	{
		return this->angle_to_mat4(this->rotateAngle4D);
	}

	void set_rotation4D(alg::bivec4 rotateAngle4D)
	{
		this->rotateAngle4D = rotateAngle4D;
		this->angle_to_mat4(this->rotateAngle4D);
	}

	glm::mat4 angle_to_mat4(alg::bivec4 rotateAngle4D)
	{
		rotateAngle4D = rotateAngle4D.radians();
		float c1(cos(rotateAngle4D.yz));
		float s1(sin(rotateAngle4D.yz));
		float c2(cos(rotateAngle4D.xz));
		float s2(sin(rotateAngle4D.xz));
		float c3(cos(rotateAngle4D.xy));
		float s3(sin(rotateAngle4D.xy));
		float c4(cos(rotateAngle4D.xw));
		float s4(sin(rotateAngle4D.xw));
		float c5(cos(rotateAngle4D.yw));
		float s5(sin(rotateAngle4D.yw));
		float c6(cos(rotateAngle4D.zw));
		float s6(sin(rotateAngle4D.zw));
		return 
			glm::mat4(
				c2 * c3, c1 * s3 - s1 * s2 * c3, s1 * s3 + c1 * s2 * c3, 0.f,
				-c2 * s3, c1 * c3 + s1 * s2 * s3, c3 * s1 - c1 * s2 * s3, 0.f,
				-s2, -c2 * s1, c1 * c2, 0.f,
				0.f, 0.f, 0.f, 1.f
			) *
			glm::mat4(
				c4, 0.f, 0.f, s4,
				-s4 * s5, c5, 0.f, c4 * s5,
				-c5 * s4 * s6, -s5 * s6, c6, c4 * c5 * s6,
				-c5 * c6 * s4, -c6 * s5, -s6, c5 * c6 * c4
			);
		//this->rotation4D = update(alg::rotor4(), alg::bivec4(0.f, 0.f, 0.f, glm::radians(rotateAngle4D.yz), 0.f, 0.f));
		//this->rotation4D = update(this->rotation4D, alg::bivec4(0.f, glm::radians(rotateAngle4D.xz), 0.f, 0.f, 0.f, 0.f));
		//this->rotation4D = update(this->rotation4D, alg::bivec4(glm::radians(rotateAngle4D.xy), 0.f, 0.f, 0.f, 0.f, 0.f));
		//this->rotation4D = update(this->rotation4D, alg::bivec4(0.f, 0.f, glm::radians(rotateAngle4D.xw), 0.f, 0.f, 0.f));
		//this->rotation4D = update(this->rotation4D, alg::bivec4(0.f, 0.f, 0.f, 0.f, glm::radians(rotateAngle4D.yw), 0.f));
		//this->rotation4D = update(this->rotation4D, alg::bivec4(0.f, 0.f, 0.f, 0.f, 0.f, glm::radians(rotateAngle4D.zw)));
	}

	const glm::vec4 get_right4D()
	{
		return glm::vec4(1.f, 0.f, 0.f, 0.f) * this->viewMat4D;
	}

	const glm::vec4 get_forward4D()
	{
		return glm::vec4(0.f, 0.f, -1.f, 0.f) * this->viewMat4D;
	}
	const glm::vec4 get_w_dir()
	{
		return glm::vec4(0.f, 0.f, 0.f, 1.f) * this->viewMat4D;
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
	glm::vec4 frontVelocity;
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
		//this->frontVelocity = glm::vec4(0.f);
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
		this->position4D = player->position4D;
		this->position4D.y += player->scale4D.z / 2.f - 0.13f;
		this->viewMat4D = get_view_mat4D();
		this->frontVelocity = -this->frontPosition4D;
		this->forward4D = get_forward4D();
		this->frontPosition4D = this->position4D + 2.f * this->forward4D;
		this->frontVelocity += this->frontPosition4D;
		this->frontVelocity /= dt;
		this->wDir = get_w_dir();
		this->right4D = get_right4D();
		if (!player->isGravity)
		{
			player->velocity4D -= 2.f*player->velocity4D * dt;
		}
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
			
			player->velocity4D.x += this->direction4D.x * 60.f * dt;
			player->velocity4D.z += this->direction4D.z * 60.f * dt;
			player->velocity4D.w += this->direction4D.w * 60.f * dt;

			this->limitedVelocity4D = glm::vec3(player->velocity4D.x, player->velocity4D.z, player->velocity4D.w);
			if (alg::length(this->limitedVelocity4D) > moveSpeed) {
				this->limitedVelocity4D = moveSpeed * alg::normalize(this->limitedVelocity4D);
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
			if (alg::length(this->limitedVelocity4D) > moveSpeed) {
				this->limitedVelocity4D = moveSpeed * alg::normalize(this->limitedVelocity4D);
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
			this->direction4D = alg::normalize(glm::vec4(this->direction4D.x, 0.f, this->direction4D.z, this->direction4D.w));
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
			this->direction4D = alg::normalize(glm::vec4(this->direction4D.x, 0.f, this->direction4D.z, this->direction4D.w));
			this->put(player, this->direction4D, dt);
			break;
		case LEFT:
			this->direction4D = glm::vec4(-1.f, 0.f, 0.f, 0.f) * viewMat4D;
			this->put(player, this->direction4D, dt);
			break;
		case RIGHT:
			this->direction4D = glm::vec4(1.f, 0.f, 0.f, 0.f) * viewMat4D;
			this->put(player, this->direction4D, dt);
			break;
		case ANA:
			if (abs(this->rotateAngle4D.yw) >= glm::radians(90.f))
			{
				this->direction4D = glm::vec4(0.f, this->rotateAngle4D.yz / 10000.f, 0.f, -1.f) * viewMat4D;
				this->direction4D = alg::normalize(glm::vec4(this->direction4D.x, 0.f, this->direction4D.z, this->direction4D.w));
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
				this->direction4D = alg::normalize(glm::vec4(this->direction4D.x, 0.f, this->direction4D.z, this->direction4D.w));
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
			if (player->isGravity)
			{
				if (this->isGround)
				{
					player->velocity4D.y = this->jumpSpeed;
				}
			}
			else
			{
				player->velocity4D.y += this->flySpeed * dt;
			}
			break;
		default:
			break;
		}
	}
	void update_mouse_input(const float dt, const double offsetX, const double offsetY)
	{
		//Update rotation
		this->rotateAngle4D.yz = alg::clamp(this->rotateAngle4D.yz - static_cast<GLfloat>(offsetY) * this->sensitivity, -90.f, 90.f);
		this->rotateAngle4D.xz -= static_cast<GLfloat>(offsetX) * this->sensitivity;
		//if (this->rotateAngle4D.xz < -360.f)
		//{
		//	this->rotateAngle4D.xz += 360.f;
		//}
		//else if (this->rotateAngle4D.xz > 360.f)
		//{
		//	this->rotateAngle4D.xz -= 360.f;
		//}
	}
	void update_mouse_input2(const float dt, const double offsetX2, const double offsetY2)
	{
		//Update rotation2
		this->rotateAngle4D.xw = alg::clamp(this->rotateAngle4D.xw - static_cast<GLfloat>(offsetX2) * this->sensitivity, -90.f, 90.f);
		this->rotateAngle4D.zw += static_cast<GLfloat>(offsetY2) * this->sensitivity;
		//if (this->rotateAngle4D.zw < -360.f)
		//{
		//	this->rotateAngle4D.zw += 360.f;
		//}
		//else if (this->rotateAngle4D.zw > 360.f)
		//{
		//	this->rotateAngle4D.zw -= 360.f;
		//}
	}
	void update_perspective_mat(const float fov,const float aspect,const float nearPlane)
	{
		this->fov = fov;
		this->aspect = aspect;
		this->nearPlane = nearPlane;
		this->projectionMat = glm::tweakedInfinitePerspective(glm::radians(fov), aspect, nearPlane);
	}
};

struct Cluster
{
	glm::vec4 minPoint;
	glm::vec4 maxPoint;
	unsigned int lightsLength;
	unsigned int lightIndices[100];
};

class ClusterGroup
{
private:
	GLuint clusterSSBO;
	Cluster* clusters;
	Shader* clusterShader;
	Shader* clusterUpdateShader;
public:
	ClusterGroup(Shader* clusterShader,Shader* clusterUpdateShader)
	{
		glGenBuffers(1,&this->clusterSSBO);
		this->clusters = new Cluster[12 * 12 * 24];
		this->clusterShader = clusterShader;
		this->clusterUpdateShader = clusterUpdateShader;
		glBindBuffer(GL_ARRAY_BUFFER, this->clusterSSBO);
		glBufferData(GL_ARRAY_BUFFER, 12 * 12 * 24, this->clusters, GL_DYNAMIC_COPY);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, this->clusterSSBO);
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}

	void set_clusterGroup(const float zNear,const glm::mat4 projectionMat, int fbW, int fbH)
	{
		//std::cout << "set cluster" << "\n";
		this->clusterShader->use();
		this->clusterShader->set1f(zNear, "zNear");
		this->clusterShader->set1f(1000.f, "zFar");
		this->clusterShader->set_mat4fv(glm::inverse(projectionMat), "inverseProjectionMat");
		this->clusterShader->set_vec2u(glm::uvec2(fbW, fbH), "screenDimensions");
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, this->clusterSSBO);
		glDispatchCompute(12, 12, 24);
		glMemoryBarrier(GL_ALL_BARRIER_BITS);
		glBindBuffer(GL_ARRAY_BUFFER, this->clusterSSBO);
		this->clusters = (Cluster*)glMapBufferRange(GL_ARRAY_BUFFER, 0, 12 * 12 * 24, GL_MAP_READ_BIT);
		glUnmapBuffer(GL_ARRAY_BUFFER);
		float f = this->clusters[2].maxPoint.x+ this->clusters[2].maxPoint.y+ this->clusters[2].maxPoint.z+ this->clusters[2].maxPoint.w;
		std::cout << f << "\n";
	}

	void update_clusterGroup(const glm::mat4 viewMat)
	{
		this->clusterUpdateShader->use();
		this->clusterUpdateShader->set_mat4fv(viewMat, "viewMat");
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, this->clusterSSBO);
		glDispatchCompute(12, 12, 24);
		glMemoryBarrier(GL_ALL_BARRIER_BITS);
	}

	~ClusterGroup()
	{
		glDeleteBuffers(1, & this->clusterSSBO);
		this->clusters = nullptr, delete this->clusters;
	}
};