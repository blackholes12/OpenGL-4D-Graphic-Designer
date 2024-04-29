#pragma once

#include"libs.h"


class PointLight
{
protected:
	glm::vec3 position;
	float constant;
	float linear;
	float quadratic;
	size_t id;
	char ss[256];
	float intensity;
	glm::vec3 color;

public:
	PointLight(size_t id,glm::vec3 position, float intensity = 1.f, glm::vec3 color = glm::vec3(1.f),
		float constant = 0.f, float linear = 0.f, float quadratic = 1.f)
	{
		this->id = id;
		this->position = position;
		this->intensity = intensity;
		this->color = color;
		this->constant = constant;
		this->linear = linear;
		this->quadratic = quadratic;
	}

	~PointLight()
	{

	}

	void set_pointlight_property(Shader& type)
	{		
		type.use();
		type.set1i((GLint)this->id+1, "PointLightAmount");
		snprintf(ss, 255,"pointLight[%i].position", (GLint)this->id);
		type.setVec3f(this->position, ss);
		snprintf(ss, 255, "pointLight[%i].intensity", (GLint)this->id);
		type.set1f(this->intensity, ss);
		snprintf(ss, 255, "pointLight[%i].color", (GLint)this->id);
		type.setVec3f(this->color, ss);
		snprintf(ss, 255, "pointLight[%i].constant", (GLint)this->id);
		type.set1f(this->constant, ss);
		snprintf(ss, 255, "pointLight[%i].linear", (GLint)this->id);
		type.set1f(this->linear, ss);
		snprintf(ss, 255, "pointLight[%i].quadratic", (GLint)this->id);
		type.set1f(this->quadratic, ss);
	}

	//set get
	void set_pointlight_position(glm::vec3 position)
	{
		this->position = position;
	}
	void get_pointlight_position(glm::vec3* position)
	{
		*position = this->position;
	}

	void set_pointlight_intensity(float intensity)
	{
		this->intensity = intensity;
	}
	void get_pointlight_intensity(float* intensity)
	{
		*intensity = this->intensity;
	}

	void set_pointlight_color(glm::vec3 color)
	{
		this->color = color;
	}
	void get_pointlight_color(glm::vec3* color)
	{
		*color = this->color;
	}

	void set_pointlight_constant(float constant)
	{
		this->constant = constant;
	}
	void get_pointlight_constant(float* constant)
	{
		*constant = this->constant;
	}

	void set_pointlight_linear(float linear)
	{
		this->linear = linear;
	}
	void get_pointlight_linear(float* linear)
	{
		*linear = this->linear;
	}

	void set_pointlight_quadratic(float quadratic)
	{
		this->quadratic = quadratic;
	}
	void get_pointlight_quadratic(float* quadratic)
	{
		*quadratic = this->quadratic;
	}
};
class DirectionLight
{
protected:
	glm::vec3 direction;
	float intensity;
	GLuint id;
	char ss[256];
	glm::vec3 color;

public:
	DirectionLight(glm::vec3 direction, float intensity = 1.f, glm::vec3 color = glm::vec3(1.f))
	{
		this->direction = direction;
		this->intensity = intensity;
		this->color = color;
	}

	~DirectionLight()
	{

	}
	void set_directionlight_property(Shader& type)
	{
		type.use();
		type.setVec3f(this->direction, "directionLight.direction");
		type.set1f(this->intensity, "directionLight.intensity");
		type.setVec3f(this->color, "directionLight.color");
	}
};
class PointLight4D 
{
protected:
	Mesh4D* mesh4D;

	char ss[256];
	bool isObjective;
	bool isStatic;
public:
	bool isRender=true, isNear= true;
	Texture3D* diffuse3D;
	glm::vec4 position4D;
	int index;
	float intensity;
	glm::vec3 color;
	float constant;
	float linear;
	float quadratic;
	float cubic;
	PointLight4D(Texture3D* diffuse3D, glm::vec4 position4D, int index,float intensity = 1.f, glm::vec3 color = glm::vec3(1.f),
		float constant = 0.f, float linear = 0.f, float quadratic = 0.f,float cubic =0.1f)
	{
		this->position4D = position4D;
		this->index = index;
		this->diffuse3D = diffuse3D;
		this->intensity = intensity;
		this->color = color;
		this->constant = constant;
		this->linear = linear;
		this->quadratic = quadratic;
		this->cubic = cubic;
		this->mesh4D = new Mesh4D(Particle4d(), position4D,
			update(alg::rotor4(), alg::bivec4(0, 0, 0, glm::radians(90.f), 0, 0))
			, glm::vec4(1.f));
	}

	~PointLight4D()
	{
		delete this->mesh4D;
		this->mesh4D = nullptr;
		delete this->diffuse3D;
		this->diffuse3D = nullptr;
	}
	void set_light4D_property(Shader* type, unsigned id)
	{
		type->use();
		snprintf(ss, 255, "pointLight4D[%i].position4D", id);
		type->setVec4f(this->position4D, ss);
		snprintf(ss, 255, "pointLight4D[%i].intensity", id);
		type->set1f(this->intensity, ss);
		snprintf(ss, 255, "pointLight4D[%i].color", id);
		type->setVec3f(this->color, ss);
		snprintf(ss, 255, "pointLight4D[%i].constant", id);
		type->set1f(this->constant, ss);
		snprintf(ss, 255, "pointLight4D[%i].linear", id);
		type->set1f(this->linear, ss);
		snprintf(ss, 255, "pointLight4D[%i].quadratic", id);
		type->set1f(this->quadratic, ss);
		snprintf(ss, 255, "pointLight4D[%i].cubic", id);
		type->set1f(this->cubic, ss);
	}

	//set get
	void set_pointlight4D_position(glm::vec4 position4D, Shader* type1, Shader* type2,unsigned id)
	{
		this->position4D = position4D;
		this->mesh4D->set_mesh_position4D(position4D);
		snprintf(ss, 255, "pointLight4D[%i].position4D", id);
		type1->use();
		type1->setVec4f(position4D, ss);
		type2->use();
		type2->setVec4f(position4D, ss);
	}
	void get_pointlight4D_position(glm::vec4* position4D)
	{
		*position4D = this->position4D;
	}

	void set_pointlight4D_intensity(float intensity)
	{
		this->intensity = intensity;
	}
	void get_pointlight4D_intensity(float* intensity)
	{
		*intensity = this->intensity;
	}

	void set_pointlight4D_color(glm::vec3 color)
	{
		this->color = color;
	}
	void get_pointlight4D_color(glm::vec3* color)
	{
		*color = this->color;
	}

	void set_pointlight4D_constant(float constant)
	{
		this->constant = constant;
	}
	void get_pointlight4D_constant(float* constant)
	{
		*constant = this->constant;
	}

	void set_pointlight4D_linear(float linear)
	{
		this->linear = linear;
	}
	void get_pointlight4D_linear(float* linear)
	{
		*linear = this->linear;
	}

	void set_pointlight4D_quadratic(float quadratic)
	{
		this->quadratic = quadratic;
	}
	void get_pointlight4D_quadratic(float* quadratic)
	{
		*quadratic = this->quadratic;
	}
	void render(Shader* shader)
	{
		this->diffuse3D->bind(0);
		shader->use();
		shader->set1f(0.335f * pow(intensity, 1.f / 3.f), "radius");
		shader->setVec4f(glm::vec4(this->color,1.f), "lightcolor");//Update uniforms	
		this->mesh4D->render(shader); //Activates shader also			
	}

	void render_frame(Shader* shader)
	{
		shader->use();//Update uniforms	
		shader->set1f(0.335f * pow(intensity, 1.f / 3.f), "radius");
		this->mesh4D->render2(shader); //Activates shader also			
	}
};

static void update_point_light4d(std::vector<PointLight4D*> pointLights4D, Shader* type1, Shader* type2)
{
	for (unsigned i = 0; i < pointLights4D.size(); i++)
	{
		pointLights4D[i]->set_light4D_property(type1, i);
		pointLights4D[i]->set_light4D_property(type2, i);
	}
	type1->use();
	type1->set1i(pointLights4D.size(), "PointLight4DAmount");
	type2->use();
	type2->set1i(pointLights4D.size(), "PointLight4DAmount");
}

static void erase_point_light4d(std::vector<PointLight4D*>* pointLights4D, Shader* type1, Shader* type2, int index0)
{
	bool isErase = false;
	for (size_t k = 0; k < pointLights4D->size(); k++)
	{
		if (pointLights4D[0][k]->index == index0)
		{
			pointLights4D->erase(pointLights4D->begin() + k);
			k--;
			isErase = true;
		}
	}
	if(isErase)
	update_point_light4d(*pointLights4D, type1, type2);
}

static void shift_point_light4d(std::vector<PointLight4D*> pointLights4D, int index0, int count)
{
	for (PointLight4D* pointLight4D : pointLights4D)
	{
		if (pointLight4D->index >= index0)
		{
			pointLight4D->index += count;
		}
	}
}

class DirectionLight4D
{
	glm::vec4 body_vec_to_world(alg::rotor4 rotation4D, glm::vec4 v)
	{
		return rotate(rotation4D, alg::vec4(v)).transform();
	}
protected:
	Mesh4D* mesh4D;
public:
	Texture3D* diffuse3D;
	glm::vec3 color;
	float intensity;
	glm::vec4 direction4D;
	alg::rotor4 rotation4D;
	alg::bivec4 RotateAngle4D;
	glm::vec4 right4D;
	DirectionLight4D(Texture3D* diffuse3D, alg::bivec4 RotateAngle4D, glm::vec3 color, float intensity)
	{
		this->diffuse3D = diffuse3D;
		this->RotateAngle4D = RotateAngle4D;
		this->rotation4D = angle_to_rotor4(this->RotateAngle4D);
		this->color = color;
		this->intensity = intensity;
		this->mesh4D = new Mesh4D(Particle4d(), glm::vec4(0,0,1,0),update(alg::rotor4(), alg::bivec4(0, 0, 0, glm::radians(90.f), 0, 0)), glm::vec4(1.f));
	}

	void update_light4D_in_earth_environment(const float period,const float worldTime)
	{
		this->rotation4D = angle_to_rotor4(alg::bivec4(0.f, -90.f));
		this->set_rotation4D(update(this->rotation4D,alg::bivec4(0.f, 0.5f,0.f, sqrt(3.f)/2.f)* worldTime* glm::radians(360 / period)));
		if (-this->direction4D.y > -0.15f)
		{
			float distance = 1.0f*65.68501f*(sqrt(this->direction4D.y* this->direction4D.y+0.00269684f) + this->direction4D.y);
			this->color = 0.96396755751f *glm::vec3(exp(-0.1889f * distance), exp(-0.51f * distance), exp(-1.2576f * distance));
		}
		else
		{
			this->color = glm::vec3(0.f);
		}
	}

	~DirectionLight4D()
	{
		delete this->mesh4D;
		this->mesh4D = nullptr;
		delete this->diffuse3D;
		this->diffuse3D = nullptr;
	}

	void set_light4D_property(Shader* type)
	{
		//std::cout << "set_light4D_property:" << "\n";
		type->use();
		type->setVec4f(this->direction4D, "directionLight4D.direction4D");
		type->set1f(intensity, "directionLight4D.intensity");
		type->setVec3f(this->color, "directionLight4D.color");
	}

	//set get
	void set_rotation4D(alg::bivec4 RotateAngle4D)
	{
		this->RotateAngle4D = RotateAngle4D;
		this->rotation4D = angle_to_rotor4(this->RotateAngle4D);
		this->direction4D = body_vec_to_world(this->rotation4D, glm::vec4(0.f, 0.f, 1.f, 0.f));
		this->right4D = body_vec_to_world(this->rotation4D, glm::vec4(1.f, 0.f, 0.f, 0.f));
		this->mesh4D->set_mesh_position4D(-this->direction4D);
	}

	void set_rotation4D(alg::rotor4 rotation4D)
	{
		this->rotation4D = rotation4D;
		this->direction4D = body_vec_to_world(this->rotation4D, glm::vec4(0.f, 0.f, 1.f, 0.f));
		this->right4D = body_vec_to_world(this->rotation4D, glm::vec4(1.f, 0.f, 0.f, 0.f));
		this->mesh4D->set_mesh_position4D(-this->direction4D);
	}

	void render_lens_flare(glm::vec4 cameraForward4D,Texture3D* texture3D, Shader* shader)
	{
		this->diffuse3D->bind(0);
		shader->use();
		shader->set1f(0.335f * intensity, "radius");
		shader->setVec4f(glm::vec4(this->color, 1.f), "lightcolor");//Update uniforms	
		shader->setVec4f(glm::vec4(0.f), "cameraPos");//Update uniforms	
		this->mesh4D->render(shader); //Activates shader also	
		texture3D->bind(0);
		glm::vec4 antiDirection = glm::reflect(-this->direction4D, cameraForward4D);

		shader->set1f(0.065f * intensity, "radius");
		shader->setVec4f(glm::vec4(glm::vec3(0.3f, 0.9f, 0.3f) * this->color / 3.f, 1.f), "lightcolor");//Update uniforms	
		this->mesh4D->set_mesh_position4D(normalize(glm::mix(-this->direction4D, -antiDirection, -1.25f / 7.f)));
		this->mesh4D->render(shader); //Activates shader also

		shader->set1f(0.01f * intensity, "radius");
		shader->setVec4f(glm::vec4(this->color / 6.f, 1.f), "lightcolor");//Update uniforms	
		this->mesh4D->set_mesh_position4D(normalize(glm::mix(-this->direction4D, -antiDirection, 1.95f / 7.f)));
		this->mesh4D->render(shader); //Activates shader also

		shader->set1f(0.01f * intensity, "radius");
		shader->setVec4f(glm::vec4(this->color/6.f, 1.f), "lightcolor");//Update uniforms	
		this->mesh4D->set_mesh_position4D(normalize(glm::mix(-this->direction4D, -antiDirection, 2.55f / 7.f)));
		this->mesh4D->render(shader); //Activates shader also

		shader->set1f(0.02f * intensity, "radius");
		shader->setVec4f(glm::vec4(this->color / 5.f, 1.f), "lightcolor");//Update uniforms	
		this->mesh4D->set_mesh_position4D(normalize(glm::mix(-this->direction4D, -antiDirection, 4.f / 7.f)));
		this->mesh4D->render(shader); //Activates shader also

		shader->set1f(0.005f * intensity, "radius");
		shader->setVec4f(glm::vec4(this->color/1.25f, 1.f), "lightcolor");//Update uniforms	
		this->mesh4D->set_mesh_position4D(normalize(glm::mix(-this->direction4D, -antiDirection, 4.05f / 7.f)));
		this->mesh4D->render(shader); //Activates shader also

		shader->set1f(0.03f * intensity, "radius");
		shader->setVec4f(glm::vec4(glm::vec3(0.9f, 0.9f, 0.3f) * this->color / 1.25f, 1.f), "lightcolor");//Update uniforms	
		this->mesh4D->set_mesh_position4D(normalize(glm::mix(-this->direction4D, -antiDirection, 5.6f / 7.f)));
		this->mesh4D->render(shader); //Activates shader also

		shader->set1f(0.0075f * intensity, "radius");
		shader->setVec4f(glm::vec4(3.2f*glm::vec3(0.86f, 0.93f, 0.4f) * this->color, 1.f), "lightcolor");//Update uniforms	
		this->mesh4D->set_mesh_position4D(normalize(glm::mix(-this->direction4D, -antiDirection, 5.7f / 7.f)));
		this->mesh4D->render(shader); //Activates shader also

		shader->set1f(0.02f * intensity, "radius");
		shader->setVec4f(glm::vec4(glm::vec3(0.251f, 0.11f, 0.851f)*this->color / 1.25f, 1.f), "lightcolor");//Update uniforms	
		this->mesh4D->set_mesh_position4D(normalize(glm::mix(-this->direction4D, -antiDirection, 6.74f / 7.f)));
		this->mesh4D->render(shader); //Activates shader also

		shader->set1f(0.015f * intensity, "radius");
		shader->setVec4f(glm::vec4(glm::vec3(0.01f, 0.01f, 1.f)*this->color / 1.25f, 1.f), "lightcolor");//Update uniforms	
		this->mesh4D->set_mesh_position4D(normalize(glm::mix(-this->direction4D, -antiDirection, 6.87f / 7.f)));
		this->mesh4D->render(shader); //Activates shader also

		shader->set1f(0.02f * intensity, "radius");
		shader->setVec4f(glm::vec4(glm::vec3(0.251f, 0.11f, 0.851f) * this->color / 1.25f, 1.f), "lightcolor");//Update uniforms	
		this->mesh4D->set_mesh_position4D(-antiDirection);
		this->mesh4D->render(shader); //Activates shader also
	}

	void render_frame(Shader* shader)
	{
		shader->use();//Update uniforms	
		shader->set1f(20000.f*0.335f, "radius");//0.013^(1/3)
		shader->setVec4f(glm::vec4(0.f), "cameraPos");//Update uniforms	
		this->mesh4D->set_mesh_position4D(-20000.f * this->direction4D);
		this->mesh4D->render2(shader); //Activates shader also		
		this->mesh4D->set_mesh_position4D(-this->direction4D);
	}
};
