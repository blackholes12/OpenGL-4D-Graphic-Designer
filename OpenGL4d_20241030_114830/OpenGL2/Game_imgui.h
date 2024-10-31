//#pragma once
#include"Game.h"
#include"imgui/imgui.h"
#include"imgui/imgui_impl_glfw.h"
#include"imgui/imgui_impl_opengl3.h"

char levelText[256]("level 1");
static char savedLevelText[64]("level 1-1");
const char* shootText("Gun");
const char* controlText("Drag");
const char* textureText("Sand");
const char* screenSizeText("");
char cameraDirText('W');
const char* swapIntervalText("vsyncI");
const char* buildingColText("BOX4D");
const char* buildingShaderText("Standard");
char paintingColorText[256]("R1/G1/B1/A1");
const char* metalColorType("None");
const char* paintingShapeText("Sphere");
const char* textureFilterText("Mag:Linear/Min:Linear Mipmap Linear");
bool isGroundTextureUI(false);
bool isObjectTextureUI(false);

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

static void select_object_texture(size_t* textureIndex)
{
	if (isObjectTextureUI)
	{
		ImGui::Begin("Object Textures", &isObjectTextureUI);
		HelpMarker("(1) ", "STONE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(STONE + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = STONE;
		}
		ImGui::SameLine(); HelpMarker("(2) ", "DEFAULTCHESSBOARD2");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(DEFAULTCHESSBOARD2 + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = DEFAULTCHESSBOARD2;
		}
		HelpMarker("(3) ", "YELLOW");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(YELLOW + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = YELLOW;
		}
		ImGui::SameLine(); HelpMarker("(4) ", "GROUND");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(GROUND + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = GROUND;
		}
		HelpMarker("(5) ", "C1");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(C1 + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = C1;
		}
		ImGui::SameLine(); HelpMarker("(6) ", "C2");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(C2 + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = C2;
		}
		HelpMarker("(7) ", "C_2");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(C_2 + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = C_2;
		}
		ImGui::SameLine(); HelpMarker("(8) ", "C3");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(C3 + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = C3;
		}
		HelpMarker("(9) ", "C4");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(C4 + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = C4;
		}
		ImGui::SameLine(); HelpMarker("(10)", "C5");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(C5 + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = C5;
		}
		HelpMarker("(11)", "GRID2");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(GRID2 + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = GRID2;
		}
		ImGui::SameLine(); HelpMarker("(12)", "C6");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(C6 + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = C6;
		}
		HelpMarker("(13)", "CHESSBOARD");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(CHESSBOARD + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = CHESSBOARD;
		}
		ImGui::SameLine(); HelpMarker("(14)", "WHITEWALL");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(WHITEWALL + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = WHITEWALL;
		}
		HelpMarker("(15)", "GREENMARBLE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(GREENMARBLE + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = GREENMARBLE;
		}
		ImGui::SameLine(); HelpMarker("(16)", "WHITEMARBLE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(WHITEMARBLE + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = WHITEMARBLE;
		}
		HelpMarker("(17)", "YELLOWMARBLE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(YELLOWMARBLE + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = YELLOWMARBLE;
		}
		ImGui::SameLine(); HelpMarker("(18)", "MARBLE_GROUND");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(MARBLE_GROUND + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = MARBLE_GROUND;
		}
		HelpMarker("(19)", "DEFAULTCHESSBOARD");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(DEFAULTCHESSBOARD + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = DEFAULTCHESSBOARD;
		}
		ImGui::SameLine(); HelpMarker("(20)", "MARBLE_C1");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(MARBLE_C1 + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = MARBLE_C1;
		}
		HelpMarker("(21)", "MARBLE_C2");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(MARBLE_C2 + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = MARBLE_C2;
		}
		ImGui::SameLine(); HelpMarker("(22)", "MARBLE_C3");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(MARBLE_C3 + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = MARBLE_C3;
		}
		HelpMarker("(23)", "MARBLE_C4");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(MARBLE_C4 + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = MARBLE_C4;
		}
		ImGui::SameLine(); HelpMarker("(24)", "MARBLE_C5");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(MARBLE_C5 + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = MARBLE_C5;
		}
		HelpMarker("(25)", "MARBLE_C6");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(MARBLE_C6 + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = MARBLE_C6;
		}
		ImGui::SameLine(); HelpMarker("(26)", "CHESSBOARDMARBLE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(CHESSBOARDMARBLE + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = CHESSBOARDMARBLE;
		}
		HelpMarker("(27)", "WHITEMAINMARBLE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(WHITEMAINMARBLE + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = WHITEMAINMARBLE;
		}
		ImGui::SameLine(); HelpMarker("(28)", "CONCRETE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(CONCRETE + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = CONCRETE;
		}
		HelpMarker("(29)", "YELLOWCONCRETE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(YELLOWCONCRETE + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = YELLOWCONCRETE;
		}
		ImGui::SameLine(); HelpMarker("(30)", "WHITECONCRETE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(WHITECONCRETE + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = WHITECONCRETE;
		}
		HelpMarker("(31)", "GRASS");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(GRASS + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = GRASS;
		}
		ImGui::SameLine(); HelpMarker("(32)", "WOODX");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(WOODX + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = WOODX;
		}
		HelpMarker("(33)", "WOODY");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(WOODY + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = WOODY;
		}
		ImGui::SameLine(); HelpMarker("(34)", "WOODZ");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(WOODZ + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = WOODZ;
		}
		HelpMarker("(35)", "OLDWOODX");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(OLDWOODX + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = OLDWOODX;
		}
		ImGui::SameLine(); HelpMarker("(36)", "OLDWOODY");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(OLDWOODY + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = OLDWOODY;
		}
		HelpMarker("(37)", "OLDWOODZ");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(OLDWOODZ + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = OLDWOODZ;
		}
		ImGui::SameLine(); HelpMarker("(38)", "GLASS");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(GLASS + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = GLASS;
		}
		HelpMarker("(39)", "GRID");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(GRID + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = GRID;
		}
		ImGui::SameLine(); HelpMarker("(40)", "STARS");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(STARS + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = STARS;
		}
		HelpMarker("(41)", "STARS_SKY");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(STARS_SKY + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = STARS_SKY;
		}
		ImGui::SameLine(); HelpMarker("(42)", "LAVA");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(LAVA + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = LAVA;
		}
		HelpMarker("(43)", "CEIL1");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(CEIL1 + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = CEIL1;
		}
		ImGui::SameLine(); HelpMarker("(44)", "CEIL2");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(CEIL2 + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = CEIL2;
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		HelpMarker("(1) ", "PURE_RED");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(PURE_RED + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = PURE_RED;
		}
		ImGui::SameLine(); HelpMarker("(2) ", "PURE_RED_HARFGREEN");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(PURE_RED_HARFGREEN + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = PURE_RED_HARFGREEN;
		}
		HelpMarker("(3) ", "PURE_RED_GREEN");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(PURE_RED_GREEN + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = PURE_RED_GREEN;
		}
		ImGui::SameLine(); HelpMarker("(4) ", "PURE_HARFRED_GREEN");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(PURE_HARFRED_GREEN + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = PURE_HARFRED_GREEN;
		}
		HelpMarker("(5) ", "PURE_GREEN");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(PURE_GREEN + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = PURE_GREEN;
		}
		ImGui::SameLine(); HelpMarker("(6) ", "PURE_GREEN_HARFBLUE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(PURE_GREEN_HARFBLUE + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = PURE_GREEN_HARFBLUE;
		}
		HelpMarker("(7) ", "PURE_GREEN_BLUE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(PURE_GREEN_BLUE + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = PURE_GREEN_BLUE;
		}
		ImGui::SameLine(); HelpMarker("(8) ", "PURE_HARFGREEN_BLUE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(PURE_HARFGREEN_BLUE + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = PURE_HARFGREEN_BLUE;
		}
		HelpMarker("(9) ", "PURE_BLUE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(PURE_BLUE + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = PURE_BLUE;
		}
		ImGui::SameLine(); HelpMarker("(10)", "PURE_HARFRED_BLUE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(PURE_HARFRED_BLUE + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = PURE_HARFRED_BLUE;
		}
		HelpMarker("(12)", "PURE_RED_BLUE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(PURE_RED_BLUE + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = PURE_RED_BLUE;
		}
		ImGui::SameLine(); HelpMarker("(13)", "PURE_RED_HARFBLUE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(PURE_RED_HARFBLUE + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = PURE_RED_HARFBLUE;
		}
		HelpMarker("(14)", "PURE_WHITE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(PURE_WHITE + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = PURE_WHITE;
		}
		ImGui::SameLine(); HelpMarker("(15)", "PURE_BLACK");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(PURE_BLACK + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = PURE_BLACK;
		}

		ImGui::End();
	}
}

static void select_ground_texture(size_t* textureIndex)
{
	if (isGroundTextureUI)
	{
		ImGui::Begin("Ground Textures", &isGroundTextureUI);
		HelpMarker("(1) ", "Sand");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(SAND + 4), ImVec2(100.f, 100.f)))
		{
			*textureIndex = 0;
		}
		ImGui::SameLine();
		HelpMarker("(2) ", "Snow");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(SNOW + 4), ImVec2(100.f, 100.f)))
		{
			*textureIndex = 1;
		}
		HelpMarker("(3) ", "Ice");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(ICE + 4), ImVec2(100.f, 100.f)))
		{
			*textureIndex = 2;
		}
		ImGui::SameLine();
		HelpMarker("(4) ", "Normal Grass");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(GRASS1 + 4), ImVec2(100.f, 100.f)))
		{
			*textureIndex = 3;
		}
		HelpMarker("(5) ", "Green Grass");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(GRASS2 + 4), ImVec2(100.f, 100.f)))
		{
			*textureIndex = 4;
		}
		ImGui::SameLine();
		HelpMarker("(6) ", "Soil");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(SOIL + 4), ImVec2(100.f, 100.f)))
		{
			*textureIndex = 5;
		}
		HelpMarker("(7) ", "Swamp Grass");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(GRASS3 + 4), ImVec2(100.f, 100.f)))
		{
			*textureIndex = 6;
		}
		ImGui::SameLine();
		HelpMarker("(8) ", "Wild Grass");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(GRASS4 + 4), ImVec2(100.f, 100.f)))
		{
			*textureIndex = 7;
		}
		HelpMarker("(9) ", "Wet Sand");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(SAND_SOIL + 4), ImVec2(100.f, 100.f)))
		{
			*textureIndex = 8;
		}
		ImGui::SameLine();
		HelpMarker("(10)", "Half Wet Sand");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(SAND_SOIL2 + 4), ImVec2(100.f, 100.f)))
		{
			*textureIndex = 9;
		}
		ImGui::End();
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
	if(this->editMode)
	{
		if (ImGui::Begin("Inspector", &this->editMode)) {
			if (!this->editMode)
			{
				this->curserMode = false;
				this->isCloseUI = true;
				glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				this->firstMouse = !this->firstMouse;
				isGroundTextureUI = false, isObjectTextureUI = false;
			}
		}
		Object4D* a(find_object4d(this->rigidBodies4D, this->walls4D, this->sticks4D, this->springs4D, this->hitIndex->n));
		ImGui::Text("Tag");ImGui::SameLine();ImGui::Text(a->objectName);
		if (ImGui::TreeNodeEx("Transform 4D", 2)) {
			glm::vec4 position4D(a->position4D);
			if (ImGui::DragFloat4("Position 4D", &position4D.x, 0.02f))
			{
				a->set_position4D(position4D);
			}
			alg::bivec4 rotation4D(a->rotateAngle4D);
			if (ImGui::DragFloat3("Rotation XY XZ XW", &rotation4D.xy))
			{
				a->set_rotation4D(rotation4D);
			}
			if (ImGui::DragFloat3("Rotation YZ YW ZW", &rotation4D.yz))
			{
				a->set_rotation4D(rotation4D);
			}
			glm::vec4 scale4D(a->scale4D);
			if (ImGui::DragFloat4("Scale 4D", &scale4D.x, 0.02f, 0.f, 100.f))
			{
				a->set_scale4D(scale4D);
			}

			ImGui::Text("Collider");
			ImGui::DragFloat("Friction", &a->mu, 0.02f, 0.f, 100.f);
			ImGui::DragFloat("Restitution", &a->restitution, 0.02f, 0.f, 100.f);
			ImGui::TreePop();
		}
		if (this->hitIndex->n < this->rigidBodies4D.size())
		{
			RigidBody4D* r(this->rigidBodies4D[this->hitIndex->n]);
			select_object_texture(&r->texture3DIndex);
			if (ImGui::TreeNodeEx("RigidBody 4D", 2)) {
				ImGui::Checkbox("Use Gravity", &r->isGravity);
				ImGui::Checkbox("Frozen", &r->isFrozen);
				ImGui::DragFloat("Mass", &r->mass);
				ImGui::DragFloat("Moment Inertia Scalar", &r->momentInertiaScalar);
				ImGui::DragFloat4("Velocity 4D", &r->velocity4D.x);
				ImGui::Text("Angular Velocity");
				ImGui::DragFloat3("xy,xz,xw1", &r->angularVelocity4D.xy);
				ImGui::DragFloat3("yz,yw,zw1", &r->angularVelocity4D.yz);
				ImGui::Checkbox("Specular", &r->isSpecular);
				ImGui::Image((ImTextureID)(r->texture3DIndex + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)); ImGui::SameLine();
				if (ImGui::Button("textures 3D"))
				{
					isObjectTextureUI = !isObjectTextureUI;
				}
				ImGui::ColorEdit4("Painting Color", &r->paintingColor.x);
				ImGui::ColorEdit4("Metal Color", &r->metalColor.x);
				ImGui::TreePop();
			}
		}
		else if (this->hitIndex->n < size_of_objects4d(this->rigidBodies4D, this->walls4D))
		{
			Wall4D* w(this->walls4D[this->hitIndex->n - this->rigidBodies4D.size()]);
			select_object_texture(&w->texture3DIndex);
			if (ImGui::TreeNodeEx("Wall 4D", 2)) {
				ImGui::Checkbox("Specular", &w->isSpecular);
				ImGui::Image((ImTextureID)(w->texture3DIndex + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)); ImGui::SameLine();
				if (ImGui::Button("textures 3D"))
				{
					isObjectTextureUI = !isObjectTextureUI;
				}
				ImGui::ColorEdit4("Painting Color", &w->paintingColor.x);
				ImGui::ColorEdit4("Metal Color", &w->metalColor.x);
				ImGui::TreePop();
			}
		}
		else if (this->hitIndex->n < size_of_objects4d(this->rigidBodies4D, this->walls4D) + this->sticks4D.size())
		{
			Stick4D* s(this->sticks4D[this->hitIndex->n - size_of_objects4d(this->rigidBodies4D, this->walls4D)]);
			select_object_texture(&s->texture3DIndex);
			if (ImGui::TreeNodeEx("Stick Joint 4D", 2)) {
				float stickLength(s->stickLength);
				if (ImGui::DragFloat("Stick Length", &stickLength, 0.02f, 0.f, 100.f))
				{
					s->set_stick_length(stickLength);
				}
				ImGui::Image((ImTextureID)(s->texture3DIndex + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)); ImGui::SameLine();
				if (ImGui::Button("textures 3D"))
				{
					isObjectTextureUI = !isObjectTextureUI;
				}
				ImGui::ColorEdit4("Painting Color", &s->paintingColor.x);
			}
		}
		else if (this->hitIndex->n < size_of_objects4d(this->rigidBodies4D, this->walls4D, this->sticks4D, this->springs4D))
		{
			Spring4D* s(this->springs4D[this->hitIndex->n - size_of_objects4d(this->rigidBodies4D, this->walls4D) - this->sticks4D.size()]);
			select_object_texture(&s->texture3DIndex);
			if (ImGui::TreeNodeEx("Spring Joint 4D", 2)) {
				ImGui::DragFloat("Spring Length", &s->springLength, 0.02f, 0.f, 100.f);
				ImGui::DragFloat("Spring Strength", &s->k, 0.02f, 0.f, 100.f);
				ImGui::Image((ImTextureID)(s->texture3DIndex + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)); ImGui::SameLine();
				if (ImGui::Button("textures 3D"))
				{
					isObjectTextureUI = !isObjectTextureUI;
				}
				ImGui::ColorEdit4("Painting Color", &s->paintingColor.x);
			}
		}
		ImGui::End();
	}
	else
	{
	ImGui::Begin("Options");
	if (ImGui::TreeNodeEx("Levels", 2)) {
		if (ImGui::BeginCombo("Level", levelText))
		{
			for (int i(0); i < 6; i++)
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
				save_file(("resourcefile/saves/"+ (std::string)savedLevelText +".txt").c_str(), 
					this->rigidBodies4D, this->groups, this->walls4D, this->dynamiteIndices, this->terrains4D, this->waters4D,
					this->sticks4D, this->springs4D, this->shifts4D, this->floats4D, this->rotates4D, this->openDoors4D, this->hingeConstraintsVec,
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
		if (ImGui::RadioButton("Selecting Mode", &this->mode, SELECTING)) {
			//this->targetIcon->logo = this->pointerTexs[SHOOTING];
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
		if (ImGui::RadioButton("Shooting Mode", &this->mode, SHOOTING)) {
			//this->targetIcon->logo = this->pointerTexs[SHOOTING];
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
		if (ImGui::BeginCombo("Shooting Type", shootText))
		{
			if (ImGui::Selectable("Gun"))
			{
				this->shootType = 0;
				shootText = "Gun";
			}
			if (ImGui::Selectable("Ray"))
			{
				this->shootType = 1;
				shootText = "Ray";
			}
			ImGui::EndCombo();
		}
		if (this->shootType == 1)
		{
			ImGui::DragInt("Reflection Steps", &this->reflectionSteps, 0.1f, 0, 4096);
		}
		if (ImGui::RadioButton("Controling Mode", &this->mode,CONTROLING)) {
			//this->targetIcon->logo = this->pointerTexs[CONTROLING];
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
				this->controlType = DRAG;
				controlText = "Drag";
			}
			if (ImGui::Selectable("Lunch"))
			{
				this->controlType = LUNCH;
				controlText = "Lunch";
			}
			if (ImGui::Selectable("Softly Drag Object"))
			{
				this->controlType = SOFT_DRAG;
				controlText = "Softly Drag Object";
			}
			if (ImGui::Selectable("Softly Drag Multiple Objects"))
			{
				this->controlType = SOFT_DRAG_MULTIPLY;
				controlText = "Softly Drag Multiple Objects";
			}
			if (ImGui::Selectable("Froze"))
			{
				this->controlType = FROZE;
				controlText = "Froze";
			}
			ImGui::EndCombo();
		}
		if (ImGui::Button("Respawn"))
		{
			this->rigidBodies4D[0] = new RigidBody4D("Player", Hypercapsule(glm::vec4(0.4f, 0.4f, 1.8f, 0.4f)), glm::vec4(0.f, 64.875f, 0.f, 0.f), alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.4f, 0.4f, 1.75f, 0.4f), 65.f, 0.f, 5.7143f, 0.f, true, false, glm::vec4(0.f), alg::bivec4(), true, PURE_WHITE, glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), CAPSULE4D, WALLD4);
			judge_objects(this->groupIndices, this->groups, this->walls4D, this->terrains4D, this->camera.position4D, this->camera.forward4D, this->camera.wDir, this->objectLoadDistance);
			this->groupIndices = judge_groups(this->rigidBodies4D, this->groupIndices, this->groups, this->camera.position4D, this->blockLoadDistance);
			update_render_indices(this->rigidBodies4D, this->groupIndices, this->groups, this->walls4D, this->sticks4D, this->springs4D, &this->renderIndices1, &this->renderIndices2, this->camera.position4D);
			sort_render_indices(&this->renderIndices1); sort_render_indices(&this->renderIndices2);
			update_collide_indices(this->rigidBodies4D, this->groupIndices, this->groups, this->walls4D);
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
			for (size_t i(1); i < this->rigidBodies4D.size(); i++)
			{
				this->rigidBodies4D[i]->isFrozen = false;
				this->rigidBodies4D[i]->isSleep = false;
			}
		}
		if (ImGui::Button("Froze"))
		{
			for (size_t i(1); i < this->rigidBodies4D.size(); i++)
			{
				this->rigidBodies4D[i]->isFrozen = true;
			}
		}
		if (ImGui::BeginCombo("Camera Vertical To", &cameraDirText))
		{
			if (ImGui::Selectable("X"))
			{
				this->camera.fit_direction(0);
				cameraDirText = 'X';
			}
			if (ImGui::Selectable("Y"))
			{
				this->camera.fit_direction(1);
				cameraDirText = 'Y';
			}
			if (ImGui::Selectable("Z"))
			{
				this->camera.fit_direction(2);
				cameraDirText = 'Z';
			}
			if (ImGui::Selectable("W"))
			{
				this->camera.fit_direction(3);
				cameraDirText = 'W';
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
	    		//this->targetIcon->logo = this->pointerTexs[PAINTING];
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
			ImGui::Image((ImTextureID)(this->paintType0 + 4), ImVec2(100.f, 100.f)); ImGui::SameLine();
			if (ImGui::Button("Ground Textures"))
			{
				isGroundTextureUI = !isGroundTextureUI;
			}
	    	ImGui::Checkbox("Hard Edge", &this->isHardPainting);
	    	ImGui::TreePop();
	    }
	ImGui::TreePop();
	}
	if (ImGui::TreeNodeEx("Objects", 2))
	{
		if (ImGui::RadioButton("Building Mode", &this->mode, BUILDING)) 
		{
			//this->targetIcon->logo = this->pointerTexs[BUILDING];
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
			if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
			{
				if (ImGui::BeginTabItem("Generic"))
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
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Shader"))
				{
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
						if (ImGui::Selectable("Water")) {
							this->buildShader = WATERD4;
							buildingShaderText = "Water";
						}
						ImGui::EndCombo();
					}
					ImGui::Image((ImTextureID)(this->buildTexture + SAND_SOIL2 + 5), ImVec2(100.f, 100.f)); ImGui::SameLine();
					if (ImGui::Button("Object Textures"))
					{
						isObjectTextureUI = !isObjectTextureUI;
					}
					if (this->buildShader == WALLD4 || this->buildShader == EMITD4)
					{
						if (ImGui::ColorEdit4("Painting Color", &this->buildColor.x))
						{
							snprintf(paintingColorText, 255, "R%0.01f/G%0.01f/B%0.01f/A%0.01f", this->buildColor.x, this->buildColor.y, this->buildColor.z, this->buildColor.w);
						}
						if (ImGui::BeginCombo("Painting Color", paintingColorText))
						{
							if (ImGui::Selectable("R1/G0.63/B0/A1"))
							{
								this->buildColor = glm::vec4(1.f, 0.63f, 0.f, 1.f);
								snprintf(paintingColorText, 255, "R1/G0.63/B0/A1");
							}
							ImGui::SameLine(); ImGui::ColorButton("R1/G0.63/B0/A1", ImVec4(1.f, 0.63f, 0.f, 1.f));
							if (ImGui::Selectable("R0.63/G1/B0/A1"))
							{
								this->buildColor = glm::vec4(0.63f, 1.f, 0.f, 1.f);
								snprintf(paintingColorText, 255, "R0.63/1/B0/A1");
							}
							ImGui::SameLine(); ImGui::ColorButton("R0.63/G1/B0/A1", ImVec4(0.63f, 1.f, 0.f, 1.f));
							if (ImGui::Selectable("R1/G0/B0.63/A1"))
							{
								this->buildColor = glm::vec4(1.f, 0.f, 0.63f, 1.f);
								snprintf(paintingColorText, 255, "R1/G0/B0.63/A1");
							}
							ImGui::SameLine(); ImGui::ColorButton("R1/G0/B0.63/A1", ImVec4(1.f, 0.f, 0.63f, 1.f));
							if (ImGui::Selectable("R0.63/0/B1/A1"))
							{
								this->buildColor = glm::vec4(0.63f, 0.f, 1.f, 1.f);
								snprintf(paintingColorText, 255, "R0.63/0/B/A11");
							}
							ImGui::SameLine(); ImGui::ColorButton("R0.63/0/B1/A1", ImVec4(0.63f, 0.f, 1.f, 1.f));
							if (ImGui::Selectable("R0/G1/B0.63/A1"))
							{
								this->buildColor = glm::vec4(0.f, 1.f, 0.63f, 1.f);
								snprintf(paintingColorText, 255, "R0/G1/B0.63/A1");
							}
							ImGui::SameLine(); ImGui::ColorButton("R0/G1/B0.63/A1", ImVec4(0.f, 1.f, 0.63f, 1.f));
							if (ImGui::Selectable("R0/G0.63/B1/A1"))
							{
								this->buildColor = glm::vec4(0.f, 0.63f, 1.f, 1.f);
								snprintf(paintingColorText, 255, "R0/0.63/B1/A1");
							}
							ImGui::SameLine(); ImGui::ColorButton("R0/G0.63/B1/A1", ImVec4(0.f, 0.63f, 1.f, 1.f));
							if (ImGui::Selectable("R1/G0/B0/A1"))
							{
								this->buildColor = glm::vec4(1.f, 0.f, 0.f, 1.f);
								snprintf(paintingColorText, 255, "R1/G0/B0/A1");
							}
							ImGui::SameLine(); ImGui::ColorButton("R1/G0/B0/A1", ImVec4(1.f, 0.f, 0.f, 1.f));
							if (ImGui::Selectable("R1/G0.5/B0/A1"))
							{
								this->buildColor = glm::vec4(1.f, 0.5f, 0.f, 1.f);
								snprintf(paintingColorText, 255, "R1/G0.5/B0/A1");
							}
							ImGui::SameLine(); ImGui::ColorButton("R1/G0.5/B0/A1", ImVec4(1.f, 0.5f, 0.f, 1.f));
							if (ImGui::Selectable("R1/G1/B0/A1"))
							{
								this->buildColor = glm::vec4(1.f, 1.f, 0.f, 1.f);
								snprintf(paintingColorText, 255, "R1/G1/B0/A1");
							}
							ImGui::SameLine(); ImGui::ColorButton("R1/G1/B0/A1", ImVec4(1.f, 1.f, 0.f, 1.f));
							if (ImGui::Selectable("R0.5/G1/B0/A1"))
							{
								this->buildColor = glm::vec4(0.5f, 1.f, 0.f, 1.f);
								snprintf(paintingColorText, 255, "R0.5/G1/B0/A1");
							}
							ImGui::SameLine(); ImGui::ColorButton("R0.5/G1/B0/A1", ImVec4(0.5f, 1.f, 0.f, 1.f));
							if (ImGui::Selectable("R0/G1/B0/A1"))
							{
								this->buildColor = glm::vec4(0.f, 1.f, 0.f, 1.f);
								snprintf(paintingColorText, 255, "R0/G1/B0/A1");
							}
							ImGui::SameLine(); ImGui::ColorButton("R0/G1/B0/A1", ImVec4(0.f, 1.f, 0.f, 1.f));
							if (ImGui::Selectable("R0/G1/B0.5/A1"))
							{
								this->buildColor = glm::vec4(0.f, 1.f, 0.5f, 1.f);
								snprintf(paintingColorText, 255, "R0/G1/B0.5/A1");
							}
							ImGui::SameLine(); ImGui::ColorButton("R0/G1/B0.5/A1", ImVec4(0.f, 1.f, 0.5f, 1.f));
							if (ImGui::Selectable("R0/G1/B1/A1"))
							{
								this->buildColor = glm::vec4(0.f, 1.f, 1.f, 1.f);
								snprintf(paintingColorText, 255, "R0/G1/B1/A1");
							}
							ImGui::SameLine(); ImGui::ColorButton("R0/G1/B1/A1", ImVec4(0.f, 1.f, 1.f, 1.f));
							if (ImGui::Selectable("R0/G0.5/B1/A1"))
							{
								this->buildColor = glm::vec4(0.f, 0.5f, 1.f, 1.f);
								snprintf(paintingColorText, 255, "R0/G0.5/B1/A1");
							}
							ImGui::SameLine(); ImGui::ColorButton("R0/G0.5/B1/A1", ImVec4(0.f, 0.5f, 1.f, 1.f));
							if (ImGui::Selectable("R0/G0/B1/A1"))
							{
								this->buildColor = glm::vec4(0.f, 0.f, 1.f, 1.f);
								snprintf(paintingColorText, 255, "R0/G0/B1/A1");
							}
							ImGui::SameLine(); ImGui::ColorButton("R0/G0/B1/A1", ImVec4(0.f, 0.f, 1.f, 1.f));
							if (ImGui::Selectable("R0.5/G0/B1/A1"))
							{
								this->buildColor = glm::vec4(0.5f, 0.f, 1.f, 1.f);
								snprintf(paintingColorText, 255, "R0.5/G0/B1/A1");
							}
							ImGui::SameLine(); ImGui::ColorButton("R0.5/G0/B1/A1", ImVec4(0.5f, 0.f, 1.f, 1.f));
							if (ImGui::Selectable("R1/G0/B1/A1"))
							{
								this->buildColor = glm::vec4(1.f, 0.f, 1.f, 1.f);
								snprintf(paintingColorText, 255, "R1/G0/B1/A1");
							}
							ImGui::SameLine(); ImGui::ColorButton("R1/G0/B1/A1", ImVec4(1.f, 0.f, 1.f, 1.f));
							if (ImGui::Selectable("R1/G0/B0.5/A1"))
							{
								this->buildColor = glm::vec4(1.f, 0.f, 0.5f, 1.f);
								snprintf(paintingColorText, 255, "R1/G0/B0.5/A1");
							}
							ImGui::SameLine(); ImGui::ColorButton("R1/G0/B0.5/A1", ImVec4(1.f, 0.f, 0.5f, 1.f));
							if (ImGui::Selectable("R1/G1/B1/A1"))
							{
								this->buildColor = glm::vec4(1.f, 1.f, 1.f, 1.f);
								snprintf(paintingColorText, 255, "R1/G1/B1/A1");
							}
							ImGui::SameLine(); ImGui::ColorButton("R1/G1/B1/A1", ImVec4(1.f, 1.f, 1.f, 1.f));
							if (ImGui::Selectable("R0/G0/B0/A1"))
							{
								this->buildColor = glm::vec4(0.f, 0.f, 0.f, 1.f);
								snprintf(paintingColorText, 255, "R0/G0/B0/A1");
							}
							ImGui::SameLine(); ImGui::ColorButton("R0/G0/B0/A1", ImVec4(0.f, 0.f, 0.f, 1.f));
							if (ImGui::Selectable("R0.5/G1/B0.5/A1"))
							{
								this->buildColor = glm::vec4(0.5f, 1.f, 0.5f, 1.f);
								snprintf(paintingColorText, 255, "R0.5/G1/B0.5/A1");
							}
							ImGui::SameLine(); ImGui::ColorButton("R0.5/G1/B0.5/A1", ImVec4(0.5f, 1.f, 0.5f, 1.f));
							if (ImGui::Selectable("R1/G0.75/B0.5/A1"))
							{
								this->buildColor = glm::vec4(1.f, 0.75f, 0.5f, 1.f);
								snprintf(paintingColorText, 255, "R1/G0.75/B0.5/A1");
							}
							ImGui::SameLine(); ImGui::ColorButton("R1/G0.75/B0.5/A1", ImVec4(1.f, 0.75f, 0.5f, 1.f));
							if (ImGui::Selectable("R1.85/G1.85/B1.85/A1"))
							{
								this->buildColor = glm::vec4(1.85f, 1.85f, 1.85f, 1.f);
								snprintf(paintingColorText, 255, "R1.85/G1.85/B1.85/A1");
							}
							ImGui::SameLine(); ImGui::ColorButton("R1.85/G1.85/B1.85/A1", ImVec4(1.85f, 1.85f, 1.85f, 1.f));
							if (ImGui::Selectable("R2/G2/B2/A1"))
							{
								this->buildColor = glm::vec4(2.f, 2.f, 2.f, 1.f);
								snprintf(paintingColorText, 255, "R2/G2/B2/A1");
							}
							ImGui::SameLine(); ImGui::ColorButton("R2/G2/B2/A1", ImVec4(2.f, 2.f, 2.f, 1.f));
							ImGui::EndCombo();
						}
						if (this->buildShader == EMITD4)
						{
							if (ImGui::DragFloat3("High Range Color", &this->buildColor.x, 0.01f, 0.f))
							{
								snprintf(paintingColorText, 255, "R2/G2/B2/A1");
							}
						}
						ImGui::Checkbox("Random Color", &this->isRandomColor);
					}
					if (this->buildShader == WALLD4)
					{
						ImGui::Checkbox("Specular Reflection", &this->isSpecular);
						ImGui::ColorEdit4("Metal Color", &this->buildMetalColor.x);
						if (ImGui::BeginCombo("MetalColor", metalColorType))
						{
							if (ImGui::Selectable("Gold"))
							{
								this->buildMetalColor = glm::vec4(1.f,0.766f,0.336f,1.f);
								metalColorType = "Gold";
							}
							ImGui::SameLine();ImGui::ColorButton("Gold", ImVec4(1.f, 0.766f, 0.336f, 1.f));
							if (ImGui::Selectable("Fake Gold"))
							{
								this->buildMetalColor = glm::vec4(255.f, 195.351f, 65.614f, 255.f)/255.f;
								metalColorType = "Fake Gold";
							}
							ImGui::SameLine();ImGui::ColorButton("Fake Gold", ImVec4(255.f / 255.f, 195.351f / 255.f, 65.614f / 255.f, 1.f));
							if (ImGui::Selectable("Silver"))
							{
								this->buildMetalColor = glm::vec4(0.972f,0.960f,0.915f,1.f);
								metalColorType = "Silver";
							}
							ImGui::SameLine();ImGui::ColorButton("Silver", ImVec4(0.972f, 0.960f, 0.915f, 1.f));
							if (ImGui::Selectable("Copper"))
							{
								this->buildMetalColor = glm::vec4(0.955f, 0.637f, 0.538f, 1.f);
								metalColorType = "Copper";
							}
							ImGui::SameLine();ImGui::ColorButton("Copper", ImVec4(0.955f, 0.637f, 0.538f, 1.f));
							if (ImGui::Selectable("Chromium"))
							{
								this->buildMetalColor = glm::vec4(0.550f, 0.556f, 0.554f, 1.f);
								metalColorType = "Chromium";
							}
							ImGui::SameLine();ImGui::ColorButton("Chromium", ImVec4(0.550f, 0.556f, 0.554f, 1.f));
							if (ImGui::Selectable("Nickel"))
							{
								this->buildMetalColor = glm::vec4(0.660f, 0.609f, 0.526f, 1.f);
								metalColorType = "Nickel";
							}
							ImGui::SameLine(); ImGui::ColorButton("Nickel", ImVec4(0.660f, 0.609f, 0.526f, 1.f));
							if (ImGui::Selectable("Titanium"))
							{
								this->buildMetalColor = glm::vec4(0.542f, 0.497f, 0.449f, 1.f);
								metalColorType = "Titanium";
							}
							ImGui::SameLine(); ImGui::ColorButton("Titanium", ImVec4(0.542f, 0.497f, 0.449f, 1.f));
							if (ImGui::Selectable("Cobalt"))
							{
								this->buildMetalColor = glm::vec4(0.662f, 0.655f, 0.634f, 1.f);
								metalColorType = "Cobalt";
							}
							ImGui::SameLine(); ImGui::ColorButton("Cobalt", ImVec4(0.662f, 0.655f, 0.634f, 1.f));
							if (ImGui::Selectable("Black Lead"))
							{
								this->buildMetalColor = glm::vec4(71.f, 76.f, 77.f, 255.f) / 255.f;
								metalColorType = "Black Lead";
							}
							ImGui::SameLine();ImGui::ColorButton("Black Lead", ImVec4(71.f / 255.f, 76.f / 255.f, 77.f / 255.f, 1.f));
							if (ImGui::Selectable("Iron"))
							{
								this->buildMetalColor = glm::vec4(0.560f, 0.570f, 0.580f, 1.f);
								metalColorType = "Iron";
							}
							ImGui::SameLine();ImGui::ColorButton("Iron", ImVec4(0.560f, 0.570f, 0.580f, 1.f));
							if (ImGui::Selectable("Tin"))
							{
								this->buildMetalColor = glm::vec4(211.f, 212.f, 213.f, 255.f) / 255.f;
								metalColorType = "Tin";
							}
							ImGui::SameLine();ImGui::ColorButton("Tin", ImVec4(211.f / 255.f, 212.f / 255.f, 213.f / 255.f, 1.f));
							if (ImGui::Selectable("Aluminium"))
							{
								this->buildMetalColor = glm::vec4(0.913f,0.921f,0.925f,1.f);
								metalColorType = "Aluminium";
							}
							ImGui::SameLine();ImGui::ColorButton("Aluminium", ImVec4(0.913f, 0.921f, 0.925f, 1.f));
							if (ImGui::Selectable("None"))
							{
								this->buildMetalColor = glm::vec4(1.f, 1.f, 1.f, 0.f);
								metalColorType = "None";
							}
							ImGui::SameLine();ImGui::ColorButton("None", ImVec4(1.f, 1.f, 1.f, 0.f));
							ImGui::EndCombo();
						}
					}
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("4D Wall"))
				{
					ImGui::DragFloat2("Build Distance", &this->buildDistance.x, 0.1f, -1.f, 1.f);
					ImGui::DragFloat4("Build Offset", &this->buildOffset.x, 0.1f, -1.f, 1.f);
					if (ImGui::ImageButton((ImTextureID)(BUILD_OBJECT + CEIL2 + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
					{
						//this->targetIcon->logo = this->pointerTexs[BUILDING];
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

					if (ImGui::ImageButton((ImTextureID)(BUILD_POOL_TABLE + CEIL2 + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
					{
						//this->targetIcon->logo = this->pointerTexs[BUILDING];
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
					ImGui::SameLine(); ImGui::Text("Pool Table4D");

					if (ImGui::ImageButton((ImTextureID)(BUILD_DYNAMITE + CEIL2 + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
					{
						//this->targetIcon->logo = this->pointerTexs[BUILDING];
						this->mode = BUILDING;
						this->isRigidBody = false;
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
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("4D Rigid Body"))
				{
					ImGui::DragFloat4("Initial Velocity", &this->initialVelocity.x, 0.1f, -100.f, 100.f);

					ImGui::Text("Initial Angular Velocity");
					ImGui::DragFloat3("xy,xz,xw1", &this->initialAngularVelocity.xy);
					ImGui::DragFloat3("yz,yw,zw1", &this->initialAngularVelocity.yz);

					if (ImGui::Checkbox("Use Light", &this->isIlluminate))
					{
						//if (this->pointLights4D.size() >= 12)
						//{
						//	this->isIlluminate = false;
						//}
					}
					if (this->isIlluminate)
					{
						ImGui::DragFloat("Light Intensity", &this->lightIntensity, 0.1f, 0.f, 20.f);
						if (ImGui::ColorEdit3("Light Color", &this->lightColor.x))
						{
						}
						ImGui::DragFloat("Light Radius", &this->lightRadius, 0.1f, 0.f, 20.f);
					}
					ImGui::Checkbox("Use Gravity", &this->isGravity);

					if (ImGui::ImageButton((ImTextureID)(BUILD_RIGIDBODY + CEIL2 + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
					{
						//this->targetIcon->logo = this->pointerTexs[BUILDING];
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
					ImGui::SameLine(); ImGui::Text("Rigid Body4D");

					if (ImGui::ImageButton((ImTextureID)(BUILD_BILLIARD + CEIL2 + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
					{
						//this->targetIcon->logo = this->pointerTexs[BUILDING];
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

					if (ImGui::ImageButton((ImTextureID)(BUILD_DYNAMITE + CEIL2 + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
					{
						//this->targetIcon->logo = this->pointerTexs[BUILDING];
						this->mode = BUILDING;
						this->isRigidBody = true;
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

					ImGui::EndTabItem();
				}
				
				if (ImGui::BeginTabItem("4D Joint"))
				{
					ImGui::DragFloat("Stick Length", &this->stickLength, 0.1f, 0.f, 20.f);
					if (ImGui::ImageButton((ImTextureID)(BUILD_STICK + CEIL2 + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
					{
						//this->targetIcon->logo = this->pointerTexs[BUILDING];
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

					if (ImGui::ImageButton((ImTextureID)(BUILD_SPRING + CEIL2 + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
					{
						//this->targetIcon->logo = this->pointerTexs[BUILDING];
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
					ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
			}
			
			//if (ImGui::ImageButton((ImTextureID)(BUILD_WALL+WALL + SAND_SOIL2 + 5), ImVec2(100.f,100.f)))
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
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
	if (ImGui::TreeNodeEx("Delete", 2))
	{
		if (ImGui::RadioButton("Deleting Mode", &this->mode, DELETING)) 
		{
			//this->targetIcon->logo = this->pointerTexs[DELETING];
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
			//this->targetIcon->logo = this->pointerTexs[AREA_DELETING];
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
		if (ImGui::Button("Clear Up All 4D Rigid Bodies And Joints"))
		{
			bool isPointLightRemoved(false);
			for (size_t i(1); i < this->rigidBodies4D.size(); i++)
			{
				erase_point_light4d(&this->pointLights4D, this->shaders[WALLD4], this->shaders[TERRAIND4], this->shaders[LIGHT_MAPD3], i);
				shift_point_light4d(this->pointLights4D, i, -1);
				isPointLightRemoved = true;
				this->rigidBodies4D.erase(this->rigidBodies4D.begin() + i);
				i--;
			}
			if (isPointLightRemoved)
			{
				this->shaders[LIGHT_MAPD3]->use();
				this->lightMap3D->bind_image(0);
				glDispatchCompute(4, 128, 4);
				glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
			}
			for (size_t i(0); i < this->dynamiteIndices.size();i++)
			{
				if (this->dynamiteIndices[i]->index == 0)this->dynamiteIndices.erase(this->dynamiteIndices.begin() + i);
			}
			this->shifts4D.clear();
			this->floats4D.clear();
			this->hingeConstraintsVec.clear();
			this->rotates4D.clear();
			this->sticks4D.clear();
			this->springs4D.clear();
			this->openDoors4D.clear();
			//judge_objects(this->groupIndices, this->groups, this->walls4D, this->terrains4D, this->camera.position4D, this->camera.forward4D, this->camera.wDir, this->objectLoadDistance);
			update_render_indices(this->rigidBodies4D, this->groupIndices, this->groups, this->walls4D, this->sticks4D, this->springs4D, &this->renderIndices1, &this->renderIndices2, this->camera.position4D);
			sort_render_indices(&this->renderIndices1); sort_render_indices(&this->renderIndices2);
			update_collide_indices(this->rigidBodies4D, this->groupIndices, this->groups, this->walls4D);
		}
		ImGui::TreePop();
	}

	if (ImGui::Button("Exit"))
	{
		glfwSetWindowShouldClose(this->window, GLFW_TRUE);
	}
	ImGui::End();

	select_ground_texture(&this->paintType0);
	select_object_texture(&this->buildTexture);

	ImGui::Begin("Settings");
	if (ImGui::TreeNodeEx("Display", 2))
	{
		ImGui::Checkbox("Use Wireframe",&this->isFramework);
		if (this->isFramework)
		{
			const int elementCOUNT = 2;
			const char* elemsNames[elementCOUNT] = { "Vertical", "Perspective" };
			if (ImGui::SliderInt("Projection Type", &this->frameworkProjectionType, 0, elementCOUNT - 1, elemsNames[this->frameworkProjectionType]))
			{
				this->shaders[FRAMED4]->use();
				this->shaders[FRAMED4]->set1i(this->frameworkProjectionType, "projectionType");
			}
			if (this->frameworkProjectionType == 1)
			{
				if (ImGui::SliderFloat("projectionScaler", &this->projectionScaler, 0.f, 4.f))
				{
					this->shaders[FRAMED4]->use();
					this->shaders[FRAMED4]->set1f(this->projectionScaler, "projectionScaler");
				}
			}
		}
		ImGui::Checkbox("Display Group Area(s)", &this->isShowingGroupArea);
		ImGui::Checkbox("Display Coordinate Lines 4D", &this->isRenderCoordinate4D);
		if (ImGui::Checkbox("Display Trails 4D", &this->isTrail4D))
		{
			if(!this->isTrail4D)
			for (int i(0); i < this->rigidBodies4D.size(); i++)
			{
				this->rigidBodies4D[i]->trail4D->reset_to_void();
			}
		}
		ImGui::Checkbox("Display Joint Lines 4D", &this->isJointLine4D);
		if (this->isTrail4D)
		{
			const int elementCOUNT = 3;
			const char* elemsNames[elementCOUNT] = { "Forget", "Linear", "Invarible"};
			if (ImGui::SliderInt("Trail Fade Type", &this->trailFadeType, 0, elementCOUNT - 1, elemsNames[this->trailFadeType]))
			{
				this->shaders[TRAILD4]->use();
				this->shaders[TRAILD4]->set1i(this->trailFadeType, "trailFadeType");
				std::cout << this->trailFadeType << '\n';
			}
		}
		ImGui::TreePop();
	}

	if (ImGui::TreeNodeEx("Controls", 2))
	{
		if (ImGui::InputText("Forward", &this->cMoveForward, 2))
		{
			this->iMoveForward = transform_input(this->cMoveForward);
		}
		if (ImGui::InputText("Backward", &this->cMoveBackward, 2))
		{
			this->iMoveBackward = transform_input(this->cMoveBackward);
		}
		if (ImGui::InputText("Left", &this->cMoveLeft, 2))
		{
			this->iMoveLeft = transform_input(this->cMoveLeft);
		}
		if (ImGui::InputText("Right", &this->cMoveRight, 2))
		{
			this->iMoveRight = transform_input(this->cMoveRight);
		}
		if (ImGui::InputText("Ana", &this->cMoveAna, 2))
		{
			this->iMoveAna = transform_input(this->cMoveAna);
		}
		if (ImGui::InputText("Kata", &this->cMoveKata, 2))
		{
			this->iMoveKata = transform_input(this->cMoveKata);
		}
		if (ImGui::InputText("Camera Turning", &this->cTurnDirection, 2))
		{
			this->iTurnDirection = transform_input(this->cTurnDirection);
		}
		if (ImGui::InputText("Switching Object Rendering Type", &this->cSwitchFrame, 2))
		{
			this->iSwitchFrame = transform_input(this->cSwitchFrame);
		}
		if (ImGui::InputText("Switching 4D Coordinate Lines", &this->cSwitchCoordinate, 2))
		{
			this->iSwitchCoordinate = transform_input(this->cSwitchCoordinate);
		}
		if (ImGui::InputText("Open Close Inventory", &this->cSwitchInventory, 2))
		{
			this->iSwitchInventory = transform_input(this->cSwitchInventory);
		}
		if (ImGui::InputText("Zoom In", &this->cFovIn, 2))
		{
			this->iFovIn = transform_input(this->cFovIn);
		}
		if (ImGui::InputText("Zoom Out", &this->cFovOut, 2))
		{
			this->iFovOut = transform_input(this->cFovOut);
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
			if (this->isFullscreen) {
				glfwSetWindowMonitor(this->window, NULL, 0, 50, this->framebufferWidth, this->framebufferHeight, GLFW_DONT_CARE);
			}
			else {
				glfwSetWindowMonitor(this->window, glfwGetPrimaryMonitor(), 0, 50, this->framebufferWidth, this->framebufferHeight, GLFW_DONT_CARE);
			}
			this->isFullscreen = !this->isFullscreen;
			glfwSwapInterval(this->vsync);
		}
		const int elementCOUNT = 3;
		const char* elemsNames[elementCOUNT] = { "Unable Vsync", "Vsync I", "Vsync II" };
		if (ImGui::SliderInt("Swap interval", &this->vsync, 0, elementCOUNT - 1, elemsNames[this->vsync]))
		{
			glfwSwapInterval(this->vsync);
		}
		ImGui::TreePop();
	}
	if (ImGui::TreeNodeEx("Camera", 2))
	{
		if (ImGui::DragFloat("Fov", &this->camera.fov, 1.0f, -180.f, 180.f))
		{
			this->updateProjectMat(this->framebufferWidth, this->framebufferHeight);
	    }
		if (ImGui::DragFloat("Near plane", &this->camera.nearPlane, 0.01f, 0.01f, 1.f))
		{
			this->updateProjectMat(this->framebufferWidth, this->framebufferHeight);
	    }
		ImGui::DragInt2("Block(s) Object(s) load distance", &this->blockLoadDistance, 0.25f, 1, INFINITY);
		if (ImGui::Checkbox("Cloud", &this->isCloud)) {
			this->shaders[WALLD4]->use();
			this->shaders[WALLD4]->set1i(this->isCloud, "isCloud");
			this->shaders[SKY_BOXD4]->use();
			this->shaders[SKY_BOXD4]->set1i(this->isCloud, "isCloud");
			this->shaders[WATERD4]->use();
			this->shaders[WATERD4]->set1i(this->isCloud, "isCloud");
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("Sky Box Fog", &this->isSkyBoxFog)) {
			this->shaders[WALLD4]->use();
			this->shaders[WALLD4]->set1i(this->isSkyBoxFog, "isSkyBoxFog");
			this->shaders[SKY_BOXD4]->use();
			this->shaders[SKY_BOXD4]->set1i(this->isSkyBoxFog, "isSkyBoxFog");
			this->shaders[WATERD4]->use();
			this->shaders[WATERD4]->set1i(this->isSkyBoxFog, "isSkyBoxFog");
		}
		ImGui::SameLine();
		ImGui::Checkbox("HDR", &this->isHDR);
		if (this->isHDR)
		{
			ImGui::Checkbox("Bloom", &this->isBloom);
			if (isBloom)
			{
				if (ImGui::DragFloat("Bloom Brightness", &this->bloomMultiplier, 0.01f, 0.f,INFINITY))
				{
					this->shaderHDRs[BLOOM]->use();
					this->shaderHDRs[BLOOM]->set1f(this->bloomMultiplier, "bloomMultiplier");
				}
			}
			ImGui::Checkbox("Automatic Exposure", &this->isAutoExposure);
			if (this->isAutoExposure)
			{
				ImGui::DragFloat("Exposure Speed", &this->exposureSpeed, 0.01f, 0.f, INFINITY);
				ImGui::DragFloat("Exposure Multiplier", &this->exposureMultiplier, 0.01f, 0.f, INFINITY);
			}
			else
			{
				ImGui::DragFloat("Exposure Brightness", &this->exposure2, 0.01f, 0.f, INFINITY);
			}
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
			for (Texture* i : this->textures)i->set_filter(this->filterType);
			for (Texture* i : this->pointerTexs)i->set_filter(this->filterType);
			for (HDRTexture* i : this->hDRTextures)i->set_filter(this->filterType);
			for (HDRTexture* i : this->bloomExpandMaps)i->set_filter(this->filterType);
			for (Texture3D* i : this->textures3D)i->set_filter(this->filterType);
			for (Texture3D* i : this->particleTexs3D)i->set_filter(this->filterType);
			for (Texture3D* i : this->wallTexs3D)i->set_filter(this->filterType);
			for (Texture3D* i : this->groundTexs3D)i->set_filter(this->filterType);
		}
		if (ImGui::Selectable("Mag:Nearest/Min:Nearest Mipmap Linear"))
		{
			this->filterType = 1;
			textureFilterText = "Mag:Nearest/Min:Nearest Mipmap Linear";
			for (Texture* i : this->textures)i->set_filter(this->filterType);
			for (Texture* i : this->pointerTexs)i->set_filter(this->filterType);
			for (HDRTexture* i : this->hDRTextures)i->set_filter(this->filterType);
			for (HDRTexture* i : this->bloomExpandMaps)i->set_filter(this->filterType);
			for (Texture3D* i : this->textures3D)i->set_filter(this->filterType);
			for (Texture3D* i : this->particleTexs3D)i->set_filter(this->filterType);
			for (Texture3D* i : this->wallTexs3D)i->set_filter(this->filterType);
			for (Texture3D* i : this->groundTexs3D)i->set_filter(this->filterType);
		}
		if (ImGui::Selectable("Mag:Linear/Min:Linear"))
		{
			this->filterType = 2;
			textureFilterText = "Mag:Linear/Min:Linear";
			for (Texture* i : this->textures)i->set_filter(this->filterType);
			for (Texture* i : this->pointerTexs)i->set_filter(this->filterType);
			for (HDRTexture* i : this->hDRTextures)i->set_filter(this->filterType);
			for (HDRTexture* i : this->bloomExpandMaps)i->set_filter(this->filterType);
			for (Texture3D* i : this->textures3D)i->set_filter(this->filterType);
			for (Texture3D* i : this->particleTexs3D)i->set_filter(this->filterType);
			for (Texture3D* i : this->wallTexs3D)i->set_filter(this->filterType);
			for (Texture3D* i : this->groundTexs3D)i->set_filter(this->filterType);
		}
		if (ImGui::Selectable("Mag:Linear/Min:Linear Mipmap Linear"))
		{
			this->filterType = 3;
			textureFilterText = "Mag:Linear/Min:Linear Mipmap Linear";
			for (Texture* i : this->textures)i->set_filter(this->filterType);
			for (Texture* i : this->pointerTexs)i->set_filter(this->filterType);
			for (HDRTexture* i : this->hDRTextures)i->set_filter(this->filterType);
			for (HDRTexture* i : this->bloomExpandMaps)i->set_filter(this->filterType);
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
	ImGui::Text("(%.1f FPS) %.3f ms/frame Application average", 1000.f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("Camera:");
	ImGui::Separator();
	ImGui::Text("(%.1f x %.1f y %.1f z %.1f w) m Position", this->camera.position4D.x, this->camera.position4D.y, this->camera.position4D.z, this->camera.position4D.w);
	ImGui::Text("(%.1f xy %.1f xz %.1f xw %.1f yz %.1f yw %.1f zw) бу Rotation", this->camera.rotateAngle4D.xy, this->camera.rotateAngle4D.xz, this->camera.rotateAngle4D.xw, this->camera.rotateAngle4D.yz, this->camera.rotateAngle4D.yw, this->camera.rotateAngle4D.zw);
	ImGui::Text("(%.1f x %.1f y %.1f z %.1f w) %.1f m/s Speed", this->rigidBodies4D[0]->velocity4D.x, this->rigidBodies4D[0]->velocity4D.y, this->rigidBodies4D[0]->velocity4D.z, this->rigidBodies4D[0]->velocity4D.w, alg::length(this->rigidBodies4D[0]->velocity4D));
	ImGui::Text("Screen:");
	ImGui::Separator();
	ImGui::Text("%1i px Frame buffer width %1i px Frame buffer height", this->framebufferWidth, this->framebufferHeight);
	if (this->isFullscreen)
		ImGui::Text("Full mode");
	if (!this->isFullscreen)
		ImGui::Text("Windowed mode");
	ImGui::Text("Load amount:");
	ImGui::Separator();
	size_t wallLoadedSize(0);
	size_t terrainLoadedSize(0);
	for (size_t groupIndex : groupIndices)
	{
		Group* i(groups[groupIndex]);
		wallLoadedSize += i->walls4DIndices.size();
		terrainLoadedSize += i->terrains4DIndices.size();
	}
	ImGui::Text("%1i Group(s) %1i Group(s) Loaded %1i Object(s) Loaded",this->groups.size()-1,this->groupIndices.size()-1, this->rigidBodies4D.size() + wallLoadedSize + terrainLoadedSize + this->waters4D.size());
	ImGui::Text("%1i Object(s) %1i Rigid Body(s) %1i Light(s)", size_of_objects4d(this->rigidBodies4D, this->walls4D) + this->terrains4D.size() + this->waters4D.size(),
		this->rigidBodies4D.size(), this->pointLights4D.size());
	ImGui::Text("%1i Sticks(s) %1i Spring(s) %1i Hinge(s)", this->sticks4D.size(), this->springs4D.size(),this->hingeConstraintsVec.size());
	int particlesCount(0);
	for (Emitter4D* i : this->emitters4D)
	{
		particlesCount += i->particles4D.size();
	}
	ImGui::Text("%1i Particle(s)", particlesCount);
	ImGui::Text("%1i Displacement(s) %1i Floating(s) %1i Rotating(s) Animation", this->shifts4D.size(), this->floats4D.size(), this->rotates4D.size());
	ImGui::Text("Load distance:");
	ImGui::Text("(%1i m) Block (%1i m) Object", this->blockLoadDistance, this->objectLoadDistance);
	ImGui::Text("Glfw version:");
	ImGui::Separator();
	ImGui::Text("%1i Major %1i Minor", this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR);
	ImGui::Text("Other:");
	ImGui::Separator();
	ImGui::Text("level %1i", this->level);
	ImGui::Text("%.1f s World Time", this->worldTime);
	ImGui::Text("%.1f s Play Time", this->curTime);
	if (ImGui::TreeNodeEx("Controls", 2))
	{
		ImGui::BulletText("Press W/S/A/D/R/F: players move forward, backward, left, right, ana, and kata");
		ImGui::BulletText("Space: jump");
		ImGui::BulletText("Double press Space: fly or land");
		ImGui::BulletText("Double press W: run");
		ImGui::BulletText("Move the mouse: move the player's perspective within a three-dimensional plane");
		ImGui::BulletText("Left click on the mouse: move the player's perspective and move the 3D section");
		ImGui::BulletText("In control mode");
		ImGui::BulletText("Press Right click :drag an object");
		ImGui::BulletText("Left and right mouse buttons :throw objects");
		ImGui::BulletText("In other modes");
		ImGui::BulletText("Right click on the mouse :execute the corresponding behavior");
		ImGui::BulletText("I: turn on or off the UI");
		ImGui::BulletText("C: Turn on or off the world coordinate system lines");
		ImGui::BulletText("G: Show or turn off wireframe");
		ImGui::BulletText("Ctrl: Lift up the construction site");
		ImGui::BulletText("F2:Captures the window (RGB) and save the image");
		ImGui::BulletText("Delete: delete the half build joint or delete objects in the selection area");
		ImGui::BulletText("M/N: Zoom in and out of perspective");
		ImGui::BulletText("1/2/3/4/5/6 or Mouse wheel: Switching behavior mode");
		ImGui::TreePop();
	}
	ImGui::End();
	ImGui::ShowDemoWindow();
	}
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Game::area_delete(){
	this->deleteMap3D->getImageData();
	{
		bool isPointLightRemoved(false);
		for (size_t index(1); index < this->rigidBodies4D.size(); index++) {
			glm::ivec4 gridPosition4D(glm::ivec4(floor(this->rigidBodies4D[index]->position4D)));
			if (this->deleteMap3D->isDelete(glm::ivec3(gridPosition4D.w + 64.f, gridPosition4D.z + 64.f, gridPosition4D.x + 64.f)))
			{
				if (this->rigidBodies4D[index - 1]->objectName != "Ground")
				{
					//std::cout << "ImageData=" << gridPosition4D.x + 64.f<< gridPosition4D.z + 64.f<< gridPosition4D.w + 64.f << "\n";
					erase_animation4D(&this->shifts4D, &this->floats4D, &this->rotates4D, &this->openDoors4D,index);
					shift_animation4D(this->shifts4D, this->floats4D, this->rotates4D, this->openDoors4D,index, -1);
					erase_joint4d(&this->sticks4D, &this->springs4D, &this->hingeConstraintsVec, index);
					shift_joint4d(this->sticks4D, this->springs4D, &this->hingeConstraintsVec, index, -1);
					erase_dynamite4d_indices(&this->dynamiteIndices, index);
					shift_dynamite4d_indices(this->dynamiteIndices, index, -1);
					erase_point_light4d(&this->pointLights4D, this->shaders[WALLD4], this->shaders[TERRAIND4], this->shaders[LIGHT_MAPD3], index);
					shift_point_light4d(this->pointLights4D, index, -1);
					isPointLightRemoved = true;
					this->rigidBodies4D.erase(this->rigidBodies4D.begin() + index);
					index--;
				}
			}
		}
		if (isPointLightRemoved)
		{
			this->shaders[LIGHT_MAPD3]->use();
			this->lightMap3D->bind_image(0);
			glDispatchCompute(4, 128, 4);
			glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
		}
	}

	for (size_t index(0); index < this->walls4D.size(); index++) {
		glm::ivec4 gridPosition4D(glm::ivec4(floor(this->walls4D[index]->position4D)));
		if (this->deleteMap3D->isDelete(glm::ivec3(gridPosition4D.w + 64.f, gridPosition4D.z + 64.f, gridPosition4D.x + 64.f)))
		{
			if (this->walls4D[index]->objectName != "Ground")
			{
				erase_joint4d(&this->sticks4D, &this->springs4D, &this->hingeConstraintsVec, this->rigidBodies4D.size() + index);
				shift_joint4d(this->sticks4D, this->springs4D, &this->hingeConstraintsVec, this->rigidBodies4D.size() + index, -1);
				erase_dynamite4d_indices(&this->dynamiteIndices, index);
				shift_dynamite4d_indices(this->dynamiteIndices, index, -1);
				this->walls4D.erase(this->walls4D.begin() + index);
				this->groupIndices = shift_group(this->groupIndices, &this->groups, index, -1);
				index--;
			}
		}
	}

	for (size_t index(0); index < size_of_objects4d(this->sticks4D,this->springs4D); index++) {
		Object4D* a(find_joint4d(this->sticks4D, this->springs4D, index));
		glm::ivec4 gridPosition4D(glm::ivec4(floor(a->position4D)));
		if (this->deleteMap3D->isDelete(glm::ivec3(gridPosition4D.w + 64.f, gridPosition4D.z + 64.f, gridPosition4D.x + 64.f)))
		{
			erase_joint4d0(&this->sticks4D, &this->springs4D, index);
			index--;
		}
	}

	bool isPointLightRemoved(false);
	for (size_t index(0); index < this->pointLights4D.size(); index++) {
		glm::ivec4 gridPosition4D(glm::ivec4(floor(this->pointLights4D[index]->position4D)));
		if (this->deleteMap3D->isDelete(glm::ivec3(gridPosition4D.w + 64.f, gridPosition4D.z + 64.f, gridPosition4D.x + 64.f)))
		{
			this->pointLights4D.erase(this->pointLights4D.begin() + index);
			index--;
			isPointLightRemoved = true;
		}
	}

	if (isPointLightRemoved)
	{
		update_point_light4d_id(&this->pointLights4D);
		update_point_light4d(this->pointLights4D, this->shaders[WALLD4], this->shaders[TERRAIND4], this->shaders[LIGHT_MAPD3]);
		this->shaders[LIGHT_MAPD3]->use();
		this->lightMap3D->bind_image(0);
		glDispatchCompute(4, 128, 4);
		glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
	}

	update_render_indices(this->rigidBodies4D, this->groupIndices, this->groups, this->walls4D, this->sticks4D, this->springs4D, &this->renderIndices1, &this->renderIndices2, this->camera.position4D);
	sort_render_indices(&this->renderIndices1); sort_render_indices(&this->renderIndices2);
	update_collide_indices(this->rigidBodies4D, this->groupIndices, this->groups, this->walls4D);
}
