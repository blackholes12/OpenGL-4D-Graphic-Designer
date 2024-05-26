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
	for (size_t i(0); i < 4; i++)
	SOIL_free_image_data(icons[i].pixels);

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
	this->shader_2D_Shape = new Shader(this->GL_VERSION_MAJOR, this->GL_VERSION_MINOR,
		"resourcefile/shaders/shape2D.vertex", "resourcefile/shaders/shape2D.fragment");
	this->shader_2D_Shape->use();
	this->shader_2D_Shape->setVec2f(glm::vec2((float)this->framebufferHeight / (float)this->framebufferWidth, 1.f), "scale2D");
	this->textures.push_back(new Texture("resourcefile/images/logo.png"));
	this->rectangle2D = new Rectangle2D(0);
	this->rectangle2D->render(this->textures[this->rectangle2D->textureIndex],this->shader_2D_Shape);
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
	this->textures.push_back(new Texture(
		"resourcefile/images/maps/VERTEX_MAP4D.png"));
	char ss[256];
	for (int i(1); i <= 10; i++){
		snprintf(ss, 255, "resourcefile/images/2d/i1-%i.png", i);
		this->textures.push_back(new Texture(ss));
	}
	for (int i(1); i <= 57; i++){
		snprintf(ss, 255, "resourcefile/images/2d/i2-%i.png", i);
		this->textures.push_back(new Texture(ss));
	}
	for (int i(1); i <= 7; i++){
		snprintf(ss, 255, "resourcefile/images/2d/i3-%i.png", i);
		this->textures.push_back(new Texture(ss));
	}
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
	this->textures[1]->bind(2);

	this->textures3D.push_back(new Texture3D(
		"resourcefile/images/noise.png"));
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
		"resourcefile/images/textures/GREEN.png"));
	this->wallTexs3D.push_back(new Texture3D(
		"resourcefile/images/textures/WHITE.png"));
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
		"resourcefile/images/textures/ORANGE_WHITE.png"));
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
		"resourcefile/images/textures/ROCK1.png"));
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

	for (int i(0); i < 10; i++)
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

	this->deleteMap3D->bind(9);

	for (int i(0); i < 20; i++)
	{
		this->groundTexs3D[i]->bind(i+10);
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
	this->demos4D.push_back(new Demo4D(new Wall4D("Hypercube", Hypercube(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, 0.f, this->buildColor, BOX4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new Wall4D("Hypersphere", Hypersphere(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, 0.f, this->buildColor, SPHERE4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new Wall4D("Hypercapsule", Hypercapsule(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, 0.f, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new Wall4D("Hypercylinder", Hypercylinder(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, 0.f, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new Wall4D("Hypercone", Hypercone(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, 0.f, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new Wall4D("Hyperpot", Hyperpot(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, 0.f, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new Wall4D("TriPrism", TriPrism(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, 0.f, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new Wall4D("Hyperslope", Hyperslope(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, 0.f, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new Wall4D("DoubleQuads4d", DoubleQuads4d(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, 0.f, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new Wall4D("Pentachoron", Pentachoron(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, 0.f, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new Wall4D("Pyramid4D", Pyramid4D(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, 0.f, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new Wall4D("Hexadecachoron", Hexadecachoron(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, 0.f, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new Wall4D("Hexacosichoron", Hexacosichoron(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.z, this->buildParameter.w, this->isSpecular, this->buildTexture, 0.f, this->buildColor, MESH4D, DEMOD4)));

	this->demos4D.push_back(new Demo4D(new RigidBody4D("Hypercube", Hypercube(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, 0.f, this->buildColor, BOX4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("Hypersphere", Hypersphere(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, 0.f, this->buildColor, SPHERE4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("Hypercapsule", Hypercapsule(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, 0.f, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("Hypercylinder", Hypercylinder(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, 0.f, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("Hypercone", Hypercone(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, 0.f, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("Hyperpot", Hyperpot(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, 0.f, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("TriPrism", TriPrism(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, 0.f, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("Hyperslope", Hyperslope(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, 0.f, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("DoubleQuads4d", DoubleQuads4d(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, 0.f, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("Pentachoron", Pentachoron(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, 0.f, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("Pyramid4D", Pyramid4D(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, 0.f, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("Hexadecachoron", Hexadecachoron(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, 0.f, this->buildColor, MESH4D, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new RigidBody4D("Hexacosichoron", Hexacosichoron(glm::vec4(0.5f)), glm::vec4(0.f), this->buildRotation, this->buildScale, this->buildParameter.x, this->buildParameter.y, this->buildParameter.z, this->buildParameter.w, this->isGravity, false, this->initialVelocity, this->initialAngularVelocity, this->isSpecular, this->buildTexture, 0.f, this->buildColor, MESH4D, DEMOD4)));
	std::vector<Wall4D*> poolTable;
	generate_pool_table4D(glm::vec4(0.f), glm::vec4(1.27f, 1.27f, 2.54f, 1.27f), 1.f, true, WOODX, true, GRASS, true, WOODY, &poolTable, DEMOD4);
	this->demos4D.push_back(new Demo4D(poolTable));
	std::vector<RigidBody4D*> billiard4D;
	generate_billiard4D(glm::vec4(0.f), glm::vec4(),alg::bivec4(),this->buildTexture, &billiard4D, this->isGravity, 0.f,glm::vec4(1.f),DEMOD4);
	this->demos4D.push_back(new Demo4D(billiard4D));
	std::vector<Wall4D*> dynamite4D;
	generate_dynamite4D(glm::vec4(0.f), WHITECONCRETE, &dynamite4D, DEMOD4);
	this->demos4D.push_back(new Demo4D(dynamite4D));
	std::vector<RigidBody4D*> dynamite4D2;
	generate_dynamite4D(glm::vec4(0.f), this->initialVelocity, this->initialAngularVelocity, WHITECONCRETE, &dynamite4D2, this->isGravity, DEMOD4);
	this->demos4D.push_back(new Demo4D(dynamite4D2));
	this->demos4D.push_back(new Demo4D(new Stick4D(glm::vec4(0.f), -1, -1, this->stickLength, WHITECONCRETE, this->buildColor, DEMOD4)));
	this->demos4D.push_back(new Demo4D(new Spring4D(glm::vec4(0.f), -1, -1, this->springLength, this->springStrength, GREEN, this->buildColor, DEMOD4)));
}

void Game::startDefault()
{
	this->isRenderCoordinate4D = false;
	this->camera.update_perspective_mat(60.f, static_cast<float>(this->framebufferWidth) / this->framebufferHeight, 0.1f);
	this->blockLoadDistance = 64;
	this->objectLoadDistance = 0;
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
	this->isCloud = true;
	this->isSkyBoxFog = true;
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
}

void Game::updateProjectMat() {
	//Update framebuffer size and projection matrix
	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);
	glfwGetWindowPos(this->window, &this->windowPosX, &this->windowPosX);
	this->shader_2D_Shape->use();
	this->shader_2D_Shape->setVec2f(glm::vec2((float)this->framebufferHeight / (float)this->framebufferWidth, 1.f) * 0.0375f, "scale2D");
	this->camera.update_perspective_mat(this->camera.fov, static_cast<float>(this->framebufferWidth) / this->framebufferHeight, this->camera.nearPlane);
	//shaders[OBJ]->use();
	//shaders[OBJ]->setMat4fv(this->projectionMat, "projectionMat");
	this->shaders[SKY_BOXD4]->use();
	this->shaders[SKY_BOXD4]->setMat4fv(this->camera.projectionMat, "projectionMat");
	this->shaders[WALLD4]->use();
	this->shaders[WALLD4]->setMat4fv(this->camera.projectionMat, "projectionMat");
	this->shaders[DEMOD4]->use();
	this->shaders[DEMOD4]->setMat4fv(this->camera.projectionMat, "projectionMat");
	this->shaders[EMITD4]->use();
	this->shaders[EMITD4]->setMat4fv(this->camera.projectionMat, "projectionMat");
	this->shaders[TERRAIND4]->use();
	this->shaders[TERRAIND4]->setMat4fv(this->camera.projectionMat, "projectionMat");
	this->shaders[WATERD4]->use();
	this->shaders[WATERD4]->setMat4fv(this->camera.projectionMat, "projectionMat");
	this->shaders[PARTICLE4D]->use();
	this->shaders[PARTICLE4D]->setMat4fv(this->camera.projectionMat, "projectionMat");
	this->shaders[COORDNATE4D]->use();
	this->shaders[COORDNATE4D]->setMat4fv(this->camera.projectionMat, "projectionMat");
	this->shaders[TRAIL4D]->use();
	this->shaders[TRAIL4D]->setMat4fv(this->camera.projectionMat, "projectionMat");
	this->shaders[JOINT_LINE4D]->use();
	this->shaders[JOINT_LINE4D]->setMat4fv(this->camera.projectionMat, "projectionMat");
	this->shaders[FRAME4D]->use();
	this->shaders[FRAME4D]->setMat4fv(this->camera.projectionMat, "projectionMat");
	this->shaders[LIGHT_FRAME4D]->use();
	this->shaders[LIGHT_FRAME4D]->setMat4fv(this->camera.projectionMat, "projectionMat");
}

void Game::updateUniforms()
{
	//Update view matrix (camera)

	//this->shaders[OBJ]->use();
	//this->shaders[OBJ]->setVec3f(this->camera.position4D, "cameraPos");

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
	this->targetIcon = new Rectangle2D(SHOOTING);
}

void Game::startLevel(int level, const char* filePath)
{
	glClearColor(1.f, 1.f, 1.f, 1.f);
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
	this->hingeConstraintsVec.clear();
	this->waters4D.clear();
	this->rigidBodies4D.clear();
	this->dynamites4D.clear();
	this->dynamites4D2.clear();
	this->pointLights4D.clear();
	this->emitters4D.clear();
	this->startObjects(level, filePath);
	this->camera.set_camera_position4D(this->rigidBodies4D[0]);
	judge_objects(this->groups, this->camera.position4D, this->camera.forward4D, this->camera.wDir, this->objectLoadDistance);
	judge_groups(this->rigidBodies4D, this->dynamites4D2, this->groups, this->camera.position4D, this->blockLoadDistance);
	update_render_indices(this->rigidBodies4D, this->dynamites4D2, this->groups, this->walls4D, this->dynamites4D,this->sticks4D,this->springs4D, &this->renderIndices1, &this->renderIndices2, this->camera.position4D);
	sort_render_indices(&this->renderIndices1); sort_render_indices(&this->renderIndices2);
	update_collide_indices(this->rigidBodies4D, this->dynamites4D2, this->groups, this->walls4D, this->dynamites4D);
	//for (int i = 0; i < 64; i++) { savedLevelText[i] = ''; }
	//savedLevelText[0]='L', savedLevelText[1] = 'e', savedLevelText[2]='v', savedLevelText[3]='e', savedLevelText[4]='l',savedLevelText[5]= ' ', savedLevelText[6] = (char)(this->level), savedLevelText[7]='-', savedLevelText[8] = '1',
	update_water4d(this->waters4D, this->shaders[WALLD4], this->shaders[EMITD4]);
	update_point_light4d(this->pointLights4D, this->shaders[WALLD4], this->shaders[TERRAIND4]);
	this->updateDt();
}
void Game::judgeRender()
{
	this->judgetime1 += this->dt;
	this->judgetime3 += this->dt;

	if (this->judgetime1 > 0.13125f ) {
		judge_objects(this->groups, this->camera.position4D, this->camera.forward4D, this->camera.wDir, this->objectLoadDistance);
		this->judgetime1 = 0.f;
	}

	if (this->judgetime3 > 0.3125 * (float)(this->blockLoadDistance)/(length(this->camera.limitedVelocity4D)+0.04f)){
		judge_groups(this->rigidBodies4D, this->dynamites4D2, this->groups, this->camera.position4D, this->blockLoadDistance);
		this->judgetime3 = 0.f;
	}
}

void::Game::updateLights()
{
	for (size_t i(0); i < this->pointLights4D.size(); i++)
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
	//if (shift != 0){
	if (mode != -1){
		this->mode = mode;
	}
	else{
		int modeAfter(this->mode + shift);
		if (modeAfter >= SHOOTING && modeAfter <= AREA_DELETING){
			this->mode = modeAfter;
		}
		else{
			if (modeAfter < SHOOTING){
				this->mode = AREA_DELETING;
			}
			else{
				this->mode = SHOOTING;
			}
		}
	}
	this->targetIcon->textureIndex = this->mode;
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
	this->judgetime0 = 0.f;
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
	this->buildTag = "4D-Object";
	this->stickLength=3.f;
	this->springLength=3.f;
	this->springStrength=10.f;
	this->buildTexture = WHITEWALL;
	this->buildShader = WALLD4;
	this->isSpecular = true;
	this->metal = 0.f;
	this->buildColor = glm::vec4(1.f);
	this->isRandomColor = false;
	this->buildScale = glm::vec4(1.f);
	this->buildRotation = alg::bivec4();
	this->initialVelocity = glm::vec4(0.f);
	this->initialAngularVelocity = alg::bivec4();
	this->buildCol=HYPERCUBE;
	this->buildParameter = glm::vec4(1.f, 1.f, 1.265f, 0.25f);
	this->lightIntensity = 1.f;
	this->lightColor = glm::vec3(1.f);
	this->lightRadius = 10.f;
	this->isIlluminate = false;
	this->isGravity = true;
	this->isTrail4D = true;
	this->isJointLine4D = true;

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
	this->skybox4D = new Sky_Box4D("Sky4d", Box4d(glm::vec4(100000.f)), alg::bivec4(), glm::vec4(100000.f), SKY_BOXD4);
	this->directionLight4D = new DirectionLight4D(PARTICLE1, alg::bivec4(0.f, -90.f), glm::vec3(1.f), 1.f);
	this->startLevel(this->level, "");
}
//Destructors
Game::~Game()
{
	glfwDestroyWindow(this->window);
	glfwTerminate();
	end_imgui();
	this->shader_2D_Shape = nullptr,delete this->shader_2D_Shape;
	this->rectangle2D = nullptr,delete this->rectangle2D;
	for (Shader* i : this->shaders) {i = nullptr, delete i;}
	for (Texture* i : this->textures) { i = nullptr, delete i;}
	for (Texture* i : this->pointerTexs) { i = nullptr, delete i;}
	delete this->deleteMap3D, this->deleteMap3D = nullptr;
	for (Texture3D* i : this->textures3D) { i = nullptr, delete i;}
	for (Texture3D* i : this->particleTexs3D) { delete i;  i = nullptr; }
	for (Texture3D* i : this->wallTexs3D) { i = nullptr, delete i;}
	for (Texture3D* i : this->groundTexs3D) { i = nullptr, delete i;}
	for (Sound* i : this->sounds) { i = nullptr, delete i;}
	for (Music* i : this->musics) { i = nullptr, delete i;}
	for (Object* i : this->objects) { i = nullptr, delete i;}
	this->skybox4D = nullptr,delete this->skybox4D;
	this->coordinate4D = nullptr,delete this->coordinate4D;
	this->targetIcon = nullptr,delete this->targetIcon;
	this->demoObjects4D = nullptr,delete this->demoObjects4D;
	for (Demo4D* i : this->demos4D) { i = nullptr, delete i;}
	for (JointLine4D* i : this->dragLines4D) { i = nullptr, delete i;}
	for (Input* i : this->inputs) { i = nullptr, delete i;}
	for (Wall4D* i : this->walls4D) { i = nullptr, delete i;}
	for (Wall4D* i : this->dynamites4D) { i = nullptr, delete i;}
	for (RigidBody4D* i : this->dynamites4D2) { i = nullptr, delete i;}
	for (RigidBody4D* i : this->rigidBodies4D) { i = nullptr, delete i;}
	for (Terrain4D* i : this->terrains4D) { i = nullptr, delete i;}
	for (Water4D* i : this->waters4D) { i = nullptr, delete i;}
	for (Group* i : this->groups) { i = nullptr, delete i;}
	for (Emitter4D* i : this->emitters4D) { i = nullptr, delete i;}
	for (RenderIndex* i : this->renderIndices1) { i = nullptr, delete i;}
	for (RenderIndex* i : this->renderIndices2) { i = nullptr, delete i;}
	for (PointLight* i : this->pointLights) { i = nullptr, delete i;}
	for (DirectionLight* i : this->directionLights) { i = nullptr, delete i;}
	for (PointLight4D* i : this->pointLights4D) { i = nullptr, delete i;}
	this->directionLight4D = nullptr,delete this->directionLight4D;
	for (Stick4D* i : this->sticks4D) { i = nullptr, delete i;}
	for (Spring4D* i : this->springs4D) { i = nullptr, delete i;}
	for (Shift4D* i : this->shifts4D) { i = nullptr, delete i;}
	for (Float4D* i : this->floats4D) { i = nullptr, delete i;}
	for (Rotate4D* i : this->rotates4D) { i = nullptr, delete i;}
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
	}
	if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_1) != GLFW_RELEASE){
		this->firstMouse = true;
	}
	else{
		this->firstMouse2 = true;
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
		phy::before_render_physic4D(this->rigidBodies4D, this->dynamites4D2, this->groups, this->walls4D,this->dynamites4D, this->sticks4D, this->springs4D,this->isTrail4D, 1.f/60.f,this->curTime);
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
					this->demoObjects4D->walls4D[0]->set_position4D(get_cap_position4D(this->hittingPos4D + glm::vec4(0.f, this->buildScale.y / 2.f, 0.f, 0.f)));
					this->demoObjects4D->walls4D[0]->set_rotation4D(this->buildRotation);
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
					this->demoObjects4D->rigidBodies4D[0]->set_position4D(this->hittingPos4D + glm::vec4(0.f, this->buildScale.y / 2.f, 0.f, 0.f));
					this->demoObjects4D->rigidBodies4D[0]->set_rotation4D(this->buildRotation);
					this->demoObjects4D->rigidBodies4D[0]->set_scale4D(this->buildScale);
					break;
				}
				case BUILD_POOL_TABLE:
				{
					for (size_t i = 0; i < this->demos4D[26]->walls4D.size(); i++)
					{
						this->demoObjects4D->walls4D.push_back(this->demos4D[26]->walls4D[i]);
						this->demoObjects4D->walls4D[i]->set_mesh_position4D(this->demos4D[26]->walls4D[i]->position4D + get_cap_position4D(this->hittingPos4D));
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
				this->hitIndex = ray::detect_object4d_index(this->rigidBodies4D, this->dynamites4D2, this->groups, this->walls4D, this->dynamites4D, this->sticks4D, this->springs4D, true,false, true, false, this->camera.position4D, this->camera.forward4D, this->camera.right4D, &this->hitPosNear);
				if (this->hitIndex > -1)
				{
					if (this->hitIndex >= size_of_objects4d(this->rigidBodies4D, this->dynamites4D2, this->groups, this->walls4D) || this->hitIndex < size_of_objects4d(this->rigidBodies4D, this->dynamites4D2, this->groups))
					{
						bool isInitial(true);
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
								this->demoObjects4D->stick4D->set_stick_length(this->stickLength);
							}
							if (this->sticks4D.size() != 0)
							{
								if (this->sticks4D[this->sticks4D.size() - 1]->index2 == -1)
								{
									this->demoObjects4D->stick4D = this->demos4D[30]->stick4D;
									this->demoObjects4D->stick4D->fixPoint4D = this->camera.frontPosition4D;
									this->demoObjects4D->stick4D->index1 = this->sticks4D[this->sticks4D.size() - 1]->index1;
									this->demoObjects4D->stick4D->index2 = this->sticks4D[this->sticks4D.size() - 1]->index1 == this->hitIndex ? -1 : this->hitIndex;
									this->demoObjects4D->stick4D->set_stick_length(this->stickLength);
								}
								if (this->sticks4D[this->sticks4D.size() - 1]->index2 != -1)
								{
									this->demoObjects4D->stick4D = this->demos4D[30]->stick4D;
									this->demoObjects4D->stick4D->fixPoint4D = this->camera.frontPosition4D;
									this->demoObjects4D->stick4D->index1 = this->hitIndex;
									this->demoObjects4D->stick4D->index2 = -1;
									this->demoObjects4D->stick4D->set_stick_length(this->stickLength);
								}
							}
							if (this->demoObjects4D->stick4D != nullptr)
								phy::update_stick4D(this->rigidBodies4D, this->dynamites4D2, this->groups, this->walls4D, this->dynamites4D, this->demoObjects4D->stick4D);
						}
					}
				}
			} else
			if (this->buildMode == BUILD_SPRING)
			{
				this->hitIndex = ray::detect_object4d_index(this->rigidBodies4D, this->dynamites4D2, this->groups, this->walls4D, this->dynamites4D, this->sticks4D, this->springs4D, true,false, true, false, this->camera.position4D, this->camera.forward4D, this->camera.right4D, &this->hitPosNear);
				if (this->hitIndex > -1)
				{
					if (this->hitIndex >= size_of_objects4d(this->rigidBodies4D, this->dynamites4D2, this->groups, this->walls4D) || this->hitIndex < size_of_objects4d(this->rigidBodies4D, this->dynamites4D2, this->groups))
					{
						bool isInitial(true);
						if (this->sticks4D.size() != 0)
						{
							if (this->sticks4D[this->sticks4D.size() - 1]->index2 == -1)
							{
								isInitial = false;
								this->demoObjects4D->stick4D = this->demos4D[30]->stick4D;
								this->demoObjects4D->stick4D->fixPoint4D = this->camera.frontPosition4D;
								this->demoObjects4D->stick4D->index1 = this->sticks4D[this->sticks4D.size() - 1]->index1;
								this->demoObjects4D->stick4D->index2 = this->sticks4D[this->sticks4D.size() - 1]->index1 == this->hitIndex ? -1 : this->hitIndex;
								this->demoObjects4D->stick4D->set_stick_length(this->stickLength);
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
	this->judgetime0 += this->dt;
	if (this->judgetime0 > 0.13125f) {
		update_render_indices(this->rigidBodies4D, this->dynamites4D2, this->groups, this->walls4D, this->dynamites4D, this->sticks4D, this->springs4D, &this->renderIndices1, &this->renderIndices2, this->camera.position4D);
		sort_render_indices(&this->renderIndices1); sort_render_indices(&this->renderIndices2);
		this->judgetime0 = 0.f;
	}
	//Update the lights
	this->updateLights();
	//Update the uniforms
	this->updateUniforms();
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
	//1:OBJS NOT TRANSPARENT
	glLineWidth(1.f);

	for (size_t index(0); index < this->renderIndices1.size(); index++)
	{
		RenderIndex* i(this->renderIndices1[index]);
		if (i->groupIndex > -1)
		{
			Wall4D* a(this->groups[i->groupIndex]->walls4D[i->objectIndex]);
			a->render(this->wallTexs3D[a->texture3DIndex],this->shaders[a->shaderIndex]);
		}
		else if (i->groupIndex == -1)
		{
			RigidBody4D* a(find_rigidbody4d(this->rigidBodies4D, this->dynamites4D2, i->objectIndex));
			a->render(this->wallTexs3D[a->texture3DIndex], this->shaders[a->shaderIndex]);
		}
		else if (i->groupIndex == -2)
		{
			Wall4D* a(find_wall4d(this->walls4D, this->dynamites4D, i->objectIndex));
			a->render(this->wallTexs3D[a->texture3DIndex], this->shaders[a->shaderIndex]);
		}
		else if (i->groupIndex == -3)
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
			for (Terrain4D* j : i->terrains4D) {
				if (j->isClamp) {
					if (j->isFront)
					{
						j->render(this->shaders[j->shaderIndex]);
					}
				}
			}
		}
	}
	for (Terrain4D* j : this->terrains4D)
	{
		j->render(this->shaders[j->shaderIndex]);
	}
	if (this->frameType == 1)
	{
		for (Group* i : this->groups) {
			if (i->isRender) {
				for (Wall4D* j : i->walls4D) {
					if (j->isFront) {
						j->render_frame(this->shaders[FRAME4D]);
					}
				}
			}
		}
		for (Wall4D* j : this->walls4D) {
			j->render_frame(this->shaders[FRAME4D]);
		}
		for (Wall4D* j : this->dynamites4D) {
			j->render_frame(this->shaders[FRAME4D]);
		}
		for (RigidBody4D* j : this->dynamites4D2) {
			j->render_frame(this->shaders[FRAME4D]);
		}
		for (RigidBody4D* j : this->rigidBodies4D) {
			j->render_frame(this->shaders[FRAME4D]);
		}
		for (Stick4D* i : this->sticks4D)
		{
			if (i->index2 != -1)
			{
				i->render_frame(this->shaders[FRAME4D]);
			}
		}
		for (Spring4D* i : this->springs4D)
		{
			if (i->index2 != -1)
			{
				i->render_frame(this->shaders[FRAME4D]);
			}
		}
		if (this->mode == BUILDING) {
			if (!(this->buildMode == BUILD_STICK || this->buildMode == BUILD_SPRING))
			{
				if (this->isFindPoint) {
					for (Wall4D* j : this->demoObjects4D->walls4D)
					{
						j->render_frame(this->shaders[FRAME4D]);
					}
					for (RigidBody4D* j : this->demoObjects4D->rigidBodies4D)
					{
						j->render_frame(this->shaders[FRAME4D]);
					}
				}
			}
			else
			{
				if (this->demoObjects4D->stick4D != nullptr)
				{
					this->demoObjects4D->stick4D->render_frame(this->shaders[FRAME4D]);
				}
				if (this->demoObjects4D->spring4D != nullptr)
				{
					this->demoObjects4D->spring4D->render_frame(this->shaders[FRAME4D]);
				}
			}
		}
		glLineWidth(1.9f);
		for (Emitter4D* i : this->emitters4D)
		{
			for (Particle4D* j : i->particles4D)
			{
				if (j->isGlowing) { glBlendFunc(GL_SRC_ALPHA, GL_ONE); }
				else { glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); }
				j->render_frame(this->shaders[LIGHT_FRAME4D]);
			}
		}
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		for (PointLight4D* p : this->pointLights4D) {
			p->render_frame(this->shaders[LIGHT_FRAME4D]);
		}
		this->directionLight4D->render_frame(this->shaders[LIGHT_FRAME4D]);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	glLineWidth(1.9f);
	if (isJointLine4D)
	{
		for (Stick4D* i : this->sticks4D)
		{
			if (i->index2 != -1)
			{
				i->render_line4D(this->shaders[JOINT_LINE4D]);
			}
		}
		for (Spring4D* i : this->springs4D)
		{
			if (i->index2 != -1)
			{
				i->render_line4D(this->shaders[JOINT_LINE4D]);
			}
		}
		if (this->mode == BUILDING) {
			if (this->buildMode == BUILD_STICK || this->buildMode == BUILD_SPRING)
			{
				if (this->demoObjects4D->stick4D != nullptr)
				{
					this->demoObjects4D->stick4D->render_line4D(this->shaders[JOINT_LINE4D]);
				}
				if (this->demoObjects4D->spring4D != nullptr)
				{
					this->demoObjects4D->spring4D->render_line4D(this->shaders[JOINT_LINE4D]);
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
		for (Particle4D* j : i->particles4D)
		{
			if (j->isGlowing) glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			else glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			j->render(this->particleTexs3D[j->texture3Dindex],this->shaders[PARTICLE4D]);
		}
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	for (PointLight4D* p : this->pointLights4D) {
		p->render(this->particleTexs3D[p->texture3DIndex], this->shaders[PARTICLE4D]);
	}

	glDepthMask(true);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (JointLine4D* i : this->dragLines4D)
	{
		i->render(this->shaders[JOINT_LINE4D]);
	}
	//
	//4:TRANSPARENT OBJS
	glLineWidth(1.f);
	//glDepthMask(false);
	//glDepthFunc(GL_ALWAYS);
	//std::cout << "render start:" << "\n";
	for (int index(this->renderIndices2.size() - 1); index >= 0; index--)
	{
		RenderIndex* i(this->renderIndices2[index]);
		if (i->groupIndex > -1)
		{
			Wall4D* a(this->groups[i->groupIndex]->walls4D[i->objectIndex]);
			a->render(this->wallTexs3D[a->texture3DIndex], this->shaders[a->shaderIndex]);
		}
		if (i->groupIndex == -1)
		{
			RigidBody4D* a(find_rigidbody4d(this->rigidBodies4D, this->dynamites4D2, i->objectIndex));
			a->render(this->wallTexs3D[a->texture3DIndex], this->shaders[a->shaderIndex]);
		}
		if (i->groupIndex == -2)
		{
			Wall4D* a(find_wall4d(this->walls4D, this->dynamites4D, i->objectIndex));
			a->render(this->wallTexs3D[a->texture3DIndex], this->shaders[a->shaderIndex]);
		}
		if (i->groupIndex == -3)
		{
			if (i->objectIndex < this->sticks4D.size())
			{
				Stick4D* stick4D(this->sticks4D[i->objectIndex]);
				stick4D->render(this->wallTexs3D[stick4D->texture3DIndex], this->shaders[stick4D->shaderIndex]);
			}
			else if (i->objectIndex < size_of_objects4d(this->sticks4D, this->springs4D))
			{
				Spring4D* springs4D(this->springs4D[i->objectIndex - this->sticks4D.size()]);
				springs4D->render(this->wallTexs3D[springs4D->texture3DIndex], this->shaders[springs4D->shaderIndex]);
			}
		}
	}
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
	if (this->isTrail4D) {
		for (RigidBody4D* i : this->rigidBodies4D)
		{
			i->trail4D->render(this->shaders[TRAIL4D]);
		}
		for (RigidBody4D* i : this->dynamites4D2)
		{
			i->trail4D->render(this->shaders[TRAIL4D]);
		}
	}
	for (Water4D* a : this->waters4D) {
		a->render(this->shaders[a->shaderIndex]);
	}
	//glDepthFunc(GL_LESS);
	//glDepthMask(true);
	//
	//5:LENS FLARE
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	if (ray::is_in_screen(-this->directionLight4D->direction4D, camera.viewMat4D, camera.projectionMat))
	{
		glm::vec4 hitPosNear2;
		if (ray::detect_object4d_index(this->rigidBodies4D, this->dynamites4D2, this->groups, this->walls4D, this->dynamites4D, this->sticks4D, this->springs4D, true, true, false, true, this->camera.position4D, -this->directionLight4D->direction4D, this->directionLight4D->right4D, &hitPosNear2) == -1)
		{
			glDepthMask(false);
			this->directionLight4D->render_lens_flare(this->camera.forward4D, this->particleTexs3D[this->directionLight4D->texture3DIndex],this->particleTexs3D[PARTICLE2], this->shaders[PARTICLE4D]);
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
		glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_COLOR);
		this->targetIcon->render(this->pointerTexs[this->mode],this->shader_2D_Shape);
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