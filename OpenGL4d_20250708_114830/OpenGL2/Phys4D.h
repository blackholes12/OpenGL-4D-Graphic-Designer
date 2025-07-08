#pragma once

namespace phy {
	static float timeToSleep=0.f;
	static void sleep_rigidBodies4D(std::vector<RigidBody4D*> rigidBodies4d, const float dt)
	{
		for (size_t i(0); i < rigidBodies4d.size(); i++)
		{
			RigidBody4D* a(rigidBodies4d[i]);
			if (!a->isSleep)
			{
				if (length(a->velocity4d) > 0.1f || length(a->angularVelocity4D) > 0.8f || length(a->position4d - a->pPosition4D) > 0.05f)
				{
					a->isContinueSleep = false;
				}
			}
		}
		timeToSleep += dt;
		if (timeToSleep > 2.f)
		{
			for (size_t i(0); i < rigidBodies4d.size(); i++)
			{
				RigidBody4D* a(rigidBodies4d[i]);
				if (!a->isSleep)
				{
					a->pPosition4D = a->position4d;
					if (a->isContinueSleep&&!a->is_static())
					{
						a->isSleep = true;
						a->velocity4d = glm::vec4(0.f);
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
			if (length(a->velocity4d) > 0.1f || length(a->angularVelocity4D) > 0.8f || length(a->position4d - a->pPosition4D) > 0.05f)
			{
				a->isSleep = false;
				a->isContinueSleep = true;
			}
		}
	}

	static void wake_up_rigidBodies4D(std::vector<RigidBody4D*> rigidBodies4d)
	{
		for (size_t i(0); i < rigidBodies4d.size(); i++)
		{
			RigidBody4D* a(rigidBodies4d[i]);
			if (a->isSleep)
			{
				if (length(a->velocity4d) > 0.1f || length(a->angularVelocity4D) > 0.8f || a->forceSystems4D.size() > 0 || length(a->position4d - a->pPosition4D) > 0.05f)
				{
					a->isSleep = false;
					a->isContinueSleep = true;
				}
				a->velocity4d = glm::vec4(0.f);
				a->angularVelocity4D = alg::bivec4();
			}
		}
	}

	static void start_rigidBodies4D(std::vector<RigidBody4D*> rigidBodies4d, std::vector<std::vector<Collision>>* collisionsVec, const float dt)
	{
		/*
		for (size_t i(0); i < collisionsVec->size(); i++)
		{
			collisionsVec[i].clear();
		}
		collisionsVec->clear();
		for (size_t i(0); i < rigidBodies4d.size(); i++)
		{
			RigidBody4D* a(rigidBodies4d[i]);
			if (!a->is_static() && !a->isSleep)
			{
				if (a->isGravity)
				{
					a->forceSystems4D.push_back(new ForceSystem4D(glm::vec4(0, -9.80665f * a->mass, 0, 0), glm::vec4(0.f)));
				}
				update_rigidbody_velocity4D(a, dt);
			}
		}
		*/
		glm::vec4 dir_a_to_b;
		float dis;
		glm::vec4 dir_a_to_b_e;
		glm::vec4 force4D;
		for (size_t i(1); i < rigidBodies4d.size(); i++)
		{
			RigidBody4D* a(rigidBodies4d[i]);
			if (a->objectName == "Celestial4D")
			{
				for (size_t j(i + 1); j < rigidBodies4d.size(); j++)
				{
					RigidBody4D* b(rigidBodies4d[j]);
					if (b->objectName == "Celestial4D")
					{
						a->isSleep = false;
						b->isSleep = false;
						dir_a_to_b = b->position4d - a->position4d;
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

	static void caculate_rigidBodies4D(std::vector<RigidBody4D*> rigidBodies4d, std::vector<size_t> groupIndices, std::vector<Group*> groups, vector<Wall4D*> walls4d, std::vector<Terrain4D*> terrains4d, std::vector<Water4D*> waters4d, std::vector < std::vector < HingeConstraint4D*>> hingeConstraintsVec, std::vector<std::vector<Collision>>* collisionsVec, std::vector <std::vector<Constraint*>>* constraintsVec0, const float dt)
	{
		for (size_t i(0); i < rigidBodies4d.size(); i++)
		{
			RigidBody4D* a(rigidBodies4d[i]);
			if (!a->isBeyond)
			{
				size_t collisionSizeBefore(collisionsVec->size());
				/*
				for (size_t k(0); k < a->rigidBodyIndices.size(); k++)
				{
					size_t j(a->rigidBodyIndices[k]);
					RigidBody4D* b(rigidBodies4d[j]);
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
								if (a->velocity4d != glm::vec4(0.f) || !a->isSleep)
									*collisionsVec = detect_rigidbody_or_wall(i, j, a, b, *collisionsVec);
							}
						}
						else
						{
							if (!b->isFrozen)
							{
								if (b->velocity4d != glm::vec4(0.f) || !b->isSleep)
									*collisionsVec = detect_rigidbody_or_wall(j, i, b, a, *collisionsVec);
							}
						}
					}
				}
				*/
				if (!a->isFrozen)
				{
					if (a->velocity4d != glm::vec4(0.f) || !a->isSleep)
					{
						for (size_t groupIndex : groupIndices)
						{
							Group* j(groups[groupIndex]);
							for (size_t terrainIndex : j->terrains4DIndices) {
								Terrain4D* k(terrains4d[terrainIndex]);
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
									Wall4D* w = walls4d[j];
									if (w->colType != NONE)
									{
										if (w->objectName == "Billiard")
										{
											update_billiards(a, w);
										}
									}
								}
							}
							//*collisionsVec = detect_rigidbody_or_wall(i, rigidBodies4d.size() + j, a, walls4d[j], *collisionsVec);
						}
					}
				}
				//if (!a->isFrozen && (a->velocity4d != glm::vec4(0.f) || !a->isSleep))
				//{
				//	*collisionsVec = detect_rigidbody_edge(i, a, *collisionsVec);
				//}
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

		//for (size_t j(0); j < collisionsVec->size(); j++)
		//{
		//	std::vector<Collision> collisions((*collisionsVec)[j]);
		//	float maxDepth(0.f);
		//	for (size_t i(0); i < collisions.size(); i++)
		//	{
		//		if (maxDepth < collisions[i].collisionManifold.depth && collisions[i].collisionManifold.depth > 0.005f)
		//		{
		//			maxDepth = collisions[i].collisionManifold.depth;
		//		}
		//	}
		//	float shiftDepth = maxDepth - 0.005f;
		//	RigidBody4D* a(rigidBodies4d[collisions[0].index1]);
		//	if (collisions[0].index2 < rigidBodies4d.size() && collisions[0].index2 != -1)
		//	{
		//		RigidBody4D* b(rigidBodies4d[collisions[0].index2]);
		//		a->set_position4D(a->position4d - b->mass * collisions[0].collisionManifold.normal * shiftDepth / (a->mass + b->mass));
		//		b->set_position4D(b->position4d + a->mass * collisions[0].collisionManifold.normal * shiftDepth / (a->mass + b->mass));
		//	}
		//	else
		//	{
		//		a->set_position4D(a->position4d - collisions[0].collisionManifold.normal * shiftDepth);
		//	}
		//}

		for (std::vector < HingeConstraint4D*> hs : hingeConstraintsVec)
		{
			if (!hs[0]->index2.isValid)
			{
				if (hs[0]->index1 < rigidBodies4d.size())
				{
					RigidBody4D* a(rigidBodies4d[hs[0]->index1]);
					if (!a->isSleep && !a->is_static())*collisionsVec = hinge_to_hinge(hs, a, a, *collisionsVec,false);
				}
			}
			else
			{
				if (hs[0]->index2.n < rigidBodies4d.size())
				{
					RigidBody4D* b(rigidBodies4d[hs[0]->index2.n]);
					if (hs[0]->index1 < rigidBodies4d.size())
					{
						RigidBody4D* a(rigidBodies4d[hs[0]->index1]);
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
						Object4D* a(find_object4d(rigidBodies4d, walls4d, hs[0]->index1));
						if (!b->isSleep&& !b->is_static())*collisionsVec = hinge_to_hinge(hs, a, b, *collisionsVec, true);
					}
				}
				else
				{
					Object4D* b(find_object4d(rigidBodies4d, walls4d, hs[0]->index2.n));
					if (hs[0]->index1 < rigidBodies4d.size())
					{
						RigidBody4D* a(rigidBodies4d[hs[0]->index1]);
						if (!a->isSleep&&!a->is_static())*collisionsVec = hinge_to_hinge(hs, a, b, *collisionsVec, false);
					}
				}
			}
		}

		//for (std::vector<Collision> &collisions : *collisionsVec)
		//{
		//	RigidBody4D* a0(rigidBodies4d[collisions[0].index1]);
		//	bool isDoubleRigidBodies(collisions[0].index2 != -1 && collisions[0].index2 < rigidBodies4d.size());
		//	if (collisions.size() == 1)
		//	{
		//		glm::vec4 contactPosA(collisions[0].collisionManifold.contactPosA);
		//		for (Collision &collision : collisions)collision.collisionManifold.balancePosA = contactPosA, collision.collisionManifold.angularVelocity4DA = wedge_v(alg::vec4(contactPosA), rotate(a0->rotation4D.reverse(), alg::vec4(collisions[0].collisionManifold.normal)));
		//		if (isDoubleRigidBodies) {
		//			RigidBody4D* b0(rigidBodies4d[collisions[0].index2]);
		//			glm::vec4 contactPosB(collisions[0].collisionManifold.contactPosB);
		//			for (Collision& collision : collisions)collision.collisionManifold.balancePosB = contactPosB, collision.collisionManifold.angularVelocity4DB = wedge_v(alg::vec4(contactPosB), rotate(b0->rotation4D.reverse(), alg::vec4(collisions[0].collisionManifold.normal)));
		//		}
		//	}
		//	else if (collisions.size() == 2)
		//	{
		//		{
		//		glm::vec4 a(collisions[0].collisionManifold.contactPosA);
		//		glm::vec4 b(collisions[1].collisionManifold.contactPosA);
		//		glm::vec4 ab(alg::normalize(b - a));
		//		float lambda(alg::dot(-a, ab));
		//		glm::vec4 contactPosA = a + lambda * ab;
		//		for (Collision& collision : collisions)collision.collisionManifold.balancePosA = contactPosA, collision.collisionManifold.angularVelocity4DA = wedge_v(alg::vec4(contactPosA), rotate(a0->rotation4D.reverse(), alg::vec4(collisions[0].collisionManifold.normal)));
		//     	}
		//		if (isDoubleRigidBodies) {
		//			RigidBody4D* b0(rigidBodies4d[collisions[0].index2]);
		//			glm::vec4 a(collisions[0].collisionManifold.contactPosB);
		//			glm::vec4 b(collisions[1].collisionManifold.contactPosB);
		//			glm::vec4 ab(alg::normalize(b - a));
		//			float lambda(alg::dot(-a, ab));
		//			glm::vec4 contactPosB = a + lambda * ab;
		//			for (Collision& collision : collisions)collision.collisionManifold.balancePosB = contactPosB, collision.collisionManifold.angularVelocity4DB = wedge_v(alg::vec4(collision.collisionManifold.balancePosB = contactPosB), rotate(b0->rotation4D.reverse(), alg::vec4(collisions[0].collisionManifold.normal)));
		//		}
		//	}
		//	else if (collisions.size() > 2)
		//	{
		//		{
		//			glm::vec4 contactPosA(glm::vec4(0.f));
		//			glm::ivec3 contactPosAIndices(glm::ivec3(0));
		//			glm::vec3 contactPosADistances(glm::vec3(0.f));
		//			for (size_t j(0); j < collisions.size(); j++)
		//			{
		//				glm::vec4 relVel;
		//				if (isDoubleRigidBodies)relVel = vel_at(rigidBodies4d[collisions[0].index2], world_pos_to_body(rigidBodies4d[collisions[0].index2], body_pos_to_world(a0, collisions[j].collisionManifold.contactPosA))) - vel_at(a0, collisions[j].collisionManifold.contactPosA);
		//				else relVel = -vel_at(a0, collisions[j].collisionManifold.contactPosA);
		//				float contactVelocity(alg::dot(-relVel, collisions[j].collisionManifold.normal));
		//				if (contactPosADistances[0] < contactVelocity)
		//				{
		//					contactPosAIndices[0] = j;
		//					contactPosADistances[0] = contactVelocity;
		//				}
		//			}
		//			for (size_t j(0); j < collisions.size(); j++)
		//			{
		//				if (j != contactPosAIndices[0])
		//				{
		//					glm::vec4 a(collisions[contactPosAIndices[0]].collisionManifold.contactPosA);
		//					glm::vec4 b(collisions[j].collisionManifold.contactPosA);
		//					glm::vec4 ab(alg::normalize(b - a));
		//					float lambda(alg::dot(-a, ab));
		//					glm::vec4 contactPosA0(a + lambda * ab);
		//					glm::vec4 relVel;
		//					if (isDoubleRigidBodies)relVel = vel_at(rigidBodies4d[collisions[0].index2], world_pos_to_body(rigidBodies4d[collisions[0].index2], body_pos_to_world(a0, contactPosA0))) - vel_at(a0, contactPosA0);
		//					else relVel = -vel_at(a0, contactPosA0);
		//					float contactVelocity(alg::dot(-relVel, collisions[j].collisionManifold.normal));
		//					if (contactPosADistances[1] < contactVelocity)
		//					{
		//						contactPosAIndices[1] = j;
		//						contactPosADistances[1] = contactVelocity;
		//					}
		//				}
		//			}
		//			for (size_t j(0); j < collisions.size(); j++)
		//			{
		//				if (j != contactPosAIndices[0] && j != contactPosAIndices[1])
		//				{
		//					glm::vec4 a(collisions[contactPosAIndices[0]].collisionManifold.contactPosA);
		//					glm::vec4 b(collisions[contactPosAIndices[1]].collisionManifold.contactPosA);
		//					glm::vec4 c(collisions[j].collisionManifold.contactPosA);
		//					glm::vec4 veAB(alg::normalize(b - a));
		//					glm::vec4 vAC(c - a);
		//					glm::vec4 neAB(alg::normalize(vAC - veAB * alg::dot(vAC, veAB)));
		//					float kv(alg::dot(-a, veAB));
		//					float kn(alg::dot(-a, neAB));
		//					glm::vec4 contactPosA0(a + kv * veAB + kn * neAB);
		//					glm::vec4 relVel;
		//					if (isDoubleRigidBodies)relVel = vel_at(rigidBodies4d[collisions[0].index2], world_pos_to_body(rigidBodies4d[collisions[0].index2], body_pos_to_world(a0, contactPosA0))) - vel_at(a0, contactPosA0);
		//					else relVel = -vel_at(a0, contactPosA0);
		//					float contactVelocity(alg::dot(-relVel, collisions[j].collisionManifold.normal));
		//					if (contactPosADistances[2] < contactVelocity)
		//					{
		//						contactPosAIndices[2] = j;
		//						contactPosADistances[2] = contactVelocity;
		//						contactPosA = contactPosA0;
		//					}
		//				}
		//			}
		//			glm::vec4 vAB(collisions[contactPosAIndices[1]].collisionManifold.contactPosA - collisions[contactPosAIndices[0]].collisionManifold.contactPosA);
		//			glm::vec4 vAC(collisions[contactPosAIndices[2]].collisionManifold.contactPosA - collisions[contactPosAIndices[0]].collisionManifold.contactPosA);
		//			alg::bivec4 AVA(wedge_v(alg::vec4(vAC), alg::vec4(vAB)));
		//			for (Collision& collision : collisions)collision.collisionManifold.balancePosA = contactPosA, collision.collisionManifold.angularVelocity4DA = alg::bivec4(AVA.zw, AVA.xy, AVA.xz, AVA.xw, AVA.yz, AVA.yw);
		//		}
		//		if (isDoubleRigidBodies) {
		//			RigidBody4D* b0(rigidBodies4d[collisions[0].index2]);
		//			glm::vec4 contactPosB(glm::vec4(0.f));
		//			glm::ivec3 contactPosBIndices(glm::ivec3(0));
		//			glm::vec3 contactPosBDistances(glm::vec3(0.f));
		//			for (size_t j(0); j < collisions.size(); j++)
		//			{
		//				glm::vec4 relVel;
		//				if (isDoubleRigidBodies)relVel = vel_at(b0, collisions[j].collisionManifold.contactPosB) - vel_at(a0, world_pos_to_body(a0, body_pos_to_world(b0, collisions[j].collisionManifold.contactPosB)));
		//				else relVel = vel_at(b0, collisions[j].collisionManifold.contactPosB);
		//				float contactVelocity(alg::dot(-relVel, collisions[j].collisionManifold.normal));
		//				if (contactPosBDistances[0] < contactVelocity)
		//				{
		//					contactPosBIndices[0] = j;
		//					contactPosBDistances[0] = contactVelocity;
		//				}
		//			}
		//			for (size_t j(0); j < collisions.size(); j++)
		//			{
		//				if (j != contactPosBIndices[0])
		//				{
		//					glm::vec4 a(collisions[contactPosBIndices[0]].collisionManifold.contactPosB);
		//					glm::vec4 b(collisions[j].collisionManifold.contactPosB);
		//					glm::vec4 ab(alg::normalize(b - a));
		//					float lambda(alg::dot(-a, ab));
		//					glm::vec4 contactPosB0(a + lambda * ab);
		//					glm::vec4 relVel;
		//					if (isDoubleRigidBodies)relVel = vel_at(b0, contactPosB0) - vel_at(a0, world_pos_to_body(a0, body_pos_to_world(b0, contactPosB0)));
		//					else relVel = vel_at(b0, contactPosB0);
		//					float contactVelocity(alg::dot(-relVel, collisions[j].collisionManifold.normal));
		//					if (contactPosBDistances[1] < contactVelocity)
		//					{
		//						contactPosBIndices[1] = j;
		//						contactPosBDistances[1] = contactVelocity;
		//					}
		//				}
		//			}
		//			for (size_t j(0); j < collisions.size(); j++)
		//			{
		//				if (j != contactPosBIndices[0] && j != contactPosBIndices[1])
		//				{
		//					glm::vec4 a(collisions[contactPosBIndices[0]].collisionManifold.contactPosB);
		//					glm::vec4 b(collisions[contactPosBIndices[1]].collisionManifold.contactPosB);
		//					glm::vec4 c(collisions[j].collisionManifold.contactPosB);
		//					glm::vec4 veAB(alg::normalize(b - a));
		//					glm::vec4 vAC(c - a);
		//					glm::vec4 neAB(alg::normalize(vAC - veAB * alg::dot(vAC, veAB)));
		//					float kv(alg::dot(-a, veAB));
		//					float kn(alg::dot(-a, neAB));
		//					glm::vec4 contactPosB0(a + kv * veAB + kn * neAB);
		//					glm::vec4 relVel;
		//					if (isDoubleRigidBodies)relVel = vel_at(b0, contactPosB0) - vel_at(a0, world_pos_to_body(a0, body_pos_to_world(b0, contactPosB0)));
		//					else relVel = vel_at(b0, contactPosB0);
		//					float contactVelocity(alg::dot(-relVel, collisions[j].collisionManifold.normal));
		//					if (contactPosBDistances[2] < contactVelocity)
		//					{
		//						contactPosBIndices[2] = j;
		//						contactPosBDistances[2] = contactVelocity;
		//						contactPosB = contactPosB0;
		//					}
		//				}
		//			}
		//			glm::vec4 vAB(collisions[contactPosBIndices[1]].collisionManifold.contactPosB - collisions[contactPosBIndices[0]].collisionManifold.contactPosB);
		//			glm::vec4 vAC(collisions[contactPosBIndices[2]].collisionManifold.contactPosB - collisions[contactPosBIndices[0]].collisionManifold.contactPosB);
		//			alg::bivec4 AVA(wedge_v(alg::vec4(vAC), alg::vec4(vAB)));
		//			for (Collision& collision : collisions)collision.collisionManifold.balancePosB = contactPosB, collision.collisionManifold.angularVelocity4DB = alg::bivec4(AVA.zw, AVA.xy, AVA.xz, AVA.xw, AVA.yz, AVA.yw);
		//		}
		//	}
		//}

		//for (size_t i(0); i < rigidBodies4d.size(); i++)
		//{
		//	RigidBody4D* a0(rigidBodies4d[i]);
		//	std::vector<glm::vec4> contactPoss;
		//	std::vector<glm::vec4> contactNormals;
		//	std::vector<glm::ivec2> contactIndices;
		//	glm::vec4 normal4D = glm::vec4();
		//	for (std::vector<Collision> collisions : *collisionsVec)
		//	{
		//		if (collisions[0].index1 == i || collisions[0].index2 == i)
		//		{
		//			normal4D = collisions[0].collisionManifold.normal;
		//			for (Collision collision : collisions)
		//			{
		//				if (collisions[0].index1 == i)
		//				{
		//					contactPoss.push_back(collision.collisionManifold.contactPosA);
		//					contactNormals.push_back(collision.collisionManifold.normal);
		//					if (collisions[0].index2 != -1 && collisions[0].index2 < rigidBodies4d.size())
		//					{
		//						contactIndices.push_back(glm::ivec2(collisions[0].index1, collisions[0].index2));
		//					}
		//					else
		//					{
		//						contactIndices.push_back(glm::ivec2(collisions[0].index1, -1));
		//					}
		//				}
		//				else
		//				{
		//					contactPoss.push_back(collision.collisionManifold.contactPosB);
		//					contactNormals.push_back(collision.collisionManifold.normal);
		//					contactIndices.push_back(glm::ivec2(collisions[0].index1, -2));
		//				}
		//			}
		//		}
		//	}
		//	//std::cout << contactPoss.size() << "," << relVels.size() << '\n';
		//	if (contactPoss.size() > 0)
		//	{
		//		glm::vec4 contactPos(contactPoss[0]);
		//		if (contactPoss.size() == 1)
		//		{
		//			a0->momentInertiaScalar = get_moment_inertia_scalar(a0, contactPos, wedge_v(alg::vec4(contactPos), rotate(a0->rotation4D.reverse(), alg::vec4(normal4D))), a0->angularVelocity4D);
		//		}
		//		if (contactPoss.size() == 2)
		//		{
		//			glm::vec4 a(contactPoss[0]);
		//			glm::vec4 b(contactPoss[1]);
		//			glm::vec4 ab(alg::normalize(b - a));
		//			float lambda(alg::dot(-a, ab));
		//			contactPos = a + lambda * ab;
		//			a0->momentInertiaScalar = get_moment_inertia_scalar(a0, contactPos, wedge_v(alg::vec4(contactPos), rotate(a0->rotation4D.reverse(), alg::vec4(normal4D))), a0->angularVelocity4D);
		//		}
		//		else if (contactPoss.size() > 2)
		//		{
		//			glm::ivec3 contactPosIndices(glm::ivec3(0));
		//			glm::vec3 contactPosDistances(glm::vec3(0.f));
		//			for (size_t j(0); j < contactPoss.size(); j++)
		//			{
		//				glm::vec4 relVel;
		//				if (contactIndices[j][1] == -1)
		//				{
		//					relVel = -vel_at(a0, contactPoss[j]);
		//				}
		//				else if (contactIndices[j][1] == -2)
		//				{
		//					RigidBody4D* b0(rigidBodies4d[contactIndices[j][0]]);
		//					relVel = vel_at(a0, contactPoss[j]) - vel_at(b0, world_pos_to_body(b0, body_pos_to_world(a0, contactPoss[j])));
		//				}
		//				else
		//				{
		//					RigidBody4D* b0(rigidBodies4d[contactIndices[j][1]]);
		//					relVel = vel_at(b0, world_pos_to_body(b0, body_pos_to_world(a0, contactPoss[j]))) - vel_at(a0, contactPoss[j]);
		//				}
		//				float lengthOfRelVel(alg::dot(-relVel, contactNormals[j]));
		//				if (contactPosDistances[0] < lengthOfRelVel / 60.f + alg::length(contactPoss[j]) / 2400.f)
		//				{
		//					contactPosIndices[0] = j;
		//					contactPosDistances[0] = lengthOfRelVel / 60.f + alg::length(contactPoss[j]) / 2400.f;
		//				}
		//			}
		//			for (size_t j(0); j < contactPoss.size(); j++)
		//			{
		//				if (j != contactPosIndices[0])
		//				{
		//					glm::vec4 a(contactPoss[contactPosIndices[0]]);
		//					glm::vec4 b(contactPoss[j]);
		//					glm::vec4 ab(alg::normalize(b - a));
		//					float lambda(alg::dot(-a, ab));
		//					glm::vec4 contactPos0(a + lambda * ab);
		//					glm::vec4 relVel;
		//					if (contactIndices[j][1] == -1)
		//					{
		//						relVel = -vel_at(a0, contactPos0);
		//					}
		//					else if (contactIndices[j][1] == -2)
		//					{
		//						RigidBody4D* b0(rigidBodies4d[contactIndices[j][0]]);
		//						relVel = vel_at(a0, contactPos0) - vel_at(b0, world_pos_to_body(b0, body_pos_to_world(a0, contactPos0)));
		//					}
		//					else
		//					{
		//						RigidBody4D* b0(rigidBodies4d[contactIndices[j][1]]);
		//						relVel = vel_at(b0, world_pos_to_body(b0, body_pos_to_world(a0, contactPos0))) - vel_at(a0, contactPos0);
		//					}
		//					float lengthOfRelVel(alg::dot(-relVel, contactNormals[j]));
		//					if (contactPosDistances[1] < lengthOfRelVel / 60.f + alg::length(contactPos0) / 2400.f)
		//					{
		//						contactPosIndices[1] = j;
		//						contactPosDistances[1] = lengthOfRelVel / 60.f + alg::length(contactPos0) / 2400.f;
		//					}
		//				}
		//			}
		//			for (size_t j(0); j < contactPoss.size(); j++)
		//			{
		//				if (j != contactPosIndices[0] && j != contactPosIndices[1])
		//				{
		//					glm::vec4 a(contactPoss[contactPosIndices[0]]);
		//					glm::vec4 b(contactPoss[contactPosIndices[1]]);
		//					glm::vec4 c(contactPoss[j]);
		//					glm::vec4 veAB(alg::normalize(b - a));
		//					glm::vec4 vAC(c - a);
		//					glm::vec4 neAB(alg::normalize(vAC - veAB * alg::dot(vAC, veAB)));
		//					float kv(alg::dot(-a, veAB));
		//					float kn(alg::dot(-a, neAB));
		//					glm::vec4 contactPos0(a + kv * veAB + kn * neAB);
		//					glm::vec4 relVel;
		//					if (contactIndices[j][1] == -1)
		//					{
		//						relVel = -vel_at(a0, contactPos0);
		//					}
		//					else if (contactIndices[j][1] == -2)
		//					{
		//						RigidBody4D* b0(rigidBodies4d[contactIndices[j][0]]);
		//						relVel = vel_at(a0, contactPos0) - vel_at(b0, world_pos_to_body(b0, body_pos_to_world(a0, contactPos0)));
		//					}
		//					else
		//					{
		//						RigidBody4D* b0(rigidBodies4d[contactIndices[j][1]]);
		//						relVel = vel_at(b0, world_pos_to_body(b0, body_pos_to_world(a0, contactPos0))) - vel_at(a0, contactPos0);
		//					}
		//					float lengthOfRelVel(alg::dot(-relVel, contactNormals[j]));
		//					if (contactPosDistances[2] < lengthOfRelVel / 60.f + alg::length(contactPos0) / 2400.f)
		//					{
		//						contactPosIndices[2] = j;
		//						contactPosDistances[2] = lengthOfRelVel / 60.f + alg::length(contactPos0) / 2400.f;
		//						contactPos = contactPos0;
		//					}
		//				}
		//			}
		//			alg::bivec4 AVA(wedge_v(alg::vec4(contactPoss[contactPosIndices[0]] - contactPoss[contactPosIndices[1]]), alg::vec4(contactPoss[contactPosIndices[0]] - contactPoss[contactPosIndices[2]])));
		//			a0->momentInertiaScalar = get_moment_inertia_scalar(a0, contactPos, alg::bivec4(AVA.zw, AVA.xy, AVA.xz, AVA.xw, AVA.yz, AVA.yw), a0->angularVelocity4D);
		//		}
		//	}
		//}
		//std::cout << "step2" << '\n';
		for (size_t i(0); i < constraintsVec0->size(); i++) 
		{
			std::vector<Constraint*> constraints0((*constraintsVec0)[i]);
		    for (std::vector<Collision>& collisions : *collisionsVec)
		    {
				if (collisions[0].index1 == constraints0[0]->index1 && collisions[0].index2 == constraints0[0]->index2)
				{
					//if(collisions.size() == constraints0.size())
					//{ }
					RigidBody4D* a = rigidBodies4d[constraints0[0]->index1];
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
									if (contactPosAToWorld != contactPosBToWorld)
									{
										glm::vec4 normal2(contactPosAToWorld - contactPosBToWorld);
										glm::vec4 normalE(alg::normalize(normal2));
										collision.collisionManifold.depth = alg::length(normal2);
										collision.collisionManifold.normal = normalE;
									}
									collision.collisionManifold.contactPosA = constraint0->collisionConstraint.contacts.contactPosA;
									collision.collisionManifold.contactPosB = constraint0->collisionConstraint.contacts.contactPosB;
								}
								resolve_impulse(a, -constraint0->impulses[0] - constraint0->impulses[1] - constraint0->impulses[2] - constraint0->impulses[3], constraint0->collisionConstraint.contacts.contactPosA, constraint0->momentInertiaScalarA);
							}
					}
					else
					{
						if (constraints0[0]->index2 < rigidBodies4d.size())
						{
							for (Collision& collision : collisions)for (Constraint* constraint0 : constraints0)
								if (length(collision.collisionManifold.contactPosA - constraint0->collisionConstraint.contacts.contactPosA) < 0.1f &&
									length(collision.collisionManifold.contactPosB - constraint0->collisionConstraint.contacts.contactPosB) < 0.1f)
								{
									RigidBody4D* b = rigidBodies4d[constraint0->index2];
									if (collision.type == 1)
									if (constraint0->impulseMagAdd < constraint0->maxImpulseAdd)
									{
										glm::vec4 contactPosAToWorld(body_pos_to_world(a, constraint0->collisionConstraint.contacts.contactPosA));
										glm::vec4 contactPosBToWorld(body_pos_to_world(b, constraint0->collisionConstraint.contacts.contactPosB));
										if (contactPosAToWorld != contactPosBToWorld)
										{
											glm::vec4 normal2(contactPosAToWorld - contactPosBToWorld);
											glm::vec4 normalE(alg::normalize(normal2));
											collision.collisionManifold.depth = alg::length(normal2);
											collision.collisionManifold.normal = normalE;
										}
										collision.collisionManifold.contactPosA = constraint0->collisionConstraint.contacts.contactPosA;
										collision.collisionManifold.contactPosB = constraint0->collisionConstraint.contacts.contactPosB;
									}
									resolve_impulse(a, -constraint0->impulses[0] - constraint0->impulses[1] - constraint0->impulses[2] - constraint0->impulses[3], constraint0->collisionConstraint.contacts.contactPosA, constraint0->momentInertiaScalarA);
									resolve_impulse(b, constraint0->impulses[0] + constraint0->impulses[1] + constraint0->impulses[2] + constraint0->impulses[3], constraint0->collisionConstraint.contacts.contactPosB, constraint0->momentInertiaScalarB);
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
										Wall4D* b(walls4d[constraint0->index2 - rigidBodies4d.size()]);
										glm::vec4 contactPosAToWorld(body_pos_to_world(a, constraint0->collisionConstraint.contacts.contactPosA));
										glm::vec4 contactPosBToWorld(body_pos_to_world(b, constraint0->collisionConstraint.contacts.contactPosB));
										if (contactPosAToWorld != contactPosBToWorld)
										{
											glm::vec4 normal2(contactPosAToWorld - contactPosBToWorld);
											glm::vec4 normalE(alg::normalize(normal2));
											collision.collisionManifold.depth = alg::length(normal2);
											collision.collisionManifold.normal = normalE;
										}
										collision.collisionManifold.contactPosA = constraint0->collisionConstraint.contacts.contactPosA;
										collision.collisionManifold.contactPosB = constraint0->collisionConstraint.contacts.contactPosB;
									}
									resolve_impulse(a, -constraint0->impulses[0]-constraint0->impulses[1]-constraint0->impulses[2]-constraint0->impulses[3], constraint0->collisionConstraint.contacts.contactPosA, constraint0->momentInertiaScalarA);
								}
						}
					}
				}
			}
			bool isContinue(false);
			if (rigidBodies4d[constraints0[0]->index1]->isSleep)
			{
				if (constraints0[0]->index2 == -1 || constraints0[0]->index2 >= rigidBodies4d.size())
				{
					isContinue = rigidBodies4d[constraints0[0]->index1]->velocity4d == glm::vec4(0.f);
				}
				else
				{
					isContinue = rigidBodies4d[constraints0[0]->index2]->isSleep;
				}
			}
			if (!isContinue)
			{
				for (Constraint* c : (*constraintsVec0)[i])c = nullptr, free(c);
				(*constraintsVec0)[i].clear();
				constraintsVec0->erase(constraintsVec0->begin() + i);
				i--;
			}
		}

		//std::cout<<constraintsVec0->size()<<'\n';
		size_t constraintsVecSizeBefore(constraintsVec0->size());
		for (std::vector<Collision> collisions : *collisionsVec)
		{
			RigidBody4D* a(rigidBodies4d[collisions[0].index1]);
			if (collisions[0].index2 == -1)
			{
				get_constraint(a, collisions, constraintsVec0);
			}
			else
			{
				if (collisions[0].index2 < rigidBodies4d.size())
				{
					RigidBody4D* b(rigidBodies4d[collisions[0].index2]);
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
					Wall4D* w(walls4d[collisions[0].index2 - rigidBodies4d.size()]);
					get_constraint(a, w, collisions, constraintsVec0);
				}
			}
		}
		size_t constraintsVecSizeAfter(constraintsVec0->size());

		bool isInverseResolve(true);
		for (size_t i(0); i < 20; i++)
		{
			isInverseResolve = !isInverseResolve;
			for (size_t j(constraintsVecSizeBefore);j < constraintsVecSizeAfter;j++)
			{
				std::vector<Constraint*> constraints;
				if (isInverseResolve)constraints = (*constraintsVec0)[constraintsVecSizeAfter - j - 1];
				else constraints = (*constraintsVec0)[j];
				RigidBody4D* a(rigidBodies4d[constraints[0]->index1]);
				if (constraints[0]->index2 == -1)
				{
					solve_rigidbody_edge(a, &constraints, isInverseResolve);
				}
				else
				{
					if (constraints[0]->index2 < rigidBodies4d.size())
					{
						RigidBody4D* b(rigidBodies4d[constraints[0]->index2]);
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
						Object4D* w(walls4d[constraints[0]->index2 - rigidBodies4d.size()]);
						solve_rigidbody_wall(a, w, &constraints, isInverseResolve);
					}
				}
			}
		}

		//for (std::vector<Constraint*> cs : *constraintsVec0)for (Constraint* c : cs)c = nullptr, free(c); constraintsVec0->clear();
	}

	static void caculate_joints4D(std::vector<RigidBody4D*> rigidBodies4d,
		std::vector<Group*> groups,
		vector<Wall4D*> walls4d,
		std::vector < Stick4D*> sticks4d,
		std::vector < Spring4D*> springs4d,
		const float dt)
	{
		for (Stick4D* i : sticks4d)
		{
			if (i->index2.isValid)
			{
				if (i->index2.n < rigidBodies4d.size())
				{
					RigidBody4D* b(rigidBodies4d[i->index2.n]);
					if (i->index1 < rigidBodies4d.size())
					{
						RigidBody4D* a(rigidBodies4d[i->index1]);
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
							Wall4D* c(walls4d[i->index1 - rigidBodies4d.size()]);
							i->solve_rigidbody_wall(b, c, dt);
						}
					}
				}
				if (i->index2.n >= rigidBodies4d.size())
				{
					if (i->index1 < rigidBodies4d.size())
					{
						RigidBody4D* a(rigidBodies4d[i->index1]);
						if (!a->isSleep)
						{
							Wall4D* d(walls4d[i->index2.n - rigidBodies4d.size()]);
							i->solve_rigidbody_wall(a, d, dt);
						}
					}
				}
			}
		}
		for (Spring4D* i : springs4d)
		{
			if (i->index2.isValid)
			{
				if (i->index2.n < rigidBodies4d.size())
				{
					RigidBody4D* b(rigidBodies4d[i->index2.n]);
					if (i->index1 < rigidBodies4d.size())
					{
						RigidBody4D* a(rigidBodies4d[i->index1]);
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
							Wall4D* c(walls4d[i->index1 - rigidBodies4d.size()]);
							i->solve_rigidbody_wall(b, c, dt);
						}
					}
				}
				else
				{
					if (i->index1 < rigidBodies4d.size())
					{
						RigidBody4D* a(rigidBodies4d[i->index1]);
						if (!a->isSleep)
						{
							Wall4D* d(walls4d[i->index2.n - rigidBodies4d.size()]);
							i->solve_rigidbody_wall(a, d, dt);
						}
					}
				}
			}
		}
	}

	static void solve_rigidBodies_position4D(std::vector<RigidBody4D*> rigidBodies4d, vector<Wall4D*> walls4d, std::vector<std::vector<Collision>>* collisionsVec, const float dt)
	{
		for (size_t i(0); i < rigidBodies4d.size(); i++)
		{
			RigidBody4D* a(rigidBodies4d[i]);
			if (!a->is_static()&&!a->isSleep)
			{
				if (a->massCenter == glm::vec4(0.f))
				{
					a->set_position4D(a->position4d + a->velocity4d * dt);
					a->set_rotation4D(update(a->rotation4D, a->angularVelocity4D * dt));

				}
				else
				{
					glm::vec4 bodyMassCenterToWorld(body_pos_to_world(a, a->massCenter));
					a->set_rotation4D(update(a->rotation4D, a->angularVelocity4D * dt));
					glm::vec4 bodyMassCenterToVec(body_vec_to_world(a, a->massCenter));
					a->set_position4D(bodyMassCenterToWorld - bodyMassCenterToVec + a->velocity4d * dt);
				}
			}
		}
	}

	static void update_stick4D(std::vector<RigidBody4D*> rigidBodies4d,
		vector<Wall4D*> walls4d,
		Stick4D* stick4D)
	{

		if (!stick4D->index2.isValid)
		{
			if (stick4D->index1 < rigidBodies4d.size())
			{
				stick4D->update_stick4D(rigidBodies4d[stick4D->index1]);
			}
			else
			{
				stick4D->update_stick4D(walls4d[stick4D->index1 - rigidBodies4d.size()]);
			}
		}
		else
		{
			if (stick4D->index2.n < rigidBodies4d.size())
			{
				if (stick4D->index1 < rigidBodies4d.size())
				{
					stick4D->update_stick4D(rigidBodies4d[stick4D->index1], rigidBodies4d[stick4D->index2.n]);
				}
				else
				{
					stick4D->update_stick4D(rigidBodies4d[stick4D->index2.n], walls4d[stick4D->index1 - rigidBodies4d.size()]);
				}
			}
			else
			{
				if (stick4D->index1 < rigidBodies4d.size())
				{
					stick4D->update_stick4D(walls4d[stick4D->index2.n - rigidBodies4d.size()], rigidBodies4d[stick4D->index1]);
				}
				else
				{
					stick4D->update_stick4D(walls4d[stick4D->index1 - rigidBodies4d.size()], walls4d[stick4D->index2.n - rigidBodies4d.size()]);
				}
			}
		}
	}
	static void update_spring4D(std::vector<RigidBody4D*> rigidBodies4d,
		vector<Wall4D*> walls4d,
		Spring4D* spring4D)
	{

		if (!spring4D->index2.isValid)
		{
			if (spring4D->index1 < rigidBodies4d.size())
			{
				spring4D->update_spring4D(rigidBodies4d[spring4D->index1]);
			}
			else
			{
				spring4D->update_spring4D(walls4d[spring4D->index1 - rigidBodies4d.size()]);
			}
		}
		else
		{
			if (spring4D->index2.n < rigidBodies4d.size())
			{
				if (spring4D->index1 < rigidBodies4d.size())
				{
					spring4D->update_spring4D(rigidBodies4d[spring4D->index1], rigidBodies4d[spring4D->index2.n]);
				}
				else
				{
					spring4D->update_spring4D(rigidBodies4d[spring4D->index2.n], walls4d[spring4D->index1 - rigidBodies4d.size()]);
				}
			}
			else
			{
				if (spring4D->index1 < rigidBodies4d.size())
				{
					spring4D->update_spring4D(walls4d[spring4D->index2.n - rigidBodies4d.size()], rigidBodies4d[spring4D->index1]);
				}
				else
				{
					spring4D->update_spring4D(walls4d[spring4D->index1 - rigidBodies4d.size()], walls4d[spring4D->index2.n - rigidBodies4d.size()]);
				}
			}
		}
	}

	static void update_trails4D(std::vector<RigidBody4D*> rigidBodies4d, const float dt, float curTime)
	{
		for (size_t i(0); i < rigidBodies4d.size(); i++)
		{
			rigidBodies4d[i]->update_trail4D(dt, curTime);
		}
	}

	static void clear_forces4D(std::vector<RigidBody4D*> rigidBodies4d)
	{
		for (RigidBody4D* i : rigidBodies4d)
		{
			for (size_t j(0); j < i->forceSystems4D.size(); j++)i->forceSystems4D[j] = nullptr, free(i->forceSystems4D[j]);i->forceSystems4D.clear();
		}
	}

	static void update_physic4D(std::vector<RigidBody4D*> rigidBodies4d,
		std::vector<size_t> groupIndices,
		std::vector<Group*> groups,
		vector<Wall4D*> walls4d,
		std::vector<Terrain4D*> terrains4d,
		std::vector<Water4D*> waters4d,
		std::vector<std::vector<Collision>>* collisionsVec,
		std::vector <std::vector<Constraint*>>* constraintsVec,
		std::vector < Stick4D*> sticks4d,
		std::vector < Spring4D*> springs4d,
		std::vector < std::vector < HingeConstraint4D*>> hingeConstraintsVec,
		const float dt0)
	{
		float dt = dt0 / 1.f;
		//for (int i(0); i < 8; i++)
		//{
			//wake_up_rigidBodies4D(rigidBodies4d);
			//sleep_rigidBodies4D(rigidBodies4d, dt);
			start_rigidBodies4D(rigidBodies4d, collisionsVec, dt);
			caculate_joints4D(rigidBodies4d, groups, walls4d, sticks4d, springs4d, dt);
			caculate_rigidBodies4D(rigidBodies4d, groupIndices, groups, walls4d, terrains4d, waters4d, hingeConstraintsVec, collisionsVec, constraintsVec, dt);
			//solve_rigidBodies_position4D(rigidBodies4d, walls4d, collisionsVec, dt);
			//clear_forces4D(rigidBodies4d);
			//if (i != 7)collisionsVec->clear();
		//}
	}

	static void before_render_physic4D(std::vector<RigidBody4D*> rigidBodies4d,
		std::vector<Group*> groups,
		vector<Wall4D*> walls4d,
		std::vector < Stick4D*> sticks4d,
		std::vector < Spring4D*> springs4d,
		bool isTrail4d,
		const float dt, float curTime)
	{
		for (Stick4D* i : sticks4d) { if (i->index2.isValid)update_stick4D(rigidBodies4d, walls4d,i); }
		for (Spring4D* i : springs4d) { if (i->index2.isValid)update_spring4D(rigidBodies4d, walls4d,i); }
		if (isTrail4d) { update_trails4D(rigidBodies4d, dt, curTime); }
	}
}