#pragma once
class Controller
{
	public:
		unsigned int cameraIndex;
		unsigned int rigidBodyIndex;
		GLfloat walkSpeed;
		GLfloat runningSpeed;
		GLfloat flySpeed;
		GLfloat jumpSpeed;
		GLfloat sensitivity;
		glm::vec3 limitedVelocity4D;
		bool isRuning;
		bool isCrouch;
		Controller(unsigned int cameraIndex,unsigned int rigidBodyIndex)
		{
			this->cameraIndex = cameraIndex;
			this->rigidBodyIndex = rigidBodyIndex;
		}
		~Controller()
		{

		}
};
