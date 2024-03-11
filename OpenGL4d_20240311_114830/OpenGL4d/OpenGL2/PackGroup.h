#pragma once
//#include"libs.h"
static glm::vec4 get_block_position4D(glm::vec4 position4D) {
 return glm::vec4(ceil(position4D.x / 64.f - 0.5f) * 64.f, ceil(position4D.y / 64.f - 0.5f) * 64.f, ceil(position4D.z / 64.f - 0.5f) * 64.f, ceil(position4D.w / 64.f - 0.5f) * 64.f);
}

static std::vector<Group*> pack_group(std::vector<Group*> groups,std::vector<Wall4D*>* walls4D, std::vector<Terrain4D*>* terrains4D)
{
	for (unsigned i=0;i< walls4D->size();i++)
	{
		if (length(walls4D[0][i]->scale4D) / 2.f < 32.f)
		{
			bool isOverlap0 = false;
			glm::vec4 groupPosition4D = get_block_position4D(walls4D[0][i]->position4D);
			for (Group* j : groups)
			{
				if (groupPosition4D == j->position4D)
				{
					j->walls4D.push_back(walls4D[0][i]);
					walls4D->erase(walls4D->begin() + i);
					i--;
					isOverlap0 = true;
				}
			}
			if (groups.size() == 0 || !isOverlap0)
			{
				groups.push_back(new Group(groupPosition4D));
				groups[groups.size() - 1]->walls4D.push_back(walls4D[0][i]);
				walls4D->erase(walls4D->begin() + i);
				i--;
			}
		}
	}

	for (unsigned i = 0; i < terrains4D->size(); i++)
	{
		if (length(terrains4D[0][i]->scale4D) / 2.f < 32.f)
		{
			bool isOverlap0 = false;
			glm::vec4 groupPosition4D = get_block_position4D(terrains4D[0][i]->position4D);
			for (Group* j : groups)
			{
				if (groupPosition4D == j->position4D)
				{
					j->terrains4D.push_back(terrains4D[0][i]);
					terrains4D->erase(terrains4D->begin() + i);
					i--;
					isOverlap0 = true;
				}
			}
			if (groups.size() == 0 || !isOverlap0)
			{
				groups.push_back(new Group(groupPosition4D));
				groups[groups.size() - 1]->terrains4D.push_back(terrains4D[0][i]);
				terrains4D->erase(terrains4D->begin() + i);
				i--;
			}
		}
	}

	return groups;
}