#include "TemplateScene.hpp"

TemplateScene::TemplateScene() :
	Scene(244, 244, 10)
{
	saveName_ = "TemplateScene";
	autoLoad_ = false;
}

TemplateScene::~TemplateScene() {}

// Load Textures, Make Sprite Sheets, Make Sprites, etc (Load and Make Assets)... Add root game objects that will be at there at scene start
void TemplateScene::init() {
	std::cout << "TemplateScene::init : Currently Loaded Scene is TemplateScene" << std::endl;

	// Printing update information
	std::cout << "TemplateScene::init : Animation updates " << animationUpdatesPerSecond_ << " times per second " << std::endl;
	std::cout << "TemplateScene::init : Game updates " << updatesPerSecond_ << " times per second " << std::endl;
	std::cout << "TemplateScene::init : Frame updates " << framesPerSeconds_ << " times per second " << std::endl;

	// Play sounds
	SoundManager::getInstance().setMusicTrack("audio/WhyAreSundaysSoDepressing.mp3");

	GLuint texID;

	// Make it so GameObjects get passed the assets
	texID = TextureRegistry::getInstance().loadTexture("image/Title.png");
	const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
		"Title", 
		texID, 
		1, 
		1, 
		{ 0, 0 }
	);
	addRootGameObject2D(std::make_unique<NonColliderSprite>(
		Transform2D({
			Vector2D({ 0.0f, 0.0f }),
			Vector2D({ 1.0f, 1.0f }),
			0.0f,
			false,
			false,
			}),
			"Title",
			"Title",
			sprite
			)
	);
}

// For scene/game specific drawing (Drawing that is not related to a GameObject)
void TemplateScene::draw() const {
	// For example this draws a background for the entire scene!
	drawSquare(
		{ 0.0f, 0.0f },
		1.0f,
		0.0f, false, false,
		{ 1.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f }
	);
}

#include "Game.hpp"
// #include "SomeOtherScene.hpp"

// For scene/game specific updates/inputs (Updates/Inputs that are not related to GameObjects)
void TemplateScene::update() {
	// Example of how a scene input may change the Game class behavior
	if (InputManager::getInstance().isPressed('c')) {
		isDrawing_ = false;
	}
	if (InputManager::getInstance().isPressed('m')) {
		isDrawing_ = true;
	}
	if (InputManager::getInstance().isPressed('n')) {
		// Game::getInstance().changeScene(std::make_unique<SomeOtherScene>());
	}
}