//#pragma once
#include"Game.h"
#include"imgui/imgui.h"
#include"imgui/imgui_impl_glfw.h"
#include"imgui/imgui_impl_opengl3.h"

char levelText[256] = "level 1";
static char savedLevelText[64] = "level 1-1";
const char* controlText = "Drag";
const char* textureText = "Sand";
const char* dynamiteTypeText = "Rigid Body4D";
const char* screenSizeText = "";
const char* cameraDirText = "W";
const char* swapIntervalText = "vsyncI";
const char* buildingColText = "BOX4D";
const char* buildingShaderText = "Standard";
char paintingColorText[256] = "R1/G1/B1/A1";
const char* paintingShapeText = "Sphere";
const char* frameTypeText = "Use Wireframe";
const char* trailFadeTypeText = "Forget";
const char* textureFilterText = "Mag:Linear/Min:Linear Mipmap Linear";

static void HelpMarker(const char* fmt,const char* desc)
{
	ImGui::TextDisabled(fmt);
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

void start_imgui(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 440");
}

void end_imgui()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
void Game::imgui_use() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("Options");
	
	if (ImGui::TreeNodeEx("Levels", 2)) {
		if (ImGui::BeginCombo("Level", levelText))
		{
			for (int i = 0; i < 6; i++)
			{
				if (ImGui::Selectable((("Level " + std::to_string(i+1)).c_str())))
				{
					this->startLevel(this->level = i+1, "");
					snprintf(levelText,255,"Level %i",this->level);
				}
			}
			ImGui::EndCombo();
		}
		if (ImGui::TreeNodeEx("Save", 0)) 
		{
			ImGui::InputText("Level Name", savedLevelText, IM_ARRAYSIZE(savedLevelText));
			if (ImGui::Button("Save The Level"))
			{
				save_file(("resourcefile/saves/"+ (std::string)savedLevelText +".txt").c_str(), this->wallTexs3D, this->particleTexs3D, this->shaders,
					this->rigidBodies4D, this->dynamites4D2, this->groups, this->walls4D, this->dynamites4D, this->waters4D,
					this->sticks4D, this->springs4D, this->shifts4D, this->floats4D, this->rotates4D, this->hingeConstraints,
					this->pointLights4D,this->worldTime);
			}
			if (ImGui::BeginCombo("Load The Level", ""))
			{
				for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator("resourcefile/saves/"))
				if (ImGui::Selectable(entry.path().string().c_str()))
				{
					this->startLevel(0, entry.path().string().c_str());
					snprintf(levelText, 255, savedLevelText);
				}
				ImGui::EndCombo();
			}

			if (ImGui::BeginCombo("Delete The Level", ""))
			{
				for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator("resourcefile/saves/"))
					if (ImGui::Selectable(entry.path().string().c_str()))
					{
						remove(entry.path().string().c_str());
					}
				ImGui::EndCombo();
			}
			
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
	if (ImGui::TreeNodeEx("Controls", 2))
	{
		if (ImGui::RadioButton("Shooting Mode", &this->mode, SHOOTING)) {
			this->targetIcon->logo = this->pointerTexs[SHOOTING];
			this->shaders[WALLD4]->use();
			this->shaders[WALLD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
			this->shaders[EMITD4]->use();
			this->shaders[EMITD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
			this->shaders[TERRAIND4]->use();
			this->shaders[TERRAIND4]->set1i(this->mode == PAINTING, "isPainting");
			this->shaders[TERRAIND4]->set1i(this->mode == BUILDING, "isBuilding");
			this->shaders[TERRAIND4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
			this->shaders[SKY_BOXD4]->use();
			this->shaders[SKY_BOXD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
		}
		if (ImGui::RadioButton("Controling Mode", &this->mode,CONTROLING)) {
			this->targetIcon->logo = this->pointerTexs[CONTROLING];
			this->shaders[WALLD4]->use();
			this->shaders[WALLD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
			this->shaders[EMITD4]->use();
			this->shaders[EMITD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
			this->shaders[TERRAIND4]->use();
			this->shaders[TERRAIND4]->set1i(this->mode == PAINTING, "isPainting");
			this->shaders[TERRAIND4]->set1i(this->mode == BUILDING, "isBuilding");
			this->shaders[TERRAIND4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
			this->shaders[SKY_BOXD4]->use();
			this->shaders[SKY_BOXD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
		}
		if (ImGui::BeginCombo("Control Type", controlText))
		{
			if (ImGui::Selectable("Drag"))
			{
				this->controlType = 0;
				controlText = "Drag";
			}
			if (ImGui::Selectable("Drag And Froze"))
			{
				this->controlType = 1;
				controlText = "Drag And Froze";
			}
			if (ImGui::Selectable("Drag multiple Objects"))
			{
				this->controlType = 2;
				controlText = "Drag multiple Objects";
			}
			ImGui::EndCombo();
		}
		if (ImGui::Button("Respawn"))
		{
			this->rigidBodies4D[0] = new RigidBody4D("Player", Hypercapsule(glm::vec4(0.4f, 0.4f, 1.4f, 0.4f)), glm::vec4(0.f, 64.7f, 0.f, 0.f), alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.4f, 0.4f, 1.4f, 0.4f), 65.f, 0.f, 1.265f, 0.25f, true, false, glm::vec4(0, 0, 0, 0), alg::bivec4(), true, this->wallTexs3D[PURE_WHITE], 0.f, glm::vec4(1.f, 1.f, 1.f, 0.25f), CAPSULE4D, this->shaders[WALLD4]);
		}
		if (ImGui::Button("Set World Time To zero"))
		{
			this->worldTime = 0.f;
		}

		bool isFrozen=false;
		for (RigidBody4D* i : this->rigidBodies4D)
		{
			if (i->isFrozen == true)
			{
				isFrozen = true;
			}
		}
		if(isFrozen)
		if (ImGui::Button("Unfroze"))
		{
			for (size_t i = 1; i < size_of_objects4d(this->rigidBodies4D,this->dynamites4D2); i++)
			{
				find_rigidbody4d(this->rigidBodies4D,this->dynamites4D2,i)->isFrozen = false;
				find_rigidbody4d(this->rigidBodies4D, this->dynamites4D2, i)->isSleep = false;
			}
		}
		if (ImGui::Button("Froze"))
		{
			for (size_t i = 1; i < size_of_objects4d(this->rigidBodies4D, this->dynamites4D2); i++)
			{
				find_rigidbody4d(this->rigidBodies4D, this->dynamites4D2, i)->isFrozen = true;
			}
		}
		if (ImGui::BeginCombo("Camera Vertical To", cameraDirText))
		{
			if (ImGui::Selectable("X"))
			{
				this->camera.fit_direction(0);
				cameraDirText = "X";
			}
			if (ImGui::Selectable("Y"))
			{
				this->camera.fit_direction(1);
				cameraDirText = "Y";
			}
			if (ImGui::Selectable("Z"))
			{
				this->camera.fit_direction(2);
				cameraDirText = "Z";
			}
			if (ImGui::Selectable("W"))
			{
				this->camera.fit_direction(3);
				cameraDirText = "W";
			}
			ImGui::EndCombo();
		}
		ImGui::TreePop();
	}
	if (ImGui::TreeNodeEx("Drawing", 2))
	{
	    if (ImGui::TreeNodeEx("Ground", 0))
	    {
	    	if (ImGui::RadioButton("Painting Mode", &this->mode, PAINTING)) {
	    		this->targetIcon->logo = this->pointerTexs[PAINTING];
				this->shaders[WALLD4]->use();
				this->shaders[WALLD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
				this->shaders[EMITD4]->use();
				this->shaders[EMITD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
	    		this->shaders[TERRAIND4]->use();
	    		this->shaders[TERRAIND4]->set1i(this->mode == PAINTING, "isPainting");
	    		this->shaders[TERRAIND4]->set1i(this->mode == BUILDING, "isBuilding");
	    		this->shaders[TERRAIND4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
				this->shaders[SKY_BOXD4]->use();
				this->shaders[SKY_BOXD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
	    	}
	    
	    	
	    	ImGui::DragInt("Painting Scale", &this->paintScale, 0.5f, 1, 64);
	    
	    	if (ImGui::BeginCombo("Painting Shape", paintingShapeText))
	    	{
	    		if (ImGui::Selectable("Sphere"))
	    		{
	    			this->isSphericalPainting = true;
	    
	    			this->shaders[TERRAIND4]->use();
	    			this->shaders[TERRAIND4]->set1i(this->isSphericalPainting, "isSphericalPainting");
	    			paintingShapeText = "Sphere";
	    		}
	    		if (ImGui::Selectable("Square"))
	    		{
	    			this->isSphericalPainting = false;
	    
	    			this->shaders[TERRAIND4]->use();
	    			this->shaders[TERRAIND4]->set1i(this->isSphericalPainting, "isSphericalPainting");
	    			paintingShapeText = "Square";
	    		}
	    		ImGui::EndCombo();
	    	}
	    
	    	ImGui::Checkbox("Hard Edge", &this->isHardPainting);
	    	if (ImGui::TreeNodeEx("Painting Texture", 0))
	    	{
	    		HelpMarker("(1) ","Sand");
	    		ImGui::SameLine();
	    		if (ImGui::ImageButton((ImTextureID)(SAND + 3), ImVec2(100, 100)))
	    		{
	    			this->paintType0 = 0;
	    		}
	    		ImGui::SameLine();
	    		HelpMarker("(2) ", "Snow");
	    		ImGui::SameLine();
	    		if (ImGui::ImageButton((ImTextureID)(SNOW + 3), ImVec2(100, 100)))
	    		{
	    			this->paintType0 = 1;
	    		}
	    		HelpMarker("(3) ", "Ice");
	    		ImGui::SameLine();
	    		if (ImGui::ImageButton((ImTextureID)(ICE + 3), ImVec2(100, 100)))
	    		{
	    			this->paintType0 = 2;
	    		}
	    		ImGui::SameLine();
	    		HelpMarker("(4) ", "Normal Grass");
	    		ImGui::SameLine();
	    		if (ImGui::ImageButton((ImTextureID)(GRASS1 + 3), ImVec2(100, 100)))
	    		{
	    			this->paintType0 = 3;
	    		}
	    		HelpMarker("(5) ", "Green Grass");
	    		ImGui::SameLine();
	    		if (ImGui::ImageButton((ImTextureID)(GRASS2 + 3), ImVec2(100, 100)))
	    		{
	    			this->paintType0 = 4;
	    		}
	    		ImGui::SameLine();
	    		HelpMarker("(6) ", "Soil");
	    		ImGui::SameLine();
	    		if (ImGui::ImageButton((ImTextureID)(SOIL + 3), ImVec2(100, 100)))
	    		{
	    			this->paintType0 = 5;
	    		}
	    		HelpMarker("(7) ", "Swamp Grass");
	    		ImGui::SameLine();
	    		if (ImGui::ImageButton((ImTextureID)(GRASS3 + 3), ImVec2(100, 100)))
	    		{
	    			this->paintType0 = 6;
	    		}
	    		ImGui::SameLine();
	    		HelpMarker("(8) ", "Wild Grass");
	    		ImGui::SameLine();
	    		if (ImGui::ImageButton((ImTextureID)(GRASS4 + 3), ImVec2(100, 100)))
	    		{
	    			this->paintType0 = 7;
	    		}
	    		HelpMarker("(9) ", "Wet Sand");
	    		ImGui::SameLine();
	    		if (ImGui::ImageButton((ImTextureID)(SAND_SOIL + 3), ImVec2(100, 100)))
	    		{
	    			this->paintType0 = 8;
	    		}
	    		ImGui::SameLine();
	    		HelpMarker("(10)", "Half Wet Sand");
	    		ImGui::SameLine();
	    		if (ImGui::ImageButton((ImTextureID)(SAND_SOIL2 + 3), ImVec2(100, 100)))
	    		{
	    			this->paintType0 = 9;
	    		}
	    		ImGui::TreePop();
	    	}
	    	ImGui::TreePop();
	    }
	ImGui::TreePop();
	}
	if (ImGui::TreeNodeEx("Objects", 2))
	{
		if (ImGui::RadioButton("Building Mode", &this->mode, BUILDING)) 
		{
			this->targetIcon->logo = this->pointerTexs[BUILDING];
			this->shaders[WALLD4]->use();
			this->shaders[WALLD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
			this->shaders[EMITD4]->use();
			this->shaders[EMITD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
			this->shaders[TERRAIND4]->use();
			this->shaders[TERRAIND4]->set1i(this->mode == PAINTING, "isPainting");
			this->shaders[TERRAIND4]->set1i(this->mode == BUILDING, "isBuilding");
			this->shaders[TERRAIND4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
			this->shaders[SKY_BOXD4]->use();
			this->shaders[SKY_BOXD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
		}

		if (ImGui::TreeNodeEx("Build", 0))
		{
			if (ImGui::BeginCombo("4D Object Tag", this->buildTag))
			{
				if (ImGui::Selectable("4D-Object"))
				{
					this->buildTag = "4D-Object";
				}
				if (ImGui::Selectable("Can-Be-Destroyed"))
				{
					this->buildTag = "Can-Be-Destroyed";
				}
				if (ImGui::Selectable("Glass4D"))
				{
					this->buildTag = "Glass4D";
				}
				if (ImGui::Selectable("Ground"))
				{
					this->buildTag = "Ground";
				}
				if (ImGui::Selectable("Celestial4D"))
				{
					this->buildTag = "Celestial4D";
				}
				if (ImGui::Selectable("Billiard"))
				{
					this->buildTag = "Billiard";
				}
				ImGui::EndCombo();
			}

			if (ImGui::TreeNodeEx("Object4D Texture", 0))
			{
				HelpMarker("(1) ", "GREEN");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(GREEN + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = GREEN;
				}
				ImGui::SameLine();HelpMarker("(2) ","WHITE");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(WHITE + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = WHITE;
				}
				HelpMarker("(3) ","YELLOW");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(YELLOW + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = YELLOW;
				}
				ImGui::SameLine(); HelpMarker("(4) ","GROUND");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(GROUND + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = GROUND;
				}
				HelpMarker("(5) ","C1");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(C1 + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = C1;
				}
				ImGui::SameLine(); HelpMarker("(6) ","C2");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(C2 + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = C2;
				}
				HelpMarker("(7) ", "C_2");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(C_2 + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = C_2;
				}
				ImGui::SameLine(); HelpMarker("(8) ","C3");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(C3 + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = C3;
				}
				HelpMarker("(9) ","C4");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(C4 + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = C4;
				}
				ImGui::SameLine(); HelpMarker("(10)","C5");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(C5 + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = C5;
				}
				HelpMarker("(11)", "C_5");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(C_5 + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = C_5;
				}
				ImGui::SameLine(); HelpMarker("(12)","C6");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(C6 + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = C6;
				}
				HelpMarker("(13)","CHESSBOARD");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(CHESSBOARD + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = CHESSBOARD;
				}
				ImGui::SameLine(); HelpMarker("(14)","WHITEWALL");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(WHITEWALL + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = WHITEWALL;
				}
				HelpMarker("(15)","GREENMARBLE");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(GREENMARBLE + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = GREENMARBLE;
				}
				ImGui::SameLine(); HelpMarker("(16)","WHITEMARBLE");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(WHITEMARBLE + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = WHITEMARBLE;
				}
				HelpMarker("(17)","YELLOWMARBLE");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(YELLOWMARBLE + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = YELLOWMARBLE;
				}
				ImGui::SameLine(); HelpMarker("(18)","MARBLE_GROUND");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(MARBLE_GROUND + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = MARBLE_GROUND;
				}
				HelpMarker("(19)", "ROCK1");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(ROCK1 + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = ROCK1;
				}
				ImGui::SameLine(); HelpMarker("(20)","MARBLE_C1");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(MARBLE_C1 + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = MARBLE_C1;
				}
			    HelpMarker("(21)","MARBLE_C2");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(MARBLE_C2 + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = MARBLE_C2;
				}
				ImGui::SameLine(); HelpMarker("(22)","MARBLE_C3");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(MARBLE_C3 + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = MARBLE_C3;
				}
				HelpMarker("(23)","MARBLE_C4");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(MARBLE_C4 + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = MARBLE_C4;
				}
				ImGui::SameLine(); HelpMarker("(24)","MARBLE_C5");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(MARBLE_C5 + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = MARBLE_C5;
				}
				HelpMarker("(25)","MARBLE_C6");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(MARBLE_C6 + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = MARBLE_C6;
				}
				ImGui::SameLine(); HelpMarker("(26)","CHESSBOARDMARBLE");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(CHESSBOARDMARBLE + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = CHESSBOARDMARBLE;
				}
				HelpMarker("(27)","WHITEMAINMARBLE");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(WHITEMAINMARBLE + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = WHITEMAINMARBLE;
				}
				ImGui::SameLine(); HelpMarker("(28)","CONCRETE");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(CONCRETE + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = CONCRETE;
				}
				HelpMarker("(29)","YELLOWCONCRETE");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(YELLOWCONCRETE + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = YELLOWCONCRETE;
				}
				ImGui::SameLine(); HelpMarker("(30)","WHITECONCRETE");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(WHITECONCRETE + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = WHITECONCRETE;
				}
				HelpMarker("(31)","GRASS");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(GRASS + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = GRASS;
				}
				ImGui::SameLine(); HelpMarker("(32)","WOODX");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(WOODX + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = WOODX;
				}
				HelpMarker("(33)","WOODY");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(WOODY + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = WOODY;
				}
				ImGui::SameLine(); HelpMarker("(34)","WOODZ");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(WOODZ + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = WOODZ;
				}
				HelpMarker("(35)", "OLDWOODX");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(OLDWOODX + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = OLDWOODX;
				}
				ImGui::SameLine(); HelpMarker("(36)", "OLDWOODY");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(OLDWOODY + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = OLDWOODY;
				}
				HelpMarker("(37)", "OLDWOODZ");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(OLDWOODZ + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = OLDWOODZ;
				}
				ImGui::SameLine(); HelpMarker("(38)","GLASS");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(GLASS + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = GLASS;
				}
				HelpMarker("(39)", "GRID");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(GRID + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = GRID;
				}
				ImGui::SameLine(); HelpMarker("(40)","STARS");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(STARS + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = STARS;
				}
				HelpMarker("(41)", "STARS_SKY");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(STARS_SKY + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = STARS_SKY;
				}
				ImGui::SameLine(); HelpMarker("(42)","CEIL1");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(CEIL1 + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = CEIL1;
				}
				HelpMarker("(43)","CEIL2");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(CEIL2 + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = CEIL2;
				}
				ImGui::TreePop();
			}
            if (ImGui::TreeNodeEx("Object4D Texture2", 0))
			{
				HelpMarker("(1) ","PURE_RED");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(PURE_RED + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = PURE_RED;
				}
				ImGui::SameLine(); HelpMarker("(2) ","PURE_RED_HARFGREEN");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(PURE_RED_HARFGREEN + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = PURE_RED_HARFGREEN;
				}
				HelpMarker("(3) ","PURE_RED_GREEN");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(PURE_RED_GREEN + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = PURE_RED_GREEN;
				}
				ImGui::SameLine(); HelpMarker("(4) ","PURE_HARFRED_GREEN");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(PURE_HARFRED_GREEN + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = PURE_HARFRED_GREEN;
				}
				HelpMarker("(5) ","PURE_GREEN");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(PURE_GREEN + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = PURE_GREEN;
				}
				ImGui::SameLine(); HelpMarker("(6) ","PURE_GREEN_HARFBLUE");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(PURE_GREEN_HARFBLUE + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = PURE_GREEN_HARFBLUE;
				}
				HelpMarker("(7) ","PURE_GREEN_BLUE");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(PURE_GREEN_BLUE + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = PURE_GREEN_BLUE;
				}
				ImGui::SameLine(); HelpMarker("(8) ","PURE_HARFGREEN_BLUE");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(PURE_HARFGREEN_BLUE + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = PURE_HARFGREEN_BLUE;
				}
				HelpMarker("(9) ","PURE_BLUE");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(PURE_BLUE + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = PURE_BLUE;
				}
				ImGui::SameLine(); HelpMarker("(10)","PURE_HARFRED_BLUE");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(PURE_HARFRED_BLUE + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = PURE_HARFRED_BLUE;
				}
				HelpMarker("(12)","PURE_RED_BLUE");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(PURE_RED_BLUE + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = PURE_RED_BLUE;
				}
				ImGui::SameLine(); HelpMarker("(13)","PURE_RED_HARFBLUE");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(PURE_RED_HARFBLUE + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = PURE_RED_HARFBLUE;
				}
				HelpMarker("(14)","PURE_WHITE");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(PURE_WHITE + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = PURE_WHITE;
				}
				ImGui::SameLine(); HelpMarker("(15)","PURE_BLACK");
				ImGui::SameLine();
				if (ImGui::ImageButton((ImTextureID)(PURE_BLACK + SAND_SOIL2 + 4), ImVec2(100, 100)))
				{
					this->buildTexture = PURE_BLACK;
				}
				ImGui::TreePop();
			}
			if (ImGui::BeginCombo("Shader Type", buildingShaderText))
			{
				if (ImGui::Selectable("Standard")) {
					this->buildShader = WALLD4;
					buildingShaderText = "Standard";
				}
				if (ImGui::Selectable("Emit")) {
					this->buildShader = EMITD4;
					buildingShaderText = "Emit";
				}
				ImGui::EndCombo();
			}
			ImGui::Checkbox("Specular Reflection",&this->isSpecular);
			ImGui::DragFloat("Metal Reflection",&this->metal,0.01f,0.f,1.f);
			if (ImGui::ColorEdit4("Painting Color", &this->buildColor.x))
			{
				snprintf(paintingColorText, 255, "R%0.01f/G%0.01f/B%0.01f/A%0.01f", this->buildColor.x, this->buildColor.y, this->buildColor.z, this->buildColor.w);
			}
			if (ImGui::BeginCombo("Painting Color", paintingColorText))
			{
				if (ImGui::Selectable("R1/G0.63/B0/A1"))
				{
					this->buildColor = glm::vec4(1.f, 0.63f, 0.f,1.f);
					snprintf(paintingColorText, 255, "R1/G0.63/B0/A1");
				}
				if (ImGui::Selectable("R0.63/G1/B0/A1"))
				{
					this->buildColor = glm::vec4(0.63f, 1.f, 0.f,1.f);
					snprintf(paintingColorText, 255, "R0.63/1/B0/A1");
				}
				if (ImGui::Selectable("R1/G0/B0.63/A1"))
				{
					this->buildColor = glm::vec4(1.f, 0.f, 0.63f,1.f);
					snprintf(paintingColorText, 255, "R1/G0/B0.63/A1");
				}
				if (ImGui::Selectable("R0.63/0/B1/A1"))
				{
					this->buildColor = glm::vec4(0.63f, 0.f, 1.f,1.f);
					snprintf(paintingColorText, 255, "R0.63/0/B/A11");
				}
				if (ImGui::Selectable("R0/G1/B0.63/A1"))
				{
					this->buildColor = glm::vec4(0.f, 1.f, 0.63f,1.f);
					snprintf(paintingColorText, 255, "R0/G1/B0.63/A1");
				}
				if (ImGui::Selectable("R0/G0.63/B1/A1"))
				{
					this->buildColor = glm::vec4(0.f, 0.63f, 1.f,1.f);
					snprintf(paintingColorText, 255, "R0/0.63/B1/A1");
				}
				if (ImGui::Selectable("R1/G0/B0/A1"))
				{
					this->buildColor = glm::vec4(1.f, 0.f, 0.f,1.f);
					snprintf(paintingColorText, 255, "R1/G0/B0/A1");
				}
				if (ImGui::Selectable("R1/G0.5/B0/A1"))
				{
					this->buildColor = glm::vec4(1.f, 0.5f, 0.f,1.f);
					snprintf(paintingColorText, 255, "R1/G0.5/B0/A1");
				}
				if (ImGui::Selectable("R1/G1/B0/A1"))
				{
					this->buildColor = glm::vec4(1.f, 1.f, 0.f,1.f);
					snprintf(paintingColorText, 255, "R1/G1/B0/A1");
				}
				if (ImGui::Selectable("R0.5/G1/B0/A1"))
				{
					this->buildColor = glm::vec4(0.5f, 1.f, 0.f,1.f);
					snprintf(paintingColorText, 255, "R0.5/G1/B0/A1");
				}
				if (ImGui::Selectable("R0/G1/B0/A1"))
				{
					this->buildColor = glm::vec4(0.f, 1.f, 0.f,1.f);
					snprintf(paintingColorText, 255, "R0/G1/B0/A1");
				}
				if (ImGui::Selectable("R0/G1/B0.5/A1"))
				{
					this->buildColor = glm::vec4(0.f, 1.f, 0.5f,1.f);
					snprintf(paintingColorText, 255, "R0/G1/B0.5/A1");
				}
				if (ImGui::Selectable("R0/G1/B1/A1"))
				{
					this->buildColor = glm::vec4(0.f, 1.f, 1.f,1.f);
					snprintf(paintingColorText, 255, "R0/G1/B1/A1");
				}
				if (ImGui::Selectable("R0/G0.5/B1/A1"))
				{
					this->buildColor = glm::vec4(0.f, 0.5f, 1.f,1.f);
					snprintf(paintingColorText, 255, "R0/G0.5/B1/A1");
				}
				if (ImGui::Selectable("R0/G0/B1/A1"))
				{
					this->buildColor = glm::vec4(0.f, 0.f, 1.f,1.f);
					snprintf(paintingColorText, 255, "R0/G0/B1/A1");
				}
				if (ImGui::Selectable("R0.5/G0/B1/A1"))
				{
					this->buildColor = glm::vec4(0.5f, 0.f, 1.f,1.f);
					snprintf(paintingColorText, 255, "R0.5/G0/B1/A1");
				}
				if (ImGui::Selectable("R1/G0/B1/A1"))
				{
					this->buildColor = glm::vec4(1.f, 0.f, 1.f,1.f);
					snprintf(paintingColorText, 255, "R1/G0/B1/A1");
				}
				if (ImGui::Selectable("R1/G0/B0.5/A1"))
				{
					this->buildColor = glm::vec4(1.f, 0.f, 0.5f,1.f);
					snprintf(paintingColorText, 255, "R1/G0/B0.5/A1");
				}
				if (ImGui::Selectable("R1/G1/B1/A1"))
				{
					this->buildColor = glm::vec4(1.f, 1.f, 1.f,1.f);
					snprintf(paintingColorText, 255, "R1/G1/B1/A1");
				}
				if (ImGui::Selectable("R0/G0/B0/A1"))
				{
					this->buildColor = glm::vec4(0.f, 0.f, 0.f,1.f);
					snprintf(paintingColorText, 255, "R0/G0/B0/A1");
				}
				if (ImGui::Selectable("R0.5/G1/B0.5/A1"))
				{
					this->buildColor = glm::vec4(0.5f, 1.f, 0.5f,1.f);
					snprintf(paintingColorText, 255, "R0.5/G1/B0.5/A1");
				}
				if (ImGui::Selectable("R1/G0.75/B0.5/A1"))
				{
					this->buildColor = glm::vec4(1.f, 0.75f, 0.5f,1.f);
					snprintf(paintingColorText, 255, "R1/G0.75/B0.5/A1");
				}
				if (ImGui::Selectable("R1.85/G1.85/B1.85/A1"))
				{
					this->buildColor = glm::vec4(1.85f, 1.85f, 1.85f, 1.f);
					snprintf(paintingColorText, 255, "R1.85/G1.85/B1.85/A1");
				}
				if (ImGui::Selectable("R2/G2/B2/A1"))
				{
					this->buildColor = glm::vec4(2.f, 2.f, 2.f, 1.f);
					snprintf(paintingColorText, 255, "R2/G2/B2/A1");
				}
				ImGui::EndCombo();
			}
			
			//if (ImGui::ImageButton((ImTextureID)(BUILD_WALL+WALL + SAND_SOIL2 + 5), ImVec2(100, 100)))
			//{
			//	this->targetIcon->logo = this->pointerTexs[BUILDING];
			//	this->mode = BUILDING;
			//
			//	this->buildMode = BUILD_WALL;
			//
			//	this->shaders[TERRAIND4]->use();
			//	this->shaders[TERRAIND4]->set1i(this->mode == PAINTING, "isPainting");
			//	this->shaders[TERRAIND4]->set1i(this->mode == BUILDING, "isBuilding");
			//	this->shaders[TERRAIND4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
			//}
			//ImGui::SameLine(); ImGui::Text("Wall4D");
			ImGui::DragFloat4("Object4D Scale", &this->buildScale.x, 0.5f, 0.f, 100.f);

			ImGui::Text("Object4D Rotation");
			ImGui::DragFloat3("xy,xz,xw0", &this->buildRotation.xy);
			ImGui::DragFloat3("yz,yw,zw0", &this->buildRotation.yz);

			ImGui::Text("(1)Mass (2)Inertia Scalar");
			ImGui::Text("(3)Frictions (4)Restitution");
			ImGui::DragFloat4("", &this->buildParameter.x, 0.1f, 0.f, 20.f);

			if (ImGui::BeginCombo("Building Collider", buildingColText))
			{
				if (ImGui::Selectable("Sphere4D"))
				{
					this->buildCol = HYPERSPHERE;
					buildingColText = "Sphere4D";
				}
				if (ImGui::Selectable("Box4D"))
				{
					this->buildCol = HYPERCUBE;
					buildingColText = "Box4D";
				}
				if (ImGui::Selectable("Capsule4D"))
				{
					this->buildCol = HYPERCAPSULE;
					buildingColText = "Capsule4D";
				}
				if (ImGui::Selectable("Cylinder4D"))
				{
					this->buildCol = HYPERCYLINDER;
					buildingColText = "Cylinder4D";
				}
				if (ImGui::Selectable("Cone4D"))
				{
					this->buildCol = HYPERCONE;
					buildingColText = "Cone4D";
				}
				if (ImGui::Selectable("Pot4D"))
				{
					this->buildCol = HYPERPOT;
					buildingColText = "Pot4D";
				}
				if (ImGui::Selectable("TriPrism"))
				{
					this->buildCol = TRIPRISM;
					buildingColText = "TriPrism";
				}
				if (ImGui::Selectable("Hyperslope"))
				{
					this->buildCol = HYPERSLOPE;
					buildingColText = "Hyperslope";
				}
				if (ImGui::Selectable("Quad4D"))
				{
					this->buildCol = HYPERQUAD;
					buildingColText = "Quad4D";
				}
				if (ImGui::Selectable("Pentachoron"))
				{
					this->buildCol = PENTACHORON;
					buildingColText = "Pentachoron";
				}
				if (ImGui::Selectable("Pyramid4D"))
				{
					this->buildCol = HYPERPYRAMID;
					buildingColText = "Pyramid4D";
				}
				if (ImGui::Selectable("Hexadecachoron"))
				{
					this->buildCol = HEXADECACHORON;
					buildingColText = "Hexadecachoron";
				}
				if (ImGui::Selectable("Hexacosichoron"))
				{
					this->buildCol = HEXACOSICHORON;
					buildingColText = "Hexacosichoron";
				}
				ImGui::EndCombo();
			}

			
			if (ImGui::ImageButton((ImTextureID)(BUILD_OBJECT + CEIL2 + SAND_SOIL2 + 5), ImVec2(100, 100)))
			{
				this->targetIcon->logo = this->pointerTexs[BUILDING];
				this->mode = BUILDING;

				this->buildMode = BUILD_OBJECT;
				this->shaders[WALLD4]->use();
				this->shaders[WALLD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
				this->shaders[EMITD4]->use();
				this->shaders[EMITD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
				this->shaders[TERRAIND4]->use();
				this->shaders[TERRAIND4]->set1i(this->mode == PAINTING, "isPainting");
				this->shaders[TERRAIND4]->set1i(this->mode == BUILDING, "isBuilding");
				this->shaders[TERRAIND4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
				this->shaders[SKY_BOXD4]->use();
				this->shaders[SKY_BOXD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
			}
			ImGui::SameLine(); ImGui::Text("Object4D");

			ImGui::DragFloat4("Initial Velocity", &this->initialVelocity.x, 0.1f, -100.f, 100.f);

			ImGui::Text("Initial Angular Velocity");
			ImGui::DragFloat3("xy,xz,xw1", &this->initialAngularVelocity.xy);
			ImGui::DragFloat3("yz,yw,zw1", &this->initialAngularVelocity.yz);

			if (ImGui::Checkbox("Use Light", &this->isIlluminate))
			{
				if (this->pointLights4D.size() >= 12)
				{
					this->isIlluminate = false;
				}
			}
			if (this->isIlluminate)
			{
				ImGui::DragFloat("Light Intensity", &this->lightIntensity, 0.1f, 0.f, 20.f);
				if (ImGui::ColorEdit3("Light Color", &this->lightColor.x))
				{
				}
				ImGui::DragFloat("Light Radius", &this->lightRadius, 0.1f, 0.f, 20.f);
			}
			ImGui::Checkbox("Use Gravity",&this->isGravity);

			if (ImGui::ImageButton((ImTextureID)(BUILD_RIGIDBODY + CEIL2 + SAND_SOIL2 + 5), ImVec2(100, 100)))
			{
				this->targetIcon->logo = this->pointerTexs[BUILDING];
				this->mode = BUILDING;

				this->buildMode = BUILD_RIGIDBODY;
				this->shaders[WALLD4]->use();
				this->shaders[WALLD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
				this->shaders[EMITD4]->use();
				this->shaders[EMITD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
				this->shaders[TERRAIND4]->use();
				this->shaders[TERRAIND4]->set1i(this->mode == PAINTING, "isPainting");
				this->shaders[TERRAIND4]->set1i(this->mode == BUILDING, "isBuilding");
				this->shaders[TERRAIND4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
				this->shaders[SKY_BOXD4]->use();
				this->shaders[SKY_BOXD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
			}

			ImGui::SameLine();ImGui::Text("Rigid Body4D");
			
			
			if (ImGui::ImageButton((ImTextureID)(BUILD_POOL_TABLE + CEIL2 + SAND_SOIL2 + 5), ImVec2(100, 100)))
			{
				this->targetIcon->logo = this->pointerTexs[BUILDING];
				this->mode = BUILDING;

				this->buildMode = BUILD_POOL_TABLE;
				this->shaders[WALLD4]->use();
				this->shaders[WALLD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
				this->shaders[EMITD4]->use();
				this->shaders[EMITD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
				this->shaders[TERRAIND4]->use();
				this->shaders[TERRAIND4]->set1i(this->mode == PAINTING, "isPainting");
				this->shaders[TERRAIND4]->set1i(this->mode == BUILDING, "isBuilding");
				this->shaders[TERRAIND4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
				this->shaders[SKY_BOXD4]->use();
				this->shaders[SKY_BOXD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
			}
			ImGui::SameLine();ImGui::Text("Pool Table4D");

			if (ImGui::ImageButton((ImTextureID)(BUILD_BILLIARD + CEIL2 + SAND_SOIL2 + 5), ImVec2(100, 100)))
			{
				this->targetIcon->logo = this->pointerTexs[BUILDING];
				this->mode = BUILDING;

				this->buildMode = BUILD_BILLIARD;
				this->shaders[WALLD4]->use();
				this->shaders[WALLD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
				this->shaders[EMITD4]->use();
				this->shaders[EMITD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
				this->shaders[TERRAIND4]->use();
				this->shaders[TERRAIND4]->set1i(this->mode == PAINTING, "isPainting");
				this->shaders[TERRAIND4]->set1i(this->mode == BUILDING, "isBuilding");
				this->shaders[TERRAIND4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
				this->shaders[SKY_BOXD4]->use();
				this->shaders[SKY_BOXD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
			}
			ImGui::SameLine(); ImGui::Text("Billiard4D");

			if (ImGui::BeginCombo("Dynamite Type", dynamiteTypeText))
			{
				if (ImGui::Selectable("Rigid Body4D"))
				{
					this->isRigidBody = true;
					dynamiteTypeText = "Rigid Body4D";
				}
				if (ImGui::Selectable("WALL4D"))
				{
					this->isRigidBody = false;
					dynamiteTypeText = "WALL4D";
				}
				ImGui::EndCombo();
			}
			if (ImGui::ImageButton((ImTextureID)(BUILD_DYNAMITE + CEIL2 + SAND_SOIL2 + 5), ImVec2(100, 100)))
			{
				this->targetIcon->logo = this->pointerTexs[BUILDING];
				this->mode = BUILDING;

				this->buildMode = BUILD_DYNAMITE;
				this->shaders[WALLD4]->use();
				this->shaders[WALLD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
				this->shaders[EMITD4]->use();
				this->shaders[EMITD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
				this->shaders[TERRAIND4]->use();
				this->shaders[TERRAIND4]->set1i(this->mode == PAINTING, "isPainting");
				this->shaders[TERRAIND4]->set1i(this->mode == BUILDING, "isBuilding");
				this->shaders[TERRAIND4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
				this->shaders[SKY_BOXD4]->use();
				this->shaders[SKY_BOXD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
			}
			ImGui::SameLine(); ImGui::Text("Dynamite4D");
			
			ImGui::DragFloat("Stick Length", &this->stickLength, 0.1f, 0.f, 20.f);
			if (ImGui::ImageButton((ImTextureID)(BUILD_STICK + CEIL2 + SAND_SOIL2 + 5), ImVec2(100, 100)))
			{
				this->targetIcon->logo = this->pointerTexs[BUILDING];
				this->mode = BUILDING;

				this->buildMode = BUILD_STICK;
				this->shaders[WALLD4]->use();
				this->shaders[WALLD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
				this->shaders[EMITD4]->use();
				this->shaders[EMITD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
				this->shaders[TERRAIND4]->use();
				this->shaders[TERRAIND4]->set1i(this->mode == PAINTING, "isPainting");
				this->shaders[TERRAIND4]->set1i(this->mode == BUILDING, "isBuilding");
				this->shaders[TERRAIND4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
				this->shaders[SKY_BOXD4]->use();
				this->shaders[SKY_BOXD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
			}
			ImGui::SameLine(); ImGui::Text("Stick Joint");
			
			ImGui::DragFloat("Spring Length", &this->springLength, 0.1f, 0.f, 20.f);
			ImGui::DragFloat("Spring Strength", &this->springStrength, 0.5f, 0.f, 100.f);

			if (ImGui::ImageButton((ImTextureID)(BUILD_SPRING + CEIL2 + SAND_SOIL2 + 5), ImVec2(100, 100)))
			{
				this->targetIcon->logo = this->pointerTexs[BUILDING];
				this->mode = BUILDING;

				this->buildMode = BUILD_SPRING;
				this->shaders[WALLD4]->use();
				this->shaders[WALLD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
				this->shaders[EMITD4]->use();
				this->shaders[EMITD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
				this->shaders[TERRAIND4]->use();
				this->shaders[TERRAIND4]->set1i(this->mode == PAINTING, "isPainting");
				this->shaders[TERRAIND4]->set1i(this->mode == BUILDING, "isBuilding");
				this->shaders[TERRAIND4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
				this->shaders[SKY_BOXD4]->use();
				this->shaders[SKY_BOXD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
			}
			ImGui::SameLine(); ImGui::Text("Spring Joint");
			
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
	if (ImGui::TreeNodeEx("Delete", 2))
	{
		if (ImGui::RadioButton("Deleting Mode", &this->mode, DELETING)) 
		{
			this->targetIcon->logo = this->pointerTexs[DELETING];
			this->shaders[WALLD4]->use();
			this->shaders[WALLD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
			this->shaders[EMITD4]->use();
			this->shaders[EMITD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
			this->shaders[TERRAIND4]->use();
			this->shaders[TERRAIND4]->set1i(this->mode == PAINTING, "isPainting");
			this->shaders[TERRAIND4]->set1i(this->mode == BUILDING, "isBuilding");
			this->shaders[TERRAIND4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
			this->shaders[SKY_BOXD4]->use();
			this->shaders[SKY_BOXD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
		}
		if (ImGui::RadioButton("Select Area To Delete Mode", &this->mode, AREA_DELETING))
		{
			this->targetIcon->logo = this->pointerTexs[AREA_DELETING];
			this->deleteMap3D->unselectArea();
			this->shaders[WALLD4]->use();
			this->shaders[WALLD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
			this->shaders[EMITD4]->use();
			this->shaders[EMITD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
			this->shaders[TERRAIND4]->use();
			this->shaders[TERRAIND4]->set1i(this->mode == PAINTING, "isPainting");
			this->shaders[TERRAIND4]->set1i(this->mode == BUILDING, "isBuilding");
			this->shaders[TERRAIND4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
			this->shaders[SKY_BOXD4]->use();
			this->shaders[SKY_BOXD4]->set1i(this->mode == AREA_DELETING, "isAreaDeleting");
		}

		if (this->mode==AREA_DELETING) 
		{
			if (ImGui::Button("Delete Object In The Area"))
			{
				this->area_delete();
			}
		}
		if (ImGui::Button("Clear Up All 4D Items"))
		{
			for (unsigned int i = 1; i < this->rigidBodies4D.size(); i++)
			{
				this->rigidBodies4D.erase(this->rigidBodies4D.begin() + i);
				erase_point_light4d(&this->pointLights4D,this->shaders[WALLD4], this->shaders[TERRAIND4],i);
				shift_point_light4d(this->pointLights4D, i, -1);
				i--;
			}
			this->dynamites4D2.clear();
			this->dynamites4D.clear();
			this->shifts4D.clear();
			this->floats4D.clear();
			this->hingeConstraints.clear();
			this->rotates4D.clear();
			this->sticks4D.clear();
			this->springs4D.clear();
			update_render_indices(this->rigidBodies4D, this->dynamites4D2, this->groups, this->walls4D, this->dynamites4D, this->sticks4D, this->springs4D, &this->renderIndices1, &this->renderIndices2, this->camera.position4D);
		}
		ImGui::TreePop();
	}

	if (ImGui::Button("Exit"))
	{
		glfwSetWindowShouldClose(this->window, GLFW_TRUE);
	}

	ImGui::End();
	ImGui::Begin("Settings");

	if (ImGui::TreeNodeEx("Display", 2))
	{
		if (ImGui::BeginCombo("Wireframe", frameTypeText))
		{
			if (ImGui::Selectable("No Wireframe")) {
				this->frameType = 0;
				frameTypeText = "No Wireframe";
			}
			if (ImGui::Selectable("Use Wireframe")) {
				this->frameType = 1;
				frameTypeText = "Use Wireframe";
			}
			ImGui::EndCombo();
		}
		ImGui::Checkbox("Display Coordinate Lines 4D", &this->isRenderCoordinate4D);
		if (ImGui::Checkbox("Display Trails 4D", &this->isTrail4D))
		{
			if(!this->isTrail4D)
			for (int i = 0; i < size_of_objects4d(this->rigidBodies4D, this->dynamites4D2); i++)
			{
				find_rigidbody4d(this->rigidBodies4D, this->dynamites4D2, i)->trail4D->reset_to_void();
			}
		}
		ImGui::Checkbox("Display Joint Lines 4D", &this->isJointLine4D);
		if(this->isTrail4D)
		if (ImGui::BeginCombo("Trail Fade Type", trailFadeTypeText))
		{
			if (ImGui::Selectable("Forget")) {
				this->shaders[TRAIL4D]->use();
				this->shaders[TRAIL4D]->set1i(FORGET, "trailFadeType");
				trailFadeTypeText = "Forget";
			}
			if (ImGui::Selectable("Linear")) {
				this->shaders[TRAIL4D]->use();
				this->shaders[TRAIL4D]->set1i(LINEAR, "trailFadeType");
				trailFadeTypeText = "Linear";
			}
			if (ImGui::Selectable("Invarible")) {
				this->shaders[TRAIL4D]->use();
				this->shaders[TRAIL4D]->set1i(INVARIBLE, "trailFadeType");
				trailFadeTypeText = "Invarible";
			}
			ImGui::EndCombo();
		}
		ImGui::TreePop();
	}

	if (ImGui::TreeNodeEx("Controls", 2))
	{
		if (ImGui::InputText("Forward", &this->cMoveForward, 2))
		{
			this->iMoveForward = transformInput(this->cMoveForward);
		}
		if (ImGui::InputText("Backward", &this->cMoveBackward, 2))
		{
			this->iMoveBackward = transformInput(this->cMoveBackward);
		}
		if (ImGui::InputText("Left", &this->cMoveLeft, 2))
		{
			this->iMoveLeft = transformInput(this->cMoveLeft);
		}
		if (ImGui::InputText("Right", &this->cMoveRight, 2))
		{
			this->iMoveRight = transformInput(this->cMoveRight);
		}
		if (ImGui::InputText("Ana", &this->cMoveAna, 2))
		{
			this->iMoveAna = transformInput(this->cMoveAna);
		}
		if (ImGui::InputText("Kata", &this->cMoveKata, 2))
		{
			this->iMoveKata = transformInput(this->cMoveKata);
		}
		if (ImGui::InputText("Camera Turning", &this->cTurnDirection, 2))
		{
			this->iTurnDirection = transformInput(this->cTurnDirection);
		}
		if (ImGui::InputText("Switching Object Rendering Type", &this->cSwitchFrame, 2))
		{
			this->iSwitchFrame = transformInput(this->cSwitchFrame);
		}
		if (ImGui::InputText("Switching 4D Coordinate Lines", &this->cSwitchCoordinate, 2))
		{
			this->iSwitchCoordinate = transformInput(this->cSwitchCoordinate);
		}
		if (ImGui::InputText("Open Close Inventory", &this->cSwitchInventory, 2))
		{
			this->iSwitchInventory = transformInput(this->cSwitchInventory);
		}
		if (ImGui::InputText("Zoom In", &this->cFovIn, 2))
		{
			this->iFovIn = transformInput(this->cFovIn);
		}
		if (ImGui::InputText("Zoom Out", &this->cFovOut, 2))
		{
			this->iFovOut = transformInput(this->cFovOut);
		}
		ImGui::TreePop();
	}
	if (ImGui::TreeNodeEx("Sound", 2))
	{
		if (ImGui::DragFloat("Sound Volume", &this->soundVolume, 0.5f, 0.f, 50.f))
		{
			for (Sound* sound : this->sounds)
			{
				sound->set_volume(this->soundVolume);
			}
		}
		if (ImGui::DragFloat("Sound Pitch", &this->soundPitch, 0.02f, 0.f, 2.f))
		{
			for (Sound* sound : this->sounds)
			{
				sound->set_pitch(this->soundPitch);
			}
		}
		if (ImGui::Checkbox("Playing Music", &this->isPlayingMusic))
		{
			if (!this->isPlayingMusic)
			{
				for (Music* music : this->musics)
				{
					music->stop();
				}
			}
			if (this->isPlayingMusic)
			{
				this->musics[1]->play();
			}
		}
		if (ImGui::DragFloat("Music Volume", &this->musicVolume, 0.5f, 0.f, 50.f))
		{
			for (Music* music : this->musics)
			{
				music->set_volume(this->musicVolume);
			}
		}
		if (ImGui::DragFloat("Music Pitch", &this->musicPitch, 0.02f, 0.f, 2.f))
		{
			for (Music* music : this->musics)
			{
				music->set_pitch(this->musicPitch);
			}
		}
		ImGui::TreePop();
	}
	if (ImGui::TreeNodeEx("Graphic", 2))
	{
		if (ImGui::BeginCombo("Screen Size", (to_string(this->framebufferWidth) + "x" + to_string(this->framebufferHeight)).c_str()))
		{
			if (ImGui::Selectable("3840x2160")) {
				glfwSetWindowSize(window, 3840, 2160);
			}
			if (ImGui::Selectable("2560x1440")) {
				glfwSetWindowSize(window, 2560, 1440);
			}
			if (ImGui::Selectable("1920x1080")) {
				glfwSetWindowSize(window, 1920, 1080);
			}
			if (ImGui::Selectable("1600x900")) {
				glfwSetWindowSize(window, 1600, 900);
			}
			if (ImGui::Selectable("1366x768")) {
				glfwSetWindowSize(window, 1366, 768);
			}
			if (ImGui::Selectable("1280x720")) {
				glfwSetWindowSize(window, 1280, 720);
			}
			if (ImGui::Selectable("1024x576")) {
				glfwSetWindowSize(window, 1024, 576);
			}
			ImGui::EndCombo();
		}
		if (ImGui::Button("Full screen?"))
		{
			if (!this->isFullscreen) {
				glfwSetWindowMonitor(this->window, glfwGetPrimaryMonitor(), 0, 50, this->framebufferWidth, this->framebufferHeight, GLFW_DONT_CARE);
			}
			if (this->isFullscreen) {
				glfwSetWindowMonitor(this->window, NULL, 0, 50, this->framebufferWidth, this->framebufferHeight, GLFW_DONT_CARE);
			}
			this->isFullscreen = !this->isFullscreen;
			glfwSwapInterval(this->vsync);
		}
		if (ImGui::BeginCombo("Swap interval", ("Swap interval " + to_string(this->vsync)).c_str()))
		{
			if (ImGui::Selectable("Unable vsync")) {
				this->vsync = 0;
				glfwSwapInterval(this->vsync);
			}
			if (ImGui::Selectable("VsyncI")) {
				this->vsync = 1;
				glfwSwapInterval(this->vsync);
			}
			if (ImGui::Selectable("VsyncII")) {
				this->vsync = 2;
				glfwSwapInterval(this->vsync);
			}
			ImGui::EndCombo();
		}
		ImGui::TreePop();
	}
	if (ImGui::TreeNodeEx("Camera", 2))
	{
		if (ImGui::DragFloat("Fov", &this->fov, 1.0f, -180.f, 180.f))
		{
			this->updateProjectMat();
	    }
		if (ImGui::DragFloat("Near plane", &this->nearPlane, 0.01f, 0.01f, 1.f))
		{
			this->updateProjectMat();
	    }
		ImGui::DragInt2("Block(s) Object(s) load distance", &this->blockLoadDistance, 0.25f, 1);
		if (ImGui::Checkbox("Cloud", &this->isCloud)) {
			this->shaders[WALLD4]->use();
			this->shaders[WALLD4]->set1i(this->isCloud, "isCloud");
			this->shaders[SKY_BOXD4]->use();
			this->shaders[SKY_BOXD4]->set1i(this->isCloud, "isCloud");
			this->shaders[WATERD4]->use();
			this->shaders[WATERD4]->set1i(this->isCloud, "isCloud");
		}
		if(ImGui::Checkbox("Fog", &this->isFog)){
			this->shaders[WALLD4]->use();
			this->shaders[WALLD4]->set1i(this->isFog, "isFog");
			this->shaders[EMITD4]->use();
			this->shaders[EMITD4]->set1i(this->isFog, "isFog");
			this->shaders[TERRAIND4]->use();
			this->shaders[TERRAIND4]->set1i(this->isFog, "isFog");
			this->shaders[WATERD4]->use();
			this->shaders[WATERD4]->set1i(this->isFog, "isFog");
	    }
		if (this->isFog){
			if (ImGui::DragFloat("Fog density", &this->fogDensity, 0.05f, 0.f, 10.f)) {
				this->shaders[WALLD4]->use();
				this->shaders[WALLD4]->set1f(this->fogDensity, "fogDensity");
				this->shaders[EMITD4]->use();
				this->shaders[EMITD4]->set1f(this->fogDensity, "fogDensity");
				this->shaders[TERRAIND4]->use();
				this->shaders[TERRAIND4]->set1f(this->fogDensity, "fogDensity");
				this->shaders[WATERD4]->use();
				this->shaders[WATERD4]->set1f(this->fogDensity, "fogDensity");
			}
	    }
		
	if (ImGui::BeginCombo("Texture Filter", textureFilterText))
	{
		if (ImGui::Selectable("Mag:Nearest/Min:Nearest"))
		{
			this->filterType = 0;
			textureFilterText = "Mag:Nearest/Min:Nearest";
			for (Texture3D* i : this->textures3D)i->set_filter(this->filterType);
			for (Texture3D* i : this->particleTexs3D)i->set_filter(this->filterType);
			for (Texture3D* i : this->wallTexs3D)i->set_filter(this->filterType);
			for (Texture3D* i : this->groundTexs3D)i->set_filter(this->filterType);
		}
		if (ImGui::Selectable("Mag:Nearest/Min:Nearest Mipmap Linear"))
		{
			this->filterType = 1;
			textureFilterText = "Mag:Nearest/Min:Nearest Mipmap Linear";
			for (Texture3D* i : this->textures3D)i->set_filter(this->filterType);
			for (Texture3D* i : this->particleTexs3D)i->set_filter(this->filterType);
			for (Texture3D* i : this->wallTexs3D)i->set_filter(this->filterType);
			for (Texture3D* i : this->groundTexs3D)i->set_filter(this->filterType);
		}
		if (ImGui::Selectable("Mag:Linear/Min:Linear"))
		{
			this->filterType = 2;
			textureFilterText = "Mag:Linear/Min:Linear";
			for (Texture3D* i : this->textures3D)i->set_filter(this->filterType);
			for (Texture3D* i : this->particleTexs3D)i->set_filter(this->filterType);
			for (Texture3D* i : this->wallTexs3D)i->set_filter(this->filterType);
			for (Texture3D* i : this->groundTexs3D)i->set_filter(this->filterType);
		}
		if (ImGui::Selectable("Mag:Linear/Min:Linear Mipmap Linear"))
		{
			this->filterType = 3;
			textureFilterText = "Mag:Linear/Min:Linear Mipmap Linear";
			for (Texture3D* i : this->textures3D)i->set_filter(this->filterType);
			for (Texture3D* i : this->particleTexs3D)i->set_filter(this->filterType);
			for (Texture3D* i : this->wallTexs3D)i->set_filter(this->filterType);
			for (Texture3D* i : this->groundTexs3D)i->set_filter(this->filterType);
		}
		ImGui::EndCombo();
	}
	ImGui::TreePop();
	}
	if (ImGui::Button("Set to default"))
	{
		this->startDefault();
	}
	ImGui::End();
	ImGui::Begin("Information");
	ImGui::Text("(%.1f FPS) %.3f ms/frame Application average", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Spacing();
	ImGui::Text("Camera:");
	ImGui::Text("(%.1f x %.1f y %.1f z %.1f w) m Position", this->camera.position4D.x, this->camera.position4D.y, this->camera.position4D.z, this->camera.position4D.w);
	ImGui::Text("(%.1f xy %.1f xz %.1f xw %.1f yz %.1f yw %.1f zw) бу Rotation", this->camera.rotateAngle4D.xy, this->camera.rotateAngle4D.xz, this->camera.rotateAngle4D.xw, this->camera.rotateAngle4D.yz, this->camera.rotateAngle4D.yw, this->camera.rotateAngle4D.zw);
	ImGui::Text("(%.1f x %.1f y %.1f z %.1f w) %.1f m/s Speed", this->rigidBodies4D[0]->velocity4D.x, this->rigidBodies4D[0]->velocity4D.y, this->rigidBodies4D[0]->velocity4D.z, this->rigidBodies4D[0]->velocity4D.w, length(this->rigidBodies4D[0]->velocity4D));
	ImGui::Spacing();
	ImGui::Text("Screen:");
	ImGui::Text("%1i px Frame buffer width %1i px Frame buffer height", this->framebufferWidth, this->framebufferHeight);
	if (this->isFullscreen)
		ImGui::Text("Full mode");
	if (!this->isFullscreen)
		ImGui::Text("Windowed mode");
	ImGui::Spacing();
	ImGui::Text("Other:");
	ImGui::Text("level %1i", this->level);
	ImGui::Text("%.1f s World Time", this->worldTime);
	ImGui::Text("%.1f s Play Time", this->curTime);
	ImGui::Text("%1i Swap interval", this->vsync);
	ImGui::Text("%.1f Degree Fov", this->fov);
	ImGui::Text("%.1f m Near Plane", this->nearPlane);
	ImGui::Spacing();
	ImGui::Text("Load amount:");
	ImGui::Text("%1i Object(s) %1i Rigid Body(s) %1i Light(s)", size_of_objects4d(this->rigidBodies4D, this->dynamites4D2, this->groups, this->walls4D, this->dynamites4D), size_of_objects4d(this->rigidBodies4D, this->dynamites4D2), this->pointLights4D.size());
	ImGui::Text("%1i Sticks(s) %1i Spring(s) %1i Hinge(s)", this->sticks4D.size(), this->springs4D.size(),this->hingeConstraints.size());
	int particlesCount = 0;
	for (Emitter4D* i : this->emitters4D)
	{
		particlesCount += i->particles4D.size();
	}
	ImGui::Text("%1i Particle(s)", particlesCount);
	ImGui::Text("%1i Displacement(s) %1i Floating(s) %1i Rotating(s) Animation", this->shifts4D.size(), this->floats4D.size(), this->rotates4D.size());
	ImGui::Text("Load distance:");
	ImGui::Text("(%1i m) Block (%1i m) Object", this->blockLoadDistance, this->objectLoadDistance);
	ImGui::Spacing();
	ImGui::Text("Glfw version:");
	ImGui::Text("%1i Major %1i Minor", this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR);
	if (ImGui::TreeNodeEx("Controls", 2))
	{
		ImGui::Text("Press W/S/A/D/R/F: players move forward, backward, left, right, ana, and kata");
		ImGui::Text("Space: jump");
		ImGui::Text("Double press Space: fly or land");
		ImGui::Text("Double press W: run");
		ImGui::Text("Move the mouse: move the player's perspective within a three-dimensional plane");
		ImGui::Text("Left click on the mouse: move the player's perspective and move the 3D section");
		ImGui::Text("In control mode");
		ImGui::Text("Press Right click :drag an object");
		ImGui::Text("Left and right mouse buttons :throw objects");
		ImGui::Text("In other modes");
		ImGui::Text("Right click on the mouse :execute the corresponding behavior");
		ImGui::Text("I: turn on or off the UI");
		ImGui::Text("C: Turn on or off the world coordinate system lines");
		ImGui::Text("G: Show or turn off wireframe");
		ImGui::Text("Ctrl: Lift up the construction site");
		ImGui::Text("F2:Captures the window (RGB) and save the image");
		ImGui::Text("Delete: delete the half build joint or delete objects in the selection area");
		ImGui::Text("M/N: Zoom in and out of perspective");
		ImGui::Text("1/2/3/4/5/6 or Mouse wheel: Switching behavior mode");
		ImGui::TreePop();
	}
	ImGui::End();
	ImGui::ShowDemoWindow();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Game::area_delete(){
	this->deleteMap3D->getImageData();
	{
		for (size_t index = 1; index < size_of_objects4d(this->rigidBodies4D, this->dynamites4D2); index++) {
			glm::ivec4 gridPosition4D = glm::ivec4(floor(find_rigidbody4d(this->rigidBodies4D, this->dynamites4D2, index)->position4D));
			if (this->deleteMap3D->isDelete(glm::ivec3(gridPosition4D.w + 64, gridPosition4D.z + 64, gridPosition4D.x + 64)))
			{
				if (find_rigidbody4d(this->rigidBodies4D, this->dynamites4D2, index - 1)->objectName != "Ground")
				{
					//std::cout << "ImageData=" << gridPosition4D.x + 64<< gridPosition4D.z + 64<< gridPosition4D.w + 64 << "\n";
					erase_animation4D(&this->shifts4D, &this->floats4D, &this->rotates4D, index);
					shift_animation4D(this->shifts4D, this->floats4D, this->rotates4D, index, -1);
					erase_joint4d(&this->sticks4D, &this->springs4D, &this->hingeConstraints, index);
					shift_joint4d(this->sticks4D, this->springs4D, this->hingeConstraints, index, -1);
					erase_point_light4d(&this->pointLights4D, this->shaders[WALLD4], this->shaders[TERRAIND4], index);
					shift_point_light4d(this->pointLights4D, index, -1);
					erase_rigidbody4d(&this->rigidBodies4D, &this->dynamites4D2, index);
					index--;
				}
			}
		}
	}
	for (size_t index = 0; index < size_of_walls4d(this->groups); index++) {
		glm::ivec4 gridPosition4D = glm::ivec4(floor(find_wall4d(this->groups, index)->position4D));
		if (this->deleteMap3D->isDelete(glm::ivec3(gridPosition4D.w + 64, gridPosition4D.z + 64, gridPosition4D.x + 64)))
		{
			if (find_wall4d(this->groups, index)->objectName != "Ground")
			{
				//std::cout << "ImageData=" << gridPosition4D.x + 64<< gridPosition4D.z + 64<< gridPosition4D.w + 64 << "\n";
				erase_joint4d(&this->sticks4D, &this->springs4D, &this->hingeConstraints, size_of_objects4d(this->rigidBodies4D, this->dynamites4D2) + index);
				shift_joint4d(this->sticks4D, this->springs4D, this->hingeConstraints, size_of_objects4d(this->rigidBodies4D, this->dynamites4D2) + index, -1);
				erase_wall4d(this->groups, index);
				index--;
			}
		}
	}

	for (size_t index = 0; index < this->walls4D.size(); index++) {
		glm::ivec4 gridPosition4D = glm::ivec4(floor(this->walls4D[index]->position4D));
		if (this->deleteMap3D->isDelete(glm::ivec3(gridPosition4D.w + 64, gridPosition4D.z + 64, gridPosition4D.x + 64)))
		{
			if (this->walls4D[index]->objectName != "Ground")
			{
				erase_joint4d(&this->sticks4D, &this->springs4D, &this->hingeConstraints, size_of_objects4d(this->rigidBodies4D, this->dynamites4D2, this->groups) + index);
				shift_joint4d(this->sticks4D, this->springs4D, this->hingeConstraints, size_of_objects4d(this->rigidBodies4D, this->dynamites4D2, this->groups) + index, -1);
				this->walls4D.erase(this->walls4D.begin() + index);
				index--;
			}
		}
	}

	for (size_t index = 0; index < this->dynamites4D.size(); index++) {
		glm::ivec4 gridPosition4D = glm::ivec4(floor(this->dynamites4D[index]->position4D));
		if (this->deleteMap3D->isDelete(glm::ivec3(gridPosition4D.w + 64, gridPosition4D.z + 64, gridPosition4D.x + 64)))
		{
			erase_joint4d(&this->sticks4D, &this->springs4D, &this->hingeConstraints, size_of_objects4d(this->rigidBodies4D, this->dynamites4D2, this->groups, this->walls4D) + index);
			shift_joint4d(this->sticks4D, this->springs4D, this->hingeConstraints, size_of_objects4d(this->rigidBodies4D, this->dynamites4D2, this->groups, this->walls4D) + index, -1);
			this->dynamites4D.erase(this->dynamites4D.begin() + index);
			index--;
		}
	}

	for (size_t index = 0; index < size_of_objects4d(this->sticks4D,this->springs4D); index++) {
		Object4D* a = find_joint4d(this->sticks4D, this->springs4D, index);
		glm::ivec4 gridPosition4D = glm::ivec4(floor(a->position4D));
		if (this->deleteMap3D->isDelete(glm::ivec3(gridPosition4D.w + 64, gridPosition4D.z + 64, gridPosition4D.x + 64)))
		{
			erase_joint4d0(&this->sticks4D, &this->springs4D, index);
			index--;
		}
	}

	for (size_t index = 0; index < this->pointLights4D.size(); index++) {
		glm::ivec4 gridPosition4D = glm::ivec4(floor(this->pointLights4D[index]->position4D));
		if (this->deleteMap3D->isDelete(glm::ivec3(gridPosition4D.w + 64, gridPosition4D.z + 64, gridPosition4D.x + 64)))
		{
			this->pointLights4D.erase(this->pointLights4D.begin() + index);
			index--;
			update_point_light4d(this->pointLights4D, this->shaders[WALLD4], this->shaders[TERRAIND4]);
		}
	}
	update_render_indices(this->rigidBodies4D, this->dynamites4D2, this->groups, this->walls4D, this->dynamites4D, this->sticks4D, this->springs4D, &this->renderIndices1, &this->renderIndices2, this->camera.position4D);
}
