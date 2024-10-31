#include"Game.h"

void Game::updateKeyboardInput()
{
	//Program
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(this->window, GLFW_TRUE);
	}
	if (this->inputs[10]->getKeyOnPress(this->window, GLFW_KEY_F2))
	{
		SYSTEMTIME systemTime;
		GetLocalTime(&systemTime);
		char ss[256];
		snprintf(ss, 255, "resourcefile/screenshots/%i %02i %02i %02i %02i %02i.png", systemTime.wYear, systemTime.wMonth, systemTime.wDay, systemTime.wHour, systemTime.wMinute, systemTime.wSecond);
		SOIL_save_screenshot(ss, SOIL_SAVE_TYPE_PNG, 0, 0, this->framebufferWidth, this->framebufferHeight);
	}

	//Set and remove lights
	this->isCloseUI = false;
	if (this->inputs[1]->getKeyOnPress(this->window, this->iSwitchInventory))
	{
		this->curserMode = !this->curserMode;
		if (this->curserMode) {
			glfwSetScrollCallback(this->window, ImGui_ImplGlfw_ScrollCallback);
			glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			isGroundTextureUI = false,isObjectTextureUI = false,this->editMode = false;
		}
		if (!this->curserMode) {
			this->isCloseUI = true;
			glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			this->firstMouse = !this->firstMouse;
		}
	}

	//Camera
	if (this->rigidBodies4D[0]->isGravity)
	{
		if (this->inputs[8]->getKeyDoublePress(this->window, this->iMoveForward, 0.25f, this->dt))
		{
			this->camera.isRuning = true;
		}
	}
	if (glfwGetKey(this->window, this->iMoveForward) == GLFW_PRESS)
	{
		this->camera.move(this->dt,FORWARD,this->rigidBodies4D[0]);
	}
	if (this->inputs[8]->getKeyOnRelease(this->window, this->iMoveForward))
	{
		this->camera.isRuning = false;
	}
	if (glfwGetKey(this->window, this->iMoveBackward) == GLFW_PRESS)
	{
		this->camera.move(this->dt, BACKWARD, this->rigidBodies4D[0]);
	}
	if (glfwGetKey(this->window, this->iMoveLeft) == GLFW_PRESS)
	{
		this->camera.move(this->dt, LEFT, this->rigidBodies4D[0]);
	}
	if (glfwGetKey(this->window, this->iMoveRight) == GLFW_PRESS)
	{
		this->camera.move(this->dt, RIGHT, this->rigidBodies4D[0]);
	}
	if (!this->rigidBodies4D[0]->isGravity)
	{
		if (glfwGetKey(this->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			this->camera.jump(this->dt, DOWN, this->rigidBodies4D[0]);
		}
	}
	else
	{
		if (this->inputs[11]->getKeyOnPress(this->window, GLFW_KEY_LEFT_SHIFT))
		{
			this->camera.isCrouch = true;
			this->rigidBodies4D[0]->position4D.y -= 0.425;
			this->rigidBodies4D[0]->scale4D.z = 0.9f;
		}
		if (this->inputs[11]->getKeyOnRelease(this->window, GLFW_KEY_LEFT_SHIFT))
		{
			this->camera.isCrouch = false;
			this->rigidBodies4D[0]->position4D.y += 0.425;
			this->rigidBodies4D[0]->scale4D.z = 1.75f;
		}
	}
	if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		this->camera.jump(this->dt, UP, this->rigidBodies4D[0]);
	}
	if (!this->camera.isCrouch)
	{
		if (this->inputs[0]->getKeyDoublePress(this->window, GLFW_KEY_SPACE, 0.25f, this->dt))
		{
			this->rigidBodies4D[0]->isGravity = !this->rigidBodies4D[0]->isGravity;
		}
	}
	if (glfwGetKey(this->window, this->iMoveAna) == GLFW_PRESS)
	{
		this->camera.move(this->dt, ANA, this->rigidBodies4D[0]);
	}
	if (glfwGetKey(this->window, this->iMoveKata) == GLFW_PRESS)
	{
		this->camera.move(this->dt, KATA, this->rigidBodies4D[0]);
	}
	this->camera.update_camera(this->rigidBodies4D[0],this->dt);
	if (this->inputs[4]->getKeyOnPress(this->window, this->iTurnDirection))
	{
		int dir;
		if (cameraDirText == 'W')
		{
			this->camera.fit_direction(dir = 0);
		}
		if (cameraDirText == 'X')
		{
			this->camera.fit_direction(dir = 1);
		}
		if (cameraDirText == 'Y')
		{
			this->camera.fit_direction(dir = 2);
		}
		if (cameraDirText == 'Z')
		{
			this->camera.fit_direction(dir = 3);
		}
		if (dir == 0)
		{
			cameraDirText = 'X';
		}
		if (dir == 1)
		{
			cameraDirText = 'Y';
		}
		if (dir == 2)
		{
			cameraDirText = 'Z';
		}
		if (dir == 3)
		{
			cameraDirText = 'W';
		}
	}
	if (this->inputs[5]->getKeyOnPress(this->window, this->iSwitchFrame))
	{
		this->isFramework = !this->isFramework;
	}
	if (this->inputs[7]->getKeyOnPress(this->window, this->iSwitchCoordinate))
	{
		this->isRenderCoordinate4D = !this->isRenderCoordinate4D;
	}
	if (glfwGetKey(this->window, this->iFovOut) == GLFW_PRESS)
	{
		this->camera.fov *= 1.f + 0.01f * 60.f * dt;
		this->camera.fov = alg::clamp(this->camera.fov, -180.f, 180.f);
		updateProjectMat(this->framebufferWidth,this->framebufferHeight);
	}
	if (glfwGetKey(this->window, this->iFovIn) == GLFW_PRESS)
	{
		this->camera.fov /= 1.f + 0.01f * 60.f * dt;
		this->camera.fov = alg::clamp(this->camera.fov, -180.f, 180.f);
		updateProjectMat(this->framebufferWidth, this->framebufferHeight);
	}

	if (!this->curserMode)
	{
		if (this->inputs[6]->getKeyOnPress(this->window, GLFW_KEY_1))this->updateModes(SELECTING, -1);
		else if (this->inputs[6]->getKeyOnPress(this->window, GLFW_KEY_2))this->updateModes(SHOOTING, -1);
		else if (this->inputs[6]->getKeyOnPress(this->window, GLFW_KEY_3))this->updateModes(CONTROLING, -1);
		else if (this->inputs[6]->getKeyOnPress(this->window, GLFW_KEY_4))this->updateModes(PAINTING, -1);
		else if (this->inputs[6]->getKeyOnPress(this->window, GLFW_KEY_5))this->updateModes(BUILDING, -1);
		else if (this->inputs[6]->getKeyOnPress(this->window, GLFW_KEY_6))this->updateModes(DELETING, -1);
		else if (this->inputs[6]->getKeyOnPress(this->window, GLFW_KEY_7))this->updateModes(AREA_DELETING, -1);
		if (this->mode == SELECTING)
		{
			if (this->inputs[2]->getMouseOnPress(this->window, GLFW_MOUSE_BUTTON_2))
			{
				ray::detect_object4d_index(this->hitIndex, this->rigidBodies4D, this->groupIndices, this->groups, this->walls4D, this->terrains4D, this->sticks4D, this->springs4D, true, true, true, true, this->camera.position4D, this->camera.forward4D, this->camera.right4D, &this->hitPosNear, &this->hitNormal);
				if (this->hitIndex->isValid)
				{
					this->curserMode = true;
					this->editMode = true;
					glfwSetScrollCallback(this->window, ImGui_ImplGlfw_ScrollCallback);
					glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
					isGroundTextureUI = false, isObjectTextureUI = false;
				}
			}
		}

		if (this->mode == SHOOTING)
		{
			if (this->shootType == 0)
			{
				if (this->inputs[2]->getMouseOnPress(this->window, GLFW_MOUSE_BUTTON_2))
				{
					ray::detect_object4d_index(this->hitIndex, this->rigidBodies4D, this->groupIndices, this->groups, this->walls4D, this->terrains4D, this->sticks4D, this->springs4D, true, true, true, true, this->camera.position4D, this->camera.forward4D, this->camera.right4D, &this->hitPosNear, &this->hitNormal);
					for (OpenDoor4D* i : this->openDoors4D)
					{
						if (i->index == this->hitIndex->n)
						{
							i->switch_state();
						}
					}
				}
				if (this->hitIndex->isValid)
				{
					if (this->hitIndex->n < this->rigidBodies4D.size())
					{
						if (this->rigidBodies4D[this->hitIndex->n]->objectName == "Glass4D")
						{
							erase_animation4D(&this->shifts4D, &this->floats4D, &this->rotates4D, &this->openDoors4D,this->hitIndex->n);
							shift_animation4D(this->shifts4D, this->floats4D, this->rotates4D, this->openDoors4D,this->hitIndex->n, -1);
							erase_joint4d(&this->sticks4D, &this->springs4D, &this->hingeConstraintsVec, this->hitIndex->n);
							shift_joint4d(this->sticks4D, this->springs4D, &this->hingeConstraintsVec, this->hitIndex->n, -1);
							erase_dynamite4d_indices(&this->dynamiteIndices, this->hitIndex->n);
							shift_dynamite4d_indices(this->dynamiteIndices, this->hitIndex->n, -1);
							this->rigidBodies4D.erase(this->rigidBodies4D.begin() + this->hitIndex->n);
							update_render_indices(this->rigidBodies4D, this->groupIndices, this->groups, this->walls4D, this->sticks4D, this->springs4D, &this->renderIndices1, &this->renderIndices2, this->camera.position4D);
							sort_render_indices(&this->renderIndices1); sort_render_indices(&this->renderIndices2);
							update_collide_indices(this->rigidBodies4D, this->groupIndices, this->groups, this->walls4D);
							this->sounds[8]->play(alg::length(this->camera.position4D - this->rigidBodies4D[this->hitIndex->n]->position4D), this->soundVolume);
						}
						else {
							glm::vec4 force4D(45000.f * this->dt * normalize(this->camera.forward4D));
							this->rigidBodies4D[this->hitIndex->n]->forceSystems4D.push_back(new ForceSystem4D(force4D, world_pos_to_body(this->rigidBodies4D[this->hitIndex->n], this->hitPosNear)));
							this->rigidBodies4D[0]->forceSystems4D.push_back(new ForceSystem4D(-force4D, glm::vec4(0.f)));
						}
						////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						for (DynamiteIndex* d : this->dynamiteIndices)//If dynamite'size>100000 how to find the dynamite quickly?
						{
							if(d->index == this->hitIndex->n)d->isExploding=true;
						}
						////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						this->sounds[4]->play(alg::length(this->camera.position4D - this->hitPosNear), this->soundVolume);
					}
					else if (this->hitIndex->n < size_of_objects4d(this->rigidBodies4D, this->walls4D))
					{
						if (this->walls4D[this->hitIndex->n - this->rigidBodies4D.size()]->objectName == "Glass4D")
						{
							erase_joint4d(&this->sticks4D, &this->springs4D, &this->hingeConstraintsVec,this->hitIndex->n);
							shift_joint4d(this->sticks4D, this->springs4D, &this->hingeConstraintsVec, this->hitIndex->n, -1);
							erase_dynamite4d_indices(&this->dynamiteIndices, this->hitIndex->n);
							shift_dynamite4d_indices(this->dynamiteIndices,this->hitIndex->n, -1);
							this->walls4D.erase(this->walls4D.begin() + this->hitIndex->n - this->rigidBodies4D.size());
							this->groupIndices = shift_group(this->groupIndices, &this->groups, this->hitIndex->n - this->rigidBodies4D.size(), -1);
							update_render_indices(this->rigidBodies4D, this->groupIndices, this->groups, this->walls4D, this->sticks4D, this->springs4D, &this->renderIndices1, &this->renderIndices2, this->camera.position4D);
							sort_render_indices(&this->renderIndices1); sort_render_indices(&this->renderIndices2);
							update_collide_indices(this->rigidBodies4D, this->groupIndices, this->groups, this->walls4D);
							this->sounds[8]->play(alg::length(this->camera.position4D - this->hitPosNear), this->soundVolume);
						}
						for (DynamiteIndex* d : this->dynamiteIndices)
						{
							if (d->index == this->hitIndex->n)d->isExploding = true;
						}
						this->sounds[5]->play(alg::length(this->camera.position4D - this->hitPosNear), this->soundVolume);
					}
					else if (this->hitIndex->n < size_of_objects4d(this->rigidBodies4D, this->walls4D, this->sticks4D, this->springs4D))
					{
						erase_joint4d0(&this->sticks4D, &this->springs4D, this->hitIndex->n - size_of_objects4d(this->rigidBodies4D, this->walls4D));
						update_render_indices(this->rigidBodies4D, this->groupIndices, this->groups, this->walls4D, this->sticks4D, this->springs4D, &this->renderIndices1, &this->renderIndices2, this->camera.position4D);
						sort_render_indices(&this->renderIndices1); sort_render_indices(&this->renderIndices2);
						update_collide_indices(this->rigidBodies4D, this->groupIndices, this->groups, this->walls4D);
						this->sounds[8]->play(alg::length(this->camera.position4D - this->hitPosNear), this->soundVolume);
						this->sounds[5]->play(alg::length(this->camera.position4D - this->hitPosNear), this->soundVolume);
					}
					else {
						this->sounds[5]->play(alg::length(this->camera.position4D - this->hitPosNear), this->soundVolume);
					}
					this->emitters4D.push_back(new Emitter4D(1, this->hitPosNear, glm::vec4(0.f), 2.f));
					//std::cout << this->hitPosNear.y << "\n";
					this->hitIndex->isValid = false;
				}
			}
			else if (this->shootType == 1)
			{
				if (this->inputs[2]->getMouseOnPress(this->window, GLFW_MOUSE_BUTTON_2))
				{
					this->xRays4D.push_back(new XRay4D());
				}
				else if (this->inputs[2]->getMouseOnRelease(this->window, GLFW_MOUSE_BUTTON_2))
				{
					this->xRays4D.clear();
				}
				else if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_2))
				{
					this->xRays4D[0]->update_x_ray4D(this->rigidBodies4D, this->groupIndices, this->groups, this->walls4D, this->terrains4D, this->sticks4D, this->springs4D, this->camera.position4D, this->camera.forward4D, this->camera.right4D, this->reflectionSteps);
				}
			}
		}

		if (this->mode == CONTROLING)
		{
			//std::cout << "this->hitIndex : " << this->hitIndex << "\n";
			if (this->controlType == DRAG || this->controlType == LUNCH || this->controlType == SOFT_DRAG || this->controlType == FROZE)
			{
				if (this->inputs[2]->getMouseOnPress(this->window, GLFW_MOUSE_BUTTON_2))
				{
					ray::detect_object4d_index(this->hitIndex, this->rigidBodies4D, this->groupIndices, this->groups, this->walls4D, this->terrains4D, this->sticks4D, this->springs4D, false,false, true, false, this->camera.position4D, this->camera.forward4D, this->camera.right4D, &this->hitPosNear, &this->hitNormal);
					if (this->hitIndex->isValid)
					{
						if (this->hitIndex->n < this->rigidBodies4D.size())
						{
							RigidBody4D* a(this->rigidBodies4D[this->hitIndex->n]);
							if (this->hitIndex->n < this->rigidBodies4D.size())
							{
								if (this->controlType == DRAG)
								{
									if (alg::length(a->position4D - this->camera.frontPosition4D) < 2.f)
									{
										a->isFrozen = false;
										a->set_position4D(this->camera.frontPosition4D);
										a->velocity4D = this->camera.frontVelocity;
										a->angularVelocity4D = alg::bivec4();
									}
								}
								else if (this->controlType == LUNCH)
								{
									if (alg::length(a->position4D - this->camera.frontPosition4D) < 2.f)
									{
										a->isFrozen = false;
										a->velocity4D = 16.f * this->camera.forward4D;
										a->angularVelocity4D = alg::bivec4();
										//this->hitIndex = -1;
									}
								}
								else if (this->controlType == SOFT_DRAG)
								{
									if (alg::length(this->hitPosNear - this->camera.frontPosition4D) < 2.f)
									{
										a->isFrozen = false;
										this->hitPosToBody = world_pos_to_body(a, this->hitPosNear);
										this->dragLines4D.clear();
										this->dragLines4D.push_back(new JointLine4D());
									}
									else
									{
										this->dragLines4D.clear();
										this->hitIndex->isValid = false;
									}
								}
								else if (this->controlType == FROZE)
								{
									if (alg::length(this->hitPosNear - this->camera.frontPosition4D) < 2.f)
									{
										a->isFrozen = true;
									}
								}
							}
						}
					}
				}
				if (this->hitIndex->isValid) {
					if (this->hitIndex->n < this->rigidBodies4D.size())
					{
						RigidBody4D* a(this->rigidBodies4D[this->hitIndex->n]);
						if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS && glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE)
						{
							if (this->isFixedTime)
							{
								if (this->controlType == DRAG)
								{
									if (alg::length(a->position4D - this->camera.frontPosition4D) < 2.f)
									{
										a->set_position4D(this->camera.frontPosition4D);
										a->velocity4D = glm::vec4(0.f);
										a->angularVelocity4D = alg::bivec4();
									}
								}
								else if (this->controlType == SOFT_DRAG)
								{
									if (alg::length(body_pos_to_world(a, this->hitPosToBody) - this->camera.frontPosition4D) < 2.f)
									{
										this->dragLines4D[0]->update_joint_line4D(body_pos_to_world(a, this->hitPosToBody), this->camera.frontPosition4D);
										glm::vec4 force4D(900.f * this->dt * (this->camera.frontPosition4D - a->position4D));
										a->forceSystems4D.push_back(new ForceSystem4D(force4D, this->hitPosToBody));
										a->velocity4D *= pow(0.25f, this->dt);
										a->angularVelocity4D =
										a->angularVelocity4D * pow(0.86f, this->dt);
										this->rigidBodies4D[0]->forceSystems4D.push_back(new ForceSystem4D(-force4D, glm::vec4(0.f)));
									}
									else
									{
										this->dragLines4D.clear();
										this->hitIndex->isValid = false;
									}
								}
								else if (this->controlType == FROZE)
								{
									//a->set_position4D(this->camera.frontPosition4D);
									this->hitIndex->isValid = false;
								}
							}
						}
						if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS && glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
						{
							if (this->isFixedTime)
							{
								if (this->controlType == DRAG)
								{
									if (alg::length(a->position4D - this->camera.frontPosition4D) < 2.f)
									{
										a->velocity4D = 4.f * this->camera.forward4D;
										this->hitIndex->isValid = false;
									}
								}
								else if (this->controlType == SOFT_DRAG)
								{
									if (alg::length(a->position4D - this->camera.frontPosition4D) < 2.f)
									{
										this->dragLines4D.clear();
										float objectMass(a->mass);
										float handMass(0.1f);
										glm::vec4 force4D(900.f * (objectMass / (objectMass + handMass)) * this->dt * this->camera.forward4D);
										a->forceSystems4D.push_back(new ForceSystem4D(force4D, glm::vec4(0.f)));
										this->rigidBodies4D[0]->forceSystems4D.push_back(new ForceSystem4D(-force4D, glm::vec4(0.f)));
									}
									else
									{
										this->dragLines4D.clear();
										this->hitIndex->isValid = false;
									}
								}
							}
						}
					}
				}
				if (this->inputs[2]->getMouseOnRelease(this->window, GLFW_MOUSE_BUTTON_2))
				{
					if (this->controlType == SOFT_DRAG)
					{
						this->dragLines4D.clear();
					}
					this->hitIndex->isValid = false;
				}
			}

			if (this->controlType == SOFT_DRAG_MULTIPLY)
			{
				if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS && glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE)
				{
					this->dragLines4D.clear();
					size_t index(0);
					for (size_t i(1); i < this->rigidBodies4D.size(); i++)
					{
						if (alg::length(this->rigidBodies4D[i]->position4D - this->camera.frontPosition4D) < 5.f)
						{
							this->rigidBodies4D[i]->isFrozen = false;
							this->dragLines4D.push_back(new JointLine4D());
							this->dragLines4D[index]->update_joint_line4D(this->rigidBodies4D[i]->position4D, this->camera.frontPosition4D);
							index++;
							glm::vec4 force4D(7.5f * (this->camera.frontPosition4D - this->rigidBodies4D[i]->position4D));
							this->rigidBodies4D[i]->forceSystems4D.push_back(new ForceSystem4D(force4D, glm::vec4(0.f)));
							this->rigidBodies4D[i]->velocity4D *= pow(0.25f, this->dt);
							this->rigidBodies4D[0]->forceSystems4D.push_back(new ForceSystem4D(-force4D, glm::vec4(0.f)));
						}
					}
				}
				if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS && glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
				{
					this->dragLines4D.clear();
					for (size_t i(1); i < this->rigidBodies4D.size(); i++)
					{
						if (alg::length(this->rigidBodies4D[i]->position4D - this->camera.frontPosition4D) < 5.f)
						{
							float objectMass(this->rigidBodies4D[i]->mass);
							float handMass(0.1f);
							glm::vec4 force4D(1028.565f * (objectMass / (objectMass + handMass)) * this->dt *this->camera.forward4D);
							this->rigidBodies4D[i]->forceSystems4D.push_back(new ForceSystem4D(force4D, glm::vec4(0.f)));
							this->rigidBodies4D[0]->forceSystems4D.push_back(new ForceSystem4D(-force4D, glm::vec4(0.f)));
						}
					}
				}
				if (this->inputs[2]->getMouseOnRelease(this->window, GLFW_MOUSE_BUTTON_2))
				{
					this->dragLines4D.clear();
				}
			}
		}
		if (this->mode == PAINTING) {
			ray::get_ray_detect_terrain_pos4D(this->camera.position4D, this->camera.forward4D, this->camera.right4D, this->groupIndices, this->groups, this->terrains4D, &this->hittingPos4D);
			this->shaders[TERRAIND4]->use();
			this->shaders[TERRAIND4]->set_vec4f(this->hittingPos4D, "hittingPos4D");
			this->shaders[TERRAIND4]->set1f(this->paintScale, "paintScale");
			if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
			{
				if (this->isHardPainting)
					this->paintType = this->paintType0 + 10;
				else
					this->paintType = this->paintType0;
				this->textures3D[BLEND]->paint_colors(this->paintType,
					glm::vec3(this->hittingPos4D.x, this->hittingPos4D.z, this->hittingPos4D.w) / (float)terrainScale,
					this->paintScale / (float)terrainScale, this->isSphericalPainting);
			}
		}
		if (this->mode == BUILDING) {

			if (glfwGetKey(this->window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(this->window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
			{
				this->hittingPos4D = get_build_position4D(this->camera.position4D, this->camera.forward4D, this->hittingPos4D, true);
			}
			else {
				if (!(this->buildMode == BUILD_STICK || this->buildMode == BUILD_SPRING))
				{
					VectorIndex hitIndex2(VectorIndex(0,false));
					ray::detect_object4d_index(&hitIndex2, this->rigidBodies4D, this->groupIndices, this->groups, this->walls4D, this->terrains4D, this->sticks4D, this->springs4D, true, true, true, true, this->camera.position4D, this->camera.forward4D, this->camera.right4D, &this->hittingPos4D, &this->hitNormal);
					this->isFindPoint = hitIndex2.isValid;
					if (this->isFindPoint &&hitIndex2.n < size_of_objects4d(this->rigidBodies4D, this->walls4D, this->sticks4D, this->springs4D)) { this->hitObject4D = find_object4d(this->rigidBodies4D, this->walls4D, this->sticks4D, this->springs4D, hitIndex2.n); }
					else { this->hitObject4D = nullptr; }
					this->hittingPos4D = get_build_position4D(this->camera.position4D, this->camera.forward4D, this->hittingPos4D, false);
				}
			}
			if (!(this->buildMode == BUILD_STICK || this->buildMode == BUILD_SPRING))
			{
				this->shaders[TERRAIND4]->use();
				this->shaders[TERRAIND4]->set_vec4f(this->hittingPos4D, "hittingPos4D");
			}

			if (this->inputs[2]->getMouseOnPress(this->window, GLFW_MOUSE_BUTTON_2))
			{
				if (this->isRandomColor)
				{
					this->buildColor = glm::vec4(rand() % 256, rand() % 256, rand() % 256, 256.f) / 256.f;
				}
				if (this->isFindPoint) {
					//if (this->buildMode == BUILD_WALL)
					//{
					//	shift_animation4D(this->shifts4D, this->floats4D,this->rotates4D, this->rigidBodies4D.size() + size_of_walls4d(this->groups), 1);
					//	shift_joint4d(this->sticks4D, this->springs4D, this->hingeConstraintsVec, this->rigidBodies4D.size() + size_of_walls4d(this->groups), 1);
					//	this->walls4D.push_back(new Wall4D("Hypercube", Hypercube(get_wall_build_scale4D()), get_wall_build_position4D(this->hittingPos4D), alg::bivec4(), get_wall_build_scale4D(), 1.6f, 0.25f, true, this->wallTexs3D[this->buildTexture],0.f, this->buildColor, BOX4D, this->shaders[this->buildShader]));
					//	this->groups = pack_group(this->groups, &this->walls4D, &this->terrains4D);
					//}
					switch (this->buildMode)
					{
					case BUILD_OBJECT: 
					{ 
						glm::vec4 buildPos(this->hitObject4D == nullptr ? get_cap_position4D(this->hittingPos4D + this->buildScale.y * this->hitNormal / 2.f, this->buildDistance, this->buildOffset) : get_cap_position4D(hitObject4D,isFindPoint, this->hittingPos4D + this->buildScale.y * this->hitNormal / 2.f, this->buildDistance, this->buildOffset));
						alg::rotor4 buildRot(this->hitObject4D ==nullptr?alg::rotor4():update(this->hitObject4D->rotation4D, this->buildRotation * glm::radians(1.f)));
						//shift_animation4D(this->shifts4D, this->floats4D, this->rotates4D, this->openDoors4D, size_of_objects4d(this->rigidBodies4D, this->walls4D), 1);
						//shift_joint4d(this->sticks4D, this->springs4D, &this->hingeConstraintsVec, size_of_objects4d(this->rigidBodies4D, this->walls4D), 1);
						//shift_dynamite4d_indices(this->dynamiteIndices, size_of_objects4d(this->rigidBodies4D, this->walls4D), 1);
						switch (this->buildCol)
						{
						case HYPERCUBE: { this->walls4D.push_back(new Wall4D(this->buildTag, Hypercube(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, BOX4D, this->buildShader)); break; }
						case HYPERSPHERE: { this->walls4D.push_back(new Wall4D(this->buildTag, Hypersphere(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, SPHERE4D, this->buildShader)); break; }
						case HYPERCAPSULE: { this->walls4D.push_back(new Wall4D(this->buildTag, Hypercapsule(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, CAPSULE4D, this->buildShader)); break; }
						case HYPERCYLINDER: { this->walls4D.push_back(new Wall4D(this->buildTag, Hypercylinder(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case HYPERCONE: { this->walls4D.push_back(new Wall4D(this->buildTag, Hypercone(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case HYPERPOT: { this->walls4D.push_back(new Wall4D(this->buildTag, Hyperpot(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case TRIPRISM: { this->walls4D.push_back(new Wall4D(this->buildTag, TriPrism(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case HYPERSLOPE: { this->walls4D.push_back(new Wall4D(this->buildTag, Hyperslope(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case HYPERQUAD: { this->walls4D.push_back(new Wall4D(this->buildTag, DoubleQuads4d(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case PENTACHORON: { this->walls4D.push_back(new Wall4D(this->buildTag, Pentachoron(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case HYPERPYRAMID: { this->walls4D.push_back(new Wall4D(this->buildTag, Pyramid4D(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case HEXADECACHORON: { this->walls4D.push_back(new Wall4D(this->buildTag, Hexadecachoron(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case HEXACOSICHORON: { this->walls4D.push_back(new Wall4D(this->buildTag, Hexacosichoron(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						}
						add_wall4d_to_group(&this->groups, this->walls4D[this->walls4D.size() - 1], this->walls4D.size() - 1);
						this->sounds[7]->play(alg::length(this->camera.position4D - this->hittingPos4D), this->soundVolume);
						break; 
					}
					case BUILD_RIGIDBODY:
					{
						shift_animation4D(this->shifts4D, this->floats4D, this->rotates4D, this->openDoors4D,this->rigidBodies4D.size(), 1);
						shift_joint4d(this->sticks4D, this->springs4D, &this->hingeConstraintsVec, this->rigidBodies4D.size(), 1);
						shift_dynamite4d_indices(this->dynamiteIndices, this->rigidBodies4D.size(), 1);
						glm::vec4 buildPos(this->hittingPos4D + this->buildScale.y * this->hitNormal / 2.f);
						alg::rotor4 buildRot(look_at(glm::vec4(0.f), this->hitNormal, rotate(this->buildRotation, glm::vec4(0.f, 1.f, 0.f, 0.f))));
						switch (this->buildCol)
						{
						case HYPERCUBE: { this->rigidBodies4D.push_back(new RigidBody4D(this->buildTag, Hypercube(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, BOX4D, this->buildShader)); break; }
						case HYPERSPHERE: { this->rigidBodies4D.push_back(new RigidBody4D(this->buildTag, Hypersphere(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, SPHERE4D, this->buildShader)); break; }
						case HYPERCAPSULE: { this->rigidBodies4D.push_back(new RigidBody4D(this->buildTag, Hypercapsule(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, CAPSULE4D, this->buildShader)); break; }
						case HYPERCYLINDER: { this->rigidBodies4D.push_back(new RigidBody4D(this->buildTag, Hypercylinder(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case HYPERCONE: { this->rigidBodies4D.push_back(new RigidBody4D(this->buildTag, Hypercone(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case HYPERPOT: { this->rigidBodies4D.push_back(new RigidBody4D(this->buildTag, Hyperpot(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case TRIPRISM: { this->rigidBodies4D.push_back(new RigidBody4D(this->buildTag, TriPrism(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case HYPERSLOPE: { this->rigidBodies4D.push_back(new RigidBody4D(this->buildTag, Hyperslope(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case HYPERQUAD: { this->rigidBodies4D.push_back(new RigidBody4D(this->buildTag, DoubleQuads4d(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case PENTACHORON: { this->rigidBodies4D.push_back(new RigidBody4D(this->buildTag, Pentachoron(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case HYPERPYRAMID: { this->rigidBodies4D.push_back(new RigidBody4D(this->buildTag, Pyramid4D(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case HEXADECACHORON: { this->rigidBodies4D.push_back(new RigidBody4D(this->buildTag, Hexadecachoron(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case HEXACOSICHORON: { this->rigidBodies4D.push_back(new RigidBody4D(this->buildTag, Hexacosichoron(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						}
						if (this->isIlluminate)
						{
							this->pointLights4D.push_back(new PointLight4D(PARTICLE1, buildPos, new VectorIndex(this->rigidBodies4D.size() - 1,true), this->pointLights4D.size(), this->lightIntensity, this->lightColor, this->lightRadius));
							update_point_light4d(this->pointLights4D, this->shaders[WALLD4], this->shaders[TERRAIND4], this->shaders[LIGHT_MAPD3]);
							this->lightMap3D->bind_image(0);
							glDispatchCompute(4, 128, 4);
							glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
							this->sounds[7]->play(alg::length(this->camera.position4D - this->hittingPos4D), this->soundVolume);
						}
						break;
					}
					case BUILD_POOL_TABLE:
					{
						//shift_animation4D(this->shifts4D, this->floats4D, this->rotates4D, this->openDoors4D,size_of_objects4d(this->rigidBodies4D, this->walls4D), 34);
						//shift_joint4d(this->sticks4D, this->springs4D, &this->hingeConstraintsVec, size_of_objects4d(this->rigidBodies4D, this->walls4D), 34);
						//shift_dynamite4d_indices(this->dynamiteIndices, size_of_objects4d(this->rigidBodies4D, this->walls4D), 34);
						generate_pool_table4D(get_cap_position4D(this->hittingPos4D, this->buildDistance, this->buildOffset), glm::vec4(1.27f, 1.27f, 2.54f, 1.27f), 1.f, true, WOODX, true, GRASS, true, WOODY, &this->walls4D, this->buildShader);
						for (size_t i(0); i < 34;i++)add_wall4d_to_group(&this->groups, this->walls4D[this->walls4D.size() - 1 - i], this->walls4D.size() - 1 - i);
						this->sounds[7]->play(alg::length(this->camera.position4D - this->hittingPos4D), this->soundVolume);
						break;
					}
					case BUILD_BILLIARD:
					{
						shift_animation4D(this->shifts4D, this->floats4D, this->rotates4D, this->openDoors4D,this->rigidBodies4D.size(), 1);
						shift_joint4d(this->sticks4D, this->springs4D, &this->hingeConstraintsVec, this->rigidBodies4D.size(), 1);
						shift_dynamite4d_indices(this->dynamiteIndices, this->rigidBodies4D.size(), 1);
						generate_billiard4D(this->hittingPos4D + glm::vec4(0.f, 0.0525f / 2.f, 0.f, 0.f), this->initialVelocity, this->initialAngularVelocity, this->buildTexture, &this->rigidBodies4D, this->isGravity, this->buildColor,this->buildMetalColor, this->buildShader);
						if (this->isIlluminate)
						{
							this->pointLights4D.push_back(new PointLight4D(PARTICLE1, this->hittingPos4D, new VectorIndex(this->rigidBodies4D.size() - 1, true), this->pointLights4D.size(), this->lightIntensity, this->lightColor, this->lightRadius));
							update_point_light4d(this->pointLights4D, this->shaders[WALLD4], this->shaders[TERRAIND4], this->shaders[LIGHT_MAPD3]);
							this->lightMap3D->bind_image(0);
							glDispatchCompute(4, 128, 4);
							glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
						}
						this->sounds[7]->play(alg::length(this->camera.position4D - this->hittingPos4D), this->soundVolume);
						break;
					}
					case BUILD_DYNAMITE:
					{
						if (this->isRigidBody)
						{
							shift_animation4D(this->shifts4D, this->floats4D, this->rotates4D, this->openDoors4D,this->rigidBodies4D.size(), 1);
							shift_joint4d(this->sticks4D, this->springs4D, &this->hingeConstraintsVec, this->rigidBodies4D.size(), 1);
							shift_dynamite4d_indices(this->dynamiteIndices, this->rigidBodies4D.size(), 1);
							generate_dynamite4D(this->hittingPos4D, this->initialVelocity, this->initialAngularVelocity, WHITECONCRETE, &this->rigidBodies4D, &this->dynamiteIndices, this->isGravity,this->buildShader);
							this->rigidBodies4D[this->rigidBodies4D.size() - 1]->componentsVector[DYNAMITE4D].push_back(this->dynamiteIndices.size()-1);
							if (this->isIlluminate)
							{
								this->pointLights4D.push_back(new PointLight4D(PARTICLE1, this->hittingPos4D, new VectorIndex(this->rigidBodies4D.size() - 1, true), this->pointLights4D.size(), this->lightIntensity, this->lightColor, this->lightRadius));
								update_point_light4d(this->pointLights4D, this->shaders[WALLD4], this->shaders[TERRAIND4], this->shaders[LIGHT_MAPD3]);
								this->lightMap3D->bind_image(0);
								glDispatchCompute(4, 128, 4);
								glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
							}
							this->sounds[7]->play(alg::length(this->camera.position4D - this->hittingPos4D), this->soundVolume);
						}
						else
						{
							//shift_animation4D(this->shifts4D, this->floats4D, this->rotates4D, this->openDoors4D,size_of_objects4d(this->rigidBodies4D, this->walls4D), 1);
							//shift_joint4d(this->sticks4D, this->springs4D, &this->hingeConstraintsVec, size_of_objects4d(this->rigidBodies4D, this->walls4D), 1);
							//shift_dynamite4d_indices(this->dynamiteIndices, size_of_objects4d(this->rigidBodies4D, this->walls4D), 1);
							generate_dynamite4D(this->hittingPos4D, WHITECONCRETE, &this->rigidBodies4D, &this->walls4D, &this->dynamiteIndices, this->buildShader);
							this->walls4D[this->rigidBodies4D.size() - 1]->componentsVector[DYNAMITE4D].push_back(this->dynamiteIndices.size() - 1);
							add_wall4d_to_group(&this->groups, this->walls4D[this->walls4D.size() - 1], this->walls4D.size() - 1);
							this->sounds[7]->play(alg::length(this->camera.position4D - this->hittingPos4D), this->soundVolume);
						}
						break;
					}
					}
				}
				if (this->buildMode == BUILD_STICK)
				{
					ray::detect_object4d_index(this->hitIndex, this->rigidBodies4D, this->groupIndices, this->groups, this->walls4D, this->terrains4D, this->sticks4D, this->springs4D, true, false, true, false, this->camera.position4D, this->camera.forward4D, this->camera.right4D, &this->hitPosNear, &this->hitNormal);
					if (this->hitIndex->isValid)
					{
						if (this->hitIndex->n < size_of_objects4d(this->rigidBodies4D, this->walls4D))
						{
							if (find_object4d(this->rigidBodies4D, this->walls4D, this->hitIndex->n)->objectName != "Ground")
							{
								bool isInitial(true);
								if (this->springs4D.size() != 0)
								{
									if ((!this->springs4D[this->springs4D.size() - 1]->index2->isValid) && this->springs4D[this->springs4D.size() - 1]->index1 != this->hitIndex->n)
									{
										isInitial = false;
										*this->springs4D[this->springs4D.size() - 1]->index2 = *this->hitIndex;
										this->sounds[7]->play(alg::length(this->camera.position4D - this->hittingPos4D), this->soundVolume);
									}
								}
								if (isInitial)
								{
									int size(this->sticks4D.size());
									if (size == 0)
									{
										this->sticks4D.push_back(new Stick4D(glm::vec4(0.f), this->hitIndex->n, new VectorIndex(0, false), this->stickLength, WHITECONCRETE, this->buildColor, this->buildShader));
										this->sounds[7]->play(alg::length(this->camera.position4D - this->hittingPos4D), this->soundVolume);
									}
									else
									{
										if (this->sticks4D[size - 1]->index2->isValid)
										{
											this->sticks4D.push_back(new Stick4D(glm::vec4(0.f), this->hitIndex->n, new VectorIndex(0, false), this->stickLength, WHITECONCRETE, this->buildColor, this->buildShader));
											this->sounds[7]->play(alg::length(this->camera.position4D - this->hittingPos4D), this->soundVolume);
										}
										else if ((!this->sticks4D[size - 1]->index2->isValid) && this->sticks4D[size - 1]->index1 != this->hitIndex->n)
										{
											*this->sticks4D[size - 1]->index2 = *this->hitIndex;
											this->sounds[7]->play(alg::length(this->camera.position4D - this->hittingPos4D), this->soundVolume);
										}
									}
								}
							}
						}
					}
				}
				else
					if (this->buildMode == BUILD_SPRING)
					{
						ray::detect_object4d_index(this->hitIndex, this->rigidBodies4D, this->groupIndices, this->groups, this->walls4D, this->terrains4D, this->sticks4D, this->springs4D, true, false, true, false, this->camera.position4D, this->camera.forward4D, this->camera.right4D, &this->hitPosNear, &this->hitNormal);
						if (this->hitIndex->isValid)
						{
							if (this->hitIndex->n < size_of_objects4d(this->rigidBodies4D, this->walls4D))
							{
								if (find_object4d(this->rigidBodies4D, this->walls4D, this->hitIndex->n)->objectName != "Ground")
								{
									bool isInitial(true);
									if (this->sticks4D.size() != 0)
									{
										if ((!this->sticks4D[this->sticks4D.size() - 1]->index2->isValid) && this->sticks4D[this->sticks4D.size() - 1]->index1 != this->hitIndex->n)
										{
											isInitial = false;
											*this->sticks4D[this->sticks4D.size() - 1]->index2 = *this->hitIndex;
											this->sounds[7]->play(alg::length(this->camera.position4D - this->hittingPos4D), this->soundVolume);
										}
									}
									if (isInitial)
									{
										int size(this->springs4D.size());
										if (size == 0)
										{
											this->springs4D.push_back(new Spring4D(glm::vec4(0.f), this->hitIndex->n, new VectorIndex(0, false), this->springLength, this->springStrength, STONE, this->buildColor, this->buildShader));
											this->sounds[7]->play(alg::length(this->camera.position4D - this->hittingPos4D), this->soundVolume);
										}
										else
										{
											if (this->springs4D[size - 1]->index2->isValid)
											{
												this->springs4D.push_back(new Spring4D(glm::vec4(0.f), this->hitIndex->n, new VectorIndex(0, false), this->springLength, this->springStrength, STONE, this->buildColor, this->buildShader));
												this->sounds[7]->play(alg::length(this->camera.position4D - this->hittingPos4D), this->soundVolume);
											}
											else if ((!this->springs4D[size - 1]->index2->isValid) && this->springs4D[size - 1]->index1 != this->hitIndex->n)
											{
												*this->springs4D[size - 1]->index2 = *this->hitIndex;
												this->sounds[7]->play(alg::length(this->camera.position4D - this->hittingPos4D), this->soundVolume);
											}
										}
									}
								}
							}
						}
					}
				judge_objects(this->groupIndices, this->groups, this->walls4D, this->terrains4D, this->camera.position4D, this->camera.forward4D, this->camera.wDir, this->objectLoadDistance);
				update_render_indices(this->rigidBodies4D, this->groupIndices, this->groups, this->walls4D, this->sticks4D, this->springs4D, &this->renderIndices1, &this->renderIndices2, this->camera.position4D);
				sort_render_indices(&this->renderIndices1); sort_render_indices(&this->renderIndices2);
				update_collide_indices(this->rigidBodies4D, this->groupIndices, this->groups, this->walls4D);
			}
			if (this->buildMode == BUILD_STICK)
			{
				if (this->sticks4D.size() != 0) {
					if (!this->sticks4D[this->sticks4D.size() - 1]->index2->isValid) {
						if (this->inputs[9]->getKeyOnPress(this->window, GLFW_KEY_DELETE)) {
							this->sticks4D.erase(this->sticks4D.begin() + this->sticks4D.size() - 1);
						}
					}
				}
			}
			else
				if (this->buildMode == BUILD_SPRING)
				{
					if (this->springs4D.size() != 0) {
						if (!this->springs4D[this->springs4D.size() - 1]->index2->isValid) {
							if (this->inputs[9]->getKeyOnPress(this->window, GLFW_KEY_DELETE)) {
								this->springs4D.erase(this->springs4D.begin() + this->springs4D.size() - 1);
							}
						}
					}
				}
		}
		if (this->mode == DELETING)
		{
			if (this->inputs[2]->getMouseOnPress(this->window, GLFW_MOUSE_BUTTON_2))
			{
				ray::detect_object4d_index(this->hitIndex, this->rigidBodies4D, this->groupIndices, this->groups, this->walls4D, this->terrains4D, this->sticks4D, this->springs4D, true, true,true, false, this->camera.position4D, this->camera.forward4D, this->camera.right4D, &this->hitPosNear, &this->hitNormal);
				if (this->hitIndex->isValid)
				{
					if (this->hitIndex->n < this->rigidBodies4D.size())
					{
						erase_animation4D(&this->shifts4D, &this->floats4D, &this->rotates4D, &this->openDoors4D,this->hitIndex->n);
						shift_animation4D(this->shifts4D, this->floats4D, this->rotates4D, this->openDoors4D,this->hitIndex->n, -1);
						erase_joint4d(&this->sticks4D, &this->springs4D, &this->hingeConstraintsVec, this->hitIndex->n);
						shift_joint4d(this->sticks4D, this->springs4D, &this->hingeConstraintsVec, this->hitIndex->n, -1);
						erase_dynamite4d_indices(&this->dynamiteIndices, this->hitIndex->n);
						shift_dynamite4d_indices(this->dynamiteIndices, this->hitIndex->n, -1);
						size_t pointLightSize(this->pointLights4D.size());
						erase_point_light4d(&this->pointLights4D, this->shaders[WALLD4], this->shaders[TERRAIND4], this->shaders[LIGHT_MAPD3], this->hitIndex->n);
						if (pointLightSize != this->pointLights4D.size())
						{
							shift_point_light4d(this->pointLights4D, this->hitIndex->n, -1);
							this->shaders[LIGHT_MAPD3]->use();
							this->lightMap3D->bind_image(0);
							glDispatchCompute(4, 128, 4);
							glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
						}
						this->rigidBodies4D.erase(this->rigidBodies4D.begin() + this->hitIndex->n);
					}
					else if (this->hitIndex->n < size_of_objects4d(this->rigidBodies4D, this->walls4D))
					{
						if (this->walls4D[this->hitIndex->n - this->rigidBodies4D.size()]->objectName != "Ground")
						{
							erase_joint4d(&this->sticks4D, &this->springs4D, &this->hingeConstraintsVec, this->hitIndex->n);
							shift_joint4d(this->sticks4D, this->springs4D, &this->hingeConstraintsVec, this->hitIndex->n, -1);
							erase_dynamite4d_indices(&this->dynamiteIndices, this->hitIndex->n);
							shift_dynamite4d_indices(this->dynamiteIndices, this->hitIndex->n, -1);
							this->walls4D.erase(this->walls4D.begin() + this->hitIndex->n - this->rigidBodies4D.size());
							this->groupIndices = shift_group(this->groupIndices, &this->groups, this->hitIndex->n - this->rigidBodies4D.size(), -1);
						}
					}
					else if (this->hitIndex->n < size_of_objects4d(this->rigidBodies4D, this->walls4D, this->sticks4D, this->springs4D))
					{
						erase_joint4d0(&this->sticks4D, &this->springs4D, this->hitIndex->n - size_of_objects4d(this->rigidBodies4D, this->walls4D));
					}
					update_render_indices(this->rigidBodies4D, this->groupIndices, this->groups, this->walls4D, this->sticks4D, this->springs4D, &this->renderIndices1, &this->renderIndices2, this->camera.position4D);
					sort_render_indices(&this->renderIndices1); sort_render_indices(&this->renderIndices2);
					update_collide_indices(this->rigidBodies4D, this->groupIndices, this->groups, this->walls4D);
					this->hitIndex->isValid = false;
				}
			}
		}
		if (this->mode == AREA_DELETING)
		{
			if (this->inputs[2]->getMouseOnPress(this->window, GLFW_MOUSE_BUTTON_2))
			{
				ray::detect_object4d_index(nullptr, this->rigidBodies4D, this->groupIndices, this->groups, this->walls4D, this->terrains4D, this->sticks4D, this->springs4D, true, true,true, true, this->camera.position4D, this->camera.forward4D, this->camera.right4D, &this->hittingPos4D, &this->hitNormal);
			}
			if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
			{
				glm::vec4 endPos;
				glm::vec4 normal;
				ray::detect_object4d_index(nullptr, this->rigidBodies4D, this->groupIndices, this->groups, this->walls4D, this->terrains4D, this->sticks4D, this->springs4D, true, true, true, true, this->camera.position4D, this->camera.forward4D, this->camera.right4D, &endPos, &normal);
				this->deleteMap3D->washArea();
				this->deleteMap3D->selectArea(glm::vec3(this->hittingPos4D.x, this->hittingPos4D.z, this->hittingPos4D.w),
					glm::vec3(endPos.x, endPos.z, endPos.w));
			}
			if (this->inputs[3]->getMouseOnRelease(this->window, GLFW_MOUSE_BUTTON_2))
			{
				this->deleteMap3D->getImageData();
			}
			if (this->inputs[9]->getKeyOnPress(this->window, GLFW_KEY_DELETE)) {
				this->area_delete();
			}
		}
	}
}