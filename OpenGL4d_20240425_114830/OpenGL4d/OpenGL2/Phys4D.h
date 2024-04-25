#pragma once
#include"PhyFunction.h"
namespace phy {
	static float timeToSleep=0.f;
	static void sleep_rigidBodies4D(std::vector<RigidBody4D*> rigidBodies4D, std::vector<RigidBody4D*> dynamites4D2, const float dt)
	{
		for (int i = 0; i < size_of_objects4d(rigidBodies4D, dynamites4D2); i++)
		{
			RigidBody4D* a = find_rigidbody4d(rigidBodies4D, dynamites4D2, i);
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
			for (int i = 0; i < size_of_objects4d(rigidBodies4D, dynamites4D2); i++)
			{
				RigidBody4D* a = find_rigidbody4d(rigidBodies4D, dynamites4D2, i);
				if (!a->isSleep)
				{
					a->pPosition4D = a->position4D;
					if (a->isContinueSleep&&!a->is_static())
					{
						a->isSleep = true;
						a->velocity4D = glm::vec4(0.f);
						a->angularVelocity4D = alg::bivec4(0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
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
		for (int i = 0; i < size_of_objects4d(rigidBodies4D, dynamites4D2); i++)
		{
			RigidBody4D* a = find_rigidbody4d(rigidBodies4D, dynamites4D2, i);
			if (a->isSleep)
			{
				if (length(a->velocity4D) > 0.1f || length(a->angularVelocity4D) > 0.8f || a->forceSystems4D.size() > 0 || length(a->position4D - a->pPosition4D) > 0.05f)
				{
					a->isSleep = false;
					a->isContinueSleep = true;
				}
			}
			if (a->isSleep)
			{
				a->velocity4D = glm::vec4(0.f);
				a->angularVelocity4D = alg::bivec4(0.f, 0.f, 0.f, 0.f, 0.f, 0.f);
			}
		}
	}

	static void update_rigidbody_velocity4D(RigidBody4D* a, const float dt)
	{
		if (!a->is_static())
		{
			alg::bivec4 delta_angular_vel = alg::bivec4();
			for (ForceSystem4D* j : a->forceSystems4D)
			{
				a->velocity4D += inverse_moment_of_mass(a, j->force4D, dt);
				if (j->position4D != glm::vec4(0.f))
				{
					delta_angular_vel = delta_angular_vel + inverse_moment_of_inertia(a,wedge_v(alg::vec4(j->position4D), rotate(a->rotation4D.reverse(), alg::vec4(j->force4D * dt))));
				}
			}
			a->angularVelocity4D = a->angularVelocity4D + delta_angular_vel;
			a->forceSystems4D.clear();
		}
	}

	static void start_rigidBodies4D(std::vector<RigidBody4D*> rigidBodies4D, std::vector<RigidBody4D*> dynamites4D2, const float dt)
	{
		for (int i = 0; i < size_of_objects4d(rigidBodies4D, dynamites4D2); i++)
		{
			RigidBody4D* a = find_rigidbody4d(rigidBodies4D, dynamites4D2, i);
			if (!a->is_static()&&!a->isSleep)
			{
				if (a->isGravity)
				{
					a->forceSystems4D.push_back(new ForceSystem4D(a->mass * glm::vec4(0, -9.8f, 0, 0), glm::vec4(0.f)));
				}
				update_rigidbody_velocity4D(a, dt);
			}
		}
	}

	static void caculate_rigidBodies4D(std::vector<RigidBody4D*> rigidBodies4D, std::vector<RigidBody4D*> dynamites4D2, std::vector<Group*> groups, vector<Wall4D*> walls4D,vector<Wall4D*> dynamites4D, std::vector<Water4D*> waters4D, std::vector<Collision*>* collisions, std::vector<Constraint*>* constraints, const float dt)
	{
		for (int i = 0; i < size_of_objects4d(rigidBodies4D, dynamites4D2); i++)
		{
			RigidBody4D* a = find_rigidbody4d(rigidBodies4D, dynamites4D2, i);
			if (!a->isBeyond)
			{
				for (int j = i + 1; j < size_of_objects4d(rigidBodies4D, dynamites4D2); j++)
				{
					RigidBody4D* b = find_rigidbody4d(rigidBodies4D, dynamites4D2, j);
					if (!b->isBeyond)
					{
						if (!a->isFrozen)
						{
							if (!b->isFrozen)
							{
								if (!a->isSleep || !b->isSleep)
								{
									*collisions = detect_rigidbody_or_wall(a, b, i, j, *collisions);
								}
							}
							if (b->isFrozen)
							{
								if (a->velocity4D != glm::vec4(0.f) || !a->isSleep)
									*collisions = detect_rigidbody_or_wall(a, b, i, -1, *collisions);
							}
						}

						if (a->isFrozen)
						{
							if (!b->isFrozen)
							{
								if (b->velocity4D != glm::vec4(0.f) || !b->isSleep)
									*collisions = detect_rigidbody_or_wall(b, a, j, -1, *collisions);
							}
						}
					}
				}
				if (!a->isFrozen)
				{
					if (a->velocity4D != glm::vec4(0.f) || !a->isSleep)
					{
						int wallIndex0 = 0;
						for (int j = 0; j < groups.size(); j++) {
							for (int k = 0; k < groups[j]->walls4D.size(); k++) {
								if (groups[j]->isRender)
									*collisions = detect_rigidbody_or_wall(a, groups[j]->walls4D[k], i, size_of_objects4d(rigidBodies4D, dynamites4D2) + wallIndex0 + k, *collisions);
							}
							wallIndex0 += groups[j]->walls4D.size();
							for (Terrain4D* k : groups[j]->terrains4D) {
								*collisions = detect_rigidbody_terrain(a, k, i, *collisions);
							}
						}
						for (int j = 0; j < walls4D.size(); j++)
						{
							*collisions = detect_rigidbody_or_wall(a, walls4D[j], i, size_of_objects4d(rigidBodies4D, dynamites4D2, groups) + j, *collisions);
						}
						for (int j = 0; j < dynamites4D.size(); j++)
						{
							*collisions = detect_rigidbody_or_wall(a, dynamites4D[j], i, size_of_objects4d(rigidBodies4D, dynamites4D2, groups, walls4D) + j, *collisions);
						}
					}
				}
				if (!a->isFrozen && (a->velocity4D != glm::vec4(0.f) || !a->isSleep))
				{
					*collisions = detect_rigidbody_edge(a, i, *collisions);
				}
			}
		}

		for (int i = 0; i < size_of_objects4d(rigidBodies4D, dynamites4D2); i++)
		{
			float count = 0.f;
			float massAdjustmentCount = 0.f;
			glm::vec4 normal4DAdd=glm::vec4(0.f);
			for (Collision* collision : *collisions)
			{
				if (collision->index1 == i)
				{
					normal4DAdd += collision->collisionManifold.normal;
					count += 1.f;
					massAdjustmentCount += 1.f / collision->massAdjustmentA;
				}
				if (collision->index2 == i)
				{
					normal4DAdd += collision->collisionManifold.normal;
					count += 1.f;
					massAdjustmentCount += 1.f / collision->massAdjustmentB;
				}
			}
			//if (count==0.f)
			//{
			//	find_rigidbody4d(rigidBodies4D, dynamites4D2,i)->isSleep=false;
			//}
			float n = 0.f;
			for (Collision* collision : *collisions)
			{
				if (collision->index1 == i || collision->index2 == i)
				{
					n += abs(dot(collision->collisionManifold.normal, normal4DAdd));
				}
			}
			for (Collision* collision : *collisions)
			{
				if (collision->index1 == i)
				{
					{
						collision->massAdjustmentA *= max(massAdjustmentCount * n / count / count, 1.f);
					}
				}
				if (collision->index2 == i)
				{
					{
						collision->massAdjustmentB *= max(massAdjustmentCount * n / count / count, 1.f);
					}
				}
			}
		}

		for (Collision* collision : *collisions)
		{
			RigidBody4D* a = find_rigidbody4d(rigidBodies4D, dynamites4D2, collision->index1);
			if (collision->index2 == -1)
			{
				get_constraint(collision->index1, a, collision, constraints);
			}
			if (collision->index2 != -1)
			{
				if (collision->index2 < size_of_objects4d(rigidBodies4D, dynamites4D2))
				{
					RigidBody4D* b = find_rigidbody4d(rigidBodies4D, dynamites4D2, collision->index2);
					get_constraint(collision->index1, collision->index2, a, b, collision, constraints);
				}
				if (collision->index2 >= size_of_objects4d(rigidBodies4D, dynamites4D2))
				{
					get_constraint(collision->index1, collision->index2,a, find_wall4d(groups, walls4D, dynamites4D, collision->index2 - size_of_objects4d(rigidBodies4D, dynamites4D2)), collision, constraints);
				}
			}
		}
		for (unsigned i = 0; i < 20; i++)
		{
			for (Constraint* constraint : *constraints)
			{
				RigidBody4D* a= find_rigidbody4d(rigidBodies4D, dynamites4D2, constraint->index1);
				if (constraint->index2 == -1)
				{
					solve_rigidbody_edge(a, constraint, dt);
					update_rigidbody_velocity4D(a,dt);
				}
				if (constraint->index2 != -1)
				{
					if (constraint->index2 < size_of_objects4d(rigidBodies4D, dynamites4D2))
					{
						RigidBody4D* b = find_rigidbody4d(rigidBodies4D, dynamites4D2, constraint->index2);
						if (!b->is_static())
						{
							solve_rigidbody_rigidbody(a, b, constraint, dt);
							update_rigidbody_velocity4D(a, dt);
							update_rigidbody_velocity4D(b, dt);
							wake_up_rigidBody4D(a);
							wake_up_rigidBody4D(b);
						}
						else
						{
							solve_rigidbody_wall(a, b, constraint, dt);
							update_rigidbody_velocity4D(a, dt);
							update_rigidbody_velocity4D(b, dt);
							wake_up_rigidBody4D(a);
							wake_up_rigidBody4D(b);
						}
					}
					if (constraint->index2 >= size_of_objects4d(rigidBodies4D, dynamites4D2))
					{
						solve_rigidbody_wall(a, find_wall4d(groups, walls4D, dynamites4D, constraint->index2 - size_of_objects4d(rigidBodies4D, dynamites4D2)), constraint, dt);
						update_rigidbody_velocity4D(a, dt);
					}
				}
			}
		}
		constraints->clear();
		glm::vec4 dir_a_to_b;
		float dis;
		glm::vec4 dir_a_to_b_e;
		glm::vec4 force4D;
		for (size_t i = 1; i < size_of_objects4d(rigidBodies4D, dynamites4D2); i++)
		{
			RigidBody4D* a = find_rigidbody4d(rigidBodies4D, dynamites4D2, i);
			if (a->objectName == "Celestial4D")
			{
				for (size_t j = i + 1; j < size_of_objects4d(rigidBodies4D, dynamites4D2); j++)
				{
					RigidBody4D* b = find_rigidbody4d(rigidBodies4D, dynamites4D2, j);
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
						a->forceSystems4D.push_back(new ForceSystem4D(force4D, glm::vec4(0.f)));
						b->forceSystems4D.push_back(new ForceSystem4D(-force4D, glm::vec4(0.f)));
						update_rigidbody_velocity4D(b, dt);
					}
				}
				update_rigidbody_velocity4D(a, dt);
			}
		}
	}

	static void update_joints4D(std::vector<RigidBody4D*> rigidBodies4D,
		std::vector<RigidBody4D*> dynamites4D2,
		std::vector<Group*> groups,
		vector<Wall4D*> walls4D,
		vector<Wall4D*> dynamites4D,
		std::vector < Stick4D*> sticks4D,
		std::vector < Spring4D*> springs4D,
		std::vector<HingeConstraint4D*> hingeConstraints,
		std::vector<Constraint*>* constraints,
		const float dt)
	{
		for (Stick4D* i : sticks4D)
		{
			if (i->index2 != -1)
			{
				if (i->index2 < size_of_objects4d(rigidBodies4D, dynamites4D2))
				{
					RigidBody4D* b = find_rigidbody4d(rigidBodies4D, dynamites4D2, i->index2);
					if (i->index1 < size_of_objects4d(rigidBodies4D, dynamites4D2))
					{
						RigidBody4D* a = find_rigidbody4d(rigidBodies4D, dynamites4D2, i->index1);
						if (!a->is_static() && !b->is_static())
						{
							i->update_rigidbody_rigidbody(a, b, dt);
						}
						if (a->is_static() && b->is_static())
						{
							i->update_rigidbody_rigidbody(a, b, dt);
						}
						if (!a->is_static() && b->is_static())
						{
							i->update_rigidbody_wall(a, b, dt);
						}
						if (a->is_static() && !b->is_static())
						{
							i->update_rigidbody_wall(b, a, dt);
						}
						update_rigidbody_velocity4D(a, dt);
					}
					if (i->index1 >= size_of_objects4d(rigidBodies4D, dynamites4D2))
					{
						Wall4D* c = find_wall4d(groups, walls4D, dynamites4D, i->index1 - size_of_objects4d(rigidBodies4D, dynamites4D2));
						if (!b->is_static())
						{
							i->update_rigidbody_wall(b, c, dt);
						}
						if (b->is_static())
						{
							i->update_rigidbody_wall(b, c, dt);
						}
					}
					update_rigidbody_velocity4D(b, dt);
				}
				if (i->index2 >= size_of_objects4d(rigidBodies4D, dynamites4D2))
				{
					if (i->index1 < size_of_objects4d(rigidBodies4D, dynamites4D2))
					{
						RigidBody4D* a = find_rigidbody4d(rigidBodies4D, dynamites4D2, i->index1);
						Wall4D* d = find_wall4d(groups, walls4D, dynamites4D, i->index2 - size_of_objects4d(rigidBodies4D, dynamites4D2));
						if (!a->is_static())
						{
							i->update_rigidbody_wall(a, d, dt);
						}
						if (a->is_static())
						{
							i->update_rigidbody_wall(a, d, dt);
						}
						update_rigidbody_velocity4D(a, dt);
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
					RigidBody4D* b = find_rigidbody4d(rigidBodies4D, dynamites4D2, i->index2);
					if (i->index1 < size_of_objects4d(rigidBodies4D, dynamites4D2))
					{
						RigidBody4D* a = find_rigidbody4d(rigidBodies4D, dynamites4D2, i->index1);
						if (!a->is_static() && !b->is_static())
						{
							i->update_rigidbody_rigidbody(a, b, dt);
						}
						if (a->is_static() && b->is_static())
						{
							i->update_rigidbody_rigidbody(a, b, dt);
						}
						if (!a->is_static() && b->is_static())
						{
							i->update_rigidbody_wall(a, b, dt);
						}
						if (a->is_static() && !b->is_static())
						{
							i->update_rigidbody_wall(b, a, dt);
						}
						update_rigidbody_velocity4D(a, dt);
					}
					if (i->index1 >= size_of_objects4d(rigidBodies4D, dynamites4D2))
					{
						Wall4D* c = find_wall4d(groups, walls4D, dynamites4D, i->index1 - size_of_objects4d(rigidBodies4D, dynamites4D2));
						if (!b->is_static())
						{
							i->update_rigidbody_wall(b, c, dt);
						}
						if (b->is_static())
						{
							i->update_rigidbody_wall(b, c, dt);
						}
					}
					update_rigidbody_velocity4D(b, dt);
				}
				if (i->index2 >= size_of_objects4d(rigidBodies4D, dynamites4D2))
				{
					RigidBody4D* a = find_rigidbody4d(rigidBodies4D, dynamites4D2, i->index1);
					Wall4D* d = find_wall4d(groups, walls4D, dynamites4D, i->index2 - size_of_objects4d(rigidBodies4D, dynamites4D2));
					if (i->index1 < size_of_objects4d(rigidBodies4D, dynamites4D2))
					{
						if (!a->is_static())
						{
							i->update_rigidbody_wall(a, d, dt);
						}
						if (a->is_static())
						{
							i->update_rigidbody_wall(a, d, dt);
						}
						update_rigidbody_velocity4D(a, dt);
					}
				}
			}
		}
		for (HingeConstraint4D* i : hingeConstraints)
		{
			if (i->index2 == -1)
			{
				if (i->index1 < size_of_objects4d(rigidBodies4D, dynamites4D2))
				{
					get_constraint(i->index1, find_rigidbody4d(rigidBodies4D, dynamites4D2, i->index1), i,constraints);
				}
			}
			if (i->index2 != -1)
			{
				if (i->index2 < size_of_objects4d(rigidBodies4D, dynamites4D2))
				{
					if (i->index1 < size_of_objects4d(rigidBodies4D, dynamites4D2))
					{
						RigidBody4D* a = find_rigidbody4d(rigidBodies4D, dynamites4D2, i->index1);
						RigidBody4D* b = find_rigidbody4d(rigidBodies4D, dynamites4D2, i->index2);
						if (!a->is_static() && !find_rigidbody4d(rigidBodies4D, dynamites4D2, i->index2)->is_static())
						{
							get_constraint(i->index1, i->index2, a, b, i, constraints);
						}
						if (a->is_static() && b->is_static())
						{
							get_constraint(i->index1, i->index2, a, b, i, constraints);
						}
						if (!a->is_static() && b->is_static())
						{
							get_constraint(i->index1, i->index2, a, b, i, constraints,false);
						}
						if (a->is_static() && !b->is_static())
						{
							get_constraint(i->index2, i->index1, b, a, i, constraints, true);
						}
					}
				}
			}
		}
		for (unsigned i = 0; i < 20; i++)
		{
			for (Constraint* i : *constraints)
			{
				if (i->index2 == -1)
				{
					if (i->index1 < size_of_objects4d(rigidBodies4D, dynamites4D2))
					{
						RigidBody4D* a = find_rigidbody4d(rigidBodies4D, dynamites4D2, i->index1);
						solve_rigidbody2(a, i, dt);
						update_rigidbody_velocity4D(a, dt);
					}
				}
				if (i->index2 != -1)
				{
					if (i->index2 < size_of_objects4d(rigidBodies4D, dynamites4D2))
					{
						if (i->index1 < size_of_objects4d(rigidBodies4D, dynamites4D2))
						{
							RigidBody4D* a = find_rigidbody4d(rigidBodies4D, dynamites4D2, i->index1);
							RigidBody4D* b = find_rigidbody4d(rigidBodies4D, dynamites4D2, i->index2);
							if (!a->is_static() && !b->is_static())
							{
								solve_rigidbody_rigidbody2(a, b, i, dt);
								update_rigidbody_velocity4D(a, dt);
								update_rigidbody_velocity4D(b, dt);
							}
							if (a->is_static() && b->is_static())
							{
								solve_rigidbody_rigidbody2(a, b, i, dt);
								update_rigidbody_velocity4D(a, dt);
								update_rigidbody_velocity4D(b, dt);
							}
							if (!a->is_static() && b->is_static())
							{
								solve_rigidbody_wall2(a, b, i, dt);
								update_rigidbody_velocity4D(a, dt);
							}
							if (a->is_static() && !b->is_static())
							{
								solve_rigidbody_wall2(b, a, i, dt);
								update_rigidbody_velocity4D(b, dt);
							}
						}
					}
				}
			}
		}
		constraints->clear();
	}

	static void update_rigidBodies_position4D(std::vector<RigidBody4D*> rigidBodies4D, std::vector<RigidBody4D*> dynamites4D2, std::vector<Group*> groups, vector<Wall4D*> walls4D, vector<Wall4D*> dynamites4D, std::vector<Collision*>* collisions, const float dt)
	{
		for (int i = 0; i < size_of_objects4d(rigidBodies4D, dynamites4D2); i++)
		{
			RigidBody4D* a = find_rigidbody4d(rigidBodies4D, dynamites4D2, i);
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
			if (stick4D->index1 >= size_of_objects4d(rigidBodies4D, dynamites4D2))
			{
				stick4D->update_stick4D(find_wall4d(groups, walls4D,dynamites4D, stick4D->index1 - size_of_objects4d(rigidBodies4D, dynamites4D2)));
			}
		}
		if (stick4D->index2 != -1)
		{
			if (stick4D->index2 < size_of_objects4d(rigidBodies4D, dynamites4D2))
			{
				if (stick4D->index1 < size_of_objects4d(rigidBodies4D, dynamites4D2))
				{
					stick4D->update_stick4D(find_rigidbody4d(rigidBodies4D, dynamites4D2, stick4D->index1), find_rigidbody4d(rigidBodies4D, dynamites4D2, stick4D->index2));
				}
				if (stick4D->index1 >= size_of_objects4d(rigidBodies4D, dynamites4D2))
				{
					stick4D->update_stick4D(find_rigidbody4d(rigidBodies4D, dynamites4D2, stick4D->index2), find_wall4d(groups, walls4D,dynamites4D, stick4D->index1 - size_of_objects4d(rigidBodies4D, dynamites4D2)));
				}
			}
			if (stick4D->index2 >= size_of_objects4d(rigidBodies4D, dynamites4D2))
			{
				if (stick4D->index1 < size_of_objects4d(rigidBodies4D, dynamites4D2))
				{
					stick4D->update_stick4D(find_wall4d(groups, walls4D,dynamites4D, stick4D->index2 - size_of_objects4d(rigidBodies4D, dynamites4D2)), find_rigidbody4d(rigidBodies4D, dynamites4D2, stick4D->index1));
				}
				if (stick4D->index1 >= size_of_objects4d(rigidBodies4D, dynamites4D2))
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
			if (spring4D->index1 >= size_of_objects4d(rigidBodies4D, dynamites4D2))
			{
				spring4D->update_spring4D(find_wall4d(groups, walls4D,dynamites4D, spring4D->index1 - size_of_objects4d(rigidBodies4D, dynamites4D2)));
			}
		}
		if (spring4D->index2 != -1)
		{
			if (spring4D->index2 < size_of_objects4d(rigidBodies4D, dynamites4D2))
			{
				if (spring4D->index1 < size_of_objects4d(rigidBodies4D, dynamites4D2))
				{
					spring4D->update_spring4D(find_rigidbody4d(rigidBodies4D, dynamites4D2, spring4D->index1), find_rigidbody4d(rigidBodies4D, dynamites4D2, spring4D->index2));
				}
				if (spring4D->index1 >= size_of_objects4d(rigidBodies4D, dynamites4D2))
				{
					spring4D->update_spring4D(find_rigidbody4d(rigidBodies4D, dynamites4D2, spring4D->index2), find_wall4d(groups, walls4D, dynamites4D, spring4D->index1 - size_of_objects4d(rigidBodies4D, dynamites4D2)));
				}
			}
			if (spring4D->index2 >= size_of_objects4d(rigidBodies4D, dynamites4D2))
			{
				if (spring4D->index1 < size_of_objects4d(rigidBodies4D, dynamites4D2))
				{
					spring4D->update_spring4D(find_wall4d(groups, walls4D, dynamites4D, spring4D->index2 - size_of_objects4d(rigidBodies4D, dynamites4D2)), find_rigidbody4d(rigidBodies4D, dynamites4D2, spring4D->index1));
				}
				if (spring4D->index1 >= size_of_objects4d(rigidBodies4D, dynamites4D2))
				{
					spring4D->update_spring4D(find_wall4d(groups, walls4D, dynamites4D, spring4D->index1 - size_of_objects4d(rigidBodies4D, dynamites4D2)), find_wall4d(groups, walls4D, dynamites4D, spring4D->index2 - size_of_objects4d(rigidBodies4D, dynamites4D2)));
				}
			}
		}
	}

	static void update_trails4D(std::vector<RigidBody4D*> rigidBodies4D, std::vector<RigidBody4D*> dynamites4D2, const float dt, float curTime)
	{
		for (int i = 0; i < size_of_objects4d(rigidBodies4D, dynamites4D2); i++)
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
		std::vector<Collision*>* collisions,
		std::vector < Stick4D*> sticks4D,
		std::vector < Spring4D*> springs4D,
		std::vector<HingeConstraint4D*> hingeConstraints,
		std::vector<Constraint*>* constraints,
		const float dt)
	{
		sleep_rigidBodies4D(rigidBodies4D, dynamites4D2, dt);
		wake_up_rigidBodies4D(rigidBodies4D, dynamites4D2);
		start_rigidBodies4D(rigidBodies4D, dynamites4D2, dt);
		caculate_rigidBodies4D(rigidBodies4D, dynamites4D2, groups, walls4D, dynamites4D, waters4D, collisions, constraints, dt);
		update_joints4D(rigidBodies4D, dynamites4D2, groups, walls4D, dynamites4D, sticks4D, springs4D, hingeConstraints, constraints, dt);
		update_rigidBodies_position4D(rigidBodies4D, dynamites4D2, groups, walls4D, dynamites4D, collisions, dt);
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