#include"Game_imgui.h"
#include"OpenglOptions.h"
#include"StartObj.h"
#include"Physics.h"
#include"Keyboard.h"
//Private functions
void Game::startGLFW()
{
	//INIT GLFW
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "ERROR::GLFW_INIT_FAILED" << "\n";
		glfwTerminate();
	}
}

void Game::startWindow(
	const char* title,
	bool resizable
)
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_VERSION_MINOR);
	glfwWindowHint(GLFW_RESIZABLE, resizable);

	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); MAC OS

	this->window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, title, NULL, NULL);
	if (this->window == nullptr)
	{
		std::cout << "ERROR::GLFW_WINDOW_INIT_FAILED" << "\n";
		glfwTerminate();
	}
	glfwSetWindowMonitor(this->window, NULL, 0, 45, this->WINDOW_WIDTH, this->WINDOW_HEIGHT, GLFW_DONT_CARE);
	this->icons[0].pixels = SOIL_load_image("resourcefile/images/icon1-1.png", &icons[0].width, &icons[0].height, 0, SOIL_LOAD_RGBA);
	this->icons[1].pixels = SOIL_load_image("resourcefile/images/icon1-2.png", &icons[1].width, &icons[1].height, 0, SOIL_LOAD_RGBA);
	this->icons[2].pixels = SOIL_load_image("resourcefile/images/icon1-3.png", &icons[2].width, &icons[2].height, 0, SOIL_LOAD_RGBA);
	this->icons[3].pixels = SOIL_load_image("resourcefile/images/icon1-4.png", &icons[3].width, &icons[3].height, 0, SOIL_LOAD_RGBA);
	glfwSetWindowIcon(this->window, 4, icons);
	for (size_t i(0); i < 4; i++)
	SOIL_free_image_data(icons[i].pixels);
	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);
	//IMPORTANT WHITH PERSPECTIVE MATRIX!!!
	glfwMakeContextCurrent(this->window); //IMPORTANT!!
	this->vsync = 1;
	glfwSwapInterval(this->vsync); // Enable vsync
	start_imgui(this->window);

	//glClearColor(0.15f, 0.5f, 0.85f, 1.f);
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(this->window);
}

void Game::startGLEW()
{
	//INIT GLEW (NEEDS WINDOW AND OPENGL CONTEXT)
	glewExperimental = GL_TRUE;
	//Error
	if (glewInit() != GLEW_OK)
	{
		std::cout << "ERROR::MAIN.CPP::GLEW_INIT_FAILED" << "\n";
		glfwTerminate();
	}
}
//load logo

void Game::startLoad()
{
	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);
	glfwGetWindowPos(this->window, &this->windowPosX, &this->windowPosY);
	GetDesktopResolution(this->deviceWidth, this->deviceHeight);
	this->shader2dShape = new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		"resourcefile/shaders/shape2D.vertex", "resourcefile/shaders/shape2D.fragment");
	this->textures.push_back(new Texture("resourcefile/images/logo.png"));
	this->image2d = new Image2D(0);
	glClearColor(0.1f, 0.1f, 0.1f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	float photoRate((float)this->textures[this->image2d->textureIndex]->height / (float)this->textures[this->image2d->textureIndex]->width);
	float screenRate((float)this->framebufferHeight / (float)this->framebufferWidth);
	glm::vec2 photoScale;
	if (photoRate < screenRate) photoScale = glm::vec2(1.f, photoRate / screenRate);
	else photoScale = glm::vec2(screenRate / photoRate,1.f);
	this->image2d->render(this->textures[this->image2d->textureIndex],this->shader2dShape, photoScale);
	this->hdrQuad = new Image2D(0);
	//End Draw
	glfwSwapBuffers(this->window);
}

void Game::startOpenGLOptions()
{
	set_gl_options(this->window);
}

void Game::startShaders()
{
	this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		"resourcefile/shaders/obj.vertex", "resourcefile/shaders/obj.fragment"));
	this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		"resourcefile/shaders/sky_box4D.vertex", "resourcefile/shaders/sky_box4D.fragment"));
	this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		"resourcefile/shaders/obj4D.vertex", "resourcefile/shaders/wall4D.fragment"));
	this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		"resourcefile/shaders/obj4D.vertex", "resourcefile/shaders/demo4D.fragment"));
	this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		"resourcefile/shaders/obj4D.vertex", "resourcefile/shaders/emit4D.fragment"));
	this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		"resourcefile/shaders/terrain4D.vertex", "resourcefile/shaders/terrain4D.fragment"));
	this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		"resourcefile/shaders/water4D.vertex", "resourcefile/shaders/water4D.fragment"));
	this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		"resourcefile/shaders/particle4D.vertex", "resourcefile/shaders/particle4D.fragment"));
	this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		"resourcefile/shaders/light_particle4D.vertex", "resourcefile/shaders/light_particle4D.fragment"));
	this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		"resourcefile/shaders/coordinate4d.vertex", "resourcefile/shaders/coordinate4d.fragment"));
	this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		"resourcefile/shaders/trail4D.vertex", "resourcefile/shaders/trail4D.fragment"));
	this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		"resourcefile/shaders/trail4D.vertex", "resourcefile/shaders/joint_line4D.fragment"));
	this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		"resourcefile/shaders/frame4D.vertex", "resourcefile/shaders/frame4D.fragment"));
	this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		"resourcefile/shaders/light_frame4D.vertex", "resourcefile/shaders/light_frame4D.fragment"));
	this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		"resourcefile/shaders/ambient_occlusion.vertex", "resourcefile/shaders/ambient_occlusion.fragment"));
	this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		"resourcefile/shaders/light_map3D.txt"));
	this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		"resourcefile/shaders/text.vertex", "resourcefile/shaders/text.fragment"));
	this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		"resourcefile/shaders/rectangle.vertex", "resourcefile/shaders/rectangle.fragment"));
	
	this->shaderHDRs.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		"resourcefile/shaders/hdr.vertex", "resourcefile/shaders/hdr.fragment"));
	this->shaderHDRs.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		"resourcefile/shaders/hdr.vertex", "resourcefile/shaders/hdr_exposure.fragment"));
	this->shaderHDRs.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		"resourcefile/shaders/hdr.vertex", "resourcefile/shaders/bloom_sub.fragment"));
	this->shaderHDRs.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		"resourcefile/shaders/hdr.vertex", "resourcefile/shaders/bloom_sub_exposure.fragment"));
	this->shaderHDRs.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		"resourcefile/shaders/hdr.vertex", "resourcefile/shaders/bloom_expand.fragment"));
	this->shaderHDRs.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		"resourcefile/shaders/hdr.vertex", "resourcefile/shaders/bloom.fragment"));
}

void Game::startMatrices()
{
	this->updateProjectMat(this->framebufferWidth, this->framebufferHeight);
}

void Game::startTextures()
{
	this->textures.push_back(new Texture(
		"resourcefile/images/maps/POINT_LIGHT.png"));
	this->textures.push_back(new Texture(
		"resourcefile/images/maps/BRIGHTNESS.png"));
	this->textures.push_back(new Texture(
		"resourcefile/images/maps/BLACK_BODY.png"));
	char ss[256];
	for (int i(1); i <= 10; i++){
		snprintf(ss, 255, "resourcefile/images/2d/i1-%i.png", i);
		this->textures.push_back(new Texture(ss));
	}
	for (int i(1); i <= 59; i++){
		snprintf(ss, 255, "resourcefile/images/2d/i2-%i.png", i);
		this->textures.push_back(new Texture(ss));
	}
	for (int i(1); i <= 8; i++){
		snprintf(ss, 255, "resourcefile/images/2d/i3-%i.png", i);
		this->textures.push_back(new Texture(ss));
	}
	this->pointerTexs.push_back(new Texture(
		"resourcefile/images/gui/edit pointer.png"));
	this->pointerTexs.push_back(new Texture(
		"resourcefile/images/gui/target pointer.png"));
	this->pointerTexs.push_back(new Texture(
		"resourcefile/images/gui/control pointer.png"));
	this->pointerTexs.push_back(new Texture(
		"resourcefile/images/gui/paint pointer.png"));
	this->pointerTexs.push_back(new Texture(
		"resourcefile/images/gui/build pointer.png"));
	this->pointerTexs.push_back(new Texture(
		"resourcefile/images/gui/delete pointer.png"));
	this->pointerTexs.push_back(new Texture(
		"resourcefile/images/gui/area delete pointer.png"));
	this->hDRTextures.push_back(new HDRTexture(this->framebufferWidth, this->framebufferHeight));
	this->hDRTextures.push_back(new HDRTexture(this->framebufferWidth / 3, this->framebufferHeight / 3));
	this->hDRTextures.push_back(new HDRTexture(3, 3));
	this->hDRTextures[1]->set_filter(1);
	
	for (size_t i(0); i < 11; i++)
	{
		this->bloomExpandMaps.push_back(new HDRTexture(this->framebufferWidth / 3, this->framebufferHeight / 3));
		this->bloomExpandMaps[i]->set_filter(1);
	}

	this->textures[1]->bind(2);
	this->textures[2]->bind(3);

	this->textures3d.push_back(new Texture3D(
		"resourcefile/images/noise2.png"));
	this->textures3d.push_back(new Texture3D(
		"resourcefile/images/sky_panorama/sky_phase_map.png"));
	this->textures3d[TEX_STARS_FIELD_3D]->set_warp(1);
	this->textures3d.push_back(new Texture3D(
		"resourcefile/images/maps/NOISE_NORMAL4D.png"));
	this->textures3d.push_back(new Texture3D(
		"resourcefile/images/animation/caustics.png"));
	this->textures3d.push_back(new Texture3D(
		"resourcefile/images/maps/BLEND.png"));
	this->textures3d.push_back(new Texture3D(
		"resourcefile/images/maps/AREA.png"));
	this->textures3d.push_back(this->textures3d[AREA]);

	this->particleTexs3d.push_back(new Texture3D(
		"resourcefile/images/particle/FIRE.png"));
	this->particleTexs3d.push_back(new Texture3D(
		"resourcefile/images/particle/PARTICLE1.png"));
	this->particleTexs3d.push_back(new Texture3D(
		"resourcefile/images/particle/PARTICLE2.png"));
	this->particleTexs3d.push_back(new Texture3D(
		"resourcefile/images/particle/PARTICLE3.png"));

	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/PURE_RED.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/PURE_RED_HARFGREEN.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/PURE_RED_GREEN.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/PURE_HARFRED_GREEN.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/PURE_GREEN.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/PURE_GREEN_HARFBLUE.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/PURE_GREEN_BLUE.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/PURE_HARFGREEN_BLUE.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/PURE_BLUE.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/PURE_HARFRED_BLUE.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/PURE_RED_BLUE.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/PURE_RED_HARFBLUE.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/PURE_WHITE.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/PURE_BLACK.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/STONE.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/CHESSBOARD0.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/DEFAULTCHESSBOARD2.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/YELLOW.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/GROUND.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/PURPLE.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/BLUE.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/BLUE_WHITE.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/RED.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/GREEN2.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/ORANGE.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/GRID2.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/GREENBLUE.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/CHESSBOARD.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/WHITEWALL.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/GREENMARBLE.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/WHITEMARBLE.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/YELLOWMARBLE.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/YELLOWGROUNDMARBLE.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/DEFAULTCHESSBOARD.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/PURPLEMARBLE.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/BLUEMARBLE.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/REDMARBLE.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/GREEN2MARBLE.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/ORANGEMARBLE.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/GREENBLUEMARBLE.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/CHESSBOARDMARBLE.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/WHITEMAINMARBLE.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/CONCRETE.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/YELLOWCONCRETE.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/WHITECONCRETE.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/GRASS.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/WOODX.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/WOODY.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/WOODZ.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/OLDWOODX.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/OLDWOODY.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/OLDWOODZ.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/GLASS.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/GRID.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/STARS.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/STARS_SKY.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/LAVA.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/CEIL1.png"));
	this->wallTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/CEIL2.png"));

	this->groundTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/SAND.png"));
	this->groundTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/SNOW.png"));
	this->groundTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/ICE.png"));
	this->groundTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/GRASS.png"));
	this->groundTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/GRASS2.png"));
	this->groundTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/SOIL.png"));
	this->groundTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/GRASS3.png"));
	this->groundTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/GRASS4.png"));
	this->groundTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/SAND_SOIL.png"));
	this->groundTexs3d.push_back(new Texture3D(
		"resourcefile/images/textures/SAND_SOIL2.png"));

	for (size_t i(0); i < 10; i++)
	{
		this->groundTexs3d.push_back(this->groundTexs3d[i]);
	}

	this->deleteMap3d = new CustomTexture3D();
	this->lightMap3d = new CustomTexture3D(glm::ivec3(32,1024,64),GL_RGBA16F);

	this->textures3d[TEX_NOISE_3D]->bind(4);
	this->textures3d[TEX_STARS_FIELD_3D]->bind(5);
	this->textures3d[TEX_NORMAL_4D]->bind(6);
	this->textures3d[CAUSTICS]->bind(7);
	this->textures3d[BLEND]->bind(8);
	this->textures3d[AREA]->bind(9);
	this->lightMap3d->bind(10);

	this->deleteMap3d->bind(11);

	for (size_t i(0); i < 20; i++)
	{
		this->groundTexs3d[i]->bind(i+12);
	}
}

void Game::startSounds()
{
	this->sounds.push_back(new Sound(
		"resourcefile/sounds/sounds/explosion-1.wav"));//0
	this->sounds.push_back(new Sound(
		"resourcefile/sounds/sounds/explosion-2.wav"));
	this->sounds.push_back(new Sound(
		"resourcefile/sounds/sounds/explosion-3.wav"));
	this->sounds.push_back(new Sound(
		"resourcefile/sounds/sounds/explosion-4.wav"));
	this->sounds.push_back(new Sound(
		"resourcefile/sounds/sounds/gun-shot-1.wav"));
	this->sounds.push_back(new Sound(
		"resourcefile/sounds/sounds/gun-shot-2.mp3"));//5
	this->sounds.push_back(new Sound(
		"resourcefile/sounds/sounds/collide-1.mp3"));
	this->sounds.push_back(new Sound(
		"resourcefile/sounds/sounds/place-1.mp3"));
	this->sounds.push_back(new Sound(
		"resourcefile/sounds/sounds/glass-breaking-2.mp3"));
	this->musics.push_back(new Music(
		"resourcefile/sounds/musics/Stellardrone - In Time [mqms2].ogg"));
	this->musics.push_back(new Music(
		"resourcefile/sounds/musics/Stellardrone - Rendezvous With Rama [mqms2].ogg"));
	this->musics.push_back(new Music(
		"resourcefile/sounds/musics/Stellardrone - Light Years [mqms2].ogg"));
}

void Game::startDemos()
{
	//start_menu 0
	this->canvas2d.push_back(new Canvas2D(
		{ new Text2D(L"4D Graphic Designer", 960, 100, 8, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 0, false) },
		{},
		{},
		{ new Button2D(
		new ImageTextPair2D(new Text2D(L"Play", 0, 0, 1, 24, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false), nullptr, glm::ivec2(0), 0),
		new Rectangle2D(860, 450, 200, 24, 4, 3, -1, glm::vec4(0.25f, 0.51f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
		glm::vec4(0.45f, 0.71f, 1.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 1.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 0.f, 1.f), 0, 0, L"Button")
		,
		new Button2D(
		new ImageTextPair2D(new Text2D(L"Goals", 0, 0, 1, 24, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false), nullptr, glm::ivec2(0), 0),
		new Rectangle2D(860, 517, 200, 24, 4, 3, -1, glm::vec4(0.25f, 0.51f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
		glm::vec4(0.45f, 0.71f, 1.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 1.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 0.f, 1.f), 0, 0, L"Button")
		,
		new Button2D(
		new ImageTextPair2D(new Text2D(L"Settings", 0, 0, 1, 24, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false), nullptr, glm::ivec2(0), 0),
		new Rectangle2D(860, 583, 200, 24, 4, 3, -1, glm::vec4(0.25f, 0.51f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
		glm::vec4(0.45f, 0.71f, 1.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 1.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 0.f, 1.f), 0, 0, L"Button")
		,
		new Button2D(
		new ImageTextPair2D(new Text2D(L"Quit", 0, 0, 1, 24, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false), nullptr, glm::ivec2(0), 0),
		new Rectangle2D(860, 650, 200, 24, 4, 3, -1, glm::vec4(0.25f, 0.51f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
		glm::vec4(0.45f, 0.71f, 1.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 1.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 0.f, 1.f), 0, 0, L"Button") },
		{},
		{},
		{},
		{},
		{},
		{},
		0
	));
	//goals 1
	this->canvas2d.push_back(new Canvas2D(
		{ new Text2D(L"Game goals:", 0, 0, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"1.Explore the game scene route to reach the destination without disrupting the game scene.", 0, 27, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"2.Find the shortest route to reach the destination without disrupting obstacles.", 0, 54, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"3. Understand the operation logic of high-dimensional space based on the slicing of four-dimensional space in three-dimensional space, and find the similarities and differences between three-dimensional space and four-dimensional space.", 0, 81, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false) },
		{},
		{},
		{ new Button2D(
		new ImageTextPair2D(new Text2D(L"Back To Title", 0, 0, 1, 24, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false), nullptr, glm::ivec2(0), 0),
		new Rectangle2D(0, 181, 200, 24, 4, 3, -1, glm::vec4(0.25f, 0.51f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
		glm::vec4(0.45f, 0.71f, 1.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 1.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 0.f, 1.f), 0, 0, L"Button")},
		{},
		{},
		{},
		{},
		{},
		{},
		1
	));
	//settings 2
	this->canvas2d.push_back(new Canvas2D(
		{ new Text2D(L"Settings", 212, 64, 1, 24, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false) },
		{},
		{ new Rectangle2D(200, 64, 734, 260, 4, 3, -1, glm::vec4(0.25f,0.51f,1.f,1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
		new Rectangle2D(200, 64, 203, 39, 4, 3, -1, glm::vec4(0.25f,0.51f,1.f,1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)) },
		{
		new Button2D(
		new ImageTextPair2D(new Text2D(L"Back To Title", 0, 0, 1, 24, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false), nullptr, glm::ivec2(0), 0),
		new Rectangle2D(0, 0, 200, 24, 4, 3, -1, glm::vec4(0.25f, 0.51f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
		glm::vec4(0.45f, 0.71f, 1.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 1.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 0.f, 1.f), 0, 0, L"Button"),
		new Button2D(
		new ImageTextPair2D(new Text2D(L"Display", 300, 100, 1, 24, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false), nullptr, glm::ivec2(0), 0),
		new Rectangle2D(200, 108, 200, 24, 4, 3, -1, glm::vec4(0.25f, 0.51f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
		glm::vec4(0.45f, 0.71f, 1.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 1.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 0.f, 1.f), 0, 0, L"Button") ,
		new Button2D(
		new ImageTextPair2D(new Text2D(L"Controls", 300, 150, 1, 24, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false), nullptr, glm::ivec2(0), 0),
		new Rectangle2D(200, 140, 200, 24, 4, 3, -1, glm::vec4(0.25f, 0.51f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
		glm::vec4(0.45f, 0.71f, 1.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 1.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 0.f, 1.f), 0, 0, L"Button") ,
		new Button2D(
		new ImageTextPair2D(new Text2D(L"Sound", 300, 200, 1, 24, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false), nullptr, glm::ivec2(0), 0),
		new Rectangle2D(200, 172, 200, 24, 4, 3, -1, glm::vec4(0.25f, 0.51f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
		glm::vec4(0.45f, 0.71f, 1.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 1.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 0.f, 1.f), 0, 0, L"Button") ,
		new Button2D(
		new ImageTextPair2D(new Text2D(L"Graphic", 300, 250, 1, 24, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false), nullptr, glm::ivec2(0), 0),
		new Rectangle2D(200, 204, 200, 24, 4, 3, -1, glm::vec4(0.25f, 0.51f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
		glm::vec4(0.45f, 0.71f, 1.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 1.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 0.f, 1.f), 0, 0, L"Button") ,
		new Button2D(
		new ImageTextPair2D(new Text2D(L"Camera", 300, 300, 1, 24, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false), nullptr, glm::ivec2(0), 0),
		new Rectangle2D(200, 236, 200, 24, 4, 3, -1, glm::vec4(0.25f, 0.51f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
		glm::vec4(0.45f, 0.71f, 1.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 1.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 0.f, 1.f), 0, 0, L"Button") },
		{},
		{},
		{},
		{},
		{},
		{ new Pages2D({
			new Page2D({
		new Text2D(L"Display", 412, 64, 1, 24, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false)
				},{},{},{},{},{},{},{},{new ScrollView2D(
		new Rectangle2D(400, 100, 534, 224, 4, 3, -1, glm::vec4(0.25f,0.25f,0.25f,1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
			new Rectangle2D(910, 100, 24, 224, 4, 3, -1, glm::vec4(0.25f,0.51f,1.f,1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
			new Button2D(
		new ImageTextPair2D(nullptr,nullptr,glm::ivec2(0),12),
		new Rectangle2D(500, 100, 24, 200, 4, 3, -1, glm::vec4(0.25f,0.51f,1.f,1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
		glm::vec4(0.45f, 0.71f, 1.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 1.f, 0.f ,1.f), glm::vec4(1.f, 1.f, 0.f, 1.f),1,3,L"Button"),
						new Button2D(
		new ImageTextPair2D(nullptr,nullptr,glm::ivec2(0),12),
		new Rectangle2D(910, 100, 24, 24, 4, 3, -1, glm::vec4(0.25f,0.51f,1.f,1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
		glm::vec4(0.45f, 0.71f, 1.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 1.f, 0.f ,1.f), glm::vec4(1.f, 1.f, 0.f, 1.f),1,3,L"Button"),
						new Button2D(
		new ImageTextPair2D(nullptr,nullptr,glm::ivec2(0),12),
		new Rectangle2D(910, 300, 24, 24, 4, 3, -1, glm::vec4(0.25f,0.51f,1.f,1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
		glm::vec4(0.45f, 0.71f, 1.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 1.f, 0.f ,1.f), glm::vec4(1.f, 1.f, 0.f, 1.f),1,3,L"Button"),
			glm::ivec2(500,600),
			{},
			{},
			{},
			{},
			{new Checkbox2D(
			new Text2D(L"Use Wireframe", 10, 0, 1, 21, glm::vec4(1.f, 1.f, 1.f, 1.f), 1,false),
		    new Button2D(
		    new ImageTextPair2D(nullptr,new Rectangle2D(0, 0, 18, 18, 0, 0, 2, glm::vec4(1.f), glm::vec4(1.f)),glm::ivec2(0),0),
		    new Rectangle2D(0, 100, 24, 24, 4, 3, -1, glm::vec4(0.25f,0.51f,1.f,1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
		    glm::vec4(0.45f, 0.71f, 1.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 1.f, 0.f ,1.f), glm::vec4(1.f, 1.f, 0.f, 1.f),1,3,L"Button"),300),
					new Checkbox2D(
			new Text2D(L"Display Group Area(s)", 10, 27, 1, 21, glm::vec4(1.f, 1.f, 1.f, 1.f), 1,false),
			new Button2D(
			new ImageTextPair2D(nullptr,new Rectangle2D(0, 0, 18, 18, 0, 0, 2, glm::vec4(1.f), glm::vec4(1.f)),glm::ivec2(0),0),
			new Rectangle2D(0, 100, 24, 24, 4, 3, -1, glm::vec4(0.25f,0.51f,1.f,1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
			glm::vec4(0.45f, 0.71f, 1.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 1.f, 0.f ,1.f), glm::vec4(1.f, 1.f, 0.f, 1.f),1,3,L"Button"),300),
					new Checkbox2D(
			new Text2D(L"Display Coordinate Lines 4D", 10, 54, 1, 21, glm::vec4(1.f, 1.f, 1.f, 1.f), 1,false),
			new Button2D(
			new ImageTextPair2D(nullptr,new Rectangle2D(0, 0, 18, 18, 0, 0, 2, glm::vec4(1.f), glm::vec4(1.f)),glm::ivec2(0),0),
			new Rectangle2D(0, 100, 24, 24, 4, 3, -1, glm::vec4(0.25f,0.51f,1.f,1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
			glm::vec4(0.45f, 0.71f, 1.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 1.f, 0.f ,1.f), glm::vec4(1.f, 1.f, 0.f, 1.f),1,3,L"Button"),300),
					new Checkbox2D(
			new Text2D(L"Display Trails 4D", 10, 81, 1, 21, glm::vec4(1.f, 1.f, 1.f, 1.f), 1,false),
			new Button2D(
			new ImageTextPair2D(nullptr,new Rectangle2D(0, 0, 18, 18, 0, 0, 2, glm::vec4(1.f), glm::vec4(1.f)),glm::ivec2(0),0),
			new Rectangle2D(0, 100, 24, 24, 4, 3, -1, glm::vec4(0.25f,0.51f,1.f,1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
			glm::vec4(0.45f, 0.71f, 1.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 1.f, 0.f ,1.f), glm::vec4(1.f, 1.f, 0.f, 1.f),1,3,L"Button"),300),
					new Checkbox2D(
			new Text2D(L"Display Joint Lines 4D", 10, 108, 1, 21, glm::vec4(1.f, 1.f, 1.f, 1.f), 1,false),
			new Button2D(
			new ImageTextPair2D(nullptr,new Rectangle2D(0, 0, 18, 18, 0, 0, 2, glm::vec4(1.f), glm::vec4(1.f)),glm::ivec2(0),0),
			new Rectangle2D(0, 100, 24, 24, 4, 3, -1, glm::vec4(0.25f,0.51f,1.f,1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
			glm::vec4(0.45f, 0.71f, 1.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 1.f, 0.f ,1.f), glm::vec4(1.f, 1.f, 0.f, 1.f),1,3,L"Button"),300)},
			{},
			{new DropDown2D(
			new Text2D(L"Trail Fade Type", 10, 135, 1, 21, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
			new Button2D(
			new ImageTextPair2D(new Text2D(L"0123456789x", 0, 0, 1, 20, glm::vec4(1.f, 1.f, 1.f, 1.f), 1,false),nullptr,glm::ivec2(0),12),
			new Rectangle2D(0, 100, 200, 24, 4, 3, -1, glm::vec4(0.25f,0.51f,1.f,1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
			glm::vec4(0.45f, 0.71f, 1.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 1.f, 0.f ,1.f), glm::vec4(1.f, 1.f, 0.f, 1.f),1,3,L"Button"),
			new Rectangle2D(600, 100, 200, 24, 4, 3, -1, glm::vec4(0.25f,0.51f,1.f,1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
			new Button2D(
			new ImageTextPair2D(new Text2D(L"0123456789x", 0, 0, 1, 20, glm::vec4(1.f, 1.f, 1.f, 1.f), 1,false),nullptr,glm::ivec2(0),12),
			new Rectangle2D(0, 0, 250, 24, 0, 3, -1, glm::vec4(0.25f,0.51f,1.f,0.f), glm::vec4(1.f, 1.f, 1.f, 0.f)),
			glm::vec4(0.45f, 0.71f, 1.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 1.f, 0.f ,0.f), glm::vec4(1.f, 1.f, 0.f, 0.f),1,3,L"Button"),
			{ L"Forget", L"Linear", L"Invarible"},0,300
		)},
			{}
		)})
			}) },
		1
	));
	//levels 3
	this->canvas2d.push_back(new Canvas2D(
		{},
		{},
		{},
		{ new Button2D(
		new ImageTextPair2D(new Text2D(L"Level 1", 0, 0, 1, 24, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false), nullptr, glm::ivec2(0), 0),
		new Rectangle2D(0, 0, 200, 24, 4, 3, -1, glm::vec4(0.25f, 0.51f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
		glm::vec4(0.45f, 0.71f, 1.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 1.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 0.f, 1.f), 0, 0, L"Button"),
		new Button2D(
		new ImageTextPair2D(new Text2D(L"Level 2", 0, 0, 1, 24, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false), nullptr, glm::ivec2(0), 0),
		new Rectangle2D(0, 50, 200, 24, 4, 3, -1, glm::vec4(0.25f, 0.51f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
		glm::vec4(0.45f, 0.71f, 1.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 1.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 0.f, 1.f), 0, 0, L"Button"),
		new Button2D(
		new ImageTextPair2D(new Text2D(L"Level 3", 0, 0, 1, 24, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false), nullptr, glm::ivec2(0), 0),
		new Rectangle2D(0, 100, 200, 24, 4, 3, -1, glm::vec4(0.25f, 0.51f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
		glm::vec4(0.45f, 0.71f, 1.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 1.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 0.f, 1.f), 0, 0, L"Button"),
		new Button2D(
		new ImageTextPair2D(new Text2D(L"Level 4", 0, 0, 1, 24, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false), nullptr, glm::ivec2(0), 0),
		new Rectangle2D(0, 150, 200, 24, 4, 3, -1, glm::vec4(0.25f, 0.51f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
		glm::vec4(0.45f, 0.71f, 1.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 1.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 0.f, 1.f), 0, 0, L"Button"),
		new Button2D(
		new ImageTextPair2D(new Text2D(L"Level 5", 0, 0, 1, 24, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false), nullptr, glm::ivec2(0), 0),
		new Rectangle2D(0, 200, 200, 24, 4, 3, -1, glm::vec4(0.25f, 0.51f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
		glm::vec4(0.45f, 0.71f, 1.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 1.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 0.f, 1.f), 0, 0, L"Button"),
		new Button2D(
		new ImageTextPair2D(new Text2D(L"Level 6", 0, 0, 1, 24, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false), nullptr, glm::ivec2(0), 0),
		new Rectangle2D(0, 250, 200, 24, 4, 3, -1, glm::vec4(0.25f, 0.51f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
		glm::vec4(0.45f, 0.71f, 1.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 1.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 0.f, 1.f), 0, 0, L"Button"),
		new Button2D(
		new ImageTextPair2D(new Text2D(L"Back To Title", 0, 0, 1, 24, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false), nullptr, glm::ivec2(0), 0),
		new Rectangle2D(0, 300, 200, 24, 4, 3, -1, glm::vec4(0.25f, 0.51f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
		glm::vec4(0.45f, 0.71f, 1.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 1.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 0.f, 1.f), 0, 0, L"Button") },
		{},
		{},
		{},
		{},
		{},
		{},
		1
	));
	//exit 4
	this->canvas2d.push_back(new Canvas2D(
		{ new Text2D(L"Game Menu", 960, 400, 4, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 0, false) },
		{},
		{},
		{ new Button2D(
		new ImageTextPair2D(new Text2D(L"Back To Game", 0, 0, 1, 24, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false), nullptr, glm::ivec2(0), 0),
		new Rectangle2D(860, 500, 200, 24, 4, 3, -1, glm::vec4(0.25f, 0.51f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
		glm::vec4(0.45f, 0.71f, 1.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 1.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 0.f, 1.f), 0, 0, L"Button"),
		new Button2D(
		new ImageTextPair2D(new Text2D(L"Quit To Title", 0, 0, 1, 24, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false), nullptr, glm::ivec2(0), 0),
		new Rectangle2D(860, 600, 200, 24, 4, 3, -1, glm::vec4(0.25f, 0.51f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
		glm::vec4(0.45f, 0.71f, 1.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 1.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 0.f, 1.f), 0, 0, L"Button") },
		{},
		{},
		{},
		{},
		{},
		{},
		0
	));
	//informations 5
	this->canvas2d.push_back(new Canvas2D(
		{ new Text2D(L"(%.1f FPS) %.3f ms/frame Application average 0123456789.", 0, 0, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"Screen:", 0, 27, 1, 18, glm::vec4(0.f, 1.f, 0.f, 1.f), 1, true),
		new Text2D(L"%1i px Frame buffer width %1i px Frame buffer height 0123456789.", 0, 54, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"Full mode Windowed mode", 0, 81, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"Camera:", 0, 108, 1, 18, glm::vec4(0.f, 1.f, 0.f, 1.f), 1, true),
		new Text2D(L"(%.1f x %.1f y %.1f z %.1f w) m Position -0123456789.", 0, 135, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"(%.1f xy %.1f xz %.1f xw %.1f yz %.1f yw %.1f zw) ° Rotation -0123456789.", 0, 162, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"(%.1f x %.1f y %.1f z %.1f w) %.1f m/s Speed -0123456789.", 0, 189, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"Load amount:", 0, 216, 1, 18, glm::vec4(0.f, 1.f, 0.f, 1.f), 1, true),
		new Text2D(L"%1i Group(s) Had %1i Group(s) Loaded %1i Object(s) Loaded 0123456789.", 0, 243, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"%1i Object(s) %1i Rigid Body(s) %1i Light(s) 0123456789.", 0, 270, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"%1i Sticks(s) %1i Spring(s) %1i Hinge(s) 0123456789.", 0, 297, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"%1i Particle(s) 0123456789.", 0, 324, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"%1i Displacement(s) %1i Floating(s) %1i Rotating(s) Animation 0123456789.", 0, 351, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"Load distance:", 0, 378, 1, 18, glm::vec4(0.f, 1.f, 0.f, 1.f), 1, true),
		new Text2D(L"(%1i m) Block (%1i m) Object 0123456789.", 0, 405, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"Glfw version:", 0, 432, 1, 18, glm::vec4(0.f, 1.f, 0.f, 1.f), 1, true),
		new Text2D(L"%1i Major %1i Minor 0123456789.", 0, 459, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"Spacetime:", 0, 486, 1, 18, glm::vec4(0.f, 1.f, 0.f, 1.f), 1, true),
		new Text2D(L"level %1i 0123456789.", 0, 513, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"%.1f s World Time 0123456789.", 0, 540, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"%.1f s Play Time 0123456789.", 0, 567, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		        
		new Text2D(L"Controls:", 0, 594, 1, 18, glm::vec4(0.f, 1.f, 0.f, 1.f), 1, true),
		new Text2D(L"Press W/S/A/D/R/F: players move forward, backward, left, right, ana, and kata", 0, 621, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"Space: jump", 0, 648, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"Double press Space: fly or land", 0, 675, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"Double press W: run", 0, 702, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"Move the mouse: move the player's perspective within a three-dimensional plane", 0, 729, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"Left click on the mouse: move the player's perspective and move the 3D section", 0, 756, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"In control mode", 0, 783, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"Press Right click :drag an object", 0, 810, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"Left and right mouse buttons :throw objects", 0, 837, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"In other modes", 0, 864, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"Right click on the mouse :execute the corresponding behavior", 0, 891, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"I: turn on or off the UI", 0, 918, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"C: Turn on or off the world coordinate system lines", 0, 945, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"G: Show or turn off wireframe", 0, 972, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"Ctrl: Lift up the construction site", 0, 999, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"F2:Captures the window (RGB) and save the image", 960, 0, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"Delete: delete the half build joint or delete objects in the selection area", 960, 27, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"M/N: Zoom in and out of perspective", 960, 54, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false),
		new Text2D(L"1/2/3/4/5/6 or Mouse wheel: Switching behavior mode", 960, 81, 1, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false)
		},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		{},
		1
	));
	//game over 6
	this->canvas2d.push_back(new Canvas2D(
		{ new Text2D(L"Game Over", 960, 400, 4, 18, glm::vec4(1.f, 1.f, 1.f, 1.f), 0, false) },
		{},
		{},
		{ new Button2D(
		new ImageTextPair2D(new Text2D(L"Restart", 0, 0, 1, 24, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false), nullptr, glm::ivec2(0), 0),
		new Rectangle2D(860, 500, 200, 24, 4, 3, -1, glm::vec4(0.25f, 0.51f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
		glm::vec4(0.45f, 0.71f, 1.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 1.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 0.f, 1.f), 0, 0, L"Button"),
		new Button2D(
		new ImageTextPair2D(new Text2D(L"Quit To Title", 0, 0, 1, 24, glm::vec4(1.f, 1.f, 1.f, 1.f), 1, false), nullptr, glm::ivec2(0), 0),
		new Rectangle2D(860, 600, 200, 24, 4, 3, -1, glm::vec4(0.25f, 0.51f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f)),
		glm::vec4(0.45f, 0.71f, 1.f, 1.f), glm::vec4(1.f), glm::vec4(0.f, 1.f, 0.f, 1.f), glm::vec4(1.f, 1.f, 0.f, 1.f), 0, 0, L"Button") },
		{},
		{},
		{},
		{},
		{},
		{},
		0
    ));
	tip2d = new Lable2D(new Rectangle2D(600, 100, 200, 24, 4, 3, -1, glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec4(0.25f, 0.25f, 0.25f, 1.f)), new Text2D(L"Texture filter", 850, 100, 1, 20, glm::vec4(0.25f, 0.25f, 0.25f, 1.f), 1, false));
	this->demoObjects4d = new Demo4D();
	this->demos4d.push_back(new Demo4D(new Wall4D("Hypercube", Hypercube(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, BOX4D, DEMOD4)));
	this->demos4d.push_back(new Demo4D(new Wall4D("Hypersphere", Hypersphere(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, SPHERE4D, DEMOD4)));
	this->demos4d.push_back(new Demo4D(new Wall4D("Hypercapsule", Hypercapsule(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4d.push_back(new Demo4D(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4d.push_back(new Demo4D(new Wall4D("Hypercone", Hypercone(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4d.push_back(new Demo4D(new Wall4D("Hyperpot", Hyperpot(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4d.push_back(new Demo4D(new Wall4D("TriPrism", TriPrism(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4d.push_back(new Demo4D(new Wall4D("Hyperslope", Hyperslope(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4d.push_back(new Demo4D(new Wall4D("DoubleQuads4d", DoubleQuads4d(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4d.push_back(new Demo4D(new Wall4D("Pentachoron", Pentachoron(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4d.push_back(new Demo4D(new Wall4D("Pyramid4D", Pyramid4D(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4d.push_back(new Demo4D(new Wall4D("Hexadecachoron", Hexadecachoron(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4d.push_back(new Demo4D(new Wall4D("Hexacosichoron", Hexacosichoron(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));

	this->demos4d.push_back(new Demo4D(new RigidBody4D("Hypercube", Hypercube(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, BOX4D, DEMOD4)));
	this->demos4d.push_back(new Demo4D(new RigidBody4D("Hypersphere", Hypersphere(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, SPHERE4D, DEMOD4)));
	this->demos4d.push_back(new Demo4D(new RigidBody4D("Hypercapsule", Hypercapsule(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4d.push_back(new Demo4D(new RigidBody4D("Hypercylinder", Hypercylinder(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4d.push_back(new Demo4D(new RigidBody4D("Hypercone", Hypercone(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4d.push_back(new Demo4D(new RigidBody4D("Hyperpot", Hyperpot(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4d.push_back(new Demo4D(new RigidBody4D("TriPrism", TriPrism(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4d.push_back(new Demo4D(new RigidBody4D("Hyperslope", Hyperslope(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4d.push_back(new Demo4D(new RigidBody4D("DoubleQuads4d", DoubleQuads4d(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4d.push_back(new Demo4D(new RigidBody4D("Pentachoron", Pentachoron(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4d.push_back(new Demo4D(new RigidBody4D("Pyramid4D", Pyramid4D(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4d.push_back(new Demo4D(new RigidBody4D("Hexadecachoron", Hexadecachoron(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4d.push_back(new Demo4D(new RigidBody4D("Hexacosichoron", Hexacosichoron(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	std::vector<Wall4D*> poolTable;
	generate_pool_table4D(glm::vec4(0.f), glm::vec4(1.27f, 1.27f, 2.54f, 1.27f), 1.f, true, WOODX, true, GRASS, true, WOODY, &poolTable, DEMOD4);
	this->demos4d.push_back(new Demo4D(poolTable));
	std::vector<RigidBody4D*> billiard4D;
	generate_billiard4D(glm::vec4(0.f), glm::vec4(),alg::bivec4(),this->buildTexture, &billiard4D, this->isGravity, glm::vec4(1.f),glm::vec4(1.f,1.f,1.f,0.f), DEMOD4);
	this->demos4d.push_back(new Demo4D(billiard4D));
	std::vector<Wall4D*> dynamite4D;
	generate_dynamite4D(glm::vec4(0.f), WHITECONCRETE, nullptr, &dynamite4D, nullptr, DEMOD4);
	this->demos4d.push_back(new Demo4D(dynamite4D));
	std::vector<RigidBody4D*> dynamite4D2;
	generate_dynamite4D(glm::vec4(0.f), this->initialVelocity, this->initialAngularVelocity, WHITECONCRETE, &dynamite4D2, nullptr, this->isGravity, DEMOD4);
	this->demos4d.push_back(new Demo4D(dynamite4D2));
	this->demos4d.push_back(new Demo4D(new Stick4D(glm::vec4(0.f), 0, { 0, false }, this->stickLength, WHITECONCRETE, this->buildColor, DEMOD4)));
	this->demos4d.push_back(new Demo4D(new Spring4D(glm::vec4(0.f), 0, { 0, false }, this->springLength, this->springStrength, STONE, this->buildColor, DEMOD4)));
	this->demos4d.push_back(new Demo4D(new PointLight4D(PARTICLE1, glm::vec4(0.f), 0, 0.f, glm::vec3(117.f, 181.f, 59.f) / 256.f, 0.f)));
	this->groupAreaHypercube = new Wall4D("Hypercube", Hypercube(glm::vec4(64.f)/2.f), glm::vec4(0.f), alg::bivec4(), glm::vec4(64.f), 0, 0, false, GRID2, glm::vec4(171.f/256.f, 222.f/256.f, 105.f/256.f, 0.25f), glm::vec4(0), NONE, EMITD4);
}

void Game::startDefault()
{
	this->isRenderCoordinate4d = false;
	this->camera.update_perspective_mat(60.f, static_cast<float>(this->framebufferWidth) / this->framebufferHeight, 0.1f);
	this->blockLoadDistance = 64;
	this->objectLoadDistance = 0;
	this->isTrail4d = true;
	this->trailFadeType = LINEAR;
	this->shaders[TRAILD4]->use();
	this->shaders[TRAILD4]->set1i(LINEAR, "trailFadeType");
	this->isJointLine4d = true;
	this->isFramework = true;
	this->frameworkProjectionType = 1;
	this->isShowingGroupArea = false;
	this->projectionScaler = 0.283f;
	this->shaders[FRAMED4]->use();
	this->shaders[FRAMED4]->set1i(1, "projectionType");
	this->shaders[FRAMED4]->set1f(this->projectionScaler, "projectionScaler");
	this->vsync = 1;
	glfwSwapInterval(this->vsync);
	glfwSetWindowMonitor(this->window, NULL, 0, 45, this->WINDOW_WIDTH, this->WINDOW_HEIGHT, GLFW_DONT_CARE);
	this->updateProjectMat(this->framebufferWidth, this->framebufferHeight);
	this->isFullscreen = false;
	this->isFog = false;
	this->fogDensity = 1.f;
	this->shaders[WALLD4]->use();
	this->shaders[WALLD4]->set1i(this->isFog, "isFog");
	this->shaders[WALLD4]->set1f(this->fogDensity, "fogDensity");
	this->shaders[EMITD4]->use();
	this->shaders[EMITD4]->set1i(this->isFog, "isFog");
	this->shaders[EMITD4]->set1f(this->fogDensity, "fogDensity");
	this->shaders[TERRAIND4]->use();
	this->shaders[TERRAIND4]->set1i(this->isFog, "isFog");
	this->shaders[TERRAIND4]->set1f(this->fogDensity, "fogDensity");
	this->shaders[WATERD4]->use();
	this->shaders[WATERD4]->set1i(this->isFog, "isFog");
	this->shaders[WATERD4]->set1f(this->fogDensity, "fogDensity");
	this->cMoveForward = 'W';this->iMoveForward = GLFW_KEY_W;this->cMoveBackward = 'S';this->iMoveBackward = GLFW_KEY_S;
	this->cMoveLeft = 'A';this->iMoveLeft = GLFW_KEY_A;this->cMoveRight = 'D';this->iMoveRight = GLFW_KEY_D;
	this->cMoveAna = 'R';this->iMoveAna = GLFW_KEY_R;this->cMoveKata = 'F';this->iMoveKata = GLFW_KEY_F;
	this->cTurnDirection = 'T'; this->iTurnDirection = GLFW_KEY_T;
	this->cSwitchCoordinate = 'C';this->iSwitchCoordinate = GLFW_KEY_C;cSwitchInventory='I'; iSwitchInventory = GLFW_KEY_I;
	this->cSwitchFrame = 'G'; this->iSwitchFrame = GLFW_KEY_G;
	this->cFovIn = 'M';this->iFovIn= GLFW_KEY_M;this->cFovOut = 'N';this->iFovOut = GLFW_KEY_N;
	this->isCloud = true;
	this->isACES = false;
	this->adaptedLum = 1.f;
	this->isSkyBoxFog = true;
	this->isHDR = false;
	this->isBloom = true;
	this->bloomMultiplier = 1.f;
	this->shaderHDRs[BLOOM]->use();
	this->shaderHDRs[BLOOM]->set1f(this->bloomMultiplier, "bloomMultiplier");
	this->isAutoExposure = false;
	this->exposure2 = 1.f;
	this->exposureSpeed = 1.f;
	this->exposureMultiplier = 1.f;
	this->shaders[WALLD4]->use();
	this->shaders[WALLD4]->set1i(this->isCloud, "isCloud");
	this->shaders[WALLD4]->set1i(this->isACES, "isACES");
	this->shaders[WALLD4]->set1f(this->adaptedLum, "adaptedLum");
	this->shaders[WALLD4]->set1i(this->isSkyBoxFog, "isSkyBoxFog");
	this->shaders[SKY_BOXD4]->use();
	this->shaders[SKY_BOXD4]->set1i(this->isCloud, "isCloud");
	this->shaders[SKY_BOXD4]->set1i(this->isACES, "isACES");
	this->shaders[SKY_BOXD4]->set1f(this->adaptedLum, "adaptedLum");
	this->shaders[SKY_BOXD4]->set1i(this->isSkyBoxFog, "isSkyBoxFog");
	this->shaders[WATERD4]->use();
	this->shaders[WATERD4]->set1i(this->isCloud, "isCloud");
	this->shaders[WATERD4]->set1i(this->isACES, "isACES");
	this->shaders[WATERD4]->set1f(this->adaptedLum, "adaptedLum");
	this->shaders[WATERD4]->set1i(this->isSkyBoxFog, "isSkyBoxFog");
	this->shaders[EMITD4]->use();
	this->shaders[EMITD4]->set1i(this->isACES, "isACES");
	this->shaders[EMITD4]->set1f(this->adaptedLum, "adaptedLum");
	this->shaders[TERRAIND4]->use();
	this->shaders[TERRAIND4]->set1i(this->isACES, "isACES");
	this->shaders[TERRAIND4]->set1f(this->adaptedLum, "adaptedLum");
	this->filterType = 3;
	for (Texture* i : this->textures)i->set_filter(this->filterType);
	for (Texture* i : this->pointerTexs)i->set_filter(this->filterType);
	for (HDRTexture* i : this->hDRTextures)i->set_filter(this->filterType);
	for (HDRTexture* i : this->bloomExpandMaps)i->set_filter(this->filterType);
	for (Texture3D* i : this->textures3d)i->set_filter(this->filterType);
	for (Texture3D* i : this->particleTexs3d)i->set_filter(this->filterType);
	for (Texture3D* i : this->wallTexs3d)i->set_filter(this->filterType);
	for (Texture3D* i : this->groundTexs3d)i->set_filter(this->filterType);
	textureFilterText = "Mag:Linear/Min:Linear Mipmap Linear";
	this->soundVolume=50.f;
	this->soundPitch = 1.f;
	for (Sound* sound : this->sounds)
	{
		sound->set_volume(this->soundVolume);
		sound->set_pitch(this->soundPitch);
	}
	this->isPlayingMusic = true;
	for (Music* music : this->musics){music->stop();}
	this->musics[2]->play();
	this->musicVolume=50.f;
	this->musicPitch = 0.707f;//0.725f//0.53f//0.51f//0.47755f
	for (Music* music : this->musics)
	{
		music->set_volume(this->musicVolume);
		music->set_pitch(this->musicPitch);
	}
}

void Game::startInputs() 
{
	for (size_t i(0);i < 14;i++) {
		this->inputs.push_back(new Input());
	}
}

void Game::firstUpdate() 
{
	this->isFixedTime = fixedUpdate::is_fixed_update(this->dt, 1.f / 60.f);
	if (this->isFixedTime) fixedUpdate::fixedCurTime += 1.f / 60.f;
}

void Game::updateProjectMat(int fbW, int fbH) {
	//Update framebuffer size and projection matrix
	this->framebufferWidth = fbW, this->framebufferHeight = fbH;
	glfwGetWindowPos(this->window, &this->windowPosX, &this->windowPosX);
	this->hDRTextures[0]->set_texture_size(this->framebufferWidth, this->framebufferHeight);
	this->hDRTextures[1]->set_texture_size(this->framebufferWidth/3, this->framebufferHeight/3);
	for (size_t i(0); i < 11; i++){
		this->bloomExpandMaps[i]->set_texture_size(this->framebufferWidth / 3, this->framebufferHeight / 3);
	}
	this->camera.update_perspective_mat(this->camera.fov, static_cast<float>(this->framebufferWidth) / this->framebufferHeight, this->camera.nearPlane);
	//shaders[OBJ]->use();
	//shaders[OBJ]->set_mat4fv(this->projectionMat, "projectionMat");
	this->shaders[SKY_BOXD4]->use();
	this->shaders[SKY_BOXD4]->set_mat4fv(this->camera.projectionMat, "projectionMat");
	this->shaders[WALLD4]->use();
	this->shaders[WALLD4]->set_mat4fv(this->camera.projectionMat, "projectionMat");
	this->shaders[DEMOD4]->use();
	this->shaders[DEMOD4]->set_mat4fv(this->camera.projectionMat, "projectionMat");
	this->shaders[EMITD4]->use();
	this->shaders[EMITD4]->set_mat4fv(this->camera.projectionMat, "projectionMat");
	this->shaders[TERRAIND4]->use();
	this->shaders[TERRAIND4]->set_mat4fv(this->camera.projectionMat, "projectionMat");
	this->shaders[WATERD4]->use();
	this->shaders[WATERD4]->set_mat4fv(this->camera.projectionMat, "projectionMat");
	this->shaders[PARTICLED4]->use();
	this->shaders[PARTICLED4]->set_mat4fv(this->camera.projectionMat, "projectionMat");
	this->shaders[LIGHT_PARTICLED4]->use();
	this->shaders[LIGHT_PARTICLED4]->set_mat4fv(this->camera.projectionMat, "projectionMat");
	this->shaders[COORDNATED4]->use();
	this->shaders[COORDNATED4]->set_mat4fv(this->camera.projectionMat, "projectionMat");
	this->shaders[TRAILD4]->use();
	this->shaders[TRAILD4]->set_mat4fv(this->camera.projectionMat, "projectionMat");
	this->shaders[JOINT_LINED4]->use();
	this->shaders[JOINT_LINED4]->set_mat4fv(this->camera.projectionMat, "projectionMat");
	this->shaders[FRAMED4]->use();
	this->shaders[FRAMED4]->set_mat4fv(this->camera.projectionMat, "projectionMat");
	this->shaders[LIGHT_FRAMED4]->use();
	this->shaders[LIGHT_FRAMED4]->set_mat4fv(this->camera.projectionMat, "projectionMat");
	this->shaders[AMBIENT_OCCLUSION]->use();
	this->shaders[AMBIENT_OCCLUSION]->set_mat4fv(this->camera.projectionMat, "projectionMat");

	this->ratio = 1080.f / (float)this->framebufferHeight;
	glm::vec2 canvasSize = glm::vec2((float)this->framebufferWidth* this->ratio, (float)this->framebufferHeight* this->ratio);
	this->shaders[TEXT]->use();
	this->shaders[TEXT]->set_vec2f(canvasSize, "screenScale");
	this->shaders[RECTANGLE]->use();
	this->shaders[RECTANGLE]->set_vec2f(canvasSize, "screenScale");
}

void Game::textinputs_add(unsigned int c)
{
	this->canvas2d[SETTINGS]->input_text(c);
}

void Game::textinputs_delete(int key, int action)
{
	if (action != 0)
	{
		switch (key)
		{
		case(259): { this->canvas2d[SETTINGS]->delete_text(true); break; }
		case(261): { this->canvas2d[SETTINGS]->delete_text(false); break; }
		case(262): { this->canvas2d[SETTINGS]->move_cursor(true); break; }
		case(263): { this->canvas2d[SETTINGS]->move_cursor(false); break; }
		}
	}
}

void Game::updateUniforms()
{
	//Update view matrix (camera)

	//this->shaders[OBJ]->use();
	//this->shaders[OBJ]->set_vec3f(this->camera.position4d, "cameraPos");

	this->shaders[SKY_BOXD4]->use();
	this->shaders[SKY_BOXD4]->set_mat4fv(this->camera.viewMat4D, "viewMat");
	this->shaders[SKY_BOXD4]->set_vec4f(this->camera.position4d, "cameraPos");
	this->shaders[SKY_BOXD4]->set1f(this->curTime, "iTime");

	this->shaders[WALLD4]->use();
	this->shaders[WALLD4]->set_mat4fv(this->camera.viewMat4D, "viewMat");
	this->shaders[WALLD4]->set_vec4f(this->camera.position4d, "cameraPos");
	this->shaders[WALLD4]->set1f(this->curTime, "iTime");

	if (this->mode == BUILDING) {
		this->shaders[DEMOD4]->use();
		this->shaders[DEMOD4]->set_mat4fv(this->camera.viewMat4D, "viewMat");
		this->shaders[DEMOD4]->set_vec4f(this->camera.position4d, "cameraPos");
		this->shaders[DEMOD4]->set1f(this->curTime, "iTime");
	}

	this->shaders[EMITD4]->use();
	this->shaders[EMITD4]->set_mat4fv(this->camera.viewMat4D, "viewMat");
	this->shaders[EMITD4]->set_vec4f(this->camera.position4d, "cameraPos");

	this->shaders[TERRAIND4]->use();
	this->shaders[TERRAIND4]->set_mat4fv(this->camera.viewMat4D, "viewMat");
	this->shaders[TERRAIND4]->set_vec4f(this->camera.position4d, "cameraPos");
	this->shaders[TERRAIND4]->set1f(this->curTime, "iTime");

	if (this->waters4d.size() != 0)
	{
		this->shaders[WATERD4]->use();
		this->shaders[WATERD4]->set_mat4fv(this->camera.viewMat4D, "viewMat");
		this->shaders[WATERD4]->set_vec4f(this->camera.position4d, "cameraPos");
		this->shaders[WATERD4]->set1f(this->curTime, "iTime");
	}

	this->shaders[PARTICLED4]->use();
	this->shaders[PARTICLED4]->set_mat4fv(this->camera.viewMat4D, "viewMat");
	this->shaders[PARTICLED4]->set_vec4f(this->camera.position4d, "cameraPos");

	this->shaders[LIGHT_PARTICLED4]->use();
	this->shaders[LIGHT_PARTICLED4]->set_mat4fv(this->camera.viewMat4D, "viewMat");
	this->shaders[LIGHT_PARTICLED4]->set_vec4f(this->camera.position4d, "cameraPos");

	if (this->isRenderCoordinate4d)
	{
		this->shaders[COORDNATED4]->use();
		this->shaders[COORDNATED4]->set_mat4fv(this->camera.viewMat4D, "viewMat");
	}

	this->shaders[TRAILD4]->use();
	this->shaders[TRAILD4]->set_mat4fv(this->camera.viewMat4D, "viewMat");
	this->shaders[TRAILD4]->set_vec4f(this->camera.position4d, "cameraPos");

	this->shaders[JOINT_LINED4]->use();
	this->shaders[JOINT_LINED4]->set_mat4fv(this->camera.viewMat4D, "viewMat");
	this->shaders[JOINT_LINED4]->set_vec4f(this->camera.position4d, "cameraPos");

	if (this->isFramework)
	{
		this->shaders[FRAMED4]->use();
		this->shaders[FRAMED4]->set_mat4fv(this->camera.viewMat4D, "viewMat");
		this->shaders[FRAMED4]->set_vec4f(this->camera.position4d, "cameraPos");

		this->shaders[LIGHT_FRAMED4]->use();
		this->shaders[LIGHT_FRAMED4]->set_mat4fv(this->camera.viewMat4D, "viewMat");
		this->shaders[LIGHT_FRAMED4]->set_vec4f(this->camera.position4d, "cameraPos");
	}
	this->shaders[AMBIENT_OCCLUSION]->use();
	this->shaders[AMBIENT_OCCLUSION]->set_mat4fv(this->camera.viewMat4D, "viewMat");
	this->shaders[AMBIENT_OCCLUSION]->set_vec4f(this->camera.position4d, "cameraPos");
}
void Game::startLines() 
{
	this->coordinate4d = new Coordinate4D();
}

void Game::startGui2()
{
	this->targetIcon = new Image2D(SHOOTING);
}

void Game::startLevel(int level, const char* filePath)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//this->image2d->render(this->textures[this->image2d->textureIndex], this->shader2dShape, glm::vec2((float)this->framebufferHeight / (float)this->framebufferWidth, 1.f));
	glfwSwapBuffers(this->window);
	if (level == 0)
	{
		//glfwSetScrollCallback(this->window, ImGui_ImplGlfw_ScrollCallback);
		glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		isGroundTextureUI = false, isObjectTextureUI = false, this->editMode = false;

		this->pageType = START_MENU;
	}
	else
	{
		this->isCloseUI = true;
		glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		this->firstMouse = !this->firstMouse;

		this->pageType = REGULAR;
	}
	this->hitIndex.isValid = false;
	for (Wall4D* i : this->walls4d)i = nullptr, free(i); this->walls4d.clear();
	for (RigidBody4D* i : this->rigidBodies4d)i = nullptr, free(i); this->rigidBodies4d.clear();
	for (Water4D* i : this->waters4d)i = nullptr, free(i); this->waters4d.clear();
	for (Terrain4D* i : this->terrains4d)i = nullptr, free(i); this->terrains4d.clear();
	for (DynamiteIndex* i : this->dynamiteIndices)i = nullptr, free(i); this->dynamiteIndices.clear();
	for (PointLight4D* i : this->pointLights4d)i = nullptr, free(i); this->pointLights4d.clear();
	for (Stick4D* i : this->sticks4d)i = nullptr, free(i); this->sticks4d.clear();
	for (Spring4D* i : this->springs4d)i = nullptr, free(i); this->springs4d.clear();
	for (std::vector<HingeConstraint4D*> i : this->hingeConstraintsVec) { for (HingeConstraint4D* j : i)j = nullptr, free(j); i.clear(); } this->hingeConstraintsVec.clear();
	for (Shift4D* i : this->shifts4d)i = nullptr, free(i); this->shifts4d.clear();
	for (Float4D* i : this->floats4d)i = nullptr, free(i); this->floats4d.clear();
	for (Rotate4D* i : this->rotates4d)i = nullptr, free(i); this->rotates4d.clear();
	for (OpenDoor4D* i : this->openDoors4d)i = nullptr, free(i); this->openDoors4d.clear();
	for (Emitter4D* i : this->emitters4d)i = nullptr, free(i); this->emitters4d.clear();
	this->collisionsVec.clear();
	for (std::vector<Constraint*> cs : this->constraintsVec) { for (Constraint* c : cs)c = nullptr, free(c); cs.clear(); }this->constraintsVec.clear();
	this->groupIndices.clear();
	this->groupIndices.push_back(0);
	this->startObjects(level, filePath);
	this->camera.update_camera(this->rigidBodies4d[0],0.f);
	this->groupIndices = judge_groups(this->rigidBodies4d, this->groupIndices, this->groups, this->camera.position4d, this->blockLoadDistance);
	judge_objects(this->groupIndices, this->groups, this->walls4d, this->terrains4d, this->camera.position4d, this->camera.forward4D, this->camera.wDir, this->objectLoadDistance);
	update_render_indices(this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d,this->sticks4d,this->springs4d, &this->renderIndices1, &this->renderIndices2, this->camera.position4d);
	sort_render_indices(&this->renderIndices1); sort_render_indices(&this->renderIndices2);
	update_collide_indices(this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d);
	//for (RigidBody4D* r : this->rigidBodies4d) std::cout<<r->rigidBodyIndices.size()<<'\n';
	//for (int i = 0; i < 64; i++) { savedLevelText[i] = ''; }
	//savedLevelText[0]='L', savedLevelText[1] = 'e', savedLevelText[2]='v', savedLevelText[3]='e', savedLevelText[4]='l',savedLevelText[5]= ' ', savedLevelText[6] = (char)(this->level), savedLevelText[7]='-', savedLevelText[8] = '1',
	update_water4d(this->waters4d, this->shaders[WALLD4], this->shaders[EMITD4]);
	update_point_light4d(this->pointLights4d, this->shaders[WALLD4], this->shaders[TERRAIND4], this->shaders[LIGHT_MAPD3]);
	this->shaders[LIGHT_MAPD3]->set_vec4f(this->camera.position4d, "cameraPosShift4D");
	this->lightMap3d->bind_image(0);
	glDispatchCompute(4, 128, 4);
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
	this->shaders[WALLD4]->use();
	this->shaders[WALLD4]->set_vec4f(this->camera.position4d, "cameraPosShift4D");
	this->shaders[TERRAIND4]->use();
	this->shaders[TERRAIND4]->set_vec4f(this->camera.position4d, "cameraPosShift4D");
	this->updateDt();
	phy::timeToSleep = 0.f;
}
void Game::judgeRender()
{
	this->judgetime1 += this->dt;
	this->judgetime3 += this->dt;

	if (this->judgetime1 > 0.13125f ) {
		judge_objects(this->groupIndices, this->groups, this->walls4d, this->terrains4d, this->camera.position4d, this->camera.forward4D, this->camera.wDir, this->objectLoadDistance);
		update_render_indices(this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d, this->sticks4d, this->springs4d, &this->renderIndices1, &this->renderIndices2, this->camera.position4d);
		sort_render_indices(&this->renderIndices1); sort_render_indices(&this->renderIndices2);
		this->judgetime1 = 0.f;
	}

	if (this->judgetime3 > 0.3125 * (float)(this->blockLoadDistance)/(length(this->camera.limitedVelocity4D)+0.04f)){
		this->groupIndices = judge_groups(this->rigidBodies4d, this->groupIndices, this->groups, this->camera.position4d, this->blockLoadDistance);
		update_render_indices(this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d, this->sticks4d, this->springs4d, &this->renderIndices1, &this->renderIndices2, this->camera.position4d);
		sort_render_indices(&this->renderIndices1); sort_render_indices(&this->renderIndices2);
		if (this->pointLights4d.size() > 0)
		{
			glm::vec4 cameraPosShift4D0 = ceil(this->camera.position4d / glm::vec4(64.f) - glm::vec4(0.5f)) * 64.f;
			if (this->cameraPosShift4D != cameraPosShift4D0)
			{
				this->shaders[LIGHT_MAPD3]->use();
				this->shaders[LIGHT_MAPD3]->set_vec4f(this->camera.position4d, "cameraPosShift4D");
				this->lightMap3d->bind_image(0);
				glDispatchCompute(4, 128, 4);
				glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
				this->shaders[WALLD4]->use();
				this->shaders[WALLD4]->set_vec4f(this->camera.position4d, "cameraPosShift4D");
				this->shaders[TERRAIND4]->use();
				this->shaders[TERRAIND4]->set_vec4f(this->camera.position4d, "cameraPosShift4D");
				this->cameraPosShift4D = cameraPosShift4D0;
			}
		}
		this->judgetime3 = 0.f;
	}
}

void::Game::updateLights()
{
	this->directionLight4d->update_light4D(1200.f, this->worldTime);
	this->directionLight4d->set_light4D_property(this->shaders[WALLD4]);
	this->directionLight4d->set_light4D_property(this->shaders[TERRAIND4]);
	this->directionLight4d->set_light4D_property(this->shaders[WATERD4]);
	this->directionLight4d->set_light4D_property(this->shaders[EMITD4]);
	this->directionLight4d->set_light4D_property(this->shaders[SKY_BOXD4]);
}

void::Game::update_scroll_input(int mode,int yOffset)
{
	if (this->pageType == REGULAR)
	{
		//if (yOffset != 0){
		if (mode != -1) {
			this->mode = mode;
		}
		else {
			int modeAfter(this->mode + yOffset);
			if (modeAfter >= SELECTING && modeAfter <= AREA_DELETING) {
				this->mode = modeAfter;
			}
			else {
				if (modeAfter < SELECTING) {
					this->mode = AREA_DELETING;
				}
				else {
					this->mode = SELECTING;
				}
			}
		}
		this->targetIcon->textureIndex = this->mode;
		if (this->mode == AREA_DELETING) this->deleteMap3d->unselectArea();
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
		this->hitIndex.isValid = false;
	}
	this->canvas2d[SETTINGS]->scroll(yOffset);
}

//Constructors
Game::Game(
	const char* title,
	const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
	const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
	bool resizable
)
	:
	WINDOW_WIDTH(WINDOW_WIDTH),
	WINDOW_HEIGHT(WINDOW_HEIGHT),
	GL_VERSION_MAJOR(GL_VERSION_MAJOR),
	GL_VERSION_MINOR(GL_VERSION_MINOR),
	camera(60.f, static_cast<float>(this->framebufferWidth) / this->framebufferHeight, 0.1f)
{
	//Init variables
	this->window = nullptr;
	this->framebufferWidth = this->WINDOW_WIDTH;
	this->framebufferHeight = this->WINDOW_HEIGHT;

	this->dt = 0.f;
	this->curTime = 0.f;
	this->lastTime = 0.f;
	this->worldTime = 0.f;
	this->judgetime1 = 0.f;
	this->judgetime2 = 0.f;
	this->judgetime3 = 0.f;

	this->lastMouseX = 0.0f;
	this->lastMouseY = 0.0f;
	this->mouseX = 0.0f;
	this->mouseY = 0.0f;
	this->mouseOffsetX = 0.0f;
	this->mouseOffsetY = 0.0f;
	this->firstMouse = true;
	this->ratio = 1.f;

	this->isDebug = false;
	this->level = 0;
	this->paintScale = 5;
	this->mode = SHOOTING;
	this->shootType = 0;
	this->reflectionSteps = 6;
	this->controlType = DRAG;
	this->isHardPainting = false;
	this->isSphericalPainting = true;
	this->paintType0 = 0;
	this->paintType = 0;
	this->penetrationCount = 1;
	this->hittingPos4D = glm::vec4(0.f);
	this->hitIndex = { 0, false };
	this->hitObject4D = nullptr;
	this->hitPosNear = glm::vec4(0.f);
	this->hitPosToBody = glm::vec4(0);
	this->hitNormal = glm::vec4(0);
	this->cameraPosShift4D = glm::vec4(0, 64, 0, 0);

	this->filterType = 3;

	this->buildMode = BUILD_OBJECT;
	this->isFindPoint = false;
	this->isRigidBody = true;
	this->buildTag = "4D-Object";
	this->stickLength=3.f;
	this->springLength=3.f;
	this->springStrength=10.f;
	this->buildDistance = glm::vec2(0.5f, 0.25f);
	this->buildOffset = glm::vec4(0.f);
	this->buildTexture = DEFAULTCHESSBOARD;
	this->buildShader = WALLD4;
	this->isSpecular = true;
	this->buildColor = glm::vec4(1.f);
	this->buildMetalColor = glm::vec4(1.f, 1.f, 1.f, 0.f);
	this->isRandomColor = false;
	this->buildScale = glm::vec4(1.f);
	this->buildRotation = alg::bivec4();
	this->initialVelocity = glm::vec4(0.f);
	this->initialAngularVelocity = alg::bivec4();
	this->buildCol=HYPERCUBE;
	this->buildParameter = glm::vec4(1.f, 2.f/3.f, 0.7f, 0.25f);
	this->lightIntensity = 1.f;
	this->lightColor = glm::vec3(1.f);
	this->lightRadius = 10.f;
	this->isGravity = true;
	this->startGLFW();
	this->startWindow(title, resizable);
	this->startGLEW();
	this->startLoad();
	this->startOpenGLOptions();
	this->startTextures();
	this->startSounds();
	this->startShaders();
	this->startDemos();
	this->startMatrices();
	this->startLines();
	this->startGui2();
	this->startDefault();
	this->startInputs();
	this->skybox4d = new Sky_Box4D("Sky4d", Hypercubecol(glm::vec4(1.f)), alg::bivec4(), glm::vec4(100000.f), SKY_BOXD4);
	this->directionLight4d = new DirectionLight4D(PARTICLE1, alg::bivec4(0.f, -90.f), glm::vec3(1.f), 0.925f);
	this->startLevel(this->level, "");
}
//Destructors
Game::~Game()
{
	glfwDestroyWindow(this->window);
	glfwTerminate();
	end_imgui();
	for (Canvas2D* i : this->canvas2d) { delete i; }
	delete tip2d;
	for (Shader* i : this->shaders) {delete i;}
	for (Shader* i : this->shaderHDRs) { delete i; }
	for (Texture* i : this->textures) { delete i;}
	for (Texture* i : this->pointerTexs) { delete i;}
	delete this->deleteMap3d;
	delete this->lightMap3d;
	for (Texture3D* i : this->textures3d) { delete i;}
	for (Texture3D* i : this->particleTexs3d) { delete i;}
	for (Texture3D* i : this->wallTexs3d) { delete i;}
	for (Texture3D* i : this->groundTexs3d) { delete i;}
	for (HDRTexture* i : this->hDRTextures) { delete i; }
	for (HDRTexture* i : this->bloomExpandMaps) { delete i; }
	for (Sound* i : this->sounds) { delete i;}
	for (Music* i : this->musics) { delete i;}
	for (Object* i : this->objects) { delete i;}
	delete this->skybox4d;
	delete this->coordinate4d;
	delete this->targetIcon;
	delete this->demoObjects4d;
	delete this->groupAreaHypercube;
	delete this->hitObject4D;
	for (Demo4D* i : this->demos4d) { delete i;}
	for (JointLine4D* i : this->dragLines4d) { delete i;}
	for (XRay4D* i : this->xRays4d) { delete i; }
	for (Input* i : this->inputs) { delete i;}
	for (Wall4D* i : this->walls4d) { delete i;}
	for (RigidBody4D* i : this->rigidBodies4d) { delete i;}
	for (DynamiteIndex* i : this->dynamiteIndices) { delete i; }
	for (Terrain4D* i : this->terrains4d) { delete i;}
	for (Water4D* i : this->waters4d) { delete i;}
	for (Group* i : this->groups) { delete i;}
	for (Emitter4D* i : this->emitters4d) { delete i;}
	for (std::vector<Constraint*> i : constraintsVec) { for (Constraint* j : i) { delete j; } i.clear(); }
	for (RenderIndex* i : this->renderIndices1) { delete i;}
	for (RenderIndex* i : this->renderIndices2) { delete i;}
	for (PointLight* i : this->pointLights) { delete i;}
	for (DirectionLight* i : this->directionLights) { delete i;}
	for (PointLight4D* i : this->pointLights4d) { delete i;}
	delete this->directionLight4d;
	for (Stick4D* i : this->sticks4d) { delete i;}
	for (Spring4D* i : this->springs4d) { delete i;}
	for (std::vector<HingeConstraint4D*> i : hingeConstraintsVec) { for (HingeConstraint4D* j : i) { delete j; } i.clear(); }
	for (Shift4D* i : this->shifts4d) { delete i;}
	for (Float4D* i : this->floats4d) { delete i;}
	for (Rotate4D* i : this->rotates4d) { delete i;}
	for (OpenDoor4D* i : this->openDoors4d) { delete i; }
}

//Accessor
int Game::getWindowShouldClose()
{
	return glfwWindowShouldClose(this->window);
}

//Modifier
void Game::setWindowShouldClose()
{
	glfwSetWindowShouldClose(this->window, GLFW_TRUE);
}

//Functions
void Game::updateDt()
{
	this->curTime = static_cast<float>(glfwGetTime());
	this->dt = this->curTime - this->lastTime;
	this->lastTime = this->curTime;
}

void::Game::updateTime()
{
	this->updateDt();
	this->worldTime += dt;
}

void Game::updateMouseInput()
{
	if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE) {
		glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);
		if (this->firstMouse)
		{
			this->lastMouseX = this->mouseX, this->lastMouseY = this->mouseY, this->firstMouse = false;
		}
		//Calc offset
		this->mouseOffsetX = this->mouseX - this->lastMouseX;
		this->mouseOffsetY = this->lastMouseY - this->mouseY;
		//Set last X and Y
		this->lastMouseX = this->mouseX, this->lastMouseY = this->mouseY;
		this->firstMouse2 = true;
	}
	else {
		glfwGetCursorPos(this->window, &this->mouseX2, &this->mouseY2);
		if (this->firstMouse2)
		{
			this->lastMouseX2 = this->mouseX2, this->lastMouseY2 = this->mouseY2, this->firstMouse2 = false;
		}
		//Calc offset
		this->mouseOffsetX2 = this->mouseX2 - this->lastMouseX2;
		this->mouseOffsetY2 = this->lastMouseY2 - this->mouseY2;
		//Set last X and Y
		this->lastMouseX2 = this->mouseX2, this->lastMouseY2 = this->mouseY2;
		this->firstMouse = true;
	}
}

void Game::updateInput()
{
	this->updateKeyboardInput();
	if (this->pageType == REGULAR) {
		this->updateMouseInput();
		if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
			this->camera.update_mouse_input2(dt, this->mouseOffsetX2, this->mouseOffsetY2);
		}
		else {
			this->camera.update_mouse_input(dt, this->mouseOffsetX, this->mouseOffsetY);
		}
	}
}

void Game::beforeRender()
{
	if (this->isFixedTime)
	{
		phy::before_render_physic4D(this->rigidBodies4d, this->groups, this->walls4d,this->sticks4d, this->springs4d,this->isTrail4d, 1.f/60.f,this->curTime);
	}
	if (this->mode == BUILDING)
	{
		//if (fixedUpdate::is_fixed_update2(this->dt, 1.f / 30.f))
		{
			this->demoObjects4d->clear();
			if (this->isFindPoint) {
				switch (this->buildMode)
				{
				case BUILD_OBJECT:
				{
					switch (this->buildCol)
					{
					case HYPERCUBE: { this->demoObjects4d->walls4d.push_back(this->demos4d[0]->walls4d[0]); break; }
					case HYPERSPHERE: { this->demoObjects4d->walls4d.push_back(this->demos4d[1]->walls4d[0]); break; }
					case HYPERCAPSULE: { this->demoObjects4d->walls4d.push_back(this->demos4d[2]->walls4d[0]); break; }
					case HYPERCYLINDER: { this->demoObjects4d->walls4d.push_back(this->demos4d[3]->walls4d[0]); break; }
					case HYPERCONE: { this->demoObjects4d->walls4d.push_back(this->demos4d[4]->walls4d[0]); break; }
					case HYPERPOT: { this->demoObjects4d->walls4d.push_back(this->demos4d[5]->walls4d[0]); break; }
					case TRIPRISM: { this->demoObjects4d->walls4d.push_back(this->demos4d[6]->walls4d[0]); break; }
					case HYPERSLOPE: { this->demoObjects4d->walls4d.push_back(this->demos4d[7]->walls4d[0]); break; }
					case HYPERQUAD: { this->demoObjects4d->walls4d.push_back(this->demos4d[8]->walls4d[0]); break; }
					case PENTACHORON: { this->demoObjects4d->walls4d.push_back(this->demos4d[9]->walls4d[0]); break; }
					case HYPERPYRAMID: { this->demoObjects4d->walls4d.push_back(this->demos4d[10]->walls4d[0]); break; }
					case HEXADECACHORON: { this->demoObjects4d->walls4d.push_back(this->demos4d[11]->walls4d[0]); break; }
					case HEXACOSICHORON: { this->demoObjects4d->walls4d.push_back(this->demos4d[12]->walls4d[0]); break; }
					}
					//alg::rotor4 rot = obj->rotation4D;
					this->demoObjects4d->walls4d[0]->set_position4D(hitObject4D == nullptr ? get_cap_position4D(this->hittingPos4D + this->buildScale.y * this->hitNormal / 2.f, this->buildDistance, this->buildOffset) : get_cap_position4D(hitObject4D, isFindPoint, this->hittingPos4D + this->buildScale.y * this->hitNormal / 2.f, this->buildDistance, this->buildOffset));
					this->demoObjects4d->walls4d[0]->set_rotation4D(hitObject4D == nullptr ? alg::rotor4() : update(hitObject4D->rotation4D, this->buildRotation*glm::radians(1.f)));
					this->demoObjects4d->walls4d[0]->set_scale4D(this->buildScale);
					this->demoObjects4d->walls4d[0]->texture3DIndex = this->buildTexture;
					break;
				}
				case BUILD_RIGIDBODY:
				{
					switch (this->buildCol)
					{
					case HYPERCUBE: { this->demoObjects4d->rigidBodies4d.push_back(this->demos4d[13]->rigidBodies4d[0]); break; }
					case HYPERSPHERE: { this->demoObjects4d->rigidBodies4d.push_back(this->demos4d[14]->rigidBodies4d[0]); break; }
					case HYPERCAPSULE: { this->demoObjects4d->rigidBodies4d.push_back(this->demos4d[15]->rigidBodies4d[0]); break; }
					case HYPERCYLINDER: { this->demoObjects4d->rigidBodies4d.push_back(this->demos4d[16]->rigidBodies4d[0]); break; }
					case HYPERCONE: { this->demoObjects4d->rigidBodies4d.push_back(this->demos4d[17]->rigidBodies4d[0]); break; }
					case HYPERPOT: { this->demoObjects4d->rigidBodies4d.push_back(this->demos4d[18]->rigidBodies4d[0]); break; }
					case TRIPRISM: { this->demoObjects4d->rigidBodies4d.push_back(this->demos4d[19]->rigidBodies4d[0]); break; }
					case HYPERSLOPE: { this->demoObjects4d->rigidBodies4d.push_back(this->demos4d[20]->rigidBodies4d[0]); break; }
					case HYPERQUAD: { this->demoObjects4d->rigidBodies4d.push_back(this->demos4d[21]->rigidBodies4d[0]); break; }
					case PENTACHORON: { this->demoObjects4d->rigidBodies4d.push_back(this->demos4d[22]->rigidBodies4d[0]); break; }
					case HYPERPYRAMID: { this->demoObjects4d->rigidBodies4d.push_back(this->demos4d[23]->rigidBodies4d[0]); break; }
					case HEXADECACHORON: { this->demoObjects4d->rigidBodies4d.push_back(this->demos4d[24]->rigidBodies4d[0]); break; }
					case HEXACOSICHORON: { this->demoObjects4d->rigidBodies4d.push_back(this->demos4d[25]->rigidBodies4d[0]); break; }
					}
					this->demoObjects4d->rigidBodies4d[0]->set_position4D(this->hittingPos4D + this->buildScale.y * this->hitNormal/2.f);
					this->demoObjects4d->rigidBodies4d[0]->set_rotation4D(look_at(glm::vec4(0.f), this->hitNormal, rotate(this->buildRotation,glm::vec4(0.f, 1.f, 0.f, 0.f))));
					this->demoObjects4d->rigidBodies4d[0]->set_scale4D(this->buildScale);
					this->demoObjects4d->rigidBodies4d[0]->texture3DIndex = this->buildTexture;
					break;
				}
				case BUILD_POOL_TABLE:
				{
					for (size_t i = 0; i < this->demos4d[26]->walls4d.size(); i++)
					{
						this->demoObjects4d->walls4d.push_back(this->demos4d[26]->walls4d[i]);
						this->demoObjects4d->walls4d[i]->set_mesh_position4D(this->demos4d[26]->walls4d[i]->position4d + get_cap_position4D(this->hittingPos4D, this->buildDistance, this->buildOffset));
					}
					break;
				}
				case BUILD_BILLIARD:
				{
					this->demoObjects4d->rigidBodies4d = this->demos4d[27]->rigidBodies4d;
					for (size_t i(0); i < this->demoObjects4d->rigidBodies4d.size(); i++)
					{
						this->demoObjects4d->rigidBodies4d[i]->set_mesh_position4D(this->demos4d[27]->rigidBodies4d[i]->position4d + this->hittingPos4D + glm::vec4(0.f, 0.0525f / 2.f, 0.f, 0.f));
					}
					break;
				}
				case BUILD_DYNAMITE:
				{
					if (this->isRigidBody)
					{
						this->demoObjects4d->rigidBodies4d = this->demos4d[29]->rigidBodies4d;
						for (size_t i(0); i < this->demoObjects4d->rigidBodies4d.size(); i++)
						{
							this->demoObjects4d->rigidBodies4d[i]->set_mesh_position4D(this->demos4d[29]->rigidBodies4d[i]->position4d + this->hittingPos4D);
						}
					}
					else
					{
						this->demoObjects4d->walls4d = this->demos4d[28]->walls4d;
						for (size_t i(0); i < this->demoObjects4d->walls4d.size(); i++)
						{
							this->demoObjects4d->walls4d[i]->set_mesh_position4D(this->demos4d[28]->walls4d[i]->position4d + this->hittingPos4D);
						}
					}
					break;
				}
				case BUILD_POINTLIGHT:
				{
					this->demoObjects4d->pointLight4D = this->demos4d[32]->pointLight4D;
					this->demoObjects4d->pointLight4D->intensity = this->lightIntensity;
					this->demoObjects4d->pointLight4D->set_pointlight4d_mesh_position(get_cap_position4D(this->hittingPos4D, this->buildDistance, this->buildOffset));
				}
				}
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
								if (!this->springs4d[this->springs4d.size() - 1]->index2.isValid)
								{
									isInitial = false;
									this->demoObjects4d->spring4D = this->demos4d[31]->spring4D;
									this->demoObjects4d->spring4D->fixPoint4D = this->camera.frontPosition4D;
									this->demoObjects4d->spring4D->index1 = this->springs4d[this->springs4d.size() - 1]->index1;
									this->demoObjects4d->spring4D->index2.isValid = this->springs4d[this->springs4d.size() - 1]->index1 == this->hitIndex.n ? false : true;
									if (this->demoObjects4d->spring4D != nullptr)
										phy::update_spring4D(this->rigidBodies4d, this->walls4d, this->demoObjects4d->spring4D);
								}
							}
							if (isInitial)
							{
								if (this->sticks4d.size() == 0)
								{
									this->demoObjects4d->stick4D = this->demos4d[30]->stick4D;
									this->demoObjects4d->stick4D->fixPoint4D = this->camera.frontPosition4D;
									this->demoObjects4d->stick4D->index1 = this->hitIndex.n;
									this->demoObjects4d->stick4D->index2.isValid = false;
									this->demoObjects4d->stick4D->set_stick_length(this->stickLength);
								}
								else if (this->sticks4d.size() != 0)
								{
									if (!this->sticks4d[this->sticks4d.size() - 1]->index2.isValid)
									{
										this->demoObjects4d->stick4D = this->demos4d[30]->stick4D;
										this->demoObjects4d->stick4D->fixPoint4D = this->camera.frontPosition4D;
										this->demoObjects4d->stick4D->index1 = this->sticks4d[this->sticks4d.size() - 1]->index1;
										this->demoObjects4d->stick4D->index2.isValid = this->sticks4d[this->sticks4d.size() - 1]->index1 == this->hitIndex.n ? false : true;
										this->demoObjects4d->stick4D->set_stick_length(this->stickLength);
									}
									else if (this->sticks4d[this->sticks4d.size() - 1]->index2.isValid)
									{
										this->demoObjects4d->stick4D = this->demos4d[30]->stick4D;
										this->demoObjects4d->stick4D->fixPoint4D = this->camera.frontPosition4D;
										this->demoObjects4d->stick4D->index1 = this->hitIndex.n;
										this->demoObjects4d->stick4D->index2.isValid = false;
										this->demoObjects4d->stick4D->set_stick_length(this->stickLength);
									}
								}
								if (this->demoObjects4d->stick4D != nullptr)
									phy::update_stick4D(this->rigidBodies4d, this->walls4d, this->demoObjects4d->stick4D);
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
									if (!this->sticks4d[this->sticks4d.size() - 1]->index2.isValid)
									{
										isInitial = false;
										this->demoObjects4d->stick4D = this->demos4d[30]->stick4D;
										this->demoObjects4d->stick4D->fixPoint4D = this->camera.frontPosition4D;
										this->demoObjects4d->stick4D->index1 = this->sticks4d[this->sticks4d.size() - 1]->index1;
										this->demoObjects4d->stick4D->index2.isValid = this->sticks4d[this->sticks4d.size() - 1]->index1 == this->hitIndex.n ? false : true;
										this->demoObjects4d->stick4D->set_stick_length(this->stickLength);
										if (this->demoObjects4d->stick4D != nullptr)
											phy::update_stick4D(this->rigidBodies4d, this->walls4d, this->demoObjects4d->stick4D);
									}
								}
								if (isInitial)
								{
									if (this->springs4d.size() == 0)
									{
										this->demoObjects4d->spring4D = this->demos4d[31]->spring4D;
										this->demoObjects4d->spring4D->fixPoint4D = this->camera.frontPosition4D;
										this->demoObjects4d->spring4D->index1 = this->hitIndex.n;
										this->demoObjects4d->spring4D->index2.isValid = false;
									}
									else if (this->springs4d.size() != 0)
									{
										if (!this->springs4d[this->springs4d.size() - 1]->index2.isValid)
										{
											this->demoObjects4d->spring4D = this->demos4d[31]->spring4D;
											this->demoObjects4d->spring4D->fixPoint4D = this->camera.frontPosition4D;
											this->demoObjects4d->spring4D->index1 = this->springs4d[this->springs4d.size() - 1]->index1;
											this->demoObjects4d->spring4D->index2.isValid = this->springs4d[this->springs4d.size() - 1]->index1 == this->hitIndex.n ? false : true;
										}
										else if (this->springs4d[this->springs4d.size() - 1]->index2.isValid)
										{
											this->demoObjects4d->spring4D = this->demos4d[31]->spring4D;
											this->demoObjects4d->spring4D->fixPoint4D = this->camera.frontPosition4D;
											this->demoObjects4d->spring4D->index1 = this->hitIndex.n;
											this->demoObjects4d->spring4D->index2.isValid = false;
										}
									}
									if (this->demoObjects4d->spring4D != nullptr)
										phy::update_spring4D(this->rigidBodies4d, this->walls4d, this->demoObjects4d->spring4D);
								}
							}
						}
					}
				}
		}
	}
	//Update the lights
	this->updateLights();
	//Update the uniforms
	this->updateUniforms();
}

void Game::update0()
{
	//UPDATE INPUT ---
	//if(this->level = 3)std::cout << "steps1" << '\n';
	this->firstUpdate();
	//if(this->level = 3)std::cout << "steps2" << '\n';
	this->updateTime();
	//if(this->level = 3)std::cout << "steps3" << '\n';
	this->updateObjects();
}

void Game::update1()
{
	//if(this->level = 3)std::cout << "steps4" << '\n';
	this->updateCollider();
	//if(this->level = 3)std::cout << "steps5" << '\n';
	this->updateDynamites();
	//if(this->level = 3)std::cout << "steps6" << '\n';
	this->updateParticles();
	//if(this->level = 3)std::cout << "steps7" << '\n';
	this->updateInput();
	//if(this->level = 3)std::cout << "steps8" << '\n';
	this->judgeRender();
	//if(this->level = 3)std::cout << "steps9" << '\n';
	this->beforeRender();
	//if(this->level = 3)std::cout << "steps10" << '\n';
}

void Game::render0()
{
	if(this->isHDR)
	this->hDRTextures[0]->bind_frame_buffer();
	//Clear
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//Render models
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_FRAMEBUFFER_SRGB);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//for (Object* i : this->objects){i->render(this->shaders[OBJ]);}
	//1:OBJS NOT TRANSPARENT
	glLineWidth(1.f);

	for (size_t index(0); index < this->renderIndices1.size(); index++)
	{
		RenderIndex* i(this->renderIndices1[index]);
        if (i->type == 0)
		{
			RigidBody4D* a(this->rigidBodies4d[i->objectIndex]);
			a->render(this->wallTexs3d[a->texture3DIndex], this->shaders[a->shaderIndex]);
		}
		else if (i->type == 1)
		{
			Wall4D* a(this->walls4d[i->objectIndex]);
			a->render(this->wallTexs3d[a->texture3DIndex], this->shaders[a->shaderIndex]);
		}
		else if (i->type == 2)
		{
			if (i->objectIndex < this->sticks4d.size())
			{
				Stick4D* stick4D(this->sticks4d[i->objectIndex]);
				stick4D->render(this->wallTexs3d[stick4D->texture3DIndex], this->shaders[stick4D->shaderIndex]);
			}
			else
			{
				Spring4D* springs4d(this->springs4d[i->objectIndex - this->sticks4d.size()]);
				springs4d->render(this->wallTexs3d[springs4d->texture3DIndex], this->shaders[springs4d->shaderIndex]);
			}
		}
	}
	for (Group* i : this->groups) {
		if (i->isRender) {
			for (size_t terrain4DIndex : i->terrains4DIndices)
			{       
				Terrain4D* t(this->terrains4d[terrain4DIndex]);
				if (t->isClamp && t->isFront) {
					t->render(this->shaders[t->shaderIndex]);
				}
			}
		}
	}

	glDisable(GL_FRAMEBUFFER_SRGB);

	if (this->isFramework)
	{
		for (Group* i : this->groups) {
			if (i->isRender) {
				for (size_t wall4DIndex : i->walls4DIndices)
				{
					Wall4D* w(this->walls4d[wall4DIndex]);
					if (w->isFront) {
						w->render_frame(this->shaders[FRAMED4]);
					}
				}
			}
		}
		for (RigidBody4D* j : this->rigidBodies4d) {
			j->render_frame(this->shaders[FRAMED4]);
		}
		for (Stick4D* i : this->sticks4d)
		{
			if (i->index2.isValid)
			{
				i->render_frame(this->shaders[FRAMED4]);
			}
		}
		for (Spring4D* i : this->springs4d)
		{
			if (i->index2.isValid)
			{
				i->render_frame(this->shaders[FRAMED4]);
			}
		}
		if (this->mode == BUILDING) {
			if (!(this->buildMode == BUILD_STICK || this->buildMode == BUILD_SPRING))
			{
				if (this->isFindPoint) {
					for (Wall4D* j : this->demoObjects4d->walls4d)
					{
						j->render_frame(this->shaders[FRAMED4]);
					}
					for (RigidBody4D* j : this->demoObjects4d->rigidBodies4d)
					{
						j->render_frame(this->shaders[FRAMED4]);
					}
					PointLight4D* p(this->demoObjects4d->pointLight4D);
					if (p != nullptr)p->render_frame(this->shaders[LIGHT_FRAMED4]);
				}
			}
			else
			{
				if (this->demoObjects4d->stick4D != nullptr)
				{
					this->demoObjects4d->stick4D->render_frame(this->shaders[FRAMED4]);
				}
				if (this->demoObjects4d->spring4D != nullptr)
				{
					this->demoObjects4d->spring4D->render_frame(this->shaders[FRAMED4]);
				}
			}
		}
		if (this->isShowingGroupArea) {
			for (size_t i(1); i < this->groupIndices.size(); i++)
			{
				Group* group(this->groups[this->groupIndices[i]]);
				this->groupAreaHypercube->set_mesh_position4D(group->position4d);
				this->groupAreaHypercube->render_frame(this->shaders[FRAMED4]);
			}
		}
		glLineWidth(1.9f);
		for (Emitter4D* i : this->emitters4d)
		{
			for (Particle4D0* j : i->particles4D)
			{
				if (j->isGlowing) { glBlendFunc(GL_SRC_ALPHA, GL_ONE); }
				else { glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); }
				j->render_frame(this->shaders[LIGHT_FRAMED4]);
			}
		}
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		for (PointLight4D* p : this->pointLights4d) {
			p->render_frame(this->shaders[LIGHT_FRAMED4]);
		}
		this->directionLight4d->render_frame(this->shaders[LIGHT_FRAMED4]);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	glLineWidth(1.9f);
	if (isJointLine4d)
	{
		for (Stick4D* i : this->sticks4d)
		{
			if (i->index2.isValid)
			{
				i->render_line4D(this->shaders[JOINT_LINED4]);
			}
		}
		for (Spring4D* i : this->springs4d)
		{
			if (i->index2.isValid)
			{
				i->render_line4D(this->shaders[JOINT_LINED4]);
			}
		}
		if (this->mode == BUILDING) {
			if (this->buildMode == BUILD_STICK || this->buildMode == BUILD_SPRING)
			{
				if (this->demoObjects4d->stick4D != nullptr)
				{
					this->demoObjects4d->stick4D->render_line4D(this->shaders[JOINT_LINED4]);
				}
				if (this->demoObjects4d->spring4D != nullptr)
				{
					this->demoObjects4d->spring4D->render_line4D(this->shaders[JOINT_LINED4]);
				}
			}
		}
	}
	//
	//2:SKY BOX

	glEnable(GL_FRAMEBUFFER_SRGB);
	this->skybox4d->render(this->shaders[this->skybox4d->shaderIndex]);
	//
	//3:PARTICLES
	glDepthMask(false);
	for (Emitter4D* i : this->emitters4d)
	{
		for (Particle4D0* j : i->particles4D)
		{
			if (j->isGlowing) glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			else glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			j->render(this->particleTexs3d[j->texture3Dindex],this->shaders[PARTICLED4]);
		}
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	for (PointLight4D* p : this->pointLights4d) {
		p->render(this->particleTexs3d[p->texture3DIndex], this->shaders[LIGHT_PARTICLED4]);
	}

	glDepthMask(true);
	glDisable(GL_FRAMEBUFFER_SRGB);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (JointLine4D* i : this->dragLines4d)
	{
		i->render(this->shaders[JOINT_LINED4]);
	}
	for (XRay4D* i : this->xRays4d)
	{
		i->render(this->shaders[JOINT_LINED4]);
	}
	//
	//4:TRANSPARENT OBJS
	glLineWidth(1.f);
	//glDepthMask(false);
	//glDepthFunc(GL_ALWAYS);
	//std::cout << "render start:" << "\n";
	glDepthMask(false);
	glEnable(GL_FRAMEBUFFER_SRGB);
	glDisable(GL_CULL_FACE);
	for (Water4D* a : this->waters4d) {
		a->render(this->shaders[a->shaderIndex]);
	}
	glEnable(GL_CULL_FACE);

	for (int index(this->renderIndices2.size() - 1); index >= 0; index--)
	{
		RenderIndex* i(this->renderIndices2[index]);
		if (i->type == 0)
		{
			RigidBody4D* a(this->rigidBodies4d[i->objectIndex]);
			a->render(this->wallTexs3d[a->texture3DIndex], this->shaders[a->shaderIndex]);
		}
		else if (i->type == 1)
		{
			Wall4D* a(this->walls4d[i->objectIndex]);
			a->render(this->wallTexs3d[a->texture3DIndex], this->shaders[a->shaderIndex]);
		}
		else if (i->type == 2)
		{
			if (i->objectIndex < this->sticks4d.size())
			{
				Stick4D* stick4D(this->sticks4d[i->objectIndex]);
				stick4D->render(this->wallTexs3d[stick4D->texture3DIndex], this->shaders[stick4D->shaderIndex]);
			}
			else
			{
				Spring4D* springs4d(this->springs4d[i->objectIndex - this->sticks4d.size()]);
				springs4d->render(this->wallTexs3d[springs4d->texture3DIndex], this->shaders[springs4d->shaderIndex]);
			}
		}
	}
	glEnable(GL_CULL_FACE);
	glDepthMask(true);
	glLineWidth(1.9f);
	if (this->mode == BUILDING) {
		if (!(this->buildMode == BUILD_STICK || this->buildMode == BUILD_SPRING))
		{
			if (this->isFindPoint) {
				for (Wall4D* a : this->demoObjects4d->walls4d)
				{
					a->render(this->wallTexs3d[a->texture3DIndex], this->shaders[a->shaderIndex]);
				}
				for (RigidBody4D* a : this->demoObjects4d->rigidBodies4d)
				{
					a->render(this->wallTexs3d[a->texture3DIndex], this->shaders[a->shaderIndex]);
				}
				if (this->buildMode == BUILD_POINTLIGHT)
				{
					glBlendFunc(GL_ONE, GL_ONE);
					PointLight4D* p(this->demoObjects4d->pointLight4D);
					if (p != nullptr)p->render(this->particleTexs3d[p->texture3DIndex], this->shaders[LIGHT_PARTICLED4]);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				}
			}
		}
		else
		{
			if (this->demoObjects4d->stick4D != nullptr)
			{
				this->demoObjects4d->stick4D->render(this->wallTexs3d[this->demoObjects4d->stick4D->texture3DIndex], this->shaders[this->demoObjects4d->stick4D->shaderIndex]);
			}
			if (this->demoObjects4d->spring4D != nullptr)
			{
				this->demoObjects4d->spring4D->render(this->wallTexs3d[this->demoObjects4d->spring4D->texture3DIndex], this->shaders[this->demoObjects4d->spring4D->shaderIndex]);
			}
		}
	}
	glDisable(GL_CULL_FACE);
	glDepthMask(false);
	if (this->isShowingGroupArea) {
		for (size_t i(1); i < this->groupIndices.size(); i++)
		{
			Group* group(this->groups[this->groupIndices[i]]);
			this->groupAreaHypercube->set_mesh_position4D(group->position4d);
			this->groupAreaHypercube->render(this->wallTexs3d[this->groupAreaHypercube->texture3DIndex], this->shaders[this->groupAreaHypercube->shaderIndex]);
		}
	}
	glDepthMask(true);
	glDisable(GL_FRAMEBUFFER_SRGB);
	glEnable(GL_CULL_FACE);
	if (this->isTrail4d) {
		//glLineWidth(4.9f);
		for (RigidBody4D* i : this->rigidBodies4d)
		{
			i->trail4D->render(this->shaders[TRAILD4]);
		}
		//glLineWidth(1.9f);
	}

	glEnable(GL_FRAMEBUFFER_SRGB);
	
	//glDepthFunc(GL_LESS);
	//glDepthMask(true);
	//
	//5:LENS FLARE
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	if (ray::is_in_screen(this->directionLight4d->direction4D, camera.viewMat4D, camera.projectionMat))
	{
		VectorIndex hitIndex2;
		glm::vec4 hitPosNear2;
		glm::vec4 hitPosNormal2;
		if (!ray::detect_object4d_index(&hitIndex2, this->rigidBodies4d, this->groupIndices, this->groups, this->walls4d, this->terrains4d, this->sticks4d, this->springs4d, true, true, false, true, this->camera.position4d, -this->directionLight4d->direction4D, this->directionLight4d->right4D, &hitPosNear2, &hitPosNormal2))
		{
			glDepthMask(false);
			this->directionLight4d->render_lens_flare(this->camera.forward4D, this->particleTexs3d[this->directionLight4d->texture3DIndex],this->particleTexs3d[PARTICLE2], this->shaders[LIGHT_PARTICLED4]);
			glDepthMask(true);
		}	
	}
	glDisable(GL_FRAMEBUFFER_SRGB);
	//
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (this->isHDR)
	{
		glEnable(GL_FRAMEBUFFER_SRGB);
		this->hdrQuad->set_is_fetched(this->shader2dShape,true);
		this->hDRTextures[0]->unbind_frame_buffer();

		if (this->isBloom)
		{
			this->bloomExpandMaps[0]->bind_frame_buffer();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glViewport(0, 0, this->framebufferWidth / 3, this->framebufferHeight / 3);
			//this->hdrQuad->
			if(!isAutoExposure) this->hdrQuad->render(this->hDRTextures[0], this->shaderHDRs[SUB_EXPOSURE], glm::vec2(this->framebufferWidth/3, this->framebufferHeight/3), this->exposure2 / 3.25f);
			else this->hdrQuad->render(this->hDRTextures[0], this->shaderHDRs[SUB_EXPOSURE], glm::vec2(this->framebufferWidth/3, this->framebufferHeight/3),this->exposure);
			this->bloomExpandMaps[0]->unbind_frame_buffer();

			for (size_t i(1); i < 11; i++)
			{
				this->bloomExpandMaps[i]->bind_frame_buffer();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				this->shaderHDRs[BLOOM_EXPAND]->use();
				this->shaderHDRs[BLOOM_EXPAND]->set1i(((i-1)-(i-1)%2)/2, "level");
				this->shaderHDRs[BLOOM_EXPAND]->set1i(i%2, "type");
				this->hdrQuad->render(this->bloomExpandMaps[i-1], this->shaderHDRs[BLOOM_EXPAND], glm::vec2(this->framebufferWidth / 3, this->framebufferHeight / 3));
				this->bloomExpandMaps[i]->unbind_frame_buffer();
			}

			this->hDRTextures[1]->bind_frame_buffer();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			this->hdrQuad->render(this->bloomExpandMaps, this->shaderHDRs[BLOOM], glm::vec2(this->framebufferWidth / 3, this->framebufferHeight / 3));
			this->hDRTextures[1]->unbind_frame_buffer();

			if(this->isAutoExposure)
			{ 
			    this->hDRTextures[2]->bind_frame_buffer();
			    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			    glViewport(0, 0, 3, 3);
			    glClearColor(0, 0, 0, 1);
			    glBlendFunc(GL_ONE, GL_ONE);
			    this->hdrQuad->render(this->hDRTextures[0], this->shaderHDRs[HDR_EXPOSURE], glm::vec2(3.f), this->exposure);
			    this->hDRTextures[2]->unbind_frame_buffer();
			    get_exposure(this->hDRTextures[2]->get_avg_color(), &this->exposure, this->exposureSpeed, this->exposureMultiplier, this->dt);
			}
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glViewport(0, 0, this->framebufferWidth, this->framebufferHeight);
			glClearColor(0, 0, 0, 1);
			glBlendFunc(GL_ONE, GL_ONE);
			if (!this->isAutoExposure)this->hdrQuad->render(this->hDRTextures[0], this->shaderHDRs[HDR_EXPOSURE], glm::vec2(this->framebufferWidth, this->framebufferHeight), this->exposure2 / 3.25f);
			else this->hdrQuad->render(this->hDRTextures[0], this->shaderHDRs[HDR_EXPOSURE], glm::vec2(this->framebufferWidth, this->framebufferHeight));
			this->hdrQuad->render(this->hDRTextures[1], this->shaderHDRs[HDR], glm::vec2(this->framebufferWidth, this->framebufferHeight));
		}
		else
		{
			if(this->isAutoExposure)
			{
				this->hDRTextures[2]->bind_frame_buffer();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glViewport(0, 0, 3, 3);
				this->hdrQuad->render(this->hDRTextures[0], this->shaderHDRs[HDR_EXPOSURE], glm::vec2(3.f), this->exposure);
				this->hDRTextures[2]->unbind_frame_buffer();
				get_exposure(this->hDRTextures[2]->get_avg_color(), &this->exposure, this->exposureSpeed, this->exposureMultiplier, this->dt);
			}
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glViewport(0, 0, this->framebufferWidth, this->framebufferHeight);
			if (!this->isAutoExposure)this->hdrQuad->render(this->hDRTextures[0], this->shaderHDRs[HDR_EXPOSURE], glm::vec2(this->framebufferWidth, this->framebufferHeight), this->exposure2 / 3.25f);
			else this->hdrQuad->render(this->hDRTextures[0], this->shaderHDRs[HDR_EXPOSURE], glm::vec2(this->framebufferWidth, this->framebufferHeight));
		}
		this->hdrQuad->set_is_fetched(this->shader2dShape, false);
		glDisable(GL_FRAMEBUFFER_SRGB);
	}
	//6:GUI
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth(1.9f);
	if (this->isRenderCoordinate4d){
		//this->coordinate4d->update(this->camera.forward4D,0);
		this->coordinate4d->render(this->shaders[COORDNATED4]);
	}

	if (this->pageType == REGULAR)
	{
		glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_COLOR);
		this->targetIcon->render(this->pointerTexs[this->mode],this->shader2dShape, (32.f/ (float)this->framebufferHeight)*glm::vec2((float)this->framebufferHeight / (float)this->framebufferWidth, 1.f));
	}
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (this->pageType == IMGUI||this->pageType == SETTINGS)
	{
		imgui_use();
	}

	if (this->pageType == GAMEOVER)
	{
		double mX, mY;
		glfwGetCursorPos(this->window, &mX, &mY);
		this->canvas2d[GAMEOVER]->interact2(this->framebufferWidth, this->framebufferHeight, this->ratio, mX, mY, this->dt, this->inputs[0], this->window);
		this->canvas2d[GAMEOVER]->interact1();
		if (this->canvas2d[GAMEOVER]->buttons2d[0]->isResponse) { this->startLevel(this->level, ""); }
		if (this->canvas2d[GAMEOVER]->buttons2d[1]->isResponse) {this->startLevel(this->level = 0, "");}
		this->canvas2d[GAMEOVER]->render(this->framebufferWidth, this->framebufferHeight, this->ratio, *this->shaders[TEXT], *this->shaders[RECTANGLE], this->dt);
	}

	if (this->pageType == EXIT)
	{
		//std::cout << "steps1" << '\n';
		double mX, mY;
		glfwGetCursorPos(this->window, &mX, &mY);
		this->canvas2d[EXIT]->interact2(this->framebufferWidth, this->framebufferHeight, this->ratio, mX, mY, this->dt, this->inputs[0], this->window);
		this->canvas2d[EXIT]->interact1();
		//std::cout << "steps2" << '\n';
		if (this->canvas2d[EXIT]->buttons2d[0]->isResponse) {
			this->isCloseUI = true;
			glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			this->firstMouse = !this->firstMouse;

			this->pageType = REGULAR;
		}
		//std::cout << "steps3" << '\n';
		if (this->canvas2d[EXIT]->buttons2d[1]->isResponse) {
			this->startLevel(this->level = 0, "");
		}
		//std::cout << "steps4" << '\n';
		this->canvas2d[EXIT]->render(this->framebufferWidth, this->framebufferHeight, this->ratio, *this->shaders[TEXT], *this->shaders[RECTANGLE], this->dt);
		//std::cout << "steps5" << '\n';
	}

	if (this->isDebug)
	{
		char ss[256];
		sprintf(ss, "(%.1f FPS) %.3f ms/frame Application average", 1000.f * this->dt, 1.f/this->dt);
		this->canvas2d[INFORMATION]->texts2d[0]->update(ss);
		sprintf(ss, "%1i px Frame buffer width %1i px Frame buffer height", this->framebufferWidth, this->framebufferHeight);
		this->canvas2d[INFORMATION]->texts2d[2]->update(ss);
		if (this->isFullscreen)
			sprintf(ss, "Full mode");
		if (!this->isFullscreen)
			sprintf(ss, "Windowed mode");
		this->canvas2d[INFORMATION]->texts2d[3]->update(ss);
		sprintf(ss, "(% .1f x % .1f y % .1f z % .1f w) m Position", this->camera.position4d.x, this->camera.position4d.y, this->camera.position4d.z, this->camera.position4d.w);
		this->canvas2d[INFORMATION]->texts2d[5]->update(ss);
		sprintf(ss, "(%.1f xy %.1f xz %.1f xw %.1f yz %.1f yw %.1f zw) ° Rotation", this->camera.rotateAngle4D.xy, this->camera.rotateAngle4D.xz, this->camera.rotateAngle4D.xw, this->camera.rotateAngle4D.yz, this->camera.rotateAngle4D.yw, this->camera.rotateAngle4D.zw);
		this->canvas2d[INFORMATION]->texts2d[6]->update(ss);
		sprintf(ss, "(%.1f x %.1f y %.1f z %.1f w) %.1f m/s Speed", this->rigidBodies4d[0]->velocity4d.x, this->rigidBodies4d[0]->velocity4d.y, this->rigidBodies4d[0]->velocity4d.z, this->rigidBodies4d[0]->velocity4d.w, alg::length(this->rigidBodies4d[0]->velocity4d));
		this->canvas2d[INFORMATION]->texts2d[7]->update(ss);
		size_t wallLoadedSize(0);
		size_t terrainLoadedSize(0);
		for (size_t groupIndex : groupIndices)
		{
			Group* i(groups[groupIndex]);
			wallLoadedSize += i->walls4DIndices.size();
			terrainLoadedSize += i->terrains4DIndices.size();
		}
		sprintf(ss, "%1i Group(s) Had %1i Group(s) Loaded %1i Object(s) Loaded", this->groups.size() - 1, this->groupIndices.size() - 1, this->rigidBodies4d.size() + wallLoadedSize + terrainLoadedSize + this->waters4d.size());
		this->canvas2d[INFORMATION]->texts2d[9]->update(ss);
		sprintf(ss, "%1i Object(s) %1i Rigid Body(s) %1i Light(s)", size_of_objects4d(this->rigidBodies4d, this->walls4d) + this->terrains4d.size() + this->waters4d.size(), this->rigidBodies4d.size(), this->pointLights4d.size());
		this->canvas2d[INFORMATION]->texts2d[10]->update(ss);
		sprintf(ss, "%1i Sticks(s) %1i Spring(s) %1i Hinge(s)", this->sticks4d.size(), this->springs4d.size(), this->hingeConstraintsVec.size());
		this->canvas2d[INFORMATION]->texts2d[11]->update(ss);
		int particlesCount(0);
		for (Emitter4D* i : this->emitters4d)
		{
			particlesCount += i->particles4D.size();
		}
		sprintf(ss, "%1i Particle(s)", particlesCount);
		this->canvas2d[INFORMATION]->texts2d[12]->update(ss);
		sprintf(ss, "%1i Displacement(s) %1i Floating(s) %1i Rotating(s) Animation", this->shifts4d.size(), this->floats4d.size(), this->rotates4d.size());
		this->canvas2d[INFORMATION]->texts2d[13]->update(ss);
		sprintf(ss, "(%1i m) Block (%1i m) Object", this->blockLoadDistance, this->objectLoadDistance);
		this->canvas2d[INFORMATION]->texts2d[15]->update(ss);
		sprintf(ss, "%1i Major %1i Minor", this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR);
		this->canvas2d[INFORMATION]->texts2d[17]->update(ss);
		sprintf(ss, "level %1i", this->level);
		this->canvas2d[INFORMATION]->texts2d[19]->update(ss);
		sprintf(ss, "%.1f s World Time", this->worldTime);
		this->canvas2d[INFORMATION]->texts2d[20]->update(ss);
		sprintf(ss, "%.1f s Play Time", this->curTime);
		this->canvas2d[INFORMATION]->texts2d[21]->update(ss);
		this->canvas2d[INFORMATION]->render(this->framebufferWidth, this->framebufferHeight, this->ratio, *this->shaders[TEXT], *this->shaders[RECTANGLE], this->dt);
	}

	if (this->pageType == START_MENU)
	{
		//this->rigidBodies4d[0]->position4d.w = 0.15f;
		//this->rigidBodies4d[0]->angularVelocity4D = alg::bivec4(0.f, 0.f, 100.f * this->dt, 0.f, 0.f, 0.f);
		this->rigidBodies4d[0]->velocity4d = -2.f * glm::vec4(0.f, 0.f, 1.f, 1.f);
		double mX, mY;
		glfwGetCursorPos(this->window, &mX, &mY);
		this->canvas2d[START_MENU]->interact2(this->framebufferWidth, this->framebufferHeight, this->ratio, mX, mY, this->dt, this->inputs[0], this->window);
		this->canvas2d[START_MENU]->interact1();
		if (this->canvas2d[START_MENU]->buttons2d[0]->isResponse)this->pageType = LEVELS;
		if (this->canvas2d[START_MENU]->buttons2d[1]->isResponse)this->pageType = GOALS;
		if (this->canvas2d[START_MENU]->buttons2d[2]->isResponse)this->pageType = SETTINGS;
		if (this->canvas2d[START_MENU]->buttons2d[3]->isResponse)glfwSetWindowShouldClose(this->window, GLFW_TRUE);;
		this->canvas2d[START_MENU]->render(this->framebufferWidth, this->framebufferHeight, this->ratio, *this->shaders[TEXT], *this->shaders[RECTANGLE], this->dt);
	}

	if (this->pageType == GOALS)
	{
		this->rigidBodies4d[0]->velocity4d = -2.f * glm::vec4(0.f, 0.f, 1.f, 1.f);
		double mX, mY;
		glfwGetCursorPos(this->window, &mX, &mY);
		this->canvas2d[GOALS]->interact2(this->framebufferWidth, this->framebufferHeight, this->ratio, mX, mY, this->dt, this->inputs[0], this->window);
		this->canvas2d[GOALS]->interact1();
		if (this->canvas2d[GOALS]->buttons2d[0]->isResponse)this->pageType = START_MENU;
		this->canvas2d[GOALS]->render(this->framebufferWidth, this->framebufferHeight, this->ratio, *this->shaders[TEXT], *this->shaders[RECTANGLE], this->dt);
	}

	if (this->pageType == LEVELS)
	{
		this->rigidBodies4d[0]->velocity4d = -2.f * glm::vec4(0.f, 0.f, 1.f, 1.f);
		double mX, mY;
		glfwGetCursorPos(this->window, &mX, &mY);
		this->canvas2d[LEVELS]->interact2(this->framebufferWidth, this->framebufferHeight, this->ratio, mX, mY, this->dt, this->inputs[0], this->window);
		this->canvas2d[LEVELS]->interact1();
		if (this->canvas2d[LEVELS]->buttons2d[0]->isResponse)this->startLevel(this->level = 1,"");
		if (this->canvas2d[LEVELS]->buttons2d[1]->isResponse)this->startLevel(this->level = 2, "");
		if (this->canvas2d[LEVELS]->buttons2d[2]->isResponse)this->startLevel(this->level = 3, "");
		if (this->canvas2d[LEVELS]->buttons2d[3]->isResponse)this->startLevel(this->level = 4, "");
		if (this->canvas2d[LEVELS]->buttons2d[4]->isResponse)this->startLevel(this->level = 5, "");
		if (this->canvas2d[LEVELS]->buttons2d[5]->isResponse)this->startLevel(this->level = 6, "");
		if (this->canvas2d[LEVELS]->buttons2d[6]->isResponse)this->pageType = START_MENU;
		this->canvas2d[LEVELS]->render(this->framebufferWidth, this->framebufferHeight, this->ratio, *this->shaders[TEXT], *this->shaders[RECTANGLE], this->dt);
	}

	if (this->pageType == SETTINGS)
	{
		this->rigidBodies4d[0]->velocity4d = -2.f * glm::vec4(0.f, 0.f, 1.f, 1.f);
		double mX, mY;
		glfwGetCursorPos(this->window, &mX, &mY);
		this->canvas2d[SETTINGS]->interact2(this->framebufferWidth, this->framebufferHeight, this->ratio, mX, mY, this->dt, this->inputs[0], this->window);
		this->canvas2d[SETTINGS]->interact1();
		if (this->canvas2d[SETTINGS]->buttons2d[0]->isResponse)this->pageType = START_MENU;
		this->canvas2d[SETTINGS]->render(this->framebufferWidth, this->framebufferHeight, this->ratio, *this->shaders[TEXT], *this->shaders[RECTANGLE], this->dt);
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//

	//End Draw
	glfwSwapBuffers(this->window);
	glfwPollEvents();
	glFlush();
}

//Static functions
//void Game::scroll_call_back(GLFWwindow* window, double xOffset, double yOffset){
//	mode2 += 1;
//	//void Game::updateModes(-1, yOffset);
//};