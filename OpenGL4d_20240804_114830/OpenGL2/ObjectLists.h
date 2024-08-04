#pragma once

static size_t size_of_walls4d(std::vector<Group*> groups)
{
    size_t size(0);
    for (Group* group : groups)
    {
        size += group->walls4D.size();
    }
    return size;
}

static bool is_wall4d_being_rendered(std::vector<Group*> groups, int index)
{
    bool isWall4DBeingRendered(false);
    size_t groupIndex2(0);
    size_t wallIndex1(0);
    size_t wallIndex2(index);
    for (size_t groupIndex1(0); groupIndex1 < groups.size(); groupIndex1++) {
        if (wallIndex1 + groups[groupIndex1]->walls4D.size() > index && wallIndex1 <= index)
        {
            wallIndex2 = index - wallIndex1;
            groupIndex2 = groupIndex1;
        }
        wallIndex1 += groups[groupIndex1]->walls4D.size();
    }
    if (groups[groupIndex2]->isRender) {
        if (groups[groupIndex2]->walls4D[wallIndex2]->isClamp) {
            if (groups[groupIndex2]->walls4D[wallIndex2]->isFront) {
                isWall4DBeingRendered = true;
            }
        }
    }
    return isWall4DBeingRendered;
}

static bool is_terrain4d_being_rendered(std::vector<Group*> groups, int index)
{
    bool isTerrain4DBeingRendered(false);
    size_t groupIndex2(0);
    size_t terrainIndex1(0);
    size_t terrainIndex2(index);
    for (size_t groupIndex1(0); groupIndex1 < groups.size(); groupIndex1++) {
        if (terrainIndex1 + groups[groupIndex1]->terrains4D.size() > index && terrainIndex1 <= index)
        {
            terrainIndex2 = index - terrainIndex1;
            groupIndex2 = groupIndex1;
        }
        terrainIndex1 += groups[groupIndex1]->terrains4D.size();
    }
    if (groups[groupIndex2]->isRender) {
        if (groups[groupIndex2]->terrains4D[terrainIndex2]->isClamp) {
            if (groups[groupIndex2]->terrains4D[terrainIndex2]->isFront) {
                isTerrain4DBeingRendered = true;
            }
        }
    }
    return isTerrain4DBeingRendered;
}

static glm::vec4 get_dynamite4d_velocity(std::vector<Wall4D*> a, std::vector<RigidBody4D*> b, unsigned int index)
{
    if (index < a.size())
    {
        return glm::vec4(0.f);
    }
    else
    {
        return b[index - a.size()]->velocity4D;
    }
}

static size_t size_of_terrains4d(std::vector<Group*> groups)
{
    size_t size = 0;;
    for (Group* group : groups)
    {
        size += group->terrains4D.size();
    }
    return size;
}

static size_t size_of_objects4d(vector<RigidBody4D*> rigidBodies4D, vector<RigidBody4D*> dynamites4D2)
{
    return rigidBodies4D.size() + dynamites4D2.size();
}

static size_t size_of_objects4d(vector<RigidBody4D*> rigidBodies4D, std::vector<Group*> groups)
{
    return rigidBodies4D.size() + size_of_walls4d(groups);
}

static size_t size_of_objects4d(vector<RigidBody4D*> rigidBodies4D, vector<Wall4D*> walls4D)
{
    return rigidBodies4D.size() + walls4D.size();
}

static size_t size_of_objects4d(std::vector<Group*> groups, vector<Wall4D*> walls4D)
{
    return size_of_walls4d(groups) + walls4D.size();
}

static size_t size_of_objects4d(vector<Wall4D*> walls4D, vector<Wall4D*> dynamites4D)
{
    return walls4D.size() + dynamites4D.size();
}

static size_t size_of_objects4d(vector<Stick4D*> sticks4D, vector<Spring4D*> springs4D)
{
    return sticks4D.size() + springs4D.size();
}

static size_t size_of_objects4d(vector<RigidBody4D*> rigidBodies4D, vector<RigidBody4D*> dynamites4D2, std::vector<Group*> groups)
{
    return rigidBodies4D.size() + dynamites4D2.size() + size_of_walls4d(groups);
}

static size_t size_of_objects4d(vector<RigidBody4D*> dynamites4D2, std::vector<Group*> groups, vector<Wall4D*> walls4D)
{
    return dynamites4D2.size() + size_of_walls4d(groups) + walls4D.size();
}

static size_t size_of_objects4d(std::vector<Group*> groups, vector<Wall4D*> walls4D, vector<Wall4D*> dynamites4D)
{
    return size_of_walls4d(groups) + walls4D.size() + dynamites4D.size();
}

static size_t size_of_objects4d(vector<RigidBody4D*> rigidBodies4D, vector<RigidBody4D*> dynamites4D2, std::vector<Group*> groups, vector<Wall4D*> walls4D)
{
    return rigidBodies4D.size() + dynamites4D2.size() + size_of_walls4d(groups) + walls4D.size();
}

static size_t size_of_objects4d(vector<RigidBody4D*> rigidBodies4D, vector<RigidBody4D*> dynamites4D2, std::vector<Group*> groups, vector<Wall4D*> walls4D, vector<Wall4D*> dynamites4D)
{
    return rigidBodies4D.size() + dynamites4D2.size() + size_of_walls4d(groups) + walls4D.size() + dynamites4D.size();
}

static size_t size_of_objects4d(vector<RigidBody4D*> rigidBodies4D, vector<RigidBody4D*> dynamites4D2, std::vector<Group*> groups, vector<Wall4D*> walls4D, vector<Wall4D*> dynamites4D, vector<Stick4D*> sticks4D, vector<Spring4D*> springs4D)
{
    return rigidBodies4D.size() + dynamites4D2.size() + size_of_walls4d(groups) + walls4D.size() + dynamites4D.size() + sticks4D.size() + springs4D.size();
}

static RigidBody4D* find_rigidbody4d(std::vector<RigidBody4D*> a, std::vector<RigidBody4D*> b, unsigned int index)
{
    if (index < a.size())
    {
        return a[index];
    }
    else
    {
        return b[index - a.size()];
    }
}

static Object4D* find_object4d(std::vector<Object4D*> a, std::vector<Object4D*> b, unsigned int index)
{
    if (index < a.size())
    {
        return a[index];
    }
    else
    {
        return b[index - a.size()];
    }
}
static Object4D* find_dynamite4d(std::vector<Wall4D*> a, std::vector<RigidBody4D*> b, unsigned int index)
{
    if (index < a.size())
    {
        return a[index];
    }
    else
    {
        return b[index - a.size()];
    }
}

static int find_group_index(std::vector<Group*> groups, int index)
{
    size_t groupIndex2 = 0;
    size_t wallIndex1 = 0;
    for (size_t groupIndex1 = 0; groupIndex1 < groups.size(); groupIndex1++) {
        if (wallIndex1 + groups[groupIndex1]->walls4D.size() > index && wallIndex1 <= index)
        {
            groupIndex2 = groupIndex1;
        }
        wallIndex1 += groups[groupIndex1]->walls4D.size();
    }
    return groupIndex2;
}

static int find_wall_index(std::vector<Group*> groups, int groupIndex,int wallIndex)
{
    int index(0);
    for (size_t i(0); i < groupIndex; i++)
    {
        index += groups[i]->walls4D.size();
    }
    index += wallIndex;
    return index;
}

static Wall4D* find_wall4d(std::vector<Group*> groups, int index)
{
    size_t groupIndex2 = 0;
    size_t wallIndex1 = 0;
    size_t wallIndex2 = index;
    for (size_t groupIndex1 = 0; groupIndex1 < groups.size(); groupIndex1++) {
        if (wallIndex1 + groups[groupIndex1]->walls4D.size() > index && wallIndex1 <= index)
        {
            wallIndex2 = index - wallIndex1;
            groupIndex2 = groupIndex1;
        }
        wallIndex1 += groups[groupIndex1]->walls4D.size();
    }
    return groups[groupIndex2]->walls4D[wallIndex2];
}

static Terrain4D* find_terrain4d(std::vector<Group*> groups, int index)
{
    size_t groupIndex2 = 0;
    size_t terrainIndex1 = 0;
    size_t terrainIndex2 = index;
    for (size_t groupIndex1 = 0; groupIndex1 < groups.size(); groupIndex1++) {
        if (terrainIndex1 + groups[groupIndex1]->terrains4D.size() > index && terrainIndex1 <= index)
        {
            terrainIndex2 = index - terrainIndex1;
            groupIndex2 = groupIndex1;
        }
        terrainIndex1 += groups[groupIndex1]->terrains4D.size();
    }
    return groups[groupIndex2]->terrains4D[terrainIndex2];
}

static Wall4D* find_wall4d(std::vector<Group*> groups, vector<Wall4D*> walls4D, int index)
{
    if (index < size_of_walls4d(groups))
    {
        size_t groupIndex2 = 0;
        size_t wallIndex1 = 0;
        size_t wallIndex2 = index;
        for (size_t groupIndex1 = 0; groupIndex1 < groups.size(); groupIndex1++) {
            if (wallIndex1 + groups[groupIndex1]->walls4D.size() > index && wallIndex1 <= index)
            {
                wallIndex2 = index - wallIndex1;
                groupIndex2 = groupIndex1;
            }
            wallIndex1 += groups[groupIndex1]->walls4D.size();
        }
        return groups[groupIndex2]->walls4D[wallIndex2];
    }
    else
    {
        return walls4D[index - size_of_walls4d(groups)];
    }
}

static Wall4D* find_wall4d(std::vector<Group*> groups, vector<Wall4D*> walls4D, vector<Wall4D*> dynamites4D, int index)
{
    if (index < size_of_walls4d(groups))
    {
        size_t groupIndex2 = 0;
        size_t wallIndex1 = 0;
        size_t wallIndex2 = index;
        for (size_t groupIndex1 = 0; groupIndex1 < groups.size(); groupIndex1++) {
            if (wallIndex1 + groups[groupIndex1]->walls4D.size() > index && wallIndex1 <= index)
            {
                wallIndex2 = index - wallIndex1;
                groupIndex2 = groupIndex1;
            }
            wallIndex1 += groups[groupIndex1]->walls4D.size();
        }
        return groups[groupIndex2]->walls4D[wallIndex2];
    }
    if (index >= size_of_walls4d(groups) && index < size_of_walls4d(groups) + walls4D.size())
    {
        return walls4D[index - size_of_walls4d(groups)];
    }
    if (index >= size_of_walls4d(groups) + walls4D.size())
    {
        return dynamites4D[index - size_of_walls4d(groups) - walls4D.size()];
    }
}

static Wall4D* find_wall4d(vector<Wall4D*> walls4D, vector<Wall4D*> dynamites4D, int index)
{
    if (index < walls4D.size())
    {
        return walls4D[index];
    }
    if (index >= walls4D.size())
    {
        return dynamites4D[index - walls4D.size()];
    }
}

static Object4D* find_joint4d(vector<Stick4D*> sticks4D, vector<Spring4D*> springs4D, int index)
{
    if (index < sticks4D.size()) return sticks4D[index];
    else return springs4D[index- sticks4D.size()];
}

static Object4D* find_object4d(std::vector<RigidBody4D*> a, std::vector<RigidBody4D*> b, std::vector<Group*> groups, vector<Wall4D*> walls4D, vector<Wall4D*> dynamites4D, int index)
{
    size_t sizeOfObject = size_of_objects4d(a, b);
    if (index < sizeOfObject) return find_rigidbody4d(a, b, index);
    else return find_wall4d(groups, walls4D, dynamites4D,index - sizeOfObject);
}
static Object4D* find_object4d(std::vector<RigidBody4D*> a, std::vector<RigidBody4D*> b, std::vector<Group*> groups, vector<Wall4D*> walls4D, vector<Wall4D*> dynamites4D, vector<Stick4D*> sticks4D, vector<Spring4D*> springs4D, int index)
{
    size_t sizeOfObject = size_of_objects4d(a, b);
    size_t sizeOfObject2 = size_of_objects4d(a, b, groups, walls4D, dynamites4D);
    if (index < sizeOfObject) return find_rigidbody4d(a, b, index);
    else if (index < sizeOfObject2) return find_wall4d(groups, walls4D, dynamites4D, index - sizeOfObject);
    else return find_joint4d(sticks4D, springs4D, index - sizeOfObject2);
}

static void erase_rigidbody4d(std::vector<RigidBody4D*>* a, std::vector<RigidBody4D*>* b, unsigned int index)
{
    if (index < a->size())
    {
        a->erase(a->begin() + index);
    }
    else
    {
        b->erase(b->begin() + (index - a->size()));
    }
}

static void erase_dynamite4d(std::vector<Wall4D*>* a, std::vector<RigidBody4D*>* b, unsigned int index)
{
    if (index < a->size())
    {
        a->erase(a->begin() + index);
    }
    else
    {
        b->erase(b->begin() + (index - a->size()));
    }
}

static void erase_joint4d0(std::vector<Stick4D*>* sticks4D, std::vector<Spring4D*>* springs4D, unsigned int index)
{
    if (index < sticks4D->size())
    {
        sticks4D->erase(sticks4D->begin() + index);
    }
    else
    {
        springs4D->erase(springs4D->begin() + index - sticks4D->size());
    }
}

static void erase_joint4d(std::vector<Stick4D*>* sticks4D, std::vector<Spring4D*>* springs4D, std::vector <std::vector<HingeConstraint4D>>* hingeConstraintsVec, unsigned int index0)
{
    for (size_t k(0); k < sticks4D->size(); k++)
    {
        if ((*sticks4D)[k]->index1 == index0 || (*sticks4D)[k]->index2 == index0)
        {
            sticks4D->erase(sticks4D->begin() + k);
            k--;
        }
    }

    for (size_t k(0); k < springs4D->size(); k++)
    {
        if ((*springs4D)[k]->index1 == index0 || (*springs4D)[k]->index2 == index0)
        {
            springs4D->erase(springs4D->begin() + k);
            k--;
        }
    }

    for (size_t k(0); k < hingeConstraintsVec->size(); k++)
    {
        if ((*hingeConstraintsVec)[k][0].index1 == index0 || (*hingeConstraintsVec)[k][0].index2 == index0)
        {
            hingeConstraintsVec->erase(hingeConstraintsVec->begin() + k);
            k--;
        }
    }
}

static void shift_joint4d(std::vector<Stick4D*> sticks4D, std::vector<Spring4D*> springs4D, std::vector <std::vector<HingeConstraint4D>>* hingeConstraintsVec, unsigned int index0, int count)
{
    for (Stick4D* stick4D : sticks4D)
    {
        if (stick4D->index1 >= index0)
        {
            stick4D->index1 += count;
        } else
        if (stick4D->index2 >= index0 && stick4D->index2 != -1)
        {
            stick4D->index2 += count;
        }
    }
    for (Spring4D* spring4D : springs4D)
    {
        if (spring4D->index1 >= index0)
        {
            spring4D->index1 += count;
        } else
        if (spring4D->index2 >= index0 && spring4D->index2 != -1)
        {
            spring4D->index2 += count;
        }
    }
    for (std::vector<HingeConstraint4D>& hingeConstraints : *hingeConstraintsVec)
    {
        if (hingeConstraints[0].index1 >= index0)
        {
            for (HingeConstraint4D& hingeConstraint : hingeConstraints)
            {
                hingeConstraint.index1 += count;
            }
        } else
        if (hingeConstraints[0].index2 >= index0 && hingeConstraints[0].index2 != -1)
        {
            for (HingeConstraint4D& hingeConstraint : hingeConstraints)
            {
                hingeConstraint.index2 += count;
            }
        }
    }
}

static void erase_wall4d(std::vector<Group*> groups, int index)
{
    size_t groupIndex2(0);
    size_t wallIndex1(0);
    size_t wallIndex2(index);
    for (int groupIndex1(0); groupIndex1 < groups.size(); groupIndex1++) {
        if (wallIndex1 + groups[groupIndex1]->walls4D.size() > index && wallIndex1 <= index)
        {
            wallIndex2 = index - wallIndex1;
            groupIndex2 = groupIndex1;
        }
        wallIndex1 += groups[groupIndex1]->walls4D.size();
    }
    groups[groupIndex2]->walls4D.erase(groups[groupIndex2]->walls4D.begin() + wallIndex2);
}

static void erase_wall4d(std::vector<Group*> groups, std::vector < Wall4D*>* walls4D, int index)
{
    unsigned size(size_of_walls4d(groups));
    if (index < size)
    {
        size_t groupIndex2(0);
        size_t wallIndex1(0);
        size_t wallIndex2(index);
        for (size_t groupIndex1(0); groupIndex1 < groups.size(); groupIndex1++) {
            if (wallIndex1 + groups[groupIndex1]->walls4D.size() > index && wallIndex1 <= index)
            {
                wallIndex2 = index - wallIndex1;
                groupIndex2 = groupIndex1;
            }
            wallIndex1 += groups[groupIndex1]->walls4D.size();
        }
        groups[groupIndex2]->walls4D.erase(groups[groupIndex2]->walls4D.begin() + wallIndex2);
    }
    else
    {
        walls4D->erase(walls4D->begin() + index - size);
    }
}

static void update_collide_indices(vector<RigidBody4D*> rigidBodies4D, vector<RigidBody4D*> dynamites4D2, std::vector<Group*> groups, vector<Wall4D*> walls4D, vector<Wall4D*> dynamites4D)
{
    for (size_t i(0);i< size_of_objects4d(rigidBodies4D, dynamites4D2);i++)
    {
        RigidBody4D* r1 = find_rigidbody4d(rigidBodies4D, dynamites4D2,i);
        if (!(r1->isSleep&&r1->is_static()))
        {
            r1->rigidBodyIndices.clear();
            r1->groupWallIndices.clear();
            r1->wallIndices.clear();
            float radius1(length(r1->scale4D) / 2.f + length(r1->velocity4D)+4.f);
            for (size_t j(i+1); j < size_of_objects4d(rigidBodies4D, dynamites4D2); j++)
            {
                RigidBody4D* r2 = find_rigidbody4d(rigidBodies4D, dynamites4D2, j);
                //if (!r2->is_static())
                {
                    float radius2(length(r2->scale4D) / 2.f + length(r2->velocity4D)+4.f);
                    if (length(r1->position4D - r2->position4D) < radius1 + radius2)
                    {
                        r1->rigidBodyIndices.push_back(j);
                    }
                }
            }
            for (size_t j(0); j < groups.size(); j++)
            {
                if (groups[j]->isRender)
                {
                    for (size_t k(0); k < groups[j]->walls4D.size(); k++)
                    {
                        Wall4D* w2 = groups[j]->walls4D[k];
                        float radius2(length(w2->scale4D) / 2.f + 4.f);
                        if (length(r1->position4D - w2->position4D) < radius1 + radius2)
                        {
                            r1->groupWallIndices.push_back(WallIndex(j, k));
                        }
                    }
                }
            }
            for (size_t j(0); j < size_of_objects4d(walls4D, dynamites4D); j++)
            {
                Wall4D* w2 = find_wall4d(walls4D, dynamites4D,j);
                float radius2(length(w2->scale4D) / 2.f + 4.f);
                if (length(r1->position4D - w2->position4D) < radius1 + radius2)
                {
                    r1->wallIndices.push_back(j);
                }
            }
        }
    }
}

static struct RenderIndex
{
    int groupIndex;
    int objectIndex;
    float distance;
    explicit RenderIndex(int groupIndex, int objectIndex, float distance)
    {
        this->groupIndex = groupIndex;
        this->objectIndex = objectIndex;
        this->distance = distance;
    }
};

static void update_render_indices(vector<RigidBody4D*> rigidBodies4D, vector<RigidBody4D*> dynamites4D2, std::vector<Group*> groups, vector<Wall4D*> walls4D, vector<Wall4D*> dynamites4D, std::vector<Stick4D*> sticks4D, std::vector<Spring4D*> springs4D, std::vector<RenderIndex*>* renderIndices1, std::vector<RenderIndex*>* renderIndices2, glm::vec4 cameraPos)
{
    renderIndices1->clear();
    renderIndices2->clear();
    float distance;
    for (int i(0); i < groups.size(); i++)
    {
        if (groups[i]->isRender)
        {
            for (int j(0); j < groups[i]->walls4D.size(); j++)
            {
                Wall4D* a(groups[i]->walls4D[j]);
                if (a->isClamp)
                {
                    if (a->isFront)
                    {
                        distance = length(a->position4D - cameraPos);
                        if (a->texture3DIndex == GLASS || a->texture3DIndex == GRID || a->paintingColor.w < 1.f)
                        {
                            renderIndices2->push_back(new RenderIndex(i, j, distance));
                        }
                        else
                        {
                            renderIndices1->push_back(new RenderIndex(i, j, distance));
                        }
                    }
                }
            }
        }
    }
    for (int i(0); i < size_of_objects4d(rigidBodies4D, dynamites4D2); i++)
    {
        RigidBody4D* a(find_rigidbody4d(rigidBodies4D, dynamites4D2, i));
        distance = length(a->position4D - cameraPos);
        if (a->texture3DIndex == GLASS || a->texture3DIndex == GRID || a->paintingColor.w < 1.f)
        {
            renderIndices2->push_back(new RenderIndex(-1, i, distance));
        }
        else
        {
            renderIndices1->push_back(new RenderIndex(-1, i, distance));
        }
    }
    for (int i(0); i < size_of_objects4d(walls4D, dynamites4D); i++)
    {
        Wall4D* a(find_wall4d(walls4D, dynamites4D, i));
        if (a->objectName == "Ground")
        {
            distance = 100000.f;
        }
        else
        {
            distance = length(find_wall4d(walls4D, dynamites4D, i)->position4D - cameraPos);
        }
        if (a->texture3DIndex == GLASS || a->texture3DIndex == GRID || a->paintingColor.w < 1.f)
        {
            renderIndices2->push_back(new RenderIndex(-2, i, distance));
        }
        else
        {
            renderIndices1->push_back(new RenderIndex(-2, i, distance));
        }
    }
    for (size_t i(0); i < size_of_objects4d(sticks4D, springs4D); i++)
    {
        if (i < sticks4D.size())
        {
            if (sticks4D[i]->index2 != -1)
            {
                distance = length(sticks4D[i]->position4D - cameraPos);
                if (sticks4D[i]->texture3DIndex == GLASS || sticks4D[i]->texture3DIndex == GRID || sticks4D[i]->paintingColor.w < 1.f)
                {
                    renderIndices2->push_back(new RenderIndex(-3, i, distance));
                }
                else
                {
                    renderIndices1->push_back(new RenderIndex(-3, i, distance));
                }
            }
        }
        else
        {
            size_t i2(i - sticks4D.size());
            if (springs4D[i2]->index2 != -1)
            {
                distance = length(springs4D[i2]->position4D - cameraPos);
                if (springs4D[i2]->texture3DIndex == GLASS || springs4D[i2]->texture3DIndex == GRID || springs4D[i2]->paintingColor.w < 1.f)
                {
                    renderIndices2->push_back(new RenderIndex(-3, i, distance));
                }
                else
                {
                    renderIndices1->push_back(new RenderIndex(-3, i, distance));
                }
            }
        }
    }
}

static void update_render_indices_distance(vector<RigidBody4D*> rigidBodies4D, vector<RigidBody4D*> dynamites4D2, std::vector<Group*> groups, vector<Wall4D*> walls4D, vector<Wall4D*> dynamites4D, std::vector<Stick4D*> sticks4D, std::vector<Spring4D*> springs4D, std::vector<RenderIndex*> renderIndices1, std::vector<RenderIndex*> renderIndices2, glm::vec4 cameraPos)
{
    for (size_t index(0); index < renderIndices1.size(); index++)
    {
        RenderIndex* i(renderIndices1[index]);
        if (i->groupIndex > -1)
        {
            i->distance = length(groups[i->groupIndex]->walls4D[i->objectIndex]->position4D - cameraPos);
        }
        else if (i->groupIndex == -1)
        {
            i->distance = length(find_rigidbody4d(rigidBodies4D, dynamites4D2, i->objectIndex)->position4D - cameraPos);
        }
        else if (i->groupIndex == -2)
        {
            i->distance = length(find_wall4d(walls4D, dynamites4D, i->objectIndex)->position4D - cameraPos);
        }
        else if (i->groupIndex == -3)
        {
            if (i->objectIndex < sticks4D.size())
            {
                i->distance = length(sticks4D[i->objectIndex]->position4D - cameraPos);
            }
            else
            {
                i->distance = length(springs4D[i->objectIndex - sticks4D.size()]->position4D - cameraPos);
            }
        }
    }
    for (size_t index(0); index < renderIndices2.size(); index++)
    {
        RenderIndex* i(renderIndices2[index]);
        if (i->groupIndex > -1)
        {
            i->distance = length(groups[i->groupIndex]->walls4D[i->objectIndex]->position4D - cameraPos);
        }
        else if (i->groupIndex == -1)
        {
            i->distance = length(find_rigidbody4d(rigidBodies4D, dynamites4D2, i->objectIndex)->position4D - cameraPos);
        }
        else if (i->groupIndex == -2)
        {
            i->distance = length(find_wall4d(walls4D, dynamites4D, i->objectIndex)->position4D - cameraPos);
        }
        else if (i->groupIndex == -3)
        {
            if (i->objectIndex < sticks4D.size())
            {
                i->distance = length(sticks4D[i->objectIndex]->position4D - cameraPos);
            }
            else
            {
                i->distance = length(springs4D[i->objectIndex - sticks4D.size()]->position4D - cameraPos);
            }
        }
    }
}

static void sort_render_indices(std::vector<RenderIndex*>* renderIndices)
{
    int n(renderIndices->size());
    for (int i(0); i < n - 1; i++)
    {
        int k(i);
        for (int j(i + 1); j < n; j++)
        {
            if ((*renderIndices)[j]->distance < (*renderIndices)[k]->distance)
            {
                k = j;
            }
        }
        if (k != i)
        {
            std::swap((*renderIndices)[k], (*renderIndices)[i]);
        }
    }
}

static void judge_groups(vector<RigidBody4D*> rigidBodies4D, vector<RigidBody4D*> dynamites4D2, std::vector<Group*> groups,glm::vec4 cameraPos,int blockLoadDistance)
{
    for (Group* i : groups)
    {
        glm::vec4 relativePos4D(i->position4D - cameraPos);
        if (length(relativePos4D) > (float)blockLoadDistance)
        {
            i->isRender = false;
        }
        else 
        {
            i->isRender = true;
        }
    }

    for (int i(1); i < size_of_objects4d(rigidBodies4D, dynamites4D2); i++)
    {
        glm::vec4 relativePos4D(get_block_position4D(find_rigidbody4d(rigidBodies4D, dynamites4D2, i)->position4D) - cameraPos);
        if (length(relativePos4D) > (float)blockLoadDistance)
        {
            find_rigidbody4d(rigidBodies4D, dynamites4D2, i)->isBeyond = true;
        }
        else 
        {
            find_rigidbody4d(rigidBodies4D, dynamites4D2, i)->isBeyond = false;
        }
    }
}

static void judge_objects(std::vector<Group*> groups, glm::vec4 cameraPos, glm::vec4 cameraFor, glm::vec4 cameraWDir, int objectLoadDistance)
{
    for (Group* i : groups) {
        if (i->isRender)
        {
            for (Object4D* j : i->walls4D)
            {
                float lengthOfScale(length(j->scale4D));
                glm::vec4 relativePos4D(j->position4D - cameraPos);
                if (dot(cameraFor, relativePos4D) < -lengthOfScale / 2.f)
                {
                    j->isFront = false;
                }
                else {
                    j->isFront = true;
                }
            }
            for (Object4D* j : i->terrains4D)
            {
                float size(8);
                glm::vec4 relativePos4D(j->position4D + j->primitive4D.vertexData4D[11904] - cameraPos);
                if (dot(cameraFor, relativePos4D) < -size)
                {
                    j->isFront = false;
                }
                else {
                    j->isFront = true;
                }
            }
        }
    }
    for (Group* i : groups) {
        if (i->isRender)
        {
            for (Object4D* j : i->walls4D)
            {
                if (j->isFront) {
                    float lengthOfScale(length(j->scale4D));
                    glm::vec4 relativePos4D(j->position4D - cameraPos);
                    if (abs(dot(cameraWDir, relativePos4D)) > lengthOfScale / 2.f + (float)objectLoadDistance)

                    {
                        j->isClamp = false;
                    }
                    else {
                        j->isClamp = true;
                    }
                }
            }
            for (Object4D* j : i->terrains4D)
            {
                if (j->isFront) {
                    float lengthOfScale(length(j->scale4D));
                    glm::vec4 relativePos4D(j->position4D - cameraPos);
                    if (abs(dot(cameraWDir, relativePos4D)) > lengthOfScale + (float)objectLoadDistance)

                    {
                        j->isClamp = false;
                    }
                    else {
                        j->isClamp = true;
                    }
                }
            }
        }
    }
}

//
//static void erase_render_index(std::vector<RenderIndex*>* renderIndices,int index1,int index2)
//{
//    for (size_t k = 0; k < renderIndices->size(); k++)
//    {
//        if ((*renderIndices)[k]->groupIndex == index1 && (*renderIndices)[k]->objectIndex == index2)
//        {
//            renderIndices->erase(renderIndices->begin() + k);
//            k--;
//        }
//    }
//}
//
//static void shift_render_index(std::vector<RenderIndex*>* renderIndices, int index1, int index2, int count)
//{
//    if (index1 >= 0)
//    {
//        for (size_t k = 0; k < renderIndices->size(); k++)
//        {
//            if ((*renderIndices)[k]->groupIndex == index1)
//            {
//                if ((*renderIndices)[k]->objectIndex >= index2)
//                {
//                    (*renderIndices)[k]->objectIndex += count;
//                }
//            }
//        }
//    }
//    else if (index1 == -1)
//    {
//        for (size_t k = 0; k < renderIndices->size(); k++)
//        {
//            if ((*renderIndices)[k]->objectIndex >= index2)
//            {
//                (*renderIndices)[k]->objectIndex += count;
//            }
//        }
//    }
//    else if (index1 == -2)
//    {
//        for (size_t k = 0; k < renderIndices->size(); k++)
//        {
//            if ((*renderIndices)[k]->objectIndex >= index2)
//            {
//                (*renderIndices)[k]->objectIndex += count;
//            }
//        }
//    }
//}