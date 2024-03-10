//#include"Openfile.h"
#include"Game_imgui.h"
#include"OpenglOptions.h"
#include"StartObj.h"
#include"Collider.h"
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
	glfwSetWindowMonitor(this->window, NULL, 0, 45, this->WINDOW_WIDTH, this->WINDOW_HEIGHT, GLFW_DONT_CARE);
	this->icons[0].pixels = SOIL_load_image("resourcefile/images/icon1-1.png", &icons[0].width, &icons[0].height, 0, SOIL_LOAD_RGBA);
	this->icons[1].pixels = SOIL_load_image("resourcefile/images/icon1-2.png", &icons[1].width, &icons[1].height, 0, SOIL_LOAD_RGBA);
	this->icons[2].pixels = SOIL_load_image("resourcefile/images/icon1-3.png", &icons[2].width, &icons[2].height, 0, SOIL_LOAD_RGBA);
	this->icons[3].pixels = SOIL_load_image("resourcefile/images/icon1-4.png", &icons[3].width, &icons[3].height, 0, SOIL_LOAD_RGBA);
	glfwSetWindowIcon(this->window, 4, icons);
	SOIL_free_image_data(icons[0].pixels);
	SOIL_free_image_data(icons[1].pixels);
	SOIL_free_image_data(icons[2].pixels);
	SOIL_free_image_data(icons[3].pixels);

	if (this->window == nullptr)
	{
		std::cout << "ERROR::GLFW_WINDOW_INIT_FAILED" << "\n";
		glfwTerminate();
	}
	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);
	//IMPORTANT WHITH PERSPECTIVE MATRIX!!!
	glfwMakeContextCurrent(this->window); //IMPORTANT!!
	this->vsync = 1;
	glfwSwapInterval(this->vsync); // Enable vsync
	start_imgui(this->window);

	glClearColor(0.15f, 0.5f, 0.85f, 1.f);
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
	this->shader_2D_Shape = new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,"resourcefile/shaders/shape2D.vertex", "resourcefile/shaders/shape2D.fragment");
	this->shader_2D_Shape->use();
	this->shader_2D_Shape->setVec2f(glm::vec2((float)this->framebufferHeight / (float)this->framebufferWidth, 1.f), "scale2D");
	this->textures.push_back(new Texture("resourcefile/images/logo.png"));
	this->rectangle2D = new Rectangle2D(this->textures[0]);
	this->rectangle2D->render(this->shader_2D_Shape);
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
		"resourcefile/shaders/obj4D.vertex", "resourcefile/shaders/water4D.fragment"));
	this->shaders.push_back(new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		"resourcefile/shaders/particle4D.vertex", "resourcefile/shaders/particle4D.fragment"));
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
}

void Game::startMatrices()
{
	this->updateProjectMat();
}

void Game::startTextures()
{
	this->textures.push_back(new Texture("resourcefile/images/maps/VERTEX_MAP4D.png"));
	char ss[256];
	for (int i = 1; i <= 10; i++)
	{
		snprintf(ss, 255, "resourcefile/images/2d/i1-%i.png", i);
		this->textures.push_back(new Texture(ss));
	}
	for (int i = 1; i <= 54; i++)
	{
		snprintf(ss, 255, "resourcefile/images/2d/i2-%i.png", i);
		this->textures.push_back(new Texture(ss));
	}
	for (int i = 1; i <= 7; i++)
	{
		snprintf(ss, 255, "resourcefile/images/2d/i3-%i.png", i);
		this->textures.push_back(new Texture(ss));
	}
	this->pointerTexs.push_back(new Texture("resourcefile/images/gui/target pointer.png"));
	this->pointerTexs.push_back(new Texture("resourcefile/images/gui/control pointer.png"));
	this->pointerTexs.push_back(new Texture("resourcefile/images/gui/paint pointer.png"));
	this->pointerTexs.push_back(new Texture("resourcefile/images/gui/build pointer.png"));
	this->pointerTexs.push_back(new Texture("resourcefile/images/gui/delete pointer.png"));
	this->pointerTexs.push_back(new Texture("resourcefile/images/gui/area delete pointer.png"));
	this->textures[1]->bind(2);

	this->textures3D.push_back(new Texture3D("resourcefile/images/noise.png"));
	this->textures3D.push_back(new Texture3D("resourcefile/images/sky_panorama/3dstars_field.png"));
	this->textures3D.push_back(new Texture3D("resourcefile/images/maps/NOISE_NORMAL4D.png"));
	this->textures3D.push_back(new Texture3D("resourcefile/images/animation/caustics.png"));
	this->textures3D.push_back(new Texture3D("resourcefile/images/maps/BLEND.png"));
	this->textures3D.push_back(new Texture3D("resourcefile/images/maps/AREA.png"));

	this->particleTexs3D.push_back(new Texture3D("resourcefile/images/particle/PARTICLE1.png"));
	this->particleTexs3D.push_back(new Texture3D("resourcefile/images/particle/FIRE.png"));
	this->particleTexs3D.push_back(new Texture3D("resourcefile/images/particle/PARTICLE3.png"));

	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/PURE_RED.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/PURE_RED_HARFGREEN.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/PURE_RED_GREEN.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/PURE_HARFRED_GREEN.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/PURE_GREEN.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/PURE_GREEN_HARFBLUE.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/PURE_GREEN_BLUE.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/PURE_HARFGREEN_BLUE.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/PURE_BLUE.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/PURE_HARFRED_BLUE.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/PURE_RED_BLUE.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/PURE_RED_HARFBLUE.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/PURE_WHITE.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/PURE_BLACK.png"));

	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/GREEN.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/WHITE.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/YELLOW.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/GROUND.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/PURPLE.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/BLUE.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/BLUE_WHITE.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/RED.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/GREEN2.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/ORANGE.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/ORANGE_WHITE.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/GREENBLUE.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/CHESSBOARD.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/WHITEWALL.png"));

	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/GREENMARBLE.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/WHITEMARBLE.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/YELLOWMARBLE.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/YELLOWGROUNDMARBLE.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/ROCK1.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/PURPLEMARBLE.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/BLUEMARBLE.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/REDMARBLE.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/GREEN2MARBLE.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/ORANGEMARBLE.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/GREENBLUEMARBLE.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/CHESSBOARDMARBLE.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/WHITEMAINMARBLE.png"));

	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/CONCRETE.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/YELLOWCONCRETE.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/WHITECONCRETE.png"));

	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/GRASS.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/WOODX.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/WOODY.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/WOODZ.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/GLASS.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/GRID.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/STARS.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/STARS_SKY.png"));

	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/CEIL1.png"));
	this->wallTexs3D.push_back(new Texture3D("resourcefile/images/texture/CEIL2.png"));

	this->groundTexs3D.push_back(new Texture3D("resourcefile/images/texture/SAND.png"));
	this->groundTexs3D.push_back(new Texture3D("resourcefile/images/texture/SNOW.png"));
	this->groundTexs3D.push_back(new Texture3D("resourcefile/images/texture/ICE.png"));
	this->groundTexs3D.push_back(new Texture3D("resourcefile/images/texture/GRASS.png"));
	this->groundTexs3D.push_back(new Texture3D("resourcefile/images/texture/GRASS2.png"));
	this->groundTexs3D.push_back(new Texture3D("resourcefile/images/texture/SOIL.png"));
	this->groundTexs3D.push_back(new Texture3D("resourcefile/images/texture/GRASS3.png"));
	this->groundTexs3D.push_back(new Texture3D("resourcefile/images/texture/GRASS4.png"));
	this->groundTexs3D.push_back(new Texture3D("resourcefile/images/texture/SAND_SOIL.png"));
	this->groundTexs3D.push_back(new Texture3D("resourcefile/images/texture/SAND_SOIL2.png"));

	for (int i = 0; i < 10; i++)
	{
		this->groundTexs3D.push_back(this->groundTexs3D[i]);
	}

	this->deleteMap3D = new DeleteMap3D();

	this->textures3D[TEX_NOISE_3D]->bind(3);
	this->textures3D[TEX_STARS_FIELD_3D]->bind(4);
	this->textures3D[TEX_NORMAL_4D]->bind(5);
	this->textures3D[CAUSTICS]->bind(6);
	this->textures3D[BLEND]->bind(7);
	this->textures3D[AREA]->bind(8);

	this->wallTexs3D[GLASS]->isTransparent = true;
	this->wallTexs3D[GRID]->isTransparent = true;

	this->deleteMap3D->bind(9);

	for (int i = 0; i < 20; i++)
	{
		this->groundTexs3D[i]->bind(i+10);
	}
}

void Game::startSounds()
{
	this->sounds.push_back(new Sound("resourcefile/sounds/sounds/explosion-1.wav"));//0
	this->sounds.push_back(new Sound("resourcefile/sounds/sounds/explosion-2.wav"));
	this->sounds.push_back(new Sound("resourcefile/sounds/sounds/explosion-3.wav"));
	this->sounds.push_back(new Sound("resourcefile/sounds/sounds/explosion-4.wav"));
	this->sounds.push_back(new Sound("resourcefile/sounds/sounds/gun-shot-1.wav"));
	this->sounds.push_back(new Sound("resourcefile/sounds/sounds/gun-shot-2.mp3"));//5
	this->sounds.push_back(new Sound("resourcefile/sounds/sounds/collide-1.mp3"));
	this->sounds.push_back(new Sound("resourcefile/sounds/sounds/place-0.mp3"));
	this->sounds.push_back(new Sound("resourcefile/sounds/sounds/glass-breaking-2.mp3"));
	this->musics.push_back(new Music("resourcefile/sounds/musics/Stellardrone - Rendezvous With Rama [mqms2].ogg"));
	this->musics.push_back(new Music("resourcefile/sounds/musics/Stellardrone - Eternity [mqms2].ogg"));
	this->musics.push_back(new Music("resourcefile/sounds/musics/Stellardrone - Cepheid [mqms2].ogg"));
}

void Game::startDemos()
{
	this->demoObjects4D = new Demo4D();
	this->demos4D.push_back(new Demo4D(new Wall4D("Hypercube", Hypercube(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->wallTexs3D[this->buildTexture], 0.f, this->buildColor, BOX4D, this->shaders[DEMOD4])));
	this->demos4D.push_back(new Demo4D(new Wall4D("Hypersphere", Hypersphere(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->wallTexs3D[this->buildTexture], 0.f, this->buildColor, SPHERE4D, this->shaders[DEMOD4])));
	this->demos4D.push_back(new Demo4D(new Wall4D("Hypercapsule", Hypercapsule(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->wallTexs3D[this->buildTexture], 0.f, this->buildColor, MESH4D, this->shaders[DEMOD4])));
	this->demos4D.push_back(new Demo4D(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->wallTexs3D[this->buildTexture], 0.f, this->buildColor, MESH4D, this->shaders[DEMOD4])));
	this->demos4D.push_back(new Demo4D(new Wall4D("Hypercone", Hypercone(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->wallTexs3D[this->buildTexture], 0.f, this->buildColor, MESH4D, this->shaders[DEMOD4])));
	this->demos4D.push_back(new Demo4D(new Wall4D("Hyperpot", Hyperpot(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->wallTexs3D[this->buildTexture], 0.f, this->buildColor, MESH4D, this->shaders[DEMOD4])));
	this->demos4D.push_back(new Demo4D(new Wall4D("TriPrism", TriPrism(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->wallTexs3D[this->buildTexture], 0.f, this->buildColor, MESH4D, this->shaders[DEMOD4])));
	this->demos4D.push_back(new Demo4D(new Wall4D("Hyperslope", Hyperslope(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->wallTexs3D[this->buildTexture], 0.f, this->buildColor, MESH4D, this->shaders[DEMOD4])));
	this->demos4D.push_back(new Demo4D(new Wall4D("DoubleQuads4d", DoubleQuads4d(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->wallTexs3D[this->buildTexture], 0.f, this->buildColor, MESH4D, this->shaders[DEMOD4])));
	this->demos4D.push_back(new Demo4D(new Wall4D("Pentachoron", Pentachoron(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->wallTexs3D[this->buildTexture], 0.f, this->buildColor, MESH4D, this->shaders[DEMOD4])));
	this->demos4D.push_back(new Demo4D(new Wall4D("Pyramid4D", Pyramid4D(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->wallTexs3D[this->buildTexture], 0.f, this->buildColor, MESH4D, this->shaders[DEMOD4])));
	this->demos4D.push_back(new Demo4D(new Wall4D("Hexadecachoron", Hexadecachoron(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->wallTexs3D[this->buildTexture], 0.f, this->buildColor, MESH4D, this->shaders[DEMOD4])));
	this->demos4D.push_back(new Demo4D(new Wall4D("Hexacosichoron", Hexacosichoron(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->wallTexs3D[this->buildTexture], 0.f, this->buildColor, MESH4D, this->shaders[DEMOD4])));

	this->demos4D.push_back(new Demo4D(new RigidBody4D("Hypercube", Hypercube(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->wallTexs3D[this->buildTexture], 0.f, this->buildColor, BOX4D, true, this->shaders[DEMOD4])));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("Hypersphere", Hypersphere(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->wallTexs3D[this->buildTexture], 0.f, this->buildColor, SPHERE4D, true, this->shaders[DEMOD4])));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("Hypercapsule", Hypercapsule(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->wallTexs3D[this->buildTexture], 0.f, this->buildColor, MESH4D, true, this->shaders[DEMOD4])));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("Hypercylinder", Hypercylinder(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->wallTexs3D[this->buildTexture], 0.f, this->buildColor, MESH4D, true, this->shaders[DEMOD4])));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("Hypercone", Hypercone(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->wallTexs3D[this->buildTexture], 0.f, this->buildColor, MESH4D, true, this->shaders[DEMOD4])));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("Hyperpot", Hyperpot(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->wallTexs3D[this->buildTexture], 0.f, this->buildColor, MESH4D, true, this->shaders[DEMOD4])));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("TriPrism", TriPrism(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->wallTexs3D[this->buildTexture], 0.f, this->buildColor, MESH4D, true, this->shaders[DEMOD4])));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("Hyperslope", Hyperslope(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->wallTexs3D[this->buildTexture], 0.f, this->buildColor, MESH4D, true, this->shaders[DEMOD4])));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("DoubleQuads4d", DoubleQuads4d(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->wallTexs3D[this->buildTexture], 0.f, this->buildColor, MESH4D, true, this->shaders[DEMOD4])));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("Pentachoron", Pentachoron(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->wallTexs3D[this->buildTexture], 0.f, this->buildColor, MESH4D, true, this->shaders[DEMOD4])));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("Pyramid4D", Pyramid4D(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->wallTexs3D[this->buildTexture], 0.f, this->buildColor, MESH4D, true, this->shaders[DEMOD4])));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("Hexadecachoron", Hexadecachoron(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->wallTexs3D[this->buildTexture], 0.f, this->buildColor, MESH4D, true, this->shaders[DEMOD4])));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("Hexacosichoron", Hexacosichoron(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->wallTexs3D[this->buildTexture], 0.f, this->buildColor, MESH4D, true, this->shaders[DEMOD4])));
	std::vector<Wall4D*> poolTable;
	generate_pool_table4D(glm::vec4(0.f), glm::vec4(1.27f, 1.27f, 2.54f, 1.27f), 1.f, true, this->wallTexs3D[WOODX], true, this->wallTexs3D[GRASS], true, this->wallTexs3D[WOODY], &poolTable, this->shaders[DEMOD4]);
	this->demos4D.push_back(new Demo4D(poolTable));
	std::vector<RigidBody4D*> billiard4D;
	generate_billiard4D(glm::vec4(0.f), this->wallTexs3D[this->buildTexture], &billiard4D, this->isGravity, this->shaders[DEMOD4]);
	this->demos4D.push_back(new Demo4D(billiard4D));
	std::vector<Wall4D*> dynamite4D;
	generate_dynamite4D(glm::vec4(0.f), this->wallTexs3D[WHITECONCRETE], &dynamite4D, this->shaders[DEMOD4]);
	this->demos4D.push_back(new Demo4D(dynamite4D));
	std::vector<RigidBody4D*> dynamite4D2;
	generate_dynamite4D(glm::vec4(0.f), this->wallTexs3D[WHITECONCRETE], &dynamite4D2, this->isGravity, this->shaders[DEMOD4]);
	this->demos4D.push_back(new Demo4D(dynamite4D2));
	this->demos4D.push_back(new Demo4D(new Stick4D(glm::vec4(0.f), -1, -1, this->stickLength, this->wallTexs3D[WHITECONCRETE], this->buildColor, this->shaders[DEMOD4])));
	this->demos4D.push_back(new Demo4D(new Spring4D(glm::vec4(0.f), -1, -1, this->springLength, this->springStrength, this->wallTexs3D[GREEN], this->buildColor, this->shaders[DEMOD4])));
}

void Game::startGroups()
{
	this->groups.clear();
	this->groups = pack_group(this->groups,&this->walls4D, &this->terrains4D);
}

void Game::startDefault()
{
	this->isRenderCoordinate4D = false;
	this->fov = 60.f;
	this->nearPlane = 0.1f;
	this->blockLoadDistance = 64;
	this->objectLoadDistance = 2;
	trailFadeTypeText = "Use Wireframe";
	this->frameType = 1;
	this->shaders[TRAIL4D]->use();
	this->shaders[TRAIL4D]->set1i(FORGET, "trailFadeType");
	trailFadeTypeText = "Forget";
	this->vsync = 1;
	glfwSwapInterval(this->vsync);
	glfwSetWindowMonitor(this->window, NULL, 0, 45, this->WINDOW_WIDTH, this->WINDOW_HEIGHT, GLFW_DONT_CARE);
	this->updateProjectMat();
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
	this->musics[0]->play();
	this->musicVolume=50.f;
	this->musicPitch = 0.53f;//0.5f
	for (Music* music : this->musics)
	{
		music->set_volume(this->musicVolume);
		music->set_pitch(this->musicPitch);
	}
}

void Game::startInputs() 
{
	for (size_t i = 0;i < 10;i++) {
		this->inputs.push_back(new Input());
	}
}

void Game::firstUpdate() 
{
	this->isFixedTime = fixedUpdate::is_fixed_update(this->dt, 1.f / 60.f);
}

void Game::updateProjectMat() {
	//Update framebuffer size and projection matrix
	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);
	glfwGetWindowPos(this->window, &this->windowPosX, &this->windowPosX);
	this->shader_2D_Shape->use();
	this->shader_2D_Shape->setVec2f(glm::vec2((float)this->framebufferHeight / (float)this->framebufferWidth, 1.f) * 0.0375f, "scale2D");
	this->camera.update_perspective_mat(glm::radians(this->fov), static_cast<float>(this->framebufferWidth) / this->framebufferHeight, this->nearPlane,this->shaders);
}

void Game::updateUniforms()
{
	//Update view matrix (camera)

	this->shaders[OBJ]->use();
	this->shaders[OBJ]->setVec3f(this->camera.position4D, "cameraPos");

	this->shaders[SKY_BOXD4]->use();
	this->shaders[SKY_BOXD4]->setMat4fv(this->camera.viewMat4D, "viewMat");
	this->shaders[SKY_BOXD4]->setVec4f(this->camera.position4D, "cameraPos");
	this->shaders[SKY_BOXD4]->set1f(this->curTime, "iTime");

	this->shaders[WALLD4]->use();
	this->shaders[WALLD4]->setMat4fv(this->camera.viewMat4D, "viewMat");
	this->shaders[WALLD4]->setVec4f(this->camera.position4D, "cameraPos");
	this->shaders[WALLD4]->set1f(this->curTime, "iTime");

	if (this->mode == BUILDING) {
		this->shaders[DEMOD4]->use();
		this->shaders[DEMOD4]->setMat4fv(this->camera.viewMat4D, "viewMat");
		this->shaders[DEMOD4]->setVec4f(this->camera.position4D, "cameraPos");
		this->shaders[DEMOD4]->set1f(this->curTime, "iTime");
	}

	this->shaders[EMITD4]->use();
	this->shaders[EMITD4]->setMat4fv(this->camera.viewMat4D, "viewMat");
	this->shaders[EMITD4]->setVec4f(this->camera.position4D, "cameraPos");

	this->shaders[TERRAIND4]->use();
	this->shaders[TERRAIND4]->setMat4fv(this->camera.viewMat4D, "viewMat");
	this->shaders[TERRAIND4]->setVec4f(this->camera.position4D, "cameraPos");
	this->shaders[TERRAIND4]->set1f(this->curTime, "iTime");

	if (this->waters4D.size() != 0)
	{
		this->shaders[WATERD4]->use();
		this->shaders[WATERD4]->setMat4fv(this->camera.viewMat4D, "viewMat");
		this->shaders[WATERD4]->setVec4f(this->camera.position4D, "cameraPos");
		this->shaders[WATERD4]->set1f(this->curTime, "iTime");
	}

	this->shaders[PARTICLE4D]->use();
	this->shaders[PARTICLE4D]->setMat4fv(this->camera.viewMat4D, "viewMat");
	this->shaders[PARTICLE4D]->setVec4f(this->camera.position4D, "cameraPos");

	if (this->isRenderCoordinate4D)
	{
		this->shaders[COORDNATE4D]->use();
		this->shaders[COORDNATE4D]->setMat4fv(this->camera.viewMat4D, "viewMat");
	}

	this->shaders[TRAIL4D]->use();
	this->shaders[TRAIL4D]->setMat4fv(this->camera.viewMat4D, "viewMat");
	this->shaders[TRAIL4D]->setVec4f(this->camera.position4D, "cameraPos");
	this->shaders[TRAIL4D]->set1f(this->curTime, "iTime");

	this->shaders[JOINT_LINE4D]->use();
	this->shaders[JOINT_LINE4D]->setMat4fv(this->camera.viewMat4D, "viewMat");
	this->shaders[JOINT_LINE4D]->setVec4f(this->camera.position4D, "cameraPos");

	if (this->frameType == 1)
	{
		this->shaders[FRAME4D]->use();
		this->shaders[FRAME4D]->setMat4fv(this->camera.viewMat4D, "viewMat");
		this->shaders[FRAME4D]->setVec4f(this->camera.position4D, "cameraPos");

		this->shaders[LIGHT_FRAME4D]->use();
		this->shaders[LIGHT_FRAME4D]->setMat4fv(this->camera.viewMat4D, "viewMat");
		this->shaders[LIGHT_FRAME4D]->setVec4f(this->camera.position4D, "cameraPos");
	}
}
void Game::startLines() 
{
	this->coordinate4D = new Coordinate4D();
}

void Game::startGui2()
{
	this->shader_2D_Shape->use();
	this->shader_2D_Shape->setVec2f(glm::vec2((float)this->framebufferHeight/(float)this->framebufferWidth, 1.f)*0.0375f, "scale2D");
	this->targetIcon = new Rectangle2D(this->pointerTexs[SHOOTING]);
}

void Game::startLevel(int level, unsigned type, const char* filePath)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(this->window);
	this->curserMode = false;
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	this->isCloseUI = true;
	this->walls4D.clear();
	this->terrains4D.clear();
	this->sticks4D.clear();
	this->springs4D.clear();
	this->shifts4D.clear();
	this->floats4D.clear();
	this->rotates4D.clear();
	this->hingeConstraints.clear();
	this->waters4D.clear();
	this->rigidBodies4D.clear();
	this->dynamites4D.clear();
	this->dynamites4D2.clear();
	this->pointLights4D.clear();
	this->emitters4D.clear();
	this->startObjects(level, type, filePath);
	this->startGroups();
	//for (int i = 0; i < 64; i++) { savedLevelText[i] = ''; }
	//savedLevelText[0]='L', savedLevelText[1] = 'e', savedLevelText[2]='v', savedLevelText[3]='e', savedLevelText[4]='l',savedLevelText[5]= ' ', savedLevelText[6] = (char)(this->level), savedLevelText[7]='-', savedLevelText[8] = '1',
	update_water4d(this->waters4D, this->shaders[WALLD4], this->shaders[EMITD4]);
	update_point_light4d(this->pointLights4D, this->shaders[WALLD4], this->shaders[TERRAIND4]);
	this->updateDt();
}
void Game::judgeRender()
{
	this->judgetime0 += this->dt;
	this->judgetime1 += this->dt;
	this->judgetime2 += this->dt;
	this->judgetime3 += this->dt;

	
	if (this->judgetime0 > 0.2625f * (float)(this->objectLoadDistance-1)) {
		for (Group* i : this->groups) {
			if (i->isRender)
			{

				for (Object4D* j : i->walls4D)
				{
					float scalePlus = j->scale4D.x + j->scale4D.y + j->scale4D.z + j->scale4D.w;
					this->relativePos4D = j->position4D - this->camera.position4D;
					if (abs(dot(this->camera.wDir, this->relativePos4D)) > scalePlus / 2.f + (float)this->objectLoadDistance)
						
					{
						j->isClamp = false;
					}
					else {
						j->isClamp = true;
					}
				}
				for (Object4D* j : i->terrains4D)
				{
					float scalePlus = j->scale4D.x + j->scale4D.y + j->scale4D.z + j->scale4D.w;
					this->relativePos4D = j->position4D - this->camera.position4D;
					if (abs(dot(this->camera.wDir, this->relativePos4D)) > scalePlus / 2.f + (float)this->objectLoadDistance)

					{
						j->isClamp = false;
					}
					else {
						j->isClamp = true;
					}
				}
			}
		}
		this->judgetime0 = 0.f;
	}
	if (this->judgetime1 > 0.13125f ) {
		for (Group* i : this->groups) {
			if (i->isRender)
			{

				for (Object4D* j : i->walls4D)
				{
					if (j->isClamp) {
						float scalePlus = j->scale4D.x + j->scale4D.y + j->scale4D.z + j->scale4D.w;
						this->relativePos4D = j->position4D - this->camera.position4D;
						if (dot(this->camera.forward4D, this->relativePos4D) < -scalePlus / 2.f)
						{
							j->isFront = false;
						}
						else {
							j->isFront = true;
						}
					}
					
				}
				for (Object4D* j : i->terrains4D)
				{
					if (j->isClamp) {
						float size = 4;
						this->relativePos4D = j->position4D + j->primitive4D.vertexData4D[1488] - this->camera.position4D;
						if (dot(this->camera.forward4D, this->relativePos4D) < -2.f* size)
						{
							j->isFront = false;
						}
						else {
							j->isFront = true;;
						}
					}

				}
			}
		}
		this->judgetime1 = 0.f;
	}

	if (this->judgetime3 > 0.3125 * (float)(this->blockLoadDistance)/(length(this->camera.limitedVelocity4D)+0.04f))
	{

		for (Group* i : this->groups)
		{
			this->relativePos4D = i->position4D - this->camera.position4D;
			if (length(this->relativePos4D) > (float)this->blockLoadDistance)
			{
				i->isRender = false;
			}
			else {
				i->isRender = true;
			}
		}

		for (int i = 1; i < size_of_objects4d(rigidBodies4D, dynamites4D2); i++)
		{
			this->relativePos4D = get_block_position4D(find_rigidbody4d(rigidBodies4D, dynamites4D2, i)->position4D) - this->camera.position4D;
			if (length(this->relativePos4D) > (float)this->blockLoadDistance)
			{
				find_rigidbody4d(rigidBodies4D, dynamites4D2, i)->isBeyond = true;
			}
			else {
				find_rigidbody4d(rigidBodies4D, dynamites4D2, i)->isBeyond = false;
			}
		}

		this->judgetime3 = 0.f;
	}
}

void::Game::updateLights()
{
	for (unsigned i = 0; i < this->pointLights4D.size(); i++)
	{
		if (this->pointLights4D[i]->index != -1)
		{
			//if(this->pointLights4D[i]->index < size_of_objects4d(this->rigidBodies4D, this->dynamites4D2))
			this->pointLights4D[i]->set_pointlight4D_position(find_rigidbody4d(this->rigidBodies4D, this->dynamites4D2, this->pointLights4D[i]->index)->position4D, this->shaders[WALLD4], this->shaders[TERRAIND4], i);
		}
	}
	this->directionLight4D->update_light4D_in_earth_environment(1200.f, this->worldTime);
	this->directionLight4D->set_light4D_property(this->shaders[WALLD4]);
	this->directionLight4D->set_light4D_property(this->shaders[TERRAIND4]);
	this->directionLight4D->set_light4D_property(this->shaders[WATERD4]);
	this->directionLight4D->set_light4D_property(this->shaders[EMITD4]);
	this->directionLight4D->set_light4D_property(this->shaders[SKY_BOXD4]);
}

void::Game::updateModes(int mode,int shift)
{
	if (shift != 0){
		if (mode != -1){
			this->mode = mode;
		}
		else{
			if (this->mode + shift >= SHOOTING && this->mode + shift <= AREA_DELETING)
				this->mode += shift;
		}
		this->targetIcon->logo = this->pointerTexs[this->mode];
		if (this->mode == AREA_DELETING)
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
	camera()
{
	//Init variables
	this->window = nullptr;
	this->framebufferWidth = this->WINDOW_WIDTH;
	this->framebufferHeight = this->WINDOW_HEIGHT;

	this->dt = 0.f;
	this->curTime = 0.f;
	this->lastTime = 0.f;
	this->worldTime = 0.f;

	this->lastMouseX = 0.0f;
	this->lastMouseY = 0.0f;
	this->mouseX = 0.0f;
	this->mouseY = 0.0f;
	this->mouseOffsetX = 0.0f;
	this->mouseOffsetY = 0.0f;
	this->firstMouse = true;
	this->isGround = false;

	this->level = 1;
	this->paintScale = 5;
	this->mode = SHOOTING;
	this->controlType = 0;
	this->isHardPainting = false;
	this->isSphericalPainting = true;
	this->paintType0 = 0;
	this->paintType = 0;
	this->hittingPos4D = glm::vec4(0.f);
	this->hitIndex = -1;
	this->hitPosNear = glm::vec4(10000.f);
	this->hitPosToBody = glm::vec4(0);

	this->filterType = 3;

	this->buildMode = BUILD_OBJECT;
	this->isFindPoint = false;
	this->isRigidBody = true;
	this->stickLength=3.f;
	this->springLength=3.f;
	this->springStrength=10.f;
	this->buildTexture = YELLOWMARBLE;
	this->buildShader = WALLD4;
	this->isSpecular = true;
	this->buildColor = glm::vec4(1.f);
	this->buildScale = glm::vec4(1.f);
	this->buildRotation = alg::bivec4();
	this->initialVelocity = glm::vec4(0.f);
	this->initialAngularVelocity = alg::bivec4();
	this->buildCol=HYPERCUBE;
	this->buildParameter = glm::vec4(1.f, 1.f, 1.6f, 0.25f);
	this->lightIntensity = 1.f;
	this->lightColor = glm::vec3(1.f);
	this->lightScale = glm::vec4(0.f,0.f,1.f,0.f);
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
	this->startLevel(this->level,0,"");
	this->startDefault();
	this->startInputs();

}
//Destructors
Game::~Game()
{
	glfwDestroyWindow(this->window);
	glfwTerminate();
	end_imgui();
	delete this->shader_2D_Shape;
	delete this->rectangle2D;
	for (Shader* i: this->shaders) { delete i; }
	for (Texture* i: this->textures) { delete i; }
	for (Texture* i : this->pointerTexs) { delete i; }
	delete this->deleteMap3D;
	for (Texture3D* i : this->textures3D) { delete i; }
	for (Texture3D* i : this->particleTexs3D) { delete i; }
	for (Texture3D* i : this->wallTexs3D) { delete i; }
	for (Texture3D* i : this->groundTexs3D) { delete i; }
	for (Sound* i : this->sounds) { delete i; }
	for (Music* i : this->musics) { delete i; }
	for (Object* i : this->objects) { delete i; }
	delete this->skybox4D;
	delete this->coordinate4D;
	delete this->targetIcon;
	delete this->demoObjects4D;
	for (Demo4D* i : this->demos4D) { delete i; }
	for (JointLine4D* i : this->dragLines4D) { delete i; }
	for (Input* i:this->inputs) { delete i; }
	for (Wall4D* i : this->walls4D) { delete i; }
	for (Wall4D* i : this->dynamites4D) { delete i; }
	for (RigidBody4D* i : this->dynamites4D2) { delete i; }
	for (RigidBody4D* i : this->rigidBodies4D) { delete i; }
	for (Terrain4D* i : this->terrains4D) { delete i; }
	for (Water4D* i : this->waters4D) { delete i; }
	for (Group* i : this->groups) { delete i; }
	for (Emitter4D* i : this->emitters4D) { delete i; }
	for (PointLight* i:this->pointLights) { delete i; }
	for (DirectionLight* i:this->directionLights) { delete i; }
	for (PointLight4D* i :this->pointLights4D) { delete i; }
	delete this->directionLight4D;
	for (Collision* i : this->collisions) { delete i; }
	for (HingeConstraint4D* i : this->hingeConstraints) { delete i; }
	for (Stick4D* i : this->sticks4D) { delete i; }
	for (Spring4D* i : this->springs4D) { delete i; }
	for (Shift4D* i : this->shifts4D) { delete i; }
	for (Float4D* i : this->floats4D) { delete i; }
	for (Rotate4D* i : this->rotates4D) { delete i; }
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
	if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_1) != GLFW_PRESS) {
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
	}

	if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_1) != GLFW_RELEASE)
	{
		this->firstMouse = true;
	}

	if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
	{
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
	}
	if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE)
	{
		this->firstMouse2 = true;
	}
}

void Game::updateInput()
{
	this->updateKeyboardInput();
	if (!this->curserMode) {
		this->updateMouseInput();
		if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_1) != GLFW_PRESS) {
			this->camera.update_mouse_input(dt, this->mouseOffsetX, this->mouseOffsetY);
		}
		if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
			this->camera.update_mouse_input2(dt, this->mouseOffsetX2, this->mouseOffsetY2);
		}
	}
}

void Game::beforeRender()
{

	//Update the uniforms
	this->updateUniforms();
	//Update the lights
	this->updateLights();
	if (this->isFixedTime)
	{
		phy::before_render_physic4D(this->rigidBodies4D, this->dynamites4D2, this->groups, this->walls4D,this->dynamites4D, this->sticks4D, this->springs4D, 1.f/60.f,this->curTime);
	}
	if (this->mode == BUILDING)
	{
		//if (fixedUpdate::is_fixed_update2(this->dt, 1.f / 30.f))
		{
			this->demoObjects4D->clear();
			if (this->isFindPoint) {
				if (this->buildMode == BUILD_OBJECT) {
					if (this->buildCol == HYPERCUBE)
						this->demoObjects4D->walls4D.push_back(this->demos4D[0]->walls4D[0]);
					if (this->buildCol == HYPERSPHERE)
						this->demoObjects4D->walls4D.push_back(this->demos4D[1]->walls4D[0]);
					if (this->buildCol == HYPERCAPSULE)
						this->demoObjects4D->walls4D.push_back(this->demos4D[2]->walls4D[0]);
					if (this->buildCol == HYPERCYLINDER)
						this->demoObjects4D->walls4D.push_back(this->demos4D[3]->walls4D[0]);
					if (this->buildCol == HYPERCONE)
						this->demoObjects4D->walls4D.push_back(this->demos4D[4]->walls4D[0]);
					if (this->buildCol == HYPERPOT)
						this->demoObjects4D->walls4D.push_back(this->demos4D[5]->walls4D[0]);
					if (this->buildCol == TRIPRISM)
						this->demoObjects4D->walls4D.push_back(this->demos4D[6]->walls4D[0]);
					if (this->buildCol == HYPERSLOPE)
						this->demoObjects4D->walls4D.push_back(this->demos4D[7]->walls4D[0]);
					if (this->buildCol == HYPERQUAD)
						this->demoObjects4D->walls4D.push_back(this->demos4D[8]->walls4D[0]);
					if (this->buildCol == PENTACHORON)
						this->demoObjects4D->walls4D.push_back(this->demos4D[9]->walls4D[0]);
					if (this->buildCol == HYPERPYRAMID)
						this->demoObjects4D->walls4D.push_back(this->demos4D[10]->walls4D[0]);
					if (this->buildCol == HEXADECACHORON)
						this->demoObjects4D->walls4D.push_back(this->demos4D[11]->walls4D[0]);
					if (this->buildCol == HEXACOSICHORON)
						this->demoObjects4D->walls4D.push_back(this->demos4D[12]->walls4D[0]);
					this->demoObjects4D->walls4D[0]->set_position4D(get_cap_position4D(this->hittingPos4D + glm::vec4(0.f, this->buildScale.y / 2.f, 0.f, 0.f)));
					this->demoObjects4D->walls4D[0]->set_rotation4D(this->buildRotation);
					this->demoObjects4D->walls4D[0]->set_scale4D(this->buildScale);
				}
				if (this->buildMode == BUILD_RIGIDBODY) {
					if (this->buildCol == HYPERCUBE)
						this->demoObjects4D->rigidBodies4D.push_back(this->demos4D[13]->rigidBodies4D[0]);
					if (this->buildCol == HYPERSPHERE)
						this->demoObjects4D->rigidBodies4D.push_back(this->demos4D[14]->rigidBodies4D[0]);
					if (this->buildCol == HYPERCAPSULE)
						this->demoObjects4D->rigidBodies4D.push_back(this->demos4D[15]->rigidBodies4D[0]);
					if (this->buildCol == HYPERCYLINDER)
						this->demoObjects4D->rigidBodies4D.push_back(this->demos4D[16]->rigidBodies4D[0]);
					if (this->buildCol == HYPERCONE)
						this->demoObjects4D->rigidBodies4D.push_back(this->demos4D[17]->rigidBodies4D[0]);
					if (this->buildCol == HYPERPOT)
						this->demoObjects4D->rigidBodies4D.push_back(this->demos4D[18]->rigidBodies4D[0]);
					if (this->buildCol == TRIPRISM)
						this->demoObjects4D->rigidBodies4D.push_back(this->demos4D[19]->rigidBodies4D[0]);
					if (this->buildCol == HYPERSLOPE)
						this->demoObjects4D->rigidBodies4D.push_back(this->demos4D[20]->rigidBodies4D[0]);
					if (this->buildCol == HYPERQUAD)
						this->demoObjects4D->rigidBodies4D.push_back(this->demos4D[21]->rigidBodies4D[0]);
					if (this->buildCol == PENTACHORON)
						this->demoObjects4D->rigidBodies4D.push_back(this->demos4D[22]->rigidBodies4D[0]);
					if (this->buildCol == HYPERPYRAMID)
						this->demoObjects4D->rigidBodies4D.push_back(this->demos4D[23]->rigidBodies4D[0]);
					if (this->buildCol == HEXADECACHORON)
						this->demoObjects4D->rigidBodies4D.push_back(this->demos4D[24]->rigidBodies4D[0]);
					if (this->buildCol == HEXACOSICHORON)
						this->demoObjects4D->rigidBodies4D.push_back(this->demos4D[25]->rigidBodies4D[0]);
					this->demoObjects4D->rigidBodies4D[0]->set_position4D(this->hittingPos4D + glm::vec4(0.f, this->buildScale.y / 2.f - 0.01f, 0.f, 0.f));
					this->demoObjects4D->rigidBodies4D[0]->set_rotation4D(this->buildRotation);
					this->demoObjects4D->rigidBodies4D[0]->set_scale4D(this->buildScale);
				}
				if (this->buildMode == BUILD_POOL_TABLE) {
					for (int i=0;i < this->demos4D[26]->walls4D.size();i++)
					{
						this->demoObjects4D->walls4D.push_back(this->demos4D[26]->walls4D[i]);
						this->demoObjects4D->walls4D[i]->set_mesh_position4D(this->demos4D[26]->walls4D[i]->position4D + get_cap_position4D(this->hittingPos4D));
					}
				}
				if (this->buildMode == BUILD_BILLIARD) {
					this->demoObjects4D->rigidBodies4D = this->demos4D[27]->rigidBodies4D;
					for (int i = 0; i < this->demoObjects4D->rigidBodies4D.size(); i++)
					{
						this->demoObjects4D->rigidBodies4D[i]->set_mesh_position4D(this->demos4D[27]->rigidBodies4D[i]->position4D + this->hittingPos4D);
					}
				}
				if (this->buildMode == BUILD_DYNAMITE) {
					if (!this->isRigidBody)
					{
						this->demoObjects4D->walls4D = this->demos4D[28]->walls4D;
						for (int i = 0; i < this->demoObjects4D->walls4D.size(); i++)
						{
							this->demoObjects4D->walls4D[i]->set_mesh_position4D(this->demos4D[28]->walls4D[i]->position4D + this->hittingPos4D);
						}
					}
					if (this->isRigidBody)
					{
						this->demoObjects4D->rigidBodies4D = this->demos4D[29]->rigidBodies4D;
						for (int i = 0; i < this->demoObjects4D->rigidBodies4D.size(); i++)
						{
							this->demoObjects4D->rigidBodies4D[i]->set_mesh_position4D(this->demos4D[29]->rigidBodies4D[i]->position4D + this->hittingPos4D);
						}
					}
				}
			}
			if (this->buildMode == BUILD_STICK)
			{
				this->hitIndex = ray::detect_object4d_index(this->rigidBodies4D, this->dynamites4D2, this->groups, this->walls4D, this->dynamites4D, true, true, false, this->camera.position4D, this->camera.forward4D, this->camera.right4D, &this->hitPosNear);
				if (this->hitIndex > -1)
				{
					bool isInitial = true;
					if (this->springs4D.size() != 0)
					{
						if (this->springs4D[this->springs4D.size() - 1]->index2 == -1)
						{
							isInitial = false;
							this->demoObjects4D->spring4D = this->demos4D[31]->spring4D;
							this->demoObjects4D->spring4D->fixPoint4D = this->camera.frontPosition4D;
							this->demoObjects4D->spring4D->index1 = this->springs4D[this->springs4D.size() - 1]->index1;
							this->demoObjects4D->spring4D->index2 = this->springs4D[this->springs4D.size() - 1]->index1 == this->hitIndex ? -1 : this->hitIndex;
							if (this->demoObjects4D->spring4D != nullptr)
								phy::update_spring4D(this->rigidBodies4D, this->dynamites4D2, this->groups, this->walls4D, this->dynamites4D, this->demoObjects4D->spring4D);
						}
					}
					if (isInitial)
					{
						if (this->sticks4D.size() == 0)
						{
							this->demoObjects4D->stick4D = this->demos4D[30]->stick4D;
							this->demoObjects4D->stick4D->fixPoint4D = this->camera.frontPosition4D;
							this->demoObjects4D->stick4D->index1 = this->hitIndex;
							this->demoObjects4D->stick4D->index2 = -1;
						}
						if (this->sticks4D.size() != 0)
						{
							if (this->sticks4D[this->sticks4D.size() - 1]->index2 == -1)
							{
								this->demoObjects4D->stick4D = this->demos4D[30]->stick4D;
								this->demoObjects4D->stick4D->fixPoint4D = this->camera.frontPosition4D;
								this->demoObjects4D->stick4D->index1 = this->sticks4D[this->sticks4D.size() - 1]->index1;
								this->demoObjects4D->stick4D->index2 = this->sticks4D[this->sticks4D.size() - 1]->index1 == this->hitIndex ? -1 : this->hitIndex;
							}
							if (this->sticks4D[this->sticks4D.size() - 1]->index2 != -1)
							{
								this->demoObjects4D->stick4D = this->demos4D[30]->stick4D;
								this->demoObjects4D->stick4D->fixPoint4D = this->camera.frontPosition4D;
								this->demoObjects4D->stick4D->index1 = this->hitIndex;
								this->demoObjects4D->stick4D->index2 = -1;
							}
						}
						if (this->demoObjects4D->stick4D != nullptr)
							phy::update_stick4D(this->rigidBodies4D, this->dynamites4D2, this->groups, this->walls4D, this->dynamites4D, this->demoObjects4D->stick4D);
					}
				}
			}
			if (this->buildMode == BUILD_SPRING)
			{
				this->hitIndex = ray::detect_object4d_index(this->rigidBodies4D, this->dynamites4D2, this->groups, this->walls4D, this->dynamites4D, true, true, false, this->camera.position4D, this->camera.forward4D, this->camera.right4D, &this->hitPosNear);
				if (this->hitIndex > -1)
				{
					bool isInitial = true;
					if (this->sticks4D.size() != 0)
					{
						if (this->sticks4D[this->sticks4D.size() - 1]->index2 == -1)
						{
							isInitial = false;
							this->demoObjects4D->stick4D = this->demos4D[30]->stick4D;
							this->demoObjects4D->stick4D->fixPoint4D = this->camera.frontPosition4D;
							this->demoObjects4D->stick4D->index1 = this->sticks4D[this->sticks4D.size() - 1]->index1;
							this->demoObjects4D->stick4D->index2 = this->sticks4D[this->sticks4D.size() - 1]->index1 == this->hitIndex ? -1 : this->hitIndex;
							if (this->demoObjects4D->stick4D != nullptr)
								phy::update_stick4D(this->rigidBodies4D, this->dynamites4D2, this->groups, this->walls4D, this->dynamites4D, this->demoObjects4D->stick4D);
						}
					}
					if (isInitial)
					{
						if (this->springs4D.size() == 0)
						{
							this->demoObjects4D->spring4D = this->demos4D[31]->spring4D;
							this->demoObjects4D->spring4D->fixPoint4D = this->camera.frontPosition4D;
							this->demoObjects4D->spring4D->index1 = this->hitIndex;
							this->demoObjects4D->spring4D->index2 = -1;
						}
						if (this->springs4D.size() != 0)
						{
							if (this->springs4D[this->springs4D.size() - 1]->index2 == -1)
							{
								this->demoObjects4D->spring4D = this->demos4D[31]->spring4D;
								this->demoObjects4D->spring4D->fixPoint4D = this->camera.frontPosition4D;
								this->demoObjects4D->spring4D->index1 = this->springs4D[this->springs4D.size() - 1]->index1;
								this->demoObjects4D->spring4D->index2 = this->springs4D[this->springs4D.size() - 1]->index1 == this->hitIndex ? -1 : this->hitIndex;
							}
							if (this->springs4D[this->springs4D.size() - 1]->index2 != -1)
							{
								this->demoObjects4D->spring4D = this->demos4D[31]->spring4D;
								this->demoObjects4D->spring4D->fixPoint4D = this->camera.frontPosition4D;
								this->demoObjects4D->spring4D->index1 = this->hitIndex;
								this->demoObjects4D->spring4D->index2 = -1;
							}
						}
						if (this->demoObjects4D->spring4D != nullptr)
							phy::update_spring4D(this->rigidBodies4D, this->dynamites4D2, this->groups, this->walls4D, this->dynamites4D, this->demoObjects4D->spring4D);
					}
				}
			}
		}
	}
}

void Game::update0()
{
	//UPDATE INPUT ---
	this->firstUpdate();
	this->updateTime();
	this->updateObjects();
	this->updateCollider();
	this->updateDynamites();
	this->updateParticles();
	this->updateInput();
	this->judgeRender();
	this->beforeRender();
}

void Game::render0()
{
	//Clear
	glClear(GL_DEPTH_BUFFER_BIT);

	//Render models
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//for (Object* i : this->objects){i->render(this->shaders[OBJ]);}
	//1:SKY BOX
	this->skybox4D->render();
	//
	//2:OBJS NOT TRANSPARENT
	glLineWidth(1.f);
	for (Group* i : this->groups) {
		if (i->isRender) {
			for (Wall4D* j : i->walls4D) {
				if (j->isClamp) {
					if (j->isFront) {
						if (!(j->diffuse3D->isTransparent || j->paintingColor.w < 1.f) && j->primitive4D.primitiveName != "Noneshape")
						{
							if (this->frameType == 1)
							{
								j->render_frame(this->shaders[FRAME4D]);
							}
							j->render();
						}
					}
				}
			}
		}
		for (Terrain4D* j : i->terrains4D) {
			if (j->isClamp) {
				if (j->isFront)
				{
					j->render();
					//if (this->frameType == 1)
					//{
					//	j->render_frame(this->shaders[FRAME4D]);
					//}
				}
			}
		}
	}
	for (Terrain4D* j : this->terrains4D)
	{
		j->render();
	}
	for (Wall4D* j : this->walls4D) {
		if (!(j->diffuse3D->isTransparent || j->paintingColor.w < 1.f) && j->primitive4D.primitiveName != "Noneshape")
		{
			if (this->frameType == 1)
			{
				j->render_frame(this->shaders[FRAME4D]);
			}
			j->render();
		}
	}

	for (Wall4D* j : this->dynamites4D) {
		if (this->frameType == 1)
		{
			j->render_frame(this->shaders[FRAME4D]);
		}
		j->render();
	}
	for (RigidBody4D* j : this->dynamites4D2) {
		if (this->frameType == 1)
		{
			j->render_frame(this->shaders[FRAME4D]);
		}
		j->render();
	}
	
	for (size_t i = 1; i < this->rigidBodies4D.size(); i++)
	{
		if (!(this->rigidBodies4D[i]->diffuse3D->isTransparent || this->rigidBodies4D[i]->paintingColor.w < 1.f))
		{
			if (this->frameType == 1)
			{
				this->rigidBodies4D[i]->render_frame(this->shaders[FRAME4D]);
			}
			this->rigidBodies4D[i]->render();
		}
	}
	for (Stick4D* i : this->sticks4D)
	{
		if(i->index2!=-1)
		if (!(i->diffuse3D->isTransparent || i->paintingColor.w < 1.f))
		{
			if (this->frameType == 1)
			{
				glLineWidth(1.f);
				i->render_frame(this->shaders[FRAME4D]);
			}
			glLineWidth(1.9f);
			i->render_line4D(this->shaders[JOINT_LINE4D]);
			i->render();
		}
	}

	for (Spring4D* i : this->springs4D)
	{
		if (i->index2 != -1)
		if (!(i->diffuse3D->isTransparent || i->paintingColor.w < 1.f))
		{
			if (this->frameType == 1)
			{
				glLineWidth(1.f);
				i->render_frame(this->shaders[FRAME4D]);
			}
			glLineWidth(1.9f);
			i->render_line4D(this->shaders[JOINT_LINE4D]);
			i->render();
		}
	}
	//
	//3:PARTICLES AND LINES
	glLineWidth(1.9f);
	for (Emitter4D* i : this->emitters4D)
	{
		for (Particle4D* j : i->particles4D)
		{
			if (j->isGlowing)
				glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			else
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDepthMask(false);
			j->render(this->shaders[PARTICLE4D]);
			if (this->frameType == 1)
			{
				glDepthMask(true);
				j->render_frame(this->shaders[LIGHT_FRAME4D]);
			}
		}
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	for (PointLight4D* i : this->pointLights4D) {
		if (i->isRender)
		{
			glDepthMask(false);
			i->render(this->shaders[PARTICLE4D]);
			if (this->frameType == 1)
			{
				glDepthMask(true);
				i->render_frame(this->shaders[LIGHT_FRAME4D]);
			}
		}
	}

	glDepthMask(true);
	if (this->frameType == 1)
	{
		this->directionLight4D->render_frame(this->shaders[LIGHT_FRAME4D]);
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (JointLine4D* i : this->dragLines4D)
	{
		i->render(this->shaders[JOINT_LINE4D]);
	}
	for (RigidBody4D* i : this->rigidBodies4D)
	{
		i->trail4D->render(this->shaders[TRAIL4D]);
	}
	for (RigidBody4D* i : this->dynamites4D2)
	{
		i->trail4D->render(this->shaders[TRAIL4D]);
	}
	//
		
	//4:TRANSPARENT OBJS
	glLineWidth(1.f);

	for (Group* i : this->groups) {
		if (i->isRender) {
			for (Wall4D* j : i->walls4D) {
				if (j->isClamp) {
					if (j->isFront) {
						if ((j->diffuse3D->isTransparent||j->paintingColor.w<1.f) && j->primitive4D.primitiveName != "Noneshape")
						{
							if (this->frameType == 1)
							{
								j->render_frame(this->shaders[FRAME4D]);
							}
							j->render();
						}
					}
				}
			}
		}
	}
	for (Wall4D* j : this->walls4D) {
		if ((j->diffuse3D->isTransparent || j->paintingColor.w < 1.f) && j->primitive4D.primitiveName != "Noneshape")
		{
			if (this->frameType == 1)
			{
				j->render_frame(this->shaders[FRAME4D]);
			}
			j->render();
		}
	}

	for (size_t i = 1; i < this->rigidBodies4D.size(); i++)
	{
		if (this->rigidBodies4D[i]->diffuse3D->isTransparent || this->rigidBodies4D[i]->paintingColor.w < 1.f)
		{
			if (this->frameType == 1)
			{
				glLineWidth(1.f);
				this->rigidBodies4D[i]->render_frame(this->shaders[FRAME4D]);
			}
			glLineWidth(1.9f);
			this->rigidBodies4D[i]->render_trail4D(this->shaders[TRAIL4D]);
			this->rigidBodies4D[i]->render();
		}
	}

	for (Stick4D* i : this->sticks4D)
	{
		if (i->index2 != -1)
		if (i->diffuse3D->isTransparent || i->paintingColor.w < 1.f)
		{
			if (this->frameType == 1)
			{
				glLineWidth(1.f);
				i->render_frame(this->shaders[FRAME4D]);
			}
			glLineWidth(1.9f);
			i->render_line4D(this->shaders[JOINT_LINE4D]);
			i->render();
		}
	}

	for (Spring4D* i : this->springs4D)
	{
		if (i->index2 != -1)
		if (i->diffuse3D->isTransparent || i->paintingColor.w < 1.f)
		{
			if (this->frameType == 1)
			{
				glLineWidth(1.f);
				i->render_frame(this->shaders[FRAME4D]);
			}
			glLineWidth(1.9f);
			i->render_line4D(this->shaders[JOINT_LINE4D]);
			i->render();
		}
	}

	if (this->mode == BUILDING) {
		if (!(this->buildMode == BUILD_STICK || this->buildMode == BUILD_SPRING))
		{
			if (this->isFindPoint) {
				for (Wall4D* j : this->demoObjects4D->walls4D)
				{
					if (this->frameType == 1)
					{
						glLineWidth(1.f);
						j->render_frame(this->shaders[FRAME4D]);
					}
					j->render();
				}
				for (RigidBody4D* j : this->demoObjects4D->rigidBodies4D)
				{
					if (this->frameType == 1)
					{
						glLineWidth(1.f);
						j->render_frame(this->shaders[FRAME4D]);
					}
					j->render();
				}
			}
		}
		else
		{
			if (this->demoObjects4D->stick4D != nullptr)
			{
				if (this->frameType == 1)
				{
					glLineWidth(1.f);
					this->demoObjects4D->stick4D->render_frame(this->shaders[FRAME4D]);
				}
				glLineWidth(1.9f);
				this->demoObjects4D->stick4D->render_line4D(this->shaders[JOINT_LINE4D]);
				this->demoObjects4D->stick4D->render();
			}
			if (this->demoObjects4D->spring4D != nullptr)
			{
				if (this->frameType == 1)
				{
					glLineWidth(1.f);
					this->demoObjects4D->spring4D->render_frame(this->shaders[FRAME4D]);
				}
				glLineWidth(1.9f);
				this->demoObjects4D->spring4D->render_line4D(this->shaders[JOINT_LINE4D]);
				this->demoObjects4D->spring4D->render();
			}
		}
	}
	for (Water4D* j : this->waters4D) {
		j->render();
	}
	//

	//5:LENS FLARE
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	if (ray::is_in_screen(-this->directionLight4D->direction4D, camera.viewMat4D, camera.projectionMat))
	{
		glm::vec4 hitPosNear2;
		if (ray::detect_object4d_index(this->rigidBodies4D, this->dynamites4D2, this->groups, this->walls4D, this->dynamites4D, true,false,true,this->camera.position4D, -this->directionLight4D->direction4D, this->directionLight4D->right4D, &hitPosNear2) == -1)
		{
			glDepthMask(false);
			this->directionLight4D->render(this->shaders[PARTICLE4D]);
			glDepthMask(true);
		}
	}
	//

	//6:GUI
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth(1.9f);
	if (this->isRenderCoordinate4D)
	{
	    this->coordinate4D->render(this->shaders[COORDNATE4D]);
    }

	if (!this->curserMode) {
		glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
		this->targetIcon->render(this->shader_2D_Shape);
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