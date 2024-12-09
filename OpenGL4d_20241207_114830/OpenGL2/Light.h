#pragma once

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
		snprintf(ss, 255,"pointLights[%i].position", (GLint)this->id);
		type.set_vec3f(this->position, ss);
		snprintf(ss, 255, "pointLights[%i].intensity", (GLint)this->id);
		type.set1f(this->intensity, ss);
		snprintf(ss, 255, "pointLights[%i].color", (GLint)this->id);
		type.set_vec3f(this->color, ss);
		snprintf(ss, 255, "pointLights[%i].constant", (GLint)this->id);
		type.set1f(this->constant, ss);
		snprintf(ss, 255, "pointLights[%i].linear", (GLint)this->id);
		type.set1f(this->linear, ss);
		snprintf(ss, 255, "pointLights[%i].quadratic", (GLint)this->id);
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
		type.set_vec3f(this->direction, "directionLight.direction");
		type.set1f(this->intensity, "directionLight.intensity");
		type.set_vec3f(this->color, "directionLight.color");
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
	size_t texture3DIndex;
	glm::vec4 position4D;
	size_t id;
	float intensity;
	glm::vec3 color;
	float radius;
	PointLight4D(size_t texture3DIndex, glm::vec4 position4D, size_t id, float intensity = 1.f, glm::vec3 color = glm::vec3(1.f),
		float radius = 10.f)
	{
		this->position4D = position4D;
		this->id = id;
		this->texture3DIndex = texture3DIndex;
		this->intensity = intensity;
		this->color = color;
		this->radius = radius;
		this->mesh4D = new Mesh4D(Particle4d(), position4D,
			update(alg::rotor4(), alg::bivec4(0.f, 0.f, 0.f, glm::radians(90.f), 0.f, 0.f))
			, glm::vec4(1.f));
	}

	~PointLight4D()
	{
		this->mesh4D = nullptr,delete this->mesh4D;
	}
	void set_light4D_property(Shader* type)
	{
		type->use();
		snprintf(ss, 255, "pointLights4D[%i].position4D", this->id);
		type->set_vec4f(this->position4D, ss);
		snprintf(ss, 255, "pointLights4D[%i].intensity", this->id);
		type->set1f(this->intensity, ss);
		snprintf(ss, 255, "pointLights4D[%i].color", this->id);
		type->set_vec3f(this->color, ss);
		snprintf(ss, 255, "pointLights4D[%i].radius", this->id);
		type->set1f(this->radius, ss);
	}

	//set get
	void set_pointlight4D_position(glm::vec4 position4D, Shader* type1)
	{
		this->position4D = position4D;
		this->mesh4D->set_mesh_position4D(position4D);
		snprintf(ss, 255, "pointLights4D[%i].position4D", this->id);
		type1->use();
		type1->set_vec4f(position4D, ss);
	}

	void set_pointlight4d_mesh_position(glm::vec4 position4D)
	{
		this->position4D = position4D;
		this->mesh4D->set_mesh_position4D(position4D);
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

	void set_pointlight4D_radius(float radius)
	{
		this->radius = radius;
	}

	void render(Texture3D* texture3D,Shader* shader)
	{
		texture3D->bind(0);
		shader->use();
		shader->set1f(0.335f * pow(intensity, 1.f / 3.f), "radius");
		shader->set_vec4f(glm::vec4(this->color,1.f), "lightColor");//Update uniforms	
		this->mesh4D->render(shader); //Activates shader also			
	}

	void render_frame(Shader* shader)
	{
		shader->use();//Update uniforms	
		shader->set1f(0.335f * pow(intensity, 1.f / 3.f), "radius");
		this->mesh4D->render2(shader); //Activates shader also			
	}
};

static void update_point_light4d(std::vector<PointLight4D*> pointLights4D, Shader* type0, Shader* type1, Shader* type2)
{
	for (size_t i(0); i < pointLights4D.size(); i++)
	{
		pointLights4D[i]->set_light4D_property(type0);
		pointLights4D[i]->set_light4D_property(type1);
		pointLights4D[i]->set_light4D_property(type2);
	}
	type0->use();
	type0->set1i(static_cast<GLint>(pointLights4D.size()), "pointLight4DAmount");
	type1->use();
	type1->set1i(static_cast<GLint>(pointLights4D.size()), "pointLight4DAmount");
	type2->use();
	type2->set1i(static_cast<GLint>(pointLights4D.size()), "pointLight4DAmount");
}

static alg::rotor4 startRotor4(angle_to_rotor4(alg::bivec4(0.f, -90.f)));
static glm::vec3 sunColor(glm::vec3(214.f, 212.f, 216.f) / 216.f);
enum type_enum { EARTH = 0, SPACE };

class DirectionLight4D
{
	glm::vec4 body_vec_to_world(alg::rotor4 rotation4D, glm::vec4 v)
	{
		return rotate(rotation4D, alg::vec4(v)).transform();
	}
protected:
	Mesh4D* mesh4D;
public:
	size_t texture3DIndex;
	unsigned int type;
	glm::vec3 color;
	float intensity;
	glm::vec4 direction4D;
	alg::rotor4 rotation4D;
	alg::bivec4 RotateAngle4D;
	glm::vec4 right4D;
	DirectionLight4D(size_t texture3DIndex, alg::bivec4 RotateAngle4D, glm::vec3 color, float intensity)
	{
		this->texture3DIndex = texture3DIndex;
		this->type = EARTH;
		this->RotateAngle4D = RotateAngle4D;
		this->color = color;
		this->intensity = intensity;
		this->direction4D = glm::vec4(-1.f, 0.f, 0.f, 0.f);
		this->rotation4D = angle_to_rotor4(this->RotateAngle4D);
		this->mesh4D = new Mesh4D(Particle4d(), glm::vec4(0.f,0.f,1.f,0.f),update(alg::rotor4(), alg::bivec4(0.f, 0.f, 0.f, glm::radians(90.f), 0.f, 0.f)), glm::vec4(1.f));
	}

	float get_cloud_distance(glm::vec4 ray, float radius, float height)
	{
		return sqrt(radius * radius * ray.y * ray.y + 2.f * height * radius + height * height) - radius * ray.y;
	}

	void update_light4D(const float period,const float worldTime)
	{
		if (this->type == EARTH)
		{
			this->set_rotation4D(update(startRotor4, alg::bivec4(0.f, 0.5f, 0.f, sqrt(3.f) / 2.f) * worldTime * glm::radians(360.f / period)));
			if (-this->direction4D.y > -0.15f)
			{
				float distance(80.46413725f * get_cloud_distance(-this->direction4D, 6371000.f, 8228.f) / 6371000.f);
				this->color = sunColor * glm::vec3(exp(-0.1889f * distance), exp(-0.51f * distance), exp(-1.2576f * distance));
			}
			else
			{
				this->color = glm::vec3(0.f);
			}
		}
		else if (this->type == SPACE)
		{
			this->set_rotation4D(startRotor4);
			this->color = sunColor;
		}
	}

	~DirectionLight4D()
	{
		delete this->mesh4D;
		this->mesh4D = nullptr;
	}

	void set_light4D_property(Shader* shader)
	{
		//std::cout << "set_light4D_property:" << "\n";
		shader->use();
		shader->set_vec4f(this->direction4D, "directionLight4D.direction4D");
		shader->set1f(this->intensity, "directionLight4D.intensity");
		shader->set_vec3f(this->color, "directionLight4D.color");
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

	void render_lens_flare(glm::vec4 cameraForward4D, Texture3D* texture3D,Texture3D* texture3D2, Shader* shader)
	{
		texture3D->bind(0);
		shader->use();
		shader->set1f(0.335f * intensity, "radius");
		shader->set_vec4f(glm::vec4(this->color, 1.f), "lightColor");//Update uniforms	
		shader->set_vec4f(glm::vec4(0.f), "cameraPos");//Update uniforms	
		this->mesh4D->render(shader); //Activates shader also	
		texture3D2->bind(0);

		shader->set1f(0.065f * intensity, "radius");
		shader->set_vec4f(glm::vec4(glm::vec3(0.3f, 0.9f, 0.3f) * this->color / 3.f, 1.f), "lightColor");//Update uniforms	
		//this->mesh4D->set_mesh_position4D(normalize(glm::mix(-this->direction4D, -antiDirection, -1.25f / 7.f)));
		this->mesh4D->set_mesh_position4D(get_lens_flare_direction4D(this->direction4D, cameraForward4D, 17.825f/14.f));
		this->mesh4D->render(shader); //Activates shader also

		shader->set1f(0.01f * intensity, "radius");
		shader->set_vec4f(glm::vec4(this->color / 6.f, 1.f), "lightColor");//Update uniforms	
		//this->mesh4D->set_mesh_position4D(normalize(glm::mix(-this->direction4D, -antiDirection, 1.95f / 7.f)));
		this->mesh4D->set_mesh_position4D(get_lens_flare_direction4D(this->direction4D, cameraForward4D, 31.f / 70.f));
		this->mesh4D->render(shader); //Activates shader also

		shader->set1f(0.01f * intensity, "radius");
		shader->set_vec4f(glm::vec4(this->color/6.f, 1.f), "lightColor");//Update uniforms	
		//this->mesh4D->set_mesh_position4D(normalize(glm::mix(-this->direction4D, -antiDirection, 2.55f / 7.f)));
		this->mesh4D->set_mesh_position4D(get_lens_flare_direction4D(this->direction4D, cameraForward4D, 19.f / 70.f));
		this->mesh4D->render(shader); //Activates shader also

		shader->set1f(0.02f * intensity, "radius");
		shader->set_vec4f(glm::vec4(this->color / 5.f, 1.f), "lightColor");//Update uniforms	
		//this->mesh4D->set_mesh_position4D(normalize(glm::mix(-this->direction4D, -antiDirection, 4.f / 7.f)));
		this->mesh4D->set_mesh_position4D(get_lens_flare_direction4D(this->direction4D, cameraForward4D, -1.f/7.f));
		this->mesh4D->render(shader); //Activates shader also

		shader->set1f(0.005f * intensity, "radius");
		shader->set_vec4f(glm::vec4(this->color/1.25f, 1.f), "lightColor");//Update uniforms	
		//this->mesh4D->set_mesh_position4D(normalize(glm::mix(-this->direction4D, -antiDirection, 4.05f / 7.f)));
		this->mesh4D->set_mesh_position4D(get_lens_flare_direction4D(this->direction4D, cameraForward4D, -11.f / 70.f));
		this->mesh4D->render(shader); //Activates shader also

		shader->set1f(0.03f * intensity, "radius");
		shader->set_vec4f(glm::vec4(glm::vec3(0.9f, 0.9f, 0.3f) * this->color / 1.25f, 1.f), "lightColor");//Update uniforms	
		//this->mesh4D->set_mesh_position4D(normalize(glm::mix(-this->direction4D, -antiDirection, 5.6f / 7.f)));
		this->mesh4D->set_mesh_position4D(get_lens_flare_direction4D(this->direction4D, cameraForward4D, -0.6f));
		this->mesh4D->render(shader); //Activates shader also

		shader->set1f(0.0075f * intensity, "radius");
		shader->set_vec4f(glm::vec4(3.2f*glm::vec3(0.86f, 0.93f, 0.4f) * this->color, 1.f), "lightColor");//Update uniforms	
		//this->mesh4D->set_mesh_position4D(normalize(glm::mix(-this->direction4D, -antiDirection, 5.7f / 7.f)));
		this->mesh4D->set_mesh_position4D(get_lens_flare_direction4D(this->direction4D, cameraForward4D, -22.f/35.f));
		this->mesh4D->render(shader); //Activates shader also

		shader->set1f(0.02f * intensity, "radius");
		shader->set_vec4f(glm::vec4(glm::vec3(0.251f, 0.11f, 0.851f)*this->color / 1.25f, 1.f), "lightColor");//Update uniforms	
		//this->mesh4D->set_mesh_position4D(normalize(glm::mix(-this->direction4D, -antiDirection, 6.74f / 7.f)));
		this->mesh4D->set_mesh_position4D(get_lens_flare_direction4D(this->direction4D, cameraForward4D, -162.f / 175.f));
		this->mesh4D->render(shader); //Activates shader also

		shader->set1f(0.015f * intensity, "radius");
		shader->set_vec4f(glm::vec4(glm::vec3(0.01f, 0.01f, 1.f)*this->color / 1.25f, 1.f), "lightColor");//Update uniforms	
		//this->mesh4D->set_mesh_position4D(normalize(glm::mix(-this->direction4D, -antiDirection, 6.87f / 7.f)));
		this->mesh4D->set_mesh_position4D(get_lens_flare_direction4D(this->direction4D, cameraForward4D, -337.f / 350.f));
		this->mesh4D->render(shader); //Activates shader also

		shader->set1f(0.02f * intensity, "radius");
		shader->set_vec4f(glm::vec4(glm::vec3(0.251f, 0.11f, 0.851f) * this->color / 1.25f, 1.f), "lightColor");//Update uniforms	
		//this->mesh4D->set_mesh_position4D(-antiDirection);
		this->mesh4D->set_mesh_position4D(get_lens_flare_direction4D(this->direction4D, cameraForward4D, -1.f));
		this->mesh4D->render(shader); //Activates shader also
	}

	void render_frame(Shader* shader)
	{
		shader->use();//Update uniforms	
		shader->set1f(20000.f*0.335f, "radius");//0.013^(1/3)
		shader->set_vec4f(glm::vec4(0.f), "cameraPos");//Update uniforms	
		this->mesh4D->set_mesh_position4D(-20000.f * this->direction4D);
		this->mesh4D->render2(shader); //Activates shader also		
		this->mesh4D->set_mesh_position4D(-this->direction4D);
	}
};
