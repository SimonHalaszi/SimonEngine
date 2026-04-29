#include "GameScene.hpp"

GameScene::GameScene() :
	Scene(244, 244, 10)
{
	saveName_ = "GameScene";
	playerFilePath_ = "image/PlayerSheet.png";
	baseGrassFilePath_ = "image/BaseGrass.png";
	appleTreeFilePath_ = "image/AppleTree.png";
	orangeTreeFilePath_ = "image/OrangeTree.png";
	foxireFilePath_ = "image/Foxire.png";
	foxireSheetFilePath_ = "image/FoxireSheet.png";
	ploistFilePath_ = "image/Ploist.png";
	ploistSheetFilePath_ = "image/PloistSheet.png";
	grandaFilePath_ = "image/Granda.png";
	grandaSheetFilePath_ = "image/GrandaSheet.png";
	norupFilePath_ = "image/Norup.png";
	norupSheetFilePath_ = "image/NorupSheet.png";
	shadowFilePath_ = "image/Shadow.png";


	playerDownKey_ = "playerDown";
	playerSidewaysKey_ = "playerSideways";
	playerUpKey_ = "playerUp";
	baseGrassKey_ = "baseGrass";
	appleTreeKey_ = "appleTree";
	orangeTreeKey_ = "orangeTree";
	foxireKey_ = "foxire";
	foxireSheetKey_ = "foxireSheet";
	ploistKey_ = "ploist";
	ploistSheetKey_ = "ploistSheet";
	grandaKey_ = "granda";
	grandaSheetKey_ = "grandaSheet";
	norupKey_ = "norup";
	norupSheetKey_ = "norupSheet";
	shadowKey_ = "shadow";
}

GameScene::~GameScene() {}

// Load Textures, Make Sprite Sheets, Make Sprites, etc (Load and Make Assets)... Add root game objects that will be at there at scene start
void GameScene::init() {
	std::cout << "TemplateScene::init : Currently Loaded Scene is TemplateScene" << std::endl;

	// Printing update information
	std::cout << "MainScene::init : Animation updates " << animationUpdatesPerSecond_ << " times per second " << std::endl;
	std::cout << "MainScene::init : Game updates " << updatesPerSecond_ << " times per second " << std::endl;
	std::cout << "MainScene::init : Frame updates " << framesPerSeconds_ << " times per second " << std::endl;

	// Play sounds
	SoundManager::getInstance().setMusicTrack("audio/GoingShopping.mp3");

	GLuint texID;
	texID = TextureRegistry::getInstance().loadTexture(baseGrassFilePath_);
	const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
		baseGrassKey_,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
	addRootGameObject2D(std::make_unique<NonColliderSprite>(
		Transform2D({
			Vector2D({ 0.0f, 0.0f }),
			Vector2D({ 1.0f, 1.0f }),
			0.0f,
			false,
			false,
			}),
			"BaseGrass",
			"BaseGrass",
			sprite
			)
	);

	texID = TextureRegistry::getInstance().loadTexture(shadowFilePath_);
	sprite = &SpriteRegistry::getInstance().makeSprite(
		shadowKey_,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
	);

	texID = TextureRegistry::getInstance().loadTexture(orangeTreeFilePath_);
	sprite = &SpriteRegistry::getInstance().makeSprite(
		orangeTreeKey_,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
	addRootGameObject2D(std::make_unique<ColliderSprite>(
		Transform2D({
			Vector2D({ 0.5f, 0.5f }),
			Vector2D({ 0.2f, 0.3f }),
			0.0f,
			false,
			false,
			}),
			"OrangeTree",
			"Collider",
			sprite
			)
	);

	texID = TextureRegistry::getInstance().loadTexture(foxireSheetFilePath_);
	const SpriteSheet* spriteSheet = &SpriteSheetRegistry::getInstance().makeSpriteSheet(
		foxireSheetKey_,
		texID,
		7,
		1,
		TileIndex({ 0, 0 }),
		TileIndex({ 6, 0 })
	);
	addRootGameObject2D(std::make_unique<Moneser>(
		Transform2D({
			Vector2D({ -0.8f, -0.5f }),
			Vector2D({ 0.1f, 0.1f }),
			0.0f,
			false,
			false,
			}),
			"Foxire",
			spriteSheet
			)
	);

	texID = TextureRegistry::getInstance().loadTexture(grandaSheetFilePath_);
	spriteSheet = &SpriteSheetRegistry::getInstance().makeSpriteSheet(
		grandaSheetKey_,
		texID,
		7,
		1,
		TileIndex({ 0, 0 }),
		TileIndex({ 6, 0 })
	);
	addRootGameObject2D(std::make_unique<Moneser>(
		Transform2D({
			Vector2D({ -0.3f, -0.5f }),
			Vector2D({ 0.1f, 0.1f }),
			0.0f,
			false,
			false,
			}),
			"Granda",
			spriteSheet
			)
	);

	texID = TextureRegistry::getInstance().loadTexture(ploistSheetFilePath_);
	spriteSheet = &SpriteSheetRegistry::getInstance().makeSpriteSheet(
		ploistSheetKey_,
		texID,
		7,
		1,
		TileIndex({ 0, 0 }),
		TileIndex({ 6, 0 })
	);
	addRootGameObject2D(std::make_unique<Moneser>(
		Transform2D({
			Vector2D({ 0.3f, -0.5f }),
			Vector2D({ 0.1f, 0.1f }),
			0.0f,
			false,
			false,
			}),
			"Ploist",
			spriteSheet
			)
	);

	texID = TextureRegistry::getInstance().loadTexture(norupSheetFilePath_);
	spriteSheet = &SpriteSheetRegistry::getInstance().makeSpriteSheet(
		norupSheetKey_,
		texID,
		7,
		1,
		TileIndex({ 0, 0 }),
		TileIndex({ 6, 0 })
	);
	addRootGameObject2D(std::make_unique<Moneser>(
		Transform2D({
			Vector2D({ 0.8f, -0.5f }),
			Vector2D({ 0.1f, 0.1f }),
			0.0f,
			false,
			false,
			}),
			"Norup",
			spriteSheet
			)
	);


	texID = TextureRegistry::getInstance().loadTexture(playerFilePath_);
	const SpriteSheet* spriteSheetDown = &SpriteSheetRegistry::getInstance().makeSpriteSheet(
		playerDownKey_,
		texID,
		4,
		3,
		TileIndex({ 0, 0 }),
		TileIndex({ 3, 0 })
	);
	const SpriteSheet* spriteSheetSideways = &SpriteSheetRegistry::getInstance().makeSpriteSheet(
		playerSidewaysKey_,
		texID,
		4,
		3,
		TileIndex({ 0, 1 }),
		TileIndex({ 3, 1 })
	);
	const SpriteSheet* spriteSheetUp = &SpriteSheetRegistry::getInstance().makeSpriteSheet(
		playerUpKey_,
		texID,
		4,
		3,
		TileIndex({ 0, 2 }),
		TileIndex({ 3, 2 })
	);

	// Make it so GameObjects get passed the assets, or dont
	addRootGameObject2D(std::make_unique<Player>(
		Transform2D({
			Vector2D({ 0.0f, 0.0f }),
			Vector2D({ 0.1f, 0.1f }),
			0.0f,
			false,
			false,
			}),
			"Player",
			"Player",
			spriteSheetDown,
			spriteSheetSideways,
			spriteSheetUp
			)
	);
}

// For scene/game specific drawing (Drawing that is not related to a GameObject)
void GameScene::draw() const {
	drawRectangle(
		Vector2D({ 0.0f, 0.0f }),
		Vector2D({ 10.0f, 10.0f }),
		0.0f,
		false, false,
		ColorRGB({1.0f, 1.0f, 1.0f}),
		ColorRGB({ 1.0f, 1.0f, 1.0f }),
		ColorRGB({ 1.0f, 1.0f, 1.0f }),
		ColorRGB({ 1.0f, 1.0f, 1.0f })
	);
}

// If you need to do SceneChanges include the SceneSpecific.hpp and Game.hpp here (In the ThisScene.cpp)
// Otherwise some really annoying circular dependencies are going to happen with Game and Scenes
// #include "SomeOtherScene.hpp"
#include "Game.hpp"
#include "TemplateScene.hpp"


// For scene/game specific updates/inputs (Updates/Inputs that are not related to GameObjects)
void GameScene::update() {
	// Example of how a scene input may change the Game class behavior
	if (InputManager::getInstance().isPressed('n')) {
		isDrawing_ = false;
	}
	if (InputManager::getInstance().isPressed('m')) {
		isDrawing_ = true;
	}
	if (InputManager::getInstance().isPressed('c')) {
		Game::getInstance().changeScene(std::make_unique<TemplateScene>());
	}
}