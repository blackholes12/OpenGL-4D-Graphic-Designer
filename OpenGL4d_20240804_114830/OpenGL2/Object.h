#pragma once
//#include"mod.h"
//#include"Mesh.h"
//#include"Texture.h"
//#include"Shader.h"
//#include"OBJLoader.h"
//#include"Line.h"


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
	
	Mesh4D* mesh4D;

public:
	const char* objectName;
	glm::vec4 position4D;
	alg::bivec4 rotateAngle4D;
	glm::vec4 scale4D;
	float mu;
	float restitution;

	unsigned int colType;
	Primitive4D primitive4D;
	unsigned int shaderIndex;
	alg::rotor4 rotation4D;
	bool isClamp;
	bool isFront;
	Object4D(
		const char* objectName,
		Primitive4D primitive4D,
		glm::vec4 position4D,
		alg::bivec4 rotateAngle4D,
		glm::vec4 scale4D,
		float mu,
	    float restitution,
		unsigned int colType,
		unsigned int shaderIndex
	)
	{
		this->objectName = objectName;
		this->position4D = position4D;
		this->rotateAngle4D = rotateAngle4D;

		this->rotation4D = angle_to_rotor4(this->rotateAngle4D);

		this->scale4D = scale4D;

		this->mu = mu;
		this->restitution = restitution;

		this->colType = colType;
		this->primitive4D = primitive4D;
	
		this->shaderIndex = shaderIndex;
		this->mesh4D = new Mesh4D(primitive4D, position4D,this->rotation4D,scale4D);
		this->isClamp = false;
		this->isFront = false;
	}

	Object4D(
		const char* objectName,
		Primitive4D primitive4D,
		glm::vec4 position4D,
		alg::rotor4 rotation4D,
		glm::vec4 scale4D,
		float mu,
		float restitution,
		unsigned int colType,
		unsigned int shaderIndex
	)
	{
		this->objectName = objectName;
		this->position4D = position4D;

		this->rotation4D = rotation4D;

		this->scale4D = scale4D;

		this->mu = mu;
		this->restitution = restitution;

		this->colType = colType;
		this->primitive4D = primitive4D;

		this->shaderIndex = shaderIndex;
		this->mesh4D = new Mesh4D(primitive4D, position4D, this->rotation4D, scale4D);
		this->isClamp = false;
		this->isFront = false;
	}
	~Object4D()
	{
		this->objectName = nullptr,delete[] this->objectName;
		this->mesh4D = nullptr,delete this->mesh4D;
	}
	//Functions

	void set_position4D(glm::vec4 position4D)
	{
		this->position4D = position4D;
		this->mesh4D->set_mesh_position4D(position4D);
	}

	void set_mesh_position4D(glm::vec4 position4D)
	{
		this->mesh4D->set_mesh_position4D(position4D);
	}
	
	void set_rotation4D(alg::bivec4 rotateAngle4D)
	{
		this->rotateAngle4D = rotateAngle4D;
		this->rotation4D = angle_to_rotor4(this->rotateAngle4D);
		this->mesh4D->set_mesh_rotation4D(this->rotation4D);
	}

	void set_rotation4D(alg::rotor4 rotation4D)
	{
		this->rotation4D = rotation4D;
		this->mesh4D->set_mesh_rotation4D(this->rotation4D);
	}
	
	void set_scale4D(glm::vec4 scale4D)
	{
		this->scale4D = scale4D;
		this->mesh4D->set_mesh_scale4D(scale4D);
	}
	void set_rotation_mat4(glm::mat4 rotationMat4)
	{
		this->mesh4D->set_mesh_rotation_mat4(rotationMat4);
	}
	const glm::mat4 get_mat4()
	{
		return this->mesh4D->get_mesh_mat4();
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
	unsigned int texture3DIndex;
	glm::vec4 paintingColor;
	glm::vec4 metalColor;
	Wall4D(const char* objectName,
		Primitive4D primitive4D,
		glm::vec4 position4D,
		alg::bivec4 rotateAngle4D,
		glm::vec4 scale4D,
		float mu,
		float restitution,
		bool isSpecular,
		unsigned int texture3DIndex,
		glm::vec4 paintingColor,
		glm::vec4 metalColor,
		unsigned int colType,
		unsigned int shaderIndex)
		: Object4D(objectName,primitive4D,position4D,rotateAngle4D,scale4D,mu,restitution, colType,shaderIndex)
	{
		this->isSpecular = isSpecular;
		this->texture3DIndex = texture3DIndex;
		this->paintingColor = paintingColor;
		this->metalColor = metalColor;
	}

	Wall4D(const char* objectName,
		Primitive4D primitive4D,
		glm::vec4 position4D,
		alg::rotor4 rotation4D,
		glm::vec4 scale4D,
		float mu,
		float restitution,
		bool isSpecular,
		unsigned int texture3DIndex,
		glm::vec4 paintingColor,
		glm::vec4 metalColor,
		unsigned int colType,
		unsigned int shaderIndex)
		: Object4D(objectName, primitive4D, position4D, rotation4D, scale4D, mu, restitution, colType, shaderIndex)
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
		shader->setVec4f(this->paintingColor, "paintingColor");
		shader->setVec4f(this->metalColor, "metalColor");
		this->mesh4D->render(shader); //Activates shader also			
	}
	void render_frame(Shader* shader)
	{
		shader->use();//Update uniforms	
		this->mesh4D->render2(shader); //Activates shader also			
	}
};

class ForceSystem4D 
{
public:
	glm::vec4 force4D;
	glm::vec4 position4D;
	ForceSystem4D(glm::vec4 force4D, glm::vec4 position4D)
	{
		this->force4D = force4D;
		this->position4D = position4D;
	};
	~ForceSystem4D(){}
};

struct WallIndex
{
	int groupIndex;
	int objectIndex;
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

	glm::vec4 animatePosition4D;
	glm::vec4 velocity4D;

	alg::bivec4 angularVelocity4D;
	bool isSpecular;

	unsigned int texture3DIndex;
	glm::vec4 paintingColor;
	glm::vec4 metalColor;
	Trail4D* trail4D;
	std::vector<int> rigidBodyIndices;
	std::vector<WallIndex> groupWallIndices;
	std::vector<int> wallIndices;
	RigidBody4D(const char* objectName,
		Primitive4D primitive4D,
		glm::vec4 position4D,
		alg::bivec4 rotateAngle4D,
		glm::vec4 scale4D,
		float mass,
		float momentInertiaScalar,
		float mu,
		float restitution,
		bool isGravity,
		bool isFrozen,
		glm::vec4 velocity4D,
		alg::bivec4 angularVelocity4D,
		bool isSpecular,
		unsigned int texture3DIndex,
		glm::vec4 paintingColor,
		glm::vec4 metalColor,
		unsigned int colType,
		unsigned int shaderIndex,
		glm::vec4 animatePosition4D = glm::vec4(0.f),
		bool isSleep=false)
		: Object4D(objectName, primitive4D, position4D, rotateAngle4D, scale4D, mu, restitution, colType, shaderIndex)
	{
		this->pPosition4D = position4D;
		this->mass = mass;
		this->animatePosition4D = glm::vec4(0.f);
		this->velocity4D = velocity4D;
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
		this->restitution = restitution;
		this->momentInertiaScalar= momentInertiaScalar;
		this->trail4D = new Trail4D();
	}

	RigidBody4D(const char* objectName,
		Primitive4D primitive4D,
		glm::vec4 position4D,
		alg::rotor4 rotation4D,
		glm::vec4 scale4D,
		float mass,
		float momentInertiaScalar,
		float mu,
		float restitution,
		bool isGravity,
		bool isFrozen,
		glm::vec4 velocity4D,
		alg::bivec4 angularVelocity4D,
		bool isSpecular,
		unsigned int texture3DIndex,
		glm::vec4 paintingColor,
		glm::vec4 metalColor,
		unsigned int colType,
		unsigned int shaderIndex,
		glm::vec4 animatePosition4D = glm::vec4(0.f),
		bool isSleep = false)
		: Object4D(objectName, primitive4D, position4D, rotation4D, scale4D, mu, restitution, colType, shaderIndex)
	{
		this->pPosition4D = position4D;
		this->mass = mass;
		this->animatePosition4D = animatePosition4D;
		this->velocity4D = velocity4D;
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
		this->restitution = restitution;
		this->momentInertiaScalar = momentInertiaScalar;
		this->trail4D = new Trail4D();
	}

	~RigidBody4D()
	{
		this->trail4D = nullptr,delete this->trail4D;
		for (ForceSystem4D* i : this->forceSystems4D) { i = nullptr, delete i;}
	}

	bool is_static()
	{
		return this->isFrozen || this->isBeyond;
	}

	void render(Texture3D* texture3D, Shader* shader)
	{
		texture3D->bind(0);
		shader->use();//Update uniforms	
		shader->set1i(this->isSpecular, "isSpecular");//Update uniforms	
		shader->setVec4f(this->paintingColor, "paintingColor");
		shader->setVec4f(this->metalColor, "metalColor");
		this->mesh4D->render(shader); //Activates shader also			
	}

	void render_frame(Shader* shader)
	{
		shader->use();//Update uniforms	
		this->mesh4D->render2(shader); //Activates shader also			
	}

	void render_trail4D(Shader* shader)
	{
		this->trail4D->render(shader);
	}
	void update_trail4D(const float dt,float curTime)
	{
		this->trail4D->update_trail4D(this->position4D,this->is_static(), dt, curTime);
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
		unsigned int shaderIndex
	) : Object4D(objectName, primitive4D, glm::vec4(0.f), rotateAngle4D, scale4D,0.f,0.f, 0, shaderIndex)
	{
	}

	~Sky_Box4D()
	{
	}

	void switch_mode(unsigned type, Texture3D* texture3D,glm::vec3 texScale,glm::vec4 paintingColor,Shader* shader)
	{
		texture3D->bind(4);
		shader->use();
		shader->set1i(type, "type");
		shader->setVec3f(texScale, "texScale");
		shader->setVec4f(paintingColor, "paintingColor");
	}

	//Functions
	void render(Shader* shader)
	{
		shader->use();
		//Update uniforms	
		this->mesh4D->render(shader); //Activates shader also			
	}
};


class Water4D : public Object4D
{
private:
public:
	Water4D(
		const char* objectName,
		Primitive4D primitive4D,
		glm::vec4 position4D,
		glm::vec4 scale4D,
		unsigned int colType,
		unsigned int shaderIndex
	) : Object4D(objectName, primitive4D, position4D, alg::bivec4(0,0,0,0,0,0), scale4D,0.f,0.f, colType, shaderIndex)
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
		this->mesh4D->render(shader); //Activates shader also			
	}
};

static void update_water4d(std::vector<Water4D*> waters4D, Shader* type1, Shader* type2)
{
	if (waters4D.size() != 0)
	{
		char ss[256];
		GLint i0 = 0;
		for (size_t i = 0; i < waters4D.size(); i++)
		{
			snprintf(ss, 255, "waterArea4D[%d].position4D", i0);
			type1->use();
			type1->setVec4f(waters4D[i]->position4D, ss);
			type2->use();
			type2->setVec4f(waters4D[i]->position4D, ss);
			snprintf(ss, 255, "waterArea4D[%d].scale4D", i0);
			type1->use();
			type1->setVec4f(waters4D[i]->scale4D, ss);
			type2->use();
			type2->setVec4f(waters4D[i]->scale4D, ss);
			i0++;
		}
		type1->use();
		type1->set1i(i0, "Water4DAmount");
		type2->use();
		type2->set1i(i0, "Water4DAmount");
	}
	if (waters4D.size() == 0)
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
	Terrain4D(
		const char* objectName,
		Primitive4D primitive4D,
		glm::vec4 position4D,
		glm::vec4 scale4D,
		float mu,
		float restitution,
		unsigned int colType,
		unsigned int shaderIndex
	) : Object4D(objectName, primitive4D, position4D, alg::bivec4(), scale4D, mu, restitution, colType, shaderIndex)
	{
	}

	~Terrain4D()
	{
	}
	void render(Shader* shader)
	{
		shader->use();
		//Update uniforms	
		this->mesh4D->render(shader); //Activates shader also			
	}
	void render_frame(Shader* shader)
	{
		shader->use();//Update uniforms	
		this->mesh4D->render2(shader); //Activates shader also			
	}
};

class Particle4D
{
public:
	unsigned int texture3Dindex;
	glm::vec4 position4D;
	glm::vec4 velocity4D;
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
	Mesh4D* mesh4D;
	Particle4D(unsigned int texture3Dindex,
		glm::vec4 position4D,
		glm::vec4 velocity4D,
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
		this->position4D = position4D;
		this->velocity4D = velocity4D;
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
		this->mesh4D = new Mesh4D(Particle4d(), position4D,update(alg::rotor4(), alg::bivec4(0, 0, 0, glm::radians(90.f), 0, 0)), glm::vec4(1.f));
	}
	~Particle4D()
	{
		this->mesh4D = nullptr,delete[] this->mesh4D;
	}
	void render(Texture3D* texture3D,Shader* shader)
	{
		texture3D->bind(0);
		shader->use();
		float size(glm::mix(this->startSize, this->endSize, this->time / this->duration));
		shader->set1f(size, "radius");
		shader->setVec4f(mix(this->startColor, this->endColor,this->time/ this->duration), "lightcolor");//Update uniforms	
		this->mesh4D->render(shader); //Activates shader also			
	}

	void render_frame(Shader* shader)
	{
		shader->use();//Update uniforms	
		float size = glm::mix(this->startSize, this->endSize, this->time / this->duration);
		shader->set1f(size, "radius");
		this->mesh4D->render2(shader); //Activates shader also			
	}

	void set_position4D(glm::vec4 position4D)
	{
		this->position4D = position4D;
		this->mesh4D->set_mesh_position4D(position4D);
	}
};

class Emitter4D
{
public:
	glm::vec4 position4D;
	glm::vec4 velocity4D;
	float duration;
	float time;
	float emitTime;
	std::vector<Particle4D*> particles4D;
	unsigned int type;
	Emitter4D(unsigned int type,
		glm::vec4 position4D,
		glm::vec4 velocity4D,
		float duration
	)
	{
		this->type = type;
		this->position4D = position4D;
		this->velocity4D = velocity4D;
		this->duration = duration;
		this->time = 0.f;
		this->emitTime = 0.f;
	}
	~Emitter4D()
	{
		for (Particle4D* i : this->particles4D) { i=nullptr,delete i; }
	}
};
