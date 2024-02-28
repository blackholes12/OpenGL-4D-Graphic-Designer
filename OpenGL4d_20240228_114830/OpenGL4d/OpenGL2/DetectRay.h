#pragma once
#include"body.h"
namespace ray {

	static glm::vec4 relativePos;
	static int cubeIndex;
	static glm::vec4 relativePos2;
	static const int size = 4;
	static float t, t1, t2, h1, h2;
	static glm::vec3 forwardXZW;
	static bool get_ray_detect_terrain4d(Object4D* j, glm::vec4 camPos, glm::vec4 forward, glm::vec4 right, glm::vec4* detectPos4D)
	{
		bool isFindPoint0 = false;
		relativePos = j->position4D - camPos;
		if (dot(glm::vec3(right.x, right.z, right.w), glm::vec3(relativePos.x, relativePos.z, relativePos.w)) < 2.f * sqrt(3))
		{
			glm::vec4 detectPos4D0;
			for (size_t x = 0; x < size; x++)
			{
				for (size_t z = 0; z < size; z++)
				{
					for (size_t w = 0; w < size; w++)
					{
						cubeIndex = 4 * 6 * (size * size * w + size * z + x);
						relativePos2 = relativePos + j->primitive4D.vertexData4D[cubeIndex] + glm::vec4(-0.5f, 0.f, 0.5f, -0.5f);
						if (dot(glm::vec3(right.x, right.z, right.w), glm::vec3(relativePos2.x, relativePos2.z, relativePos2.w)) < 0.5f * sqrt(3))
						{
							forwardXZW = normalize(glm::vec3(forward.x, forward.z, forward.w));
							t = dot(forwardXZW, glm::vec3(relativePos2.x, relativePos2.z, relativePos2.w)) / dot(forwardXZW, forwardXZW);
							t1 = t - 0.5f * sqrt(3);
							t2 = t + 0.5f * sqrt(3);
							h1 = camPos.y + (forward * t1 / length(glm::vec3(forward.x, forward.z, forward.w))).y;
							h2 = camPos.y + (forward * t2 / length(glm::vec3(forward.x, forward.z, forward.w))).y;
							if (t >= 0.f)
							{
								if (h1 -
									min(j->primitive4D.vertexData4D[cubeIndex + 3].y,
										min(j->primitive4D.vertexData4D[cubeIndex + 21].y,
											min(j->primitive4D.vertexData4D[cubeIndex + 9].y,
												min(j->primitive4D.vertexData4D[cubeIndex + 17].y,
													min(j->primitive4D.vertexData4D[cubeIndex + 2].y,
														min(j->primitive4D.vertexData4D[cubeIndex + 12].y,
															min(j->primitive4D.vertexData4D[cubeIndex + 5].y, j->primitive4D.vertexData4D[cubeIndex + 4].y)
														)))))) > -1.f
									&&
									h2 -
									max(j->primitive4D.vertexData4D[cubeIndex + 3].y,
										max(j->primitive4D.vertexData4D[cubeIndex + 21].y,
											max(j->primitive4D.vertexData4D[cubeIndex + 9].y,
												max(j->primitive4D.vertexData4D[cubeIndex + 17].y,
													max(j->primitive4D.vertexData4D[cubeIndex + 2].y,
														max(j->primitive4D.vertexData4D[cubeIndex + 12].y,
															max(j->primitive4D.vertexData4D[cubeIndex + 5].y, j->primitive4D.vertexData4D[cubeIndex + 4].y)
														)))))) < 1.f
									) {
									for (size_t i = 0; i < 6; i++)
									{
										detectPos4D0 = get_ray_detect_tetra_pos(camPos, forward, 
											j->primitive4D.normalData4D[cubeIndex + 4 * i],
											j->position4D + j->primitive4D.vertexData4D[cubeIndex + 4 * i],
											j->position4D + j->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
											j->position4D + j->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
											j->position4D + j->primitive4D.vertexData4D[cubeIndex + 4 * i + 3]);
										if (is_in_tetra(detectPos4D0 - j->position4D,
											j->primitive4D.vertexData4D[cubeIndex + 4 * i],
											j->primitive4D.vertexData4D[cubeIndex + 4 * i + 1],
											j->primitive4D.vertexData4D[cubeIndex + 4 * i + 2],
											j->primitive4D.vertexData4D[cubeIndex + 4 * i + 3]))
										{
											*detectPos4D = detectPos4D0;
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
	static bool get_ray_detect_terrain_pos4D(glm::vec4 camPos, glm::vec4 forward, glm::vec4 right, std::vector<Group*> groups, glm::vec4* detectPos4D)
	{
		glm::vec4 detectPos4D0 = camPos;
		bool isFindPoint = false;
		for (Group* i : groups)
		{
			if (i->isRender)
			{
				for (Terrain4D* j : i->terrains4D)
				{
					if (j->isClamp) {
						if (j->isFront) {
							if (j->colType == TERRAIN4D)
							{
								if (get_ray_detect_terrain4d(j, camPos, forward, right, &detectPos4D0))
								{
									if (length(*detectPos4D - camPos) > length(detectPos4D0 - camPos))
									{
										*detectPos4D = detectPos4D0;
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
	
	static glm::vec4 endPos4D;
	static bool ray_detect_collider4D(Object4D* j, glm::vec4 camPos, glm::vec4 forward, glm::vec4 right, glm::vec4* hitPosNear, glm::vec4* hitPosFar)
	{
		bool isDetected = false;
		switch (j->colType)
		{
		case SPHERE4D:
		{
			glm::vec4 rPos = j->position4D - camPos;
			float distance = length(rPos);
			float cosAMutiDistance = dot(rPos, forward);
			if (cosAMutiDistance > 0)
			{
				float sinAMutiDistance = sqrt(distance * distance - cosAMutiDistance * cosAMutiDistance);
				float radious = min(j->scale4D.w, min(j->scale4D.z, min(j->scale4D.x, j->scale4D.y))) / 2.f;
				if (sinAMutiDistance < radious)
				{
					float t1 = cosAMutiDistance - sqrt(radious * radious - sinAMutiDistance * sinAMutiDistance);
					float t2 = cosAMutiDistance + sqrt(radious * radious - sinAMutiDistance * sinAMutiDistance);
					*hitPosNear = camPos + forward * t1;
					*hitPosFar = camPos + forward * t2;
					isDetected = true;
				}
			}
			break;
		}
		case BOX4D:
		{
			glm::vec4 startPos4D = world_pos_to_body(j, camPos);
			glm::vec4 forward2 = world_vec_to_body(j, forward);
			endPos4D = startPos4D + forward2 * 120000.f;
			if (line_sigment_detect_box4D(startPos4D, endPos4D, j->scale4D, hitPosNear, hitPosFar))
			{
				*hitPosNear = body_pos_to_world(j, *hitPosNear);
				*hitPosFar = body_pos_to_world(j, *hitPosFar);
				isDetected = true;
			}
			break;
		}
		case STEP4D:
		{
			glm::vec4 startPos4D = world_pos_to_body(j, camPos);
			glm::vec4 forward2 = world_vec_to_body(j, forward);
			endPos4D = startPos4D + forward2 * 120000.f;
			if (line_sigment_detect_box4D(startPos4D, endPos4D, j->scale4D, hitPosNear, hitPosFar))
			{
				*hitPosNear = body_pos_to_world(j, *hitPosNear);
				*hitPosFar = body_pos_to_world(j, *hitPosFar);
				isDetected = true;
			}
			break;
		}
		case MESH4D:
		{
			glm::vec4 startPos4D = world_pos_to_body(j, camPos);
			glm::vec4 forward2 = world_vec_to_body(j, forward);
			for (int i = 0; i < j->primitive4D.get_size_of_vertices4D() / 4; i++)
			{
				glm::vec4 vertexPos4D1 = j->primitive4D.vertexData4D[4 * i] * j->scale4D;
				glm::vec4 vertexPos4D2 = j->primitive4D.vertexData4D[4 * i + 1] * j->scale4D;
				glm::vec4 vertexPos4D3 = j->primitive4D.vertexData4D[4 * i + 2] * j->scale4D;
				glm::vec4 vertexPos4D4 = j->primitive4D.vertexData4D[4 * i + 3] * j->scale4D;
				if (length(vertexPos4D1 - vertexPos4D2) > 0.001f && length(vertexPos4D1 - vertexPos4D3) > 0.001f &&
					length(vertexPos4D1 - vertexPos4D4) > 0.001f && length(vertexPos4D2 - vertexPos4D3) > 0.001f &&
					length(vertexPos4D2 - vertexPos4D4) > 0.001f && length(vertexPos4D3 - vertexPos4D4) > 0.001f)
				{
					if (get_ray_detect_tetra_pos(startPos4D, forward2, normalize(j->primitive4D.normalData4D[4 * i] / j->scale4D), vertexPos4D1, vertexPos4D2, vertexPos4D3, vertexPos4D4, hitPosNear, hitPosFar))
					{
						isDetected = true;
					}
				}
			}
			*hitPosNear = body_pos_to_world(j, *hitPosNear);
			*hitPosFar = body_pos_to_world(j, *hitPosFar);
			break;
		}
		case CAPSULE4D:
		{
			float radious = glm::min(j->scale4D.w, glm::min(j->scale4D.x, j->scale4D.y)) / 2.f;
			float capsuleLength = j->scale4D.z;
			float t = 0.f;
			for(int i=0;i<2;i++)
			{
				float sign = 1.f;
				if (i == 1)
					sign = -1.f;
				glm::vec4 rPos = j->position4D + sign*body_vec_to_world(j, glm::vec4(0, 0, capsuleLength / 2.f - radious, 0)) - camPos;
				float distance = length(rPos);
				float cosAMutiDistance = dot(rPos, forward);
				if (cosAMutiDistance > 0)
				{
					float sinAMutiDistance = sqrt(distance * distance - cosAMutiDistance * cosAMutiDistance);
					float radious = min(j->scale4D.w, min(j->scale4D.z, min(j->scale4D.x, j->scale4D.y))) / 2.f;
					if (sinAMutiDistance <= radious)
					{
						float t1 = cosAMutiDistance - sqrt(radious * radious - sinAMutiDistance * sinAMutiDistance);
						if (t > t1||t==0.f)
						{
							t = t1;
						}
						float t2 = cosAMutiDistance + sqrt(radious * radious - sinAMutiDistance * sinAMutiDistance);
						isDetected = true;
					}
				}
			}
			{
				glm::vec4 rPos = -world_pos_to_body(j, camPos);
				glm::vec3 rPosXYW = glm::vec3(rPos.x, rPos.y, rPos.w);
				glm::vec4 forward0= world_vec_to_body(j, forward);
				glm::vec3 forwardXYW = glm::vec3(forward0.x, forward0.y, forward0.w);
				glm::vec3 forwardXYWe = normalize(forwardXYW);
				float k = length(forwardXYW);
				if (k != 0.f)
				{
					float distance = length(rPosXYW);
					float cosAMutiDistance = dot(rPosXYW, forwardXYWe);
					if (cosAMutiDistance > 0)
					{
						float sinAMutiDistance = sqrt(distance * distance - cosAMutiDistance * cosAMutiDistance);
						float radious = min(j->scale4D.w, min(j->scale4D.z, min(j->scale4D.x, j->scale4D.y))) / 2.f;
						if (sinAMutiDistance < radious)
						{
							float t1 = (cosAMutiDistance - sqrt(radious * radious - sinAMutiDistance * sinAMutiDistance))/k;
							float t2 = (cosAMutiDistance + sqrt(radious * radious - sinAMutiDistance * sinAMutiDistance))/k;
							if (abs(-rPos.z + forward0.z * t1) < capsuleLength / 2.f - radious)
							{
								if (t > t1 || t == 0.f)
								{
									t = t1;
								}
								isDetected = true;
							}
						}
					}
				}
			}
			*hitPosNear = camPos + forward * t;
			break;
		}
		case TERRAIN4D:
		{
			if (get_ray_detect_terrain4d(j, camPos, forward, right, hitPosNear))
			{
				*hitPosFar = *hitPosNear;
				isDetected = true;
			}
			break;
		}
		default:
			break;
		}
	
		return isDetected;
	}

	static int detect_object4d_index(vector<RigidBody4D*> rigidBodies4D, 
		vector<RigidBody4D*> dynamites4D2, 
		vector<Group*>groups, 
		vector<Wall4D*> walls4D,
		vector<Wall4D*> dynamites4D, 
		bool isDetectStatic, 
		bool isDetectTransparent,
		bool isDetectTerrain4D,
		glm::vec4 camPos, 
		glm::vec4 camFor,
		glm::vec4 camRight,
	glm::vec4* hitPosNear)
	{
		bool isDetected = false;
		int hitIndex = -1;
		glm::vec4 detectedObjectPos;
		glm::vec4 none;
		for (size_t i = 1; i < rigidBodies4D.size(); i++) {
			float colRadious = length(rigidBodies4D[i]->scale4D) / 2.f;
			float distance4D = length(rigidBodies4D[i]->position4D - camPos);
			float cosView = dot(camFor, normalize(rigidBodies4D[i]->position4D - camPos));
			float sinView = sqrt(1.f- cosView* cosView);
			if (cosView* distance4D >-colRadious&& sinView * distance4D < colRadious)
			{
				if (ray::ray_detect_collider4D(rigidBodies4D[i], camPos, camFor, camRight,  hitPosNear, &none))
				{
					if (length(*hitPosNear - camPos) < length(detectedObjectPos - camPos))
					{
						detectedObjectPos = *hitPosNear;
						hitIndex = i;
						isDetected = true;
					}
					if (!isDetected && ray::ray_detect_collider4D(rigidBodies4D[i], camPos, camFor, camRight, hitPosNear, &none))
					{
						detectedObjectPos = *hitPosNear;
						hitIndex = i;
						isDetected = true;
					}
				}
			}
		}

		for (size_t i = 0; i < dynamites4D2.size(); i++) {
			float colRadious = length(dynamites4D2[i]->scale4D) / 2.f;
			float distance4D = length(dynamites4D2[i]->position4D - camPos);
			float cosView = dot(camFor, normalize(dynamites4D2[i]->position4D - camPos));
			float sinView = sqrt(1.f - cosView * cosView);
			if (cosView * distance4D > -colRadious && sinView * distance4D < colRadious)
			{
				if (ray::ray_detect_collider4D(dynamites4D2[i], camPos, camFor, camRight, hitPosNear, &none))
				{
					if (length(*hitPosNear - camPos) < length(detectedObjectPos - camPos))
					{
						detectedObjectPos = *hitPosNear;
						hitIndex = i + rigidBodies4D.size();
						isDetected = true;
					}
					if (!isDetected && ray::ray_detect_collider4D(dynamites4D2[i], camPos, camFor, camRight, hitPosNear, &none))
					{
						detectedObjectPos = *hitPosNear;
						hitIndex = i + rigidBodies4D.size();
						isDetected = true;
					}
				}
			}
		}
		
		if (isDetectStatic)
		{
			for (size_t i = 0; i < size_of_walls4d(groups); i++) {
				if (is_wall4d_being_rendered(groups, i))
				{
					if (!find_wall4d(groups, i)->diffuse3D->isTransparent || isDetectTransparent)
					{
						float colRadious = length(find_wall4d(groups, i)->scale4D) / 2.f;
						float distance4D = length(find_wall4d(groups, i)->position4D - camPos);
						float cosView = dot(camFor, normalize(find_wall4d(groups, i)->position4D - camPos));
						float sinView = sqrt(1.f - cosView * cosView);
						if (cosView * distance4D > -colRadious && sinView * distance4D < colRadious)
						{
							if (ray::ray_detect_collider4D(find_wall4d(groups, i), camPos, camFor, camRight, hitPosNear, &none))
							{
								if (length(*hitPosNear - camPos) < length(detectedObjectPos - camPos))
								{
									detectedObjectPos = *hitPosNear;
									hitIndex = i + size_of_objects4d(rigidBodies4D, dynamites4D2);
									isDetected = true;
								}
								if (!isDetected)
								{
									detectedObjectPos = *hitPosNear;
									hitIndex = i + size_of_objects4d(rigidBodies4D, dynamites4D2);
									isDetected = true;
								}
							}
						}
					}
				}
			}
			
			for (size_t i = 0; i < walls4D.size(); i++) {
				float colRadious = length(walls4D[i]->scale4D) / 2.f;
				float distance4D = length(walls4D[i]->position4D - camPos);
				float cosView = dot(camFor, normalize(walls4D[i]->position4D - camPos));
				float sinView = sqrt(1.f - cosView * cosView);
				if (cosView * distance4D > -colRadious && sinView * distance4D < colRadious)
				{
					if (ray::ray_detect_collider4D(walls4D[i], camPos, camFor, camRight, hitPosNear, &none))
					{
						if (length(*hitPosNear - camPos) < length(detectedObjectPos - camPos))
						{
							detectedObjectPos = *hitPosNear;
							hitIndex = i + size_of_objects4d(rigidBodies4D, dynamites4D2, groups);
							isDetected = true;
						}
						if (!isDetected)
						{
							detectedObjectPos = *hitPosNear;
							hitIndex = i + size_of_objects4d(rigidBodies4D, dynamites4D2, groups);
							isDetected = true;
						}
					}
				}
			}
			
			for (size_t i = 0; i < dynamites4D.size(); i++) {
				float colRadious = length(dynamites4D[i]->scale4D) / 2.f;
				float distance4D = length(dynamites4D[i]->position4D - camPos);
				float cosView = dot(camFor, normalize(dynamites4D[i]->position4D - camPos));
				float sinView = sqrt(1.f - cosView * cosView);
				if (cosView * distance4D > -colRadious && sinView * distance4D < colRadious)
				{
					if (ray::ray_detect_collider4D(dynamites4D[i], camPos, camFor, camRight, hitPosNear, &none))
					{
						if (length(*hitPosNear - camPos) < length(detectedObjectPos - camPos))
						{
							detectedObjectPos = *hitPosNear;
							hitIndex = i + size_of_objects4d(rigidBodies4D, dynamites4D2, groups, walls4D);
							isDetected = true;
						}
						if (!isDetected)
						{
							detectedObjectPos = *hitPosNear;
							hitIndex = i + size_of_objects4d(rigidBodies4D, dynamites4D2, groups, walls4D);
							isDetected = true;
						}
					}
				}
			}
			
			if (isDetectTerrain4D)
			{
				for (size_t i = 0; i < size_of_terrains4d(groups); i++)
				{
					if (is_terrain4d_being_rendered(groups, i))
					{
						if (ray::ray_detect_collider4D(find_terrain4d(groups, i), camPos, camFor, camRight, hitPosNear, &none))
						{
							if (length(*hitPosNear - camPos) < length(detectedObjectPos - camPos))
							{
								detectedObjectPos = *hitPosNear;
								hitIndex = i + size_of_objects4d(rigidBodies4D, dynamites4D2, groups, walls4D, dynamites4D);
								isDetected = true;
							}
							if (!isDetected)
							{
								detectedObjectPos = *hitPosNear;
								hitIndex = i + size_of_objects4d(rigidBodies4D, dynamites4D2, groups, walls4D, dynamites4D);
								isDetected = true;
							}
						}
					}
				}
			}
		}
		if (!isDetected)
		{
			if (camFor.y < 0.f)
			{
				detectedObjectPos = camPos - (camPos.y / camFor.y)*camFor;
				hitIndex = -2;
				isDetected = true;
			}
		}
		*hitPosNear = detectedObjectPos;
		return hitIndex;
	}

	static glm::vec4 ray4d_to_screen_position(glm::vec4 direction4D, glm::mat4 viewMat4D, glm::mat4 projectionMat)
	{
		glm::vec4 pos0 = viewMat4D * direction4D;
		glm::vec4 screenPosition = projectionMat * glm::vec4(pos0.x, pos0.y, pos0.z,1.f);
		return screenPosition;
	}

	static bool is_in_screen(glm::vec4 direction4D, glm::mat4 viewMat4D, glm::mat4 projectionMat)
	{
		glm::vec4 screenPosition = ray4d_to_screen_position(direction4D, viewMat4D, projectionMat);
		//std::cout << "screenPosition.x=" << screenPosition.x << "\n";
		return abs(screenPosition.x) < 1.f && abs(screenPosition.y) < 1.f&& screenPosition.z>0.f;
	}
}