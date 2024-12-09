#pragma once
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
		collisionsVec->clear();
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
									*collisionsVec = detect_rigidbody_or_wall(i, j, a, b, *collisionsVec);
							}
						}
						else
						{
							if (!b->isFrozen)
							{
								if (b->velocity4D != glm::vec4(0.f) || !b->isSleep)
									*collisionsVec = detect_rigidbody_or_wall(j, i, b, a, *collisionsVec);
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
			if (!hs[0]->index2.isValid)
			{
				if (hs[0]->index1 < rigidBodies4D.size())
				{
					RigidBody4D* a(rigidBodies4D[hs[0]->index1]);
					if (!a->isSleep && !a->is_static())*collisionsVec = hinge_to_hinge(hs, a, a, *collisionsVec,false);
				}
			}
			else
			{
				if (hs[0]->index2.n < rigidBodies4D.size())
				{
					RigidBody4D* b(rigidBodies4D[hs[0]->index2.n]);
					if (hs[0]->index1 < rigidBodies4D.size())
					{
						RigidBody4D* a(rigidBodies4D[hs[0]->index1]);
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
					else
					{
						Object4D* a(find_object4d(rigidBodies4D, walls4D, hs[0]->index1));
						if (!b->isSleep&& !b->is_static())*collisionsVec = hinge_to_hinge(hs, a, b, *collisionsVec, true);
					}
				}
				else
				{
					Object4D* b(find_object4d(rigidBodies4D, walls4D, hs[0]->index2.n));
					if (hs[0]->index1 < rigidBodies4D.size())
					{
						RigidBody4D* a(rigidBodies4D[hs[0]->index1]);
						if (!a->isSleep&&!a->is_static())*collisionsVec = hinge_to_hinge(hs, a, b, *collisionsVec, false);
					}
				}
			}
		}

		//for (std::vector<Collision> collisions : *collisionsVec)
		//{
		//	RigidBody4D* a(rigidBodies4D[collisions[0].index1]);
		//	glm::vec4 contactPosA(collisions[0].collisionManifold.contactPosA);
		//	if (collisions.size() == 2)
		//	{
		//		glm::vec4 a(collisions[0].collisionManifold.contactPosA);
		//		glm::vec4 b(collisions[1].collisionManifold.contactPosA);
		//		glm::vec4 ab(alg::normalize(b - a));
		//		float lambda(alg::dot(-a, ab));
		//		contactPosA = a + lambda * ab;
		//	}
		//	else if (collisions.size() > 2)
		//	{
		//		glm::ivec3 contactPosAIndices(glm::ivec3(0));
		//		glm::vec3 contactPosADistances(glm::vec3(0.f));
		//		for (size_t j(0);j < collisions.size();j++)
		//		{
		//			if (contactPosADistances[0] < alg::length(collisions[j].collisionManifold.contactPosA))
		//			{
		//				contactPosAIndices[0] = j;
		//				contactPosADistances[0] = alg::length(collisions[j].collisionManifold.contactPosA);
		//			}
		//		}
		//		for (size_t j(0); j < collisions.size(); j++)
		//		{
		//			if (j != contactPosAIndices[0])
		//			{
		//				glm::vec4 a(collisions[contactPosAIndices[0]].collisionManifold.contactPosA);
		//				glm::vec4 b(collisions[j].collisionManifold.contactPosA);
		//				glm::vec4 ab(alg::normalize(b - a));
		//				float lambda(alg::dot(-a, ab));
		//				glm::vec4 contactPosA0(a + lambda * ab);
		//				if (contactPosADistances[1] < alg::length(contactPosA0))
		//				{
		//					contactPosAIndices[1] = j;
		//					contactPosADistances[1] = alg::length(contactPosA0);
		//				}
		//			}
		//		}
		//		for (size_t j(0); j < collisions.size(); j++)
		//		{
		//			if (j != contactPosAIndices[0] && j != contactPosAIndices[1])
		//			{
		//				glm::vec4 a(collisions[contactPosAIndices[0]].collisionManifold.contactPosA);
		//				glm::vec4 b(collisions[contactPosAIndices[1]].collisionManifold.contactPosA);
		//				glm::vec4 c(collisions[j].collisionManifold.contactPosA);
		//				glm::vec4 veAB(alg::normalize(b - a));
		//				glm::vec4 vAC(c - a);
		//				glm::vec4 neAB(alg::normalize(vAC - veAB * alg::dot(vAC, veAB)));
		//				float kv(alg::dot(-a, veAB));
		//				float kn(alg::dot(-a, neAB));
		//				glm::vec4 contactPosA0(a + kv * veAB + kn * neAB);
		//				if (contactPosADistances[2] < alg::length(contactPosA0))
		//				{
		//					contactPosAIndices[2] = j;
		//					contactPosADistances[2] = alg::length(contactPosA0);
		//					contactPosA = contactPosA0;
		//				}
		//			}
		//		}
		//	}
		//	for (Collision collision : collisions)collision.collisionManifold.momentInertiaScalarA = get_moment_inertia_scalar(a, contactPosA, wedge_v(alg::vec4(contactPosA), rotate(a->rotation4D.reverse(), alg::vec4(collisions[0].collisionManifold.normal))), a->angularVelocity4D);
		//	if (collisions[0].index2 != -1 && collisions[0].index2 < rigidBodies4D.size()) {
		//		RigidBody4D* b(rigidBodies4D[collisions[0].index2]);
		//	}
		//
		//}
		for (size_t i(0); i < rigidBodies4D.size(); i++)
		{
			RigidBody4D* a0(rigidBodies4D[i]);
			std::vector<glm::vec4> contactPoss;
			glm::vec4 normal4D = glm::vec4();
			for (std::vector<Collision> collisions : *collisionsVec)
			{
				if (collisions[0].index1 == i || collisions[0].index2 == i)
				{
					normal4D = collisions[0].collisionManifold.normal;
					for (Collision collision : collisions)
					{
						contactPoss.push_back(collisions[0].index1 == i ? collision.collisionManifold.contactPosA : collision.collisionManifold.contactPosB);
					}
				}
			}
			if (contactPoss.size() > 0)
			{
				glm::vec4 contactPosA(contactPoss[0]);
				if (contactPoss.size() == 1)
				{
					a0->momentInertiaScalar = get_moment_inertia_scalar(a0, contactPosA, wedge_v(alg::vec4(contactPosA), rotate(a0->rotation4D.reverse(), alg::vec4(normal4D))), a0->angularVelocity4D);
				}
				if (contactPoss.size() == 2)
				{
					glm::vec4 a(contactPoss[0]);
					glm::vec4 b(contactPoss[1]);
					glm::vec4 ab(alg::normalize(b - a));
					float lambda(alg::dot(-a, ab));
					contactPosA = a + lambda * ab;
					a0->momentInertiaScalar = get_moment_inertia_scalar(a0, contactPosA, a0->angularVelocity4D, wedge_v(alg::vec4(contactPosA), rotate(a0->rotation4D.reverse(), alg::vec4(normal4D))));
				}
				else if (contactPoss.size() > 2)
				{
					glm::ivec3 contactPosAIndices(glm::ivec3(0));
					glm::vec3 contactPosADistances(glm::vec3(0.f));
					for (size_t j(0); j < contactPoss.size(); j++)
					{
						if (contactPosADistances[0] < alg::length(contactPoss[j]))
						{
							contactPosAIndices[0] = j;
							contactPosADistances[0] = alg::length(contactPoss[j]);
						}
					}
					for (size_t j(0); j < contactPoss.size(); j++)
					{
						if (j != contactPosAIndices[0])
						{
							glm::vec4 a(contactPoss[contactPosAIndices[0]]);
							glm::vec4 b(contactPoss[j]);
							glm::vec4 ab(alg::normalize(b - a));
							float lambda(alg::dot(-a, ab));
							glm::vec4 contactPosA0(a + lambda * ab);
							if (contactPosADistances[1] < alg::length(contactPosA0))
							{
								contactPosAIndices[1] = j;
								contactPosADistances[1] = alg::length(contactPosA0);
							}
						}
					}
					for (size_t j(0); j < contactPoss.size(); j++)
					{
						if (j != contactPosAIndices[0] && j != contactPosAIndices[1])
						{
							glm::vec4 a(contactPoss[contactPosAIndices[0]]);
							glm::vec4 b(contactPoss[contactPosAIndices[1]]);
							glm::vec4 c(contactPoss[j]);
							glm::vec4 veAB(alg::normalize(b - a));
							glm::vec4 vAC(c - a);
							glm::vec4 neAB(alg::normalize(vAC - veAB * alg::dot(vAC, veAB)));
							float kv(alg::dot(-a, veAB));
							float kn(alg::dot(-a, neAB));
							glm::vec4 contactPosA0(a + kv * veAB + kn * neAB);
							if (contactPosADistances[2] < alg::length(contactPosA0))
							{
								contactPosAIndices[2] = j;
								contactPosADistances[2] = alg::length(contactPosA0);
								contactPosA = contactPosA0;
							}
						}
					}
					a0->momentInertiaScalar = get_moment_inertia_scalar(a0, contactPosA, a0->angularVelocity4D, wedge_v(alg::vec4(contactPosA), rotate(a0->rotation4D.reverse(), alg::vec4(normal4D))));
				}
			}
		}
		for (size_t i(0); i < constraintsVec0->size(); i++) 
		{
			std::vector<Constraint*> constraints0((*constraintsVec0)[i]);
		    for (std::vector<Collision>& collisions : *collisionsVec)
		    {
				if (collisions[0].index1 == constraints0[0]->index1 && collisions[0].index2 == constraints0[0]->index2)
				{
					//if(collisions.size() == constraints0.size())
					//{ }
					RigidBody4D* a = rigidBodies4D[constraints0[0]->index1];
					if (constraints0[0]->index2 == -1)
					{
						for (Collision& collision : collisions)for (Constraint* constraint0 : constraints0)
							if (length(collision.collisionManifold.contactPosA - constraint0->collisionConstraint.contacts.contactPosA) < 0.1f &&
								length(collision.collisionManifold.contactPosB - constraint0->collisionConstraint.contacts.contactPosB) < 0.1f)
							{
								if(collision.type == 1)
								if (constraint0->impulseMagAdd < constraint0->maxImpulseAdd)
								{
									glm::vec4 contactPosAToWorld(body_pos_to_world(a, constraint0->collisionConstraint.contacts.contactPosA));
									glm::vec4 contactPosBToWorld(constraint0->collisionConstraint.contacts.contactPosB);
									glm::vec4 normal2(contactPosAToWorld - contactPosBToWorld);
									glm::vec4 normalE(alg::normalize(normal2));
									collision.collisionManifold.depth = alg::length(normal2);
									collision.collisionManifold.normal = normalE;
									collision.collisionManifold.contactPosA = constraint0->collisionConstraint.contacts.contactPosA;
									collision.collisionManifold.contactPosB = constraint0->collisionConstraint.contacts.contactPosB;
								}
								for (unsigned i(0); i < 4; i++) {
									resolve_impulse(a, -constraint0->impulses[i], constraint0->collisionConstraint.contacts.contactPosA);
								}
							}
					}
					else
					{
						if (constraints0[0]->index2 < rigidBodies4D.size())
						{
							for (Collision& collision : collisions)for (Constraint* constraint0 : constraints0)
								if (length(collision.collisionManifold.contactPosA - constraint0->collisionConstraint.contacts.contactPosA) < 0.1f &&
									length(collision.collisionManifold.contactPosB - constraint0->collisionConstraint.contacts.contactPosB) < 0.1f)
								{
									RigidBody4D* b = rigidBodies4D[constraint0->index2];
									if (collision.type == 1)
									if (constraint0->impulseMagAdd < constraint0->maxImpulseAdd)
									{
										glm::vec4 contactPosAToWorld(body_pos_to_world(a, constraint0->collisionConstraint.contacts.contactPosA));
										glm::vec4 contactPosBToWorld(body_pos_to_world(b, constraint0->collisionConstraint.contacts.contactPosB));
										glm::vec4 normal2(contactPosAToWorld - contactPosBToWorld);
										glm::vec4 normalE(alg::normalize(normal2));
										collision.collisionManifold.depth = alg::length(normal2);
										collision.collisionManifold.normal = normalE;
										collision.collisionManifold.contactPosA = constraint0->collisionConstraint.contacts.contactPosA;
										collision.collisionManifold.contactPosB = constraint0->collisionConstraint.contacts.contactPosB;
									}
									for (unsigned i(0); i < 4; i++) {
										resolve_impulse(a, -constraint0->impulses[i], constraint0->collisionConstraint.contacts.contactPosA);
										resolve_impulse(b, constraint0->impulses[i], constraint0->collisionConstraint.contacts.contactPosB);
									}
								}
						}
						else
						{
							for (Collision& collision : collisions)for (Constraint* constraint0 : constraints0)
								if (length(collision.collisionManifold.contactPosA - constraint0->collisionConstraint.contacts.contactPosA) < 0.1f &&
									length(collision.collisionManifold.contactPosB - constraint0->collisionConstraint.contacts.contactPosB) < 0.1f)
								{
									if (collision.type == 1)
									if (constraint0->impulseMagAdd < constraint0->maxImpulseAdd)
									{
										Wall4D* b(walls4D[constraint0->index2 - rigidBodies4D.size()]);
										glm::vec4 contactPosAToWorld(body_pos_to_world(a, constraint0->collisionConstraint.contacts.contactPosA));
										glm::vec4 contactPosBToWorld(body_pos_to_world(b, constraint0->collisionConstraint.contacts.contactPosB));
										glm::vec4 normal2(contactPosAToWorld - contactPosBToWorld);
										glm::vec4 normalE(alg::normalize(normal2));
										collision.collisionManifold.depth = alg::length(normal2);
										collision.collisionManifold.normal = normalE;
										collision.collisionManifold.contactPosA = constraint0->collisionConstraint.contacts.contactPosA;
										collision.collisionManifold.contactPosB = constraint0->collisionConstraint.contacts.contactPosB;
									}
									for (unsigned i(0); i < 4; i++) {
										resolve_impulse(a, -constraint0->impulses[i], constraint0->collisionConstraint.contacts.contactPosA);
									}
								}
						}
					}
				}
			}
			bool isContinue(false);
			if (rigidBodies4D[constraints0[0]->index1]->isSleep)
			{
				if (constraints0[0]->index2 == -1 || constraints0[0]->index2 >= rigidBodies4D.size())
				{
					isContinue = rigidBodies4D[constraints0[0]->index1]->velocity4D == glm::vec4(0.f);
				}
				else
				{
					isContinue = rigidBodies4D[constraints0[0]->index2]->isSleep;
				}
			}
			if (!isContinue)
			{
				for (Constraint* c : (*constraintsVec0)[i])c = nullptr, free(c);
				constraintsVec0->erase(constraintsVec0->begin() + i);
				i--;
			}
		}

		//std::cout<<constraintsVec0->size()<<'\n';
		size_t constraintsVecSizeBefore(constraintsVec0->size());
		for (std::vector<Collision> collisions : *collisionsVec)
		{
			RigidBody4D* a(rigidBodies4D[collisions[0].index1]);
			if (collisions[0].index2 == -1)
			{
				get_constraint(a, collisions, constraintsVec0);
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
					else if(b->isFrozen)
					{
						get_constraint(a, collisions, constraintsVec0);
					}
					else
					{
						get_constraint(a, b, collisions, constraintsVec0);
					}
				}
				else
				{
					Wall4D* w(walls4D[collisions[0].index2 - rigidBodies4D.size()]);
					get_constraint(a, w, collisions, constraintsVec0);
				}
			}
		}
		size_t constraintsVecSizeAfter(constraintsVec0->size());

		bool isInverseResolve(true);
		for (size_t i(0); i < 64; i++)
		{
			isInverseResolve = !isInverseResolve;
			for (size_t j(constraintsVecSizeBefore);j < constraintsVecSizeAfter;j++)
			{
				std::vector<Constraint*> constraints;
				if (isInverseResolve)constraints = (*constraintsVec0)[constraintsVecSizeAfter - j - 1];
				else constraints = (*constraintsVec0)[j];
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
		}

		//for (std::vector<Constraint*> cs : *constraintsVec0)for (Constraint* c : cs)c = nullptr, free(c); constraintsVec0->clear();
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
			if (i->index2.isValid)
			{
				if (i->index2.n < rigidBodies4D.size())
				{
					RigidBody4D* b(rigidBodies4D[i->index2.n]);
					if (i->index1 < rigidBodies4D.size())
					{
						RigidBody4D* a(rigidBodies4D[i->index1]);
						if (!a->isSleep || !b->isSleep)
						{
							if (!a->is_static() && !b->is_static())
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
					}
					else
					{
						if (!b->isSleep)
						{
							Wall4D* c(walls4D[i->index1 - rigidBodies4D.size()]);
							i->solve_rigidbody_wall(b, c, dt);
						}
					}
				}
				if (i->index2.n >= rigidBodies4D.size())
				{
					if (i->index1 < rigidBodies4D.size())
					{
						RigidBody4D* a(rigidBodies4D[i->index1]);
						if (!a->isSleep)
						{
							Wall4D* d(walls4D[i->index2.n - rigidBodies4D.size()]);
							i->solve_rigidbody_wall(a, d, dt);
						}
					}
				}
			}
		}
		for (Spring4D* i : springs4D)
		{
			if (i->index2.isValid)
			{
				if (i->index2.n < rigidBodies4D.size())
				{
					RigidBody4D* b(rigidBodies4D[i->index2.n]);
					if (i->index1 < rigidBodies4D.size())
					{
						RigidBody4D* a(rigidBodies4D[i->index1]);
						if (!a->isSleep || !b->isSleep)
						{
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
					}
					else
					{
						if (!b->isSleep)
						{
							Wall4D* c(walls4D[i->index1 - rigidBodies4D.size()]);
							i->solve_rigidbody_wall(b, c, dt);
						}
					}
				}
				else
				{
					if (i->index1 < rigidBodies4D.size())
					{
						RigidBody4D* a(rigidBodies4D[i->index1]);
						if (!a->isSleep)
						{
							Wall4D* d(walls4D[i->index2.n - rigidBodies4D.size()]);
							i->solve_rigidbody_wall(a, d, dt);
						}
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
				if (a->massCenter == glm::vec4(0.f))
				{
					a->set_position4D(a->position4D + a->velocity4D * dt);
					a->set_rotation4D(update(a->rotation4D, a->angularVelocity4D * dt));

				}
				else
				{
					glm::vec4 bodyMassCenterToWorld(body_pos_to_world(a, a->massCenter));
					a->set_rotation4D(update(a->rotation4D, a->angularVelocity4D * dt));
					glm::vec4 bodyMassCenterToVec(body_vec_to_world(a, a->massCenter));
					a->set_position4D(bodyMassCenterToWorld - bodyMassCenterToVec + a->velocity4D * dt);
				}
			}
		}
	}

	static void update_stick4D(std::vector<RigidBody4D*> rigidBodies4D,
		vector<Wall4D*> walls4D,
		Stick4D* stick4D)
	{

		if (!stick4D->index2.isValid)
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
			if (stick4D->index2.n < rigidBodies4D.size())
			{
				if (stick4D->index1 < rigidBodies4D.size())
				{
					stick4D->update_stick4D(rigidBodies4D[stick4D->index1], rigidBodies4D[stick4D->index2.n]);
				}
				else
				{
					stick4D->update_stick4D(rigidBodies4D[stick4D->index2.n], walls4D[stick4D->index1 - rigidBodies4D.size()]);
				}
			}
			else
			{
				if (stick4D->index1 < rigidBodies4D.size())
				{
					stick4D->update_stick4D(walls4D[stick4D->index2.n - rigidBodies4D.size()], rigidBodies4D[stick4D->index1]);
				}
				else
				{
					stick4D->update_stick4D(walls4D[stick4D->index1 - rigidBodies4D.size()], walls4D[stick4D->index2.n - rigidBodies4D.size()]);
				}
			}
		}
	}
	static void update_spring4D(std::vector<RigidBody4D*> rigidBodies4D,
		vector<Wall4D*> walls4D,
		Spring4D* spring4D)
	{

		if (!spring4D->index2.isValid)
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
			if (spring4D->index2.n < rigidBodies4D.size())
			{
				if (spring4D->index1 < rigidBodies4D.size())
				{
					spring4D->update_spring4D(rigidBodies4D[spring4D->index1], rigidBodies4D[spring4D->index2.n]);
				}
				else
				{
					spring4D->update_spring4D(rigidBodies4D[spring4D->index2.n], walls4D[spring4D->index1 - rigidBodies4D.size()]);
				}
			}
			else
			{
				if (spring4D->index1 < rigidBodies4D.size())
				{
					spring4D->update_spring4D(walls4D[spring4D->index2.n - rigidBodies4D.size()], rigidBodies4D[spring4D->index1]);
				}
				else
				{
					spring4D->update_spring4D(walls4D[spring4D->index1 - rigidBodies4D.size()], walls4D[spring4D->index2.n - rigidBodies4D.size()]);
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
		wake_up_rigidBodies4D(rigidBodies4D);
		sleep_rigidBodies4D(rigidBodies4D, dt);
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
		for (Stick4D* i : sticks4D) { if (i->index2.isValid)update_stick4D(rigidBodies4D, walls4D,i); }
		for (Spring4D* i : springs4D) { if (i->index2.isValid)update_spring4D(rigidBodies4D, walls4D,i); }
		if (isTrail4D) { update_trails4D(rigidBodies4D, dt, curTime); }
	}
}