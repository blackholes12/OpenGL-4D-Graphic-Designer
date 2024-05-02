#pragma once
//#include"Object.h"

class Group
{
private:
public:
	std::vector<Wall4D*> walls4D;
	std::vector<Terrain4D*> terrains4D;
	bool isRender=true;
	glm::vec4 position4D;
	Group(glm::vec4 position4D)
	{
		this->position4D = position4D;
	}
	~Group() {
		for (Wall4D* i : this->walls4D) { delete i; i = nullptr; }
		for (Terrain4D* i : this->terrains4D) { delete i; i = nullptr;}
	}
};