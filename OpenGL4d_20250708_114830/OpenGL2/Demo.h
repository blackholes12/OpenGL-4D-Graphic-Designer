#pragma once
//#include"Object.h"

class Demo4D
{
private:
public:
	PointLight4D* pointLight4D;
	std::vector<Wall4D*> walls4d;
	std::vector < RigidBody4D*> rigidBodies4d;
	Stick4D* stick4D;
	Spring4D* spring4D;
	Demo4D(){}
	Demo4D(PointLight4D* pointLight4D)
	{
		this->pointLight4D = pointLight4D;
	}
	Demo4D(Wall4D* wall4D)
	{
		this->walls4d.push_back(wall4D);
	}
	Demo4D(std::vector<Wall4D*> walls4d)
	{
		this->walls4d = walls4d;
	}
	Demo4D(RigidBody4D* rigidBody4D)
	{
		this->rigidBodies4d.push_back(rigidBody4D);
	}
	Demo4D(std::vector < RigidBody4D*> rigidBodies4d)
	{
		this->rigidBodies4d = rigidBodies4d;
	}
	Demo4D(Stick4D* stick4D)
	{
		this->stick4D = stick4D;
	}
	Demo4D(Spring4D* spring4D)
	{
		this->spring4D = spring4D;
	}
	void clear()
	{
		this->walls4d.clear();
		this->rigidBodies4d.clear();
		this->stick4D = nullptr;
		this->spring4D = nullptr;
	}
	~Demo4D() {
		delete this->pointLight4D;
		for (Wall4D* i : this->walls4d) { delete i;}
		for (RigidBody4D* i : this->rigidBodies4d) { delete i;}
		delete this->stick4D;
		delete this->spring4D;
	}
};
