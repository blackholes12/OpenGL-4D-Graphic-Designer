#pragma once

#include "libs.h"

//ZOOOOOOOOOOOM IN BEFORE RECORDING!


class Game
{
public:
	//Variables
		//Window
	GLFWwindow* window;
private:
	GLFWimage icons[4];
	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	int framebufferWidth;
	int framebufferHeight;
	int deviceWidth;
	int deviceHeight;
	int windowPosX;
	int windowPosY;
	int vsync;
	bool isFullscreen = false;
	//OpenGL Context
	const int GL_VERSION_MAJOR;
	const int GL_VERSION_MINOR;

	//Delta time
	float dt;
	float curTime;
	float lastTime;
	float worldTime;
	float judgetime1, judgetime2, judgetime3;
public:
	bool isFixedTime;
private:
	//Mouse Input
	double lastMouseX;
	double lastMouseY;
	double mouseX;
	double mouseY;
	double mouseOffsetX;
	double mouseOffsetY;
	bool firstMouse;

	double lastMouseX2;
	double lastMouseY2;
	double mouseX2;
	double mouseY2;
	double mouseOffsetX2;
	double mouseOffsetY2;
	bool firstMouse2;
	float ratio;
	int pageType;
	bool isDebug;
	bool editMode;
public:
	bool isCloseUI;
private:
	//Key board Input
	std::vector <Input*> inputs;
	char cMoveForward;
	int iMoveForward;
	char cMoveBackward;
	int iMoveBackward;
	char cMoveLeft;
	int iMoveLeft;
	char cMoveRight;
	int iMoveRight;
	char cMoveAna;
	int iMoveAna;
	char cMoveKata;
	int iMoveKata;
	char cTurnDirection;
	int iTurnDirection;
	char cSwitchFrame;
	int iSwitchFrame;
	char cSwitchCoordinate;
	int iSwitchCoordinate;
	char cSwitchInventory;
	int iSwitchInventory;
	char cFovIn;
	int iFovIn;
	char cFovOut;
	int iFovOut;
	//Camera
	Camera camera;
	//Matrices

	//Shaders
	std::vector<Shader*> shaders;
	Shader* shader2dShape;
	std::vector < Shader*> shaderHDRs;
	//Textures
	std::vector<Texture*> textures;
	std::vector<Texture*> pointerTexs;
	std::vector<Texture3D*> textures3d;
	std::vector<Texture3D*> particleTexs3d;
	std::vector<Texture3D*> wallTexs3d;
	std::vector<Texture3D*> groundTexs3d;
	CustomTexture3D* deleteMap3d;
	CustomTexture3D* lightMap3d;
	std::vector < HDRTexture*> hDRTextures;
	std::vector < HDRTexture*> bloomExpandMaps;
	//Materials
	//2D shapes 
	Image2D* image2d;
	Image2D* targetIcon;
	Image2D* hdrQuad;
	std::vector<Canvas2D*> canvas2d;
	//Sounds
	std::vector<Sound*> sounds;
	std::vector<Music*> musics;
	//Models
	std::vector<Object*> objects;
	public:
	std::vector<Wall4D*> walls4d;
	std::vector<RigidBody4D*> rigidBodies4d;
	private:
	std::vector<DynamiteIndex*> dynamiteIndices;
	std::vector<Terrain4D*> terrains4d;
	std::vector<Water4D*> waters4d;
	Sky_Box4D* skybox4d;
	Demo4D* demoObjects4d;
	std::vector <Demo4D*> demos4d;
	Wall4D* groupAreaHypercube;
	std::vector<Group*> groups;
	std::vector<size_t> groupIndices;
	std::vector<Emitter4D*> emitters4d;
	std::vector<RenderIndex*> renderIndices1;
	std::vector<RenderIndex*> renderIndices2;
	//Lines
	Coordinate4D* coordinate4d;
	std::vector <JointLine4D*> dragLines4d;
	std::vector <XRay4D*> xRays4d;
	bool isRenderCoordinate4d;
	//Lights
	std::vector<PointLight*> pointLights;
	std::vector<PointLight4D*> pointLights4d;
	DirectionLight4D* directionLight4d;
	std::vector<DirectionLight*> directionLights;
	//physical
	public:
	std::vector < std::vector<Collision>> collisionsVec;
	private:
	std::vector <std::vector<Constraint*>> constraintsVec;
	std::vector < std::vector < HingeConstraint4D*>> hingeConstraintsVec;
	std::vector < Stick4D*> sticks4d;
	std::vector < Spring4D*> springs4d;
	std::vector < Shift4D*> shifts4d;
	std::vector < Float4D*> floats4d;
	std::vector < Rotate4D*> rotates4d;
	std::vector < OpenDoor4D*> openDoors4d;
	//logo
	int texSizeX, texSizeY;
	//settings
	int level;
	int page;
	int blockLoadDistance;
	int objectLoadDistance;
	bool isFramework;
	int frameworkProjectionType;
	float projectionScaler;
	bool isShowingGroupArea;
	bool isFog;
	float fogDensity;
	//gameing
	glm::vec4 hittingPos4D;
	VectorIndex hitIndex;
	Object4D* hitObject4D;
	glm::vec4 hitPosNear;
	glm::vec4 hitPosToBody;
	glm::vec4 hitNormal;
	glm::vec4 cameraPosShift4D;
	int mode;
	unsigned char shootType;
	int reflectionSteps;
	unsigned char controlType;
	bool isHardPainting;
	bool isSphericalPainting;
	int paintScale;
	size_t paintType0;
	size_t paintType;
	int penetrationCount;

	bool isRigidBody;
	const char* buildTag;
	float stickLength;
	float springLength;
	float springStrength;
	unsigned char buildMode;
	glm::vec2 buildDistance;
	glm::vec4 buildOffset;
	bool isFindPoint;
	size_t buildTexture;
	size_t buildShader;
	bool isSpecular;
	glm::vec4 buildColor;
	glm::vec4 buildMetalColor;
	bool isRandomColor;
	glm::vec4 buildScale;
	alg::bivec4 buildRotation;
	glm::vec4 initialVelocity;
	alg::bivec4 initialAngularVelocity;
	int buildCol;
	glm::vec4 buildParameter;
	float lightIntensity;
	glm::vec3 lightColor;
	float lightRadius;
	bool isGravity;
	bool isTrail4d;
	int trailFadeType;
	bool isJointLine4d;
	bool isCloud;
	bool isACES;
	float adaptedLum;
	bool isSkyBoxFog;
	bool isHDR;
	bool isBloom;
	float bloomMultiplier;
	bool isAutoExposure;
	float exposure;
	float exposure2;
	float exposureSpeed;
	float exposureMultiplier;
	unsigned char filterType;

	float soundVolume;
	float soundPitch;
	bool isPlayingMusic;
	float musicVolume;
	float musicPitch;

	//Private functions
	void startGLFW();
	void startWindow(
		const char* title,
		bool resizable
	);
	void startGLEW(); //AFTER CONTEXT CREATION!!!
	void startLoad();
	void startOpenGLOptions();
	void startMatrices();
	void startShaders();
	void startTextures();
	void startDemos();
	void startSounds();
	void startGui2();
	void startObjects(int level, const char* filePath);
	void startLines();
	void startLevel(int level, const char* filePath);
	void startDefault();
	void startInputs();
	//Static variables
public:
	//Constructors / Destructors
	Game(
		const char* title,
		const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
		const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
		bool resizable
	);
	virtual ~Game();

	//Accessors
	int getWindowShouldClose();
	//Modifiers
	void setWindowShouldClose();
	//Functions
	void firstUpdate();
	void updateProjectMat(int fbW, int fbH);
	void updateUniforms();
	void judgeRender();
	void updateObjects();
	void updateLights();
	void textinputs_add(unsigned int c);
	void textinputs_delete(int key, int action);
	void update_scroll_input(int mode, int yOffset);
	void updateCollider();
	void updateDynamites();
	void updateParticles();
	void imgui_use();
	void area_delete();
	void updateDt();
	void updateTime();
	void updateMouseInput();
	void updateKeyboardInput();
	void updateInput();
	void beforeRender();
	void update0();
	void update1();
	void render0();
	//static void scroll_call_back(GLFWwindow* window, double xOffset, double yOffset);
};