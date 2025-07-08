#include"Game.h"

void Game::updateKeyboardInput()
{
	//Program
	if (this->inputs[12]->getKeyOnPress(this->window, GLFW_KEY_ESCAPE)) {
		if (this->pageType == REGULAR)
		{
			glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			isGroundTextureUI = false, isObjectTextureUI = false, this->editMode = false;
			this->pageType = EXIT;
		}
		else if (this->pageType == EXIT)
		{
			glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			this->firstMouse = !this->firstMouse;
			this->pageType = REGULAR;
		}
		else if (this->pageType == LEVELS)
		{
			this->pageType = START_MENU;
		}
		else if (this->pageType == GOALS)
		{
			this->pageType = START_MENU;
		}
		else if (this->pageType == SETTINGS)
		{
			this->pageType = START_MENU;
		}
	}
	if (this->inputs[13]->getKeyOnPress(this->window, GLFW_KEY_F3)) {
		this->isDebug = !this->isDebug;
	}
	if (this->inputs[10]->getKeyOnPress(this->window, GLFW_KEY_F2)){
		SYSTEMTIME systemTime;
		GetLocalTime(&systemTime);
		char ss[256];
		snprintf(ss, 255, "resourcefile/screenshots/%i %02i %02i %02i %02i %02i.png", systemTime.wYear, systemTime.wMonth, systemTime.wDay, systemTime.wHour, systemTime.wMinute, systemTime.wSecond);
		SOIL_save_screenshot(ss, SOIL_SAVE_TYPE_PNG, 0, 0, this->framebufferWidth, this->framebufferHeight);
	}

	//Set and remove lights
	this->isCloseUI = false;
	if (this->inputs[1]->getKeyOnPress(this->window, this->iSwitchInventory)){
		if (this->pageType == REGULAR)
		{
			glfwSetScrollCallback(this->window, ImGui_ImplGlfw_ScrollCallback);
			glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			isGroundTextureUI = false, isObjectTextureUI = false, this->editMode = false;

			this->pageType = IMGUI;
		}
		else if (this->pageType == IMGUI)
		{
			this->isCloseUI = true;
			glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			this->firstMouse = !this->firstMouse;

			this->pageType = REGULAR;
		}
	}

	//Camera
	if (this->pageType == REGULAR)
	{
		if (this->rigidBodies4d[0]->isGravity) {
			this->rigidBodies4d[0]->mu = 5.7143f;
			if (this->inputs[8]->getKeyDoublePress(this->window, this->iMoveForward, 0.25f, this->dt)) {
				this->camera.isRuning = true;
			}
		}
		if (glfwGetKey(this->window, this->iMoveForward) == GLFW_PRESS) {
			this->camera.move(this->dt, FORWARD, this->rigidBodies4d[0]);
		}
		if (this->inputs[8]->getKeyOnRelease(this->window, this->iMoveForward)) {
			this->camera.isRuning = false;
		}
		if (glfwGetKey(this->window, this->iMoveBackward) == GLFW_PRESS) {
			this->camera.move(this->dt, BACKWARD, this->rigidBodies4d[0]);
		}
		if (glfwGetKey(this->window, this->iMoveLeft) == GLFW_PRESS) {
			this->camera.move(this->dt, LEFT, this->rigidBodies4d[0]);
		}
		if (glfwGetKey(this->window, this->iMoveRight) == GLFW_PRESS) {
			this->camera.move(this->dt, RIGHT, this->rigidBodies4d[0]);
		}
		if (!this->rigidBodies4d[0]->isGravity) {
			if (glfwGetKey(this->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
				this->camera.jump(this->dt, DOWN, this->rigidBodies4d[0]);
			}
		}
		else
		{
			if (this->inputs[11]->getKeyOnPress(this->window, GLFW_KEY_LEFT_SHIFT)) {
				this->camera.isCrouch = true;
				this->rigidBodies4d[0]->position4d.y -= 0.425;
				this->rigidBodies4d[0]->scale4D.z = 0.9f;
			}
			if (this->inputs[11]->getKeyOnRelease(this->window, GLFW_KEY_LEFT_SHIFT)) {
				this->camera.isCrouch = false;
				this->rigidBodies4d[0]->position4d.y += 0.425;
				this->rigidBodies4d[0]->scale4D.z = 1.75f;
			}
		}
		if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			this->camera.jump(this->dt, UP, this->rigidBodies4d[0]);
		}
		if (!this->camera.isCrouch) {
			if (this->inputs[0]->getKeyDoublePress(this->window, GLFW_KEY_SPACE, 0.25f, this->dt)) {
				this->rigidBodies4d[0]->isGravity = !this->rigidBodies4d[0]->isGravity;
			}
		}
		if (glfwGetKey(this->window, this->iMoveAna) == GLFW_PRESS) {
			this->camera.move(this->dt, ANA, this->rigidBodies4d[0]);
		}
		if (glfwGetKey(this->window, this->iMoveKata) == GLFW_PRESS) {
			this->camera.move(this->dt, KATA, this->rigidBodies4d[0]);
		}
	}
	this->camera.update_camera(this->rigidBodies4d[0],this->dt);
	if (this->pageType == REGULAR)
	{
		if (this->inputs[4]->getKeyOnPress(this->window, this->iTurnDirection)) {
			int dir;
			if (cameraDirText == 'W') {
				this->camera.fit_direction(dir = 0);
			}
			if (cameraDirText == 'X') {
				this->camera.fit_direction(dir = 1);
			}
			if (cameraDirText == 'Y') {
				this->camera.fit_direction(dir = 2);
			}
			if (cameraDirText == 'Z') {
				this->camera.fit_direction(dir = 3);
			}
			if (dir == 0) {
				cameraDirText = 'X';
			}
			if (dir == 1) {
				cameraDirText = 'Y';
			}
			if (dir == 2) {
				cameraDirText = 'Z';
			}
			if (dir == 3) {
				cameraDirText = 'W';
			}
		}
	}
	if (this->inputs[5]->getKeyOnPress(this->window, this->iSwitchFrame)){
		this->isFramework = !this->isFramework;
	}
	if (this->inputs[7]->getKeyOnPress(this->window, this->iSwitchCoordinate)){
		this->isRenderCoordinate4d = !this->isRenderCoordinate4d;
	}
	if (glfwGetKey(this->window, this->iFovOut) == GLFW_PRESS){
		this->camera.fov *= 1.f + 0.01f * 60.f * dt;
		this->camera.fov = alg::clamp(this->camera.fov, -180.f, 180.f);
		updateProjectMat(this->framebufferWidth,this->framebufferHeight);
	}
	if (glfwGetKey(this->window, this->iFovIn) == GLFW_PRESS){
		this->camera.fov /= 1.f + 0.01f * 60.f * dt;
		this->camera.fov = alg::clamp(this->camera.fov, -180.f, 180.f);
		updateProjectMat(this->framebufferWidth, this->framebufferHeight);
	}

	if (this->pageType == REGULAR){
		if (this->inputs[6]->getKeyOnPress(this->window, GLFW_KEY_1))this->update_scroll_input(SELECTING, -1);
		else if (this->inputs[6]->getKeyOnPress(this->window, GLFW_KEY_2))this->update_scroll_input(SHOOTING, -1);
		else if (this->inputs[6]->getKeyOnPress(this->window, GLFW_KEY_3))this->update_scroll_input(CONTROLING, -1);
		else if (this->inputs[6]->getKeyOnPress(this->window, GLFW_KEY_4))this->update_scroll_input(PAINTING, -1);
		else if (this->inputs[6]->getKeyOnPress(this->window, GLFW_KEY_5))this->update_scroll_input(BUILDING, -1);
		else if (this->inputs[6]->getKeyOnPress(this->window, GLFW_KEY_6))this->update_scroll_input(DELETING, -1);
		else if (this->inputs[6]->getKeyOnPress(this->window, GLFW_KEY_7))this->update_scroll_input(AREA_DELETING, -1);
		if (this->mode == SELECTING){
			if (this->inputs[2]->getMouseOnPress(this->window, GLFW_MOUSE_BUTTON_2)){
				ray::detect_object4d_index(&this->hitIndex, this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d, this->terrains4d, this->sticks4d, this->springs4d, true, true, true, true, this->camera.position4d, this->camera.forward4D, this->camera.right4D, &this->hitPosNear, &this->hitNormal);
				if (this->hitIndex.isValid){
					this->pageType = IMGUI;
					this->editMode = true;
					glfwSetScrollCallback(this->window, ImGui_ImplGlfw_ScrollCallback);
					glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
					isGroundTextureUI = false, isObjectTextureUI = false;
				}
			}
		}

		if (this->mode == SHOOTING){
			if (this->shootType == 0){
				if (this->inputs[2]->getMouseOnPress(this->window, GLFW_MOUSE_BUTTON_2)){
					ray::detect_object4d_index(&this->hitIndex, this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d, this->terrains4d, this->sticks4d, this->springs4d, true, true, true, true, this->camera.position4d, this->camera.forward4D, this->camera.right4D, &this->hitPosNear, &this->hitNormal);
					if (this->hitIndex.isValid){
						if (this->hitIndex.n < size_of_objects4d(this->rigidBodies4d, this->walls4d)){
							Object4D* o(find_object4d(this->rigidBodies4d, this->walls4d, this->hitIndex.n));
							for (size_t i(0); i < o->componentsVec[OPENDOOR4D_ANIMATION].size(); i++){
								this->openDoors4d[o->componentsVec[OPENDOOR4D_ANIMATION][i]]->switch_state();
							}
						}
						if (this->hitIndex.n < this->rigidBodies4d.size()){
							RigidBody4D* r(this->rigidBodies4d[this->hitIndex.n]);
							if (r->objectName == "Glass4D"){
								delete_object4d(&this->rigidBodies4d, &this->walls4d, &this->groupIndices, this->groups, this->camera.position4d, &this->renderIndices1, &this->renderIndices2, &this->constraintsVec, &this->dynamiteIndices, &this->sticks4d, &this->springs4d, &this->hingeConstraintsVec, &this->shifts4d, &this->floats4d, &this->rotates4d, &this->openDoors4d, this->hitIndex.n);
								this->sounds[8]->play(alg::length(this->camera.position4d - r->position4d), this->soundVolume);
							}
							else {
								glm::vec4 force4D(45000.f * this->dt * normalize(this->camera.forward4D));
								r->forceSystems4D.push_back(new ForceSystem4D(force4D, world_pos_to_body(r, this->hitPosNear)));
								this->rigidBodies4d[0]->forceSystems4D.push_back(new ForceSystem4D(-force4D, glm::vec4(0.f)));
							}
							for (size_t i(0); i < r->componentsVec[DYNAMITE4D].size(); i++){
								this->dynamiteIndices[r->componentsVec[DYNAMITE4D][i]]->isExploding = true;
							}
							////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							//for (DynamiteIndex* d : this->dynamiteIndices)//If dynamite'size>100000 how to find the dynamite quickly?
							//{
							//	if(d->index == this->hitIndex.n)d->isExploding=true;
							//}
							////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							this->sounds[4]->play(alg::length(this->camera.position4d - this->hitPosNear), this->soundVolume);
						}
						else if (this->hitIndex.n < size_of_objects4d(this->rigidBodies4d, this->walls4d))
						{
							Wall4D* w(this->walls4d[this->hitIndex.n - this->rigidBodies4d.size()]);
							if (w->objectName == "Glass4D"){
								delete_object4d(&this->rigidBodies4d, &this->walls4d, &this->groupIndices, this->groups, this->camera.position4d, &this->renderIndices1, &this->renderIndices2, &this->constraintsVec, &this->dynamiteIndices, &this->sticks4d, &this->springs4d, &this->hingeConstraintsVec, &this->shifts4d, &this->floats4d, &this->rotates4d, &this->openDoors4d, this->hitIndex.n);
								this->sounds[8]->play(alg::length(this->camera.position4d - this->hitPosNear), this->soundVolume);
							}
							for (size_t i(0); i < w->componentsVec[DYNAMITE4D].size(); i++){
								this->dynamiteIndices[w->componentsVec[DYNAMITE4D][i]]->isExploding = true;
							}
							this->sounds[5]->play(alg::length(this->camera.position4d - this->hitPosNear), this->soundVolume);
						}
						else if (this->hitIndex.n < size_of_objects4d(this->rigidBodies4d, this->walls4d, this->sticks4d, this->springs4d))
						{
							erase_joint4d0(&this->sticks4d, &this->springs4d, this->hitIndex.n - size_of_objects4d(this->rigidBodies4d, this->walls4d));
							for (size_t i(0); i < size_of_objects4d(this->rigidBodies4d, this->walls4d); i++){
								for (size_t j(0); j < OPENDOOR4D_ANIMATION + 1; j++)find_object4d(this->rigidBodies4d, this->walls4d, i)->componentsVec[j].clear();
							}
							update_components_index(this->rigidBodies4d, this->walls4d, dynamiteIndices, sticks4d, springs4d, hingeConstraintsVec, shifts4d, floats4d, rotates4d, openDoors4d);
							update_render_indices(this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d, this->sticks4d, this->springs4d, &this->renderIndices1, &this->renderIndices2, this->camera.position4d);
							sort_render_indices(&this->renderIndices1); sort_render_indices(&this->renderIndices2);
							update_collide_indices(this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d);
							this->sounds[8]->play(alg::length(this->camera.position4d - this->hitPosNear), this->soundVolume);
							this->sounds[5]->play(alg::length(this->camera.position4d - this->hitPosNear), this->soundVolume);
						}
						else {
							this->sounds[5]->play(alg::length(this->camera.position4d - this->hitPosNear), this->soundVolume);
						}
						this->emitters4d.push_back(new Emitter4D(1, this->hitPosNear, glm::vec4(0.f), 2.f));
						//std::cout << this->hitPosNear.y << "\n";
						this->hitIndex.isValid = false;
					}
				}
			}
			else if (this->shootType == 1)
			{
				if (this->inputs[2]->getMouseOnPress(this->window, GLFW_MOUSE_BUTTON_2))
				{
					this->xRays4d.push_back(new XRay4D());
				}
				else if (this->inputs[2]->getMouseOnRelease(this->window, GLFW_MOUSE_BUTTON_2))
				{
					if (this->xRays4d.size() > 0)this->xRays4d[0] = nullptr, free(this->xRays4d[0]), this->xRays4d.clear();
				}
				else if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_2))
				{
					if (this->xRays4d.size() > 0)this->xRays4d[0]->update_x_ray4D(this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d, this->terrains4d, this->sticks4d, this->springs4d, this->camera.position4d, this->camera.forward4D, this->camera.right4D, this->reflectionSteps);
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
					ray::detect_object4d_index(&this->hitIndex, this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d, this->terrains4d, this->sticks4d, this->springs4d, false,false, true, false, this->camera.position4d, this->camera.forward4D, this->camera.right4D, &this->hitPosNear, &this->hitNormal);
					if (this->hitIndex.isValid)
					{
						if (this->hitIndex.n < this->rigidBodies4d.size())
						{
							RigidBody4D* a(this->rigidBodies4d[this->hitIndex.n]);
							if (this->hitIndex.n < this->rigidBodies4d.size())
							{
								if (this->controlType == DRAG)
								{
									if (alg::length(a->position4d - this->camera.frontPosition4D) < 2.f)
									{
										a->isFrozen = false;
										a->isContinueSleep = a->isSleep = false;
										a->set_position4D(this->camera.frontPosition4D);
										a->velocity4d = this->camera.frontVelocity;
										a->angularVelocity4D = alg::bivec4();
									}
								}
								else if (this->controlType == LUNCH)
								{
									if (alg::length(a->position4d - this->camera.frontPosition4D) < 2.f)
									{
										a->isFrozen = false;
										a->velocity4d = 16.f * this->camera.forward4D;
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
										this->dragLines4d.clear();
										this->dragLines4d.push_back(new JointLine4D());
									}
									else
									{
										this->dragLines4d.clear();
										this->hitIndex.isValid = false;
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
				if (this->hitIndex.isValid) {
					if (this->hitIndex.n < this->rigidBodies4d.size())
					{
						RigidBody4D* a(this->rigidBodies4d[this->hitIndex.n]);
						if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS && glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE)
						{
							if (this->isFixedTime)
							{
								if (this->controlType == DRAG)
								{
									if (alg::length(a->position4d - this->camera.frontPosition4D) < 2.f)
									{
										a->set_position4D(this->camera.frontPosition4D);
										a->velocity4d = glm::vec4(0.f);
										a->angularVelocity4D = alg::bivec4();
									}
								}
								else if (this->controlType == SOFT_DRAG)
								{
									if (alg::length(body_pos_to_world(a, this->hitPosToBody) - this->camera.frontPosition4D) < 2.f)
									{
										this->dragLines4d[0]->update_joint_line4D(body_pos_to_world(a, this->hitPosToBody), this->camera.frontPosition4D);
										glm::vec4 force4D(900.f * this->dt * (this->camera.frontPosition4D - a->position4d));
										a->forceSystems4D.push_back(new ForceSystem4D(force4D, this->hitPosToBody));
										a->velocity4d *= pow(0.25f, this->dt);
										a->angularVelocity4D =
										a->angularVelocity4D * pow(0.86f, this->dt);
										this->rigidBodies4d[0]->forceSystems4D.push_back(new ForceSystem4D(-force4D, glm::vec4(0.f)));
									}
									else
									{
										this->dragLines4d.clear();
										this->hitIndex.isValid = false;
									}
								}
								else if (this->controlType == FROZE)
								{
									//a->set_position4D(this->camera.frontPosition4D);
									this->hitIndex.isValid = false;
								}
							}
						}
						if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS && glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
						{
							if (this->isFixedTime)
							{
								if (this->controlType == DRAG)
								{
									if (alg::length(a->position4d - this->camera.frontPosition4D) < 2.f)
									{
										a->velocity4d = 4.f * this->camera.forward4D;
										this->hitIndex.isValid = false;
									}
								}
								else if (this->controlType == SOFT_DRAG)
								{
									if (alg::length(a->position4d - this->camera.frontPosition4D) < 2.f)
									{
										this->dragLines4d.clear();
										float objectMass(a->mass);
										float handMass(0.1f);
										glm::vec4 force4D(900.f * (objectMass / (objectMass + handMass)) * this->dt * this->camera.forward4D);
										a->forceSystems4D.push_back(new ForceSystem4D(force4D, glm::vec4(0.f)));
										this->rigidBodies4d[0]->forceSystems4D.push_back(new ForceSystem4D(-force4D, glm::vec4(0.f)));
									}
									else
									{
										this->dragLines4d.clear();
										this->hitIndex.isValid = false;
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
						this->dragLines4d.clear();
					}
					this->hitIndex.isValid = false;
				}
			}

			if (this->controlType == SOFT_DRAG_MULTIPLY)
			{
				if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS && glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE)
				{
					this->dragLines4d.clear();
					size_t index(0);
					for (size_t i(1); i < this->rigidBodies4d.size(); i++)
					{
						if (alg::length(this->rigidBodies4d[i]->position4d - this->camera.frontPosition4D) < 5.f)
						{
							this->rigidBodies4d[i]->isFrozen = false;
							this->dragLines4d.push_back(new JointLine4D());
							this->dragLines4d[index]->update_joint_line4D(this->rigidBodies4d[i]->position4d, this->camera.frontPosition4D);
							index++;
							glm::vec4 force4D(7.5f * (this->camera.frontPosition4D - this->rigidBodies4d[i]->position4d));
							this->rigidBodies4d[i]->forceSystems4D.push_back(new ForceSystem4D(force4D, glm::vec4(0.f)));
							this->rigidBodies4d[i]->velocity4d *= pow(0.25f, this->dt);
							this->rigidBodies4d[0]->forceSystems4D.push_back(new ForceSystem4D(-force4D, glm::vec4(0.f)));
						}
					}
				}
				if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS && glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
				{
					this->dragLines4d.clear();
					for (size_t i(1); i < this->rigidBodies4d.size(); i++)
					{
						if (alg::length(this->rigidBodies4d[i]->position4d - this->camera.frontPosition4D) < 5.f)
						{
							float objectMass(this->rigidBodies4d[i]->mass);
							float handMass(0.1f);
							glm::vec4 force4D(1028.565f * (objectMass / (objectMass + handMass)) * this->dt *this->camera.forward4D);
							this->rigidBodies4d[i]->forceSystems4D.push_back(new ForceSystem4D(force4D, glm::vec4(0.f)));
							this->rigidBodies4d[0]->forceSystems4D.push_back(new ForceSystem4D(-force4D, glm::vec4(0.f)));
						}
					}
				}
				if (this->inputs[2]->getMouseOnRelease(this->window, GLFW_MOUSE_BUTTON_2))
				{
					this->dragLines4d.clear();
				}
			}
		}
		if (this->mode == PAINTING) {
			ray::get_ray_detect_terrain_pos4D(this->camera.position4d, this->camera.forward4D, this->camera.right4D, this->groupIndices, this->groups, this->terrains4d, &this->hittingPos4D);
			this->shaders[TERRAIND4]->use();
			this->shaders[TERRAIND4]->set_vec4f(this->hittingPos4D, "hittingPos4D");
			this->shaders[TERRAIND4]->set1f(this->paintScale, "paintScale");
			if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
			{
				if (this->isHardPainting)
					this->paintType = this->paintType0 + 10;
				else
					this->paintType = this->paintType0;
				this->textures3d[BLEND]->paint_colors(this->paintType,
					glm::vec3(this->hittingPos4D.x, this->hittingPos4D.z, this->hittingPos4D.w),
					this->paintScale, this->isSphericalPainting);
			}
		}
		if (this->mode == BUILDING) {

			if (glfwGetKey(this->window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(this->window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
			{
				this->hittingPos4D = get_build_position4D(this->camera.position4d, this->camera.forward4D, this->hittingPos4D, true);
			}
			else {
				if (!(this->buildMode == BUILD_STICK || this->buildMode == BUILD_SPRING))
				{
					VectorIndex hitIndex2({ 0,false });
					ray::detect_object4d_index(&hitIndex2, this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d, this->terrains4d, this->sticks4d, this->springs4d, true, true, true, true, this->camera.position4d, this->camera.forward4D, this->camera.right4D, &this->hittingPos4D, &this->hitNormal);
					this->isFindPoint = hitIndex2.isValid;
					if (this->isFindPoint &&hitIndex2.n < size_of_objects4d(this->rigidBodies4d, this->walls4d, this->sticks4d, this->springs4d)) { this->hitObject4D = find_object4d(this->rigidBodies4d, this->walls4d, this->sticks4d, this->springs4d, hitIndex2.n); }
					else { this->hitObject4D = nullptr; }
					this->hittingPos4D = get_build_position4D(this->camera.position4d, this->camera.forward4D, this->hittingPos4D, false);
				}
			}
			if (!(this->buildMode == BUILD_STICK || this->buildMode == BUILD_SPRING))
			{
				this->shaders[TERRAIND4]->use();
				this->shaders[TERRAIND4]->set_vec4f(this->hittingPos4D, "hittingPos4D");
			}

			if (this->inputs[2]->getMouseOnPress(this->window, GLFW_MOUSE_BUTTON_2))
			{
				size_t sizeOfGroups(this->groups.size());
				if (this->isRandomColor)
				{
					this->buildColor = glm::vec4(rand() % 256, rand() % 256, rand() % 256, 256.f) / 256.f;
				}
				if (this->isFindPoint) {
					//if (this->buildMode == BUILD_WALL)
					//{
					//	shift_animation4D(this->shifts4d, this->floats4d,this->rotates4d, this->rigidBodies4d.size() + size_of_walls4d(this->groups), 1);
					//	shift_joint4d(this->sticks4d, this->springs4d, this->hingeConstraintsVec, this->rigidBodies4d.size() + size_of_walls4d(this->groups), 1);
					//	this->walls4d.push_back(new Wall4D("Hypercube", Hypercube(get_wall_build_scale4D()), get_wall_build_position4D(this->hittingPos4D), alg::bivec4(), get_wall_build_scale4D(), 1.6f, 0.25f, true, this->wallTexs3d[this->buildTexture],0.f, this->buildColor, BOX4D, this->shaders[this->buildShader]));
					//	this->groups = pack_group(this->groups, &this->walls4d, &this->terrains4d);
					//}
					switch (this->buildMode)
					{
					case BUILD_OBJECT: 
					{ 
						glm::vec4 buildPos(this->hitObject4D == nullptr ? get_cap_position4D(this->hittingPos4D + this->buildScale.y * this->hitNormal / 2.f, this->buildDistance, this->buildOffset) : get_cap_position4D(hitObject4D,isFindPoint, this->hittingPos4D + this->buildScale.y * this->hitNormal / 2.f, this->buildDistance, this->buildOffset));
						alg::rotor4 buildRot(this->hitObject4D ==nullptr?alg::rotor4():update(this->hitObject4D->rotation4D, this->buildRotation * glm::radians(1.f)));
						shift_animation4D(this->shifts4d, this->floats4d, this->rotates4d, this->openDoors4d, size_of_objects4d(this->rigidBodies4d, this->walls4d), 1);
						shift_joint4d(this->sticks4d, this->springs4d, &this->hingeConstraintsVec, size_of_objects4d(this->rigidBodies4d, this->walls4d), 1);
						shift_dynamite4d_indices(this->dynamiteIndices, size_of_objects4d(this->rigidBodies4d, this->walls4d), 1);
						switch (this->buildCol)
						{
						case HYPERCUBE: { this->walls4d.push_back(new Wall4D(this->buildTag, Hypercube(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, BOX4D, this->buildShader)); break; }
						case HYPERSPHERE: { this->walls4d.push_back(new Wall4D(this->buildTag, Hypersphere(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, SPHERE4D, this->buildShader)); break; }
						case HYPERCAPSULE: { this->walls4d.push_back(new Wall4D(this->buildTag, Hypercapsule(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, CAPSULE4D, this->buildShader)); break; }
						case HYPERCYLINDER: { this->walls4d.push_back(new Wall4D(this->buildTag, Hypercylinder(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case HYPERCONE: { this->walls4d.push_back(new Wall4D(this->buildTag, Hypercone(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case HYPERPOT: { this->walls4d.push_back(new Wall4D(this->buildTag, Hyperpot(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case TRIPRISM: { this->walls4d.push_back(new Wall4D(this->buildTag, TriPrism(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case HYPERSLOPE: { this->walls4d.push_back(new Wall4D(this->buildTag, Hyperslope(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case HYPERQUAD: { this->walls4d.push_back(new Wall4D(this->buildTag, DoubleQuads4d(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case PENTACHORON: { this->walls4d.push_back(new Wall4D(this->buildTag, Pentachoron(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case HYPERPYRAMID: { this->walls4d.push_back(new Wall4D(this->buildTag, Pyramid4D(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case HEXADECACHORON: { this->walls4d.push_back(new Wall4D(this->buildTag, Hexadecachoron(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case HEXACOSICHORON: { this->walls4d.push_back(new Wall4D(this->buildTag, Hexacosichoron(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						}
						add_wall4d_to_group(&this->groups, this->walls4d[this->walls4d.size() - 1], this->walls4d.size() - 1);
						this->sounds[7]->play(alg::length(this->camera.position4d - this->hittingPos4D), this->soundVolume);
						break; 
					}
					case BUILD_RIGIDBODY:
					{
						shift_animation4D(this->shifts4d, this->floats4d, this->rotates4d, this->openDoors4d,this->rigidBodies4d.size(), 1);
						shift_joint4d(this->sticks4d, this->springs4d, &this->hingeConstraintsVec, this->rigidBodies4d.size(), 1);
						shift_dynamite4d_indices(this->dynamiteIndices, this->rigidBodies4d.size(), 1);
						glm::vec4 buildPos(this->hittingPos4D + this->buildScale.y * this->hitNormal / 2.f);
						alg::rotor4 buildRot(look_at(glm::vec4(0.f), this->hitNormal, rotate(this->buildRotation, glm::vec4(0.f, 1.f, 0.f, 0.f))));
						switch (this->buildCol)
						{
						case HYPERCUBE: { this->rigidBodies4d.push_back(new RigidBody4D(this->buildTag, Hypercube(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, BOX4D, this->buildShader)); break; }
						case HYPERSPHERE: { this->rigidBodies4d.push_back(new RigidBody4D(this->buildTag, Hypersphere(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, SPHERE4D, this->buildShader)); break; }
						case HYPERCAPSULE: { this->rigidBodies4d.push_back(new RigidBody4D(this->buildTag, Hypercapsule(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, CAPSULE4D, this->buildShader)); break; }
						case HYPERCYLINDER: { this->rigidBodies4d.push_back(new RigidBody4D(this->buildTag, Hypercylinder(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case HYPERCONE: { this->rigidBodies4d.push_back(new RigidBody4D(this->buildTag, Hypercone(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader, this->buildScale * glm::vec4(0.f, 0.f, -0.25f, 0.f))); break; }
						case HYPERPOT: { this->rigidBodies4d.push_back(new RigidBody4D(this->buildTag, Hyperpot(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case TRIPRISM: { this->rigidBodies4d.push_back(new RigidBody4D(this->buildTag, TriPrism(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case HYPERSLOPE: { this->rigidBodies4d.push_back(new RigidBody4D(this->buildTag, Hyperslope(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader, this->buildScale * glm::vec4(0.5f / 3.f, -0.5f / 3.f, 0.5f / 3.f, 0.5f / 3.f))); break; }
						case HYPERQUAD: { this->rigidBodies4d.push_back(new RigidBody4D(this->buildTag, DoubleQuads4d(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case PENTACHORON: { this->rigidBodies4d.push_back(new RigidBody4D(this->buildTag, Pentachoron(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case HYPERPYRAMID: { this->rigidBodies4d.push_back(new RigidBody4D(this->buildTag, Pyramid4D(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader, this->buildScale * glm::vec4(0.f,-0.25f,0.f,0.f))); break; }
						case HEXADECACHORON: { this->rigidBodies4d.push_back(new RigidBody4D(this->buildTag, Hexadecachoron(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						case HEXACOSICHORON: { this->rigidBodies4d.push_back(new RigidBody4D(this->buildTag, Hexacosichoron(this->buildScale / 2.f), buildPos, buildRot, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildColor,this->buildMetalColor, MESH4D, this->buildShader)); break; }
						}
						break;
					}
					case BUILD_POOL_TABLE:
					{
						shift_animation4D(this->shifts4d, this->floats4d, this->rotates4d, this->openDoors4d,size_of_objects4d(this->rigidBodies4d, this->walls4d), 34);
						shift_joint4d(this->sticks4d, this->springs4d, &this->hingeConstraintsVec, size_of_objects4d(this->rigidBodies4d, this->walls4d), 34);
						shift_dynamite4d_indices(this->dynamiteIndices, size_of_objects4d(this->rigidBodies4d, this->walls4d), 34);
						generate_pool_table4D(get_cap_position4D(this->hittingPos4D, this->buildDistance, this->buildOffset), glm::vec4(1.27f, 1.27f, 2.54f, 1.27f), 1.f, true, WOODX, true, GRASS, true, WOODY, &this->walls4d, this->buildShader);
						for (size_t i(0); i < 34;i++)add_wall4d_to_group(&this->groups, this->walls4d[this->walls4d.size() - 1 - i], this->walls4d.size() - 1 - i);
						this->sounds[7]->play(alg::length(this->camera.position4d - this->hittingPos4D), this->soundVolume);
						break;
					}
					case BUILD_BILLIARD:
					{
						shift_animation4D(this->shifts4d, this->floats4d, this->rotates4d, this->openDoors4d,this->rigidBodies4d.size(), 1);
						shift_joint4d(this->sticks4d, this->springs4d, &this->hingeConstraintsVec, this->rigidBodies4d.size(), 1);
						shift_dynamite4d_indices(this->dynamiteIndices, this->rigidBodies4d.size(), 1);
						generate_billiard4D(this->hittingPos4D + glm::vec4(0.f, 0.0525f / 2.f, 0.f, 0.f), this->initialVelocity, this->initialAngularVelocity, this->buildTexture, &this->rigidBodies4d, this->isGravity, this->buildColor,this->buildMetalColor, this->buildShader);
						this->sounds[7]->play(alg::length(this->camera.position4d - this->hittingPos4D), this->soundVolume);
						break;
					}
					case BUILD_DYNAMITE:
					{
						if (this->isRigidBody)
						{
							shift_animation4D(this->shifts4d, this->floats4d, this->rotates4d, this->openDoors4d,this->rigidBodies4d.size(), 1);
							shift_joint4d(this->sticks4d, this->springs4d, &this->hingeConstraintsVec, this->rigidBodies4d.size(), 1);
							shift_dynamite4d_indices(this->dynamiteIndices, this->rigidBodies4d.size(), 1);
							generate_dynamite4D(this->hittingPos4D, this->initialVelocity, this->initialAngularVelocity, WHITECONCRETE, &this->rigidBodies4d, &this->dynamiteIndices, this->isGravity,this->buildShader);
							this->rigidBodies4d[this->rigidBodies4d.size() - 1]->componentsVec[DYNAMITE4D].push_back(this->dynamiteIndices.size()-1);
							this->sounds[7]->play(alg::length(this->camera.position4d - this->hittingPos4D), this->soundVolume);
						}
						else
						{
							shift_animation4D(this->shifts4d, this->floats4d, this->rotates4d, this->openDoors4d,size_of_objects4d(this->rigidBodies4d, this->walls4d), 1);
							shift_joint4d(this->sticks4d, this->springs4d, &this->hingeConstraintsVec, size_of_objects4d(this->rigidBodies4d, this->walls4d), 1);
							shift_dynamite4d_indices(this->dynamiteIndices, size_of_objects4d(this->rigidBodies4d, this->walls4d), 1);
							generate_dynamite4D(this->hittingPos4D, WHITECONCRETE, &this->rigidBodies4d, &this->walls4d, &this->dynamiteIndices, this->buildShader);
							add_wall4d_to_group(&this->groups, this->walls4d[this->walls4d.size() - 1], this->walls4d.size() - 1);
							this->sounds[7]->play(alg::length(this->camera.position4d - this->hittingPos4D), this->soundVolume);
						}
						break;
					}
					case BUILD_POINTLIGHT:
					{
						glm::vec4 buildPos(get_cap_position4D(this->hittingPos4D, this->buildDistance, this->buildOffset));
						this->pointLights4d.push_back(new PointLight4D(PARTICLE1, buildPos, this->pointLights4d.size(), this->lightIntensity, this->lightColor, this->lightRadius));
						update_point_light4d(this->pointLights4d, this->shaders[WALLD4], this->shaders[TERRAIND4], this->shaders[LIGHT_MAPD3]);
						this->shaders[LIGHT_MAPD3]->set_vec4f(this->camera.position4d, "cameraPosShift4D");
						this->lightMap3d->bind_image(0);
						glDispatchCompute(4, 128, 4);
						glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
						this->shaders[WALLD4]->use();
						this->shaders[WALLD4]->set_vec4f(this->camera.position4d, "cameraPosShift4D");
						this->shaders[TERRAIND4]->use();
						this->shaders[TERRAIND4]->set_vec4f(this->camera.position4d, "cameraPosShift4D");
						break;
					}
					}
					for (size_t i(0); i < size_of_objects4d(this->rigidBodies4d,this->walls4d); i++)
					{
						for (size_t j(0); j < OPENDOOR4D_ANIMATION + 1; j++)find_object4d(this->rigidBodies4d, this->walls4d, i)->componentsVec[j].clear();
					}
					update_components_index(this->rigidBodies4d, this->walls4d, dynamiteIndices, sticks4d, springs4d, hingeConstraintsVec, shifts4d, floats4d, rotates4d, openDoors4d);
					isObjectParameterUpdated0 = true;
                }
				if (this->buildMode == BUILD_STICK)
				{
					ray::detect_object4d_index(&this->hitIndex, this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d, this->terrains4d, this->sticks4d, this->springs4d, true, false, true, false, this->camera.position4d, this->camera.forward4D, this->camera.right4D, &this->hitPosNear, &this->hitNormal);
					if (this->hitIndex.isValid)
					{
						if (this->hitIndex.n < size_of_objects4d(this->rigidBodies4d, this->walls4d))
						{
							Object4D* o(find_object4d(this->rigidBodies4d, this->walls4d, this->hitIndex.n));
							if (o->objectName != "Ground")
							{
								bool isInitial(true);
								if (this->springs4d.size() != 0)
								{
									if ((!this->springs4d[this->springs4d.size() - 1]->index2.isValid) && this->springs4d[this->springs4d.size() - 1]->index1 != this->hitIndex.n)
									{
										isInitial = false;
										this->springs4d[this->springs4d.size() - 1]->index2 = this->hitIndex;
										o->componentsVec[SPRING_JOINT].push_back(this->springs4d.size() - 1);
										this->sounds[7]->play(alg::length(this->camera.position4d - this->hittingPos4D), this->soundVolume);
									}
								}
								if (isInitial)
								{
									int size(this->sticks4d.size());
									if (size == 0)
									{
										this->sticks4d.push_back(new Stick4D(glm::vec4(0.f), this->hitIndex.n, { 0, false }, this->stickLength, WHITECONCRETE, this->buildColor, this->buildShader));
										o->componentsVec[STICK_JOINT].push_back(0);
										this->sounds[7]->play(alg::length(this->camera.position4d - this->hittingPos4D), this->soundVolume);
									}
									else
									{
										if (this->sticks4d[size - 1]->index2.isValid)
										{
											this->sticks4d.push_back(new Stick4D(glm::vec4(0.f), this->hitIndex.n, { 0, false }, this->stickLength, WHITECONCRETE, this->buildColor, this->buildShader));
											o->componentsVec[STICK_JOINT].push_back(size);
											this->sounds[7]->play(alg::length(this->camera.position4d - this->hittingPos4D), this->soundVolume);
										}
										else if ((!this->sticks4d[size - 1]->index2.isValid) && this->sticks4d[size - 1]->index1 != this->hitIndex.n)
										{
											this->sticks4d[size - 1]->index2 = this->hitIndex;
											o->componentsVec[STICK_JOINT].push_back(size - 1);
											this->sounds[7]->play(alg::length(this->camera.position4d - this->hittingPos4D), this->soundVolume);
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
						ray::detect_object4d_index(&this->hitIndex, this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d, this->terrains4d, this->sticks4d, this->springs4d, true, false, true, false, this->camera.position4d, this->camera.forward4D, this->camera.right4D, &this->hitPosNear, &this->hitNormal);
						if (this->hitIndex.isValid)
						{
							if (this->hitIndex.n < size_of_objects4d(this->rigidBodies4d, this->walls4d))
							{
								Object4D* o(find_object4d(this->rigidBodies4d, this->walls4d, this->hitIndex.n));
								if (o->objectName != "Ground")
								{
									bool isInitial(true);
									if (this->sticks4d.size() != 0)
									{
										if ((!this->sticks4d[this->sticks4d.size() - 1]->index2.isValid) && this->sticks4d[this->sticks4d.size() - 1]->index1 != this->hitIndex.n)
										{
											isInitial = false;
											this->sticks4d[this->sticks4d.size() - 1]->index2 = this->hitIndex;
											o->componentsVec[STICK_JOINT].push_back(this->sticks4d.size() - 1);
											this->sounds[7]->play(alg::length(this->camera.position4d - this->hittingPos4D), this->soundVolume);
										}
									}
									if (isInitial)
									{
										int size(this->springs4d.size());
										if (size == 0)
										{
											this->springs4d.push_back(new Spring4D(glm::vec4(0.f), this->hitIndex.n, { 0, false }, this->springLength, this->springStrength, STONE, this->buildColor, this->buildShader));
											o->componentsVec[SPRING_JOINT].push_back(0);
											this->sounds[7]->play(alg::length(this->camera.position4d - this->hittingPos4D), this->soundVolume);
										}
										else
										{
											if (this->springs4d[size - 1]->index2.isValid)
											{
												this->springs4d.push_back(new Spring4D(glm::vec4(0.f), this->hitIndex.n, { 0, false }, this->springLength, this->springStrength, STONE, this->buildColor, this->buildShader));
												o->componentsVec[SPRING_JOINT].push_back(size);
												this->sounds[7]->play(alg::length(this->camera.position4d - this->hittingPos4D), this->soundVolume);
											}
											else if ((!this->springs4d[size - 1]->index2.isValid) && this->springs4d[size - 1]->index1 != this->hitIndex.n)
											{
												this->springs4d[size - 1]->index2 = this->hitIndex;
												o->componentsVec[SPRING_JOINT].push_back(size - 1);
												this->sounds[7]->play(alg::length(this->camera.position4d - this->hittingPos4D), this->soundVolume);
											}
										}
									}
								}
							}
						}
					}
				this->groupIndices = judge_groups(this->rigidBodies4d, this->groupIndices, this->groups, this->camera.position4d, this->blockLoadDistance);
				judge_objects(this->groupIndices, this->groups, this->walls4d, this->terrains4d, this->camera.position4d, this->camera.forward4D, this->camera.wDir, this->objectLoadDistance);
				update_render_indices(this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d, this->sticks4d, this->springs4d, &this->renderIndices1, &this->renderIndices2, this->camera.position4d);
				sort_render_indices(&this->renderIndices1); sort_render_indices(&this->renderIndices2);
				update_collide_indices(this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d);
			}
			if (this->buildMode == BUILD_STICK)
			{
				if (this->sticks4d.size() != 0) {
					if (!this->sticks4d[this->sticks4d.size() - 1]->index2.isValid) {
						if (this->inputs[9]->getKeyOnPress(this->window, GLFW_KEY_DELETE)) {
							this->sticks4d.erase(this->sticks4d.begin() + this->sticks4d.size() - 1);
						}
					}
				}
			}
			else
				if (this->buildMode == BUILD_SPRING)
				{
					if (this->springs4d.size() != 0) {
						if (!this->springs4d[this->springs4d.size() - 1]->index2.isValid) {
							if (this->inputs[9]->getKeyOnPress(this->window, GLFW_KEY_DELETE)) {
								this->springs4d.erase(this->springs4d.begin() + this->springs4d.size() - 1);
							}
						}
					}
				}
		}
		if (this->mode == DELETING)
		{
			if (this->inputs[2]->getMouseOnPress(this->window, GLFW_MOUSE_BUTTON_2))
			{
				for (int i(0); i < this->penetrationCount; i++)
				{
					ray::detect_object4d_index(&this->hitIndex, this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d, this->terrains4d, this->sticks4d, this->springs4d, true, true, true, false, this->camera.position4d, this->camera.forward4D, this->camera.right4D, &this->hitPosNear, &this->hitNormal);
					if (this->hitIndex.isValid)
					{
						if (this->hitIndex.n < this->rigidBodies4d.size())
						{
							delete_object4d(&this->rigidBodies4d, &this->walls4d, &this->groupIndices, this->groups, this->camera.position4d, &this->renderIndices1, &this->renderIndices2, &this->constraintsVec, &this->dynamiteIndices, &this->sticks4d, &this->springs4d, &this->hingeConstraintsVec, &this->shifts4d, &this->floats4d, &this->rotates4d, &this->openDoors4d, this->hitIndex.n);
						}
						else if (this->hitIndex.n < size_of_objects4d(this->rigidBodies4d, this->walls4d))
						{
							if (this->walls4d[this->hitIndex.n - this->rigidBodies4d.size()]->objectName != "Ground")
							{
								delete_object4d(&this->rigidBodies4d, &this->walls4d, &this->groupIndices, this->groups, this->camera.position4d, &this->renderIndices1, &this->renderIndices2, &this->constraintsVec, &this->dynamiteIndices, &this->sticks4d, &this->springs4d, &this->hingeConstraintsVec, &this->shifts4d, &this->floats4d, &this->rotates4d, &this->openDoors4d, this->hitIndex.n);
							}
							else
							{
								break;
							}
						}
						else if (this->hitIndex.n < size_of_objects4d(this->rigidBodies4d, this->walls4d, this->sticks4d, this->springs4d))
						{
							erase_joint4d0(&this->sticks4d, &this->springs4d, this->hitIndex.n - size_of_objects4d(this->rigidBodies4d, this->walls4d));
							for (size_t i(0); i < size_of_objects4d(this->rigidBodies4d, this->walls4d); i++)
							{
								for (size_t j(0); j < OPENDOOR4D_ANIMATION + 1; j++)find_object4d(this->rigidBodies4d, this->walls4d, i)->componentsVec[j].clear();
							}
							update_components_index(this->rigidBodies4d, this->walls4d, dynamiteIndices, sticks4d, springs4d, hingeConstraintsVec, shifts4d, floats4d, rotates4d, openDoors4d);
							update_render_indices(this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d, this->sticks4d, this->springs4d, &this->renderIndices1, &this->renderIndices2, this->camera.position4d);
							sort_render_indices(&this->renderIndices1); sort_render_indices(&this->renderIndices2);
							update_collide_indices(this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d);
						}
						else
						{
							break;
						}
						this->hitIndex.isValid = false;
					}
				}
			}
		}
		if (this->mode == AREA_DELETING)
		{
			if (this->inputs[2]->getMouseOnPress(this->window, GLFW_MOUSE_BUTTON_2))
			{
				VectorIndex hitIndex2 = VectorIndex();
				ray::detect_object4d_index(&hitIndex2, this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d, this->terrains4d, this->sticks4d, this->springs4d, true, true, true, true, this->camera.position4d, this->camera.forward4D, this->camera.right4D, &this->hittingPos4D, &this->hitNormal);
			}
			if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
			{
				glm::vec4 endPos;
				glm::vec4 normal;
				VectorIndex hitIndex2 = VectorIndex();
				ray::detect_object4d_index(&hitIndex2, this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d, this->terrains4d, this->sticks4d, this->springs4d, true, true, true, true, this->camera.position4d, this->camera.forward4D, this->camera.right4D, &endPos, &normal);
				this->deleteMap3d->washArea();
				this->deleteMap3d->selectArea(glm::vec3(this->hittingPos4D.x, this->hittingPos4D.z, this->hittingPos4D.w),
					glm::vec3(endPos.x, endPos.z, endPos.w));
			}
			if (this->inputs[3]->getMouseOnRelease(this->window, GLFW_MOUSE_BUTTON_2))
			{
				this->deleteMap3d->getImageData();
			}
			if (this->inputs[9]->getKeyOnPress(this->window, GLFW_KEY_DELETE)) {
				this->area_delete();
			}
		}
	}
}