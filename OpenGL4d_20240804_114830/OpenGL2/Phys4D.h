#pragma once
#include"PhyFunction.h"
namespace phy {
	static float timeToSleep=0.f;
	static void sleep_rigidBodies4D(std::vector<RigidBody4D*> rigidBodies4D, std::vector<RigidBody4D*> dynamites4D2, const float dt)
	{
		for (int i(0); i < size_of_objects4d(rigidBodies4D, dynamites4D2); i++)
		{
			RigidBody4D* a(find_rigidbody4d(rigidBodies4D, dynamites4D2, i));
			if (!a->isSleep)
			{
				if (length(a->velocity4D) > 0.1f || length(a->angularVelocity4D) > 0.8f || length(a->position4D - a->pPosition4D) > 0.05f)
				{
					a->isContinueSleep = false;
				}
			}
		}
		timeToSleep += dt;
		if (timeToSleep > 2.f)
		{
			for (int i(0); i < size_of_objects4d(rigidBodies4D, dynamites4D2); i++)
			{
				RigidBody4D* a = find_rigidbody4d(rigidBodies4D, dynamites4D2, i);
				if (!a->isSleep)
				{
					a->pPosition4D = a->position4D;
					if (a->isContinueSleep&&!a->is_static())
					{
						a->isSleep = true;
						a->velocity4D = glm::vec4(0.f);
						a->angularVelocity4D = alg::bivec4();
					}
					a->isContinueSleep = true;
				}
			}
			timeToSleep = 0.f;
		}
	}
	static void wake_up_rigidBody4D(RigidBody4D* a)
	{
		if (a->isSleep)
		{
			if (length(a->velocity4D) > 0.1f || length(a->angularVelocity4D) > 0.8f || length(a->position4D - a->pPosition4D) > 0.05f)
			{
				a->isSleep = false;
				a->isContinueSleep = true;
			}
		}
	}

	static void wake_up_rigidBodies4D(std::vector<RigidBody4D*> rigidBodies4D, std::vector<RigidBody4D*> dynamites4D2)
	{
		for (int i(0); i < size_of_objects4d(rigidBodies4D, dynamites4D2); i++)
		{
			RigidBody4D* a(find_rigidbody4d(rigidBodies4D, dynamites4D2, i));
			if (a->isSleep)
			{
				if (length(a->velocity4D) > 0.1f || length(a->angularVelocity4D) > 0.8f || a->forceSystems4D.size() > 0 || length(a->position4D - a->pPosition4D) > 0.05f)
				{
					a->isSleep = false;
					a->isContinueSleep = true;
				}
				a->velocity4D = glm::vec4(0.f);
				a->angularVelocity4D = alg::bivec4();
			}
		}
	}

	static void start_rigidBodies4D(std::vector<RigidBody4D*> rigidBodies4D, std::vector<RigidBody4D*> dynamites4D2, const float dt)
	{
		for (int i(0); i < size_of_objects4d(rigidBodies4D, dynamites4D2); i++)
		{
			RigidBody4D* a(find_rigidbody4d(rigidBodies4D, dynamites4D2, i));
			if (!a->is_static()&&!a->isSleep)
			{
				if (a->isGravity)
				{
					a->forceSystems4D.push_back(new ForceSystem4D(glm::vec4(0, -9.80665f * a->mass, 0, 0), glm::vec4(0.f)));
				}
				update_rigidbody_velocity4D(a, dt);
			}
		}
		glm::vec4 dir_a_to_b;
		float dis;
		glm::vec4 dir_a_to_b_e;
		glm::vec4 force4D;
		for (size_t i(1); i < size_of_objects4d(rigidBodies4D, dynamites4D2); i++)
		{
			RigidBody4D* a(find_rigidbody4d(rigidBodies4D, dynamites4D2, i));
			if (a->objectName == "Celestial4D")
			{
				for (size_t j(i + 1); j < size_of_objects4d(rigidBodies4D, dynamites4D2); j++)
				{
					RigidBody4D* b(find_rigidbody4d(rigidBodies4D, dynamites4D2, j));
					if (b->objectName == "Celestial4D")
					{
						a->isSleep = false;
						b->isSleep = false;
						dir_a_to_b = b->position4D - a->position4D;
						dis = length(dir_a_to_b);
						dir_a_to_b_e = normalize(dir_a_to_b);
						if (dis >= 0.5f)
						{
							force4D = 10.f * a->mass * b->mass * dir_a_to_b_e / pow(dis, 2.f);
						}
						else
						{
							force4D = 40.f * a->mass * b->mass * dir_a_to_b_e;
						}
						resolve_impulse0(a, force4D * dt);
						resolve_impulse0(b, -force4D * dt);
					}
				}
			}
		}
	}

	static void caculate_rigidBodies4D(std::vector<RigidBody4D*> rigidBodies4D, std::vector<RigidBody4D*> dynamites4D2, std::vector<Group*> groups, vector<Wall4D*> walls4D,vector<Wall4D*> dynamites4D, std::vector<Water4D*> waters4D, std::vector<std::vector<Collision>>* collisionsVec, std::vector <std::vector<Constraint*>>* constraintsVec0, const float dt)
	{

		for (size_t i(0); i < size_of_objects4d(rigidBodies4D, dynamites4D2); i++)
		{
			RigidBody4D* a(find_rigidbody4d(rigidBodies4D, dynamites4D2, i));
			if (!a->isBeyond)
			{
				for (size_t k(0); k < a->rigidBodyIndices.size(); k++)
				{
					GLint j(a->rigidBodyIndices[k]);
					RigidBody4D* b(find_rigidbody4d(rigidBodies4D, dynamites4D2, j));
					if (!b->isBeyond)
					{
						if (!a->isFrozen)
						{
							if (!b->isFrozen)
							{
								if (!(a->isSleep && b->isSleep))
								{
									*collisionsVec = detect_rigidbody_or_wall(a, b, i, j, *collisionsVec);
								}
							}
							if (b->isFrozen)
							{
								if (a->velocity4D != glm::vec4(0.f) || !a->isSleep)
									*collisionsVec = detect_rigidbody_or_wall(a, b, i, -1, *collisionsVec);
							}
						}

						if (a->isFrozen)
						{
							if (!b->isFrozen)
							{
								if (b->velocity4D != glm::vec4(0.f) || !b->isSleep)
									*collisionsVec = detect_rigidbody_or_wall(b, a, j, -1, *collisionsVec);
							}
						}
					}
				}
				if (!a->isFrozen)
				{
					if (a->velocity4D != glm::vec4(0.f) || !a->isSleep)
					{
						for (size_t l(0); l < a->groupWallIndices.size(); l++)
						{
							size_t j(a->groupWallIndices[l].groupIndex);
							size_t k(a->groupWallIndices[l].objectIndex);
							int wallIndex0(find_wall_index(groups,j, k));
							*collisionsVec = detect_rigidbody_or_wall(a, groups[j]->walls4D[k], i, size_of_objects4d(rigidBodies4D, dynamites4D2) + wallIndex0, *collisionsVec);
						}
						for (size_t j(0); j < groups.size(); j++) {
							for (Terrain4D* k : groups[j]->terrains4D) {
								*collisionsVec = detect_rigidbody_terrain(a, k, i, *collisionsVec);
							}
						}
						for (size_t k(0); k < a->wallIndices.size(); k++)
						{
							size_t j(a->wallIndices[k]);
							*collisionsVec = detect_rigidbody_or_wall(a, find_wall4d(walls4D, dynamites4D,j), i, size_of_objects4d(rigidBodies4D, dynamites4D2, groups) + j, *collisionsVec);
						}
					}
				}
				if (!a->isFrozen && (a->velocity4D != glm::vec4(0.f) || !a->isSleep))
				{
					*collisionsVec = detect_rigidbody_edge(a, i, *collisionsVec);
				}
			}
		}
		size_t objectSize(size_of_objects4d(rigidBodies4D, dynamites4D2));
		for (int i(0); i < objectSize; i++)
		{
			size_t countA(0.f);
			size_t countB(0.f);
			for (std::vector<Collision> collisions : *collisionsVec)
			{
				if (collisions[0].index1 == i)
				{
					countA += collisions.size();
				}
				else if (collisions[0].index2 == i)
				{
					countB += collisions.size();
				}
			}
			for (std::vector<Collision>& collisions : *collisionsVec)
			{
				if (collisions[0].index1 == i)
				{
					for (Collision& collision: collisions)
					collision.massAdjustmentA = (float)countA;
				}
				else if (collisions[0].index2 == i)
				{
					for (Collision& collision : collisions)
					collision.massAdjustmentB = (float)countB;
				}
			}
		}
		std::vector <std::vector<Constraint*>> constraintsVec;
		for (std::vector<Collision> collisions : *collisionsVec)
		{
			RigidBody4D* a(find_rigidbody4d(rigidBodies4D, dynamites4D2, collisions[0].index1));
			if (collisions[0].index2 == -1)
			{
				get_constraint(collisions[0].index1, a, collisions, &constraintsVec);
			}
			else if (collisions[0].index2 != -1)
			{
				if (collisions[0].index2 < size_of_objects4d(rigidBodies4D, dynamites4D2))
				{
					RigidBody4D* b(find_rigidbody4d(rigidBodies4D, dynamites4D2, collisions[0].index2));
					get_constraint(collisions[0].index1, collisions[0].index2, a, b, collisions, &constraintsVec);
				}
				else if (collisions[0].index2 >= size_of_objects4d(rigidBodies4D, dynamites4D2))
				{
					Wall4D* w = find_wall4d(groups, walls4D, dynamites4D, collisions[0].index2 - size_of_objects4d(rigidBodies4D, dynamites4D2));
					get_constraint(collisions[0].index1, collisions[0].index2, a, w, collisions, &constraintsVec);
				}
			}
		}
		for (std::vector<Constraint*>& constraints : constraintsVec)
		{
			for (Constraint* constraint : constraints)
			{
				for (std::vector<Constraint*> constraints0 : *constraintsVec0)
				{
					for (Constraint* constraint0 : constraints0)
					{
						if (length(constraint->collisionConstraint.contacts.contactPosA - constraint0->collisionConstraint.contacts.contactPosA) < 0.1f)
						{
							if (constraint->index2 == -1)
							{
								for (unsigned i(0); i < 4; i++) {
									resolve_impulse0(find_rigidbody4d(rigidBodies4D, dynamites4D2, constraint->index1), constraint0->impulses[i], constraint0->collisionConstraint.contacts.contactPosB);
								}
							}
							else if (constraint->index2 != -1)
							{
								if (constraint->index2 < size_of_objects4d(rigidBodies4D, dynamites4D2))
								{
									for (unsigned i(0); i < 4; i++) {
										resolve_impulse0(find_rigidbody4d(rigidBodies4D, dynamites4D2, constraint->index1), -constraint0->impulses[i], constraint0->collisionConstraint.contacts.contactPosA);
										resolve_impulse0(find_rigidbody4d(rigidBodies4D, dynamites4D2, constraint->index2), constraint0->impulses[i], constraint0->collisionConstraint.contacts.contactPosB);
									}
								}
								else if (constraint->index2 >= size_of_objects4d(rigidBodies4D, dynamites4D2))
								{
									for (unsigned i(0); i < 4; i++) {
										resolve_impulse0(find_rigidbody4d(rigidBodies4D, dynamites4D2, constraint->index1), constraint0->impulses[i], constraint0->collisionConstraint.contacts.contactPosB);
									}
								}
							}
						}
					}
				}
			}
		}
		for (unsigned i(0); i < 20; i++)
		{
			bool isInverseSolve(i % 2 == 0);
			for (unsigned int j(0);j< constraintsVec.size();j++)
			{
				std::vector<Constraint*> constraints;
				if (isInverseSolve)constraints = constraintsVec[constraintsVec.size() - j - 1];
				else constraints = constraintsVec[j];
				RigidBody4D* a(find_rigidbody4d(rigidBodies4D, dynamites4D2, constraints[0]->index1));
				if (constraints[0]->index2 == -1)
				{
					solve_rigidbody_edge(a, &constraints, isInverseSolve);
				}
				else if (constraints[0]->index2 != -1)
				{
					if (constraints[0]->index2 < size_of_objects4d(rigidBodies4D, dynamites4D2))
					{
						RigidBody4D* b(find_rigidbody4d(rigidBodies4D, dynamites4D2, constraints[0]->index2));
						if (!b->is_static())
						{
							solve_rigidbody_rigidbody(a, b, &constraints, isInverseSolve);
							wake_up_rigidBody4D(a);
							wake_up_rigidBody4D(b);
						}
						else
						{
							solve_rigidbody_wall(a, b, &constraints, isInverseSolve);
							wake_up_rigidBody4D(a);
							wake_up_rigidBody4D(b);
						}
					}
					if (constraints[0]->index2 >= size_of_objects4d(rigidBodies4D, dynamites4D2))
					{
						solve_rigidbody_wall(a, find_wall4d(groups, walls4D, dynamites4D, constraints[0]->index2 - size_of_objects4d(rigidBodies4D, dynamites4D2)), &constraints, isInverseSolve);
					}
				}
			}
		}
		//for (std::vector<Constraint*> cs : *constraintsVec0)for (Constraint* c : cs)c = nullptr, free(c);
		*constraintsVec0 = constraintsVec;
		for (std::vector<Constraint*> cs: constraintsVec)for (Constraint* c : cs)c = nullptr, free(c);
	}

	static void caculate_joints4D(std::vector<RigidBody4D*> rigidBodies4D,
		std::vector<RigidBody4D*> dynamites4D2,
		std::vector<Group*> groups,
		vector<Wall4D*> walls4D,
		vector<Wall4D*> dynamites4D,
		std::vector < Stick4D*> sticks4D,
		std::vector < Spring4D*> springs4D,
		std::vector <std::vector<Constraint*>>* constraintsVec2,
		std::vector < std::vector < HingeConstraint4D>> hingeConstraintsVec,
		const float dt)
	{
		for (Stick4D* i : sticks4D)
		{
			if (i->index2 != -1)
			{
				if (i->index2 < size_of_objects4d(rigidBodies4D, dynamites4D2))
				{
					RigidBody4D* b(find_rigidbody4d(rigidBodies4D, dynamites4D2, i->index2));
					if (i->index1 < size_of_objects4d(rigidBodies4D, dynamites4D2))
					{
						RigidBody4D* a(find_rigidbody4d(rigidBodies4D, dynamites4D2, i->index1));
						if (!a->is_static() && !b->is_static())
						{
							i->solve_rigidbody_rigidbody(a, b, dt);
						}
						else if (a->is_static() && b->is_static())
						{
							i->solve_rigidbody_rigidbody(a, b, dt);
						}
						else if (!a->is_static() && b->is_static())
						{
							i->solve_rigidbody_wall(a, b, dt);
						}
						else if (a->is_static() && !b->is_static())
						{
							i->solve_rigidbody_wall(b, a, dt);
						}
					}
					else if (i->index1 >= size_of_objects4d(rigidBodies4D, dynamites4D2))
					{
						Wall4D* c(find_wall4d(groups, walls4D, dynamites4D, i->index1 - size_of_objects4d(rigidBodies4D, dynamites4D2)));
						i->solve_rigidbody_wall(b, c, dt);
					}
				}
				if (i->index2 >= size_of_objects4d(rigidBodies4D, dynamites4D2))
				{
					if (i->index1 < size_of_objects4d(rigidBodies4D, dynamites4D2))
					{
						RigidBody4D* a(find_rigidbody4d(rigidBodies4D, dynamites4D2, i->index1));
						Wall4D* d(find_wall4d(groups, walls4D, dynamites4D, i->index2 - size_of_objects4d(rigidBodies4D, dynamites4D2)));
						i->solve_rigidbody_wall(a, d, dt);
					}
				}
			}
		}
		for (Spring4D* i : springs4D)
		{
			if (i->index2 != -1)
			{
				if (i->index2 < size_of_objects4d(rigidBodies4D, dynamites4D2))
				{
					RigidBody4D* b(find_rigidbody4d(rigidBodies4D, dynamites4D2, i->index2));
					if (i->index1 < size_of_objects4d(rigidBodies4D, dynamites4D2))
					{
						RigidBody4D* a(find_rigidbody4d(rigidBodies4D, dynamites4D2, i->index1));
						if (!a->is_static() && !b->is_static())
						{
							i->solve_rigidbody_rigidbody(a, b, dt);
						}
						else if (a->is_static() && b->is_static())
						{
							i->solve_rigidbody_rigidbody(a, b, dt);
						}
						else if (!a->is_static() && b->is_static())
						{
							i->solve_rigidbody_wall(a, b, dt);
						}
						else if (a->is_static() && !b->is_static())
						{
							i->solve_rigidbody_wall(b, a, dt);
						}
					}
					else if (i->index1 >= size_of_objects4d(rigidBodies4D, dynamites4D2))
					{
						Wall4D* c(find_wall4d(groups, walls4D, dynamites4D, i->index1 - size_of_objects4d(rigidBodies4D, dynamites4D2)));
						i->solve_rigidbody_wall(b, c, dt);
					}
				}
				if (i->index2 >= size_of_objects4d(rigidBodies4D, dynamites4D2))
				{
					if (i->index1 < size_of_objects4d(rigidBodies4D, dynamites4D2))
					{
						RigidBody4D* a(find_rigidbody4d(rigidBodies4D, dynamites4D2, i->index1));
						Wall4D* d(find_wall4d(groups, walls4D, dynamites4D, i->index2 - size_of_objects4d(rigidBodies4D, dynamites4D2)));
						i->solve_rigidbody_wall(a, d, dt);
					}
				}
			}
		}
		std::vector <std::vector<Constraint*>> constraintsVec;
		for (std::vector < HingeConstraint4D> hs : hingeConstraintsVec)
		{
			if (hs[0].index2 == -1)
			{
				if (hs[0].index1 < size_of_objects4d(rigidBodies4D, dynamites4D2))
				{
					RigidBody4D* a(find_rigidbody4d(rigidBodies4D, dynamites4D2, hs[0].index1));
					if(!a->isSleep)get_constraint(hs[0].index1, a, hs,&constraintsVec);
				}
			}
			else if (hs[0].index2 != -1)
			{
				if (hs[0].index2 < size_of_objects4d(rigidBodies4D, dynamites4D2))
				{
					if (hs[0].index1 < size_of_objects4d(rigidBodies4D, dynamites4D2))
					{
						RigidBody4D* a(find_rigidbody4d(rigidBodies4D, dynamites4D2, hs[0].index1));
						RigidBody4D* b(find_rigidbody4d(rigidBodies4D, dynamites4D2, hs[0].index2));
						if (!a->is_static() && !b->is_static())
						{
							if (!(a->isSleep&&b->isSleep))get_constraint(hs[0].index1, hs[0].index2, a, b, hs, &constraintsVec,20);
						}
						//else if (a->is_static() && b->is_static())
						//{
						//	get_constraint(hs[0].index1, hs[0].index2, a, b, hs, &constraintsVec,20);
						//}
						else if (!a->is_static() && b->is_static())
						{
							if (!b->isSleep)get_constraint(hs[0].index1, hs[0].index2, a, b, hs, &constraintsVec,false);
						}
						else if (a->is_static() && !b->is_static())
						{
							if (!a->isSleep)get_constraint(hs[0].index2, hs[0].index1, b, a, hs, &constraintsVec, true);
						}
					}
				}
			}
		}
		for (std::vector<Constraint*>& constraints : constraintsVec)
		{
			for (Constraint* constraint : constraints)
			{
				for (std::vector<Constraint*> constraints2 : *constraintsVec2)
				{
					for (Constraint* constraint2 : constraints2)
					{
						if (length(constraint->collisionConstraint.contacts.contactPosA - constraint2->collisionConstraint.contacts.contactPosA) < 0.1f)
						{
							if (constraint2->index2 == -1)
							{
								for (unsigned i(0); i < 4; i++) {
									resolve_impulse0(find_rigidbody4d(rigidBodies4D, dynamites4D2, constraint2->index1), constraint2->impulses[i], constraint2->collisionConstraint.contacts.contactPosB);
								}
							}
							else if (constraint2->index2 != -1)
							{
								if (constraint2->index2 < size_of_objects4d(rigidBodies4D, dynamites4D2))
								{
									for (unsigned i(0); i < 4; i++) {
										resolve_impulse0(find_rigidbody4d(rigidBodies4D, dynamites4D2, constraint2->index1), -constraint2->impulses[i], constraint2->collisionConstraint.contacts.contactPosA);
										resolve_impulse0(find_rigidbody4d(rigidBodies4D, dynamites4D2, constraint2->index2), constraint2->impulses[i], constraint2->collisionConstraint.contacts.contactPosB);
									}
								}
								else if (constraint2->index2 >= size_of_objects4d(rigidBodies4D, dynamites4D2))
								{
									for (unsigned i(0); i < 4; i++) {
										resolve_impulse0(find_rigidbody4d(rigidBodies4D, dynamites4D2, constraint2->index1), constraint2->impulses[i], constraint2->collisionConstraint.contacts.contactPosB);
									}
								}
							}
						}
					}
				}
			}
		}
		for (unsigned i(0); i < 20; i++)
		{
			bool isInverseSolve(i % 2 == 0);
			for (unsigned int j(0); j < constraintsVec.size(); j++)
			{
				std::vector<Constraint*> constraints;
				if (isInverseSolve)constraints = constraintsVec[constraintsVec.size() - j - 1];
				else constraints = constraintsVec[j];
				if (constraints[0]->index2 == -1)
				{
					if (constraints[0]->index1 < size_of_objects4d(rigidBodies4D, dynamites4D2))
					{
						RigidBody4D* a(find_rigidbody4d(rigidBodies4D, dynamites4D2, constraints[0]->index1));
						solve_rigidbody2(a, &constraints, isInverseSolve);
					}
				}
				else if (constraints[0]->index2 != -1)
				{
					if (constraints[0]->index2 < size_of_objects4d(rigidBodies4D, dynamites4D2))
					{
						if (constraints[0]->index1 < size_of_objects4d(rigidBodies4D, dynamites4D2))
						{
							RigidBody4D* a(find_rigidbody4d(rigidBodies4D, dynamites4D2, constraints[0]->index1));
							RigidBody4D* b(find_rigidbody4d(rigidBodies4D, dynamites4D2, constraints[0]->index2));
							if (!a->is_static() && !b->is_static())
							{
								solve_rigidbody_rigidbody2(a, b, &constraints, isInverseSolve);
							}
							else if (a->is_static() && b->is_static())
							{
								solve_rigidbody_rigidbody2(a, b, &constraints, isInverseSolve);
							}
							else if (!a->is_static() && b->is_static())
							{
								solve_rigidbody_wall2(a, b, &constraints, isInverseSolve);
							}
							else if (a->is_static() && !b->is_static())
							{
								solve_rigidbody_wall2(b, a, &constraints, isInverseSolve);
							}
						}
					}
				}
			}
		}
		for (std::vector<Constraint*> cs : constraintsVec)for (Constraint* c : cs)c = nullptr, free(c);
	}

	static void solve_rigidBodies_position4D(std::vector<RigidBody4D*> rigidBodies4D, std::vector<RigidBody4D*> dynamites4D2, std::vector<Group*> groups, vector<Wall4D*> walls4D, vector<Wall4D*> dynamites4D, std::vector<std::vector<Collision>>* collisions, const float dt)
	{
		for (int i(0); i < size_of_objects4d(rigidBodies4D, dynamites4D2); i++)
		{
			RigidBody4D* a(find_rigidbody4d(rigidBodies4D, dynamites4D2, i));
			if (!a->is_static()&&!a->isSleep)
			{
				a->set_position4D(a->position4D + a->velocity4D * dt);
				a->set_rotation4D(update(a->rotation4D, a->angularVelocity4D * dt));	
			}
		}
	}

	static void update_stick4D(std::vector<RigidBody4D*> rigidBodies4D,
		std::vector<RigidBody4D*> dynamites4D2,
		std::vector<Group*> groups,
		vector<Wall4D*> walls4D,
		vector<Wall4D*> dynamites4D,
		Stick4D* stick4D)
	{

		if (stick4D->index2 == -1)
		{
			if (stick4D->index1 < size_of_objects4d(rigidBodies4D, dynamites4D2))
			{
				stick4D->update_stick4D(find_rigidbody4d(rigidBodies4D, dynamites4D2, stick4D->index1));
			}
			else if (stick4D->index1 >= size_of_objects4d(rigidBodies4D, dynamites4D2))
			{
				stick4D->update_stick4D(find_wall4d(groups, walls4D,dynamites4D, stick4D->index1 - size_of_objects4d(rigidBodies4D, dynamites4D2)));
			}
		}
		else if (stick4D->index2 != -1)
		{
			if (stick4D->index2 < size_of_objects4d(rigidBodies4D, dynamites4D2))
			{
				if (stick4D->index1 < size_of_objects4d(rigidBodies4D, dynamites4D2))
				{
					stick4D->update_stick4D(find_rigidbody4d(rigidBodies4D, dynamites4D2, stick4D->index1), find_rigidbody4d(rigidBodies4D, dynamites4D2, stick4D->index2));
				}
				else if (stick4D->index1 >= size_of_objects4d(rigidBodies4D, dynamites4D2))
				{
					stick4D->update_stick4D(find_rigidbody4d(rigidBodies4D, dynamites4D2, stick4D->index2), find_wall4d(groups, walls4D,dynamites4D, stick4D->index1 - size_of_objects4d(rigidBodies4D, dynamites4D2)));
				}
			}
			else if (stick4D->index2 >= size_of_objects4d(rigidBodies4D, dynamites4D2))
			{
				if (stick4D->index1 < size_of_objects4d(rigidBodies4D, dynamites4D2))
				{
					stick4D->update_stick4D(find_wall4d(groups, walls4D,dynamites4D, stick4D->index2 - size_of_objects4d(rigidBodies4D, dynamites4D2)), find_rigidbody4d(rigidBodies4D, dynamites4D2, stick4D->index1));
				}
				else if (stick4D->index1 >= size_of_objects4d(rigidBodies4D, dynamites4D2))
				{
					stick4D->update_stick4D(find_wall4d(groups, walls4D,dynamites4D, stick4D->index1 - size_of_objects4d(rigidBodies4D, dynamites4D2)), find_wall4d(groups, walls4D,dynamites4D, stick4D->index2 - size_of_objects4d(rigidBodies4D, dynamites4D2)));
				}
			}
		}
	}
	static void update_spring4D(std::vector<RigidBody4D*> rigidBodies4D,
		std::vector<RigidBody4D*> dynamites4D2,
		std::vector<Group*> groups,
		vector<Wall4D*> walls4D,
		vector<Wall4D*> dynamites4D,
		Spring4D* spring4D)
	{

		if (spring4D->index2 == -1)
		{
			if (spring4D->index1 < size_of_objects4d(rigidBodies4D, dynamites4D2))
			{
				spring4D->update_spring4D(find_rigidbody4d(rigidBodies4D, dynamites4D2, spring4D->index1));
			}
			else if (spring4D->index1 >= size_of_objects4d(rigidBodies4D, dynamites4D2))
			{
				spring4D->update_spring4D(find_wall4d(groups, walls4D,dynamites4D, spring4D->index1 - size_of_objects4d(rigidBodies4D, dynamites4D2)));
			}
		}
		else if (spring4D->index2 != -1)
		{
			if (spring4D->index2 < size_of_objects4d(rigidBodies4D, dynamites4D2))
			{
				if (spring4D->index1 < size_of_objects4d(rigidBodies4D, dynamites4D2))
				{
					spring4D->update_spring4D(find_rigidbody4d(rigidBodies4D, dynamites4D2, spring4D->index1), find_rigidbody4d(rigidBodies4D, dynamites4D2, spring4D->index2));
				}
				else if (spring4D->index1 >= size_of_objects4d(rigidBodies4D, dynamites4D2))
				{
					spring4D->update_spring4D(find_rigidbody4d(rigidBodies4D, dynamites4D2, spring4D->index2), find_wall4d(groups, walls4D, dynamites4D, spring4D->index1 - size_of_objects4d(rigidBodies4D, dynamites4D2)));
				}
			}
			else if (spring4D->index2 >= size_of_objects4d(rigidBodies4D, dynamites4D2))
			{
				if (spring4D->index1 < size_of_objects4d(rigidBodies4D, dynamites4D2))
				{
					spring4D->update_spring4D(find_wall4d(groups, walls4D, dynamites4D, spring4D->index2 - size_of_objects4d(rigidBodies4D, dynamites4D2)), find_rigidbody4d(rigidBodies4D, dynamites4D2, spring4D->index1));
				}
				else if (spring4D->index1 >= size_of_objects4d(rigidBodies4D, dynamites4D2))
				{
					spring4D->update_spring4D(find_wall4d(groups, walls4D, dynamites4D, spring4D->index1 - size_of_objects4d(rigidBodies4D, dynamites4D2)), find_wall4d(groups, walls4D, dynamites4D, spring4D->index2 - size_of_objects4d(rigidBodies4D, dynamites4D2)));
				}
			}
		}
	}

	static void update_trails4D(std::vector<RigidBody4D*> rigidBodies4D, std::vector<RigidBody4D*> dynamites4D2, const float dt, float curTime)
	{
		for (int i(0); i < size_of_objects4d(rigidBodies4D, dynamites4D2); i++)
		{
			find_rigidbody4d(rigidBodies4D, dynamites4D2, i)->update_trail4D(dt, curTime);
		}
	}

	static void clear_forces4D(std::vector<RigidBody4D*> rigidBodies4D, std::vector<RigidBody4D*> dynamites4D2)
	{
		for (RigidBody4D* i : rigidBodies4D)
		{
			i->forceSystems4D.clear();
		}
		for (RigidBody4D* i : dynamites4D2)
		{
			i->forceSystems4D.clear();
		}
	}

	static void update_physic4D(std::vector<RigidBody4D*> rigidBodies4D,
		std::vector<RigidBody4D*> dynamites4D2,
		std::vector<Group*> groups,
		vector<Wall4D*> walls4D,
		vector<Wall4D*> dynamites4D,
		std::vector<Water4D*> waters4D,
		std::vector<std::vector<Collision>>* collisions,
		std::vector <std::vector<Constraint*>>* constraintsVec,
		std::vector <std::vector<Constraint*>>* constraintsVec2,
		std::vector < Stick4D*> sticks4D,
		std::vector < Spring4D*> springs4D,
		std::vector < std::vector < HingeConstraint4D>> hingeConstraintsVec,
		const float dt)
	{
		sleep_rigidBodies4D(rigidBodies4D, dynamites4D2, dt);
		wake_up_rigidBodies4D(rigidBodies4D, dynamites4D2);
		start_rigidBodies4D(rigidBodies4D, dynamites4D2, dt);
		caculate_rigidBodies4D(rigidBodies4D, dynamites4D2, groups, walls4D, dynamites4D, waters4D, collisions, constraintsVec, dt);
		caculate_joints4D(rigidBodies4D, dynamites4D2, groups, walls4D, dynamites4D, sticks4D, springs4D, constraintsVec2,hingeConstraintsVec, dt);
		solve_rigidBodies_position4D(rigidBodies4D, dynamites4D2, groups, walls4D, dynamites4D, collisions, dt);
		clear_forces4D(rigidBodies4D, dynamites4D2);
	}

	static void before_render_physic4D(std::vector<RigidBody4D*> rigidBodies4D,
		std::vector<RigidBody4D*> dynamites4D2,
		std::vector<Group*> groups,
		vector<Wall4D*> walls4D,
		vector<Wall4D*> dynamites4D,
		std::vector < Stick4D*> sticks4D,
		std::vector < Spring4D*> springs4D,
		bool isTrail4D,
		const float dt, float curTime)
	{
		for (Stick4D* i : sticks4D) { if (i->index2 != -1)update_stick4D(rigidBodies4D, dynamites4D2, groups, walls4D,dynamites4D, i); }
		for (Spring4D* i : springs4D) { if (i->index2 != -1)update_spring4D(rigidBodies4D, dynamites4D2, groups, walls4D,dynamites4D, i); }
		if (isTrail4D) { update_trails4D(rigidBodies4D, dynamites4D2, dt, curTime); }
	}
}