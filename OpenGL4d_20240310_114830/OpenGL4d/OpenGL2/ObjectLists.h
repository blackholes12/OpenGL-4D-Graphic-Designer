
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
    if (index >= size_of_walls4d(groups) && index < size_of_walls4d(groups)+walls4D.size())
    {
        return walls4D[index - size_of_walls4d(groups)];
    }
    if(index >= size_of_walls4d(groups) + walls4D.size())
    {
        return dynamites4D[index - size_of_walls4d(groups) - walls4D.size()];
    }
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
