#pragma once
//#include"Object.h"

class Demo4D
{
private:
public:
	std::vector<Wall4D*> walls4D;
	std::vector < RigidBody4D*> rigidBodies4D;
	Stick4D* stick4D;
	Spring4D* spring4D;
	Demo4D(){}
	Demo4D(Wall4D* wall4D)
	{
		this->walls4D.push_back(wall4D);
	}
	Demo4D(std::vector<Wall4D*> walls4D)
	{
		this->walls4D = walls4D;
	}
	Demo4D(RigidBody4D* rigidBody4D)
	{
		this->rigidBodies4D.push_back(rigidBody4D);
	}
	Demo4D(std::vector < RigidBody4D*> rigidBodies4D)
	{
		this->rigidBodies4D = rigidBodies4D;
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
		this->walls4D.clear();
		this->rigidBodies4D.clear();
		this->stick4D = nullptr;
		this->spring4D = nullptr;
	}
	~Demo4D() {
		for (Wall4D* i : this->walls4D) { i = nullptr, delete i;}
		for (RigidBody4D* i : this->rigidBodies4D) { i = nullptr, delete i;}
		this->stick4D = nullptr,delete this->stick4D;
		this->spring4D = nullptr,delete this->spring4D;
	}
};
