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

	createTeleporters();
	createPauseDisplay();
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

#include "Game.hpp"
#include "TemplateScene.hpp"

// For scene/game specific updates/inputs (Updates/Inputs that are not related to GameObjects)
void GameScene::update() {
	if (InputManager::getInstance().isPressed('p')) {
		pauseFlag_ = !pauseFlag_;
	}
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
	// END FIRE AREA
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
	std::string healthDisplayFilePath = "image/MoneserHealth.png";
	std::string healthBarFilepath = "image/Health.png";
	std::string healthDisplayKey = "MoneserHealth";
	std::string healthBarKey = "Health";
	GLuint outsideTexID = TextureRegistry::getInstance().loadTexture(healthDisplayFilePath);
	const Sprite* healthDisplay = &SpriteRegistry::getInstance().makeSprite(
		healthDisplayKey,
		outsideTexID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
	outsideTexID = TextureRegistry::getInstance().loadTexture(healthBarFilepath);
	const Sprite* healthBar = &SpriteRegistry::getInstance().makeSprite(
		healthBarKey,
		outsideTexID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
	
	// Foxire
	{
		std::string foxireSheetFilePath = "image/FoxireSheet.png";
		std::string foxireFightFilePath = "image/FoxireFight.png";
		std::string foxireTakeFilePath = "image/FoxireTake.png";
		std::string foxireSheetKey = "Foxire";
		std::string foxireFightSheetKey = "FoxireFight";
		std::string foxireTakeSheetKey = "FoxireTake";

		GLuint texID = TextureRegistry::getInstance().loadTexture(foxireSheetFilePath);
		const SpriteSheet* spriteSheet = &SpriteSheetRegistry::getInstance().makeSpriteSheet(
			foxireSheetKey,
			texID,
			7,
			1,
			TileIndex({ 0, 0 }),
			TileIndex({ 6, 0 })
		);
		texID = TextureRegistry::getInstance().loadTexture(foxireFightFilePath);
		const Sprite* spriteFight = &SpriteRegistry::getInstance().makeSprite(
			foxireFightSheetKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		texID = TextureRegistry::getInstance().loadTexture(foxireTakeFilePath);
		const Sprite* spriteTake = &SpriteRegistry::getInstance().makeSprite(
			foxireTakeSheetKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
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
				20.0f,
				MoneserType::Fire,
				spriteSheet,
				spriteFight,
				spriteTake,
				healthDisplay,
				healthBar
				)
		);
	}
	
	// Granda
	{
		std::string grandaSheetFilePath = "image/GrandaSheet.png";
		std::string grandaFightFilePath = "image/GrandaFight.png";
		std::string grandaTakeFilePath = "image/GrandaTake.png";
		std::string grandaSheetKey = "Granda";
		std::string grandaFightSheetKey = "GrandaFight";
		std::string grandaTakeSheetKey = "GrandaTake";

		GLuint texID = TextureRegistry::getInstance().loadTexture(grandaSheetFilePath);
		const SpriteSheet* spriteSheet = &SpriteSheetRegistry::getInstance().makeSpriteSheet(
			grandaSheetKey,
			texID,
			7,
			1,
			TileIndex({ 0, 0 }),
			TileIndex({ 6, 0 })
		);
		texID = TextureRegistry::getInstance().loadTexture(grandaFightFilePath);
		const Sprite* spriteFight = &SpriteRegistry::getInstance().makeSprite(
			grandaFightSheetKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		texID = TextureRegistry::getInstance().loadTexture(grandaTakeFilePath);
		const Sprite* spriteTake = &SpriteRegistry::getInstance().makeSprite(
			grandaTakeSheetKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
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
				20.0f,
				MoneserType::Grass,
				spriteSheet,
				spriteFight,
				spriteTake,
				healthDisplay,
				healthBar
				)
		);
	}
	
	// Ploist
	{
		std::string ploistSheetFilePath = "image/PloistSheet.png";
		std::string ploistFightFilePath = "image/PloistFight.png";
		std::string ploistTakeFilePath = "image/PloistTake.png";
		std::string ploistSheetKey = "Ploist";
		std::string ploistFightSheetKey = "PloistFight";
		std::string ploistTakeSheetKey = "PloistTake";

		GLuint texID = TextureRegistry::getInstance().loadTexture(ploistSheetFilePath);
		const SpriteSheet* spriteSheet = &SpriteSheetRegistry::getInstance().makeSpriteSheet(
			ploistSheetKey,
			texID,
			7,
			1,
			TileIndex({ 0, 0 }),
			TileIndex({ 6, 0 })
		);
		texID = TextureRegistry::getInstance().loadTexture(ploistFightFilePath);
		const Sprite* spriteFight = &SpriteRegistry::getInstance().makeSprite(
			ploistFightSheetKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		texID = TextureRegistry::getInstance().loadTexture(ploistTakeFilePath);
		const Sprite* spriteTake = &SpriteRegistry::getInstance().makeSprite(
			ploistTakeSheetKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
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
				20.0f,
				MoneserType::Water,
				spriteSheet,
				spriteFight,
				spriteTake,
				healthDisplay,
				healthBar
				)
		);
	}
	
	// Norup
	{
		std::string norupSheetFilePath = "image/NorupSheet.png";
		std::string norupFightFilePath = "image/NorupFight.png";
		std::string norupTakeFilePath = "image/NorupTake.png";
		std::string norupSheetKey = "Norup";
		std::string norupFightSheetKey = "NorupFight";
		std::string norupTakeSheetKey = "NorupTake";

		GLuint texID = TextureRegistry::getInstance().loadTexture(norupSheetFilePath);
		const SpriteSheet* spriteSheet = &SpriteSheetRegistry::getInstance().makeSpriteSheet(
			norupSheetKey,
			texID,
			7,
			1,
			TileIndex({ 0, 0 }),
			TileIndex({ 6, 0 })
		);
		texID = TextureRegistry::getInstance().loadTexture(norupFightFilePath);
		const Sprite* spriteFight = &SpriteRegistry::getInstance().makeSprite(
			norupFightSheetKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		texID = TextureRegistry::getInstance().loadTexture(norupTakeFilePath);
		const Sprite* spriteTake = &SpriteRegistry::getInstance().makeSprite(
			norupTakeSheetKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
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
				20.0f,
				MoneserType::Norm,
				spriteSheet,
				spriteFight,
				spriteTake,
				healthDisplay,
				healthBar
				)
		);

		// Ts lowkey dont need to be so serious but whatever, we are professionals
		Moneser* norup = dynamic_cast<Moneser*>(getRootObjects()->back().get());
		if (norup) {
			if (norup->getName() == "Norup") {
				norup->setHealth(0.0f);
			}
		}
	}
}

void GameScene::spawnPlayer() {
	std::string playerFilePath = "image/PlayerSheet.png";
	std::string playerDownKey = "PlayerDown";
	std::string playerSidewaysKey = "PlayerSideways";
	std::string playerUpKey = "PlayerUp";

	// Icons
	std::string normIconFilePath = "image/NormIcon.png";
	std::string grassIconFilePath = "image/GrassIcon.png";
	std::string fireIconFilePath = "image/FireIcon.png";
	std::string waterIconFilePath = "image/WaterIcon.png";
	std::string normIconKey = "NormIcon";
	std::string grassIconKey = "GrassIcon";
	std::string fireIconKey = "FireIcon";
	std::string waterIconKey = "WaterIcon";

	// Displays
	std::string healDisplayFilePath = "image/Heal.png";
	std::string goToMenuDisplayFilepath = "image/GoToMenu.png";
	std::string healDisplayKey = "HealDisplay";
	std::string goToMenuDisplayKey = "GoToMenu";

	std::string healthDisplayFilePath = "image/PlayerHealth.png";
	std::string healthBarFilepath = "image/Health.png";
	std::string healthDisplayKey = "PlayerHealth";
	std::string healthBarKey = "Health";

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
	texID = TextureRegistry::getInstance().loadTexture(normIconFilePath);
	const Sprite* normIcon = &SpriteRegistry::getInstance().makeSprite(
		normIconKey,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
	texID = TextureRegistry::getInstance().loadTexture(grassIconFilePath);
	const Sprite* grassIcon = &SpriteRegistry::getInstance().makeSprite(
		grassIconKey,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
	texID = TextureRegistry::getInstance().loadTexture(fireIconFilePath);
	const Sprite* fireIcon = &SpriteRegistry::getInstance().makeSprite(
		fireIconKey,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
	texID = TextureRegistry::getInstance().loadTexture(waterIconFilePath);
	const Sprite* waterIcon = &SpriteRegistry::getInstance().makeSprite(
		waterIconKey,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
	texID = TextureRegistry::getInstance().loadTexture(healDisplayFilePath);
	const Sprite* healDisplay = &SpriteRegistry::getInstance().makeSprite(
		healDisplayKey,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
	texID = TextureRegistry::getInstance().loadTexture(goToMenuDisplayFilepath);
	const Sprite* goToMenuDisplay = &SpriteRegistry::getInstance().makeSprite(
		goToMenuDisplayKey,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
	texID = TextureRegistry::getInstance().loadTexture(healthDisplayFilePath);
	const Sprite* healthDisplay = &SpriteRegistry::getInstance().makeSprite(
		healthDisplayKey,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
	texID = TextureRegistry::getInstance().loadTexture(healthBarFilepath);
	const Sprite* healthBar = &SpriteRegistry::getInstance().makeSprite(
		healthBarKey,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
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
			20.0f,
			spriteSheetDown,
			spriteSheetSideways,
			spriteSheetUp,
			normIcon,
			grassIcon,
			fireIcon,
			waterIcon,
			healDisplay,
			goToMenuDisplay,
			healthDisplay,
			healthBar
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
			Vector2D({houseOrgin_.x + 0.4f, houseOrgin_.y + 0.5f}),
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
			"Rug",
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
	addRootGameObject2D(std::make_unique<ColliderSprite>(
		Transform2D({
			Vector2D({houseOrgin_.x + 0.4f, houseOrgin_.y + 0.5f}),
			Vector2D({ 0.2f, 0.2f }),
			0.0f,
			false,
			false,
			}),
			"RestArea",
			"RestArea",
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
	addRootGameObject2D(std::make_unique<ColliderSprite>(
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
	addRootGameObject2D(std::make_unique<ColliderSprite>(
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
	addRootGameObject2D(std::make_unique<ColliderSprite>(
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
	addRootGameObject2D(std::make_unique<ColliderSprite>(
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
	addRootGameObject2D(std::make_unique<ColliderSprite>(
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
	addRootGameObject2D(std::make_unique<ColliderSprite>(
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

void GameScene::createTeleporters() {
	std::string goOutFilePath = "image/GoOut.png";
	std::string goOutKey = "GoOut";
	std::string goInFilePath = "image/GoIn.png";
	std::string goInKey = "GoIn";
	GLuint texID = TextureRegistry::getInstance().loadTexture(goOutFilePath);
	const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
		goOutKey,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
	addRootGameObject2D(std::make_unique<Teleporter>(
		Transform2D({
			Vector2D({houseOrgin_.x, houseOrgin_.y - 0.4f}),
			Vector2D({ 0.3f, 0.1f }),
			0.0f,
			false,
			false,
			}),
			"Go Outside",
			Vector2D({ 0.0f, -0.4f }),
			sprite
			)
	);
	texID = TextureRegistry::getInstance().loadTexture(goInFilePath);
	sprite = &SpriteRegistry::getInstance().makeSprite(
		goInKey,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
	addRootGameObject2D(std::make_unique<Teleporter>(
		Transform2D({
			Vector2D({ 0.0f, -0.4f }),
			Vector2D({ 0.1f, 0.1f }),
			0.0f,
			false,
			false,
			}),
			"Go Inside",
			Vector2D({ houseOrgin_.x, houseOrgin_.y - 0.4f }),
			sprite
			)
	);
}

void GameScene::createPauseDisplay() {
	std::string filePath = "image/Paused.png";
	std::string key = "Paused";
	GLuint texID = TextureRegistry::getInstance().loadTexture(filePath);
	const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
		key,
		texID,
		1,
		1,
		TileIndex({ 0, 0 })
	);
	addRootGameObject2D(std::make_unique<PauseDisplay>(
		Transform2D({
			Vector2D({0.0f, 0.0f}),
			Vector2D({1.0f, 1.0f}),
			0.0f,
			false, false
			}),
		"PauseDisplay",
		sprite
	)
	);
}