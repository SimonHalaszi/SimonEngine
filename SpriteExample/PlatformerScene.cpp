#include "PlatformerScene.hpp"

PlatformerScene::PlatformerScene() :
	Scene(60, 244, 10)
{
	// Initialize Filepaths
	playerSpriteSheetFilePath_ = "sprite/BillsGuy-sheet.png";
	turfTextureFilePath_ = "sprite/TurfTexture.jpg";
	skyboxTextureFilepath_ = "sprite/Background.jpg";
	concreteTextureFilePath_ = "sprite/Concrete.jpg";

	playerSpriteSheet_ = "PlayerSpriteSheet";
	turfSprite_ = "turfSprite";
	skyboxSprite_ = "skyboxSprite";
	concreteSprite_ = "concreteSprite";
}

PlatformerScene::~PlatformerScene() {}

// Load Textures, Make Sprite Sheets, Make Sprites, etc (Load and Make Assets)... Add root game objects that will be at there at scene start
void PlatformerScene::init() {
	std::cout << "TemplateScene::init : Currently Loaded Scene is TemplateScene" << std::endl;

	// Loading textures from file path
	TextureRegistry::getInstance().loadTexture(playerSpriteSheetFilePath_);
	TextureRegistry::getInstance().loadTexture(turfTextureFilePath_);
	TextureRegistry::getInstance().loadTexture(skyboxTextureFilepath_);
	TextureRegistry::getInstance().loadTexture(concreteTextureFilePath_);

	// Making player sprite sheet
	SpriteSheetRegistry::getInstance().makeSpriteSheet(
		playerSpriteSheet_,
		TextureRegistry::getInstance().getTextureID(playerSpriteSheetFilePath_),
		6, 1,
		{ 0, 0 }, { 5, 0 }
	);
	// Making sprites
	SpriteRegistry::getInstance().makeSprite(
		turfSprite_,
		TextureRegistry::getInstance().getTextureID(turfTextureFilePath_),
		1, 1,
		{ 0, 0 }
	);
	SpriteRegistry::getInstance().makeSprite(
		skyboxSprite_,
		TextureRegistry::getInstance().getTextureID(skyboxTextureFilepath_),
		1, 1,
		{ 0, 0 }
	);
	SpriteRegistry::getInstance().makeSprite(
		concreteSprite_,
		TextureRegistry::getInstance().getTextureID(concreteTextureFilePath_),
		1, 1,
		{ 0, 0 }
	);

	// Printing update information
	std::cout << "MainScene::init : Animation updates " << animationUpdatesPerSecond_ << " times per second " << std::endl;
	std::cout << "MainScene::init : Game updates " << updatesPerSecond_ << " times per second " << std::endl;
	std::cout << "MainScene::init : Frame updates " << framesPerSeconds_ << " times per second " << std::endl;

	// Root Game Objects
	addRootGameObject2D(std::make_unique<SpriteGameObject>(
		Transform2D({
			Vector2D({ 0.0f, 0.0f }),
			Vector2D({ 5.5f, 6.0f }),
			0.0f,
			false,
			false,
		}),
		skyboxSprite_,
		"Skybox"
		)
	);
	addRootGameObject2D(std::make_unique<StaticSprite>(
		Transform2D({
			Vector2D({ 0.0f, 2.0f }),
			Vector2D({ 5.5f, 0.5f }),
			0.0f,
			false,
			false,
		}),
		concreteSprite_,
		"Ceiling"
		)
	);
	addRootGameObject2D(std::make_unique<StaticSprite>(
		Transform2D({
			Vector2D({ 6.0f, 0.0f }),
			Vector2D({ 0.5f, 3.0f }),
			0.0f,
			false,
			false,
		}),
		concreteSprite_,
		"RightWall"
		)
	);
	addRootGameObject2D(std::make_unique<StaticSprite>(
		Transform2D({
			Vector2D({ -6.0f, 0.0f }),
			Vector2D({ 0.5f, 3.0f }),
			0.0f,
			false,
			false,
		}),
		concreteSprite_,
		"LeftWall"
		)
	);

	addRootGameObject2D(std::make_unique<SpriteObstacle>(
		Transform2D({
			Vector2D({ 1.0f, 0.25f }),
			Vector2D({ 0.25f, 0.25f }),
			0.0f,
			false,
			false,
			}),
			concreteSprite_
			)
	);
	addRootGameObject2D(std::make_unique<SpriteObstacle>(
		Transform2D({
			Vector2D({ -1.0f, -1.0f }),
			Vector2D({ 0.25f, 1.0f }),
			0.0f,
			false,
			false,
			}),
			concreteSprite_
			)
	);

	addRootGameObject2D(std::make_unique<StaticSprite>(
		Transform2D({
			Vector2D({ 0.0f, -1.0f }),
			Vector2D({ 5.5f, 0.5f }),
			0.0f,
			false,
			false,
		}),
		turfSprite_,
		"Floor"
		)
	);
	addRootGameObject2D(std::make_unique<PlatformerPlayer>(playerSpriteSheet_));
}

// For scene/game specific drawing (Drawing that is not related to a GameObject)
void PlatformerScene::draw() const { }

// For scene/game specific updates/inputs (Updates/Inputs that are not related to GameObjects)
void PlatformerScene::update() {
	// Example of how a scene input may change the Game class behavior
	if (InputManager::getInstance().isPressed('c')) {
		isDrawing_ = false;
	}
	if (InputManager::getInstance().isPressed('m')) {
		isDrawing_ = true;
	}
}