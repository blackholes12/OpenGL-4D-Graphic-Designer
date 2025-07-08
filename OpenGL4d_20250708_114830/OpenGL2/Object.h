#pragma once
//#include"mod.h"
//#include"Mesh.h"
//#include"Texture.h"
//#include"Shader.h"
//#include"OBJLoader.h"
//#include"Line.h"
static bool isObjectParameterUpdated0;

class Object
{
private:
	Texture* overrideTextureDiffuse;
	Texture* overrideTextureSpecular;
	Mesh* mesh;	
public:
	const char* objectName;
	glm::vec3 position;
	glm::vec3 scale;
	Object(
		const char* objectName,
		Primitive primitive,
		glm::vec3 position,
		glm::vec3 Rotate_Angle,
		glm::vec3 scale,
		Shader* shader,
		Texture* orTexDif,
		Texture* orTexSpec
	)
	{
		this->objectName = objectName;
		this->position = position;
		this->scale = scale;
		this->overrideTextureDiffuse = orTexDif;
		this->overrideTextureSpecular = orTexSpec;

		this->mesh=new Mesh(primitive, position,
			Rotate_Angle,
			scale);
	}

	//OBJ file loaded model
	Object(
		const char* objectName,
		const char* objFile,
		glm::vec3 position,
		glm::vec3 Rotate_Angle,
		glm::vec3 scale,
		Shader* shader,
		Texture* orTexDif,
		Texture* orTexSpec	
	)
	{
		this->objectName = objectName;
		this->position = position;
		this->scale = scale;
		this->overrideTextureDiffuse = orTexDif;
		this->overrideTextureSpecular = orTexSpec;

		//Primitive primitive = loadOBJ(objFile);
		this->mesh=new Mesh(loadOBJ(objFile), position,
			Rotate_Angle,
			scale);
	}
	void switch_diffuse_texture(Texture* orTexDif) {
		this->overrideTextureDiffuse = orTexDif;
	}
	void switch_specular_texture(Texture* orTexDif) {
		this->overrideTextureSpecular = orTexDif;
	}
	~Object()
	{
		delete this->mesh;
	}

	//Functions
	void setObjectMat() {
			this->mesh->setObjMat();
	}
	bool isBind = false;
	void render(Shader* shader)
	{	

		//Draw		
			//Activate texture for each mesh
			this->overrideTextureDiffuse->bind(0);
			this->overrideTextureSpecular->bind(1);
			if (!isBind) {
				shader->use();
				shader->set1i(0, "material.diffuseTex");
				shader->set1i(1, "material.specularTex");//Update uniforms	
				isBind = true;
			}
			
			this->mesh->render(shader); //Activates shader also			
	}
	//set get
	void set_object_position(glm::vec3 position)
	{
		this->mesh->set_mesh_position(position);
		this->position = position;
	}
	void get_object_position(glm::vec3* position)
	{
		this->mesh->get_mesh_position(position);
	}

	void set_object_rotate_angle(glm::vec3 Rotate_Angle)
	{
		this->mesh->set_mesh_rotate_angle(Rotate_Angle);
	}
	void get_object_rotate_angle(glm::vec3* Rotate_Angle)
	{
		this->mesh->get_mesh_rotate_angle(Rotate_Angle);
	}

	void set_object_scale(glm::vec3 scale)
	{
		this->mesh->set_mesh_scale(scale);
		this->scale = scale;
	}
	void get_object_scale(glm::vec3* scale)
	{
		this->mesh->get_mesh_scale(scale);
	}
};

class Object4D
{
protected:
	Mesh4D* mesh4d;
public:
	const char* objectName;
	glm::vec4 position4d;
	alg::bivec4 rotateAngle4D;
	glm::vec4 scale4D;
	float mu;
	float restitution;

	unsigned char colType;
	Primitive4D primitive4D;
	size_t shaderIndex;
	alg::rotor4 rotation4D;
	bool isClamp;
	bool isFront;
	std::vector<std::vector<size_t>> componentsVec;
	Object4D(
		const char* objectName,
		Primitive4D primitive4D,
		glm::vec4 position4d,
		alg::bivec4 rotateAngle4D,
		glm::vec4 scale4D,
		float mu,
	    float restitution,
		unsigned char colType,
		size_t shaderIndex
	)
	{
		this->objectName = objectName;
		this->position4d = position4d;
		this->rotateAngle4D = rotateAngle4D;

		this->rotation4D = angle_to_rotor4(this->rotateAngle4D);

		this->scale4D = scale4D;

		this->mu = mu;
		this->restitution = restitution;

		this->colType = colType;
		this->primitive4D = primitive4D;
	
		this->shaderIndex = shaderIndex;
		this->mesh4d = new Mesh4D(primitive4D, position4d,this->rotation4D,scale4D);
		this->isClamp = false;
		this->isFront = false;
		this->componentsVec.resize(OPENDOOR4D_ANIMATION+1);
	}

	Object4D(
		const char* objectName,
		Primitive4D primitive4D,
		glm::vec4 position4d,
		alg::rotor4 rotation4D,
		glm::vec4 scale4D,
		float mu,
		float restitution,
		unsigned char colType,
		size_t shaderIndex
	)
	{
		this->objectName = objectName;
		this->position4d = position4d;

		this->rotation4D = rotation4D;

		this->scale4D = scale4D;

		this->mu = mu;
		this->restitution = restitution;

		this->colType = colType;
		this->primitive4D = primitive4D;

		this->shaderIndex = shaderIndex;
		this->mesh4d = new Mesh4D(primitive4D, position4d, this->rotation4D, scale4D);
		this->isClamp = false;
		this->isFront = false;
		this->componentsVec.resize(OPENDOOR4D_ANIMATION+1);
	}
	~Object4D()
	{
		delete[] this->objectName;
		delete this->mesh4d;
	}
	//Functions

	void set_position4D(glm::vec4 position4d)
	{
		this->position4d = position4d;
		this->mesh4d->set_mesh_position4D(position4d);
	}

	void set_mesh_position4D(glm::vec4 position4d)
	{
		this->mesh4d->set_mesh_position4D(position4d);
	}
	
	void set_rotation4D(alg::bivec4 rotateAngle4D)
	{
		this->rotateAngle4D = rotateAngle4D;
		this->rotation4D = angle_to_rotor4(this->rotateAngle4D);
		this->mesh4d->set_mesh_rotation4D(this->rotation4D);
	}

	void set_rotation4D(alg::rotor4 rotation4D)
	{
		this->rotation4D = rotation4D;
		this->mesh4d->set_mesh_rotation4D(this->rotation4D);
	}

	void set_rotation4D(alg::rotor4 rotation4D, glm::mat4 mesh4DMat)
	{
		this->rotation4D = rotation4D;
		this->mesh4d->set_mesh_rotation4D(this->rotation4D, mesh4DMat);
	}
	
	void set_scale4D(glm::vec4 scale4D)
	{
		this->scale4D = scale4D;
		this->mesh4d->set_mesh_scale4D(scale4D);
	}
	void set_rotation_mat4(glm::mat4 rotationMat4)
	{
		this->mesh4d->set_mesh_rotation_mat4(rotationMat4);
	}
	const glm::mat4 get_mat4()
	{
		return this->mesh4d->get_mesh_mat4();
	}
	//virtual void render() = 0;
};

struct Material4D
{
	float mu;
	float restitution;
	bool isSpecular;
	Texture3D* diffuse3D;
	glm::vec4 paintingColor;
	glm::vec4 metalColor;
};

class Wall4D : public Object4D
{
public:
	bool isSpecular;
	size_t texture3DIndex;
	glm::vec4 paintingColor;
	glm::vec4 metalColor;
	Wall4D(const char* objectName,
		Primitive4D primitive4D,
		glm::vec4 position4d,
		alg::bivec4 rotateAngle4D,
		glm::vec4 scale4D,
		float mu,
		float restitution,
		bool isSpecular,
		size_t texture3DIndex,
		glm::vec4 paintingColor,
		glm::vec4 metalColor,
		unsigned char colType,
		size_t shaderIndex)
		: Object4D(objectName,primitive4D,position4d,rotateAngle4D,scale4D,mu,restitution, colType,shaderIndex)
	{
		this->isSpecular = isSpecular;
		this->texture3DIndex = texture3DIndex;
		this->paintingColor = paintingColor;
		this->metalColor = metalColor;
	}

	Wall4D(const char* objectName,
		Primitive4D primitive4D,
		glm::vec4 position4d,
		alg::rotor4 rotation4D,
		glm::vec4 scale4D,
		float mu,
		float restitution,
		bool isSpecular,
		size_t texture3DIndex,
		glm::vec4 paintingColor,
		glm::vec4 metalColor,
		unsigned char colType,
		size_t shaderIndex)
		: Object4D(objectName, primitive4D, position4d, rotation4D, scale4D, mu, restitution, colType, shaderIndex)
	{
		this->isSpecular = isSpecular;
		this->texture3DIndex = texture3DIndex;
		this->paintingColor = paintingColor;
		this->metalColor = metalColor;
	}

	~Wall4D()
	{
	}

	void render(Texture3D* texture3D,Shader* shader)
	{
		texture3D->bind(0);
		shader->use();//Update uniforms	
		shader->set1i(this->isSpecular, "isSpecular");//Update uniforms	
		shader->set_vec4f(this->paintingColor, "paintingColor");
		shader->set_vec4f(this->metalColor, "metalColor");
		this->mesh4d->render(shader); //Activates shader also			
	}
	void render_frame(Shader* shader)
	{
		shader->use();//Update uniforms	
		this->mesh4d->render2(shader); //Activates shader also			
	}
};

class ForceSystem4D
{
public:
	glm::vec4 force4D;
	glm::vec4 position4d;
	ForceSystem4D(glm::vec4 force4D, glm::vec4 position4d)
	{
		this->force4D = force4D;
		this->position4d = position4d;
	};
	~ForceSystem4D() {}
};

class RigidBody4D : public Object4D
{
public:
	bool isGravity;
	bool isFrozen;
	bool isBeyond;
	bool isSleep;
	bool isContinueSleep;
	glm::vec4 pPosition4D;
	std::vector<ForceSystem4D*> forceSystems4D;
	float mass;
	float momentInertiaScalar; 

	glm::vec4 massCenter;
	glm::vec4 animatePosition4D;
	glm::vec4 velocity4d;

	alg::bivec4 angularVelocity4D;
	bool isSpecular;

	size_t texture3DIndex;
	glm::vec4 paintingColor;
	glm::vec4 metalColor;
	Trail4D* trail4D;
	std::vector<size_t> rigidBodyIndices;
	std::vector<size_t> wallIndices;
	RigidBody4D(const char* objectName,
		Primitive4D primitive4D,
		glm::vec4 position4d,
		alg::bivec4 rotateAngle4D,
		glm::vec4 scale4D,
		float mass,
		float momentInertiaScalar,
		float mu,
		float restitution,
		bool isGravity,
		bool isFrozen,
		glm::vec4 velocity4d,
		alg::bivec4 angularVelocity4D,
		bool isSpecular,
		size_t texture3DIndex,
		glm::vec4 paintingColor,
		glm::vec4 metalColor,
		unsigned char colType,
		size_t shaderIndex,
		glm::vec4 massCenter = glm::vec4(0.f),
		glm::vec4 animatePosition4D = glm::vec4(0.f),
		bool isSleep=false)
		: Object4D(objectName, primitive4D, position4d, rotateAngle4D, scale4D, mu, restitution, colType, shaderIndex)
	{
		this->pPosition4D = position4d;
		this->mass = mass;
		this->massCenter = massCenter;
		this->animatePosition4D = glm::vec4(0.f);
		this->velocity4d = velocity4d;
		this->angularVelocity4D= angularVelocity4D;
		this->isSpecular = isSpecular;
		this->texture3DIndex = texture3DIndex;
		this->paintingColor = paintingColor;
		this->metalColor = metalColor;
		this->isGravity = isGravity;
		this->isFrozen = isFrozen;
		this->isBeyond = false;
		this->isSleep = isSleep;
		this->isContinueSleep = true;
		this->momentInertiaScalar = momentInertiaScalar;
		this->trail4D = new Trail4D();
	}

	RigidBody4D(const char* objectName,
		Primitive4D primitive4D,
		glm::vec4 position4d,
		alg::rotor4 rotation4D,
		glm::vec4 scale4D,
		float mass,
		float momentInertiaScalar,
		float mu,
		float restitution,
		bool isGravity,
		bool isFrozen,
		glm::vec4 velocity4d,
		alg::bivec4 angularVelocity4D,
		bool isSpecular,
		size_t texture3DIndex,
		glm::vec4 paintingColor,
		glm::vec4 metalColor,
		unsigned char colType,
		size_t shaderIndex,
		glm::vec4 massCenter = glm::vec4(0.f),
		glm::vec4 animatePosition4D = glm::vec4(0.f),
		bool isSleep = false)
		: Object4D(objectName, primitive4D, position4d, rotation4D, scale4D, mu, restitution, colType, shaderIndex)
	{
		this->pPosition4D = position4d;
		this->mass = mass;
		this->massCenter = massCenter;
		this->animatePosition4D = animatePosition4D;
		this->velocity4d = velocity4d;
		this->angularVelocity4D = angularVelocity4D;
		this->isSpecular = isSpecular;
		this->texture3DIndex = texture3DIndex;
		this->paintingColor = paintingColor;
		this->metalColor = metalColor;
		this->isGravity = isGravity;
		this->isFrozen = isFrozen;
		this->isBeyond = false;
		this->isSleep = isSleep;
		this->isContinueSleep = true;
		this->momentInertiaScalar = momentInertiaScalar;
		this->trail4D = new Trail4D();
	}

	~RigidBody4D()
	{
		delete this->trail4D;
		for (ForceSystem4D* i : this->forceSystems4D) { delete i;}
	}

	bool is_static()
	{
		return this->isFrozen || this->isBeyond;
	}

	bool is_static_and_sleep()
	{
		return this->isFrozen || this->isBeyond || this->isSleep;
	}

	void render(Texture3D* texture3D, Shader* shader)
	{
		texture3D->bind(0);
		shader->use();//Update uniforms	
		shader->set1i(this->isSpecular, "isSpecular");//Update uniforms	
		shader->set_vec4f(this->paintingColor, "paintingColor");
		shader->set_vec4f(this->metalColor, "metalColor");
		this->mesh4d->render(shader); //Activates shader also			
	}

	void render_frame(Shader* shader)
	{
		shader->use();//Update uniforms	
		this->mesh4d->render2(shader); //Activates shader also			
	}

	void render_trail4D(Shader* shader)
	{
		this->trail4D->render(shader);
	}
	void update_trail4D(const float dt,float curTime)
	{
		this->trail4D->update_trail4D(this->position4d,this->is_static(), dt, curTime);
	}
};

class Sky_Box4D : public Object4D
{
public:
	Sky_Box4D(
		const char* objectName,
		Primitive4D primitive4D,
		alg::bivec4 rotateAngle4D,
		glm::vec4 scale4D,
		size_t shaderIndex
	) : Object4D(objectName, primitive4D, glm::vec4(0.f), rotateAngle4D, scale4D,0.f,0.f, 0, shaderIndex)
	{
	}

	~Sky_Box4D()
	{
	}

	void switch_mode(GLint type, Texture3D* texture3D,glm::vec3 texScale,glm::vec4 paintingColor,Shader* shader)
	{
		texture3D->bind(5);
		shader->use();
		shader->set1i(type, "type");
		shader->set_vec3f(texScale, "texScale");
		shader->set_vec4f(paintingColor, "paintingColor");
	}

	//Functions
	void render(Shader* shader)
	{
		shader->use();
		//Update uniforms	
		this->mesh4d->render(shader); //Activates shader also			
	}
};


class Water4D : public Object4D
{
private:
public:
	Water4D(
		const char* objectName,
		Primitive4D primitive4D,
		glm::vec4 position4d,
		glm::vec4 scale4D,
		unsigned char colType,
		size_t shaderIndex
	) : Object4D(objectName, primitive4D, position4d, alg::bivec4(0,0,0,0,0,0), scale4D,0.f,0.f, colType, shaderIndex)
	{
	}

	~Water4D()
	{
	}

	//Functions

	void render(Shader* shader)
	{
		shader->use();
		//Update uniforms	
		this->mesh4d->render(shader); //Activates shader also			
	}
};

static void update_water4d(std::vector<Water4D*> waters4d, Shader* type1, Shader* type2)
{
	if (waters4d.size() != 0)
	{
		char ss[256];
		GLint i0 = 0;
		for (size_t i = 0; i < waters4d.size(); i++)
		{
			snprintf(ss, 255, "waterArea4D[%d].position4d", i0);
			type1->use();
			type1->set_vec4f(waters4d[i]->position4d, ss);
			type2->use();
			type2->set_vec4f(waters4d[i]->position4d, ss);
			snprintf(ss, 255, "waterArea4D[%d].scale4D", i0);
			type1->use();
			type1->set_vec4f(waters4d[i]->scale4D, ss);
			type2->use();
			type2->set_vec4f(waters4d[i]->scale4D, ss);
			i0++;
		}
		type1->use();
		type1->set1i(i0, "Water4DAmount");
		type2->use();
		type2->set1i(i0, "Water4DAmount");
	}
	if (waters4d.size() == 0)
	{
		type1->use();
		type1->set1i(0, "Water4DAmount");
		type2->use();
		type2->set1i(0, "Water4DAmount");
	}
}

class Terrain4D : public Object4D
{
private:
public:
	float topHeight;
	float bottomHeight;
	Terrain4D(
		const char* objectName,
		Primitive4D primitive4D,
		glm::vec4 position4d,
		glm::vec4 scale4D,
		float mu,
		float restitution,
		unsigned char colType,
		size_t shaderIndex
	) : Object4D(objectName, primitive4D, position4d, alg::bivec4(), scale4D, mu, restitution, colType, shaderIndex)
	{
		this->topHeight = this->support_distance(glm::vec4(0.f,1.f,0.f,0.f),1.f);
		this->bottomHeight = this->support_distance(glm::vec4(0.f, -1.f, 0.f, 0.f),-1.f);
	}

	~Terrain4D()
	{
	}
	float support_distance(glm::vec4 direction4D,float inverseCount)
	{
		glm::vec4 direction4DToObj(direction4D);
		float dot0(0.f);
		for (unsigned int i(0); i < this->primitive4D.get_size_of_vertices4D(); i++)
		{
			glm::vec4 vertexPos4D(this->primitive4D.vertexData4D[i]);
			float dot1(dot(direction4DToObj, vertexPos4D));
			if (inverseCount * dot1 > inverseCount * dot0||i==0)
			{
				dot0 = dot1;
			}
		}
		return inverseCount * dot0;
	}
	void render(Shader* shader)
	{
		shader->use();
		//Update uniforms	
		this->mesh4d->render(shader); //Activates shader also			
	}
	void render_frame(Shader* shader)
	{
		shader->use();//Update uniforms	
		this->mesh4d->render2(shader); //Activates shader also			
	}
};

class Particle4D0
{
public:
	size_t texture3Dindex;
	glm::vec4 position4d;
	glm::vec4 velocity4d;
	float startSize;
	float endSize;
	glm::vec4 startColor;
	glm::vec4 endColor;
	bool isGlowing;
	float duration;
	float time;
	float emitTime;
	float gravity;
	float retention;
	float friction;
	unsigned int level;
	unsigned int index;
	Mesh4D* mesh4d;
	Particle4D0(size_t texture3Dindex,
		glm::vec4 position4d,
		glm::vec4 velocity4d,
		float startSize,
	    float endSize,
		glm::vec4 startColor,
		glm::vec4 endColor,
		bool isGlowing,
		float duration,
		float gravity,
		float retention,
		float friction,
		unsigned int level,
		unsigned int index
	)
	{
		this->texture3Dindex = texture3Dindex;
		this->position4d = position4d;
		this->velocity4d = velocity4d;
		this->startSize = startSize;
		this->endSize = endSize;
		this->startColor= startColor;
		this->endColor = endColor;
		this->isGlowing = isGlowing;
		this->duration = duration;
		this->time = 0.f;
		this->emitTime = 0.f;
		this->gravity = gravity;
		this->retention = retention;
		this->friction = friction;
		this->level = level;
		this->index = index;
		this->mesh4d = new Mesh4D(Particle4d(), position4d,update(alg::rotor4(), alg::bivec4(0, 0, 0, glm::radians(90.f), 0, 0)), glm::vec4(1.f));
	}
	~Particle4D0()
	{
		delete[] this->mesh4d;
	}
	void render(Texture3D* texture3D,Shader* shader)
	{
		texture3D->bind(0);
		shader->use();
		float size(glm::mix(this->startSize, this->endSize, this->time / this->duration));
		shader->set1f(size, "radius");
		shader->set_vec4f(mix(this->startColor, this->endColor,this->time/ this->duration), "lightColor");//Update uniforms	
		this->mesh4d->render(shader); //Activates shader also			
	}

	void render_frame(Shader* shader)
	{
		shader->use();//Update uniforms	
		float size = glm::mix(this->startSize, this->endSize, this->time / this->duration);
		shader->set1f(size, "radius");
		this->mesh4d->render2(shader); //Activates shader also			
	}

	void set_position4D(glm::vec4 position4d)
	{
		this->position4d = position4d;
		this->mesh4d->set_mesh_position4D(position4d);
	}
};

class Emitter4D
{
public:
	glm::vec4 position4d;
	glm::vec4 velocity4d;
	float duration;
	float time;
	float emitTime;
	std::vector<Particle4D0*> particles4D;
	unsigned int type;
	Emitter4D(unsigned int type,
		glm::vec4 position4d,
		glm::vec4 velocity4d,
		float duration
	)
	{
		this->type = type;
		this->position4d = position4d;
		this->velocity4d = velocity4d;
		this->duration = duration;
		this->time = 0.f;
		this->emitTime = 0.f;
	}
	~Emitter4D()
	{
		for (Particle4D0* i : this->particles4D) { delete i; }
	}
};



//struct RigidBody4DIndex
//{
//	bool isGravity;
//	bool isFrozen;
//	bool isBeyond;
//	bool isSleep;
//	bool isContinueSleep;
//	std::vector<ForceSystem4D*> forceSystems4D;
//	float mass;
//	float momentInertiaScalar;
//	glm::vec4 animatePosition4D;
//	glm::vec4 velocity4d;
//	alg::bivec4 angularVelocity4D;
//	Trail4D* trail4D;
//	std::vector<int> rigidBodyIndices;
//	std::vector<int> wallIndices;
//	explicit RigidBody4DIndex(
//		float mass,
//		float momentInertiaScalar,
//		bool isGravity,
//		bool isFrozen,
//		glm::vec4 velocity4d,
//		alg::bivec4 angularVelocity4D,
//		glm::vec4 animatePosition4D = glm::vec4(0.f),
//		bool isSleep = false)
//	{
//		this->mass = mass;
//		this->animatePosition4D = animatePosition4D;
//		this->velocity4d = velocity4d;
//		this->angularVelocity4D = angularVelocity4D;
//		this->isGravity = isGravity;
//		this->isFrozen = isFrozen;
//		this->isBeyond = false;
//		this->isSleep = isSleep;
//		this->isContinueSleep = true;
//		this->momentInertiaScalar = momentInertiaScalar;
//		this->trail4D = new Trail4D();
//	}
//	~RigidBody4DIndex()
//	{
//		this->trail4D = nullptr, delete this->trail4D;
//		for (ForceSystem4D* i : this->forceSystems4D) { i = nullptr, delete i; }
//	}
//};

struct DynamiteIndex
{
	size_t index;
	bool isExploding;
	explicit DynamiteIndex(size_t index, bool isExploding)
	{
		this->index = index;
		this->isExploding = isExploding;
	}
};
