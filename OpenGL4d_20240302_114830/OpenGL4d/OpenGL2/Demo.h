#pragma once
#include"Object.h"

class Demo4D
{
private:
public:
	std::vector<Wall4D*> walls4D;
	std::vector < RigidBody4D*> rigidBodies4D;
	Stick4D* stick4D;
	Spring4D* spring4D;
	Demo4D()
	{
	}
	void clear()
	{
		this->walls4D.clear();
		this->rigidBodies4D.clear();
		this->stick4D = nullptr;
		this->spring4D = nullptr;
	}
	~Demo4D() {
		for (Wall4D* i : this->walls4D) { delete i; }
		for (RigidBody4D* i : this->rigidBodies4D) { delete i; }
		delete this->stick4D;
		delete this->spring4D;
	}
};
