//#pragma once
#include"Game.h"
#include <filesystem>
#include"imgui/imgui.h"
#include"imgui/imgui_impl_glfw.h"
#include"imgui/imgui_impl_opengl3.h"

char levelText[256]("level 1");
static char savedLevelText[64]("level 1-1");
const char* shootText("Gun");
const char* controlText("Drag");
const char* textureText("Sand");
float lightTemperture(0.f);
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
size_t selectTextureIndex(0);
bool isObjectTextureUI(false);

static void HelpMarker(const char* desc)
{
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

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

static bool select_index(VectorIndex vectorIndex,size_t size)
{
	bool isSeleced(false);
	if (ImGui::BeginCombo("Index", vectorIndex.isValid ? std::to_string(vectorIndex.n).c_str() : "None"))
	{
		if (ImGui::Selectable("None"))
		{
			vectorIndex.isValid = false;
			isSeleced = true;
		}
		for (size_t i(0); i < size; i++)
		{
			if (ImGui::Selectable(std::to_string(i).c_str()))
			{
				vectorIndex = { i, true };
				isSeleced = true;
			}
		}
		ImGui::EndCombo();
	}
	return isSeleced;
}

static void select_object_texture(size_t* textureIndex,size_t selectTextureIndex0)
{
	if (isObjectTextureUI&& selectTextureIndex0 == selectTextureIndex)
	{
		ImGui::Begin("Object Textures", &isObjectTextureUI);
		HelpMarker("(1) ", "STONE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(STONE + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = STONE;
		}
		HelpMarker("STONE");
		ImGui::SameLine(); HelpMarker("(2) ", "CHESSBOARD0");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(CHESSBOARD0 + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = CHESSBOARD0;
		}
		HelpMarker("DEFAULTCHESSBOARD2");
		HelpMarker("(3) ", "DEFAULTCHESSBOARD2");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(DEFAULTCHESSBOARD2 + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = DEFAULTCHESSBOARD2;
		}
		HelpMarker("DEFAULTCHESSBOARD2");
		ImGui::SameLine();HelpMarker("(4) ", "YELLOW");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(YELLOW + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = YELLOW;
		}
		HelpMarker("YELLOW");
		HelpMarker("(5) ", "GROUND");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(GROUND + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = GROUND;
		}
		HelpMarker("GROUND");
		ImGui::SameLine();HelpMarker("(6) ", "C1");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(C1 + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = C1;
		}
		HelpMarker("C1");
		HelpMarker("(7) ", "C2");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(C2 + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = C2;
		}
		HelpMarker("C2");
		ImGui::SameLine();HelpMarker("(8) ", "C_2");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(C_2 + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = C_2;
		}
		HelpMarker("C_2");
		HelpMarker("(9) ", "C3");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(C3 + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = C3;
		}
		HelpMarker("C3");
		ImGui::SameLine();HelpMarker("(10) ", "C4");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(C4 + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = C4;
		}
		HelpMarker("C4");
		HelpMarker("(11)", "C5");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(C5 + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = C5;
		}
		HelpMarker("C5");
		ImGui::SameLine();HelpMarker("(12)", "GRID2");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(GRID2 + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = GRID2;
		}
		HelpMarker("GRID2");
		HelpMarker("(13)", "C6");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(C6 + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = C6;
		}
		HelpMarker("C6");
		ImGui::SameLine();HelpMarker("(14)", "CHESSBOARD");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(CHESSBOARD + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = CHESSBOARD;
		}
		HelpMarker("CHESSBOARD");
		HelpMarker("(15)", "WHITEWALL");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(WHITEWALL + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = WHITEWALL;
		}
		HelpMarker("WHITEWALL");
		ImGui::SameLine();HelpMarker("(16)", "GREENMARBLE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(GREENMARBLE + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = GREENMARBLE;
		}
		HelpMarker("GREENMARBLE");
		HelpMarker("(17)", "WHITEMARBLE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(WHITEMARBLE + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = WHITEMARBLE;
		}
		HelpMarker("WHITEMARBLE");
		ImGui::SameLine();HelpMarker("(18)", "YELLOWMARBLE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(YELLOWMARBLE + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = YELLOWMARBLE;
		}
		HelpMarker("YELLOWMARBLE");
		HelpMarker("(19)", "MARBLE_GROUND");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(MARBLE_GROUND + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = MARBLE_GROUND;
		}
		HelpMarker("MARBLE_GROUND");
		ImGui::SameLine();HelpMarker("(20)", "DEFAULTCHESSBOARD");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(DEFAULTCHESSBOARD + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = DEFAULTCHESSBOARD;
		}
		HelpMarker("DEFAULTCHESSBOARD");
		HelpMarker("(21)", "MARBLE_C1");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(MARBLE_C1 + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = MARBLE_C1;
		}
		HelpMarker("MARBLE_C1");
		ImGui::SameLine();HelpMarker("(22)", "MARBLE_C2");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(MARBLE_C2 + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = MARBLE_C2;
		}
		HelpMarker("MARBLE_C2");
		HelpMarker("(23)", "MARBLE_C3");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(MARBLE_C3 + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = MARBLE_C3;
		}
		HelpMarker("MARBLE_C3");
		ImGui::SameLine();HelpMarker("(24)", "MARBLE_C4");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(MARBLE_C4 + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = MARBLE_C4;
		}
		HelpMarker("MARBLE_C4");
		HelpMarker("(25)", "MARBLE_C5");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(MARBLE_C5 + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = MARBLE_C5;
		}
		HelpMarker("MARBLE_C5");
		ImGui::SameLine();HelpMarker("(26)", "MARBLE_C6");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(MARBLE_C6 + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = MARBLE_C6;
		}
		HelpMarker("MARBLE_C6");
		HelpMarker("(27)", "CHESSBOARDMARBLE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(CHESSBOARDMARBLE + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = CHESSBOARDMARBLE;
		}
		HelpMarker("CHESSBOARDMARBLE");
		ImGui::SameLine();HelpMarker("(28)", "WHITEMAINMARBLE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(WHITEMAINMARBLE + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = WHITEMAINMARBLE;
		}
		HelpMarker("WHITEMAINMARBLE");
		HelpMarker("(29)", "CONCRETE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(CONCRETE + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = CONCRETE;
		}
		HelpMarker("CONCRETE");
		ImGui::SameLine();HelpMarker("(30)", "YELLOWCONCRETE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(YELLOWCONCRETE + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = YELLOWCONCRETE;
		}
		HelpMarker("YELLOWCONCRETE");
		HelpMarker("(31)", "WHITECONCRETE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(WHITECONCRETE + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = WHITECONCRETE;
		}
		HelpMarker("WHITECONCRETE");
		ImGui::SameLine();HelpMarker("(32)", "GRASS");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(GRASS + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = GRASS;
		}
		HelpMarker("GRASS");
		HelpMarker("(33)", "WOODX");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(WOODX + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = WOODX;
		}
		HelpMarker("WOODX");
		ImGui::SameLine();HelpMarker("(34)", "WOODY");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(WOODY + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = WOODY;
		}
		HelpMarker("WOODY");
		HelpMarker("(35)", "WOODZ");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(WOODZ + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = WOODZ;
		}
		HelpMarker("WOODZ");
		ImGui::SameLine();HelpMarker("(36)", "OLDWOODX");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(OLDWOODX + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = OLDWOODX;
		}
		HelpMarker("OLDWOODX");
		HelpMarker("(37)", "OLDWOODY");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(OLDWOODY + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = OLDWOODY;
		}
		HelpMarker("OLDWOODY");
		ImGui::SameLine();HelpMarker("(38)", "OLDWOODZ");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(OLDWOODZ + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = OLDWOODZ;
		}
		HelpMarker("OLDWOODZ");
		HelpMarker("(39)", "GLASS");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(GLASS + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = GLASS;
		}
		HelpMarker("GLASS");
		ImGui::SameLine();HelpMarker("(40)", "GRID");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(GRID + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = GRID;
		}
		HelpMarker("GRID");
		HelpMarker("(41)", "STARS");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(STARS + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = STARS;
		}
		HelpMarker("STARS");
		ImGui::SameLine();HelpMarker("(42)", "STARS_SKY");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(STARS_SKY + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = STARS_SKY;
		}
		HelpMarker("STARS_SKY");
		HelpMarker("(43)", "LAVA");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(LAVA + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = LAVA;
		}
		HelpMarker("LAVA");
		ImGui::SameLine();HelpMarker("(44)", "CEIL1");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(CEIL1 + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = CEIL1;
		}
		HelpMarker("CEIL1");
		HelpMarker("(45)", "CEIL2");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(CEIL2 + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = CEIL2;
		}
		HelpMarker("CEIL2");
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		HelpMarker("(1) ", "PURE_RED");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(PURE_RED + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = PURE_RED;
		}
		HelpMarker("PURE_RED");
		ImGui::SameLine(); HelpMarker("(2) ", "PURE_RED_HARFGREEN");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(PURE_RED_HARFGREEN + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = PURE_RED_HARFGREEN;
		}
		HelpMarker("PURE_RED_HARFGREEN");
		HelpMarker("(3) ", "PURE_RED_GREEN");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(PURE_RED_GREEN + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = PURE_RED_GREEN;
		}
		HelpMarker("PURE_RED_GREEN");
		ImGui::SameLine(); HelpMarker("(4) ", "PURE_HARFRED_GREEN");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(PURE_HARFRED_GREEN + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = PURE_HARFRED_GREEN;
		}
		HelpMarker("PURE_HARFRED_GREEN");
		HelpMarker("(5) ", "PURE_GREEN");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(PURE_GREEN + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = PURE_GREEN;
		}
		HelpMarker("PURE_GREEN");
		ImGui::SameLine(); HelpMarker("(6) ", "PURE_GREEN_HARFBLUE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(PURE_GREEN_HARFBLUE + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = PURE_GREEN_HARFBLUE;
		}
		HelpMarker("PURE_GREEN_HARFBLUE");
		HelpMarker("(7) ", "PURE_GREEN_BLUE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(PURE_GREEN_BLUE + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = PURE_GREEN_BLUE;
		}
		HelpMarker("PURE_GREEN_BLUE");
		ImGui::SameLine(); HelpMarker("(8) ", "PURE_HARFGREEN_BLUE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(PURE_HARFGREEN_BLUE + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = PURE_HARFGREEN_BLUE;
		}
		HelpMarker("PURE_HARFGREEN_BLUE");
		HelpMarker("(9) ", "PURE_BLUE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(PURE_BLUE + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = PURE_BLUE;
		}
		HelpMarker("PURE_BLUE");
		ImGui::SameLine(); HelpMarker("(10)", "PURE_HARFRED_BLUE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(PURE_HARFRED_BLUE + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = PURE_HARFRED_BLUE;
		}
		HelpMarker("PURE_HARFRED_BLUE");
		HelpMarker("(11)", "PURE_RED_BLUE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(PURE_RED_BLUE + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = PURE_RED_BLUE;
		}
		HelpMarker("PURE_RED_BLUE");
		ImGui::SameLine(); HelpMarker("(12)", "PURE_RED_HARFBLUE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(PURE_RED_HARFBLUE + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = PURE_RED_HARFBLUE;
		}
		HelpMarker("PURE_RED_HARFBLUE");
		HelpMarker("(13)", "PURE_WHITE");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(PURE_WHITE + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = PURE_WHITE;
		}
		HelpMarker("PURE_WHITE");
		ImGui::SameLine(); HelpMarker("(14)", "PURE_BLACK");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(PURE_BLACK + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)))
		{
			*textureIndex = PURE_BLACK;
		}
		HelpMarker("PURE_BLACK");
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
		if (ImGui::ImageButton((ImTextureID)(SAND + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = 0;
		}
		HelpMarker("Sand");
		ImGui::SameLine();
		HelpMarker("(2) ", "Snow");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(SNOW + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = 1;
		}
		HelpMarker("Snow");
		HelpMarker("(3) ", "Ice");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(ICE + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = 2;
		}
		HelpMarker("Ice");
		ImGui::SameLine();
		HelpMarker("(4) ", "Normal Grass");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(GRASS1 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = 3;
		}
		HelpMarker("Normal Grass");
		HelpMarker("(5) ", "Green Grass");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(GRASS2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = 4;
		}
		HelpMarker("Green Grass");
		ImGui::SameLine();
		HelpMarker("(6) ", "Soil");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(SOIL + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = 5;
		}
		HelpMarker("Soil");
		HelpMarker("(7) ", "Swamp Grass");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(GRASS3 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = 6;
		}
		HelpMarker("Swamp Grass");
		ImGui::SameLine();
		HelpMarker("(8) ", "Wild Grass");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(GRASS4 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = 7;
		}
		HelpMarker("Wild Grass");
		HelpMarker("(9) ", "Wet Sand");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(SAND_SOIL + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = 8;
		}
		HelpMarker("Wet Sand");
		ImGui::SameLine();
		HelpMarker("(10)", "Half Wet Sand");
		ImGui::SameLine();
		if (ImGui::ImageButton((ImTextureID)(SAND_SOIL2 + 5), ImVec2(100.f, 100.f)))
		{
			*textureIndex = 9;
		}
		HelpMarker("Half Wet Sand");
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
		//ImGui::Begin("Light Hierarchy");
		//for (size_t i(0); i < this->pointLights.size(); i++)
		//{
		//	if (ImGui::Selectable(("Point Light 4D " + std::to_string(i)).c_str()))
		//	{
		//
		//	}
		//}
		//ImGui::End();
		ImGui::Begin("Inspector", &this->editMode);
		if (!this->editMode)
		{
			this->isCloseUI = true;
			glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			this->firstMouse = !this->firstMouse;
			isGroundTextureUI = false, isObjectTextureUI = false;
			this->pageType = REGULAR;
		}
		if (this->hitIndex.isValid && this->hitIndex.n < size_of_objects4d(this->rigidBodies4d, this->walls4d, this->sticks4d, this->springs4d))
		{
			Object4D* a(find_object4d(this->rigidBodies4d, this->walls4d, this->sticks4d, this->springs4d, this->hitIndex.n));
			size_t selectTextureIndex0(0);
			std::string ss(a->objectName);
			ImGui::Text(("Tag:" + ss + " Id:" + std::to_string(this->hitIndex.n)).c_str());
			if (ImGui::TreeNodeEx("Transform 4D", 2)) {
				glm::vec4 position4d(a->position4d);
				if (ImGui::DragFloat4("Position 4D", &position4d.x, 0.02f))
				{
					a->set_position4D(position4d);
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
			if (this->hitIndex.n < this->rigidBodies4d.size())
			{
				RigidBody4D* r(this->rigidBodies4d[this->hitIndex.n]);
				selectTextureIndex0++;select_object_texture(&r->texture3DIndex, selectTextureIndex0);
				if (ImGui::TreeNodeEx("RigidBody 4D", 2)) {
					ImGui::Checkbox("Use Gravity", &r->isGravity);
					ImGui::Checkbox("Frozen", &r->isFrozen);
					ImGui::DragFloat("Mass", &r->mass);
					ImGui::DragFloat("Moment Inertia Scalar", &r->momentInertiaScalar);
					ImGui::DragFloat4("Velocity 4D", &r->velocity4d.x);
					ImGui::Text("Angular Velocity");
					ImGui::DragFloat3("xy,xz,xw1", &r->angularVelocity4D.xy);
					ImGui::DragFloat3("yz,yw,zw1", &r->angularVelocity4D.yz);
					ImGui::Checkbox("Specular", &r->isSpecular);
					ImGui::Image((ImTextureID)(r->texture3DIndex + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)); ImGui::SameLine();
					if (ImGui::Button("textures 3D"))
					{
						isObjectTextureUI = !isObjectTextureUI; selectTextureIndex = selectTextureIndex0;
					}
					ImGui::ColorEdit4("Painting Color", &r->paintingColor.x);
					ImGui::ColorEdit4("Metal Color", &r->metalColor.x);
					ImGui::TreePop();
				}
			}
			else if (this->hitIndex.n < size_of_objects4d(this->rigidBodies4d, this->walls4d))
			{
				Wall4D* w(this->walls4d[this->hitIndex.n - this->rigidBodies4d.size()]);
				selectTextureIndex0++;select_object_texture(&w->texture3DIndex, selectTextureIndex0);
				if (ImGui::TreeNodeEx("Wall 4D", 2)) {
					ImGui::Checkbox("Specular", &w->isSpecular);
					ImGui::Image((ImTextureID)(w->texture3DIndex + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)); ImGui::SameLine();
					if (ImGui::Button("textures 3D"))
					{
						isObjectTextureUI = !isObjectTextureUI;selectTextureIndex = selectTextureIndex0;
					}
					ImGui::ColorEdit4("Painting Color", &w->paintingColor.x);
					ImGui::ColorEdit4("Metal Color", &w->metalColor.x);
					ImGui::TreePop();
				}
			}
			else if (this->hitIndex.n < size_of_objects4d(this->rigidBodies4d, this->walls4d) + this->sticks4d.size())
			{
				size_t componentIndex(this->hitIndex.n - size_of_objects4d(this->rigidBodies4d, this->walls4d));
				Stick4D* s(this->sticks4d[componentIndex]);
				selectTextureIndex0++;select_object_texture(&s->texture3DIndex, selectTextureIndex0);
				if (ImGui::TreeNodeEx(("Stick Joint 4D " + std::to_string(componentIndex)).c_str(), 2)) {
					float stickLength(s->stickLength);
					if (ImGui::DragFloat("Stick Length", &stickLength, 0.02f, 0.f, 100.f))
					{
						s->set_stick_length(stickLength);
					}
					ImGui::Image((ImTextureID)(s->texture3DIndex + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)); ImGui::SameLine();
					if (ImGui::Button("textures 3D"))
					{
						isObjectTextureUI = !isObjectTextureUI;selectTextureIndex = selectTextureIndex0;
					}
					ImGui::ColorEdit4("Painting Color", &s->paintingColor.x);
					ImGui::TreePop();
				}
			}
			else if (this->hitIndex.n < size_of_objects4d(this->rigidBodies4d, this->walls4d, this->sticks4d, this->springs4d))
			{
				size_t componentIndex(this->hitIndex.n - size_of_objects4d(this->rigidBodies4d, this->walls4d) - this->sticks4d.size());
				Spring4D* s(this->springs4d[componentIndex]);
				selectTextureIndex0++;select_object_texture(&s->texture3DIndex, selectTextureIndex0);
				if (ImGui::TreeNodeEx(("Spring Joint 4D " + std::to_string(componentIndex)).c_str(), 2)) {
					ImGui::DragFloat("Spring Length", &s->springLength, 0.02f, 0.f, 100.f);
					ImGui::DragFloat("Spring Strength", &s->k, 0.02f, 0.f, 100.f);
					ImGui::Image((ImTextureID)(s->texture3DIndex + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)); ImGui::SameLine();
					if (ImGui::Button("textures 3D"))
					{
						isObjectTextureUI = !isObjectTextureUI;selectTextureIndex = selectTextureIndex0;
					}
					ImGui::ColorEdit4("Painting Color", &s->paintingColor.x);
					ImGui::TreePop();
				}
			}
			if (this->hitIndex.n < size_of_objects4d(this->rigidBodies4d, this->walls4d))
			{
				if (a->componentsVec[DYNAMITE4D].size() > 0)
				{
					for (size_t i(0); i < a->componentsVec[DYNAMITE4D].size(); i++)
					{
						size_t componentIndex(a->componentsVec[DYNAMITE4D][i]);
						DynamiteIndex* d(this->dynamiteIndices[componentIndex]);
						if (ImGui::Button("Delete 0"))
						{
							this->dynamiteIndices[componentIndex] = nullptr, free(this->dynamiteIndices[componentIndex]);
							this->dynamiteIndices.erase(this->dynamiteIndices.begin() + componentIndex);
							for (size_t i(0); i < size_of_objects4d(this->rigidBodies4d, this->walls4d); i++)
							{
								find_object4d(this->rigidBodies4d, this->walls4d, i)->componentsVec[DYNAMITE4D].clear();
							}
							for (size_t i(0); i < dynamiteIndices.size(); i++) {
								DynamiteIndex* d(dynamiteIndices[i]);
								find_object4d(this->rigidBodies4d, this->walls4d, d->index)->componentsVec[DYNAMITE4D].push_back(i);
							}
						}
						ImGui::SameLine();
						if (ImGui::TreeNodeEx(("Dynamite 4D " + std::to_string(componentIndex)).c_str(), 2)) {
							ImGui::Checkbox("Exploding", &d->isExploding);
							ImGui::TreePop();
						}
					}
				}
				if (a->componentsVec[STICK_JOINT].size() > 0)
				{
					for (size_t i(0); i < a->componentsVec[STICK_JOINT].size(); i++)
					{
						size_t componentIndex(a->componentsVec[STICK_JOINT][i]);
						Stick4D* s(this->sticks4d[componentIndex]);
						selectTextureIndex0++;select_object_texture(&s->texture3DIndex, selectTextureIndex0);
						if (ImGui::Button("Delete 1"))
						{
							erase_joint4d0(&this->sticks4d, &this->springs4d, componentIndex);
							for (size_t i(0); i < size_of_objects4d(this->rigidBodies4d, this->walls4d); i++)
							{
								for (size_t j(0); j < OPENDOOR4D_ANIMATION + 1; j++)find_object4d(this->rigidBodies4d, this->walls4d, i)->componentsVec[j].clear();
							}
							update_components_index(this->rigidBodies4d, this->walls4d, dynamiteIndices, sticks4d, springs4d, hingeConstraintsVec, shifts4d, floats4d, rotates4d, openDoors4d);
							update_render_indices(this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d, this->sticks4d, this->springs4d, &this->renderIndices1, &this->renderIndices2, this->camera.position4d);
							sort_render_indices(&this->renderIndices1); sort_render_indices(&this->renderIndices2);
							update_collide_indices(this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d);
						}
						ImGui::SameLine();
						if (ImGui::TreeNodeEx(("Stick Joint 4D " + std::to_string(componentIndex)).c_str(), 2)) {
							if (select_index(s->index2, size_of_objects4d(this->rigidBodies4d, this->walls4d, this->sticks4d, this->springs4d)))
							{
								for (size_t i(0); i < size_of_objects4d(this->rigidBodies4d, this->walls4d); i++)
								{
									find_object4d(this->rigidBodies4d, this->walls4d, i)->componentsVec[STICK_JOINT].clear();
								}
								for (size_t i(0); i < this->sticks4d.size(); i++) {
									Stick4D* s(this->sticks4d[i]);
									find_object4d(this->rigidBodies4d, this->walls4d, s->index1)->componentsVec[STICK_JOINT].push_back(i);
									if (s->index2.isValid)find_object4d(this->rigidBodies4d, this->walls4d, s->index2.n)->componentsVec[STICK_JOINT].push_back(i);
								}
							}
							float stickLength(s->stickLength);
							if (ImGui::DragFloat("Stick Length", &stickLength, 0.02f, 0.f, 100.f))
							{
								s->set_stick_length(stickLength);
							}
							ImGui::Image((ImTextureID)(s->texture3DIndex + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)); ImGui::SameLine();
							if (ImGui::Button("textures 3D"))
							{
								isObjectTextureUI = !isObjectTextureUI;selectTextureIndex = selectTextureIndex0;
							}
							ImGui::ColorEdit4("Painting Color", &s->paintingColor.x);
							ImGui::TreePop();
						}
					}
				}
				if (a->componentsVec[SPRING_JOINT].size() > 0)
				{
					for (size_t i(0); i < a->componentsVec[SPRING_JOINT].size(); i++)
					{
						size_t componentIndex(a->componentsVec[SPRING_JOINT][i]);
						Spring4D* s(this->springs4d[componentIndex]);
						selectTextureIndex0++;select_object_texture(&s->texture3DIndex, selectTextureIndex0);
						if (ImGui::Button("Delete 2"))
						{
							erase_joint4d0(&this->sticks4d, &this->springs4d, this->sticks4d.size() + componentIndex);
							for (size_t i(0); i < size_of_objects4d(this->rigidBodies4d, this->walls4d); i++)
							{
								for (size_t j(0); j < OPENDOOR4D_ANIMATION + 1; j++)find_object4d(this->rigidBodies4d, this->walls4d, i)->componentsVec[j].clear();
							}
							update_components_index(this->rigidBodies4d, this->walls4d, dynamiteIndices, sticks4d, springs4d, hingeConstraintsVec, shifts4d, floats4d, rotates4d, openDoors4d);
							update_render_indices(this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d, this->sticks4d, this->springs4d, &this->renderIndices1, &this->renderIndices2, this->camera.position4d);
							sort_render_indices(&this->renderIndices1); sort_render_indices(&this->renderIndices2);
							update_collide_indices(this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d);
						}
						ImGui::SameLine();
						if (ImGui::TreeNodeEx(("Spring Joint 4D " + std::to_string(componentIndex)).c_str(), 2)) {
							if (select_index(s->index2, size_of_objects4d(this->rigidBodies4d, this->walls4d, this->sticks4d, this->springs4d)))
							{
								for (size_t i(0); i < size_of_objects4d(this->rigidBodies4d, this->walls4d); i++)
								{
									find_object4d(this->rigidBodies4d, this->walls4d, i)->componentsVec[SPRING_JOINT].clear();
								}
								for (size_t i(0); i < this->springs4d.size(); i++) {
									Spring4D* s(this->springs4d[i]);
									find_object4d(this->rigidBodies4d, this->walls4d, s->index1)->componentsVec[SPRING_JOINT].push_back(i);
									if (s->index2.isValid)find_object4d(this->rigidBodies4d, this->walls4d, s->index2.n)->componentsVec[SPRING_JOINT].push_back(i);
								}
							}
							ImGui::DragFloat("Spring Length", &s->springLength, 0.02f, 0.f, 100.f);
							ImGui::DragFloat("Spring Strength", &s->k, 0.02f, 0.f, 100.f);
							ImGui::Image((ImTextureID)(s->texture3DIndex + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)); ImGui::SameLine();
							if (ImGui::Button("textures 3D"))
							{
								isObjectTextureUI = !isObjectTextureUI;selectTextureIndex = selectTextureIndex0;
							}
							ImGui::ColorEdit4("Painting Color", &s->paintingColor.x);
							ImGui::TreePop();
						}
					}
				}
				if (a->componentsVec[HINGE_CONSTRAINT].size() > 0)
				{
					for (size_t i(0); i < a->componentsVec[HINGE_CONSTRAINT].size(); i++)
					{
						size_t componentIndex(a->componentsVec[HINGE_CONSTRAINT][i]);
						std::vector<HingeConstraint4D*>* hs(&this->hingeConstraintsVec[componentIndex]);
						if (ImGui::Button("Delete 3"))
						{
							for (size_t j(0); j < hs->size(); j++)
							{
								(*hs)[j] = nullptr, delete (*hs)[j];
							}
							this->hingeConstraintsVec.erase(this->hingeConstraintsVec.begin() + componentIndex);
							for (size_t i(0); i < size_of_objects4d(this->rigidBodies4d, this->walls4d); i++)
							{
								find_object4d(this->rigidBodies4d, this->walls4d, i)->componentsVec[HINGE_CONSTRAINT].clear();
							}
							for (size_t i(0); i < this->hingeConstraintsVec.size(); i++) {
								HingeConstraint4D* h(this->hingeConstraintsVec[i][0]);
								find_object4d(this->rigidBodies4d, this->walls4d, h->index1)->componentsVec[HINGE_CONSTRAINT].push_back(i);
								if(h->index2.isValid)find_object4d(this->rigidBodies4d, this->walls4d, h->index2.n)->componentsVec[HINGE_CONSTRAINT].push_back(i);
							}
						}
						ImGui::SameLine();
						if (ImGui::TreeNodeEx(("Hinge Constraint 4D " + std::to_string(componentIndex)).c_str(), 2)) {
							if (select_index((*hs)[0]->index2, size_of_objects4d(this->rigidBodies4d, this->walls4d, this->sticks4d, this->springs4d)))
							{
								for (size_t i(0); i < size_of_objects4d(this->rigidBodies4d, this->walls4d); i++)
								{
									find_object4d(this->rigidBodies4d, this->walls4d, i)->componentsVec[HINGE_CONSTRAINT].clear();
								}
								for (size_t i(0); i < this->hingeConstraintsVec.size(); i++) {
									HingeConstraint4D* h(this->hingeConstraintsVec[i][0]);
									find_object4d(this->rigidBodies4d, this->walls4d, h->index1)->componentsVec[HINGE_CONSTRAINT].push_back(i);
									if (h->index2.isValid)find_object4d(this->rigidBodies4d, this->walls4d, h->index2.n)->componentsVec[HINGE_CONSTRAINT].push_back(i);
								}
							}
							ImGui::Text("Hinges' Position 4D List"), ImGui::SameLine(), ImGui::Text("%i", hs->size());
							for (size_t j(0); j < hs->size(); j++)
							{
								//(*hs)[j]->index2 = (*hs)[0];
								if (ImGui::TreeNodeEx(("Position 4D List " + std::to_string(j)).c_str(), 1)) {
									ImGui::DragFloat4("Body Position 4D 1", &(*hs)[j]->bodyPosition4D1.x, 0.02f);
									ImGui::DragFloat4("Body Position 4D 2", &(*hs)[j]->bodyPosition4D2.x, 0.02f);
									ImGui::DragFloat4("World Position 4D", &(*hs)[j]->worldPosition4D.x, 0.02f);
									ImGui::TreePop();
								}
							}
							if (ImGui::Button("+"))
							{
								HingeConstraint4D* h((*hs)[hs->size() - 1]);
								hs->push_back(new HingeConstraint4D(h->worldPosition4D, h->bodyPosition4D1, h->bodyPosition4D2, h->index1, { h->index2.n, h->index2.isValid }));
							}
							if (hs->size() > 1)
							{
								ImGui::SameLine();
								if (ImGui::Button("-"))
								{
									(*hs)[hs->size() - 1] = nullptr, free((*hs)[hs->size() - 1]);
									hs->erase(hs->begin() + hs->size() - 1);
								}
							}
							ImGui::TreePop();
						}
					}
				}
				if (a->componentsVec[SHIFT4D_ANIMATION].size() > 0)
				{
					for (size_t i(0); i < a->componentsVec[SHIFT4D_ANIMATION].size(); i++)
					{
						size_t componentIndex(a->componentsVec[SHIFT4D_ANIMATION][i]);
						Shift4D* s(this->shifts4d[componentIndex]);
						if (ImGui::Button("Delete 4"))
						{
							this->shifts4d[componentIndex] = nullptr, free(this->shifts4d[componentIndex]);
							this->shifts4d.erase(this->shifts4d.begin() + componentIndex);
							for (size_t i(0); i < size_of_objects4d(this->rigidBodies4d, this->walls4d); i++)
							{
								find_object4d(this->rigidBodies4d, this->walls4d, i)->componentsVec[SHIFT4D_ANIMATION].clear();
							}
							for (size_t i(0); i < this->shifts4d.size(); i++) {
								Shift4D* s2(this->shifts4d[i]);
								find_object4d(this->rigidBodies4d, this->walls4d, s2->index)->componentsVec[SHIFT4D_ANIMATION].push_back(i);
							}
						}
						ImGui::SameLine();
						if (ImGui::TreeNodeEx(("Shift Animation 4D " + std::to_string(componentIndex)).c_str(), 2)) {
							ImGui::Text("Shift4D States"), ImGui::SameLine(), ImGui::Text("%i", s->pTs.size());
							for (size_t j(0); j < s->pTs.size(); j++)
							{
								if (ImGui::TreeNodeEx(("Position4D And Delta Time " + std::to_string(j)).c_str(), 1)) {
									ImGui::DragFloat4("Position 4D", &s->pTs[j].positions4D.x, 0.02f);
									if (ImGui::DragFloat("Delta Time", &s->pTs[j].dt, 0.02f))
									{
										s->update_period();
									}
									ImGui::TreePop();
								}
							}
							if (ImGui::Button("+"))
							{
								s->pTs.push_back(s->pTs[s->pTs.size() - 1]);
								s->update_period();
							}
							if (s->pTs.size() > 1)
							{
								ImGui::SameLine();
								if (ImGui::Button("-"))
								{
									s->pTs.erase(s->pTs.begin() + s->pTs.size() - 1);
									s->update_period();
								}
							}
							ImGui::TreePop();
						}
					}
				}
				if (a->componentsVec[FLOAT4D_ANIMATION].size() > 0)
				{
					for (size_t i(0); i < a->componentsVec[FLOAT4D_ANIMATION].size(); i++)
					{
						size_t componentIndex(a->componentsVec[FLOAT4D_ANIMATION][i]);
						Float4D* f(this->floats4d[componentIndex]);
						if (ImGui::Button("Delete 5"))
						{
							this->floats4d[componentIndex] = nullptr, free(this->floats4d[componentIndex]);
							this->floats4d.erase(this->floats4d.begin() + componentIndex);
							for (size_t i(0); i < size_of_objects4d(this->rigidBodies4d, this->walls4d); i++)
							{
								find_object4d(this->rigidBodies4d, this->walls4d, i)->componentsVec[FLOAT4D_ANIMATION].clear();
							}
							for (size_t i(0); i < floats4d.size(); i++) {
								Float4D* f(this->floats4d[i]);
								find_object4d(this->rigidBodies4d, this->walls4d, f->index)->componentsVec[FLOAT4D_ANIMATION].push_back(i);
							}
						}
						ImGui::SameLine();
						if (ImGui::TreeNodeEx(("Float Animation 4D " + std::to_string(componentIndex)).c_str(), 2)) {
							if (ImGui::DragInt("Direction 4D", &f->direction4D, 1.f, 1, 8))
							{
								f->direction4D = alg::clamp(f->direction4D, 1, 8);
							}
							ImGui::DragFloat("Distance", &f->distance, 0.02f);
							ImGui::DragFloat4("Position 4D", &f->position4d.x, 0.02f);
							ImGui::DragFloat("Speed", &f->speed, 0.02f);
							ImGui::TreePop();
						}
					}
				}
				if (a->componentsVec[ROTATE4D_ANIMATION].size() > 0)
				{
					for (size_t i(0); i < a->componentsVec[ROTATE4D_ANIMATION].size(); i++)
					{
						size_t componentIndex(a->componentsVec[ROTATE4D_ANIMATION][i]);
						Rotate4D* r(this->rotates4d[componentIndex]);
						if (ImGui::Button("Delete 6"))
						{
							this->rotates4d[componentIndex] = nullptr, free(this->rotates4d[componentIndex]);
							this->rotates4d.erase(this->rotates4d.begin() + componentIndex);
							for (size_t i(0); i < size_of_objects4d(this->rigidBodies4d, this->walls4d); i++)
							{
								find_object4d(this->rigidBodies4d, this->walls4d, i)->componentsVec[ROTATE4D_ANIMATION].clear();
							}
							for (size_t i(0); i < this->rotates4d.size(); i++) {
								Rotate4D* r(this->rotates4d[i]);
								find_object4d(this->rigidBodies4d, this->walls4d, r->index1)->componentsVec[ROTATE4D_ANIMATION].push_back(i);
								if(r->index2.isValid)find_object4d(this->rigidBodies4d, this->walls4d, r->index2.n)->componentsVec[ROTATE4D_ANIMATION].push_back(i);
							}
						}
						ImGui::SameLine();
						if (ImGui::TreeNodeEx(("Rotate Animation 4D " + std::to_string(componentIndex)).c_str(), 2)) {
							select_index(r->index2, size_of_objects4d(this->rigidBodies4d, this->walls4d, this->sticks4d, this->springs4d));
							ImGui::DragFloat3("xy,xz,xw1", &r->angularVelocity4D.xy);
							ImGui::DragFloat3("yz,yw,zw1", &r->angularVelocity4D.yz);
							ImGui::DragFloat4("Body Position 4D", &r->bodyPosition4D.x, 0.02f);
							ImGui::Checkbox("Position Fixed", &r->isPositionFixed);
							ImGui::DragFloat4("Position 4D", &r->position4d.x, 0.02f);
							ImGui::TreePop();
						}
					}
				}
				if (a->componentsVec[OPENDOOR4D_ANIMATION].size() > 0)
				{
					for (size_t i(0); i < a->componentsVec[OPENDOOR4D_ANIMATION].size(); i++)
					{
						size_t componentIndex(a->componentsVec[OPENDOOR4D_ANIMATION][i]);
						OpenDoor4D* o(this->openDoors4d[componentIndex]);
						if (ImGui::Button("Delete 7"))
						{
							this->openDoors4d[componentIndex] = nullptr, free(this->openDoors4d[componentIndex]);
							this->openDoors4d.erase(this->openDoors4d.begin() + componentIndex);
							for (size_t i(0); i < size_of_objects4d(this->rigidBodies4d, this->walls4d); i++)
							{
								find_object4d(this->rigidBodies4d, this->walls4d, i)->componentsVec[OPENDOOR4D_ANIMATION].clear();
							}
							for (size_t i(0); i < openDoors4d.size(); i++) {
								OpenDoor4D* o(this->openDoors4d[i]);
								find_object4d(this->rigidBodies4d, this->walls4d, o->index)->componentsVec[OPENDOOR4D_ANIMATION].push_back(i);
							}
						}
						ImGui::SameLine();
						if (ImGui::TreeNodeEx(("Open Door Animation 4D " + std::to_string(componentIndex)).c_str(), 2)) {
							ImGui::DragFloat4("Position 4D", &o->position4d.x, 0.02f);
							ImGui::DragFloat("During Time", &o->duringTime, 0.02f);
							ImGui::DragFloat("Current Time", &o->curTime, 0.02f);
							ImGui::DragFloat3("xy,xz,xw1", &o->rotateAngle4D.xy);
							ImGui::DragFloat3("yz,yw,zw1", &o->rotateAngle4D.yz);
							int state(o->state);
							if (ImGui::DragInt("State", &state, 1.f, 0, 3))
							{
								o->state = alg::clamp(state, 0, 3);
							}
							ImGui::TreePop();
						}
					}
				}
				if (ImGui::BeginCombo("Add Component",""))
				{
					if (ImGui::Selectable("Dynamite 4D"))
					{
						this->dynamiteIndices.push_back(new DynamiteIndex(this->hitIndex.n, false));
						for (size_t i(0); i < size_of_objects4d(this->rigidBodies4d, this->walls4d); i++)
						{
							find_object4d(this->rigidBodies4d, this->walls4d, i)->componentsVec[DYNAMITE4D].clear();
						}
						for (size_t i(0); i < dynamiteIndices.size(); i++) {
							DynamiteIndex* d(dynamiteIndices[i]);
							find_object4d(this->rigidBodies4d, this->walls4d, d->index)->componentsVec[DYNAMITE4D].push_back(i);
						}
					}
					if (ImGui::Selectable("Stick Joint 4D"))
					{
						this->sticks4d.push_back(new Stick4D(glm::vec4(0.f), this->hitIndex.n, { 0,false }, 3.f, WHITECONCRETE, glm::vec4(1.f), WALLD4));
						for (size_t i(0); i < size_of_objects4d(this->rigidBodies4d, this->walls4d); i++)
						{
							find_object4d(this->rigidBodies4d, this->walls4d, i)->componentsVec[STICK_JOINT].clear();
						}
						for (size_t i(0); i < this->sticks4d.size(); i++) {
							Stick4D* s(this->sticks4d[i]);
							find_object4d(this->rigidBodies4d, this->walls4d, s->index1)->componentsVec[STICK_JOINT].push_back(i);
							if (s->index2.isValid)find_object4d(this->rigidBodies4d, this->walls4d, s->index2.n)->componentsVec[STICK_JOINT].push_back(i);
						}
					}
					if (ImGui::Selectable("Spring Joint 4D"))
					{
						this->springs4d.push_back(new Spring4D(glm::vec4(0.f), this->hitIndex.n, { 0, false }, 3.f, 10.f, WHITECONCRETE, glm::vec4(1.f), WALLD4));
						for (size_t i(0); i < size_of_objects4d(this->rigidBodies4d, this->walls4d); i++)
						{
							find_object4d(this->rigidBodies4d, this->walls4d, i)->componentsVec[SPRING_JOINT].clear();
						}
						for (size_t i(0); i < this->springs4d.size(); i++) {
							Spring4D* s(this->springs4d[i]);
							find_object4d(this->rigidBodies4d, this->walls4d, s->index1)->componentsVec[SPRING_JOINT].push_back(i);
							if(s->index2.isValid)find_object4d(this->rigidBodies4d, this->walls4d, s->index2.n)->componentsVec[SPRING_JOINT].push_back(i);
						}
					}
					if (ImGui::Selectable("Hinge Constraint 4D"))
					{
						this->hingeConstraintsVec.push_back({ new HingeConstraint4D(glm::vec4(0.f), glm::vec4(0.f), glm::vec4(0.f), this->hitIndex.n, {0, false}) });
						for (size_t i(0); i < size_of_objects4d(this->rigidBodies4d, this->walls4d); i++)
						{
							find_object4d(this->rigidBodies4d, this->walls4d, i)->componentsVec[HINGE_CONSTRAINT].clear();
						}
						for (size_t i(0); i < this->hingeConstraintsVec.size(); i++) {
							HingeConstraint4D* h(this->hingeConstraintsVec[i][0]);
							find_object4d(this->rigidBodies4d, this->walls4d, h->index1)->componentsVec[HINGE_CONSTRAINT].push_back(i);
							if(h->index2.isValid)find_object4d(this->rigidBodies4d, this->walls4d, h->index2.n)->componentsVec[HINGE_CONSTRAINT].push_back(i);
						}
					}
					if (this->hitIndex.n < this->rigidBodies4d.size())
					{
						if (ImGui::Selectable("Shift 4D Animation"))
						{
							this->shifts4d.push_back(new Shift4D({ { glm::vec4(-10.3f, 63.9f, 0.f, 0.f), 1.f } }, this->hitIndex.n));
							for (size_t i(0); i < size_of_objects4d(this->rigidBodies4d, this->walls4d); i++)
							{
								find_object4d(this->rigidBodies4d, this->walls4d, i)->componentsVec[SHIFT4D_ANIMATION].clear();
							}
							for (size_t i(0); i < this->shifts4d.size(); i++) {
								Shift4D* s(this->shifts4d[i]);
								find_object4d(this->rigidBodies4d, this->walls4d, s->index)->componentsVec[SHIFT4D_ANIMATION].push_back(i);
							}
						}
						if (ImGui::Selectable("Float 4D Animation"))
						{
							this->floats4d.push_back(new Float4D(glm::vec4(0.f), 0.f, 0.f, 1, this->hitIndex.n));
							for (size_t i(0); i < size_of_objects4d(this->rigidBodies4d, this->walls4d); i++)
							{
								find_object4d(this->rigidBodies4d, this->walls4d, i)->componentsVec[FLOAT4D_ANIMATION].clear();
							}
							for (size_t i(0); i < floats4d.size(); i++) {
								Float4D* f(this->floats4d[i]);
								find_object4d(this->rigidBodies4d, this->walls4d, f->index)->componentsVec[FLOAT4D_ANIMATION].push_back(i);
							}
						}
						if (ImGui::Selectable("Rotate 4D Animation"))
						{
							this->rotates4d.push_back(new Rotate4D(glm::vec4(0.f), glm::vec4(), alg::bivec4(), alg::bivec4(0.f), true, this->hitIndex.n, { 0, false }));
							for (size_t i(0); i < size_of_objects4d(this->rigidBodies4d, this->walls4d); i++)
							{
								find_object4d(this->rigidBodies4d, this->walls4d, i)->componentsVec[ROTATE4D_ANIMATION].clear();
							}
							for (size_t i(0); i < rotates4d.size(); i++) {
								Rotate4D* r(this->rotates4d[i]);
								find_object4d(this->rigidBodies4d, this->walls4d, r->index1)->componentsVec[ROTATE4D_ANIMATION].push_back(i);
								if (r->index2.isValid)find_object4d(this->rigidBodies4d, this->walls4d, r->index2.n)->componentsVec[ROTATE4D_ANIMATION].push_back(i);
							}
						}
						if (ImGui::Selectable("Open Door 4D Animation"))
						{
							this->openDoors4d.push_back(new OpenDoor4D(glm::vec4(0.f), 0.f, 0.f, alg::bivec4(), alg::rotor4(), 0, this->hitIndex.n));
							for (size_t i(0); i < size_of_objects4d(this->rigidBodies4d, this->walls4d); i++)
							{
								find_object4d(this->rigidBodies4d, this->walls4d, i)->componentsVec[OPENDOOR4D_ANIMATION].clear();
							}
							for (size_t i(0); i < openDoors4d.size(); i++) {
								OpenDoor4D* o(this->openDoors4d[i]);
								find_object4d(this->rigidBodies4d, this->walls4d, o->index)->componentsVec[OPENDOOR4D_ANIMATION].push_back(i);
							}
						}
					}
					ImGui::EndCombo();
				}
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
					this->rigidBodies4d, this->groups, this->walls4d, this->dynamiteIndices, this->terrains4d, this->waters4d,
					this->sticks4d, this->springs4d, this->shifts4d, this->floats4d, this->rotates4d, this->openDoors4d, this->hingeConstraintsVec,
					this->pointLights4d,this->worldTime);
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
			this->rigidBodies4d[0] = new RigidBody4D("Player", Hypercapsule(glm::vec4(0.4f, 0.4f, 1.8f, 0.4f)), glm::vec4(0.f, 64.875f, 0.f, 0.f), alg::bivec4(0.f, 0.f, 0.f, 90.f), glm::vec4(0.4f, 0.4f, 1.75f, 0.4f), 65.f, 0.f, 5.7143f, 0.f, true, false, glm::vec4(0.f), alg::bivec4(), true, PURE_WHITE, glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 0.f), CAPSULE4D, WALLD4);
			judge_objects(this->groupIndices, this->groups, this->walls4d, this->terrains4d, this->camera.position4d, this->camera.forward4D, this->camera.wDir, this->objectLoadDistance);
			this->groupIndices = judge_groups(this->rigidBodies4d, this->groupIndices, this->groups, this->camera.position4d, this->blockLoadDistance);
			update_render_indices(this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d, this->sticks4d, this->springs4d, &this->renderIndices1, &this->renderIndices2, this->camera.position4d);
			sort_render_indices(&this->renderIndices1); sort_render_indices(&this->renderIndices2);
			update_collide_indices(this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d);
		}
		if (ImGui::Button("Set World Time To zero"))
		{
			this->worldTime = 0.f;
		}

		bool isFrozen=false;
		for (RigidBody4D* i : this->rigidBodies4d)
		{
			if (i->isFrozen == true)
			{
				isFrozen = true;
			}
		}
		if(isFrozen)
		if (ImGui::Button("Unfroze"))
		{
			for (size_t i(1); i < this->rigidBodies4d.size(); i++)
			{
				this->rigidBodies4d[i]->isFrozen = false;
				this->rigidBodies4d[i]->isSleep = false;
			}
			update_collide_indices(this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d);
		}
		if (ImGui::Button("Froze"))
		{
			for (size_t i(1); i < this->rigidBodies4d.size(); i++)
			{
				this->rigidBodies4d[i]->isFrozen = true;
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
			ImGui::Image((ImTextureID)(this->paintType0 + 5), ImVec2(100.f, 100.f)); ImGui::SameLine();
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
					ImGui::Image((ImTextureID)(this->buildTexture + SAND_SOIL2 + 6), ImVec2(100.f, 100.f)); ImGui::SameLine();
					if (ImGui::Button("Object Textures"))
					{
						isObjectTextureUI = !isObjectTextureUI;selectTextureIndex = 0;
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
					if (ImGui::ImageButton((ImTextureID)(BUILD_OBJECT + CEIL2 + SAND_SOIL2 + 7), ImVec2(100.f, 100.f)))
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
					ImGui::SameLine(); ImGui::Text("4D Object");

					if (ImGui::ImageButton((ImTextureID)(BUILD_POOL_TABLE + CEIL2 + SAND_SOIL2 + 7), ImVec2(100.f, 100.f)))
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
					ImGui::SameLine(); ImGui::Text("4D Pool Table");

					if (ImGui::ImageButton((ImTextureID)(BUILD_DYNAMITE + CEIL2 + SAND_SOIL2 + 7), ImVec2(100.f, 100.f)))
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
					ImGui::SameLine(); ImGui::Text("4D Dynamite");
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("4D Rigid Body"))
				{
					ImGui::DragFloat4("Initial Velocity", &this->initialVelocity.x, 0.1f, -100.f, 100.f);

					ImGui::Text("Initial Angular Velocity");
					ImGui::DragFloat3("xy,xz,xw1", &this->initialAngularVelocity.xy);
					ImGui::DragFloat3("yz,yw,zw1", &this->initialAngularVelocity.yz);

					//if (this->isIlluminate)
					//{
					//	ImGui::DragFloat("Light Intensity", &this->lightIntensity, 0.1f, 0.f, 20.f);
					//	if (ImGui::ColorEdit3("Light Color", &this->lightColor.x))
					//	{
					//	}
					//	ImGui::DragFloat("Light Radius", &this->lightRadius, 0.1f, 0.f, 20.f);
					//}
					ImGui::Checkbox("Use Gravity", &this->isGravity);

					if (ImGui::ImageButton((ImTextureID)(BUILD_RIGIDBODY + CEIL2 + SAND_SOIL2 + 7), ImVec2(100.f, 100.f)))
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
					ImGui::SameLine(); ImGui::Text("4D Rigid Body");

					if (ImGui::ImageButton((ImTextureID)(BUILD_BILLIARD + CEIL2 + SAND_SOIL2 + 7), ImVec2(100.f, 100.f)))
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
					ImGui::SameLine(); ImGui::Text("4D Billiard");

					if (ImGui::ImageButton((ImTextureID)(BUILD_DYNAMITE + CEIL2 + SAND_SOIL2 + 7), ImVec2(100.f, 100.f)))
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
					ImGui::SameLine(); ImGui::Text("4D Dynamite");

					ImGui::EndTabItem();
				}
				
				if (ImGui::BeginTabItem("4D Joint"))
				{
					ImGui::DragFloat("Stick Length", &this->stickLength, 0.1f, 0.f, 20.f);
					if (ImGui::ImageButton((ImTextureID)(BUILD_STICK + CEIL2 + SAND_SOIL2 + 7), ImVec2(100.f, 100.f)))
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
					ImGui::SameLine(); ImGui::Text("4D Stick Joint");

					ImGui::DragFloat("Spring Length", &this->springLength, 0.1f, 0.f, 20.f);
					ImGui::DragFloat("Spring Strength", &this->springStrength, 0.5f, 0.f, 100.f);

					if (ImGui::ImageButton((ImTextureID)(BUILD_SPRING + CEIL2 + SAND_SOIL2 + 7), ImVec2(100.f, 100.f)))
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
					ImGui::SameLine(); ImGui::Text("4D Spring Joint");
					ImGui::EndTabItem();
				}
				
				if (ImGui::BeginTabItem("4D Light"))
				{
					ImGui::DragFloat("Light Intensity", &this->lightIntensity, 0.1f, 0.f, 20.f);
					ImGui::ColorEdit3("Light Color", &this->lightColor.x);

					if (ImGui::BlackBodyDragFloat("Light Color Temperture", (ImTextureID)4, &lightTemperture, 0.f, 10000.f))
					{
						lightTemperture = alg::clamp(lightTemperture, 0.f, 10000.f);
						this->lightColor = calculate_blackbody_color(lightTemperture);
					}
					ImGui::DragFloat("Light Radius", &this->lightRadius, 0.1f, 0.f, 200.f);
					if (ImGui::ImageButton((ImTextureID)(BUILD_POINTLIGHT + CEIL2 + SAND_SOIL2 + 7), ImVec2(100.f, 100.f)))
					{
						//this->targetIcon->logo = this->pointerTexs[BUILDING];
						this->mode = BUILDING;

						this->buildMode = BUILD_POINTLIGHT;
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
					ImGui::SameLine(); ImGui::Text("4D Point Light");
					ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
			}
			
			//if (ImGui::ImageButton((ImTextureID)(BUILD_WALL+WALL + SAND_SOIL2 + 6), ImVec2(100.f,100.f)))
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
		ImGui::DragInt("Penetration Count", &this->penetrationCount, 1.f, 0, INFINITY);
		if (ImGui::RadioButton("Select Area To Delete Mode", &this->mode, AREA_DELETING))
		{
			//this->targetIcon->logo = this->pointerTexs[AREA_DELETING];
			this->deleteMap3d->unselectArea();
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
		if (ImGui::Button("Clear Up All 4D Rigid Bodies And Components"))
		{
			for (size_t i(1); i < this->rigidBodies4d.size(); i++)
			{
				this->rigidBodies4d[i] = nullptr, free(this->rigidBodies4d[i]);
				this->rigidBodies4d.erase(this->rigidBodies4d.begin() + i);
				i--;
			}
			for (Wall4D* i : this->walls4d)for (size_t j(0); j < OPENDOOR4D_ANIMATION + 1; j++)i->componentsVec[j].clear();
			for (DynamiteIndex* i : this->dynamiteIndices)i = nullptr, free(i); this->dynamiteIndices.clear();
			for (Stick4D* i : this->sticks4d)i = nullptr, free(i); this->sticks4d.clear();
			for (Spring4D* i : this->springs4d)i = nullptr, free(i); this->springs4d.clear();
			for (std::vector<HingeConstraint4D*> i : this->hingeConstraintsVec) { for (HingeConstraint4D* j : i)j = nullptr, free(j); i.clear(); }this->hingeConstraintsVec.clear();
			for (Shift4D* i : this->shifts4d)i = nullptr, free(i); this->shifts4d.clear();
			for (Float4D* i : this->floats4d)i = nullptr, free(i); this->floats4d.clear();
			for (Rotate4D* i : this->rotates4d)i = nullptr, free(i); this->rotates4d.clear();
			for (OpenDoor4D* i : this->openDoors4d)i = nullptr, free(i); this->openDoors4d.clear();
			for (std::vector<Constraint*> cs : this->constraintsVec) { for (Constraint* c : cs)c = nullptr, free(c); cs.clear(); }this->constraintsVec.clear();
			//judge_objects(this->groupIndices, this->groups, this->walls4d, this->terrains4d, this->camera.position4d, this->camera.forward4D, this->camera.wDir, this->objectLoadDistance);
			update_render_indices(this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d, this->sticks4d, this->springs4d, &this->renderIndices1, &this->renderIndices2, this->camera.position4d);
			sort_render_indices(&this->renderIndices1); sort_render_indices(&this->renderIndices2);
			update_collide_indices(this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d);
		}
		ImGui::TreePop();
	}

	if (ImGui::Button("Exit"))
	{
		glfwSetWindowShouldClose(this->window, GLFW_TRUE);
	}
	ImGui::End();

	select_ground_texture(&this->paintType0);
	select_object_texture(&this->buildTexture, 0);

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
		ImGui::Checkbox("Display Coordinate Lines 4D", &this->isRenderCoordinate4d);
		if (ImGui::Checkbox("Display Trails 4D", &this->isTrail4d))
		{
			if(!this->isTrail4d)
			for (int i(0); i < this->rigidBodies4d.size(); i++)
			{
				this->rigidBodies4d[i]->trail4D->reset_to_void();
			}
		}
		ImGui::Checkbox("Display Joint Lines 4D", &this->isJointLine4d);
		if (this->isTrail4d)
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
		if (ImGui::Checkbox("Is ACES", &this->isACES)) {
			this->shaders[WALLD4]->use();
			this->shaders[WALLD4]->set1i(this->isACES, "isACES");
			this->shaders[SKY_BOXD4]->use();;
			this->shaders[SKY_BOXD4]->set1i(this->isACES, "isACES");
			this->shaders[WATERD4]->use();
			this->shaders[WATERD4]->set1i(this->isACES, "isACES");
			this->shaders[EMITD4]->use();
			this->shaders[EMITD4]->set1i(this->isACES, "isACES");
			this->shaders[TERRAIND4]->use();
			this->shaders[TERRAIND4]->set1i(this->isACES, "isACES");
		}
		if (this->isACES)
		{
			ImGui::SameLine();
			if (ImGui::DragFloat("Adapted Lum", &this->adaptedLum, 0.01f, 0.f, INFINITY)) {
				this->shaders[WALLD4]->use();
				this->shaders[WALLD4]->set1f(this->adaptedLum, "adaptedLum");
				this->shaders[SKY_BOXD4]->use();;
				this->shaders[SKY_BOXD4]->set1f(this->adaptedLum, "adaptedLum");
				this->shaders[WATERD4]->use();
				this->shaders[WATERD4]->set1f(this->adaptedLum, "adaptedLum");
				this->shaders[EMITD4]->use();
				this->shaders[EMITD4]->set1f(this->adaptedLum, "adaptedLum");
				this->shaders[TERRAIND4]->use();
				this->shaders[TERRAIND4]->set1f(this->adaptedLum, "adaptedLum");
			}
		}
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
			for (Texture3D* i : this->textures3d)i->set_filter(this->filterType);
			for (Texture3D* i : this->particleTexs3d)i->set_filter(this->filterType);
			for (Texture3D* i : this->wallTexs3d)i->set_filter(this->filterType);
			for (Texture3D* i : this->groundTexs3d)i->set_filter(this->filterType);
		}
		if (ImGui::Selectable("Mag:Nearest/Min:Nearest Mipmap Linear"))
		{
			this->filterType = 1;
			textureFilterText = "Mag:Nearest/Min:Nearest Mipmap Linear";
			for (Texture* i : this->textures)i->set_filter(this->filterType);
			for (Texture* i : this->pointerTexs)i->set_filter(this->filterType);
			for (HDRTexture* i : this->hDRTextures)i->set_filter(this->filterType);
			for (HDRTexture* i : this->bloomExpandMaps)i->set_filter(this->filterType);
			for (Texture3D* i : this->textures3d)i->set_filter(this->filterType);
			for (Texture3D* i : this->particleTexs3d)i->set_filter(this->filterType);
			for (Texture3D* i : this->wallTexs3d)i->set_filter(this->filterType);
			for (Texture3D* i : this->groundTexs3d)i->set_filter(this->filterType);
		}
		if (ImGui::Selectable("Mag:Linear/Min:Linear"))
		{
			this->filterType = 2;
			textureFilterText = "Mag:Linear/Min:Linear";
			for (Texture* i : this->textures)i->set_filter(this->filterType);
			for (Texture* i : this->pointerTexs)i->set_filter(this->filterType);
			for (HDRTexture* i : this->hDRTextures)i->set_filter(this->filterType);
			for (HDRTexture* i : this->bloomExpandMaps)i->set_filter(this->filterType);
			for (Texture3D* i : this->textures3d)i->set_filter(this->filterType);
			for (Texture3D* i : this->particleTexs3d)i->set_filter(this->filterType);
			for (Texture3D* i : this->wallTexs3d)i->set_filter(this->filterType);
			for (Texture3D* i : this->groundTexs3d)i->set_filter(this->filterType);
		}
		if (ImGui::Selectable("Mag:Linear/Min:Linear Mipmap Linear"))
		{
			this->filterType = 3;
			textureFilterText = "Mag:Linear/Min:Linear Mipmap Linear";
			for (Texture* i : this->textures)i->set_filter(this->filterType);
			for (Texture* i : this->pointerTexs)i->set_filter(this->filterType);
			for (HDRTexture* i : this->hDRTextures)i->set_filter(this->filterType);
			for (HDRTexture* i : this->bloomExpandMaps)i->set_filter(this->filterType);
			for (Texture3D* i : this->textures3d)i->set_filter(this->filterType);
			for (Texture3D* i : this->particleTexs3d)i->set_filter(this->filterType);
			for (Texture3D* i : this->wallTexs3d)i->set_filter(this->filterType);
			for (Texture3D* i : this->groundTexs3d)i->set_filter(this->filterType);
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
	ImGui::ShowDemoWindow();
	}
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Game::area_delete(){
	this->deleteMap3d->getImageData();
	
	for (size_t index(1); index < this->rigidBodies4d.size(); index++) {
		glm::ivec4 gridPosition4D(glm::ivec4(floor(this->rigidBodies4d[index]->position4d)));
		if (this->deleteMap3d->isDelete(glm::ivec3(gridPosition4D.w + 64.f, gridPosition4D.z + 64.f, gridPosition4D.x + 64.f)))
		{
			if (this->rigidBodies4d[index - 1]->objectName != "Ground")
			{
				delete_object4d(&this->rigidBodies4d, &this->walls4d, &this->groupIndices, this->groups, this->camera.position4d, &this->renderIndices1, &this->renderIndices2, &this->constraintsVec, &this->dynamiteIndices, &this->sticks4d, &this->springs4d, &this->hingeConstraintsVec, &this->shifts4d, &this->floats4d, &this->rotates4d, &this->openDoors4d, index);
				index--;
			}
		}
	}

	for (size_t index(0); index < this->walls4d.size(); index++) {
		glm::ivec4 gridPosition4D(glm::ivec4(floor(this->walls4d[index]->position4d)));
		if (this->deleteMap3d->isDelete(glm::ivec3(gridPosition4D.w + 64.f, gridPosition4D.z + 64.f, gridPosition4D.x + 64.f)))
		{
			if (this->walls4d[index]->objectName != "Ground")
			{
				delete_object4d(&this->rigidBodies4d, &this->walls4d, &this->groupIndices, this->groups, this->camera.position4d, &this->renderIndices1, &this->renderIndices2, &this->constraintsVec, &this->dynamiteIndices, &this->sticks4d, &this->springs4d, &this->hingeConstraintsVec, &this->shifts4d, &this->floats4d, &this->rotates4d, &this->openDoors4d, index + this->rigidBodies4d.size());
				index--;
			}
		}
	}

	for (size_t index(0); index < size_of_objects4d(this->sticks4d,this->springs4d); index++) {
		Object4D* a(find_joint4d(this->sticks4d, this->springs4d, index));
		glm::ivec4 gridPosition4D(glm::ivec4(floor(a->position4d)));
		if (this->deleteMap3d->isDelete(glm::ivec3(gridPosition4D.w + 64.f, gridPosition4D.z + 64.f, gridPosition4D.x + 64.f)))
		{
			erase_joint4d0(&this->sticks4d, &this->springs4d, index);
			for (size_t i(0); i < size_of_objects4d(this->rigidBodies4d, this->walls4d); i++)
			{
				for (size_t j(0); j < OPENDOOR4D_ANIMATION + 1; j++)find_object4d(this->rigidBodies4d, this->walls4d, i)->componentsVec[j].clear();
			}
			update_components_index(this->rigidBodies4d, this->walls4d, dynamiteIndices, sticks4d, springs4d, hingeConstraintsVec, shifts4d, floats4d, rotates4d, openDoors4d);
			index--;
		}
	}

	bool isPointLightRemoved(false);
	for (size_t index(0); index < this->pointLights4d.size(); index++) {
		glm::ivec4 gridPosition4D(glm::ivec4(floor(this->pointLights4d[index]->position4d)));
		if (this->deleteMap3d->isDelete(glm::ivec3(gridPosition4D.w + 64.f, gridPosition4D.z + 64.f, gridPosition4D.x + 64.f)))
		{
			this->pointLights4d[index] = nullptr, free(this->pointLights4d[index]);
			this->pointLights4d.erase(this->pointLights4d.begin() + index);
			index--;
			isPointLightRemoved = true;
		}
	}

	if (isPointLightRemoved)
	{
		update_point_light4d_id(&this->pointLights4d);
		update_point_light4d(this->pointLights4d, this->shaders[WALLD4], this->shaders[TERRAIND4], this->shaders[LIGHT_MAPD3]);
		this->shaders[LIGHT_MAPD3]->use();
		this->lightMap3d->bind_image(0);
		glDispatchCompute(4, 128, 4);
		glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
	}

	update_render_indices(this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d, this->sticks4d, this->springs4d, &this->renderIndices1, &this->renderIndices2, this->camera.position4d);
	sort_render_indices(&this->renderIndices1); sort_render_indices(&this->renderIndices2);
	update_collide_indices(this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d);
}
