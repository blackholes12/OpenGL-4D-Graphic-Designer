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
        return b[index - a.size()]->velocity4D;
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

static size_t size_of_objects4d(vector<RigidBody4D*> rigidBodies4D, vector<Wall4D*> walls4D)
{
    return rigidBodies4D.size() + walls4D.size();
}

static size_t size_of_objects4d(vector<Stick4D*> sticks4D, vector<Spring4D*> springs4D)
{
    return sticks4D.size() + springs4D.size();
}

static size_t size_of_objects4d(vector<RigidBody4D*> rigidBodies4D, vector<Wall4D*> walls4D, vector<Stick4D*> sticks4D, vector<Spring4D*> springs4D)
{
    return rigidBodies4D.size() + walls4D.size() + sticks4D.size() + springs4D.size();
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
//        if (wallIndex1 + groups[groupIndex1]->walls4D.size() > index && wallIndex1 <= index)
//        {
//            groupIndex2 = groupIndex1;
//        }
//        wallIndex1 += groups[groupIndex1]->walls4D.size();
//    }
//    return groupIndex2;
//}

//static int find_wall_index(std::vector<Group*> groups, int groupIndex,int wallIndex)
//{
//    int index(0);
//    for (size_t i(0); i < groupIndex; i++)
//    {
//        index += groups[i]->walls4D.size();
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
//        if (wallIndex1 + groups[groupIndex1]->walls4D.size() > index && wallIndex1 <= index)
//        {
//            wallIndex2 = index - wallIndex1;
//            groupIndex2 = groupIndex1;
//        }
//        wallIndex1 += groups[groupIndex1]->walls4D.size();
//    }
//    return groups[groupIndex2]->walls4D[wallIndex2];
//}

//static Terrain4D* find_terrain4d(std::vector<Group*> groups, int index)
//{
//    size_t groupIndex2 = 0;
//    size_t terrainIndex1 = 0;
//    size_t terrainIndex2 = index;
//    for (size_t groupIndex1 = 0; groupIndex1 < groups.size(); groupIndex1++) {
//        if (terrainIndex1 + groups[groupIndex1]->terrains4D.size() > index && terrainIndex1 <= index)
//        {
//            terrainIndex2 = index - terrainIndex1;
//            groupIndex2 = groupIndex1;
//        }
//        terrainIndex1 += groups[groupIndex1]->terrains4D.size();
//    }
//    return groups[groupIndex2]->terrains4D[terrainIndex2];
//}

//static Wall4D* find_wall4d(std::vector<Group*> groups, vector<Wall4D*> walls4D, int index)
//{
//    if (index < size_of_walls4d(groups))
//    {
//        size_t groupIndex2 = 0;
//        size_t wallIndex1 = 0;
//        size_t wallIndex2 = index;
//        for (size_t groupIndex1 = 0; groupIndex1 < groups.size(); groupIndex1++) {
//            if (wallIndex1 + groups[groupIndex1]->walls4D.size() > index && wallIndex1 <= index)
//            {
//                wallIndex2 = index - wallIndex1;
//                groupIndex2 = groupIndex1;
//            }
//            wallIndex1 += groups[groupIndex1]->walls4D.size();
//        }
//        return groups[groupIndex2]->walls4D[wallIndex2];
//    }
//    else
//    {
//        return walls4D[index - size_of_walls4d(groups)];
//    }
//}

//static Wall4D* find_wall4d(std::vector<Group*> groups, vector<Wall4D*> walls4D, vector<Wall4D*> dynamites4D, int index)
//{
//    if (index < size_of_walls4d(groups))
//    {
//        size_t groupIndex2 = 0;
//        size_t wallIndex1 = 0;
//        size_t wallIndex2 = index;
//        for (size_t groupIndex1 = 0; groupIndex1 < groups.size(); groupIndex1++) {
//            if (wallIndex1 + groups[groupIndex1]->walls4D.size() > index && wallIndex1 <= index)
//            {
//                wallIndex2 = index - wallIndex1;
//                groupIndex2 = groupIndex1;
//            }
//            wallIndex1 += groups[groupIndex1]->walls4D.size();
//        }
//        return groups[groupIndex2]->walls4D[wallIndex2];
//    }
//    if (index >= size_of_walls4d(groups) && index < size_of_walls4d(groups) + walls4D.size())
//    {
//        return walls4D[index - size_of_walls4d(groups)];
//    }
//    if (index >= size_of_walls4d(groups) + walls4D.size())
//    {
//        return dynamites4D[index - size_of_walls4d(groups) - walls4D.size()];
//    }
//}

static Object4D* find_joint4d(vector<Stick4D*> sticks4D, vector<Spring4D*> springs4D, size_t index)
{
    if (index < sticks4D.size()) return sticks4D[index];
    else return springs4D[index- sticks4D.size()];
}

static Object4D* find_object4d(std::vector<RigidBody4D*> a, vector<Wall4D*> walls4D, size_t index)
{
    size_t sizeOfObject = a.size();
    if (index < sizeOfObject) return a[index];
    else return walls4D[index - sizeOfObject];
}
static Object4D* find_object4d(std::vector<RigidBody4D*> a, vector<Wall4D*> walls4D, vector<Stick4D*> sticks4D, vector<Spring4D*> springs4D, size_t index)
{
    size_t sizeOfObject = a.size();
    size_t sizeOfObject2 = size_of_objects4d(a, walls4D);
    if (index < sizeOfObject) return a[index];
    else if (index < sizeOfObject2) return walls4D[index - sizeOfObject];
    else return find_joint4d(sticks4D, springs4D, index - sizeOfObject2);
}

static void erase_object4d(std::vector<RigidBody4D*>* a, vector<Wall4D*>* b, size_t index)
{
    if (index < a->size())
    {
        a->erase(a->begin() + index);
    }
    else
    {
        b->erase(b->begin() + index - a->size());
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

static void erase_joint4d0(std::vector<Stick4D*>* sticks4D, std::vector<Spring4D*>* springs4D, int index)
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

static int erase_stick4d_indices(std::vector<Stick4D*>* sticks4D, size_t index)
{
    int count(0);
    for (size_t k(0); k < sticks4D->size(); k++)
    {
        if ((*sticks4D)[k]->index1 == index || (*sticks4D)[k]->index2->n == index)
        {
            sticks4D->erase(sticks4D->begin() + k);
            k--;
            count++;
        }
    }
    return count;
}

static int erase_spring4d_indices(std::vector<Spring4D*>* springs4D, size_t index)
{
    int count(0);
    for (size_t k(0); k < springs4D->size(); k++)
    {
        if ((*springs4D)[k]->index1 == index || (*springs4D)[k]->index2->n == index)
        {
            springs4D->erase(springs4D->begin() + k);
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
        if ((*hingeConstraintsVec)[k][0]->index1 == index || (*hingeConstraintsVec)[k][0]->index2->n == index)
        {
            hingeConstraintsVec->erase(hingeConstraintsVec->begin() + k);
            k--;
            count++;
        }
    }
    return count;
}

static void erase_joint4d(std::vector<Stick4D*>* sticks4D, std::vector<Spring4D*>* springs4D, std::vector <std::vector<HingeConstraint4D*>>* hingeConstraintsVec, size_t index0)
{
    for (size_t k(0); k < sticks4D->size(); k++)
    {
        if ((*sticks4D)[k]->index1 == index0 || (*sticks4D)[k]->index2->n == index0)
        {
            sticks4D->erase(sticks4D->begin() + k);
            k--;
        }
    }

    for (size_t k(0); k < springs4D->size(); k++)
    {
        if ((*springs4D)[k]->index1 == index0 || (*springs4D)[k]->index2->n == index0)
        {
            springs4D->erase(springs4D->begin() + k);
            k--;
        }
    }

    for (size_t k(0); k < hingeConstraintsVec->size(); k++)
    {
        if ((*hingeConstraintsVec)[k][0]->index1 == index0 || (*hingeConstraintsVec)[k][0]->index2->n == index0)
        {
            hingeConstraintsVec->erase(hingeConstraintsVec->begin() + k);
            k--;
        }
    }
}

static size_t erase_dynamite4d_indices(std::vector<DynamiteIndex*>* dynamiteIndices, size_t index0)
{
    size_t count(0);
    for (size_t k(0); k < dynamiteIndices->size(); k++)
    {
        if ((*dynamiteIndices)[k]->index == index0)
        {
            dynamiteIndices->erase(dynamiteIndices->begin() + k);
            k--;
            count++;
        }
    }
    return count;
}

static void erase_point_light4d(std::vector<PointLight4D*>* pointLights4D, Shader* type0, Shader* type1, Shader* type2, size_t index0)
{
    for (size_t k(0); k < pointLights4D->size(); k++)
    {
        if ((*pointLights4D)[k]->index->isValid)
        if ((*pointLights4D)[k]->index->n == index0)
        {
            pointLights4D->erase(pointLights4D->begin() + k);
            for (size_t j(k); j < pointLights4D->size(); j++)
            {
                (*pointLights4D)[j]->id--;
            }
            k--;
            update_point_light4d(*pointLights4D, type0, type1, type2);
        }
    }
}

static void shift_stick4d_indices(std::vector<Stick4D*> sticks4D, size_t index0, int count)
{
    for (Stick4D* stick4D : sticks4D)
    {
        if (stick4D->index1 >= index0)
        {
            stick4D->index1 += count;
        }
        if(stick4D->index2->isValid)
        if (stick4D->index2->n >= index0)
        {
            stick4D->index2->n += count;
        }
    }
}

static void shift_spring4d_indices(std::vector<Spring4D*> springs4D, size_t index0, int count)
{
    for (Spring4D* spring4D : springs4D)
    {
        if (spring4D->index1 >= index0)
        {
            spring4D->index1 += count;
        }
        if (spring4D->index2->isValid)
        if (spring4D->index2->n >= index0)
        {
            spring4D->index2->n += count;
        }
    }
}

static void shift_hinge_constraints_vec_indices(std::vector <std::vector<HingeConstraint4D*>>* hingeConstraintsVec, size_t index0, int count)
{
    for (std::vector<HingeConstraint4D*> hingeConstraints : *hingeConstraintsVec)
    {
        if (hingeConstraints[0]->index1 >= index0)
        {
            for (HingeConstraint4D* hingeConstraint : hingeConstraints)
            {
                hingeConstraint->index1 += count;
            }
        }
        if (hingeConstraints[0]->index2->isValid)
        if (hingeConstraints[0]->index2->n >= index0)
        {
            for (HingeConstraint4D* hingeConstraint : hingeConstraints)
            {
                hingeConstraint->index2->n += count;
            }
        }
    }
}

static void shift_joint4d(std::vector<Stick4D*> sticks4D, std::vector<Spring4D*> springs4D, std::vector <std::vector<HingeConstraint4D*>>* hingeConstraintsVec, size_t index0, int count)
{
    for (Stick4D* stick4D : sticks4D)
    {
        if (stick4D->index1 >= index0)
        {
            stick4D->index1 += count;
        } 
        if (stick4D->index2->isValid)
        if (stick4D->index2->n >= index0)
        {
            stick4D->index2->n += count;
        }
    }
    for (Spring4D* spring4D : springs4D)
    {
        if (spring4D->index1 >= index0)
        {
            spring4D->index1 += count;
        } 
        if (spring4D->index2->isValid)
        if (spring4D->index2->n >= index0)
        {
            spring4D->index2->n += count;
        }
    }
    for (std::vector<HingeConstraint4D*> hingeConstraints : *hingeConstraintsVec)
    {
        if (hingeConstraints[0]->index1 >= index0)
        {
            for (HingeConstraint4D* hingeConstraint : hingeConstraints)
            {
                hingeConstraint->index1 += count;
            }
        } 
        if (hingeConstraints[0]->index2->isValid)
        if (hingeConstraints[0]->index2->n >= index0)
        {
            for (HingeConstraint4D* hingeConstraint : hingeConstraints)
            {
                hingeConstraint->index2->n += count;
            }
        }
    }
}

static void shift_dynamite4d_indices(std::vector<DynamiteIndex*> dynamiteIndices, size_t index0, int count)
{
    for (DynamiteIndex* dynamiteIndex : dynamiteIndices)
    {
        if (dynamiteIndex->index >= index0)
        {
            dynamiteIndex->index += count;
        }
    }
}

static void shift_point_light4d(std::vector<PointLight4D*> pointLights4D, size_t index0, int count)
{
    for (PointLight4D* pointLight4D : pointLights4D)
    {
        if (pointLight4D->index->isValid)
        if (pointLight4D->index->n >= index0)
        {
            pointLight4D->index->n += count;
        }
    }
}

static std::vector<size_t> shift_group(std::vector<size_t> groupIndices, std::vector<Group*>* groups,size_t index0, int count)
{
    for (Group* group : *groups)
    {
        for (size_t wallIndex(0); wallIndex < group->walls4DIndices.size(); wallIndex++)
        {
            if (group->walls4DIndices[wallIndex] > index0)
            {
                group->walls4DIndices[wallIndex] += count;
            }
            else if (group->walls4DIndices[wallIndex] == index0)
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
    //        if (groupIndex > index0)
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
//        if (wallIndex1 + groups[groupIndex1]->walls4D.size() > index && wallIndex1 <= index)
//        {
//            wallIndex2 = index - wallIndex1;
//            groupIndex2 = groupIndex1;
//        }
//        wallIndex1 += groups[groupIndex1]->walls4D.size();
//    }
//    groups[groupIndex2]->walls4D.erase(groups[groupIndex2]->walls4D.begin() + wallIndex2);
//}

//static void erase_wall4d(std::vector<Group*> groups, std::vector < Wall4D*>* walls4D, int index)
//{
//    unsigned size(size_of_walls4d(groups));
//    if (index < size)
//    {
//        size_t groupIndex2(0);
//        size_t wallIndex1(0);
//        size_t wallIndex2(index);
//        for (size_t groupIndex1(0); groupIndex1 < groups.size(); groupIndex1++) {
//            if (wallIndex1 + groups[groupIndex1]->walls4D.size() > index && wallIndex1 <= index)
//            {
//                wallIndex2 = index - wallIndex1;
//                groupIndex2 = groupIndex1;
//            }
//            wallIndex1 += groups[groupIndex1]->walls4D.size();
//        }
//        groups[groupIndex2]->walls4D.erase(groups[groupIndex2]->walls4D.begin() + wallIndex2);
//    }
//    else
//    {
//        walls4D->erase(walls4D->begin() + index - size);
//    }
//}

static void update_collide_indices(vector<RigidBody4D*> rigidBodies4D, std::vector<size_t> groupIndices, std::vector<Group*> groups, vector<Wall4D*> walls4D)
{
    for (size_t i(0);i< rigidBodies4D.size();i++)
    {
        RigidBody4D* r1 = rigidBodies4D[i];
        if (r1->colType != NONE)
        {
            if (!(r1->isSleep && r1->is_static()))
            {
                r1->rigidBodyIndices.clear();
                r1->wallIndices.clear();
                float radius1(alg::length(r1->scale4D) / 2.f + alg::length(r1->velocity4D) + 4.f);
                for (size_t j(i + 1); j < rigidBodies4D.size(); j++)
                {
                    RigidBody4D* r2 = rigidBodies4D[j];
                    if (r2->colType != NONE)
                    {
                        float radius2(alg::length(r2->scale4D) / 2.f + alg::length(r2->velocity4D) + 4.f);
                        if (alg::length(r1->position4D - r2->position4D) < radius1 + radius2)
                        {
                            r1->rigidBodyIndices.push_back(j);
                        }
                    }
                }
                for (size_t groupIndex : groupIndices)
                {
                    Group* j(groups[groupIndex]);
                    for (size_t k(0); k < j->walls4DIndices.size(); k++)
                    {
                        size_t wallIndex(j->walls4DIndices[k]);
                        Wall4D* w2 = walls4D[wallIndex];
                        if (w2->colType != NONE)
                        {
                            float radius2(alg::length(w2->scale4D) / 2.f + 4.f);
                            if (alg::length(r1->position4D - w2->position4D) < radius1 + radius2)
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

static void update_render_indices(vector<RigidBody4D*> rigidBodies4D, std::vector<size_t> groupIndices, std::vector<Group*> groups, vector<Wall4D*> walls4D, std::vector<Stick4D*> sticks4D, std::vector<Spring4D*> springs4D, std::vector<RenderIndex*>* renderIndices1, std::vector<RenderIndex*>* renderIndices2, glm::vec4 cameraPos)
{
    renderIndices1->clear();
    renderIndices2->clear();
    float distance;
    for (size_t i(0); i < rigidBodies4D.size(); i++)
    {
        RigidBody4D* a(rigidBodies4D[i]);
        distance = alg::length(a->position4D - cameraPos);
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
            Wall4D* a(walls4D[wallIndex]);
            if (a->isClamp && a->isFront)
            {
                if (a->objectName == "Ground")
                {
                    distance = 100000.f;
                }
                else
                {
                    distance = alg::length(a->position4D - cameraPos);
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
    for (size_t i(0); i < size_of_objects4d(sticks4D, springs4D); i++)
    {
        if (i < sticks4D.size())
        {
            if (sticks4D[i]->index2 != nullptr)
            {
                distance = alg::length(sticks4D[i]->position4D - cameraPos);
                if (sticks4D[i]->texture3DIndex == GLASS || sticks4D[i]->texture3DIndex == GRID || sticks4D[i]->paintingColor.w < 1.f)
                {
                    renderIndices2->push_back(new RenderIndex(2, i, distance));
                }
                else
                {
                    renderIndices1->push_back(new RenderIndex(2, i, distance));
                }
            }
        }
        else
        {
            size_t i2(i - sticks4D.size());
            if (springs4D[i2]->index2 != nullptr)
            {
                distance = alg::length(springs4D[i2]->position4D - cameraPos);
                if (springs4D[i2]->texture3DIndex == GLASS || springs4D[i2]->texture3DIndex == GRID || springs4D[i2]->paintingColor.w < 1.f)
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
}

static void update_render_indices_distance(vector<RigidBody4D*> rigidBodies4D, std::vector<Group*> groups, vector<Wall4D*> walls4D, std::vector<Stick4D*> sticks4D, std::vector<Spring4D*> springs4D, std::vector<RenderIndex*> renderIndices1, std::vector<RenderIndex*> renderIndices2, glm::vec4 cameraPos)
{
    for (size_t index(0); index < renderIndices1.size(); index++)
    {
        RenderIndex* i(renderIndices1[index]);
        if (i->type == 0)
        {
            i->distance = alg::length(rigidBodies4D[i->objectIndex]->position4D - cameraPos);
        }
        else if (i->type == 1)
        {
            i->distance = alg::length(walls4D[i->objectIndex]->position4D - cameraPos);
        }
        else if (i->type == 2)
        {
            if (i->objectIndex < sticks4D.size())
            {
                i->distance = alg::length(sticks4D[i->objectIndex]->position4D - cameraPos);
            }
            else
            {
                i->distance = alg::length(springs4D[i->objectIndex - sticks4D.size()]->position4D - cameraPos);
            }
        }
    }
    for (size_t index(0); index < renderIndices2.size(); index++)
    {
        RenderIndex* i(renderIndices2[index]);
        if (i->type == 0)
        {
            i->distance = alg::length(rigidBodies4D[i->objectIndex]->position4D - cameraPos);
        }
        else if (i->type == 1)
        {
            i->distance = alg::length(walls4D[i->objectIndex]->position4D - cameraPos);
        }
        else if (i->type == 2)
        {
            if (i->objectIndex < sticks4D.size())
            {
                i->distance = alg::length(sticks4D[i->objectIndex]->position4D - cameraPos);
            }
            else
            {
                i->distance = alg::length(springs4D[i->objectIndex - sticks4D.size()]->position4D - cameraPos);
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

static std::vector<size_t> judge_groups(vector<RigidBody4D*> rigidBodies4D, std::vector<size_t> groupIndices, std::vector<Group*> groups,glm::vec4 cameraPos,int blockLoadDistance)
{
    if (groupIndices.size() == 1)
    {
        for (size_t groupIndex(1); groupIndex < groups.size(); groupIndex++)
        {
            Group* i(groups[groupIndex]);
            glm::vec4 relativePos4D(i->position4D - cameraPos);
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
            glm::vec4 relativePos4D(i->position4D - cameraPos);
            if (alg::length(relativePos4D) < (float)blockLoadDistance)
            {
                for (size_t j(0); j < i->groupAroundIndices.size(); j++)
                {
                    if (groups[i->groupAroundIndices[j]]->isRender == false)
                    {
                        if (alg::length(groups[i->groupAroundIndices[j]]->position4D - cameraPos) < (float)blockLoadDistance)
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

    for (size_t i(1); i < rigidBodies4D.size(); i++)
    {
        glm::vec4 relativePos4D(get_block_position4D(rigidBodies4D[i]->position4D) - cameraPos);
        if (alg::length(relativePos4D) > (float)blockLoadDistance)
        {
            rigidBodies4D[i]->isBeyond = true;
        }
        else 
        {
            rigidBodies4D[i]->isBeyond = false;
        }
    }
    return groupIndices;
}

static void judge_objects(std::vector<size_t> groupIndices, std::vector<Group*> groups, vector<Wall4D*> walls4D, vector<Terrain4D*> terrains4D, glm::vec4 cameraPos, glm::vec4 cameraFor, glm::vec4 cameraWDir, int objectLoadDistance)
{
    for (size_t groupIndex : groupIndices)
    {
        Group* i(groups[groupIndex]);
        for (size_t wallIndex : i->walls4DIndices)
        {
            Object4D* o(walls4D[wallIndex]);
            float lengthOfScale(alg::length(o->scale4D));
            glm::vec4 relativePos4D(o->position4D - cameraPos);
            if (alg::dot(cameraFor, relativePos4D) < -lengthOfScale / 2.f)
            {
                o->isFront = false;
            }
            else 
            {
                float lengthOfScale(alg::length(o->scale4D));
                glm::vec4 relativePos4D(o->position4D - cameraPos);
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
            Terrain4D* t(terrains4D[terrainIndex]);
            glm::vec4 relativePos4D(t->position4D + glm::vec4(0.f,(t->topHeight + t->bottomHeight)/2.f,0.f,0.f) - cameraPos);
            if (alg::dot(cameraFor, relativePos4D) < -(float)(terrainScale * terrainSize))
            {
                t->isFront = false;
            }
            else 
            {
                float lengthOfScale(alg::length(t->scale4D));
                glm::vec4 relativePos4D(t->position4D - cameraPos);
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

static void update_point_light4d_id(std::vector<PointLight4D*>* pointLights4D)
{
    for (size_t k(0); k < pointLights4D->size(); k++)
    {
        (*pointLights4D)[k]->id = k;
    }
}

static void delete_object4d(std::vector<RigidBody4D*> a, std::vector<RigidBody4D*> b,
    std::vector<DynamiteIndex*>* dynamiteIndices, 
    std::vector<Stick4D*>* sticks4D, 
    std::vector<Spring4D*>* springs4D, 
    std::vector<std::vector<HingeConstraint4D*>>* hingeConstraintsVector, 
    std::vector<PointLight4D*> pointLights4D,
    std::vector<Shift4D*> shifts4D,
    std::vector<Float4D*> floats4D,
    std::vector<Rotate4D*> rotates4D,
    std::vector<OpenDoor4D*> openDoors4D,
    size_t index)
{
    int dynamitesEraseCount(erase_dynamite4d_indices(dynamiteIndices, index));
    shift_dynamite4d_indices(*dynamiteIndices, index, -dynamitesEraseCount);
    int sticksEraseCount(erase_stick4d_indices(sticks4D, index));
    shift_stick4d_indices(*sticks4D, index, -sticksEraseCount);
    int springsEraseCount(erase_stick4d_indices(sticks4D, index));
    shift_spring4d_indices(*springs4D, index, -springsEraseCount);
    int hingeConstraintsEraseCount(erase_hinge_constraints_vec_indices(hingeConstraintsVector, index));
    shift_spring4d_indices(*springs4D, index, -hingeConstraintsEraseCount);
}