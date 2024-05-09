#pragma once
//#include"Object.h"
//#include<GLFW/glfw3.h>
//#include<glm.hpp>
//#include<vec2.hpp>
//#include<vec3.hpp>
//#include<vec4.hpp>
//#include<mat4x4.hpp>
//#include<gtc\type_ptr.hpp>
class Stick4D:public Object4D
{
private:
	glm::vec4 nStickDir;
	glm::vec4 noStickPos1;
	glm::vec4 noStickPos2;
	glm::vec4 posOffset;
	glm::vec4 velocityOffset;
	float noStickLength;
	float noStickLengthOffset;
	glm::vec4 force4D;
public:
	glm::vec4 fixPoint4D;
	int index1;
	int index2;
	float stickLength;
	Texture3D* diffuse3D;
	glm::vec4 paintingColor;
	JointLine4D* jointLine4D;

	Stick4D(glm::vec4 fixPoint4D,int index1,int index2,float stickLength, Texture3D* diffuse3D, glm::vec4 paintingColor, Shader* shader)
	: Object4D("Stick4D", Hypercylinder(glm::vec4(0.1f, 0.1f, stickLength, 0.1f)), fixPoint4D, alg::bivec4(), glm::vec4(0.1f,0.1f, stickLength,0.1f),0,0, CAPSULE4D, shader)
	{
		this->fixPoint4D = fixPoint4D;
		this->index1 = index1;
		this->index2 = index2;
		this->stickLength = stickLength;
		this->diffuse3D = diffuse3D;
		this->paintingColor = paintingColor;
		this->jointLine4D = new JointLine4D();
	}
	void update_rigidbody_rigidbody(RigidBody4D* a, RigidBody4D* b,const float dt)
	{
		this->noStickPos1 = a->position4D + a->velocity4D * dt;

		this->noStickPos2 = b->position4D + b->velocity4D * dt;
		this->noStickLength = length(this->noStickPos2 - this->noStickPos1);
		this->noStickLengthOffset = this->noStickLength - stickLength;
		
		this->nStickDir = normalize(b->position4D - a->position4D);
		this->posOffset = noStickLengthOffset * nStickDir;
		this->velocityOffset = posOffset / dt;
		
		this->force4D = velocityOffset * a->mass * b->mass / (b->mass + a->mass) /dt;
		a->forceSystems4D.push_back(new ForceSystem4D(this->force4D,glm::vec4(0.f)));
		b->forceSystems4D.push_back(new ForceSystem4D(-this->force4D, glm::vec4(0.f)));
	}
	void update_stick4D(Object4D* a, Object4D* b)
	{
		this->set_position4D((a->position4D + b->position4D) / 2.f);
		this->set_rotation4D(look_at(a->position4D, b->position4D));
		this->jointLine4D->update_joint_line4D(a->position4D, b->position4D);
	}
	void update_rigidbody_wall(RigidBody4D* a, Object4D* b, const float dt)
	{
		this->noStickPos1 = a->position4D + a->velocity4D * dt;
		this->noStickLength = length(b->position4D - this->noStickPos1);
		this->noStickLengthOffset = this->noStickLength - stickLength;
		
		this->nStickDir = normalize(b->position4D - a->position4D);
		this->posOffset = this->noStickLengthOffset * this->nStickDir;
		this->velocityOffset = this->posOffset / dt;
		
		this->force4D = this->velocityOffset * a->mass / dt;
		a->forceSystems4D.push_back(new ForceSystem4D(this->force4D, glm::vec4(0.f)));
	}
	void update_rigidbody(RigidBody4D* a, const float dt)
	{
		this->noStickPos1 = a->position4D + a->velocity4D * dt;
		this->noStickLength = length(this->fixPoint4D - this->noStickPos1);
		this->noStickLengthOffset = this->noStickLength - stickLength;

		this->nStickDir = normalize(this->fixPoint4D - a->position4D);
		this->posOffset = this->noStickLengthOffset * this->nStickDir;
		this->velocityOffset = this->posOffset / dt;

		this->force4D = this->velocityOffset * a->mass / dt;
		a->forceSystems4D.push_back(new ForceSystem4D(this->force4D, glm::vec4(0.f)));
	}
	void update_stick4D(Object4D* a)
	{
		this->set_position4D((this->fixPoint4D + a->position4D) / 2.f);
		this->set_rotation4D(look_at(this->fixPoint4D, a->position4D));
		this->jointLine4D->update_joint_line4D(this->fixPoint4D, a->position4D);
	}
	~Stick4D(){
		delete this->diffuse3D,this->diffuse3D = nullptr;
		delete[] this->jointLine4D,this->jointLine4D = nullptr;
	}

	void render_line4D(Shader* shader)
	{
		this->jointLine4D->render(shader);
	}

	void render()
	{
		this->diffuse3D->bind(0);
		this->shader->use();//Update uniforms	
		this->shader->set1i(true, "isReflect");//Update uniforms	
		this->shader->set1f(0.4f, "metal");
		this->shader->setVec4f(this->paintingColor, "paintingColor");
		this->mesh4D->render(this->shader); //Activates shader also			
	}
	void render_frame(Shader* shader)
	{
		shader->use();//Update uniforms	
		this->mesh4D->render2(shader); //Activates shader also			
	}
};

class Spring4D :public Object4D
{
private:
	glm::vec4 springDir;
	glm::vec4 nSpringDir;
	float lengthBetween;
	glm::vec4 force4D;
public:
	glm::vec4 fixPoint4D;
	int index1;
	int index2;
	float springLength;
	float k;
	Texture3D* diffuse3D;
	glm::vec4 paintingColor;
	JointLine4D* jointLine4D;
	
	Spring4D(glm::vec4 fixPoint4D, int index1, int index2,float springLength,float k, Texture3D* diffuse3D, glm::vec4 paintingColor, Shader* shader)
		: Object4D("Spring4D", Hypercylinder(glm::vec4(0.05f, 0.05f, springLength, 0.05f)), fixPoint4D, alg::bivec4(), glm::vec4(0.05f, 0.05f, springLength, 0.05f),0,0, CAPSULE4D, shader)
	{
		this->fixPoint4D = fixPoint4D;
		this->index1 = index1;
		this->index2 = index2;
		this->springLength = springLength;
		this->k = k;
		this->diffuse3D = diffuse3D;
		this->paintingColor = paintingColor;
		this->jointLine4D = new JointLine4D();
	}
	void update_rigidbody_rigidbody(RigidBody4D* a, RigidBody4D* b, const float dt)
	{
		this->springDir = b->position4D - a->position4D;
		this->nSpringDir = normalize(this->springDir);
		this->lengthBetween = length(this->springDir);
		this->force4D = k*(this->lengthBetween- springLength)*this->nSpringDir;
		a->forceSystems4D.push_back(new ForceSystem4D(this->force4D, glm::vec4(0.f)));
		b->forceSystems4D.push_back(new ForceSystem4D(-this->force4D, glm::vec4(0.f)));
	}
	void update_spring4D(Object4D* a, Object4D* b)
	{
		this->set_position4D((a->position4D + b->position4D) / 2.f);
		this->set_scale4D(glm::vec4(0.05f, 0.05f, length(a->position4D - b->position4D), 0.05f));
		this->set_rotation4D(look_at(a->position4D, b->position4D));
		this->jointLine4D->update_joint_line4D(a->position4D, b->position4D);
	}
	void update_rigidbody_wall(RigidBody4D* a, Object4D* b, const float dt)
	{
		this->springDir = b->position4D - a->position4D;
		this->nSpringDir = normalize(this->springDir);
		this->lengthBetween= length(this->springDir);
		this->force4D = k * (this->lengthBetween - springLength) * this->nSpringDir;
		a->forceSystems4D.push_back(new ForceSystem4D(this->force4D, glm::vec4(0.f)));
	}
	void update_rigidbody(RigidBody4D* a, const float dt)
	{
		this->springDir = this->fixPoint4D - a->position4D;
		this->nSpringDir = normalize(this->springDir);
		this->lengthBetween = length(this->springDir);
		this->force4D = k * (this->lengthBetween - springLength) * this->nSpringDir;
		a->forceSystems4D.push_back(new ForceSystem4D(this->force4D, glm::vec4(0.f)));
	}
	void update_spring4D(Object4D* a)
	{
		this->set_position4D((this->fixPoint4D + a->position4D) / 2.f);
		this->set_scale4D(glm::vec4(0.05f, 0.05f, length(this->fixPoint4D - a->position4D), 0.05f));
		this->set_rotation4D(look_at(this->fixPoint4D, a->position4D));
		this->jointLine4D->update_joint_line4D(this->fixPoint4D, a->position4D);
	}
	~Spring4D(){
		delete this->diffuse3D,this->diffuse3D = nullptr;
		delete[] this->jointLine4D,this->jointLine4D = nullptr;
	}

	void render_line4D(Shader* shader)
	{
		this->jointLine4D->render(shader);
	}

	void render()
	{
		this->diffuse3D->bind(0);
		this->shader->use();//Update uniforms	
		this->shader->set1i(true, "isReflect");//Update uniforms	
		this->shader->set1f(0.f, "metal");
		this->shader->setVec4f(this->paintingColor, "paintingColor");
		this->mesh4D->render(this->shader); //Activates shader also			
	}
	void render_frame(Shader* shader)
	{
		shader->use();//Update uniforms	
		this->mesh4D->render2(shader); //Activates shader also			
	}
};
static struct HingeConstraint4D
{
	glm::vec4 worldPosition4D;
	glm::vec4 bodyPosition4D1;
	glm::vec4 bodyPosition4D2;
	int index1;
	int index2;
	glm::vec4 normal;
	float depth;
	explicit HingeConstraint4D(glm::vec4 worldPosition4D, glm::vec4 bodyPosition4D1, glm::vec4 bodyPosition4D2, int index1,int index2, glm::vec4 normal = glm::vec4(), float depth = 0.f)
	{
		this->worldPosition4D = worldPosition4D;
		this->bodyPosition4D1 = bodyPosition4D1;
		this->bodyPosition4D2 = bodyPosition4D2;
		this->index1 = index1;
		this->index2 = index2;
		this->normal = normal;
		this->depth = depth;
	}
};