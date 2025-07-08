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

	void set_pointlight_property_c(Shader& type)
	{
		type.use();
		type.set1i((GLint)this->id + 1, "PointLightAmount");
		snprintf(ss, 255, "pointLights[%i].position", (GLint)this->id);
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
	Mesh4D* mesh4d;

	char ss[256];
	bool isObjective;
	bool isStatic;
public:
	size_t texture3DIndex;
	glm::vec4 position4d;
	size_t id;
	float intensity;
	glm::vec3 color;
	float radius;
	PointLight4D(size_t texture3DIndex, glm::vec4 position4d, size_t id, float intensity = 1.f, glm::vec3 color = glm::vec3(1.f),
		float radius = 10.f)
	{
		this->position4d = position4d;
		this->id = id;
		this->texture3DIndex = texture3DIndex;
		this->intensity = intensity;
		this->color = color;
		this->radius = radius;
		this->mesh4d = new Mesh4D(Particle4d(), position4d,
			update(alg::rotor4(), alg::bivec4(0.f, 0.f, 0.f, glm::radians(90.f), 0.f, 0.f))
			, glm::vec4(1.f));
	}

	~PointLight4D()
	{
		delete this->mesh4d;
	}
	void set_light4D_property(Shader* type)
	{
		type->use();
		snprintf(ss, 255, "pointLights4d[%i].position4d", this->id);
		type->set_vec4f(this->position4d, ss);
		snprintf(ss, 255, "pointLights4d[%i].intensity", this->id);
		type->set1f(this->intensity, ss);
		snprintf(ss, 255, "pointLights4d[%i].color", this->id);
		type->set_vec3f(this->color, ss);
		snprintf(ss, 255, "pointLights4d[%i].radius", this->id);
		type->set1f(this->radius, ss);
	}

	void set_light4D_property2(Shader* type)
	{
		type->use();
		snprintf(ss, 255, "pointLights4DPosition[%i]", this->id);
		type->set_vec4f(this->position4d, ss);
		snprintf(ss, 255, "radius[%i]", this->id);
		type->set1f(this->radius, ss);
	}

	//set get
	void set_pointlight4D_position(glm::vec4 position4d, Shader* type1)
	{
		this->position4d = position4d;
		this->mesh4d->set_mesh_position4D(position4d);
		snprintf(ss, 255, "pointLights4d[%i].position4d", this->id);
		type1->use();
		type1->set_vec4f(position4d, ss);
	}

	void set_pointlight4d_mesh_position(glm::vec4 position4d)
	{
		this->position4d = position4d;
		this->mesh4d->set_mesh_position4D(position4d);
	}

	void get_pointlight4D_position(glm::vec4* position4d)
	{
		*position4d = this->position4d;
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
		shader->set1f(0.925f * 0.335f * pow(intensity, 1.f / 3.f), "radius");
		shader->set_vec4f(glm::vec4(this->color,1.f), "lightColor");//Update uniforms	
		this->mesh4d->render(shader); //Activates shader also			
	}

	void render_frame(Shader* shader)
	{
		shader->use();//Update uniforms	
		shader->set1f(0.925f * 0.335f * pow(intensity, 1.f / 3.f), "radius");
		this->mesh4d->render2(shader); //Activates shader also			
	}
};

static void update_point_light4d(std::vector<PointLight4D*> pointLights4d, Shader* type0, Shader* type1, Shader* type2)
{
	for (size_t i(0); i < pointLights4d.size(); i++)
	{
		pointLights4d[i]->set_light4D_property(type0);
		pointLights4d[i]->set_light4D_property(type1);
		pointLights4d[i]->set_light4D_property2(type2);
	}
	type0->use();
	type0->set1i(static_cast<GLint>(pointLights4d.size()), "pointLight4DAmount");
	type1->use();
	type1->set1i(static_cast<GLint>(pointLights4d.size()), "pointLight4DAmount");
	type2->use();
	type2->set1i(static_cast<GLint>(pointLights4d.size()), "pointLight4DAmount");
}

static alg::rotor4 startRotor4(angle_to_rotor4(alg::bivec4(0.f, -90.f)));
static glm::vec3 sunColor = glm::vec3(1.50541666f, 1.85f, 1.8875f) / 1.8875f;//https://www.ossila.com/pages/the-solar-spectrum
enum type_enum { EARTH = 0, SPACE };

static const glm::vec3 atmosphere_absorb_color[200] = {
		glm::vec3(0,0,0),
		glm::vec3(0,0,0),
		glm::vec3(0,0,0),
		glm::vec3(0,0,0),
		glm::vec3(0,0,0),
		glm::vec3(0,0,0),
		glm::vec3(0,0,0),
		glm::vec3(0,0,0),
		glm::vec3(0,0,0),
		glm::vec3(0,0,0),
		glm::vec3(0,0,0),
		glm::vec3(0,0,0),
		glm::vec3(0,0,0),
		glm::vec3(0,0,0),
		glm::vec3(0.00390625,0,0),
		glm::vec3(0.0234375,0,0),
		glm::vec3(0.0507812,0.00390625,0),
		glm::vec3(0.0859375,0.0078125,0),
		glm::vec3(0.125,0.0117188,0),
		glm::vec3(0.164062,0.0195312,0),
		glm::vec3(0.203125,0.03125,0),
		glm::vec3(0.238281,0.0429688,0),
		glm::vec3(0.273438,0.0585938,0.00390625),
		glm::vec3(0.308594,0.0742188,0.00390625),
		glm::vec3(0.339844,0.0898438,0.0078125),
		glm::vec3(0.367188,0.105469,0.0117188),
		glm::vec3(0.394531,0.125,0.015625),
		glm::vec3(0.421875,0.140625,0.0195312),
		glm::vec3(0.445312,0.160156,0.0234375),
		glm::vec3(0.464844,0.175781,0.03125),
		glm::vec3(0.488281,0.195312,0.0390625),
		glm::vec3(0.507812,0.214844,0.046875),
		glm::vec3(0.527344,0.230469,0.0546875),
		glm::vec3(0.542969,0.246094,0.0625),
		glm::vec3(0.558594,0.265625,0.0703125),
		glm::vec3(0.574219,0.28125,0.0820312),
		glm::vec3(0.589844,0.296875,0.0898438),
		glm::vec3(0.601562,0.3125,0.101562),
		glm::vec3(0.613281,0.328125,0.109375),
		glm::vec3(0.628906,0.34375,0.121094),
		glm::vec3(0.636719,0.355469,0.132812),
		glm::vec3(0.648438,0.371094,0.144531),
		glm::vec3(0.660156,0.382812,0.152344),
		glm::vec3(0.667969,0.394531,0.164062),
		glm::vec3(0.679688,0.410156,0.175781),
		glm::vec3(0.6875,0.421875,0.183594),
		glm::vec3(0.695312,0.433594,0.195312),
		glm::vec3(0.703125,0.445312,0.207031),
		glm::vec3(0.710938,0.453125,0.214844),
		glm::vec3(0.71875,0.464844,0.226562),
		glm::vec3(0.722656,0.476562,0.234375),
		glm::vec3(0.730469,0.484375,0.246094),
		glm::vec3(0.738281,0.496094,0.253906),
		glm::vec3(0.742188,0.503906,0.265625),
		glm::vec3(0.75,0.511719,0.273438),
		glm::vec3(0.753906,0.519531,0.285156),
		glm::vec3(0.757812,0.527344,0.292969),
		glm::vec3(0.765625,0.539062,0.300781),
		glm::vec3(0.769531,0.546875,0.308594),
		glm::vec3(0.773438,0.550781,0.316406),
		glm::vec3(0.777344,0.558594,0.328125),
		glm::vec3(0.78125,0.566406,0.335938),
		glm::vec3(0.785156,0.574219,0.34375),
		glm::vec3(0.789062,0.582031,0.351562),
		glm::vec3(0.792969,0.585938,0.359375),
		glm::vec3(0.796875,0.59375,0.367188),
		glm::vec3(0.800781,0.597656,0.375),
		glm::vec3(0.804688,0.605469,0.378906),
		glm::vec3(0.808594,0.609375,0.386719),
		glm::vec3(0.8125,0.617188,0.394531),
		glm::vec3(0.8125,0.621094,0.402344),
		glm::vec3(0.816406,0.628906,0.410156),
		glm::vec3(0.820312,0.632812,0.414062),
		glm::vec3(0.824219,0.636719,0.421875),
		glm::vec3(0.824219,0.640625,0.429688),
		glm::vec3(0.828125,0.648438,0.433594),
		glm::vec3(0.832031,0.652344,0.441406),
		glm::vec3(0.832031,0.65625,0.445312),
		glm::vec3(0.835938,0.660156,0.453125),
		glm::vec3(0.835938,0.664062,0.457031),
		glm::vec3(0.839844,0.667969,0.464844),
		glm::vec3(0.84375,0.671875,0.46875),
		glm::vec3(0.84375,0.675781,0.472656),
		glm::vec3(0.847656,0.679688,0.480469),
		glm::vec3(0.847656,0.683594,0.484375),
		glm::vec3(0.851562,0.6875,0.488281),
		glm::vec3(0.851562,0.691406,0.496094),
		glm::vec3(0.855469,0.695312,0.5),
		glm::vec3(0.855469,0.699219,0.503906),
		glm::vec3(0.859375,0.703125,0.507812),
		glm::vec3(0.859375,0.707031,0.515625),
		glm::vec3(0.863281,0.710938,0.519531),
		glm::vec3(0.863281,0.714844,0.523438),
		glm::vec3(0.863281,0.714844,0.527344),
		glm::vec3(0.867188,0.71875,0.53125),
		glm::vec3(0.867188,0.722656,0.535156),
		glm::vec3(0.871094,0.726562,0.539062),
		glm::vec3(0.871094,0.726562,0.542969),
		glm::vec3(0.871094,0.730469,0.546875),
		glm::vec3(0.875,0.734375,0.554688),
		glm::vec3(0.875,0.734375,0.558594),
		glm::vec3(0.875,0.738281,0.5625),
		glm::vec3(0.878906,0.742188,0.5625),
		glm::vec3(0.878906,0.742188,0.566406),
		glm::vec3(0.878906,0.746094,0.570312),
		glm::vec3(0.882812,0.75,0.574219),
		glm::vec3(0.882812,0.75,0.578125),
		glm::vec3(0.882812,0.753906,0.582031),
		glm::vec3(0.886719,0.753906,0.585938),
		glm::vec3(0.886719,0.757812,0.589844),
		glm::vec3(0.886719,0.761719,0.59375),
		glm::vec3(0.886719,0.761719,0.597656),
		glm::vec3(0.890625,0.765625,0.597656),
		glm::vec3(0.890625,0.765625,0.601562),
		glm::vec3(0.890625,0.769531,0.605469),
		glm::vec3(0.890625,0.769531,0.609375),
		glm::vec3(0.894531,0.773438,0.613281),
		glm::vec3(0.894531,0.773438,0.613281),
		glm::vec3(0.894531,0.777344,0.617188),
		glm::vec3(0.894531,0.777344,0.621094),
		glm::vec3(0.898438,0.78125,0.625),
		glm::vec3(0.898438,0.78125,0.625),
		glm::vec3(0.898438,0.785156,0.628906),
		glm::vec3(0.898438,0.785156,0.632812),
		glm::vec3(0.902344,0.789062,0.632812),
		glm::vec3(0.902344,0.789062,0.636719),
		glm::vec3(0.902344,0.789062,0.640625),
		glm::vec3(0.902344,0.792969,0.640625),
		glm::vec3(0.902344,0.792969,0.644531),
		glm::vec3(0.90625,0.796875,0.648438),
		glm::vec3(0.90625,0.796875,0.648438),
		glm::vec3(0.90625,0.800781,0.652344),
		glm::vec3(0.90625,0.800781,0.65625),
		glm::vec3(0.90625,0.800781,0.65625),
		glm::vec3(0.910156,0.804688,0.660156),
		glm::vec3(0.910156,0.804688,0.660156),
		glm::vec3(0.910156,0.804688,0.664062),
		glm::vec3(0.910156,0.808594,0.667969),
		glm::vec3(0.910156,0.808594,0.667969),
		glm::vec3(0.910156,0.8125,0.671875),
		glm::vec3(0.914062,0.8125,0.671875),
		glm::vec3(0.914062,0.8125,0.675781),
		glm::vec3(0.914062,0.816406,0.675781),
		glm::vec3(0.914062,0.816406,0.679688),
		glm::vec3(0.914062,0.816406,0.679688),
		glm::vec3(0.914062,0.820312,0.683594),
		glm::vec3(0.917969,0.820312,0.683594),
		glm::vec3(0.917969,0.820312,0.6875),
		glm::vec3(0.917969,0.820312,0.6875),
		glm::vec3(0.917969,0.824219,0.691406),
		glm::vec3(0.917969,0.824219,0.691406),
		glm::vec3(0.917969,0.824219,0.695312),
		glm::vec3(0.917969,0.828125,0.695312),
		glm::vec3(0.921875,0.828125,0.699219),
		glm::vec3(0.921875,0.828125,0.699219),
		glm::vec3(0.921875,0.832031,0.703125),
		glm::vec3(0.921875,0.832031,0.703125),
		glm::vec3(0.921875,0.832031,0.707031),
		glm::vec3(0.921875,0.832031,0.707031),
		glm::vec3(0.921875,0.835938,0.707031),
		glm::vec3(0.925781,0.835938,0.710938),
		glm::vec3(0.925781,0.835938,0.710938),
		glm::vec3(0.925781,0.835938,0.714844),
		glm::vec3(0.925781,0.839844,0.714844),
		glm::vec3(0.925781,0.839844,0.71875),
		glm::vec3(0.925781,0.839844,0.71875),
		glm::vec3(0.925781,0.839844,0.71875),
		glm::vec3(0.925781,0.84375,0.722656),
		glm::vec3(0.925781,0.84375,0.722656),
		glm::vec3(0.929688,0.84375,0.726562),
		glm::vec3(0.929688,0.84375,0.726562),
		glm::vec3(0.929688,0.847656,0.726562),
		glm::vec3(0.929688,0.847656,0.730469),
		glm::vec3(0.929688,0.847656,0.730469),
		glm::vec3(0.929688,0.847656,0.730469),
		glm::vec3(0.929688,0.847656,0.734375),
		glm::vec3(0.929688,0.851562,0.734375),
		glm::vec3(0.929688,0.851562,0.738281),
		glm::vec3(0.933594,0.851562,0.738281),
		glm::vec3(0.933594,0.851562,0.738281),
		glm::vec3(0.933594,0.855469,0.742188),
		glm::vec3(0.933594,0.855469,0.742188),
		glm::vec3(0.933594,0.855469,0.742188),
		glm::vec3(0.933594,0.855469,0.746094),
		glm::vec3(0.933594,0.855469,0.746094),
		glm::vec3(0.933594,0.859375,0.746094),
		glm::vec3(0.933594,0.859375,0.75),
		glm::vec3(0.933594,0.859375,0.75),
		glm::vec3(0.933594,0.859375,0.75),
		glm::vec3(0.9375,0.859375,0.753906),
		glm::vec3(0.9375,0.863281,0.753906),
		glm::vec3(0.9375,0.863281,0.753906),
		glm::vec3(0.9375,0.863281,0.757812),
		glm::vec3(0.9375,0.863281,0.757812),
		glm::vec3(0.9375,0.863281,0.757812),
		glm::vec3(0.9375,0.863281,0.757812),
		glm::vec3(0.9375,0.867188,0.761719),
		glm::vec3(0.9375,0.867188,0.761719),
		glm::vec3(0.9375,0.867188,0.761719),
		glm::vec3(0.9375,0.867188,0.765625)
};

static inline glm::vec3 color_from_absorbion(float lDotY)
{
	const int colNum(200);
	float idx = (lDotY + 0.1f) / 1.1f * (float)colNum;
	idx = alg::min(float(colNum - 1), idx);
	idx = alg::max(0.f, idx);
	return alg::max(glm::mix(atmosphere_absorb_color[int(floor(idx))], atmosphere_absorb_color[int(ceil(idx))], glm::fract(idx)), glm::vec3(0.f));
}

class DirectionLight4D
{
	glm::vec4 body_vec_to_world(alg::rotor4 rotation4D, glm::vec4 v)
	{
		return rotate(rotation4D, alg::vec4(v)).transform();
	}
protected:
	Mesh4D* mesh4d;
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
		this->mesh4d = new Mesh4D(Particle4d(), glm::vec4(0.f,0.f,1.f,0.f),update(alg::rotor4(), alg::bivec4(0.f, 0.f, 0.f, glm::radians(90.f), 0.f, 0.f)), glm::vec4(1.f));
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
			//this->set_rotation4D(update(startRotor4, alg::bivec4(0.f, 0.f, 0.f, 1.f) * asin(floor(worldTime/10.f)/10.f)/ PI * 600.f * glm::radians(360.f / period)));
			this->color = sunColor * color_from_absorbion(-this->direction4D.y);
		}
		else if (this->type == SPACE)
		{
			this->set_rotation4D(startRotor4);
			this->color = sunColor;
		}
	}

	~DirectionLight4D()
	{
		delete this->mesh4d;
	}

	void set_light4D_property(Shader* shader)
	{
		//std::cout << "set_light4D_property:" << "\n";
		shader->use();
		shader->set_vec4f(this->direction4D, "directionLight4d.direction4D");
		shader->set1f(this->intensity, "directionLight4d.intensity");
		shader->set_vec3f(this->color, "directionLight4d.color");
	}

	//set get
	void set_rotation4D(alg::bivec4 RotateAngle4D)
	{
		this->RotateAngle4D = RotateAngle4D;
		this->rotation4D = angle_to_rotor4(this->RotateAngle4D);
		this->direction4D = body_vec_to_world(this->rotation4D, glm::vec4(0.f, 0.f, 1.f, 0.f));
		this->right4D = body_vec_to_world(this->rotation4D, glm::vec4(1.f, 0.f, 0.f, 0.f));
		this->mesh4d->set_mesh_position4D(-this->direction4D);
	}

	void set_rotation4D(alg::rotor4 rotation4D)
	{
		this->rotation4D = rotation4D;
		this->direction4D = body_vec_to_world(this->rotation4D, glm::vec4(0.f, 0.f, 1.f, 0.f));
		this->right4D = body_vec_to_world(this->rotation4D, glm::vec4(1.f, 0.f, 0.f, 0.f));
		this->mesh4d->set_mesh_position4D(-this->direction4D);
	}

	void render_lens_flare(glm::vec4 cameraForward4D, Texture3D* texture3D,Texture3D* texture3D2, Shader* shader)
	{
		texture3D->bind(0);
		shader->use();
		shader->set1f(0.925f*0.335f * intensity, "radius");
		shader->set_vec4f(glm::vec4(this->color, 1.f), "lightColor");//Update uniforms	
		shader->set_vec4f(glm::vec4(0.f), "cameraPos");//Update uniforms	
		this->mesh4d->render(shader); //Activates shader also	
		texture3D2->bind(0);

		shader->set1f(0.925f*0.065f * intensity, "radius");
		shader->set_vec4f(glm::vec4(glm::vec3(0.3f, 0.9f, 0.3f) * this->color / 3.f, 1.f), "lightColor");//Update uniforms	
		//this->mesh4d->set_mesh_position4D(normalize(glm::mix(-this->direction4D, -antiDirection, -1.25f / 7.f)));
		this->mesh4d->set_mesh_position4D(get_lens_flare_direction4D(this->direction4D, cameraForward4D, 17.825f/14.f));
		this->mesh4d->render(shader); //Activates shader also

		shader->set1f(0.925f * 0.01f * intensity, "radius");
		shader->set_vec4f(glm::vec4(this->color / 6.f, 1.f), "lightColor");//Update uniforms	
		//this->mesh4d->set_mesh_position4D(normalize(glm::mix(-this->direction4D, -antiDirection, 1.95f / 7.f)));
		this->mesh4d->set_mesh_position4D(get_lens_flare_direction4D(this->direction4D, cameraForward4D, 31.f / 70.f));
		this->mesh4d->render(shader); //Activates shader also

		shader->set1f(0.925f * 0.01f * intensity, "radius");
		shader->set_vec4f(glm::vec4(this->color/6.f, 1.f), "lightColor");//Update uniforms	
		//this->mesh4d->set_mesh_position4D(normalize(glm::mix(-this->direction4D, -antiDirection, 2.55f / 7.f)));
		this->mesh4d->set_mesh_position4D(get_lens_flare_direction4D(this->direction4D, cameraForward4D, 19.f / 70.f));
		this->mesh4d->render(shader); //Activates shader also

		shader->set1f(0.925f * 0.02f * intensity, "radius");
		shader->set_vec4f(glm::vec4(this->color / 5.f, 1.f), "lightColor");//Update uniforms	
		//this->mesh4d->set_mesh_position4D(normalize(glm::mix(-this->direction4D, -antiDirection, 4.f / 7.f)));
		this->mesh4d->set_mesh_position4D(get_lens_flare_direction4D(this->direction4D, cameraForward4D, -1.f/7.f));
		this->mesh4d->render(shader); //Activates shader also

		shader->set1f(0.925f * 0.005f * intensity, "radius");
		shader->set_vec4f(glm::vec4(this->color/1.25f, 1.f), "lightColor");//Update uniforms	
		//this->mesh4d->set_mesh_position4D(normalize(glm::mix(-this->direction4D, -antiDirection, 4.05f / 7.f)));
		this->mesh4d->set_mesh_position4D(get_lens_flare_direction4D(this->direction4D, cameraForward4D, -11.f / 70.f));
		this->mesh4d->render(shader); //Activates shader also

		shader->set1f(0.925f * 0.03f * intensity, "radius");
		shader->set_vec4f(glm::vec4(glm::vec3(0.9f, 0.9f, 0.3f) * this->color / 1.25f, 1.f), "lightColor");//Update uniforms	
		//this->mesh4d->set_mesh_position4D(normalize(glm::mix(-this->direction4D, -antiDirection, 5.6f / 7.f)));
		this->mesh4d->set_mesh_position4D(get_lens_flare_direction4D(this->direction4D, cameraForward4D, -0.6f));
		this->mesh4d->render(shader); //Activates shader also

		shader->set1f(0.925f * 0.0075f * intensity, "radius");
		shader->set_vec4f(glm::vec4(3.2f*glm::vec3(0.86f, 0.93f, 0.4f) * this->color, 1.f), "lightColor");//Update uniforms	
		//this->mesh4d->set_mesh_position4D(normalize(glm::mix(-this->direction4D, -antiDirection, 5.7f / 7.f)));
		this->mesh4d->set_mesh_position4D(get_lens_flare_direction4D(this->direction4D, cameraForward4D, -22.f/35.f));
		this->mesh4d->render(shader); //Activates shader also

		shader->set1f(0.925f * 0.02f * intensity, "radius");
		shader->set_vec4f(glm::vec4(glm::vec3(0.251f, 0.11f, 0.851f)*this->color / 1.25f, 1.f), "lightColor");//Update uniforms	
		//this->mesh4d->set_mesh_position4D(normalize(glm::mix(-this->direction4D, -antiDirection, 6.74f / 7.f)));
		this->mesh4d->set_mesh_position4D(get_lens_flare_direction4D(this->direction4D, cameraForward4D, -162.f / 175.f));
		this->mesh4d->render(shader); //Activates shader also

		shader->set1f(0.925f * 0.015f * intensity, "radius");
		shader->set_vec4f(glm::vec4(glm::vec3(0.01f, 0.01f, 1.f)*this->color / 1.25f, 1.f), "lightColor");//Update uniforms	
		//this->mesh4d->set_mesh_position4D(normalize(glm::mix(-this->direction4D, -antiDirection, 6.87f / 7.f)));
		this->mesh4d->set_mesh_position4D(get_lens_flare_direction4D(this->direction4D, cameraForward4D, -337.f / 350.f));
		this->mesh4d->render(shader); //Activates shader also

		shader->set1f(0.925f * 0.02f * intensity, "radius");
		shader->set_vec4f(glm::vec4(glm::vec3(0.251f, 0.11f, 0.851f) * this->color / 1.25f, 1.f), "lightColor");//Update uniforms	
		//this->mesh4d->set_mesh_position4D(-antiDirection);
		this->mesh4d->set_mesh_position4D(get_lens_flare_direction4D(this->direction4D, cameraForward4D, -1.f));
		this->mesh4d->render(shader); //Activates shader also
	}

	void render_frame(Shader* shader)
	{
		shader->use();//Update uniforms	
		shader->set1f(0.925f * 20000.f*0.335f, "radius");//0.013^(1/3)
		shader->set_vec4f(glm::vec4(0.f), "cameraPos");//Update uniforms	
		this->mesh4d->set_mesh_position4D(-20000.f * this->direction4D);
		this->mesh4d->render2(shader); //Activates shader also		
		this->mesh4d->set_mesh_position4D(-this->direction4D);
	}
};
