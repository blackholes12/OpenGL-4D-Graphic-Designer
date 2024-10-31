#pragma once
#define PARTICLE_TYPE_LAUNCHER 0
#define PARTICLE_TYPE_SHELL 1
#define PARTICLE_TYPE_SECONDARY_SHELL 2
struct Particle4D {
	float type;
	glm::vec4 position4D;
	glm::vec4 velocity4D;
	float radius;
	glm::vec4 color;
	float lifeTime;
};

class ParticleSystem4D
{
private:
	std::vector<Particle4D> particles4D;
	Shader* particleUpdateShader;
	bool isFirst;
	unsigned int currVB;
	unsigned int currTFB;
	GLuint particleBuffers[2];
	GLuint transformFeedbacks[2];
	int time;
	void start_shader(const int versionMajor, const int versionMinor)
	{
		this->particleUpdateShader = new Shader(versionMajor, versionMinor,
			"resourcefile/shaders/particle_system_update.vertex", "resourcefile/shaders/particle_system_update.geometry");
		const GLchar* varyings[6] = { "type1","position1","velocity1","radius1","color1","age1"};
		glTransformFeedbackVaryings(this->particleUpdateShader->get_id(), 6, varyings, GL_INTERLEAVED_ATTRIBS);
	}
public:
	ParticleSystem4D(const glm::vec4 position4D, const int versionMajor, const int versionMinor)
	{
		this->particles4D.push_back(Particle4D(PARTICLE_TYPE_LAUNCHER, position4D, glm::vec4(0.f), 0.f));
		glGenTransformFeedbacks(2, this->transformFeedbacks);
		glGenBuffers(2, this->particleBuffers);
		for (unsigned int i(0); i < 2; i++) {
			glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, this->transformFeedbacks[i]);
			glBindBuffer(GL_ARRAY_BUFFER, this->particleBuffers[i]);
			glBufferData(GL_ARRAY_BUFFER, this->particles4D.size(), this->particles4D.data(), GL_DYNAMIC_DRAW);
			glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, this->particleBuffers[i]);
		}
	}
	~ParticleSystem4D()
	{
		this->particleUpdateShader = nullptr, delete this->particleUpdateShader;
		glDeleteTransformFeedbacks(2, this->transformFeedbacks);
		glDeleteBuffers(2, this->particleBuffers);
	}

	void update_particles(const float dt)
	{
		glEnable(GL_RASTERIZER_DISCARD);
		glBindBuffer(GL_ARRAY_BUFFER, this->particleBuffers[currVB]);
		glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, this->transformFeedbacks[currTFB]);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, sizeof(Particle4D), (GLvoid*)offsetof(Particle4D, type)); // type
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Particle4D), (GLvoid*)offsetof(Particle4D, position4D)); // position
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Particle4D), (GLvoid*)offsetof(Particle4D, velocity4D)); // velocity
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Particle4D), (GLvoid*)offsetof(Particle4D, radius)); // radius
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Particle4D), (GLvoid*)offsetof(Particle4D, color)); // color
		glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(Particle4D), (GLvoid*)offsetof(Particle4D, lifeTime)); // lifetime
		glBeginTransformFeedback(GL_POINTS);
		if (this->isFirst) {
			glDrawArrays(GL_POINTS, 0, 1);
			this->isFirst = false;
		}
		else {
			glDrawTransformFeedback(GL_POINTS, this->transformFeedbacks[this->currVB]); //VB
		}
		glEndTransformFeedback();
		//glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER,0,this->particles4D.size(), &this->particles4D);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		glDisable(GL_RASTERIZER_DISCARD);
	}

	void render_particles(glm::vec4 cameraPosition4D)
	{
		glDisable(GL_RASTERIZER_DISCARD);
		glBindBuffer(GL_ARRAY_BUFFER, this->particleBuffers[this->currTFB]);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Particle4D), (GLvoid*)offsetof(Particle4D, position4D)); // position
		glDrawTransformFeedback(GL_POINTS, this->transformFeedbacks[this->currTFB]); //TFB
		glDisableVertexAttribArray(0);
	}

	//void update(const float dt, const glm::mat4 vP, const glm::vec4 cameraPosition4D)
	//{
	//	this->time += dt;
	//	update_particles(dt);
	//	//render_particles(vP, V);
	//	this->currVB = this->currTFB;
	//	this->currTFB = (this->currTFB + 1) & 0x1;
	//}
};
