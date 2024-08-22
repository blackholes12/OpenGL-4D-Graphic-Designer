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
	float judgetime0,judgetime1, judgetime2, judgetime3;
	bool isFixedTime;
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
	bool curserMode;
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
	Shader* shader2DShape;
	std::vector < Shader*> shaderHDRs;
	//Textures
	std::vector<Texture*> textures;
	std::vector<Texture*> pointerTexs;
	std::vector<Texture3D*> textures3D;
	std::vector<Texture3D*> particleTexs3D;
	std::vector<Texture3D*> wallTexs3D;
	std::vector<Texture3D*> groundTexs3D;
	DeleteMap3D* deleteMap3D;
	std::vector < HDRTexture*> hDRTextures;
	std::vector < HDRTexture*> bloomMipMaps;
	//Materials
	//2D shapes 
	Rectangle2D* rectangle2D;
	Rectangle2D* targetIcon;
	Rectangle2D* hdrQuad;
	//Sounds
	std::vector<Sound*> sounds;
	std::vector<Music*> musics;
	//Models
	std::vector<Object*> objects;
	std::vector<Wall4D*> walls4D;
	std::vector<Wall4D*> dynamites4D;
	std::vector<RigidBody4D*> rigidBodies4D;
	std::vector<RigidBody4D*> dynamites4D2;
	std::vector<Terrain4D*> terrains4D;
	std::vector<Water4D*> waters4D;
	Sky_Box4D* skybox4D;
	Demo4D* demoObjects4D;
	std::vector <Demo4D*> demos4D;
	std::vector<Group*> groups;
	std::vector<Emitter4D*> emitters4D;
	std::vector<RenderIndex*> renderIndices1;
	std::vector<RenderIndex*> renderIndices2;
	//Lines
	Coordinate4D* coordinate4D;
	std::vector <JointLine4D*> dragLines4D;
	std::vector <XRay4D*> xRays4D;
	bool isRenderCoordinate4D;
	//Lights
	std::vector<PointLight*> pointLights;
	std::vector<PointLight4D*> pointLights4D;
	DirectionLight4D* directionLight4D;
	int lightId;
	std::vector<DirectionLight*> directionLights;
	//physical
	std::vector < std::vector<Collision>> collisionsVec;
	std::vector <std::vector<Constraint*>> constraintsVec;
	std::vector <std::vector<Constraint*>> constraintsVec2;
	std::vector < std::vector < HingeConstraint4D>> hingeConstraintsVec;
	std::vector < Stick4D*> sticks4D;
	std::vector < Spring4D*> springs4D;
	std::vector < Shift4D*> shifts4D;
	std::vector < Float4D*> floats4D;
	std::vector < Rotate4D*> rotates4D;
	//logo
	int texSizeX, texSizeY;
	//settings
	int level;
	int blockLoadDistance;
	int objectLoadDistance;
	bool isFramework;
	int FrameworkProjectionType;
	float projectionScaler;
	bool isFog;
	float fogDensity;
	//gameing
	glm::vec4 hittingPos4D;
	int hitIndex;
	Object4D* hitObject4D;
	glm::vec4 hitPosNear;
	glm::vec4 hitPosToBody;
	glm::vec4 hitNormal;
	int mode;
	int shootType;
	int reflectionSteps;
	int controlType;
	bool isHardPainting;
	bool isSphericalPainting;
	int paintScale;
	int paintType0;
	int paintType;

	bool isRigidBody;
	const char* buildTag;
	float stickLength;
	float springLength;
	float springStrength;
	int buildMode;
	bool isFindPoint;
	int buildTexture;
	int buildShader;
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
	bool isIlluminate;
	bool isGravity;
	bool isTrail4D;
	int trailFadeType;
	bool isJointLine4D;
	bool isCloud;
	bool isSkyBoxFog;
	bool isHDR;
	bool isBloom;
	float bloomMultiplier;
	bool isAutoExposure;
	float exposure;
	float exposure2;
	float exposureSpeed;
	float exposureMultiplier;
	unsigned filterType;

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
	void updateModes(int mode, int shift);
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
	void render0();
	//static void scroll_call_back(GLFWwindow* window, double xOffset, double yOffset);
};