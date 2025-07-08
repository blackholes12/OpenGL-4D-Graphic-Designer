#pragma once
//#include"body.h"
namespace ray {

	static bool get_ray_detect_terrain4d(Object4D* j, glm::vec4 camPos, glm::vec4 forward, glm::vec4 right, float* t,glm::vec4* hitNormal)
	{
		glm::vec4 relativePos(j->position4d - camPos);
		bool isFindPoint0(false);
		if (dot(glm::vec3(right.x, right.z, right.w), glm::vec3(relativePos.x, relativePos.z, relativePos.w)) < (float)(terrainScale * terrainSize) * sqrt(3)/2.f)
		{
			glm::vec4 detectPos4D0;
			for (size_t x(0); x < terrainSize; x++)
			{
				for (size_t z(0); z < terrainSize; z++)
				{
					for (size_t w(0); w < terrainSize; w++)
					{
						int cubeIndex(4 * 6 * (terrainSize * terrainSize * w + terrainSize * z + x));
						glm::vec4 relativePos2(relativePos + j->primitive4D.vertexData4D[cubeIndex] + glm::vec4(-0.5f, 0.f, 0.5f, -0.5f));
						if (dot(glm::vec3(right.x, right.z, right.w), glm::vec3(relativePos2.x, relativePos2.z, relativePos2.w)) < terrainScale * 0.5f * sqrt(3))
						{
							glm::vec3 forwardXZW(normalize(glm::vec3(forward.x, forward.z, forward.w)));
							float t0(dot(forwardXZW, glm::vec3(relativePos2.x, relativePos2.z, relativePos2.w)) / dot(forwardXZW, forwardXZW));
							float t1(t0 - terrainScale * 0.5f * sqrt(3));
							float t2(t0 + terrainScale * 0.5f * sqrt(3));
							float h1(camPos.y + (forward * t1 / length(glm::vec3(forward.x, forward.z, forward.w))).y);
							float h2(camPos.y + (forward * t2 / length(glm::vec3(forward.x, forward.z, forward.w))).y);
							if (t0 >= 0.f)
							{
								if (h1 -
									alg::min(j->primitive4D.vertexData4D[cubeIndex + 3].y,
										alg::min(j->primitive4D.vertexData4D[cubeIndex + 21].y,
											alg::min(j->primitive4D.vertexData4D[cubeIndex + 9].y,
												alg::min(j->primitive4D.vertexData4D[cubeIndex + 17].y,
													alg::min(j->primitive4D.vertexData4D[cubeIndex + 2].y,
														alg::min(j->primitive4D.vertexData4D[cubeIndex + 12].y,
															alg::min(j->primitive4D.vertexData4D[cubeIndex + 5].y, j->primitive4D.vertexData4D[cubeIndex + 4].y)
														)))))) > -1.f
									&&
									h2 -
									alg::max(j->primitive4D.vertexData4D[cubeIndex + 3].y,
										alg::max(j->primitive4D.vertexData4D[cubeIndex + 21].y,
											alg::max(j->primitive4D.vertexData4D[cubeIndex + 9].y,
												alg::max(j->primitive4D.vertexData4D[cubeIndex + 17].y,
													alg::max(j->primitive4D.vertexData4D[cubeIndex + 2].y,
														alg::max(j->primitive4D.vertexData4D[cubeIndex + 12].y,
															alg::max(j->primitive4D.vertexData4D[cubeIndex + 5].y, j->primitive4D.vertexData4D[cubeIndex + 4].y)
														)))))) < 1.f
									) {
									for (size_t i(0); i < 6; i++)
									{
										//std::cout << "detect" << "\n";
										detectPos4D0 = get_ray_detect_tetra_pos(camPos, forward, 
											j->primitive4D.normalData4D[cubeIndex + 4 * i],
											j->position4d + j->primitive4D.vertexData4D[cubeIndex + 4 * i],
											j->position4d + j->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
											j->position4d + j->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
											j->position4d + j->primitive4D.vertexData4D[cubeIndex + 4 * i + 3]);
										if (is_in_terrain_tetra(detectPos4D0 - j->position4d,
											j->primitive4D.vertexData4D[cubeIndex + 4 * i],
											j->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
											j->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
											j->primitive4D.vertexData4D[cubeIndex + 4 * i + 3]))
										{
											*t = length(detectPos4D0 - camPos);
											*hitNormal = j->primitive4D.normalData4D[cubeIndex];
											isFindPoint0 = true;
											//std::cout << "FindPoint.y=" << detectPos4D.y << "\n";
										}
									}
								}
							}
						}
					}
				}
			}

		}
		return isFindPoint0;
	}
	//
	static bool get_ray_detect_terrain_pos4D(glm::vec4 camPos, glm::vec4 forward, glm::vec4 right, std::vector<size_t> groupIndices, std::vector<Group*> groups, vector<Terrain4D*> terrains4d, glm::vec4* detectPos4D)
	{
		glm::vec4 detectPos4D0(camPos);
		bool isFindPoint(false);
		glm::vec4 hitNormal;
		float t;
		*detectPos4D = glm::vec4(1000000.f);
		for (size_t groupIndex : groupIndices)
		{
			Group* i(groups[groupIndex]);
			for (size_t terrain4DIndex:i->terrains4DIndices)
			{
				Terrain4D* j(terrains4d[terrain4DIndex]);
				if (j->isClamp && j->isFront) {
					if (j->colType == TERRAIN4D)
					{
						if (get_ray_detect_terrain4d(j, camPos, forward, right, &t,&hitNormal))
						{
							if (length(*detectPos4D - camPos) > t)
							{
								*detectPos4D = camPos + t * forward;
								isFindPoint = true;
							}
							if (!isFindPoint)
							{
								*detectPos4D = detectPos4D0;
								isFindPoint = true;
							}
						}
					}
				}
			}
		}
		return isFindPoint;
	}
	/*
	if (camPos.y * forward.y < 0.f)
	{
		float hitLength = -camPos.y / forward.y;
		glm::vec4 hitPos = camPos + hitLength * forward;
		isFindPoint = true;
		return glm::vec4(hitPos.x, 0.f, hitPos.z, hitPos.w);
	}
	else
	{
		return glm::vec4(200.f, 0.f, 0.f, 0.f);
	}
	*/
	
	static bool ray_detect_collider4D(Object4D* j, glm::vec4 camPos, glm::vec4 forward, glm::vec4 right, float* t, glm::vec4* hitNormal)
	{
		bool isDetected(false);
		float t0(100000000.f);
		switch (j->colType)
		{
		case SPHERE4D:
		{
			glm::vec4 rPos(j->position4d - camPos);
			float distance(length(rPos));
			float cosAMutiDistance(dot(rPos, forward));
			if (cosAMutiDistance > 0)
			{
				float sinAMutiDistance(sqrt(distance * distance - cosAMutiDistance * cosAMutiDistance));
				float radius(alg::min(j->scale4D.w, alg::min(j->scale4D.z, alg::min(j->scale4D.x, j->scale4D.y))) / 2.f);
				if (sinAMutiDistance < radius)
				{
					t0 = cosAMutiDistance - sqrt(radius * radius - sinAMutiDistance * sinAMutiDistance);
					//float t2(cosAMutiDistance + sqrt(radius * radius - sinAMutiDistance * sinAMutiDistance));
					*hitNormal = normalize(camPos + forward * t0 - j->position4d);
					//*hitPosFar = camPos + forward * t2;
					isDetected=true;
				}
			}
			break;
		}
		case BOX4D:
		{
			glm::vec4 startPos4D(world_pos_to_body(j, camPos));
			glm::vec4 forward2(world_vec_to_body(j, forward));
			glm::vec4 endPos4D(startPos4D + forward2 * 120000.f);
			if (line_sigment_detect_box4D(startPos4D, endPos4D, j->scale4D, &t0, hitNormal))
			{
				*hitNormal = body_vec_to_world(j, *hitNormal);
				isDetected = true;
			}
			break;
		}
		case STEP4D:
		{
			glm::vec4 startPos4D(world_pos_to_body(j, camPos));
			glm::vec4 forward2(world_vec_to_body(j, forward));
			glm::vec4 endPos4D(startPos4D + forward2 * 120000.f);
			if (line_sigment_detect_box4D(startPos4D, endPos4D, j->scale4D, &t0, hitNormal))
			{
				*hitNormal = body_vec_to_world(j, *hitNormal);
				isDetected = true;
			}
			break;
		}
		case MESH4D:
		{
			glm::vec4 startPos4D(world_pos_to_body(j, camPos));
			glm::vec4 forward2(world_vec_to_body(j, forward));
			glm::vec4 hitNormal0;
			for (int i(0); i < j->primitive4D.get_size_of_vertices4D() / 4; i++)
			{
				glm::vec4 vertexPos4D1(j->primitive4D.vertexData4D[4 * i] * j->scale4D);
				glm::vec4 vertexPos4D2(j->primitive4D.vertexData4D[4 * i + 1] * j->scale4D);
				glm::vec4 vertexPos4D3(j->primitive4D.vertexData4D[4 * i + 2] * j->scale4D);
				glm::vec4 vertexPos4D4(j->primitive4D.vertexData4D[4 * i + 3] * j->scale4D);
				//if (length(vertexPos4D1 - vertexPos4D2) > 0.001f && length(vertexPos4D1 - vertexPos4D3) > 0.001f &&
				//	length(vertexPos4D1 - vertexPos4D4) > 0.001f && length(vertexPos4D2 - vertexPos4D3) > 0.001f &&
				//	length(vertexPos4D2 - vertexPos4D4) > 0.001f && length(vertexPos4D3 - vertexPos4D4) > 0.001f)
				{
					hitNormal0 = normalize(j->primitive4D.normalData4D[4 * i] / j->scale4D);
					if (get_ray_detect_tetra_distance(startPos4D, forward2, hitNormal0, vertexPos4D1, vertexPos4D2, vertexPos4D3, vertexPos4D4, &t0))
					{
						*hitNormal = hitNormal0;
						isDetected = true;
					}
				}
			}
			if (isDetected)
			{
				*hitNormal = body_vec_to_world(j, *hitNormal);
			}
			break;
		}
		case CAPSULE4D:
		{
			float radius(alg::min(j->scale4D.w, alg::min(j->scale4D.x, j->scale4D.y)) / 2.f);
			float capsuleLength(j->scale4D.z);
			{
				glm::vec4 rPos(-world_pos_to_body(j, camPos));
				glm::vec3 rPosXYW(glm::vec3(rPos.x, rPos.y, rPos.w));
				glm::vec4 forward0(world_vec_to_body(j, forward));
				glm::vec3 forwardXYW(glm::vec3(forward0.x, forward0.y, forward0.w));
				glm::vec3 forwardXYWe(normalize(forwardXYW));
				float k(length(forwardXYW));
				if (k != 0.f)
				{
					float distance(length(rPosXYW));
					float cosAMutiDistance(dot(rPosXYW, forwardXYWe));
					if (cosAMutiDistance > 0)
					{
						float sinAMutiDistance(sqrt(distance * distance - cosAMutiDistance * cosAMutiDistance));
						if (sinAMutiDistance < radius)
						{
							float t1((cosAMutiDistance - sqrt(radius * radius - sinAMutiDistance * sinAMutiDistance)) / k);
							//float t2((cosAMutiDistance + sqrt(radius * radius - sinAMutiDistance * sinAMutiDistance))/k);
							if (t0 > t1&&t1>0.f)
							{
								if (abs(-rPos.z + forward0.z * t1) < capsuleLength / 2.f - radius)
								{
									t0 = t1;
									*hitNormal = -rPos + forward0 * t0;
									hitNormal->z = 0.f;
									*hitNormal = normalize(body_vec_to_world(j, *hitNormal));
									isDetected = true;
								}
							}
						}
					}
				}
			}
			for(int i(0);i<2;i++)
			{
				float sign(1.f);
				if (i == 1)
					sign = -1.f;
				glm::vec4 rPos(body_pos_to_world(j, sign * (glm::vec4(0, 0, capsuleLength / 2.f - radius, 0))) - camPos);
				float distance(length(rPos));
				float cosAMutiDistance(dot(rPos, forward));
				if (cosAMutiDistance > 0)
				{
					float sinAMutiDistance(sqrt(distance * distance - cosAMutiDistance * cosAMutiDistance));
					if (sinAMutiDistance < radius)
					{
						float t1(cosAMutiDistance - sqrt(radius * radius - sinAMutiDistance * sinAMutiDistance));
						if (t0 > t1)
						{
							t0 = t1;
							*hitNormal = normalize(camPos + forward * t0 - rPos - camPos);
							isDetected = true;
						}
						//float t2(cosAMutiDistance + sqrt(radius * radius - sinAMutiDistance * sinAMutiDistance));
					}
				}
			}
			break;
		}
		case TERRAIN4D:
		{
			if (get_ray_detect_terrain4d(j, camPos, forward, right, &t0, hitNormal))
			{
				isDetected = true;
			}
			break;
		}
		default:
			break;
		}
		*t = t0;
		return isDetected;
	}

	static bool detect_object4d_index(
		VectorIndex* hitIndex,
		vector<RigidBody4D*> rigidBodies4d,
		std::vector<size_t> groupIndices,
		vector<Group*> groups,
		vector<Wall4D*> walls4d,
		vector<Terrain4D*> terrains4d,
		vector<Stick4D*> sticks4d,
		vector<Spring4D*> springs4d,
		bool isDetectWall,
		bool isDetectJoint,
		bool isDetectTransparent,
		bool isDetectTerrain4D,
		glm::vec4 camPos,
		glm::vec4 camFor,
		glm::vec4 camRight,
		glm::vec4* hitPosNear,
		glm::vec4* hitNormal)
	{
		bool isDetected(false);
		size_t hitIndex0;
		glm::vec4 hitNormal0;
		float t0;
		float t1(10000000.f);
		for (size_t i(1); i < rigidBodies4d.size(); i++) {
			RigidBody4D* a(rigidBodies4d[i]);
			float colRadious(length(a->scale4D) / 2.f);
			float distance4D(length(a->position4d - camPos));
			float cosView(dot(camFor, normalize(a->position4d - camPos)));
			float sinView(sqrt(1.f - cosView * cosView));
			if (cosView * distance4D > -colRadious && sinView * distance4D < colRadious)
			{
				if (!(a->texture3DIndex == GLASS || a->texture3DIndex == GRID || a->paintingColor.w < 1.f) || isDetectTransparent)
				{
					if (ray::ray_detect_collider4D(a, camPos, camFor, camRight, &t0, &hitNormal0))
					{
						if (t0 < t1 || !isDetected)
						{
							t1 = t0;
							*hitNormal = hitNormal0;
							hitIndex0 = i;
							isDetected = true;
						}
					}
				}
			}
		}

		if (isDetectWall)
		{
			for (size_t groupIndex : groupIndices)
			{
				Group* i(groups[groupIndex]);
				for (size_t j(0); j < i->walls4DIndices.size(); j++) {
					size_t wallIndex(i->walls4DIndices[j]);
					Wall4D* a(walls4d[wallIndex]);
					float colRadious(length(a->scale4D) / 2.f);
					float distance4D(length(a->position4d - camPos));
					float cosView(dot(camFor, normalize(a->position4d - camPos)));
					float sinView(sqrt(1.f - cosView * cosView));
					if (cosView * distance4D > -colRadious && sinView * distance4D < colRadious)
					{
						if (!(a->texture3DIndex == GLASS || a->texture3DIndex == GRID || a->paintingColor.w < 1.f) || isDetectTransparent)
						{
							if (ray::ray_detect_collider4D(a, camPos, camFor, camRight, &t0, &hitNormal0))
							{
								if (t0 < t1 || !isDetected)
								{
									t1 = t0;
									*hitNormal = hitNormal0;
									hitIndex0 = wallIndex + rigidBodies4d.size();
									isDetected = true;
								}
							}
						}
					}
				}
			}
		}

		if (isDetectJoint)
		{
			for (size_t i(0); i < size_of_objects4d(sticks4d, springs4d); i++)
			{
				Object4D* a(find_joint4d(sticks4d, springs4d, i));
				float colRadious(length(a->scale4D) / 2.f);
				float distance4D(length(a->position4d - camPos));
				float cosView(dot(camFor, normalize(a->position4d - camPos)));
				float sinView(sqrt(1.f - cosView * cosView));
				if (cosView * distance4D > -colRadious && sinView * distance4D < colRadious)
				{
					if (ray::ray_detect_collider4D(a, camPos, camFor, camRight, &t0, &hitNormal0))
					{
						if (t0 < t1 || !isDetected)
						{
							t1 = t0;
							*hitNormal = hitNormal0;
							hitIndex0 = i + size_of_objects4d(rigidBodies4d, walls4d);
							isDetected = true;
						}
					}
				}
			}
		}

		if (isDetectTerrain4D)
		{
			for (size_t groupIndex : groupIndices)
			{
				Group* i(groups[groupIndex]);
				for (size_t terrainIndex : i->terrains4DIndices) {
					Terrain4D* a(terrains4d[terrainIndex]);
					if (ray::ray_detect_collider4D(a, camPos, camFor, camRight, &t0, &hitNormal0))
					{
						if (t0 < t1 || !isDetected)
						{
							t1 = t0;
							*hitNormal = hitNormal0;
							hitIndex0 = terrainIndex + size_of_objects4d(rigidBodies4d, walls4d, sticks4d, springs4d);
							isDetected = true;
							hitIndex->isValid = false;
						}
					}
				}
			}
		}

		if (isDetected)
		{
			*hitPosNear = camPos + t1 * camFor;
			hitIndex->n = hitIndex0;
			hitIndex->isValid = true;
			return true;
		}
		else
		{
			if (camFor.y < 0.f)
			{
				t1 = -camPos.y / camFor.y;
				*hitNormal = glm::vec4(0.f, 1.f, 0.f, 0.f);
				*hitPosNear = camPos + t1 * camFor;
				isDetected = true;
			}
			hitIndex->isValid = false;
			return isDetected;
		}
	}

	static glm::vec4 ray4d_to_screen_position(glm::vec4 direction4D, glm::mat4 viewMat4D, glm::mat4 projectionMat)
	{
		glm::vec4 pos0(viewMat4D * -direction4D);
		glm::vec4 screenPosition(projectionMat * glm::vec4(pos0.x, pos0.y, pos0.z,1.f));
		return screenPosition;
	}

	static bool is_in_screen(glm::vec4 direction4D, glm::mat4 viewMat4D, glm::mat4 projectionMat)
	{
		glm::vec4 screenPosition(ray4d_to_screen_position(direction4D, viewMat4D, projectionMat));
		//std::cout << "screenPosition.x=" << screenPosition.x << " screenPosition.y=" << screenPosition.y << " screenPosition.z=" << screenPosition.z << " screenPosition.w=" << screenPosition.w << "\n";
		return abs(screenPosition.x/ screenPosition.w) < 1.f && abs(screenPosition.y/ screenPosition.w) < 1.f && screenPosition.z > 0.f;
	}
}

class XRay4D {
	unsigned int VBO, VAO, sizeOfLineVertices4D;
public:
	size_t steps;
	LineVertex4D* lineVertices4D;
	XRay4D() {
		glCreateVertexArrays(1, &this->VAO);
		glGenBuffers(1, &this->VBO);
	}
	void update_x_ray4D(vector<RigidBody4D*> rigidBodies4d, std::vector<size_t> groupIndices, std::vector<Group*> groups, vector<Wall4D*> walls4d, vector<Terrain4D*> terrains4d, std::vector<Stick4D*> sticks4d, std::vector<Spring4D*> springs4d, glm::vec4 cameraPos, glm::vec4 cameraFor, glm::vec4 cameraRight, unsigned int reflectionSteps)
	{
		std::vector<glm::vec4> startPositions4D, normals4D, directions4D;
		startPositions4D.push_back(cameraPos), directions4D.push_back(cameraFor);
		bool isBeyond(false);
		VectorIndex voidVectorIndex;
		for (unsigned int i(0); i < reflectionSteps + 1; i++)
		{
			startPositions4D.push_back(glm::vec4(0.f)), normals4D.push_back(glm::vec4(0.f));
			if (ray::detect_object4d_index(&voidVectorIndex, rigidBodies4d, groupIndices, groups, walls4d, terrains4d, sticks4d, springs4d, true, true, false, true, startPositions4D[i], directions4D[i], cameraRight, &startPositions4D[i + 1], &normals4D[i]))
			{
				directions4D.push_back(glm::reflect(directions4D[i], normals4D[i]));
			}
			else
			{
				isBeyond = true;
				break;
			}
		}
		this->steps = startPositions4D.size();
		this->lineVertices4D = new LineVertex4D[steps];
		for (size_t i(0); i < steps - 1; i++)
		{
			this->lineVertices4D[i] = { startPositions4D[i],glm::vec3(0.f) };
		}
		if (isBeyond)this->lineVertices4D[steps - 1].pos4D = startPositions4D[steps - 2] + 100000.f * directions4D[steps - 2];
		else this->lineVertices4D[steps - 1].pos4D = startPositions4D[steps - 1];

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		this->sizeOfLineVertices4D = this->steps * sizeof(LineVertex4D);
		glBindVertexArray(this->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, this->sizeOfLineVertices4D, this->lineVertices4D, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(LineVertex4D), (GLvoid*)offsetof(LineVertex4D, pos4D));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(LineVertex4D), (GLvoid*)offsetof(LineVertex4D, color));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
	}
	void render(Shader* shader) {
		shader->use();
		glBindVertexArray(this->VAO);
		glDrawArrays(GL_LINE_STRIP, 0, this->steps);
	}
	~XRay4D() {
		glDeleteVertexArrays(1, &this->VAO);
		glDeleteBuffers(1, &this->VBO);
		delete[] this->lineVertices4D;
	}
};