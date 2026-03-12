#include "TemplateScene.hpp"

TemplateScene::TemplateScene() :
	Scene(244, 244, 10)
{
	filePath_ = "sprite/Example.jpg";
	key_ = "Example";
}

TemplateScene::~TemplateScene() {}

// Load Textures, Make Sprite Sheets, Make Sprites, etc (Load and Make Assets)... Add root game objects that will be at there at scene start
void TemplateScene::init() {
	std::cout << "TemplateScene::init : Currently Loaded Scene is TemplateScene" << std::endl;

	// Loading sprite textures from file path
	TextureRegistry::getInstance().loadTexture(filePath_);

	// Making a sprite sheet
	SpriteSheetRegistry::getInstance().makeSpriteSheet(
		key_,
		TextureRegistry::getInstance().getTextureID(filePath_),
		10, 10,
		{ 0, 0 }, { 9, 9 }
	);

	// Making a sprite
	SpriteRegistry::getInstance().makeSprite(
		key_,
		TextureRegistry::getInstance().getTextureID(filePath_),
		1, 1,
		{ 0, 0 }
	);


	// Just showing errors
	TextureRegistry::getInstance().loadTexture(filePath_);
	SpriteSheetRegistry::getInstance().makeSpriteSheet(
		key_,
		TextureRegistry::getInstance().getTextureID(filePath_),
		6, 1,
		{ 0, 0 }, { 5, 0 }
	);
	SpriteRegistry::getInstance().makeSprite(
		key_,
		TextureRegistry::getInstance().getTextureID(filePath_),
		1, 1,
		{ 0, 0 }
	);
	SpriteSheetRegistry::getInstance().getSpriteSheet("NOT key_");

	// Printing update information
	std::cout << "MainScene::init : Animation updates " << animationUpdatesPerSecond_ << " times per second " << std::endl;
	std::cout << "MainScene::init : Game updates " << updatesPerSecond_ << " times per second " << std::endl;
	std::cout << "MainScene::init : Frame updates " << framesPerSeconds_ << " times per second " << std::endl;

	// Make it so GameObjects get passed the keys to the Assets they use
	addRootGameObject2D(std::make_unique<StaticSprite>(
		Transform2D({ Vector2D({ -0.5f, 0.0f }),
		Vector2D({ 0.5f, 0.5f }),
		0.0f,
		false,
		false, }),
		key_
		)
	);
	addRootGameObject2D(std::make_unique<AnimatedSprite>(
		Transform2D({ Vector2D({ 0.5f, 0.0f }),
		Vector2D({ 0.5f, 0.5f }),
		0.0f,
		false,
		false, }),
		key_
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

// If you need to do SceneChanges include the SceneSpecific.hpp and Game.hpp here (In the ThisScene.cpp)
// Otherwise some really annoying circular dependencies are going to happen with Game and Scenes

// Im going to find a better way to do this TOMORROW
#include "ArchiveScene.hpp"
#include "Game.hpp"


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
		Game::getInstance().changeScene(std::make_unique<ArchiveScene>());
	}
}