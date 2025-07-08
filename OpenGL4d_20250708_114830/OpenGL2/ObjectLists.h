#pragma once

static bool is_terrain4d_being_rendered(std::vector<Group*> groups, int index)
{
    bool isTerrain4DBeingRendered(false);
    for (Group* group : groups)
    {
        for (size_t terrain4DIndex : group->terrains4DIndices)if (terrain4DIndex == index)isTerrain4DBeingRendered = group->isRender;
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
        return b[index - a.size()]->velocity4d;
    }
}

static size_t size_of_terrains4d(std::vector<Group*> groups)
{
    size_t size(0);
    for (Group* group : groups)
    {
        size += group->terrains4DIndices.size();
    }
    return size;
}

static size_t size_of_objects4d(vector<RigidBody4D*> rigidBodies4d, vector<Wall4D*> walls4d)
{
    return rigidBodies4d.size() + walls4d.size();
}

static size_t size_of_objects4d(vector<Stick4D*> sticks4d, vector<Spring4D*> springs4d)
{
    return sticks4d.size() + springs4d.size();
}

static size_t size_of_objects4d(vector<RigidBody4D*> rigidBodies4d, vector<Wall4D*> walls4d, vector<Stick4D*> sticks4d, vector<Spring4D*> springs4d)
{
    return rigidBodies4d.size() + walls4d.size() + sticks4d.size() + springs4d.size();
}

static Object4D* find_dynamite4d(std::vector<RigidBody4D*> a, std::vector<Wall4D*> b, DynamiteIndex* dynamiteIndices)
{
    size_t objectSize(a.size());
    if (dynamiteIndices->index < objectSize) return a[dynamiteIndices->index];
    else return b[dynamiteIndices->index - objectSize];
}

static size_t find_wall_index(std::vector<Group*> groups, int groupIndex, int wallIndex)
{
    return groups[groupIndex]->walls4DIndices[wallIndex];
}


//static int find_group_index(std::vector<Group*> groups, int index)
//{
//    size_t groupIndex2 = 0;
//    size_t wallIndex1 = 0;
//    for (size_t groupIndex1 = 0; groupIndex1 < groups.size(); groupIndex1++) {
//        if (wallIndex1 + groups[groupIndex1]->walls4d.size() > index && wallIndex1 <= index)
//        {
//            groupIndex2 = groupIndex1;
//        }
//        wallIndex1 += groups[groupIndex1]->walls4d.size();
//    }
//    return groupIndex2;
//}

//static int find_wall_index(std::vector<Group*> groups, int groupIndex,int wallIndex)
//{
//    int index(0);
//    for (size_t i(0); i < groupIndex; i++)
//    {
//        index += groups[i]->walls4d.size();
//    }
//    index += wallIndex;
//    return index;
//}

//static Wall4D* find_wall4d(std::vector<Group*> groups, int index)
//{
//    size_t groupIndex2 = 0;
//    size_t wallIndex1 = 0;
//    size_t wallIndex2 = index;
//    for (size_t groupIndex1 = 0; groupIndex1 < groups.size(); groupIndex1++) {
//        if (wallIndex1 + groups[groupIndex1]->walls4d.size() > index && wallIndex1 <= index)
//        {
//            wallIndex2 = index - wallIndex1;
//            groupIndex2 = groupIndex1;
//        }
//        wallIndex1 += groups[groupIndex1]->walls4d.size();
//    }
//    return groups[groupIndex2]->walls4d[wallIndex2];
//}

//static Terrain4D* find_terrain4d(std::vector<Group*> groups, int index)
//{
//    size_t groupIndex2 = 0;
//    size_t terrainIndex1 = 0;
//    size_t terrainIndex2 = index;
//    for (size_t groupIndex1 = 0; groupIndex1 < groups.size(); groupIndex1++) {
//        if (terrainIndex1 + groups[groupIndex1]->terrains4d.size() > index && terrainIndex1 <= index)
//        {
//            terrainIndex2 = index - terrainIndex1;
//            groupIndex2 = groupIndex1;
//        }
//        terrainIndex1 += groups[groupIndex1]->terrains4d.size();
//    }
//    return groups[groupIndex2]->terrains4d[terrainIndex2];
//}

//static Wall4D* find_wall4d(std::vector<Group*> groups, vector<Wall4D*> walls4d, int index)
//{
//    if (index < size_of_walls4d(groups))
//    {
//        size_t groupIndex2 = 0;
//        size_t wallIndex1 = 0;
//        size_t wallIndex2 = index;
//        for (size_t groupIndex1 = 0; groupIndex1 < groups.size(); groupIndex1++) {
//            if (wallIndex1 + groups[groupIndex1]->walls4d.size() > index && wallIndex1 <= index)
//            {
//                wallIndex2 = index - wallIndex1;
//                groupIndex2 = groupIndex1;
//            }
//            wallIndex1 += groups[groupIndex1]->walls4d.size();
//        }
//        return groups[groupIndex2]->walls4d[wallIndex2];
//    }
//    else
//    {
//        return walls4d[index - size_of_walls4d(groups)];
//    }
//}

//static Wall4D* find_wall4d(std::vector<Group*> groups, vector<Wall4D*> walls4d, vector<Wall4D*> dynamites4D, int index)
//{
//    if (index < size_of_walls4d(groups))
//    {
//        size_t groupIndex2 = 0;
//        size_t wallIndex1 = 0;
//        size_t wallIndex2 = index;
//        for (size_t groupIndex1 = 0; groupIndex1 < groups.size(); groupIndex1++) {
//            if (wallIndex1 + groups[groupIndex1]->walls4d.size() > index && wallIndex1 <= index)
//            {
//                wallIndex2 = index - wallIndex1;
//                groupIndex2 = groupIndex1;
//            }
//            wallIndex1 += groups[groupIndex1]->walls4d.size();
//        }
//        return groups[groupIndex2]->walls4d[wallIndex2];
//    }
//    if (index >= size_of_walls4d(groups) && index < size_of_walls4d(groups) + walls4d.size())
//    {
//        return walls4d[index - size_of_walls4d(groups)];
//    }
//    if (index >= size_of_walls4d(groups) + walls4d.size())
//    {
//        return dynamites4D[index - size_of_walls4d(groups) - walls4d.size()];
//    }
//}

static Object4D* find_joint4d(vector<Stick4D*> sticks4d, vector<Spring4D*> springs4d, size_t index)
{
    if (index < sticks4d.size()) return sticks4d[index];
    else return springs4d[index- sticks4d.size()];
}

static Object4D* find_object4d(std::vector<RigidBody4D*> a, vector<Wall4D*> walls4d, size_t index)
{
    size_t sizeOfObject = a.size();
    if (index < sizeOfObject) return a[index];
    else return walls4d[index - sizeOfObject];
}
static Object4D* find_object4d(std::vector<RigidBody4D*> a, vector<Wall4D*> walls4d, vector<Stick4D*> sticks4d, vector<Spring4D*> springs4d, size_t index)
{
    size_t sizeOfObject = a.size();
    size_t sizeOfObject2 = size_of_objects4d(a, walls4d);
    if (index < sizeOfObject) return a[index];
    else if (index < sizeOfObject2) return walls4d[index - sizeOfObject];
    else return find_joint4d(sticks4d, springs4d, index - sizeOfObject2);
}

static void erase_object4d(std::vector<RigidBody4D*>* a, vector<Wall4D*>* b, size_t index)
{
    if (index < a->size())
    {
        (*a)[index] = nullptr, free((*a)[index]);
        a->erase(a->begin() + index);
    }
    else
    {
        index -= a->size();
        (*b)[index] = nullptr, free((*b)[index]);
        b->erase(b->begin() + index);
    }
}

static void erase_dynamite4d(std::vector<RigidBody4D*>* a, std::vector<Wall4D*>* b, DynamiteIndex* dynamiteIndices)
{
    size_t objectSize(a->size());
    if (dynamiteIndices->index < objectSize)
    {
        a->erase(a->begin() + dynamiteIndices->index);
    }
    else
    {
        b->erase(b->begin() + dynamiteIndices->index - objectSize);
    }
}

static void erase_joint4d0(std::vector<Stick4D*>* sticks4d, std::vector<Spring4D*>* springs4d, int index)
{
    if (index < sticks4d->size())
    {
        (*sticks4d)[index] = nullptr, free((*sticks4d)[index]);
        sticks4d->erase(sticks4d->begin() + index);
    }
    else
    {
        index -= sticks4d->size();
        (*springs4d)[index] = nullptr, free((*springs4d)[index]);
        springs4d->erase(springs4d->begin() + index);
    }
}

static int erase_stick4d_indices(std::vector<Stick4D*>* sticks4d, size_t index)
{
    int count(0);
    for (size_t k(0); k < sticks4d->size(); k++)
    {
        if ((*sticks4d)[k]->index1 == index || (*sticks4d)[k]->index2.n == index)
        {
            sticks4d->erase(sticks4d->begin() + k);
            k--;
            count++;
        }
    }
    return count;
}

static int erase_spring4d_indices(std::vector<Spring4D*>* springs4d, size_t index)
{
    int count(0);
    for (size_t k(0); k < springs4d->size(); k++)
    {
        if ((*springs4d)[k]->index1 == index || (*springs4d)[k]->index2.n == index)
        {
            springs4d->erase(springs4d->begin() + k);
            k--;
            count++;
        }
    }
    return count;
}

static int erase_hinge_constraints_vec_indices(std::vector <std::vector<HingeConstraint4D*>>* hingeConstraintsVec, size_t index)
{
    int count(0);
    for (size_t k(0); k < hingeConstraintsVec->size(); k++)
    {
        if ((*hingeConstraintsVec)[k][0]->index1 == index || (*hingeConstraintsVec)[k][0]->index2.n == index)
        {
            hingeConstraintsVec->erase(hingeConstraintsVec->begin() + k);
            k--;
            count++;
        }
    }
    return count;
}

static void erase_joint4d(std::vector<Stick4D*>* sticks4d, std::vector<Spring4D*>* springs4d, std::vector <std::vector<HingeConstraint4D*>>* hingeConstraintsVec, size_t index)
{
    for (size_t k(0); k < sticks4d->size(); k++)
    {
        if ((*sticks4d)[k]->index1 == index || (*sticks4d)[k]->index2.n == index)
        {
            sticks4d->erase(sticks4d->begin() + k);
            k--;
        }
    }

    for (size_t k(0); k < springs4d->size(); k++)
    {
        if ((*springs4d)[k]->index1 == index || (*springs4d)[k]->index2.n == index)
        {
            springs4d->erase(springs4d->begin() + k);
            k--;
        }
    }

    for (size_t k(0); k < hingeConstraintsVec->size(); k++)
    {
        if ((*hingeConstraintsVec)[k][0]->index1 == index || (*hingeConstraintsVec)[k][0]->index2.n == index)
        {
            hingeConstraintsVec->erase(hingeConstraintsVec->begin() + k);
            k--;
        }
    }
}

static size_t erase_dynamite4d_indices(std::vector<DynamiteIndex*>* dynamiteIndices, size_t index)
{
    size_t count(0);
    for (size_t k(0); k < dynamiteIndices->size(); k++)
    {
        if ((*dynamiteIndices)[k]->index == index)
        {
            dynamiteIndices->erase(dynamiteIndices->begin() + k);
            k--;
            count++;
        }
    }
    return count;
}

static size_t erase_shift4d_indices(std::vector <Shift4D*>* shifts4d, size_t index)
{
    size_t count(0);
    for (size_t k(0); k < shifts4d->size(); k++)
    {
        if ((*shifts4d)[k]->index == index)
        {
            shifts4d->erase(shifts4d->begin() + k);
            k--;
            count++;
        }
    }
    return count;
}

static size_t erase_float4d_indices(std::vector <Float4D*>* floats4d, size_t index)
{
    size_t count(0);
    for (size_t k(0); k < floats4d->size(); k++)
    {
        if ((*floats4d)[k]->index == index)
        {
            floats4d->erase(floats4d->begin() + k);
            k--;
            count++;
        }
    }
    return count;
}

static size_t erase_rotate4d_indices(std::vector <Rotate4D*>* rotates4d, size_t index)
{
    size_t count(0);
    for (size_t k(0); k < rotates4d->size(); k++)
    {
        if ((*rotates4d)[k]->index1 == index || (*rotates4d)[k]->index2.n == index)
        {
            rotates4d->erase(rotates4d->begin() + k);
            k--;
            count++;
        }
    }
    return count;
}

static size_t erase_open_door4d_indices(std::vector < OpenDoor4D*>* openDoors4d, size_t index)
{
    size_t count(0);
    for (size_t k(0); k < openDoors4d->size(); k++)
    {
        if ((*openDoors4d)[k]->index == index)
        {
            openDoors4d->erase(openDoors4d->begin() + k);
            k--;
            count++;
        }
    }
    return count;
}

static void shift_stick4d_indices(std::vector<Stick4D*> sticks4d, size_t index, int count)
{
    for (Stick4D* stick4D : sticks4d)
    {
        if (stick4D->index1 >= index)
        {
            stick4D->index1 += count;
        }
        if(stick4D->index2.isValid)
        if (stick4D->index2.n >= index)
        {
            stick4D->index2.n += count;
        }
    }
}

static void shift_spring4d_indices(std::vector<Spring4D*> springs4d, size_t index, int count)
{
    for (Spring4D* spring4D : springs4d)
    {
        if (spring4D->index1 >= index)
        {
            spring4D->index1 += count;
        }
        if (spring4D->index2.isValid)
        if (spring4D->index2.n >= index)
        {
            spring4D->index2.n += count;
        }
    }
}

static void shift_hinge_constraints_vec_indices(std::vector <std::vector<HingeConstraint4D*>> hingeConstraintsVec, size_t index, int count)
{
    for (std::vector<HingeConstraint4D*> hingeConstraints : hingeConstraintsVec)
    {
        if (hingeConstraints[0]->index1 >= index)
        {
            for (HingeConstraint4D* hingeConstraint : hingeConstraints)
            {
                hingeConstraint->index1 += count;
            }
        }
        if (hingeConstraints[0]->index2.isValid)
        if (hingeConstraints[0]->index2.n >= index)
        {
            for (HingeConstraint4D* hingeConstraint : hingeConstraints)
            {
                hingeConstraint->index2.n += count;
            }
        }
    }
}

static void shift_joint4d(std::vector<Stick4D*> sticks4d, std::vector<Spring4D*> springs4d, std::vector <std::vector<HingeConstraint4D*>>* hingeConstraintsVec, size_t index, int count)
{
    for (Stick4D* stick4D : sticks4d)
    {
        if (stick4D->index1 >= index)
        {
            stick4D->index1 += count;
        } 
        if (stick4D->index2.isValid)
        if (stick4D->index2.n >= index)
        {
            stick4D->index2.n += count;
        }
    }
    for (Spring4D* spring4D : springs4d)
    {
        if (spring4D->index1 >= index)
        {
            spring4D->index1 += count;
        } 
        if (spring4D->index2.isValid)
        if (spring4D->index2.n >= index)
        {
            spring4D->index2.n += count;
        }
    }
    for (std::vector<HingeConstraint4D*> hingeConstraints : *hingeConstraintsVec)
    {
        if (hingeConstraints[0]->index1 >= index)
        {
            for (HingeConstraint4D* hingeConstraint : hingeConstraints)
            {
                hingeConstraint->index1 += count;
            }
        } 
        if (hingeConstraints[0]->index2.isValid)
        if (hingeConstraints[0]->index2.n >= index)
        {
            for (HingeConstraint4D* hingeConstraint : hingeConstraints)
            {
                hingeConstraint->index2.n += count;
            }
        }
    }
}

static void shift_constraint_indices(std::vector <std::vector<Constraint*>> constraintsVec, size_t index, int count)
{
    for (std::vector<Constraint*> constraints : constraintsVec)
    {
        if (constraints[0]->index1 >= index)
        {
            for (Constraint* constraint : constraints)
            {
                constraint->index1 += count;
            }
        }
        if (constraints[0]->index2!=-1)
            if (constraints[0]->index2 >= index)
            {
                for (Constraint* constraint : constraints)
                {
                    constraint->index2 += count;
                }
            }
    }
}

static void shift_dynamite4d_indices(std::vector<DynamiteIndex*> dynamiteIndices, size_t index, int count)
{
    for (DynamiteIndex* dynamiteIndex : dynamiteIndices)
    {
        if (dynamiteIndex->index >= index)
        {
            dynamiteIndex->index += count;
        }
    }
}

static void shift_shift4d_indices(std::vector <Shift4D*> shifts4d, size_t index, int count)
{
    for (Shift4D* shift4D : shifts4d)
    {
        if (shift4D->index >= index)
        {
            shift4D->index += count;
        }
    }
}

static void shift_float4d_indices(std::vector <Float4D*> floats4d, size_t index, int count)
{
    for (Float4D* float4D : floats4d)
    {
        if (float4D->index >= index)
        {
            float4D->index += count;
        }
    }
}

static void shift_rotate4d_indices(std::vector <Rotate4D*> rotates4d, size_t index, int count)
{
    for (Rotate4D* rotate4D : rotates4d)
    {
        if (rotate4D->index1 >= index)
        {
            rotate4D->index1 += count;
        }
        if (rotate4D->index2.isValid)
            if (rotate4D->index2.n >= index)
            {
                rotate4D->index2.n += count;
            }
    }
}

static void shift_open_door4d_indices(std::vector < OpenDoor4D*> openDoors4d, size_t index, int count)
{
    for (OpenDoor4D* openDoor4D : openDoors4d)
    {
        if (openDoor4D->index >= index)
        {
            openDoor4D->index += count;
        }
    }
}

static std::vector<size_t> shift_group(std::vector<size_t> groupIndices, std::vector<Group*>* groups,size_t index, int count)
{
    for (Group* group : *groups)
    {
        for (size_t wallIndex(0); wallIndex < group->walls4DIndices.size(); wallIndex++)
        {
            if (group->walls4DIndices[wallIndex] > index)
            {
                group->walls4DIndices[wallIndex] += count;
            }
            else if (group->walls4DIndices[wallIndex] == index)
            {
                group->walls4DIndices.erase(group->walls4DIndices.begin() + wallIndex);
                wallIndex--;
            }
        }
    }
    //for (size_t groupIndicesIndex(1); groupIndicesIndex < groupIndices.size(); groupIndicesIndex++)
    //{
    //if (group->walls4DIndices.size() == 0)
    //{
    //    groups.erase(groups.begin() + groupIndex);
    //    for (size_t groupIndicesIndex(1); groupIndicesIndex < groupIndices.size(); groupIndicesIndex++)
    //    {
    //        size_t groupIndex(groupIndices[groupIndicesIndex]);
    //        if (groupIndex > index)
    //        {
    //            groupIndices[groupIndicesIndex] += count;
    //        }
    //    }
    //    groupIndices.erase(groupIndices.begin() + groupIndicesIndex);
    //    groupIndicesIndex--;
    //}
    //}
    return groupIndices;
}

//static void erase_wall4d(std::vector<Group*> groups, int index)
//{
//    size_t groupIndex2(0);
//    size_t wallIndex1(0);
//    size_t wallIndex2(index);
//    for (int groupIndex1(0); groupIndex1 < groups.size(); groupIndex1++) {
//        if (wallIndex1 + groups[groupIndex1]->walls4d.size() > index && wallIndex1 <= index)
//        {
//            wallIndex2 = index - wallIndex1;
//            groupIndex2 = groupIndex1;
//        }
//        wallIndex1 += groups[groupIndex1]->walls4d.size();
//    }
//    groups[groupIndex2]->walls4d.erase(groups[groupIndex2]->walls4d.begin() + wallIndex2);
//}

//static void erase_wall4d(std::vector<Group*> groups, std::vector < Wall4D*>* walls4d, int index)
//{
//    unsigned size(size_of_walls4d(groups));
//    if (index < size)
//    {
//        size_t groupIndex2(0);
//        size_t wallIndex1(0);
//        size_t wallIndex2(index);
//        for (size_t groupIndex1(0); groupIndex1 < groups.size(); groupIndex1++) {
//            if (wallIndex1 + groups[groupIndex1]->walls4d.size() > index && wallIndex1 <= index)
//            {
//                wallIndex2 = index - wallIndex1;
//                groupIndex2 = groupIndex1;
//            }
//            wallIndex1 += groups[groupIndex1]->walls4d.size();
//        }
//        groups[groupIndex2]->walls4d.erase(groups[groupIndex2]->walls4d.begin() + wallIndex2);
//    }
//    else
//    {
//        walls4d->erase(walls4d->begin() + index - size);
//    }
//}

static void update_collide_indices(vector<RigidBody4D*> rigidBodies4d, std::vector<size_t> groupIndices, std::vector<Group*> groups, vector<Wall4D*> walls4d)
{
    for (size_t i(0);i< rigidBodies4d.size();i++)
    {
        RigidBody4D* r1 = rigidBodies4d[i];
        if (r1->colType != NONE)
        {
            if (!(r1->isSleep && r1->is_static()))
            {
                r1->rigidBodyIndices.clear();
                r1->wallIndices.clear();
                float radius1(alg::length(r1->scale4D) / 2.f + alg::length(r1->velocity4d) + 0.15f);
                for (size_t j(i + 1); j < rigidBodies4d.size(); j++)
                {
                    RigidBody4D* r2 = rigidBodies4d[j];
                    if (r2->colType != NONE)
                    {
                        if (!r2->isBeyond) {
                            float radius2(alg::length(r2->scale4D) / 2.f + alg::length(r2->velocity4d) + 0.15f);
                            if (alg::length(r1->position4d - r2->position4d) < radius1 + radius2)
                            {
                                r1->rigidBodyIndices.push_back(j);
                            }
                        }
                    }
                }
                for (size_t groupIndex : groupIndices)
                {
                    Group* j(groups[groupIndex]);
                    for (size_t k(0); k < j->walls4DIndices.size(); k++)
                    {
                        size_t wallIndex(j->walls4DIndices[k]);
                        Wall4D* w2 = walls4d[wallIndex];
                        if (w2->colType != NONE)
                        {
                            float radius2(alg::length(w2->scale4D) / 2.f + 0.15f);
                            if (alg::length(r1->position4d - w2->position4d) < radius1 + radius2)
                            {
                                r1->wallIndices.push_back(wallIndex);
                            }
                        }
                    }
                }
            }
        }
    }
}

static struct RenderIndex
{
    unsigned char type;
    size_t objectIndex;
    float distance;
    explicit RenderIndex(unsigned char type, size_t objectIndex, float distance)
    {
        this->type = type;
        this->objectIndex = objectIndex;
        this->distance = distance;
    }
};

static void update_render_indices(vector<RigidBody4D*> rigidBodies4d, std::vector<size_t> groupIndices, std::vector<Group*> groups, vector<Wall4D*> walls4d, std::vector<Stick4D*> sticks4d, std::vector<Spring4D*> springs4d, std::vector<RenderIndex*>* renderIndices1, std::vector<RenderIndex*>* renderIndices2, glm::vec4 cameraPos)
{
    renderIndices1->clear();
    renderIndices2->clear();
    float distance;
    for (size_t i(0); i < rigidBodies4d.size(); i++)
    {
        RigidBody4D* a(rigidBodies4d[i]);
        distance = alg::length(a->position4d - cameraPos);
        if (a->texture3DIndex == GLASS || a->texture3DIndex == GRID || a->paintingColor.w < 1.f)
        {
            renderIndices2->push_back(new RenderIndex(0, i, distance));
        }
        else
        {
            renderIndices1->push_back(new RenderIndex(0, i, distance));
        }
    }
    for (size_t groupIndex : groupIndices)
    {
        Group* i(groups[groupIndex]);
        for (size_t j(0); j < i->walls4DIndices.size(); j++)
        {
            size_t wallIndex(i->walls4DIndices[j]);
            Wall4D* a(walls4d[wallIndex]);
            if (a->isClamp && a->isFront)
            {
                if (a->objectName == "Ground")
                {
                    distance = 100000.f;
                }
                else
                {
                    distance = alg::length(a->position4d - cameraPos);
                }
                //if (i == 0)std::cout << "push" << '\n';
                if (a->texture3DIndex == GLASS || a->texture3DIndex == GRID || a->paintingColor.w < 1.f)
                {
                    renderIndices2->push_back(new RenderIndex(1, wallIndex, distance));
                }
                else
                {
                    renderIndices1->push_back(new RenderIndex(1, wallIndex, distance));
                }
            }
        }
    }
    for (size_t i(0); i < size_of_objects4d(sticks4d, springs4d); i++)
    {
        if (i < sticks4d.size())
        {
            distance = alg::length(sticks4d[i]->position4d - cameraPos);
            if (sticks4d[i]->texture3DIndex == GLASS || sticks4d[i]->texture3DIndex == GRID || sticks4d[i]->paintingColor.w < 1.f)
            {
                renderIndices2->push_back(new RenderIndex(2, i, distance));
            }
            else
            {
                renderIndices1->push_back(new RenderIndex(2, i, distance));
            }
        }
        else
        {
            size_t i2(i - sticks4d.size());
            distance = alg::length(springs4d[i2]->position4d - cameraPos);
            if (springs4d[i2]->texture3DIndex == GLASS || springs4d[i2]->texture3DIndex == GRID || springs4d[i2]->paintingColor.w < 1.f)
            {
                renderIndices2->push_back(new RenderIndex(2, i, distance));
            }
            else
            {
                renderIndices1->push_back(new RenderIndex(2, i, distance));
            }
        }
    }
}

static void update_render_indices_distance(vector<RigidBody4D*> rigidBodies4d, std::vector<Group*> groups, vector<Wall4D*> walls4d, std::vector<Stick4D*> sticks4d, std::vector<Spring4D*> springs4d, std::vector<RenderIndex*> renderIndices1, std::vector<RenderIndex*> renderIndices2, glm::vec4 cameraPos)
{
    for (size_t index(0); index < renderIndices1.size(); index++)
    {
        RenderIndex* i(renderIndices1[index]);
        if (i->type == 0)
        {
            i->distance = alg::length(rigidBodies4d[i->objectIndex]->position4d - cameraPos);
        }
        else if (i->type == 1)
        {
            i->distance = alg::length(walls4d[i->objectIndex]->position4d - cameraPos);
        }
        else if (i->type == 2)
        {
            if (i->objectIndex < sticks4d.size())
            {
                i->distance = alg::length(sticks4d[i->objectIndex]->position4d - cameraPos);
            }
            else
            {
                i->distance = alg::length(springs4d[i->objectIndex - sticks4d.size()]->position4d - cameraPos);
            }
        }
    }
    for (size_t index(0); index < renderIndices2.size(); index++)
    {
        RenderIndex* i(renderIndices2[index]);
        if (i->type == 0)
        {
            i->distance = alg::length(rigidBodies4d[i->objectIndex]->position4d - cameraPos);
        }
        else if (i->type == 1)
        {
            i->distance = alg::length(walls4d[i->objectIndex]->position4d - cameraPos);
        }
        else if (i->type == 2)
        {
            if (i->objectIndex < sticks4d.size())
            {
                i->distance = alg::length(sticks4d[i->objectIndex]->position4d - cameraPos);
            }
            else
            {
                i->distance = alg::length(springs4d[i->objectIndex - sticks4d.size()]->position4d - cameraPos);
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
            RenderIndex* rIK((*renderIndices)[k]);
            (*renderIndices)[k] = (*renderIndices)[i];
            (*renderIndices)[i] = rIK;
        }
    }
}

static std::vector<size_t> judge_groups(vector<RigidBody4D*> rigidBodies4d, std::vector<size_t> groupIndices, std::vector<Group*> groups,glm::vec4 cameraPos,int blockLoadDistance)
{
    if (groupIndices.size() == 1)
    {
        for (size_t groupIndex(1); groupIndex < groups.size(); groupIndex++)
        {
            Group* i(groups[groupIndex]);
            glm::vec4 relativePos4D(i->position4d - cameraPos);
            if (alg::length(relativePos4D) < (float)blockLoadDistance)
            {
                i->isRender = true;
                groupIndices.push_back(groupIndex);
            }
            else
            {
                i->isRender = false;
            }
        }
    }
    else
    {
        for (size_t groupIndicesIndex(1); groupIndicesIndex < groupIndices.size(); groupIndicesIndex++)
        {
            size_t groupIndex(groupIndices[groupIndicesIndex]);
            Group* i(groups[groupIndex]);
            glm::vec4 relativePos4D(i->position4d - cameraPos);
            if (alg::length(relativePos4D) < (float)blockLoadDistance)
            {
                for (size_t j(0); j < i->groupAroundIndices.size(); j++)
                {
                    if (groups[i->groupAroundIndices[j]]->isRender == false)
                    {
                        if (alg::length(groups[i->groupAroundIndices[j]]->position4d - cameraPos) < (float)blockLoadDistance)
                        {
                            groups[i->groupAroundIndices[j]]->isRender = true;
                            groupIndices.push_back(i->groupAroundIndices[j]);
                        }
                    }
                }
            }
            else
            {
                i->isRender = false;
                groupIndices.erase(groupIndices.begin() + groupIndicesIndex);
                groupIndicesIndex--;
            }
        }
    }

    for (size_t i(1); i < rigidBodies4d.size(); i++)
    {
        glm::vec4 relativePos4D(get_block_position4D(rigidBodies4d[i]->position4d) - cameraPos);
        if (alg::length(relativePos4D) > (float)blockLoadDistance)
        {
            rigidBodies4d[i]->isBeyond = true;
        }
        else 
        {
            rigidBodies4d[i]->isBeyond = false;
        }
    }
    return groupIndices;
}

static void judge_objects(std::vector<size_t> groupIndices, std::vector<Group*> groups, vector<Wall4D*> walls4d, vector<Terrain4D*> terrains4d, glm::vec4 cameraPos, glm::vec4 cameraFor, glm::vec4 cameraWDir, int objectLoadDistance)
{
    for (size_t groupIndex : groupIndices)
    {
        Group* i(groups[groupIndex]);
        for (size_t wallIndex : i->walls4DIndices)
        {
            Object4D* o(walls4d[wallIndex]);
            float lengthOfScale(alg::length(o->scale4D));
            glm::vec4 relativePos4D(o->position4d - cameraPos);
            if (alg::dot(cameraFor, relativePos4D) < -lengthOfScale / 2.f)
            {
                o->isFront = false;
            }
            else 
            {
                float lengthOfScale(alg::length(o->scale4D));
                glm::vec4 relativePos4D(o->position4d - cameraPos);
                if (alg::abs(alg::dot(cameraWDir, relativePos4D)) > lengthOfScale / 2.f + (float)objectLoadDistance)
                {
                    o->isClamp = false;
                }
                else
                {
                    o->isClamp = true;
                }
                o->isFront = true;
            }
        }
        for (size_t terrainIndex : i->terrains4DIndices)
        {
            Terrain4D* t(terrains4d[terrainIndex]);
            glm::vec4 relativePos4D(t->position4d + glm::vec4(0.f,(t->topHeight + t->bottomHeight)/2.f,0.f,0.f) - cameraPos);
            if (alg::dot(cameraFor, relativePos4D) < -(float)(terrainScale * terrainSize))
            {
                t->isFront = false;
            }
            else 
            {
                float lengthOfScale(alg::length(t->scale4D));
                glm::vec4 relativePos4D(t->position4d - cameraPos);
                if (alg::abs(alg::dot(cameraWDir, relativePos4D)) > lengthOfScale + (float)objectLoadDistance)
                {
                    t->isClamp = false;
                }
                else
                {
                    t->isClamp = true;
                }
                t->isFront = true;
            }
        }
    }
}

static void update_point_light4d_id(std::vector<PointLight4D*>* pointLights4d)
{
    for (size_t k(0); k < pointLights4d->size(); k++)
    {
        (*pointLights4d)[k]->id = k;
    }
}

static void update_components_index(std::vector<RigidBody4D*> a, vector<Wall4D*> b,
    std::vector<DynamiteIndex*> dynamiteIndices,
    std::vector<Stick4D*> sticks4d,
    std::vector<Spring4D*> springs4d,
    std::vector<std::vector<HingeConstraint4D*>> hingeConstraintsVec,
    std::vector<Shift4D*> shifts4d,
    std::vector<Float4D*> floats4d,
    std::vector<Rotate4D*> rotates4d,
    std::vector<OpenDoor4D*> openDoors4d)
{
    for (size_t i(0); i < dynamiteIndices.size(); i++) {
        DynamiteIndex* d(dynamiteIndices[i]);
        find_object4d(a, b, d->index)->componentsVec[DYNAMITE4D].push_back(i);
    }
    for (size_t i(0); i < sticks4d.size(); i++) {
        Stick4D* s(sticks4d[i]);
        find_object4d(a, b, s->index1)->componentsVec[STICK_JOINT].push_back(i);
        if (s->index2.isValid)find_object4d(a, b, s->index2.n)->componentsVec[STICK_JOINT].push_back(i);
    }
    for (size_t i(0); i < springs4d.size(); i++) {
        Spring4D* s(springs4d[i]);
        find_object4d(a, b, s->index1)->componentsVec[SPRING_JOINT].push_back(i);
        if (s->index2.isValid)find_object4d(a, b, s->index2.n)->componentsVec[SPRING_JOINT].push_back(i);
    }
    for (size_t i(0); i < hingeConstraintsVec.size(); i++) {
        std::vector<HingeConstraint4D*> hs(hingeConstraintsVec[i]);
        find_object4d(a, b, hs[0]->index1)->componentsVec[HINGE_CONSTRAINT].push_back(i);
        if (hs[0]->index2.isValid)find_object4d(a, b, hs[0]->index2.n)->componentsVec[HINGE_CONSTRAINT].push_back(i);
    }
    for (size_t i(0); i < shifts4d.size(); i++) {
        Shift4D* s(shifts4d[i]);
        find_object4d(a, b, s->index)->componentsVec[SHIFT4D_ANIMATION].push_back(i);
    }
    for (size_t i(0); i < floats4d.size(); i++) {
        Float4D* f(floats4d[i]);
        find_object4d(a, b, f->index)->componentsVec[FLOAT4D_ANIMATION].push_back(i);
    }
    for (size_t i(0); i < rotates4d.size(); i++) {
        Rotate4D* r(rotates4d[i]);
        find_object4d(a, b, r->index1)->componentsVec[ROTATE4D_ANIMATION].push_back(i);
        if (r->index2.isValid)find_object4d(a, b, r->index2.n)->componentsVec[ROTATE4D_ANIMATION].push_back(i);
    }
    for (size_t i(0); i < openDoors4d.size(); i++) {
        OpenDoor4D* o(openDoors4d[i]);
        find_object4d(a, b, o->index)->componentsVec[OPENDOOR4D_ANIMATION].push_back(i);
    }
}

static void delete_object4d(std::vector<RigidBody4D*>* a, std::vector<Wall4D*>* b,
    std::vector<size_t>* groupIndices,
    std::vector<Group*> groups,
    glm::vec4 cameraPos4D,
    std::vector<RenderIndex*>* renderIndices1,
    std::vector<RenderIndex*>* renderIndices2,
    std::vector <std::vector<Constraint*>>* constraintsVec,
    std::vector<DynamiteIndex*>* dynamiteIndices, 
    std::vector<Stick4D*>* sticks4d, 
    std::vector<Spring4D*>* springs4d, 
    std::vector<std::vector<HingeConstraint4D*>>* hingeConstraintsVec, 
    std::vector<Shift4D*>* shifts4d,
    std::vector<Float4D*>* floats4d,
    std::vector<Rotate4D*>* rotates4d,
    std::vector<OpenDoor4D*>* openDoors4d,
    size_t index)
{
    Object4D* o(find_object4d(*a, *b, index));
    for (size_t i(0); i < constraintsVec->size(); i++) {
        if ((*constraintsVec)[i][0]->index1 == index)
        {
            if ((*constraintsVec)[i][0]->index2 < a->size() && (*constraintsVec)[i][0]->index2 != -1)
            {
                (*a)[(*constraintsVec)[i][0]->index2]->isSleep = false, (*a)[(*constraintsVec)[i][0]->index2]->isContinueSleep = true;
            }
            for (Constraint* c : (*constraintsVec)[i])c = nullptr, free(c);
            constraintsVec->erase(constraintsVec->begin() + i);
        }
        else if ((*constraintsVec)[i][0]->index2 == index)
        {
            (*a)[(*constraintsVec)[i][0]->index1]->isSleep = false, (*a)[(*constraintsVec)[i][0]->index1]->isContinueSleep = true;
            for (Constraint* c : (*constraintsVec)[i])c = nullptr, free(c);
            constraintsVec->erase(constraintsVec->begin() + i);
        }
    }
    shift_constraint_indices(*constraintsVec, index, -1);
    if (o->componentsVec[DYNAMITE4D].size() > 0){
        for (size_t i(0); i < o->componentsVec[DYNAMITE4D].size(); i++) { 
            size_t componentIndex(o->componentsVec[DYNAMITE4D][i] - i); 
            (*dynamiteIndices)[componentIndex] = nullptr, free((*dynamiteIndices)[componentIndex]);
            dynamiteIndices->erase(dynamiteIndices->begin() + componentIndex); 
        }
        o->componentsVec[DYNAMITE4D].clear();
    }
    shift_dynamite4d_indices(*dynamiteIndices, index, -1);
    if (o->componentsVec[STICK_JOINT].size() > 0) {
        for (size_t i(0); i < o->componentsVec[STICK_JOINT].size(); i++) { 
            size_t componentIndex(o->componentsVec[STICK_JOINT][i] - i);
            (*sticks4d)[componentIndex] = nullptr, free((*sticks4d)[componentIndex]);
            sticks4d->erase(sticks4d->begin() + componentIndex);
        }
        o->componentsVec[STICK_JOINT].clear();
    }
    shift_stick4d_indices(*sticks4d, index, -1);
    if (o->componentsVec[SPRING_JOINT].size() > 0) {
        for (size_t i(0); i < o->componentsVec[SPRING_JOINT].size(); i++) { 
            size_t componentIndex(o->componentsVec[SPRING_JOINT][i] - i);
            (*springs4d)[componentIndex] = nullptr, free((*springs4d)[componentIndex]);
            springs4d->erase(springs4d->begin() + componentIndex);
        }
        o->componentsVec[SPRING_JOINT].clear();
    }
    shift_spring4d_indices(*springs4d, index, -1);
    if (o->componentsVec[HINGE_CONSTRAINT].size() > 0) {
        for (size_t i(0); i < o->componentsVec[HINGE_CONSTRAINT].size(); i++) { 
            size_t componentIndex(o->componentsVec[HINGE_CONSTRAINT][i] - i);
            for(HingeConstraint4D* h: (*hingeConstraintsVec)[componentIndex])h = nullptr, free(h);
            hingeConstraintsVec->erase(hingeConstraintsVec->begin() + componentIndex);
        }
        o->componentsVec[HINGE_CONSTRAINT].clear();
    }
    shift_hinge_constraints_vec_indices(*hingeConstraintsVec, index, -1);
    if (o->componentsVec[SHIFT4D_ANIMATION].size() > 0) {
        for (size_t i(0); i < o->componentsVec[SHIFT4D_ANIMATION].size(); i++) { 
            size_t componentIndex(o->componentsVec[SHIFT4D_ANIMATION][i] - i);
            (*shifts4d)[componentIndex] = nullptr, free((*shifts4d)[componentIndex]);
            shifts4d->erase(shifts4d->begin() + componentIndex);
        }
        o->componentsVec[SHIFT4D_ANIMATION].clear();
    }
    shift_shift4d_indices(*shifts4d, index, -1);
    if (o->componentsVec[FLOAT4D_ANIMATION].size() > 0) {
        for (size_t i(0); i < o->componentsVec[FLOAT4D_ANIMATION].size(); i++) { 
            size_t componentIndex(o->componentsVec[FLOAT4D_ANIMATION][i] - i);
            (*floats4d)[componentIndex] = nullptr, free((*floats4d)[componentIndex]);
            floats4d->erase(floats4d->begin() + componentIndex);
        }
        o->componentsVec[FLOAT4D_ANIMATION].clear();
    }
    shift_float4d_indices(*floats4d, index, -1);
    if (o->componentsVec[ROTATE4D_ANIMATION].size() > 0) {
        for (size_t i(0); i < o->componentsVec[ROTATE4D_ANIMATION].size(); i++) { 
            size_t componentIndex(o->componentsVec[ROTATE4D_ANIMATION][i] - i);
            (*rotates4d)[componentIndex] = nullptr, free((*rotates4d)[componentIndex]);
            rotates4d->erase(rotates4d->begin() + componentIndex);
        }
        o->componentsVec[ROTATE4D_ANIMATION].clear();
    }
    shift_rotate4d_indices(*rotates4d, index, -1);
    if (o->componentsVec[OPENDOOR4D_ANIMATION].size() > 0) {
        for (size_t i(0); i < o->componentsVec[OPENDOOR4D_ANIMATION].size(); i++) { 
            size_t componentIndex(o->componentsVec[OPENDOOR4D_ANIMATION][i] - i);
            (*openDoors4d)[componentIndex] = nullptr, free((*openDoors4d)[componentIndex]);
            openDoors4d->erase(openDoors4d->begin() + componentIndex);
        }
        o->componentsVec[OPENDOOR4D_ANIMATION].clear();
    }
    shift_open_door4d_indices(*openDoors4d, index, -1);

    bool isDeleteRigidBody(index < a->size());
    erase_object4d(a, b, index);
    if(!isDeleteRigidBody)*groupIndices = shift_group(*groupIndices, &groups, index - a->size(), -1);
    update_render_indices(*a, *groupIndices, groups, *b, *sticks4d, *springs4d, renderIndices1, renderIndices2, cameraPos4D);
    sort_render_indices(renderIndices1); sort_render_indices(renderIndices2);
    update_collide_indices(*a, *groupIndices, groups, *b);

    for (size_t i(0); i < size_of_objects4d(*a,*b); i++)
    {
        for (size_t j(0); j < OPENDOOR4D_ANIMATION + 1; j++)find_object4d(*a, *b, i)->componentsVec[j].clear();
    }
    update_components_index(*a, *b, *dynamiteIndices, *sticks4d, *springs4d, *hingeConstraintsVec, *shifts4d, *floats4d, *rotates4d, *openDoors4d);
    isObjectParameterUpdated0 = true;
}