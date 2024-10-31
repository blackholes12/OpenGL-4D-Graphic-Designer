#pragma once
#include"PhyFunction.h"
namespace phy {
	static float timeToSleep=0.f;
	static void sleep_rigidBodies4D(std::vector<RigidBody4D*> rigidBodies4D, const float dt)
	{
		for (size_t i(0); i < rigidBodies4D.size(); i++)
		{
			RigidBody4D* a(rigidBodies4D[i]);
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
			for (size_t i(0); i < rigidBodies4D.size(); i++)
			{
				RigidBody4D* a(rigidBodies4D[i]);
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

	static void wake_up_rigidBodies4D(std::vector<RigidBody4D*> rigidBodies4D)
	{
		for (size_t i(0); i < rigidBodies4D.size(); i++)
		{
			RigidBody4D* a(rigidBodies4D[i]);
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

	static void start_rigidBodies4D(std::vector<RigidBody4D*> rigidBodies4D, std::vector<std::vector<Collision>>* collisionsVec, const float dt)
	{
		collisionsVec->clear(),collisionsVec = nullptr, free(collisionsVec);
		for (size_t i(0); i < rigidBodies4D.size(); i++)
		{
			RigidBody4D* a(rigidBodies4D[i]);
			if (!a->is_static() && !a->isSleep)
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
		for (size_t i(1); i < rigidBodies4D.size(); i++)
		{
			RigidBody4D* a(rigidBodies4D[i]);
			if (a->objectName == "Celestial4D")
			{
				for (size_t j(i + 1); j < rigidBodies4D.size(); j++)
				{
					RigidBody4D* b(rigidBodies4D[j]);
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
						resolve_impulse(a, force4D * dt);
						resolve_impulse(b, -force4D * dt);
					}
				}
			}
		}
	}

	static void caculate_rigidBodies4D(std::vector<RigidBody4D*> rigidBodies4D, std::vector<size_t> groupIndices, std::vector<Group*> groups, vector<Wall4D*> walls4D, std::vector<Terrain4D*> terrains4D, std::vector<Water4D*> waters4D, std::vector < std::vector < HingeConstraint4D*>> hingeConstraintsVec, std::vector<std::vector<Collision>>* collisionsVec, std::vector <std::vector<Constraint*>>* constraintsVec0, const float dt)
	{
		for (size_t i(0); i < rigidBodies4D.size(); i++)
		{
			RigidBody4D* a(rigidBodies4D[i]);
			if (!a->isBeyond)
			{
				size_t collisionSizeBefore(collisionsVec->size());
				for (size_t k(0); k < a->rigidBodyIndices.size(); k++)
				{
					size_t j(a->rigidBodyIndices[k]);
					RigidBody4D* b(rigidBodies4D[j]);
					if (!b->isBeyond)
					{
						if (!a->isFrozen)
						{
							if (!b->isFrozen)
							{
								if (!(a->isSleep && b->isSleep))
								{
									*collisionsVec = detect_rigidbody_or_wall(i, j, a, b, *collisionsVec);
								}
							}
							else
							{
								if (a->velocity4D != glm::vec4(0.f) || !a->isSleep)
									*collisionsVec = detect_rigidbody_or_wall(i, -1, a, b, *collisionsVec);
							}
						}
						else
						{
							if (!b->isFrozen)
							{
								if (b->velocity4D != glm::vec4(0.f) || !b->isSleep)
									*collisionsVec = detect_rigidbody_or_wall(j, -1, b, a, *collisionsVec);
							}
						}
					}
				}
				if (!a->isFrozen)
				{
					if (a->velocity4D != glm::vec4(0.f) || !a->isSleep)
					{
						for (size_t groupIndex : groupIndices)
						{
							Group* j(groups[groupIndex]);
							for (size_t terrainIndex : j->terrains4DIndices) {
								Terrain4D* k(terrains4D[terrainIndex]);
								*collisionsVec = detect_rigidbody_terrain(i, a, k, *collisionsVec);
							}
						}
						for (size_t k(0); k < a->wallIndices.size(); k++)
						{
							size_t j(a->wallIndices[k]);
							if (a->colType != NONE)
							{
								if (a->objectName == "Billiard")
								{
									Wall4D* w = walls4D[j];
									if (w->colType != NONE)
									{
										if (w->objectName == "Billiard")
										{
											update_billiards(a, w);
										}
									}
								}
							}
							*collisionsVec = detect_rigidbody_or_wall(i, rigidBodies4D.size() + j, a, walls4D[j], *collisionsVec);
						}
					}
				}
				if (!a->isFrozen && (a->velocity4D != glm::vec4(0.f) || !a->isSleep))
				{
					*collisionsVec = detect_rigidbody_edge(i, a, *collisionsVec);
				}
				size_t collisionSizeAfter(collisionsVec->size());
				size_t countA(0);
				for (size_t j(collisionSizeBefore); j < collisionSizeAfter;j++)
				{
					std::vector<Collision> collisions((*collisionsVec)[j]);
					countA += collisions.size();
				}
				for (size_t j(collisionSizeBefore); j < collisionSizeAfter; j++)
				{
					std::vector<Collision>& collisions((*collisionsVec)[j]);
					for (Collision& collision : collisions)collision.massAdjustmentA = (float)countA;
					for (Collision& collision : collisions)collision.massAdjustmentB = (float)collisions.size();
				}
			}
		}
		for (std::vector < HingeConstraint4D*> hs : hingeConstraintsVec)
		{
			if (!hs[0]->index2->isValid)
			{
				if (hs[0]->index1 < rigidBodies4D.size())
				{
					RigidBody4D* a(rigidBodies4D[hs[0]->index1]);
					if (!a->isSleep)*collisionsVec = hinge_to_hinge(hs, a, nullptr, *collisionsVec,false);
				}
			}
			else
			{
				if (hs[0]->index2->n < rigidBodies4D.size())
				{
					if (hs[0]->index1 < rigidBodies4D.size())
					{
						RigidBody4D* a(rigidBodies4D[hs[0]->index1]);
						RigidBody4D* b(rigidBodies4D[hs[0]->index2->n]);
						if (!a->is_static() && !b->is_static())	 
						{
							if (!(a->isSleep && b->isSleep))*collisionsVec = hinge_to_hinge(hs, a, b, *collisionsVec,false);
						}
						else if (!a->is_static() && b->is_static())
						{
							if (!a->isSleep)*collisionsVec = hinge_to_hinge(hs, a, b, *collisionsVec,false);
						}
						else if (a->is_static() && !b->is_static())
						{
							if (!b->isSleep)*collisionsVec = hinge_to_hinge(hs, a, b, *collisionsVec,true);
						}
					}
				}
			}
		}

		for (std::vector<Collision>& collisions : *collisionsVec)
		{
			for (std::vector<Constraint*> constraints0 : *constraintsVec0)
			{
				if (collisions[0].index1 == constraints0[0]->index1 && collisions[0].index2 == constraints0[0]->index2)
				{
					RigidBody4D* a = rigidBodies4D[constraints0[0]->index1];
					if (constraints0[0]->index2 == -1)
					{
						for (Collision& collision : collisions)for (Constraint* constraint0 : constraints0)
						if (length(collision.collisionManifold.contactPosA - constraint0->collisionConstraint.contacts.contactPosA) < 0.05f)
						{
							for (unsigned i(0); i < 4; i++) {
								resolve_impulse(a, constraint0->impulses[i], constraint0->collisionConstraint.contacts.contactPosA);
							}
						}
					}
					else
					{
						if (constraints0[0]->index2 < rigidBodies4D.size())
						{
							for (Collision& collision : collisions)for (Constraint* constraint0 : constraints0)
							if (length(collision.collisionManifold.contactPosA - constraint0->collisionConstraint.contacts.contactPosA) < 0.05f &&
								length(collision.collisionManifold.contactPosB - constraint0->collisionConstraint.contacts.contactPosB) < 0.05f)
							{
								RigidBody4D* b = rigidBodies4D[constraint0->index2];
								for (unsigned i(0); i < 4; i++) {
									resolve_impulse(a, -constraint0->impulses[i], constraint0->collisionConstraint.contacts.contactPosB);
									resolve_impulse(b, constraint0->impulses[i], constraint0->collisionConstraint.contacts.contactPosA);
								}
							}
						}
						else
						{
							for (Collision& collision : collisions)for (Constraint* constraint0 : constraints0)
							if (length(collision.collisionManifold.contactPosA - constraint0->collisionConstraint.contacts.contactPosA) < 0.05f)
							{
								for (unsigned i(0); i < 4; i++) {
									resolve_impulse(a, constraint0->impulses[i], constraint0->collisionConstraint.contacts.contactPosA);
								}
								//Object4D* o = find_wall4d(groups, walls4D, dynamites4D, constraint0->index2 - rigidBodies4D.size());
								//glm::vec4 contactPosAToB(body_pos_to_world(o, constraint0->collisionConstraint.contacts.contactPosB) - body_pos_to_world(a, constraint0->collisionConstraint.contacts.contactPosA));
								//glm::vec4 eContactPosAToB(normalize(contactPosAToB));
								//glm::vec4 normalShift(eContactPosAToB - dot(collision.collisionManifold.normal, eContactPosAToB) * eContactPosAToB);
								//collision.collisionManifold.normal = normalize(collision.collisionManifold.normal + normalShift);
								//collision.collisionManifold.depth = length(contactPosAToB);
							}
						}
					}
				}
			}
		}
		std::vector <std::vector<Constraint*>> constraintsVec;
		for (std::vector<Collision> collisions : *collisionsVec)
		{
			RigidBody4D* a(rigidBodies4D[collisions[0].index1]);
			if (collisions[0].index2 == -1)
			{
				get_constraint(a, collisions, &constraintsVec);
			}
			else
			{
				if (collisions[0].index2 < rigidBodies4D.size())
				{
					RigidBody4D* b(rigidBodies4D[collisions[0].index2]);
					if (a->objectName == "Billiard" && b->objectName == "Billiard")
					{
						update_billiards(a, b, collisions);
					}
					else
					{
						get_constraint(a, b, collisions, &constraintsVec);
					}
				}
				else
				{
					Wall4D* w(walls4D[collisions[0].index2 - rigidBodies4D.size()]);
					get_constraint(a, w, collisions, &constraintsVec);
				}
			}
		}

		bool isInverseResolve(true);
		for (size_t i(0); i < 20; i++)
		{
			//std::vector<glm::vec4> velocities4D;
			//std::vector<alg::bivec4> angularVelocities4D;
			//for (size_t i(1); i < rigidBodies4D.size(); i++)
			//{
			//	velocities4D.push_back(rigidBodies4D[i]->velocity4D);
			//	angularVelocities4D.push_back(rigidBodies4D[i]->angularVelocity4D);
			//}
			isInverseResolve = !isInverseResolve;
			for (size_t j(0);j< constraintsVec.size();j++)
			{
				std::vector<Constraint*> constraints;
				if (isInverseResolve)constraints = constraintsVec[constraintsVec.size() - j - 1];
				else constraints = constraintsVec[j];
				RigidBody4D* a(rigidBodies4D[constraints[0]->index1]);
				if (constraints[0]->index2 == -1)
				{
					solve_rigidbody_edge(a, &constraints, isInverseResolve);
				}
				else
				{
					if (constraints[0]->index2 < rigidBodies4D.size())
					{
						RigidBody4D* b(rigidBodies4D[constraints[0]->index2]);
						if (!b->is_static())
						{
							solve_rigidbody_rigidbody(a, b, &constraints, isInverseResolve);
						}
						else
						{
							solve_rigidbody_wall(a, b, &constraints, isInverseResolve);
						}
						wake_up_rigidBody4D(a);
						wake_up_rigidBody4D(b);
					}
					else
					{
						Object4D* w(walls4D[constraints[0]->index2 - rigidBodies4D.size()]);
						solve_rigidbody_wall(a, w, &constraints, isInverseResolve);
					}
				}
			}
			//for (size_t i(1); i < rigidBodies4D.size(); i++)
			//{
			//	velocities4D[i-1] = rigidBodies4D[i]->velocity4D - velocities4D[i - 1];
			//	angularVelocities4D[i-1] = rigidBodies4D[i]->angularVelocity4D - angularVelocities4D[i-1];
			//	rigidBodies4D[i]->momentInertiaScalar = get_moment_inertia_scalar(rigidBodies4D[i], velocities4D[i-1], angularVelocities4D[i-1]);
			//}
		}

		//for (std::vector<Constraint*> cs : *constraintsVec0)for (Constraint* c : cs)c = nullptr, free(c);
		*constraintsVec0 = constraintsVec;
		for (std::vector<Constraint*> cs: constraintsVec)for (Constraint* c : cs)c = nullptr, free(c);
	}

	static void caculate_joints4D(std::vector<RigidBody4D*> rigidBodies4D,
		std::vector<Group*> groups,
		vector<Wall4D*> walls4D,
		std::vector < Stick4D*> sticks4D,
		std::vector < Spring4D*> springs4D,
		const float dt)
	{
		for (Stick4D* i : sticks4D)
		{
			if (i->index2->isValid)
			{
				if (i->index2->n < rigidBodies4D.size())
				{
					RigidBody4D* b(rigidBodies4D[i->index2->n]);
					if (i->index1 < rigidBodies4D.size())
					{
						RigidBody4D* a(rigidBodies4D[i->index1]);
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
					else
					{
						Wall4D* c(walls4D[i->index1 - rigidBodies4D.size()]);
						i->solve_rigidbody_wall(b, c, dt);
					}
				}
				if (i->index2->n >= rigidBodies4D.size())
				{
					if (i->index1 < rigidBodies4D.size())
					{
						RigidBody4D* a(rigidBodies4D[i->index1]);
						Wall4D* d(walls4D[i->index2->n - rigidBodies4D.size()]);
						i->solve_rigidbody_wall(a, d, dt);
					}
				}
			}
		}
		for (Spring4D* i : springs4D)
		{
			if (i->index2->isValid)
			{
				if (i->index2->n < rigidBodies4D.size())
				{
					RigidBody4D* b(rigidBodies4D[i->index2->n]);
					if (i->index1 < rigidBodies4D.size())
					{
						RigidBody4D* a(rigidBodies4D[i->index1]);
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
					else if (i->index1 >= rigidBodies4D.size())
					{
						Wall4D* c(walls4D[i->index1 - rigidBodies4D.size()]);
						i->solve_rigidbody_wall(b, c, dt);
					}
				}
				else
				{
					if (i->index1 < rigidBodies4D.size())
					{
						RigidBody4D* a(rigidBodies4D[i->index1]);
						Wall4D* d(walls4D[i->index2->n - rigidBodies4D.size()]);
						i->solve_rigidbody_wall(a, d, dt);
					}
				}
			}
		}
	}

	static void solve_rigidBodies_position4D(std::vector<RigidBody4D*> rigidBodies4D, vector<Wall4D*> walls4D, std::vector<std::vector<Collision>>* collisionsVec, const float dt)
	{
		for (size_t i(0); i < rigidBodies4D.size(); i++)
		{
			RigidBody4D* a(rigidBodies4D[i]);
			if (!a->is_static()&&!a->isSleep)
			{
				a->set_position4D(a->position4D + a->velocity4D * dt);
				a->set_rotation4D(update(a->rotation4D, a->angularVelocity4D * dt));	
			}
		}
	}

	static void update_stick4D(std::vector<RigidBody4D*> rigidBodies4D,
		vector<Wall4D*> walls4D,
		Stick4D* stick4D)
	{

		if (!stick4D->index2->isValid)
		{
			if (stick4D->index1 < rigidBodies4D.size())
			{
				stick4D->update_stick4D(rigidBodies4D[stick4D->index1]);
			}
			else
			{
				stick4D->update_stick4D(walls4D[stick4D->index1 - rigidBodies4D.size()]);
			}
		}
		else
		{
			if (stick4D->index2->n < rigidBodies4D.size())
			{
				if (stick4D->index1 < rigidBodies4D.size())
				{
					stick4D->update_stick4D(rigidBodies4D[stick4D->index1], rigidBodies4D[stick4D->index2->n]);
				}
				else
				{
					stick4D->update_stick4D(rigidBodies4D[stick4D->index2->n], walls4D[stick4D->index1 - rigidBodies4D.size()]);
				}
			}
			else
			{
				if (stick4D->index1 < rigidBodies4D.size())
				{
					stick4D->update_stick4D(walls4D[stick4D->index2->n - rigidBodies4D.size()], rigidBodies4D[stick4D->index1]);
				}
				else
				{
					stick4D->update_stick4D(walls4D[stick4D->index1 - rigidBodies4D.size()], walls4D[stick4D->index2->n - rigidBodies4D.size()]);
				}
			}
		}
	}
	static void update_spring4D(std::vector<RigidBody4D*> rigidBodies4D,
		vector<Wall4D*> walls4D,
		Spring4D* spring4D)
	{

		if (!spring4D->index2->isValid)
		{
			if (spring4D->index1 < rigidBodies4D.size())
			{
				spring4D->update_spring4D(rigidBodies4D[spring4D->index1]);
			}
			else
			{
				spring4D->update_spring4D(walls4D[spring4D->index1 - rigidBodies4D.size()]);
			}
		}
		else
		{
			if (spring4D->index2->n < rigidBodies4D.size())
			{
				if (spring4D->index1 < rigidBodies4D.size())
				{
					spring4D->update_spring4D(rigidBodies4D[spring4D->index1], rigidBodies4D[spring4D->index2->n]);
				}
				else
				{
					spring4D->update_spring4D(rigidBodies4D[spring4D->index2->n], walls4D[spring4D->index1 - rigidBodies4D.size()]);
				}
			}
			else
			{
				if (spring4D->index1 < rigidBodies4D.size())
				{
					spring4D->update_spring4D(walls4D[spring4D->index2->n - rigidBodies4D.size()], rigidBodies4D[spring4D->index1]);
				}
				else
				{
					spring4D->update_spring4D(walls4D[spring4D->index1 - rigidBodies4D.size()], walls4D[spring4D->index2->n - rigidBodies4D.size()]);
				}
			}
		}
	}

	static void update_trails4D(std::vector<RigidBody4D*> rigidBodies4D, const float dt, float curTime)
	{
		for (size_t i(0); i < rigidBodies4D.size(); i++)
		{
			rigidBodies4D[i]->update_trail4D(dt, curTime);
		}
	}

	static void clear_forces4D(std::vector<RigidBody4D*> rigidBodies4D)
	{
		for (RigidBody4D* i : rigidBodies4D)
		{
			i->forceSystems4D.clear();
		}
	}

	static void update_physic4D(std::vector<RigidBody4D*> rigidBodies4D,
		std::vector<size_t> groupIndices,
		std::vector<Group*> groups,
		vector<Wall4D*> walls4D,
		std::vector<Terrain4D*> terrains4D,
		std::vector<Water4D*> waters4D,
		std::vector<std::vector<Collision>>* collisionsVec,
		std::vector <std::vector<Constraint*>>* constraintsVec,
		std::vector < Stick4D*> sticks4D,
		std::vector < Spring4D*> springs4D,
		std::vector < std::vector < HingeConstraint4D*>> hingeConstraintsVec,
		const float dt)
	{
		sleep_rigidBodies4D(rigidBodies4D, dt);
		wake_up_rigidBodies4D(rigidBodies4D);
		start_rigidBodies4D(rigidBodies4D, collisionsVec,dt);
		caculate_joints4D(rigidBodies4D, groups, walls4D, sticks4D, springs4D, dt);
		caculate_rigidBodies4D(rigidBodies4D, groupIndices, groups, walls4D, terrains4D, waters4D, hingeConstraintsVec, collisionsVec, constraintsVec, dt);
		solve_rigidBodies_position4D(rigidBodies4D, walls4D, collisionsVec, dt);
		clear_forces4D(rigidBodies4D);
	}

	static void before_render_physic4D(std::vector<RigidBody4D*> rigidBodies4D,
		std::vector<Group*> groups,
		vector<Wall4D*> walls4D,
		std::vector < Stick4D*> sticks4D,
		std::vector < Spring4D*> springs4D,
		bool isTrail4D,
		const float dt, float curTime)
	{
		for (Stick4D* i : sticks4D) { if (i->index2->isValid)update_stick4D(rigidBodies4D, walls4D,i); }
		for (Spring4D* i : springs4D) { if (i->index2->isValid)update_spring4D(rigidBodies4D, walls4D,i); }
		if (isTrail4D) { update_trails4D(rigidBodies4D, dt, curTime); }
	}
}