#pragma once
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
        sticks4D->erase(sticks4D->begin()+index);
    }
    else
    {
        springs4D->erase(springs4D->begin()+index - sticks4D->size());
    }
}

static void erase_joint4d(std::vector<Stick4D*>* sticks4D,std::vector<Spring4D*>* springs4D, std::vector<HingeConstraint4D*>* hingeConstraints, unsigned int index0)
{
    for (size_t k = 0; k < sticks4D->size(); k++)
    {
        if (sticks4D[0][k]->index1 == index0|| sticks4D[0][k]->index2 == index0)
        {
            sticks4D->erase(sticks4D->begin() + k);
            k--;
        }
    }

    for (size_t k = 0; k < springs4D->size(); k++)
    {
        if (springs4D[0][k]->index1 == index0|| springs4D[0][k]->index2 == index0)
        {
            springs4D->erase(springs4D->begin() + k);
            k--;
        }
    }

    for (size_t k = 0; k < hingeConstraints->size(); k++)
    {
        if (hingeConstraints[0][k]->index1 == index0|| hingeConstraints[0][k]->index2 == index0)
        {
            hingeConstraints->erase(hingeConstraints->begin() + k);
            k--;
        }
    }
}

static void shift_joint4d(std::vector<Stick4D*> sticks4D, std::vector<Spring4D*> springs4D, std::vector<HingeConstraint4D*> hingeConstraints, unsigned int index0,int count)
{
    for (Stick4D* stick4D : sticks4D)
    {
        if (stick4D->index1 >= index0)
        {
            stick4D->index1 += count;
        }
        if (stick4D->index2 >= index0)
        {
            stick4D->index2 += count;
        }
    }
    for (Spring4D* spring4D : springs4D)
    {
        if (spring4D->index1 >= index0)
        {
            spring4D->index1 += count;
        }
        if (spring4D->index2 >= index0)
        {
            spring4D->index2 += count;
        }
    }
    for (HingeConstraint4D* hingeConstraint : hingeConstraints)
    {
        if (hingeConstraint->index1 >= index0)
        {
            hingeConstraint->index1 += count;
        }
        if (hingeConstraint->index2 >= index0&& hingeConstraint->index2!=-1)
        {
            hingeConstraint->index2 += count;
        }
    }
}

static void erase_wall4d(std::vector<Group*> groups, int index)
{
    int groupIndex2 = 0;
    int wallIndex1 = 0;
    int wallIndex2 = index;
    for (int groupIndex1 = 0; groupIndex1 < groups.size(); groupIndex1++) {
        if (wallIndex1 + groups[groupIndex1]->walls4D.size() > index && wallIndex1 <= index)
        {
            wallIndex2 = index - wallIndex1;
            groupIndex2 = groupIndex1;
        }
        wallIndex1 += groups[groupIndex1]->walls4D.size();
    }
    groups[groupIndex2]->walls4D.erase(groups[groupIndex2]->walls4D.begin()+wallIndex2);
}

static size_t size_of_walls4d(std::vector<Group*> groups)
{
    size_t size = 0;;
    for (Group* group : groups)
    {
        size += group->walls4D.size();
    }
    return size;
}

static void erase_wall4d(std::vector<Group*> groups, std::vector < Wall4D*>* walls4D, int index)
{
    unsigned size = size_of_walls4d(groups);
    if (index < size)
    {
        int groupIndex2 = 0;
        int wallIndex1 = 0;
        int wallIndex2 = index;
        for (int groupIndex1 = 0; groupIndex1 < groups.size(); groupIndex1++) {
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

static bool is_wall4d_being_rendered(std::vector<Group*> groups, int index)
{
    bool isWall4DBeingRendered = false;
    int groupIndex2 = 0;
    int wallIndex1 = 0;
    int wallIndex2 = index;
    for (int groupIndex1 = 0; groupIndex1 < groups.size(); groupIndex1++) {
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
    bool isTerrain4DBeingRendered = false;
    int groupIndex2 = 0;
    int terrainIndex1 = 0;
    int terrainIndex2 = index;
    for (int groupIndex1 = 0; groupIndex1 < groups.size(); groupIndex1++) {
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
    int groupIndex2 = 0;
    int wallIndex1 = 0;
    for (int groupIndex1 = 0; groupIndex1 < groups.size(); groupIndex1++) {
        if (wallIndex1 + groups[groupIndex1]->walls4D.size() > index && wallIndex1 <= index)
        {
            groupIndex2 = groupIndex1;
        }
        wallIndex1 += groups[groupIndex1]->walls4D.size();
    }
    return groupIndex2;
}

static Wall4D* find_wall4d(std::vector<Group*> groups, int index)
{
    int groupIndex2 = 0;
    int wallIndex1 = 0;
    int wallIndex2 = index;
    for (int groupIndex1 = 0; groupIndex1 < groups.size(); groupIndex1++) {
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
    int groupIndex2 = 0;
    int terrainIndex1 = 0;
    int terrainIndex2 = index;
    for (int groupIndex1 = 0; groupIndex1 < groups.size(); groupIndex1++) {
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
        int groupIndex2 = 0;
        int wallIndex1 = 0;
        int wallIndex2 = index;
        for (int groupIndex1 = 0; groupIndex1 < groups.size(); groupIndex1++) {
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
        int groupIndex2 = 0;
        int wallIndex1 = 0;
        int wallIndex2 = index;
        for (int groupIndex1 = 0; groupIndex1 < groups.size(); groupIndex1++) {
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
    unsigned sizeOfObject = size_of_objects4d(a, b);
    if (index < sizeOfObject) return find_rigidbody4d(a, b, index);
    else return find_wall4d(groups, walls4D, dynamites4D,index - sizeOfObject);
}
static Object4D* find_object4d(std::vector<RigidBody4D*> a, std::vector<RigidBody4D*> b, std::vector<Group*> groups, vector<Wall4D*> walls4D, vector<Wall4D*> dynamites4D, vector<Stick4D*> sticks4D, vector<Spring4D*> springs4D, int index)
{
    unsigned sizeOfObject = size_of_objects4d(a, b);
    unsigned sizeOfObject2 = size_of_objects4d(a, b, groups, walls4D, dynamites4D);
    if (index < sizeOfObject) return find_rigidbody4d(a, b, index);
    else if (index < sizeOfObject2) return find_wall4d(groups, walls4D, dynamites4D, index - sizeOfObject);
    else  find_joint4d(sticks4D, springs4D, index - sizeOfObject2);
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
    for (int i = 0; i < groups.size(); i++)
    {
        if (groups[i]->isRender)
        {
            for (int j = 0; j < groups[i]->walls4D.size(); j++)
            {
                Wall4D* a = groups[i]->walls4D[j];
                if (a->isClamp)
                {
                    if (a->isFront)
                    {
                        distance = length(a->position4D - cameraPos);
                        if (a->diffuse3D->isTransparent||a->paintingColor.w<1.f)
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
    for (int i = 0; i < size_of_objects4d(rigidBodies4D, dynamites4D2); i++)
    {
        RigidBody4D* a = find_rigidbody4d(rigidBodies4D, dynamites4D2, i);
        distance = length(a->position4D - cameraPos);
        if (a->diffuse3D->isTransparent || a->paintingColor.w < 1.f)
        {
            renderIndices2->push_back(new RenderIndex(-1, i, distance));
        }
        else
        {
            renderIndices1->push_back(new RenderIndex(-1, i, distance));
        }
    }
    for (int i = 0; i < size_of_objects4d(walls4D, dynamites4D); i++)
    {
        Wall4D* a = find_wall4d(walls4D, dynamites4D, i);
        if (a->objectName == "Ground")
        {
            distance = 100000.f;
        }
        else
        {
            distance = length(find_wall4d(walls4D, dynamites4D, i)->position4D - cameraPos);
        }
        if (a->diffuse3D->isTransparent || a->paintingColor.w < 1.f)
        {
            renderIndices2->push_back(new RenderIndex(-2, i, distance));
        }
        else
        {
            renderIndices1->push_back(new RenderIndex(-2, i, distance));
        }
    }
    for (int i = 0; i < size_of_objects4d(sticks4D, springs4D); i++)
    {
        if (i < sticks4D.size())
        {
            if (sticks4D[i]->index2 != -1)
            {
                distance = length(sticks4D[i]->position4D - cameraPos);
                if (sticks4D[i]->diffuse3D->isTransparent || sticks4D[i]->paintingColor.w < 1.f)
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
            int i2 = i - sticks4D.size();
            if (springs4D[i2]->index2 != -1)
            {
                distance = length(springs4D[i2]->position4D - cameraPos);
                if (springs4D[i2]->diffuse3D->isTransparent || springs4D[i2]->paintingColor.w < 1.f)
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

static void sort_render_indices(std::vector<RenderIndex*>* renderIndices)
{
    int n = renderIndices->size();
    for (int i = 0; i < n - 1; i++)
    {
        int k = i;
        for (int j = i + 1; j < n; j++)
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