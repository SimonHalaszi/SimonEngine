#include "GameScene.hpp"

GameScene::GameScene() :
	Scene(244, 244, 10)
{
	saveName_ = "GameScene";
	houseOrgin_ = { 5.0f, 5.0f };
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
	
	loadMisc();
	
	createBaseArea();
	createMarshArea();
	createFireArea();
	createGrassArea();
	createHouseArea();
	createBackdrop();
	
	spawnMonesers();
	spawnPlayer();
}

// For scene/game specific drawing (Drawing that is not related to a GameObject)
void GameScene::draw() const {
	drawRectangle(
		Vector2D({ 0.0f, 0.0f }),
		Vector2D({ 10.0f, 10.0f }),
		0.0f,
		false, false,
		ColorRGB({ 0.0f, 0.0f, 0.0f }),
		ColorRGB({ 0.0f, 0.0f, 0.0f }),
		ColorRGB({ 0.0f, 0.0f, 0.0f }),
		ColorRGB({ 0.0f, 0.0f, 0.0f })
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

void GameScene::loadMisc() {
	std::string shadowFilePath = "image/Shadow.png";
	std::string shadowKey = "Shadow";
	// SHADOW SPRITE
	GLuint texID = TextureRegistry::getInstance().loadTexture(shadowFilePath);
	const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
		shadowKey,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
}

void GameScene::createMarshArea() {
	std::string baseFilePath = "image/BaseMarsh.png";
	std::string baseKey = "BaseMarsh";
	// MARSH AREA { (-3.0f - -1.0f), (-1.0f - 1.0f) }
	GLuint texID = TextureRegistry::getInstance().loadTexture(baseFilePath);
	const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
		baseKey,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
	addRootGameObject2D(std::make_unique<NonColliderSprite>(
		Transform2D({
			Vector2D({ -2.0f, 0.0f }),
			Vector2D({ 1.0f, 1.0f }),
			0.0f,
			false,
			false,
			}),
			"BaseMarsh",
			"BaseMarsh",
			sprite
			)
	);
	// END MARSH AREA
}

void GameScene::createFireArea() {
	std::string baseFilePath = "image/BaseFire.png";
	std::string baseKey = "BaseFire";
	// FIRE AREA { (-1.0f - 1.0f), (1.0f - 3.0f) }
	GLuint texID = TextureRegistry::getInstance().loadTexture(baseFilePath);
	const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
		baseKey,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
	addRootGameObject2D(std::make_unique<NonColliderSprite>(
		Transform2D({
			Vector2D({ 0.0f, 2.0f }),
			Vector2D({ 1.0f, 1.0f }),
			0.0f,
			false,
			false,
			}),
			"BaseFire",
			"BaseFire",
			sprite
			)
	);
	// FIRE MARSH AREA
}

void GameScene::createGrassArea() {
	std::string baseFilePath = "image/BaseGrass.png";
	std::string baseKey = "BaseGrass";
	std::string bushFilePath = "image/Bush.png";
	std::string bushKey = "Bush";
	std::string berryBushFilePath = "image/BerryBush.png";
	std::string berryBushKey = "BerryBush";
	std::string appleTreeFilePath = "image/AppleTree.png";
	std::string appleTreeKey = "AppleTree";
	std::string orangeTreeFilePath = "image/OrangeTree.png";
	std::string orangeTreeKey = "OrangeTree";
	// GRASS AREA { (-1.0f - 1.0f), (-1.0f - 1.0f) }
	GLuint texID = TextureRegistry::getInstance().loadTexture(baseFilePath);
	const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
		baseKey,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
	addRootGameObject2D(std::make_unique<NonColliderSprite>(
		Transform2D({
			Vector2D({ 2.0f, 0.0f }),
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
	texID = TextureRegistry::getInstance().loadTexture(bushFilePath);
	sprite = &SpriteRegistry::getInstance().makeSprite(
		bushKey,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
	addRootGameObject2D(std::make_unique<ColliderSprite>(
		Transform2D({
			Vector2D({ 2.5f, 0.5f }),
			Vector2D({ 0.1f, 0.1f }),
			0.0f,
			false,
			false,
			}),
			"Bush",
			"Collider",
			sprite
			)
	);
	texID = TextureRegistry::getInstance().loadTexture(berryBushFilePath);
	sprite = &SpriteRegistry::getInstance().makeSprite(
		berryBushFilePath,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
	addRootGameObject2D(std::make_unique<ColliderSprite>(
		Transform2D({
			Vector2D({ 1.5f, -0.5f }),
			Vector2D({ 0.1f, 0.1f }),
			0.0f,
			false,
			false,
			}),
			"BerryBush",
			"Collider",
			sprite
			)
	);
	texID = TextureRegistry::getInstance().loadTexture(appleTreeFilePath);
	sprite = &SpriteRegistry::getInstance().makeSprite(
		appleTreeKey,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
	addRootGameObject2D(std::make_unique<ColliderSprite>(
		Transform2D({
			Vector2D({ 2.5f, -0.7f }),
			Vector2D({ 0.2f, 0.3f }),
			0.0f,
			false,
			false,
			}),
			"AppleTree",
			"Collider",
			sprite
			)
	);
	texID = TextureRegistry::getInstance().loadTexture(orangeTreeFilePath);
	sprite = &SpriteRegistry::getInstance().makeSprite(
		orangeTreeKey,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
	addRootGameObject2D(std::make_unique<ColliderSprite>(
		Transform2D({
			Vector2D({ 1.5f, 0.7f }),
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
	// END GRASS AREA
}

void GameScene::createBaseArea() {
	std::string baseFilePath = "image/BaseGrass.png";
	std::string baseKey = "BaseGrass";
	std::string houseFilePath = "image/House.png";
	std::string houseKey = "House";
	// BASE AREA { (-1.0f - 1.0f), (-1.0f - 1.0f) }
	GLuint texID = TextureRegistry::getInstance().loadTexture(baseFilePath);
	const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
		baseKey,
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
	texID = TextureRegistry::getInstance().loadTexture(houseFilePath);
	sprite = &SpriteRegistry::getInstance().makeSprite(
		houseKey,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
	addRootGameObject2D(std::make_unique<ColliderSprite>(
		Transform2D({
			Vector2D({ 0.0f, 0.0f }),
			Vector2D({ 0.3f, 0.3f }),
			0.0f,
			false,
			false,
			}),
			"House",
			"Collider",
			sprite
			)
	);
	// END BASE AREA
}

void GameScene::spawnMonesers() {
	std::string foxireSheetFilePath = "image/FoxireSheet.png";
	std::string foxireSheetKey = "Foxire";
	std::string grandaSheetFilePath = "image/GrandaSheet.png";
	std::string grandaSheetKey = "Granda";
	std::string ploistSheetFilePath = "image/PloistSheet.png";
	std::string ploistSheetKey = "Ploist";
	std::string norupSheetFilePath = "image/NorupSheet.png";
	std::string norupSheetKey = "Norup";
	GLuint texID = TextureRegistry::getInstance().loadTexture(foxireSheetFilePath);
	const SpriteSheet* spriteSheet = &SpriteSheetRegistry::getInstance().makeSpriteSheet(
		foxireSheetKey,
		texID,
		7,
		1,
		TileIndex({ 0, 0 }),
		TileIndex({ 6, 0 })
	);
	addRootGameObject2D(std::make_unique<Moneser>(
		Transform2D({
			Vector2D({ 0.0f, 2.2f }),
			Vector2D({ 0.1f, 0.1f }),
			0.0f,
			false,
			false,
			}),
			"Foxire",
			spriteSheet
			)
	);
	texID = TextureRegistry::getInstance().loadTexture(grandaSheetFilePath);
	spriteSheet = &SpriteSheetRegistry::getInstance().makeSpriteSheet(
		grandaSheetKey,
		texID,
		7,
		1,
		TileIndex({ 0, 0 }),
		TileIndex({ 6, 0 })
	);
	addRootGameObject2D(std::make_unique<Moneser>(
		Transform2D({
			Vector2D({ 2.2f, 0.0f }),
			Vector2D({ 0.1f, 0.1f }),
			0.0f,
			false,
			false,
			}),
			"Granda",
			spriteSheet
			)
	);
	texID = TextureRegistry::getInstance().loadTexture(ploistSheetFilePath);
	spriteSheet = &SpriteSheetRegistry::getInstance().makeSpriteSheet(
		ploistSheetKey,
		texID,
		7,
		1,
		TileIndex({ 0, 0 }),
		TileIndex({ 6, 0 })
	);
	addRootGameObject2D(std::make_unique<Moneser>(
		Transform2D({
			Vector2D({ -2.6f, 0.6f }),
			Vector2D({ 0.1f, 0.1f }),
			0.0f,
			false,
			false,
			}),
			"Ploist",
			spriteSheet
			)
	);

	texID = TextureRegistry::getInstance().loadTexture(norupSheetFilePath);
	spriteSheet = &SpriteSheetRegistry::getInstance().makeSpriteSheet(
		norupSheetKey,
		texID,
		7,
		1,
		TileIndex({ 0, 0 }),
		TileIndex({ 6, 0 })
	);
	addRootGameObject2D(std::make_unique<Moneser>(
		Transform2D({
			Vector2D({houseOrgin_.x - 0.4f, houseOrgin_.y + 0.4f}),
			Vector2D({ 0.1f, 0.1f }),
			0.0f,
			false,
			false,
			}),
			"Norup",
			spriteSheet
			)
	);
}

void GameScene::spawnPlayer() {
	std::string playerFilePath = "image/PlayerSheet.png";
	std::string playerDownKey = "PlayerDown";
	std::string playerSidewaysKey = "PlayerSideways";
	std::string playerUpKey = "PlayerUp";
	GLuint texID = TextureRegistry::getInstance().loadTexture(playerFilePath);
	const SpriteSheet* spriteSheetDown = &SpriteSheetRegistry::getInstance().makeSpriteSheet(
		playerDownKey,
		texID,
		4,
		3,
		TileIndex({ 0, 0 }),
		TileIndex({ 3, 0 })
	);
	const SpriteSheet* spriteSheetSideways = &SpriteSheetRegistry::getInstance().makeSpriteSheet(
		playerSidewaysKey,
		texID,
		4,
		3,
		TileIndex({ 0, 1 }),
		TileIndex({ 3, 1 })
	);
	const SpriteSheet* spriteSheetUp = &SpriteSheetRegistry::getInstance().makeSpriteSheet(
		playerUpKey,
		texID,
		4,
		3,
		TileIndex({ 0, 2 }),
		TileIndex({ 3, 2 })
	);
	// Make it so GameObjects get passed the assets, or dont
	addRootGameObject2D(std::make_unique<Player>(
		Transform2D({
			Vector2D({houseOrgin_.x, houseOrgin_.y}),
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

void GameScene::createHouseArea() {
	std::string houseFloorFilePath = "image/HouseFloor.png";
	std::string houseFloorKey = "HouseFloor";
	std::string houseWallFilePath = "image/HouseWall.png";
	std::string houseWallKey = "HouseWall";
	std::string chairFilePath = "image/Chair.png";
	std::string chairKey = "Chair";
	std::string rugFilePath = "image/Rug.png";
	std::string rugKey = "Rug";
	std::string blankFilePath = "image/Blank.png";
	std::string blankKey = "Blank";
	GLuint texID = TextureRegistry::getInstance().loadTexture(houseFloorFilePath);
	const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
		houseFloorKey,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
	addRootGameObject2D(std::make_unique<NonColliderSprite>(
		Transform2D({
			houseOrgin_,
			Vector2D({ 0.5f, 0.5f }),
			0.0f,
			false,
			false,
			}),
			"HouseFloor",
			"HouseFloor",
			sprite
			)
	);
	texID = TextureRegistry::getInstance().loadTexture(houseWallFilePath);
	sprite = &SpriteRegistry::getInstance().makeSprite(
		houseWallKey,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
	addRootGameObject2D(std::make_unique<ColliderSprite>(
		Transform2D({
			Vector2D({houseOrgin_.x, houseOrgin_.y + 0.7f}),
			Vector2D({ 0.5f, 0.2f }),
			0.0f,
			false,
			false,
			}),
			"HouseWall",
			"Collider",
			sprite
			)
	);
	texID = TextureRegistry::getInstance().loadTexture(chairFilePath);
	sprite = &SpriteRegistry::getInstance().makeSprite(
		chairKey,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
	addRootGameObject2D(std::make_unique<ColliderSprite>(
		Transform2D({
			Vector2D({houseOrgin_.x + 0.4f, houseOrgin_.y + 0.4f}),
			Vector2D({ 0.1f, 0.1f }),
			0.0f,
			false,
			false,
			}),
			"Chair",
			"Collider",
			sprite
			)
	);
	texID = TextureRegistry::getInstance().loadTexture(rugFilePath);
	sprite = &SpriteRegistry::getInstance().makeSprite(
		rugKey,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
	addRootGameObject2D(std::make_unique<ColliderSprite>(
		Transform2D({
			Vector2D({houseOrgin_.x, houseOrgin_.y - 0.4f}),
			Vector2D({ 0.3f, 0.1f }),
			0.0f,
			false,
			false,
			}),
			"Rug",
			"Teleporter",
			sprite
			)
	);
	texID = TextureRegistry::getInstance().loadTexture(blankFilePath);
	sprite = &SpriteRegistry::getInstance().makeSprite(
		blankKey,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
	addRootGameObject2D(std::make_unique<ColliderSprite>(
		Transform2D({
			Vector2D({houseOrgin_.x, houseOrgin_.y - 0.6f}),
			Vector2D({ 0.5f, 0.1f }),
			0.0f,
			false,
			false,
			}),
			"House Binder",
			"Collider",
			sprite
			)
	);
	addRootGameObject2D(std::make_unique<ColliderSprite>(
		Transform2D({
			Vector2D({houseOrgin_.x - 0.6f, houseOrgin_.y}),
			Vector2D({ 0.1f, 0.5f }),
			0.0f,
			false,
			false,
			}),
			"House Binder",
			"Collider",
			sprite
			)
	);
	addRootGameObject2D(std::make_unique<ColliderSprite>(
		Transform2D({
			Vector2D({houseOrgin_.x + 0.6f, houseOrgin_.y}),
			Vector2D({ 0.1f, 0.5f }),
			0.0f,
			false,
			false,
			}),
			"House Binder",
			"Collider",
			sprite
			)
	);
}

void GameScene::createBackdrop() {
	std::string cliffFilePath = "image/Cliff.png";
	std::string cliffKey = "Cliff";
	std::string cliffTopFilePath = "image/CliffTop.png";
	std::string cliffTopKey = "CliffTop";
	std::string shoreFilePath = "image/Shore.png";
	std::string shoreKey = "Shore";
	std::string stoneShoreFilePath = "image/StoneShore.png";
	std::string stoneShoreKey = "StoneShore";
	GLuint texID = TextureRegistry::getInstance().loadTexture(cliffFilePath);
	const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
		cliffKey,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
	addRootGameObject2D(std::make_unique<ColliderSprite>(
		Transform2D({
			Vector2D({ 0.0f, 4.0f }),
			Vector2D({ 1.0f, 1.0f }),
			0.0f,
			false,
			false,
			}),
			"Cliff",
			"Collider",
			sprite
			)
	);
	addRootGameObject2D(std::make_unique<ColliderSprite>(
		Transform2D({
			Vector2D({ 2.0f, 2.0f }),
			Vector2D({ 1.0f, 1.0f }),
			0.0f,
			false,
			false,
			}),
			"Cliff",
			"Collider",
			sprite
			)
	);
	addRootGameObject2D(std::make_unique<ColliderSprite>(
		Transform2D({
			Vector2D({ -2.0f, 2.0f }),
			Vector2D({ 1.0f, 1.0f }),
			0.0f,
			false,
			false,
			}),
			"Cliff",
			"Collider",
			sprite
			)
	);
	addRootGameObject2D(std::make_unique<ColliderSprite>(
		Transform2D({
			Vector2D({ -4.0f, 00.0f }),
			Vector2D({ 1.0f, 1.0f }),
			0.0f,
			false,
			false,
			}),
			"Cliff",
			"Collider",
			sprite
			)
	);
	addRootGameObject2D(std::make_unique<ColliderSprite>(
		Transform2D({
			Vector2D({ 4.0f, 0.0f }),
			Vector2D({ 1.0f, 1.0f }),
			0.0f,
			false,
			false,
			}),
			"Cliff",
			"Collider",
			sprite
			)
	);
	texID = TextureRegistry::getInstance().loadTexture(shoreFilePath);
	sprite = &SpriteRegistry::getInstance().makeSprite(
		shoreKey,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
	addRootGameObject2D(std::make_unique<ColliderSprite>(
		Transform2D({
			Vector2D({ 0.0f, -2.0f }),
			Vector2D({ 1.0f, 1.0f }),
			0.0f,
			false,
			false,
			}),
			"Shore",
			"Collider",
			sprite
			)
	);
	addRootGameObject2D(std::make_unique<ColliderSprite>(
		Transform2D({
			Vector2D({ 2.0f, -2.0f }),
			Vector2D({ 1.0f, 1.0f }),
			0.0f,
			false,
			false,
			}),
			"Shore",
			"Collider",
			sprite
			)
	);
	addRootGameObject2D(std::make_unique<ColliderSprite>(
		Transform2D({
			Vector2D({ -2.0f, -2.0f }),
			Vector2D({ 1.0f, 1.0f }),
			0.0f,
			false,
			false,
			}),
			"Shore",
			"Collider",
			sprite
			)
	);
	texID = TextureRegistry::getInstance().loadTexture(stoneShoreFilePath);
	sprite = &SpriteRegistry::getInstance().makeSprite(
		stoneShoreKey,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
	addRootGameObject2D(std::make_unique<NonColliderSprite>(
		Transform2D({
			Vector2D({ -4.0f, -2.0f }),
			Vector2D({ 1.0f, 1.0f }),
			0.0f,
			false,
			false,
			}),
			"StoneShore",
			"StoneShore",
			sprite
			)
	);
	addRootGameObject2D(std::make_unique<NonColliderSprite>(
		Transform2D({
			Vector2D({ 4.0f, -2.0f }),
			Vector2D({ 1.0f, 1.0f }),
			0.0f,
			false,
			false,
			}),
			"StoneShore",
			"StoneShore",
			sprite
			)
	);
	texID = TextureRegistry::getInstance().loadTexture(cliffTopFilePath);
	sprite = &SpriteRegistry::getInstance().makeSprite(
		cliffTopKey,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
	addRootGameObject2D(std::make_unique<NonColliderSprite>(
		Transform2D({
			Vector2D({ -2.0f, 4.0f }),
			Vector2D({ 1.0f, 1.0f }),
			0.0f,
			false,
			false,
			}),
			"CliffTop",
			"CliffTop",
			sprite
			)
	);
	addRootGameObject2D(std::make_unique<NonColliderSprite>(
		Transform2D({
			Vector2D({ 2.0f, 4.0f }),
			Vector2D({ 1.0f, 1.0f }),
			0.0f,
			false,
			false,
			}),
			"CliffTop",
			"CliffTop",
			sprite
			)
	);
	addRootGameObject2D(std::make_unique<NonColliderSprite>(
		Transform2D({
			Vector2D({ -4.0f, 2.0f }),
			Vector2D({ 1.0f, 1.0f }),
			0.0f,
			false,
			false,
			}),
			"CliffTop",
			"CliffTop",
			sprite
			)
	);
	addRootGameObject2D(std::make_unique<NonColliderSprite>(
		Transform2D({
			Vector2D({ 4.0f, 2.0f }),
			Vector2D({ 1.0f, 1.0f }),
			0.0f,
			false,
			false,
			}),
			"CliffTop",
			"CliffTop",
			sprite
			)
	);
}