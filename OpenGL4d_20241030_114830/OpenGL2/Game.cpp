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
	this->shader2DShape = new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		"resourcefile/shaders/shape2D.vertex", "resourcefile/shaders/shape2D.fragment");
	this->textures.push_back(new Texture("resourcefile/images/logo.png"));
	this->rectangle2D = new Rectangle2D(0);
	glClearColor(0.1f, 0.1f, 0.1f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	float photoRate((float)this->textures[this->rectangle2D->textureIndex]->height / (float)this->textures[this->rectangle2D->textureIndex]->width);
	float screenRate((float)this->framebufferHeight / (float)this->framebufferWidth);
	glm::vec2 photoScale;
	if (photoRate < screenRate) photoScale = glm::vec2(1.f, photoRate / screenRate);
	else photoScale = glm::vec2(screenRate / photoRate,1.f);
	this->rectangle2D->render(this->textures[this->rectangle2D->textureIndex],this->shader2DShape, photoScale);
	this->hdrQuad = new Rectangle2D(0);
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
		"resourcefile/shaders/light_particle4D.vertex", "resourcefile/shaders/light_particle4D.fragment"));
	this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		"resourcefile/shaders/coordinate4D.vertex", "resourcefile/shaders/coordinate4D.fragment"));
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
		"resourcefile/images/maps/VERTEX_MAP4D.png"));
	this->textures.push_back(new Texture(
		"resourcefile/images/maps/BRIGHTNESS.png"));
	char ss[256];
	for (int i(1); i <= 10; i++){
		snprintf(ss, 255, "resourcefile/images/2d/i1-%i.png", i);
		this->textures.push_back(new Texture(ss));
	}
	for (int i(1); i <= 58; i++){
		snprintf(ss, 255, "resourcefile/images/2d/i2-%i.png", i);
		this->textures.push_back(new Texture(ss));
	}
	for (int i(1); i <= 7; i++){
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

	this->textures3D.push_back(new Texture3D(
		"resourcefile/images/noise2.png"));
	this->textures3D.push_back(new Texture3D(
		"resourcefile/images/sky_panorama/3dstars_field.png"));
	this->textures3D.push_back(new Texture3D(
		"resourcefile/images/maps/NOISE_NORMAL4D.png"));
	this->textures3D.push_back(new Texture3D(
		"resourcefile/images/animation/caustics.png"));
	this->textures3D.push_back(new Texture3D(
		"resourcefile/images/maps/BLEND.png"));
	this->textures3D.push_back(new Texture3D(
		"resourcefile/images/maps/AREA.png"));
	this->textures3D.push_back(this->textures3D[AREA]);

	this->particleTexs3D.push_back(new Texture3D(
		"resourcefile/images/particle/FIRE.png"));
	this->particleTexs3D.push_back(new Texture3D(
		"resourcefile/images/particle/PARTICLE1.png"));
	this->particleTexs3D.push_back(new Texture3D(
		"resourcefile/images/particle/PARTICLE2.png"));
	this->particleTexs3D.push_back(new Texture3D(
		"resourcefile/images/particle/PARTICLE3.png"));

	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/PURE_RED.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/PURE_RED_HARFGREEN.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/PURE_RED_GREEN.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/PURE_HARFRED_GREEN.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/PURE_GREEN.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/PURE_GREEN_HARFBLUE.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/PURE_GREEN_BLUE.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/PURE_HARFGREEN_BLUE.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/PURE_BLUE.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/PURE_HARFRED_BLUE.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/PURE_RED_BLUE.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/PURE_RED_HARFBLUE.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/PURE_WHITE.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/PURE_BLACK.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/STONE.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/DEFAULTCHESSBOARD2.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/YELLOW.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/GROUND.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/PURPLE.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/BLUE.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/BLUE_WHITE.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/RED.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/GREEN2.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/ORANGE.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/GRID2.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/GREENBLUE.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/CHESSBOARD.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/WHITEWALL.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/GREENMARBLE.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/WHITEMARBLE.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/YELLOWMARBLE.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/YELLOWGROUNDMARBLE.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/DEFAULTCHESSBOARD.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/PURPLEMARBLE.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/BLUEMARBLE.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/REDMARBLE.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/GREEN2MARBLE.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/ORANGEMARBLE.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/GREENBLUEMARBLE.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/CHESSBOARDMARBLE.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/WHITEMAINMARBLE.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/CONCRETE.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/YELLOWCONCRETE.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/WHITECONCRETE.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/GRASS.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/WOODX.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/WOODY.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/WOODZ.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/OLDWOODX.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/OLDWOODY.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/OLDWOODZ.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/GLASS.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/GRID.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/STARS.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/STARS_SKY.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/LAVA.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/CEIL1.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/CEIL2.png"));

	this->groundTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/SAND.png"));
	this->groundTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/SNOW.png"));
	this->groundTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/ICE.png"));
	this->groundTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/GRASS.png"));
	this->groundTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/GRASS2.png"));
	this->groundTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/SOIL.png"));
	this->groundTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/GRASS3.png"));
	this->groundTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/GRASS4.png"));
	this->groundTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/SAND_SOIL.png"));
	this->groundTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/SAND_SOIL2.png"));

	for (size_t i(0); i < 10; i++)
	{
		this->groundTexs3D.push_back(this->groundTexs3D[i]);
	}

	this->deleteMap3D = new CustomTexture3D();
	this->lightMap3D = new CustomTexture3D(glm::ivec3(32,1024,64),GL_RGBA16F);

	this->textures3D[TEX_NOISE_3D]->bind(4);
	this->textures3D[TEX_STARS_FIELD_3D]->bind(5);
	this->textures3D[TEX_NORMAL_4D]->bind(6);
	this->textures3D[CAUSTICS]->bind(7);
	this->textures3D[BLEND]->bind(8);
	this->textures3D[AREA]->bind(9);
	this->lightMap3D->bind(10);

	this->deleteMap3D->bind(11);

	for (size_t i(0); i < 20; i++)
	{
		this->groundTexs3D[i]->bind(i+12);
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
	this->demoObjects4D = new Demo4D();
	this->demos4D.push_back(new Demo4D(new Wall4D("Hypercube", Hypercube(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, BOX4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new Wall4D("Hypersphere", Hypersphere(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, SPHERE4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new Wall4D("Hypercapsule", Hypercapsule(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new Wall4D("Hypercone", Hypercone(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new Wall4D("Hyperpot", Hyperpot(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new Wall4D("TriPrism", TriPrism(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new Wall4D("Hyperslope", Hyperslope(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new Wall4D("DoubleQuads4d", DoubleQuads4d(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new Wall4D("Pentachoron", Pentachoron(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new Wall4D("Pyramid4D", Pyramid4D(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new Wall4D("Hexadecachoron", Hexadecachoron(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new Wall4D("Hexacosichoron", Hexacosichoron(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));

	this->demos4D.push_back(new Demo4D(new RigidBody4D("Hypercube", Hypercube(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, BOX4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("Hypersphere", Hypersphere(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, SPHERE4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("Hypercapsule", Hypercapsule(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("Hypercylinder", Hypercylinder(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("Hypercone", Hypercone(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("Hyperpot", Hyperpot(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("TriPrism", TriPrism(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("Hyperslope", Hyperslope(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("DoubleQuads4d", DoubleQuads4d(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("Pentachoron", Pentachoron(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("Pyramid4D", Pyramid4D(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("Hexadecachoron", Hexadecachoron(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("Hexacosichoron", Hexacosichoron(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, this->buildMetalColor, this->buildColor, MESH4D, DEMOD4)));
	std::vector<Wall4D*> poolTable;
	generate_pool_table4D(glm::vec4(0.f), glm::vec4(1.27f, 1.27f, 2.54f, 1.27f), 1.f, true, WOODX, true, GRASS, true, WOODY, &poolTable, DEMOD4);
	this->demos4D.push_back(new Demo4D(poolTable));
	std::vector<RigidBody4D*> billiard4D;
	generate_billiard4D(glm::vec4(0.f), glm::vec4(),alg::bivec4(),this->buildTexture, &billiard4D, this->isGravity, glm::vec4(1.f),glm::vec4(1.f,1.f,1.f,0.f), DEMOD4);
	this->demos4D.push_back(new Demo4D(billiard4D));
	std::vector<Wall4D*> dynamite4D;
	generate_dynamite4D(glm::vec4(0.f), WHITECONCRETE, nullptr, &dynamite4D, nullptr, DEMOD4);
	this->demos4D.push_back(new Demo4D(dynamite4D));
	std::vector<RigidBody4D*> dynamite4D2;
	generate_dynamite4D(glm::vec4(0.f), this->initialVelocity, this->initialAngularVelocity, WHITECONCRETE, &dynamite4D2, nullptr, this->isGravity, DEMOD4);
	this->demos4D.push_back(new Demo4D(dynamite4D2));
	this->demos4D.push_back(new Demo4D(new Stick4D(glm::vec4(0.f), 0, new VectorIndex(0, false), this->stickLength, WHITECONCRETE, this->buildColor, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new Spring4D(glm::vec4(0.f), 0, new VectorIndex(0, false), this->springLength, this->springStrength, STONE, this->buildColor, DEMOD4)));
	this->groupAreaHypercube = new Wall4D("Hypercube", Hypercube(glm::vec4(64.f)/2.f), glm::vec4(0.f), alg::bivec4(), glm::vec4(64.f), 0, 0, false, GRID2, glm::vec4(171.f/256.f, 222.f/256.f, 105.f/256.f, 0.25f), glm::vec4(0), NONE, EMITD4);
}

void Game::startDefault()
{
	this->isRenderCoordinate4D = false;
	this->camera.update_perspective_mat(60.f, static_cast<float>(this->framebufferWidth) / this->framebufferHeight, 0.1f);
	this->blockLoadDistance = 64;
	this->objectLoadDistance = 0;
	this->isTrail4D = true;
	this->trailFadeType = LINEAR;
	this->shaders[TRAILD4]->use();
	this->shaders[TRAILD4]->set1i(LINEAR, "trailFadeType");
	this->isJointLine4D = true;
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
	this->shaders[WALLD4]->set1i(this->isSkyBoxFog, "isSkyBoxFog");
	this->shaders[SKY_BOXD4]->use();
	this->shaders[SKY_BOXD4]->set1i(this->isCloud, "isCloud");
	this->shaders[SKY_BOXD4]->set1i(this->isSkyBoxFog, "isSkyBoxFog");
	this->shaders[WATERD4]->use();
	this->shaders[WATERD4]->set1i(this->isCloud, "isCloud");
	this->shaders[WATERD4]->set1i(this->isSkyBoxFog, "isSkyBoxFog");
	this->filterType = 3;
	for (Texture3D* i : this->textures3D)i->set_filter(this->filterType);
	for (Texture3D* i : this->particleTexs3D)i->set_filter(this->filterType);
	for (Texture3D* i : this->wallTexs3D)i->set_filter(this->filterType);
	for (Texture3D* i : this->groundTexs3D)i->set_filter(this->filterType);
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
	for (size_t i(0);i < 12;i++) {
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
}

void Game::updateUniforms()
{
	//Update view matrix (camera)

	//this->shaders[OBJ]->use();
	//this->shaders[OBJ]->set_vec3f(this->camera.position4D, "cameraPos");

	this->shaders[SKY_BOXD4]->use();
	this->shaders[SKY_BOXD4]->set_mat4fv(this->camera.viewMat4D, "viewMat");
	this->shaders[SKY_BOXD4]->set_vec4f(this->camera.position4D, "cameraPos");
	this->shaders[SKY_BOXD4]->set1f(this->curTime, "iTime");

	this->shaders[WALLD4]->use();
	this->shaders[WALLD4]->set_mat4fv(this->camera.viewMat4D, "viewMat");
	this->shaders[WALLD4]->set_vec4f(this->camera.position4D, "cameraPos");
	this->shaders[WALLD4]->set1f(this->curTime, "iTime");

	if (this->mode == BUILDING) {
		this->shaders[DEMOD4]->use();
		this->shaders[DEMOD4]->set_mat4fv(this->camera.viewMat4D, "viewMat");
		this->shaders[DEMOD4]->set_vec4f(this->camera.position4D, "cameraPos");
		this->shaders[DEMOD4]->set1f(this->curTime, "iTime");
	}

	this->shaders[EMITD4]->use();
	this->shaders[EMITD4]->set_mat4fv(this->camera.viewMat4D, "viewMat");
	this->shaders[EMITD4]->set_vec4f(this->camera.position4D, "cameraPos");

	this->shaders[TERRAIND4]->use();
	this->shaders[TERRAIND4]->set_mat4fv(this->camera.viewMat4D, "viewMat");
	this->shaders[TERRAIND4]->set_vec4f(this->camera.position4D, "cameraPos");
	this->shaders[TERRAIND4]->set1f(this->curTime, "iTime");

	if (this->waters4D.size() != 0)
	{
		this->shaders[WATERD4]->use();
		this->shaders[WATERD4]->set_mat4fv(this->camera.viewMat4D, "viewMat");
		this->shaders[WATERD4]->set_vec4f(this->camera.position4D, "cameraPos");
		this->shaders[WATERD4]->set1f(this->curTime, "iTime");
	}

	this->shaders[PARTICLED4]->use();
	this->shaders[PARTICLED4]->set_mat4fv(this->camera.viewMat4D, "viewMat");
	this->shaders[PARTICLED4]->set_vec4f(this->camera.position4D, "cameraPos");

	if (this->isRenderCoordinate4D)
	{
		this->shaders[COORDNATED4]->use();
		this->shaders[COORDNATED4]->set_mat4fv(this->camera.viewMat4D, "viewMat");
	}

	this->shaders[TRAILD4]->use();
	this->shaders[TRAILD4]->set_mat4fv(this->camera.viewMat4D, "viewMat");
	this->shaders[TRAILD4]->set_vec4f(this->camera.position4D, "cameraPos");

	this->shaders[JOINT_LINED4]->use();
	this->shaders[JOINT_LINED4]->set_mat4fv(this->camera.viewMat4D, "viewMat");
	this->shaders[JOINT_LINED4]->set_vec4f(this->camera.position4D, "cameraPos");

	if (this->isFramework)
	{
		this->shaders[FRAMED4]->use();
		this->shaders[FRAMED4]->set_mat4fv(this->camera.viewMat4D, "viewMat");
		this->shaders[FRAMED4]->set_vec4f(this->camera.position4D, "cameraPos");

		this->shaders[LIGHT_FRAMED4]->use();
		this->shaders[LIGHT_FRAMED4]->set_mat4fv(this->camera.viewMat4D, "viewMat");
		this->shaders[LIGHT_FRAMED4]->set_vec4f(this->camera.position4D, "cameraPos");
	}
	this->shaders[AMBIENT_OCCLUSION]->use();
	this->shaders[AMBIENT_OCCLUSION]->set_mat4fv(this->camera.viewMat4D, "viewMat");
	this->shaders[AMBIENT_OCCLUSION]->set_vec4f(this->camera.position4D, "cameraPos");
}
void Game::startLines() 
{
	this->coordinate4D = new Coordinate4D();
}

void Game::startGui2()
{
	this->targetIcon = new Rectangle2D(SHOOTING);
}

void Game::startLevel(int level, const char* filePath)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//this->rectangle2D->render(this->textures[this->rectangle2D->textureIndex], this->shader2DShape, glm::vec2((float)this->framebufferHeight / (float)this->framebufferWidth, 1.f));
	glfwSwapBuffers(this->window);
	this->curserMode = false;
	this->editMode = false;
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	this->isCloseUI = true;
	for (Wall4D* i : this->walls4D)i = nullptr, delete i; this->walls4D.clear();
	for (RigidBody4D* i : this->rigidBodies4D)i = nullptr, delete i; this->rigidBodies4D.clear();
	for (Water4D* i : this->waters4D)i = nullptr, delete i; this->waters4D.clear();
	for (Terrain4D* i : this->terrains4D)i = nullptr, delete i; this->terrains4D.clear();
	for (DynamiteIndex* i : this->dynamiteIndices)i = nullptr, delete i; this->dynamiteIndices.clear();
	for (PointLight4D* i : this->pointLights4D)i = nullptr, delete i; this->pointLights4D.clear();
	for (Stick4D* i : this->sticks4D)i = nullptr, delete i; this->sticks4D.clear();
	for (Spring4D* i : this->springs4D)i = nullptr, delete i; this->springs4D.clear();
	for (std::vector<HingeConstraint4D*> i : this->hingeConstraintsVec)for(HingeConstraint4D* j:i)j = nullptr, delete j; this->hingeConstraintsVec.clear();
	for (Shift4D* i : this->shifts4D)i = nullptr, delete i; this->shifts4D.clear();
	for (Float4D* i : this->floats4D)i = nullptr, delete i; this->floats4D.clear();
	for (Rotate4D* i : this->rotates4D)i = nullptr, delete i; this->rotates4D.clear();
	for (OpenDoor4D* i : this->openDoors4D)i = nullptr, delete i; this->openDoors4D.clear();
	for (Emitter4D* i : this->emitters4D)i = nullptr, delete i; this->emitters4D.clear();
	this->groupIndices.clear();
	this->groupIndices.push_back(0);
	this->startObjects(level, filePath);
	this->camera.update_camera(this->rigidBodies4D[0],0.f);
	this->groupIndices = judge_groups(this->rigidBodies4D, this->groupIndices, this->groups, this->camera.position4D, this->blockLoadDistance);
	judge_objects(this->groupIndices, this->groups, this->walls4D, this->terrains4D, this->camera.position4D, this->camera.forward4D, this->camera.wDir, this->objectLoadDistance);
	update_render_indices(this->rigidBodies4D, this->groupIndices, this->groups, this->walls4D,this->sticks4D,this->springs4D, &this->renderIndices1, &this->renderIndices2, this->camera.position4D);
	sort_render_indices(&this->renderIndices1); sort_render_indices(&this->renderIndices2);
	update_collide_indices(this->rigidBodies4D, this->groupIndices, this->groups, this->walls4D);
	//for (int i = 0; i < 64; i++) { savedLevelText[i] = ''; }
	//savedLevelText[0]='L', savedLevelText[1] = 'e', savedLevelText[2]='v', savedLevelText[3]='e', savedLevelText[4]='l',savedLevelText[5]= ' ', savedLevelText[6] = (char)(this->level), savedLevelText[7]='-', savedLevelText[8] = '1',
	update_water4d(this->waters4D, this->shaders[WALLD4], this->shaders[EMITD4]);
	update_point_light4d(this->pointLights4D, this->shaders[WALLD4], this->shaders[TERRAIND4], this->shaders[LIGHT_MAPD3]);
	this->shaders[LIGHT_MAPD3]->set_vec4f(this->camera.position4D, "cameraPosShift4D");
	this->lightMap3D->bind_image(0);
	glDispatchCompute(4, 128, 4);
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
	this->shaders[WALLD4]->use();
	this->shaders[WALLD4]->set_vec4f(this->camera.position4D, "cameraPosShift4D");
	this->updateDt();
	phy::timeToSleep = 0.f;
}
void Game::judgeRender()
{
	this->judgetime1 += this->dt;
	this->judgetime3 += this->dt;

	if (this->judgetime1 > 0.13125f ) {
		judge_objects(this->groupIndices, this->groups, this->walls4D, this->terrains4D, this->camera.position4D, this->camera.forward4D, this->camera.wDir, this->objectLoadDistance);
		update_render_indices(this->rigidBodies4D, this->groupIndices, this->groups, this->walls4D, this->sticks4D, this->springs4D, &this->renderIndices1, &this->renderIndices2, this->camera.position4D);
		sort_render_indices(&this->renderIndices1); sort_render_indices(&this->renderIndices2);
		this->judgetime1 = 0.f;
	}

	if (this->judgetime3 > 0.3125 * (float)(this->blockLoadDistance)/(length(this->camera.limitedVelocity4D)+0.04f)){
		this->groupIndices = judge_groups(this->rigidBodies4D, this->groupIndices, this->groups, this->camera.position4D, this->blockLoadDistance);
		update_render_indices(this->rigidBodies4D, this->groupIndices, this->groups, this->walls4D, this->sticks4D, this->springs4D, &this->renderIndices1, &this->renderIndices2, this->camera.position4D);
		sort_render_indices(&this->renderIndices1); sort_render_indices(&this->renderIndices2);
		if (this->pointLights4D.size() > 0)
		{
			glm::vec4 cameraPosShift4D0 = ceil(this->camera.position4D / glm::vec4(64.f) - glm::vec4(0.5f)) * 64.f;
			if (this->cameraPosShift4D != cameraPosShift4D0)
			{
				this->shaders[LIGHT_MAPD3]->use();
				this->shaders[LIGHT_MAPD3]->set_vec4f(this->camera.position4D, "cameraPosShift4D");
				this->lightMap3D->bind_image(0);
				glDispatchCompute(4, 128, 4);
				glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
				this->shaders[WALLD4]->use();
				this->shaders[WALLD4]->set_vec4f(this->camera.position4D, "cameraPosShift4D");
				this->cameraPosShift4D = cameraPosShift4D0;
			}
		}
		this->judgetime3 = 0.f;
	}
}

void::Game::updateLights()
{
	for (size_t i(0); i < this->pointLights4D.size(); i++)
	{
		if (this->pointLights4D[i]->index->isValid)
		{
			RigidBody4D* a(this->rigidBodies4D[this->pointLights4D[i]->index->n]);
			if (!(a->is_static()|| a->isSleep))
			{
				this->pointLights4D[i]->set_pointlight4D_position(a->position4D, this->shaders[WALLD4]);
				this->pointLights4D[i]->set_pointlight4D_position(a->position4D, this->shaders[TERRAIND4]);
			}
		}
	}
	this->directionLight4D->update_light4D(1200.f, this->worldTime);
	this->directionLight4D->set_light4D_property(this->shaders[WALLD4]);
	this->directionLight4D->set_light4D_property(this->shaders[TERRAIND4]);
	this->directionLight4D->set_light4D_property(this->shaders[WATERD4]);
	this->directionLight4D->set_light4D_property(this->shaders[EMITD4]);
	this->directionLight4D->set_light4D_property(this->shaders[SKY_BOXD4]);
}

void::Game::updateModes(int mode,int shift)
{
	//if (shift != 0){
	if (mode != -1){
		this->mode = mode;
	}
	else{
		int modeAfter(this->mode + shift);
		if (modeAfter >= SELECTING && modeAfter <= AREA_DELETING){
			this->mode = modeAfter;
		}
		else{
			if (modeAfter < SELECTING){
				this->mode = AREA_DELETING;
			}
			else{
				this->mode = SELECTING;
			}
		}
	}
	this->targetIcon->textureIndex = this->mode;
	if (this->mode == AREA_DELETING) this->deleteMap3D->unselectArea();
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

	this->level = 1;
	this->paintScale = 5;
	this->mode = SHOOTING;
	this->shootType = 0;
	this->reflectionSteps = 6;
	this->controlType = DRAG;
	this->isHardPainting = false;
	this->isSphericalPainting = true;
	this->paintType0 = 0;
	this->paintType = 0;
	this->hittingPos4D = glm::vec4(0.f);
	this->hitIndex = new VectorIndex(0, false);
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
	this->isIlluminate = false;
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
	this->skybox4D = new Sky_Box4D("Sky4d", Hypercubecol(glm::vec4(1.f)), alg::bivec4(), glm::vec4(100000.f), SKY_BOXD4);
	this->directionLight4D = new DirectionLight4D(PARTICLE1, alg::bivec4(0.f, -90.f), glm::vec3(1.f), 0.925f);
	this->startLevel(this->level, "");
}
//Destructors
Game::~Game()
{
	glfwDestroyWindow(this->window);
	glfwTerminate();
	end_imgui();
	this->shader2DShape = nullptr,delete this->shader2DShape;
	this->rectangle2D = nullptr,delete this->rectangle2D;
	for (Shader* i : this->shaders) {i = nullptr, delete i;}
	for (Shader* i : this->shaderHDRs) { i = nullptr, delete i; }
	for (Texture* i : this->textures) { i = nullptr, delete i;}
	for (Texture* i : this->pointerTexs) { i = nullptr, delete i;}
	this->deleteMap3D = nullptr, delete this->deleteMap3D;
	this->lightMap3D = nullptr, delete this->lightMap3D;
	for (Texture3D* i : this->textures3D) { i = nullptr, delete i;}
	for (Texture3D* i : this->particleTexs3D) { i = nullptr, delete i;}
	for (Texture3D* i : this->wallTexs3D) { i = nullptr, delete i;}
	for (Texture3D* i : this->groundTexs3D) { i = nullptr, delete i;}
	for (HDRTexture* i : this->hDRTextures) { i = nullptr, delete i; }
	for (HDRTexture* i : this->bloomExpandMaps) { i = nullptr, delete i; }
	for (Sound* i : this->sounds) { i = nullptr, delete i;}
	for (Music* i : this->musics) { i = nullptr, delete i;}
	for (Object* i : this->objects) { i = nullptr, delete i;}
	this->skybox4D = nullptr,delete this->skybox4D;
	this->coordinate4D = nullptr,delete this->coordinate4D;
	this->targetIcon = nullptr,delete this->targetIcon;
	this->demoObjects4D = nullptr,delete this->demoObjects4D;
	this->groupAreaHypercube = nullptr, delete this->groupAreaHypercube;
	this->hitIndex = nullptr, delete this->hitIndex;
	this->hitObject4D = nullptr, delete this->hitObject4D;
	for (Demo4D* i : this->demos4D) { i = nullptr, delete i;}
	for (JointLine4D* i : this->dragLines4D) { i = nullptr, delete i;}
	for (XRay4D* i : this->xRays4D) { i = nullptr, delete i; }
	for (Input* i : this->inputs) { i = nullptr, delete i;}
	for (Wall4D* i : this->walls4D) { i = nullptr, delete i;}
	for (RigidBody4D* i : this->rigidBodies4D) { i = nullptr, delete i;}
	for (DynamiteIndex* i : this->dynamiteIndices) { i = nullptr, delete i; }
	for (Terrain4D* i : this->terrains4D) { i = nullptr, delete i;}
	for (Water4D* i : this->waters4D) { i = nullptr, delete i;}
	for (Group* i : this->groups) { i = nullptr, delete i;}
	for (Emitter4D* i : this->emitters4D) { i = nullptr, delete i;}
	for (std::vector<Constraint*> i : constraintsVec)for (Constraint* j : i) { j = nullptr, delete j; }
	for (RenderIndex* i : this->renderIndices1) { i = nullptr, delete i;}
	for (RenderIndex* i : this->renderIndices2) { i = nullptr, delete i;}
	for (PointLight* i : this->pointLights) { i = nullptr, delete i;}
	for (DirectionLight* i : this->directionLights) { i = nullptr, delete i;}
	for (PointLight4D* i : this->pointLights4D) { i = nullptr, delete i;}
	this->directionLight4D = nullptr,delete this->directionLight4D;
	for (Stick4D* i : this->sticks4D) { i = nullptr, delete i;}
	for (Spring4D* i : this->springs4D) { i = nullptr, delete i;}
	for (std::vector<HingeConstraint4D*> i : hingeConstraintsVec)for (HingeConstraint4D* j : i) { j = nullptr, delete j; }
	for (Shift4D* i : this->shifts4D) { i = nullptr, delete i;}
	for (Float4D* i : this->floats4D) { i = nullptr, delete i;}
	for (Rotate4D* i : this->rotates4D) { i = nullptr, delete i;}
	for (OpenDoor4D* i : this->openDoors4D) { i = nullptr, delete i; }
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
	if (!this->curserMode) {
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
		phy::before_render_physic4D(this->rigidBodies4D, this->groups, this->walls4D,this->sticks4D, this->springs4D,this->isTrail4D, 1.f/60.f,this->curTime);
	}
	if (this->mode == BUILDING)
	{
		//if (fixedUpdate::is_fixed_update2(this->dt, 1.f / 30.f))
		{
			this->demoObjects4D->clear();
			if (this->isFindPoint) {
				switch (this->buildMode)
				{
				case BUILD_OBJECT:
				{
					switch (this->buildCol)
					{
					case HYPERCUBE: { this->demoObjects4D->walls4D.push_back(this->demos4D[0]->walls4D[0]); break; }
					case HYPERSPHERE: { this->demoObjects4D->walls4D.push_back(this->demos4D[1]->walls4D[0]); break; }
					case HYPERCAPSULE: { this->demoObjects4D->walls4D.push_back(this->demos4D[2]->walls4D[0]); break; }
					case HYPERCYLINDER: { this->demoObjects4D->walls4D.push_back(this->demos4D[3]->walls4D[0]); break; }
					case HYPERCONE: { this->demoObjects4D->walls4D.push_back(this->demos4D[4]->walls4D[0]); break; }
					case HYPERPOT: { this->demoObjects4D->walls4D.push_back(this->demos4D[5]->walls4D[0]); break; }
					case TRIPRISM: { this->demoObjects4D->walls4D.push_back(this->demos4D[6]->walls4D[0]); break; }
					case HYPERSLOPE: { this->demoObjects4D->walls4D.push_back(this->demos4D[7]->walls4D[0]); break; }
					case HYPERQUAD: { this->demoObjects4D->walls4D.push_back(this->demos4D[8]->walls4D[0]); break; }
					case PENTACHORON: { this->demoObjects4D->walls4D.push_back(this->demos4D[9]->walls4D[0]); break; }
					case HYPERPYRAMID: { this->demoObjects4D->walls4D.push_back(this->demos4D[10]->walls4D[0]); break; }
					case HEXADECACHORON: { this->demoObjects4D->walls4D.push_back(this->demos4D[11]->walls4D[0]); break; }
					case HEXACOSICHORON: { this->demoObjects4D->walls4D.push_back(this->demos4D[12]->walls4D[0]); break; }
					}
					//alg::rotor4 rot = obj->rotation4D;
					this->demoObjects4D->walls4D[0]->set_position4D(hitObject4D == nullptr ? get_cap_position4D(this->hittingPos4D + this->buildScale.y * this->hitNormal / 2.f, this->buildDistance, this->buildOffset) : get_cap_position4D(hitObject4D, isFindPoint, this->hittingPos4D + this->buildScale.y * this->hitNormal / 2.f, this->buildDistance, this->buildOffset));
					this->demoObjects4D->walls4D[0]->set_rotation4D(hitObject4D == nullptr ? alg::rotor4() : update(hitObject4D->rotation4D, this->buildRotation*glm::radians(1.f)));
					this->demoObjects4D->walls4D[0]->set_scale4D(this->buildScale);
					break;
				}
				case BUILD_RIGIDBODY:
				{
					switch (this->buildCol)
					{
					case HYPERCUBE: { this->demoObjects4D->rigidBodies4D.push_back(this->demos4D[13]->rigidBodies4D[0]); break; }
					case HYPERSPHERE: { this->demoObjects4D->rigidBodies4D.push_back(this->demos4D[14]->rigidBodies4D[0]); break; }
					case HYPERCAPSULE: { this->demoObjects4D->rigidBodies4D.push_back(this->demos4D[15]->rigidBodies4D[0]); break; }
					case HYPERCYLINDER: { this->demoObjects4D->rigidBodies4D.push_back(this->demos4D[16]->rigidBodies4D[0]); break; }
					case HYPERCONE: { this->demoObjects4D->rigidBodies4D.push_back(this->demos4D[17]->rigidBodies4D[0]); break; }
					case HYPERPOT: { this->demoObjects4D->rigidBodies4D.push_back(this->demos4D[18]->rigidBodies4D[0]); break; }
					case TRIPRISM: { this->demoObjects4D->rigidBodies4D.push_back(this->demos4D[19]->rigidBodies4D[0]); break; }
					case HYPERSLOPE: { this->demoObjects4D->rigidBodies4D.push_back(this->demos4D[20]->rigidBodies4D[0]); break; }
					case HYPERQUAD: { this->demoObjects4D->rigidBodies4D.push_back(this->demos4D[21]->rigidBodies4D[0]); break; }
					case PENTACHORON: { this->demoObjects4D->rigidBodies4D.push_back(this->demos4D[22]->rigidBodies4D[0]); break; }
					case HYPERPYRAMID: { this->demoObjects4D->rigidBodies4D.push_back(this->demos4D[23]->rigidBodies4D[0]); break; }
					case HEXADECACHORON: { this->demoObjects4D->rigidBodies4D.push_back(this->demos4D[24]->rigidBodies4D[0]); break; }
					case HEXACOSICHORON: { this->demoObjects4D->rigidBodies4D.push_back(this->demos4D[25]->rigidBodies4D[0]); break; }
					}
					this->demoObjects4D->rigidBodies4D[0]->set_position4D(this->hittingPos4D + this->buildScale.y * this->hitNormal/2.f);
					this->demoObjects4D->rigidBodies4D[0]->set_rotation4D(look_at(glm::vec4(0.f), this->hitNormal, rotate(this->buildRotation,glm::vec4(0.f, 1.f, 0.f, 0.f))));
					this->demoObjects4D->rigidBodies4D[0]->set_scale4D(this->buildScale);
					break;
				}
				case BUILD_POOL_TABLE:
				{
					for (size_t i = 0; i < this->demos4D[26]->walls4D.size(); i++)
					{
						this->demoObjects4D->walls4D.push_back(this->demos4D[26]->walls4D[i]);
						this->demoObjects4D->walls4D[i]->set_mesh_position4D(this->demos4D[26]->walls4D[i]->position4D + get_cap_position4D(this->hittingPos4D, this->buildDistance, this->buildOffset));
					}
					break;
				}
				case BUILD_BILLIARD:
				{
					this->demoObjects4D->rigidBodies4D = this->demos4D[27]->rigidBodies4D;
					for (size_t i(0); i < this->demoObjects4D->rigidBodies4D.size(); i++)
					{
						this->demoObjects4D->rigidBodies4D[i]->set_mesh_position4D(this->demos4D[27]->rigidBodies4D[i]->position4D + this->hittingPos4D + glm::vec4(0.f, 0.0525f / 2.f, 0.f, 0.f));
					}
					break;
				}
				case BUILD_DYNAMITE:
				{
					if (this->isRigidBody)
					{
						this->demoObjects4D->rigidBodies4D = this->demos4D[29]->rigidBodies4D;
						for (size_t i(0); i < this->demoObjects4D->rigidBodies4D.size(); i++)
						{
							this->demoObjects4D->rigidBodies4D[i]->set_mesh_position4D(this->demos4D[29]->rigidBodies4D[i]->position4D + this->hittingPos4D);
						}
					}
					else
					{
						this->demoObjects4D->walls4D = this->demos4D[28]->walls4D;
						for (size_t i(0); i < this->demoObjects4D->walls4D.size(); i++)
						{
							this->demoObjects4D->walls4D[i]->set_mesh_position4D(this->demos4D[28]->walls4D[i]->position4D + this->hittingPos4D);
						}
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
						bool isInitial(true);
						if (this->springs4D.size() != 0)
						{
							if (!this->springs4D[this->springs4D.size() - 1]->index2->isValid)
							{
								isInitial = false;
								this->demoObjects4D->spring4D = this->demos4D[31]->spring4D;
								this->demoObjects4D->spring4D->fixPoint4D = this->camera.frontPosition4D;
								this->demoObjects4D->spring4D->index1 = this->springs4D[this->springs4D.size() - 1]->index1;
								*this->demoObjects4D->spring4D->index2 = this->springs4D[this->springs4D.size() - 1]->index1 == this->hitIndex->n ? VectorIndex(0,false) : VectorIndex(this->hitIndex->n, true);
								if (this->demoObjects4D->spring4D != nullptr)
									phy::update_spring4D(this->rigidBodies4D, this->walls4D, this->demoObjects4D->spring4D);
							}
						}
						if (isInitial)
						{
							if (this->sticks4D.size() == 0)
							{
								this->demoObjects4D->stick4D = this->demos4D[30]->stick4D;
								this->demoObjects4D->stick4D->fixPoint4D = this->camera.frontPosition4D;
								this->demoObjects4D->stick4D->index1 = this->hitIndex->n;
								this->demoObjects4D->stick4D->index2->isValid = false;
								this->demoObjects4D->stick4D->set_stick_length(this->stickLength);
							}
							else if (this->sticks4D.size() != 0)
							{
								if (!this->sticks4D[this->sticks4D.size() - 1]->index2->isValid)
								{
									this->demoObjects4D->stick4D = this->demos4D[30]->stick4D;
									this->demoObjects4D->stick4D->fixPoint4D = this->camera.frontPosition4D;
									this->demoObjects4D->stick4D->index1 = this->sticks4D[this->sticks4D.size() - 1]->index1;
									*this->demoObjects4D->stick4D->index2 = this->sticks4D[this->sticks4D.size() - 1]->index1 == this->hitIndex->n ? VectorIndex(0,false) : VectorIndex(this->hitIndex->n, true);
									this->demoObjects4D->stick4D->set_stick_length(this->stickLength);
								}
								else if (this->sticks4D[this->sticks4D.size() - 1]->index2->isValid)
								{
									this->demoObjects4D->stick4D = this->demos4D[30]->stick4D;
									this->demoObjects4D->stick4D->fixPoint4D = this->camera.frontPosition4D;
									this->demoObjects4D->stick4D->index1 = this->hitIndex->n;
									this->demoObjects4D->stick4D->index2->isValid = false;
									this->demoObjects4D->stick4D->set_stick_length(this->stickLength);
								}
							}
							if (this->demoObjects4D->stick4D != nullptr)
								phy::update_stick4D(this->rigidBodies4D, this->walls4D, this->demoObjects4D->stick4D);
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
							bool isInitial(true);
							if (this->sticks4D.size() != 0)
							{
								if (!this->sticks4D[this->sticks4D.size() - 1]->index2->isValid)
								{
									isInitial = false;
									this->demoObjects4D->stick4D = this->demos4D[30]->stick4D;
									this->demoObjects4D->stick4D->fixPoint4D = this->camera.frontPosition4D;
									this->demoObjects4D->stick4D->index1 = this->sticks4D[this->sticks4D.size() - 1]->index1;
									*this->demoObjects4D->stick4D->index2 = this->sticks4D[this->sticks4D.size() - 1]->index1 == this->hitIndex->n ? VectorIndex(0.f,false) : VectorIndex(this->hitIndex->n, true);
									this->demoObjects4D->stick4D->set_stick_length(this->stickLength);
									if (this->demoObjects4D->stick4D != nullptr)
										phy::update_stick4D(this->rigidBodies4D, this->walls4D, this->demoObjects4D->stick4D);
								}
							}
							if (isInitial)
							{
								if (this->springs4D.size() == 0)
								{
									this->demoObjects4D->spring4D = this->demos4D[31]->spring4D;
									this->demoObjects4D->spring4D->fixPoint4D = this->camera.frontPosition4D;
									this->demoObjects4D->spring4D->index1 = this->hitIndex->n;
									this->demoObjects4D->spring4D->index2->isValid = false;
								}
								else if (this->springs4D.size() != 0)
								{
									if (!this->springs4D[this->springs4D.size() - 1]->index2->isValid)
									{
										this->demoObjects4D->spring4D = this->demos4D[31]->spring4D;
										this->demoObjects4D->spring4D->fixPoint4D = this->camera.frontPosition4D;
										this->demoObjects4D->spring4D->index1 = this->springs4D[this->springs4D.size() - 1]->index1;
										*this->demoObjects4D->spring4D->index2 = this->springs4D[this->springs4D.size() - 1]->index1 == this->hitIndex->n ? VectorIndex(0,false) : VectorIndex(this->hitIndex->n,true);
									}
									else if (this->springs4D[this->springs4D.size() - 1]->index2->isValid)
									{
										this->demoObjects4D->spring4D = this->demos4D[31]->spring4D;
										this->demoObjects4D->spring4D->fixPoint4D = this->camera.frontPosition4D;
										this->demoObjects4D->spring4D->index1 = this->hitIndex->n;
										this->demoObjects4D->spring4D->index2->isValid = false;
									}
								}
								if (this->demoObjects4D->spring4D != nullptr)
									phy::update_spring4D(this->rigidBodies4D, this->walls4D, this->demoObjects4D->spring4D);
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
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//for (Object* i : this->objects){i->render(this->shaders[OBJ]);}
	//1:OBJS NOT TRANSPARENT
	glLineWidth(1.f);

	for (size_t index(0); index < this->renderIndices1.size(); index++)
	{
		RenderIndex* i(this->renderIndices1[index]);
        if (i->type == 0)
		{
			RigidBody4D* a(this->rigidBodies4D[i->objectIndex]);
			a->render(this->wallTexs3D[a->texture3DIndex], this->shaders[a->shaderIndex]);
		}
		else if (i->type == 1)
		{
			Wall4D* a(this->walls4D[i->objectIndex]);
			a->render(this->wallTexs3D[a->texture3DIndex], this->shaders[a->shaderIndex]);
		}
		else if (i->type == 2)
		{
			if (i->objectIndex < this->sticks4D.size())
			{
				Stick4D* stick4D(this->sticks4D[i->objectIndex]);
				stick4D->render(this->wallTexs3D[stick4D->texture3DIndex], this->shaders[stick4D->shaderIndex]);
			}
			else
			{
				Spring4D* springs4D(this->springs4D[i->objectIndex - this->sticks4D.size()]);
				springs4D->render(this->wallTexs3D[springs4D->texture3DIndex], this->shaders[springs4D->shaderIndex]);
			}
		}
	}
	for (Group* i : this->groups) {
		if (i->isRender) {
			for (size_t terrain4DIndex : i->terrains4DIndices)
			{       
				Terrain4D* t(this->terrains4D[terrain4DIndex]);
				if (t->isClamp && t->isFront) {
					t->render(this->shaders[t->shaderIndex]);
				}
			}
		}
	}

	if (this->isFramework)
	{
		for (Group* i : this->groups) {
			if (i->isRender) {
				for (size_t wall4DIndex : i->walls4DIndices)
				{
					Wall4D* w(this->walls4D[wall4DIndex]);
					if (w->isFront) {
						w->render_frame(this->shaders[FRAMED4]);
					}
				}
			}
		}
		for (RigidBody4D* j : this->rigidBodies4D) {
			j->render_frame(this->shaders[FRAMED4]);
		}
		for (Stick4D* i : this->sticks4D)
		{
			if (i->index2->isValid)
			{
				i->render_frame(this->shaders[FRAMED4]);
			}
		}
		for (Spring4D* i : this->springs4D)
		{
			if (i->index2->isValid)
			{
				i->render_frame(this->shaders[FRAMED4]);
			}
		}
		if (this->mode == BUILDING) {
			if (!(this->buildMode == BUILD_STICK || this->buildMode == BUILD_SPRING))
			{
				if (this->isFindPoint) {
					for (Wall4D* j : this->demoObjects4D->walls4D)
					{
						j->render_frame(this->shaders[FRAMED4]);
					}
					for (RigidBody4D* j : this->demoObjects4D->rigidBodies4D)
					{
						j->render_frame(this->shaders[FRAMED4]);
					}
				}
			}
			else
			{
				if (this->demoObjects4D->stick4D != nullptr)
				{
					this->demoObjects4D->stick4D->render_frame(this->shaders[FRAMED4]);
				}
				if (this->demoObjects4D->spring4D != nullptr)
				{
					this->demoObjects4D->spring4D->render_frame(this->shaders[FRAMED4]);
				}
			}
		}
		if (this->isShowingGroupArea) {
			for (size_t i(1); i < this->groupIndices.size(); i++)
			{
				Group* group(this->groups[this->groupIndices[i]]);
				this->groupAreaHypercube->set_mesh_position4D(group->position4D);
				this->groupAreaHypercube->render_frame(this->shaders[FRAMED4]);
			}
		}
		glLineWidth(1.9f);
		for (Emitter4D* i : this->emitters4D)
		{
			for (Particle4D0* j : i->particles4D)
			{
				if (j->isGlowing) { glBlendFunc(GL_SRC_ALPHA, GL_ONE); }
				else { glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); }
				j->render_frame(this->shaders[LIGHT_FRAMED4]);
			}
		}
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		for (PointLight4D* p : this->pointLights4D) {
			p->render_frame(this->shaders[LIGHT_FRAMED4]);
		}
		this->directionLight4D->render_frame(this->shaders[LIGHT_FRAMED4]);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	glLineWidth(1.9f);
	if (isJointLine4D)
	{
		for (Stick4D* i : this->sticks4D)
		{
			if (i->index2->isValid)
			{
				i->render_line4D(this->shaders[JOINT_LINED4]);
			}
		}
		for (Spring4D* i : this->springs4D)
		{
			if (i->index2->isValid)
			{
				i->render_line4D(this->shaders[JOINT_LINED4]);
			}
		}
		if (this->mode == BUILDING) {
			if (this->buildMode == BUILD_STICK || this->buildMode == BUILD_SPRING)
			{
				if (this->demoObjects4D->stick4D != nullptr)
				{
					this->demoObjects4D->stick4D->render_line4D(this->shaders[JOINT_LINED4]);
				}
				if (this->demoObjects4D->spring4D != nullptr)
				{
					this->demoObjects4D->spring4D->render_line4D(this->shaders[JOINT_LINED4]);
				}
			}
		}
	}
	//
	//2:SKY BOX
	this->skybox4D->render(this->shaders[this->skybox4D->shaderIndex]);
	//
	//3:PARTICLES
	glDepthMask(false);
	for (Emitter4D* i : this->emitters4D)
	{
		for (Particle4D0* j : i->particles4D)
		{
			if (j->isGlowing) glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			else glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			j->render(this->particleTexs3D[j->texture3Dindex],this->shaders[PARTICLED4]);
		}
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	for (PointLight4D* p : this->pointLights4D) {
		p->render(this->particleTexs3D[p->texture3DIndex], this->shaders[PARTICLED4]);
	}

	glDepthMask(true);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (JointLine4D* i : this->dragLines4D)
	{
		i->render(this->shaders[JOINT_LINED4]);
	}
	for (XRay4D* i : this->xRays4D)
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
	glDisable(GL_CULL_FACE);
	for (int index(this->renderIndices2.size() - 1); index >= 0; index--)
	{
		RenderIndex* i(this->renderIndices2[index]);
		if (i->type == 0)
		{
			RigidBody4D* a(this->rigidBodies4D[i->objectIndex]);
			a->render(this->wallTexs3D[a->texture3DIndex], this->shaders[a->shaderIndex]);
		}
		else if (i->type == 1)
		{
			Wall4D* a(this->walls4D[i->objectIndex]);
			a->render(this->wallTexs3D[a->texture3DIndex], this->shaders[a->shaderIndex]);
		}
		else if (i->type == 2)
		{
			if (i->objectIndex < this->sticks4D.size())
			{
				Stick4D* stick4D(this->sticks4D[i->objectIndex]);
				stick4D->render(this->wallTexs3D[stick4D->texture3DIndex], this->shaders[stick4D->shaderIndex]);
			}
			else
			{
				Spring4D* springs4D(this->springs4D[i->objectIndex - this->sticks4D.size()]);
				springs4D->render(this->wallTexs3D[springs4D->texture3DIndex], this->shaders[springs4D->shaderIndex]);
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
				for (Wall4D* a : this->demoObjects4D->walls4D)
				{
					a->render(this->wallTexs3D[a->texture3DIndex], this->shaders[a->shaderIndex]);
				}
				for (RigidBody4D* a : this->demoObjects4D->rigidBodies4D)
				{
					a->render(this->wallTexs3D[a->texture3DIndex], this->shaders[a->shaderIndex]);
				}
			}
		}
		else
		{
			if (this->demoObjects4D->stick4D != nullptr)
			{
				this->demoObjects4D->stick4D->render(this->wallTexs3D[this->demoObjects4D->stick4D->texture3DIndex], this->shaders[this->demoObjects4D->stick4D->shaderIndex]);
			}
			if (this->demoObjects4D->spring4D != nullptr)
			{
				this->demoObjects4D->spring4D->render(this->wallTexs3D[this->demoObjects4D->spring4D->texture3DIndex], this->shaders[this->demoObjects4D->spring4D->shaderIndex]);
			}
		}
	}
	glDisable(GL_CULL_FACE);
	glDepthMask(false);
	if (this->isShowingGroupArea) {
		for (size_t i(1); i < this->groupIndices.size(); i++)
		{
			Group* group(this->groups[this->groupIndices[i]]);
			this->groupAreaHypercube->set_mesh_position4D(group->position4D);
			this->groupAreaHypercube->render(this->wallTexs3D[this->groupAreaHypercube->texture3DIndex], this->shaders[this->groupAreaHypercube->shaderIndex]);
		}
	}
	glDepthMask(true);
	glEnable(GL_CULL_FACE);
	if (this->isTrail4D) {
		//glLineWidth(4.9f);
		for (RigidBody4D* i : this->rigidBodies4D)
		{
			i->trail4D->render(this->shaders[TRAILD4]);
		}
		//glLineWidth(1.9f);
	}
	glDisable(GL_CULL_FACE);
	for (Water4D* a : this->waters4D) {
		a->render(this->shaders[a->shaderIndex]);
	}
	glEnable(GL_CULL_FACE);
	//glDepthFunc(GL_LESS);
	//glDepthMask(true);
	//
	//5:LENS FLARE
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	if (ray::is_in_screen(this->directionLight4D->direction4D, camera.viewMat4D, camera.projectionMat))
	{
		glm::vec4 hitPosNear2;
		glm::vec4 hitPosNormal2;
		if (!ray::detect_object4d_index(nullptr, this->rigidBodies4D, this->groupIndices, this->groups, this->walls4D, this->terrains4D, this->sticks4D, this->springs4D, true, true, false, true, this->camera.position4D, -this->directionLight4D->direction4D, this->directionLight4D->right4D, &hitPosNear2, &hitPosNormal2))
		{
			glDepthMask(false);
			this->directionLight4D->render_lens_flare(this->camera.forward4D, this->particleTexs3D[this->directionLight4D->texture3DIndex],this->particleTexs3D[PARTICLE2], this->shaders[PARTICLED4]);
			glDepthMask(true);
		}	
	}
	//
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (this->isHDR)
	{
		this->hdrQuad->set_is_fetched(this->shader2DShape,true);
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
		this->hdrQuad->set_is_fetched(this->shader2DShape, false);
	}
	//6:GUI
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth(1.9f);
	if (this->isRenderCoordinate4D){
		//this->coordinate4D->update(this->camera.forward4D,0);
		this->coordinate4D->render(this->shaders[COORDNATED4]);
	}

	if (!this->curserMode) {
		glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_COLOR);
		this->targetIcon->render(this->pointerTexs[this->mode],this->shader2DShape, (32.f/ (float)this->framebufferHeight)*glm::vec2((float)this->framebufferHeight / (float)this->framebufferWidth, 1.f));
	}

	if (this->curserMode) {
		imgui_use();
	}
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