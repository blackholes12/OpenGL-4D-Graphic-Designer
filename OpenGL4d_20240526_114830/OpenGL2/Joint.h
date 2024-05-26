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
public:
	glm::vec4 fixPoint4D;
	int index1;
	int index2;
	float stickLength;
	unsigned int texture3DIndex;
	glm::vec4 paintingColor;
	JointLine4D* jointLine4D;

	Stick4D(glm::vec4 fixPoint4D,int index1,int index2,float stickLength, unsigned int texture3DIndex, glm::vec4 paintingColor, unsigned int shaderIndex)
	: Object4D("Stick4D", Hypercylinder(glm::vec4(0.1f, 0.1f, stickLength, 0.1f)), fixPoint4D, alg::bivec4(), glm::vec4(0.1f,0.1f, stickLength,0.1f),0,0, CAPSULE4D, shaderIndex)
	{
		this->fixPoint4D = fixPoint4D;
		this->index1 = index1;
		this->index2 = index2;
		this->stickLength = stickLength;
		this->texture3DIndex = texture3DIndex;
		this->paintingColor = paintingColor;
		this->jointLine4D = new JointLine4D();
	}
	void solve_rigidbody_rigidbody(RigidBody4D* a, RigidBody4D* b,const float dt)
	{
		glm::vec4 noStickPos1(a->position4D + a->velocity4D * dt);
		glm::vec4 noStickPos2(b->position4D + b->velocity4D * dt);
		float noStickLengthOffset = (length(noStickPos2 - noStickPos1) - stickLength);
		glm::vec4 posOffset(noStickLengthOffset * normalize(b->position4D - a->position4D));
		glm::vec4 velocityOffset(posOffset / dt);
		glm::vec4 impulse4D(velocityOffset * a->mass * b->mass / (b->mass + a->mass));
		resolve_impulse0(a, impulse4D);
		resolve_impulse0(b, -impulse4D);
	}
	void update_stick4D(Object4D* a, Object4D* b)
	{
		this->set_position4D((a->position4D + b->position4D) / 2.f);
		this->set_rotation4D(look_at(a->position4D, b->position4D));
		this->jointLine4D->update_joint_line4D(a->position4D, b->position4D);
	}
	void solve_rigidbody_wall(RigidBody4D* a, Object4D* b, const float dt)
	{
		glm::vec4 noStickPos1(a->position4D + a->velocity4D * dt);
		float noStickLengthOffset(length(b->position4D - noStickPos1) - stickLength);
		glm::vec4 posOffset(noStickLengthOffset * normalize(b->position4D - a->position4D));
		glm::vec4 velocityOffset(posOffset / dt);
		glm::vec4 impulse4D(velocityOffset * a->mass);
		resolve_impulse0(a, impulse4D);
	}
	void solve_rigidbody(RigidBody4D* a, const float dt)
	{
		glm::vec4 noStickPos1(a->position4D + a->velocity4D * dt);
		float noStickLengthOffset(length(fixPoint4D - noStickPos1) - stickLength);
		glm::vec4 posOffset((length(fixPoint4D - noStickPos1) - stickLength) * normalize(fixPoint4D - a->position4D));
		glm::vec4 velocityOffset(posOffset / dt);
		glm::vec4 impulse4D(velocityOffset * a->mass);
		resolve_impulse0(a, impulse4D);
	}
	void update_stick4D(Object4D* a)
	{
		this->set_position4D((this->fixPoint4D + a->position4D) / 2.f);
		this->set_rotation4D(look_at(this->fixPoint4D, a->position4D));
		this->jointLine4D->update_joint_line4D(this->fixPoint4D, a->position4D);
	}
	void set_stick_length(float stickLength)
	{
		this->stickLength = stickLength;
		this->set_scale4D(glm::vec4(0.1f, 0.1f, stickLength, 0.1f));
	}
	~Stick4D(){
		this->jointLine4D = nullptr,delete[] this->jointLine4D;
	}

	void render_line4D(Shader* shader)
	{
		this->jointLine4D->render(shader);
	}

	void render(Texture3D* texture3D,Shader* shader)
	{
		texture3D->bind(0);
		shader->use();//Update uniforms	
		shader->set1i(true, "isReflect");//Update uniforms	
		shader->set1f(0.4f, "metal");
		shader->setVec4f(this->paintingColor, "paintingColor");
		this->mesh4D->render(shader); //Activates shader also			
	}
	void render_frame(Shader* shader)
	{
		shader->use();//Update uniforms	
		this->mesh4D->render2(shader); //Activates shader also			
	}
};

class Spring4D :public Object4D
{
public:
	glm::vec4 fixPoint4D;
	int index1;
	int index2;
	float springLength;
	float k;
	unsigned int texture3DIndex;
	glm::vec4 paintingColor;
	JointLine4D* jointLine4D;
	
	Spring4D(glm::vec4 fixPoint4D, int index1, int index2,float springLength,float k, unsigned int texture3DIndex, glm::vec4 paintingColor, unsigned int shaderIndex)
		: Object4D("Spring4D", Hypercylinder(glm::vec4(0.05f, 0.05f, springLength, 0.05f)), fixPoint4D, alg::bivec4(), glm::vec4(0.05f, 0.05f, springLength, 0.05f),0,0, CAPSULE4D, shaderIndex)
	{
		this->fixPoint4D = fixPoint4D;
		this->index1 = index1;
		this->index2 = index2;
		this->springLength = springLength;
		this->k = k;
		this->texture3DIndex = texture3DIndex;
		this->paintingColor = paintingColor;
		this->jointLine4D = new JointLine4D();
	}
	void solve_rigidbody_rigidbody(RigidBody4D* a, RigidBody4D* b, const float dt)
	{
		glm::vec4 springDir(b->position4D - a->position4D);
		glm::vec4 force4D(k*(length(springDir) - springLength)* normalize(springDir));
		resolve_impulse0(a, force4D*dt);
		resolve_impulse0(b, -force4D*dt);
	}
	void update_spring4D(Object4D* a, Object4D* b)
	{
		this->set_position4D((a->position4D + b->position4D) / 2.f);
		this->set_scale4D(glm::vec4(0.05f, 0.05f, length(a->position4D - b->position4D), 0.05f));
		this->set_rotation4D(look_at(a->position4D, b->position4D));
		this->jointLine4D->update_joint_line4D(a->position4D, b->position4D);
	}
	void solve_rigidbody_wall(RigidBody4D* a, Object4D* b, const float dt)
	{
		glm::vec4 springDir(b->position4D - a->position4D);
		glm::vec4 force4D(k * (length(springDir) - springLength) * normalize(springDir));
		resolve_impulse0(a, force4D * dt);
	}
	void solve_rigidbody(RigidBody4D* a, const float dt)
	{
		glm::vec4 springDir(fixPoint4D - a->position4D);
		glm::vec4 force4D(k * (length(springDir) - springLength) * normalize(springDir));
		resolve_impulse0(a, force4D * dt);
	}
	void update_spring4D(Object4D* a)
	{
		this->set_position4D((this->fixPoint4D + a->position4D) / 2.f);
		this->set_scale4D(glm::vec4(0.05f, 0.05f, length(this->fixPoint4D - a->position4D), 0.05f));
		this->set_rotation4D(look_at(this->fixPoint4D, a->position4D));
		this->jointLine4D->update_joint_line4D(this->fixPoint4D, a->position4D);
	}
	~Spring4D(){
		this->jointLine4D = nullptr,delete[] this->jointLine4D;
	}

	void render_line4D(Shader* shader)
	{
		this->jointLine4D->render(shader);
	}

	void render(Texture3D* texture3D, Shader* shader)
	{
		texture3D->bind(0);
		shader->use();//Update uniforms	
		shader->set1i(true, "isReflect");//Update uniforms	
		shader->set1f(0.f, "metal");
		shader->setVec4f(this->paintingColor, "paintingColor");
		this->mesh4D->render(shader); //Activates shader also			
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