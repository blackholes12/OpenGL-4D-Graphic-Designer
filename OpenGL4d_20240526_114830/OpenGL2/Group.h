#pragma once
//#include"Object.h"

class Group
{
private:
public:
	std::vector<Wall4D*> walls4D;
	std::vector<Terrain4D*> terrains4D;
	std::vector<PointLight4D*> pointLights4D;
	bool isRender=true;
	glm::vec4 position4D;
	Group(glm::vec4 position4D)
	{
		this->position4D = position4D;
	}
	~Group() {
		for (Wall4D* i : this->walls4D) { i = nullptr, delete i;}
		for (Terrain4D* i : this->terrains4D) { i = nullptr, delete i;}
		for (PointLight4D* i : this->pointLights4D) { i = nullptr, delete i;}
	}
};

static glm::vec4 get_block_position4D(glm::vec4 position4D) {
	return glm::vec4(ceil(position4D.x / 64.f - 0.5f) * 64.f, ceil(position4D.y / 64.f - 0.5f) * 64.f, ceil(position4D.z / 64.f - 0.5f) * 64.f, ceil(position4D.w / 64.f - 0.5f) * 64.f);
}

static void pack_group(std::vector<Group*>* groups, std::vector<Wall4D*>* walls4D, std::vector<Terrain4D*>* terrains4D, std::vector<PointLight4D*>* pointLights4D)
{
	for (size_t i(0); i < walls4D->size(); i++)
	{
		if ((*walls4D)[i]->scale4D.x * (*walls4D)[i]->scale4D.y * (*walls4D)[i]->scale4D.z * (*walls4D)[i]->scale4D.w <= 0.f)
		{
			walls4D->erase(walls4D->begin() + i);
			i--;
		}
		else
		{
			if (length((*walls4D)[i]->scale4D) / 2.f < 32.f)
			{
				bool isOverlap0(false);
				glm::vec4 groupPosition4D(get_block_position4D((*walls4D)[i]->position4D));
				for (Group* j : *groups)
				{
					if (groupPosition4D == j->position4D)
					{
						j->walls4D.push_back((*walls4D)[i]);
						walls4D->erase(walls4D->begin() + i);
						i--;
						isOverlap0 = true;
					}
				}
				if (groups->size() == 0 || !isOverlap0)
				{
					groups->push_back(new Group(groupPosition4D));
					(*groups)[groups->size() - 1]->walls4D.push_back((*walls4D)[i]);
					walls4D->erase(walls4D->begin() + i);
					i--;
				}
			}
		}
	}

	for (size_t i(0); i < terrains4D->size(); i++)
	{
		if (length((*terrains4D)[i]->scale4D) / 2.f < 32.f)
		{
			bool isOverlap0(false);
			glm::vec4 groupPosition4D(get_block_position4D((*terrains4D)[i]->position4D));
			for (Group* j : *groups)
			{
				if (groupPosition4D == j->position4D)
				{
					j->terrains4D.push_back((*terrains4D)[i]);
					terrains4D->erase(terrains4D->begin() + i);
					i--;
					isOverlap0 = true;
				}
			}
			if (groups->size() == 0 || !isOverlap0)
			{
				groups->push_back(new Group(groupPosition4D));
				(*groups)[groups->size() - 1]->terrains4D.push_back((*terrains4D)[i]);
				terrains4D->erase(terrains4D->begin() + i);
				i--;
			}
		}
	}

	//for (unsigned i = 0; i < pointLights4D->size(); i++)
	//{
	//	if ((*pointLights4D)[i]->index<0)
	//	{
	//		bool isOverlap0 = false;
	//		glm::vec4 groupPosition4D = get_block_position4D((*pointLights4D)[i]->position4D);
	//		for (Group* j : groups)
	//		{
	//			if (groupPosition4D == j->position4D)
	//			{
	//				j->pointLights4D.push_back((*pointLights4D)[i]);
	//				pointLights4D->erase(pointLights4D->begin() + i);
	//				i--;
	//				isOverlap0 = true;
	//			}
	//		}
	//		if (groups->size() == 0 || !isOverlap0)
	//		{
	//			groups->push_back(new Group(groupPosition4D));
	//			groups[groups->size() - 1]->pointLights4D.push_back((*pointLights4D)[i]);
	//			pointLights4D->erase(pointLights4D->begin() + i);
	//			i--;
	//		}
	//	}
	//}
}