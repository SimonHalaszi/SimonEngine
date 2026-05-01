#include "AssetFactory.hpp"

// Needed GameObjects
#include "NonColliderSprite.hpp"
#include "Moneser.hpp"
#include "ColliderSprite.hpp"
#include "Player.hpp"
#include "Teleporter.hpp"
#include "PauseDisplay.hpp"
#include "MainMenu.hpp"

// Expand this with more options as you go on
AssetFactory::AssetFactory() {
	factoryOptions_.push_back("BaseGrass");
	factoryOptions_.push_back("House");

	factoryOptions_.push_back("Bush");
	factoryOptions_.push_back("BerryBush");
	factoryOptions_.push_back("AppleTree");
	factoryOptions_.push_back("OrangeTree");

	factoryOptions_.push_back("BaseMarsh");
	factoryOptions_.push_back("BaseFire");

	factoryOptions_.push_back("HouseFloor");
	factoryOptions_.push_back("HouseWall");
	factoryOptions_.push_back("Chair");
	factoryOptions_.push_back("Rug");
	factoryOptions_.push_back("Collider");
	factoryOptions_.push_back("RestArea");

	factoryOptions_.push_back("Cliff");
	factoryOptions_.push_back("CliffTop");
	factoryOptions_.push_back("Shore");
	factoryOptions_.push_back("StoneShore");

	factoryOptions_.push_back("Player");

	factoryOptions_.push_back("GoOutTeleporter");
	factoryOptions_.push_back("GoInTeleporter");

	factoryOptions_.push_back("PauseDisplay");

	factoryOptions_.push_back("Norup");
	factoryOptions_.push_back("Granda");
	factoryOptions_.push_back("Ploist");
	factoryOptions_.push_back("Foxire");

	factoryOptions_.push_back("MainMenu");

	factoryOptions_.push_back("Man");
	factoryOptions_.push_back("Bird");
}

// Expand this with more options as you go on
std::unique_ptr<GameObject2D> AssetFactory::createGameObject(std::string option) {
	if (option == "BaseGrass") {
		std::string baseFilePath = "image/BaseGrass.png";
		std::string baseKey = "BaseGrass";
		GLuint texID = TextureRegistry::getInstance().loadTexture(baseFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			baseKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return std::make_unique<NonColliderSprite>(
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
				);
	}
	if (option == "House") {
		std::string houseFilePath = "image/House.png";
		std::string houseKey = "House";
		GLuint texID = TextureRegistry::getInstance().loadTexture(houseFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			houseKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return std::make_unique<ColliderSprite>(
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
				);
	}

	if (option == "Bush") {
		std::string bushFilePath = "image/Bush.png";
		std::string bushKey = "Bush";
		GLuint texID = TextureRegistry::getInstance().loadTexture(bushFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			bushKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return std::make_unique<ColliderSprite>(
			Transform2D({
				Vector2D({ 0.0f, 0.0f }),
				Vector2D({ 0.1f, 0.1f }),
				0.0f,
				false,
				false,
				}),
				"Bush",
				"Collider",
				sprite
				);
	}
	if (option == "BerryBush") {
		std::string berryBushFilePath = "image/BerryBush.png";
		std::string berryBushKey = "BerryBush";
		GLuint texID = TextureRegistry::getInstance().loadTexture(berryBushFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			berryBushFilePath,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return std::make_unique<ColliderSprite>(
			Transform2D({
				Vector2D({ 0.0f, 0.0f }),
				Vector2D({ 0.1f, 0.1f }),
				0.0f,
				false,
				false,
				}),
				"BerryBush",
				"Collider",
				sprite
				);
	}
	if (option == "AppleTree") {
		std::string appleTreeFilePath = "image/AppleTree.png";
		std::string appleTreeKey = "AppleTree";
		GLuint texID = TextureRegistry::getInstance().loadTexture(appleTreeFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			appleTreeKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return std::make_unique<ColliderSprite>(
			Transform2D({
				Vector2D({ 0.0f, 0.0f }),
				Vector2D({ 0.2f, 0.3f }),
				0.0f,
				false,
				false,
				}),
				"AppleTree",
				"Collider",
				sprite
				);
	}
	if (option == "OrangeTree") {
		std::string orangeTreeFilePath = "image/OrangeTree.png";
		std::string orangeTreeKey = "OrangeTree";
		GLuint texID = TextureRegistry::getInstance().loadTexture(orangeTreeFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			orangeTreeKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return std::make_unique<ColliderSprite>(
			Transform2D({
				Vector2D({ 0.0f, 0.0f }),
				Vector2D({ 0.2f, 0.3f }),
				0.0f,
				false,
				false,
				}),
				"OrangeTree",
				"Collider",
				sprite
				);
	}

	if (option == "BaseMarsh") {
		std::string baseFilePath = "image/BaseMarsh.png";
		std::string baseKey = "BaseMarsh";
		GLuint texID = TextureRegistry::getInstance().loadTexture(baseFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			baseKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return std::make_unique<NonColliderSprite>(
			Transform2D({
				Vector2D({ 0.0f, 0.0f }),
				Vector2D({ 1.0f, 1.0f }),
				0.0f,
				false,
				false,
				}),
				"BaseMarsh",
				"BaseMarsh",
				sprite
				);
	}

	if (option == "BaseFire") {
		std::string baseFilePath = "image/BaseFire.png";
		std::string baseKey = "BaseFire";
		GLuint texID = TextureRegistry::getInstance().loadTexture(baseFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			baseKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return std::make_unique<NonColliderSprite>(
			Transform2D({
				Vector2D({ 0.0f, 0.0f }),
				Vector2D({ 1.0f, 1.0f }),
				0.0f,
				false,
				false,
				}),
				"BaseFire",
				"BaseFire",
				sprite
				);
	}

	if (option == "HouseFloor") {
		std::string houseFloorFilePath = "image/HouseFloor.png";
		std::string houseFloorKey = "HouseFloor";
		GLuint texID = TextureRegistry::getInstance().loadTexture(houseFloorFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			houseFloorKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return std::make_unique<NonColliderSprite>(
			Transform2D({
				Vector2D({ 0.0f, 0.0f }),
				Vector2D({ 0.5f, 0.5f }),
				0.0f,
				false,
				false,
				}),
				"HouseFloor",
				"HouseFloor",
				sprite
				);
	}
	if (option == "HouseWall") {
		std::string houseWallFilePath = "image/HouseWall.png";
		std::string houseWallKey = "HouseWall";
		GLuint texID = TextureRegistry::getInstance().loadTexture(houseWallFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			houseWallKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return std::make_unique<ColliderSprite>(
			Transform2D({
				Vector2D({ 0.0f, 0.0f }),
				Vector2D({ 0.5f, 0.2f }),
				0.0f,
				false,
				false,
				}),
				"HouseWall",
				"Collider",
				sprite
				);
	}
	if (option == "Chair") {
		std::string chairFilePath = "image/Chair.png";
		std::string chairKey = "Chair";
		GLuint texID = TextureRegistry::getInstance().loadTexture(chairFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			chairKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return std::make_unique<ColliderSprite>(
			Transform2D({
				Vector2D({ 0.0f, 0.0f }),
				Vector2D({ 0.1f, 0.1f }),
				0.0f,
				false,
				false,
				}),
				"Chair",
				"Collider",
				sprite
				);
	}
	if (option == "Rug") {
		std::string rugFilePath = "image/Rug.png";
		std::string rugKey = "Rug";
		GLuint texID = TextureRegistry::getInstance().loadTexture(rugFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			rugKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return std::make_unique<NonColliderSprite>(
			Transform2D({
				Vector2D({ 0.0f, 0.0f }),
				Vector2D({ 0.3f, 0.1f }),
				0.0f,
				false,
				false,
				}),
				"Rug",
				"Rug",
				sprite
				);
	}
	if (option == "Collider") {
		std::string blankFilePath = "image/Blank.png";
		std::string blankKey = "Blank";
		GLuint texID = TextureRegistry::getInstance().loadTexture(blankFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			blankKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return std::make_unique<ColliderSprite>(
			Transform2D({
				Vector2D({ 0.0f, 0.0f }),
				Vector2D({ 0.1f, 0.5f }),
				0.0f,
				false,
				false,
				}),
				"Collider",
				"Collider",
				sprite
				);
	}
	if (option == "RestArea") {
		std::string blankFilePath = "image/Blank.png";
		std::string blankKey = "Blank";
		GLuint texID = TextureRegistry::getInstance().loadTexture(blankFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			blankKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return std::make_unique<ColliderSprite>(
			Transform2D({
				Vector2D({ 0.0f, 0.0f }),
				Vector2D({ 0.2f, 0.2f }),
				0.0f,
				false,
				false,
				}),
				"RestArea",
				"RestArea",
				sprite
				);
	}

	if (option == "Cliff") {
		std::string cliffFilePath = "image/Cliff.png";
		std::string cliffKey = "Cliff";
		GLuint texID = TextureRegistry::getInstance().loadTexture(cliffFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			cliffKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return std::make_unique<ColliderSprite>(
			Transform2D({
				Vector2D({ 0.0f, 0.0f }),
				Vector2D({ 1.0f, 1.0f }),
				0.0f,
				false,
				false,
				}),
				"Cliff",
				"Collider",
				sprite
				);
	}
	if (option == "CliffTop") {
		std::string cliffTopFilePath = "image/CliffTop.png";
		std::string cliffTopKey = "CliffTop";
		GLuint texID = TextureRegistry::getInstance().loadTexture(cliffTopFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			cliffTopKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return std::make_unique<ColliderSprite>(
			Transform2D({
				Vector2D({ 0.0f, 0.0f }),
				Vector2D({ 1.0f, 1.0f }),
				0.0f,
				false,
				false,
				}),
				"CliffTop",
				"Collider",
				sprite
				);
	}
	if (option == "Shore") {
		std::string shoreFilePath = "image/Shore.png";
		std::string shoreKey = "Shore";
		GLuint texID = TextureRegistry::getInstance().loadTexture(shoreFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			shoreKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return std::make_unique<ColliderSprite>(
			Transform2D({
				Vector2D({ 0.0f, 0.0f }),
				Vector2D({ 1.0f, 1.0f }),
				0.0f,
				false,
				false,
				}),
				"Shore",
				"Collider",
				sprite
				);
	}
	if (option == "StoneShore") {
		std::string stoneShoreFilePath = "image/StoneShore.png";
		std::string stoneShoreKey = "StoneShore";
		GLuint texID = TextureRegistry::getInstance().loadTexture(stoneShoreFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			stoneShoreKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return std::make_unique<ColliderSprite>(
			Transform2D({
				Vector2D({ 0.0f, 0.0f }),
				Vector2D({ 1.0f, 1.0f }),
				0.0f,
				false,
				false,
				}),
				"StoneShore",
				"Collider",
				sprite
				);
	}

	if (option == "Player") {
		std::string shadowFilePath = "image/Shadow.png";
		std::string shadowKey = "Shadow";
		// SHADOW SPRITE
		GLuint outsideTexID = TextureRegistry::getInstance().loadTexture(shadowFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			shadowKey,
			outsideTexID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
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
		return std::make_unique<Player>(
			Transform2D({
				Vector2D({ 0.0f, 0.0f }),
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
				);
	}

	if (option == "GoOutTeleporter") {
		std::string goOutFilePath = "image/GoOut.png";
		std::string goOutKey = "GoOut";
		GLuint texID = TextureRegistry::getInstance().loadTexture(goOutFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			goOutKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return std::make_unique<Teleporter>(
			Transform2D({
				Vector2D({ 0.0f, 0.0f }),
				Vector2D({ 0.3f, 0.1f }),
				0.0f,
				false,
				false,
				}),
				"GoOut",
				Vector2D({ 0.0f, 0.0f }),
				sprite
				);
	}
	if (option == "GoInTeleporter") {
		std::string goInFilePath = "image/GoIn.png";
		std::string goInKey = "GoIn";
		GLuint texID = TextureRegistry::getInstance().loadTexture(goInFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			goInKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return std::make_unique<Teleporter>(
			Transform2D({
				Vector2D({ 0.0f, 0.0f }),
				Vector2D({ 0.3f, 0.1f }),
				0.0f,
				false,
				false,
				}),
				"GoIn",
				Vector2D({ 0.0f, 0.0f }),
				sprite
				);
	}

	if (option == "PauseDisplay") {
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
		return std::make_unique<PauseDisplay>(
			Transform2D({
				Vector2D({0.0f, 0.0f}),
				Vector2D({1.0f, 1.0f}),
				0.0f,
				false, false
				}),
			"PauseDisplay",
			sprite
		);
	}

	if (option == "Norup") {
		std::string shadowFilePath = "image/Shadow.png";
		std::string shadowKey = "Shadow";
		// SHADOW SPRITE
		GLuint outsideTexID = TextureRegistry::getInstance().loadTexture(shadowFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			shadowKey,
			outsideTexID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		std::string healthDisplayFilePath = "image/MoneserHealth.png";
		std::string healthBarFilepath = "image/Health.png";
		std::string healthDisplayKey = "MoneserHealth";
		std::string healthBarKey = "Health";
		outsideTexID = TextureRegistry::getInstance().loadTexture(healthDisplayFilePath);
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
		return std::make_unique<Moneser>(
			Transform2D({
				Vector2D({0.0f, 0.0f}),
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
				);
	}
	if (option == "Granda") {
		std::string shadowFilePath = "image/Shadow.png";
		std::string shadowKey = "Shadow";
		// SHADOW SPRITE
		GLuint outsideTexID = TextureRegistry::getInstance().loadTexture(shadowFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			shadowKey,
			outsideTexID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		std::string healthDisplayFilePath = "image/MoneserHealth.png";
		std::string healthBarFilepath = "image/Health.png";
		std::string healthDisplayKey = "MoneserHealth";
		std::string healthBarKey = "Health";
		outsideTexID = TextureRegistry::getInstance().loadTexture(healthDisplayFilePath);
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
		return std::make_unique<Moneser>(
			Transform2D({
				Vector2D({ 0.0f, 0.0f }),
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
				);
	}
	if (option == "Ploist") {
		std::string shadowFilePath = "image/Shadow.png";
		std::string shadowKey = "Shadow";
		// SHADOW SPRITE
		GLuint outsideTexID = TextureRegistry::getInstance().loadTexture(shadowFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			shadowKey,
			outsideTexID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		std::string healthDisplayFilePath = "image/MoneserHealth.png";
		std::string healthBarFilepath = "image/Health.png";
		std::string healthDisplayKey = "MoneserHealth";
		std::string healthBarKey = "Health";
		outsideTexID = TextureRegistry::getInstance().loadTexture(healthDisplayFilePath);
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
		return std::make_unique<Moneser>(
			Transform2D({
				Vector2D({ 0.0f, 0.0f }),
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
				);
	}
	if (option == "Foxire") {
		std::string shadowFilePath = "image/Shadow.png";
		std::string shadowKey = "Shadow";
		// SHADOW SPRITE
		GLuint outsideTexID = TextureRegistry::getInstance().loadTexture(shadowFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			shadowKey,
			outsideTexID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		std::string healthDisplayFilePath = "image/MoneserHealth.png";
		std::string healthBarFilepath = "image/Health.png";
		std::string healthDisplayKey = "MoneserHealth";
		std::string healthBarKey = "Health";
		outsideTexID = TextureRegistry::getInstance().loadTexture(healthDisplayFilePath);
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
		return std::make_unique<Moneser>(
			Transform2D({
				Vector2D({ 0.0f, 0.0f }),
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
				);
	}

	if (option == "MainMenu") {
		std::string mainMenufilePath = "image/MainMenu.png";
		std::string mainMenukey = "MainMenu";
		std::string controlsMenufilePath = "image/ControlsMenu.png";
		std::string controlsMenukey = "ControlsMenu";
		std::string howToMenufilePath = "image/HowToMenu.png";
		std::string howToMenukey = "HowToMenu";
		GLuint texID;
		texID = TextureRegistry::getInstance().loadTexture(mainMenufilePath);
		const Sprite* main = &SpriteRegistry::getInstance().makeSprite(
			mainMenukey,
			texID,
			1,
			1,
			{ 0, 0 }
		);
		texID = TextureRegistry::getInstance().loadTexture(controlsMenufilePath);
		const Sprite* controls = &SpriteRegistry::getInstance().makeSprite(
			controlsMenukey,
			texID,
			1,
			1,
			{ 0, 0 }
		);
		texID = TextureRegistry::getInstance().loadTexture(howToMenufilePath);
		const Sprite* howTo = &SpriteRegistry::getInstance().makeSprite(
			howToMenukey,
			texID,
			1,
			1,
			{ 0, 0 }
		);
		return std::make_unique<MainMenu>(
			Transform2D({
				Vector2D({ 0.0f, 0.0f }),
				Vector2D({ 1.0f, 1.0f }),
				0.0f,
				false,
				false,
				}),
				main,
				controls,
				howTo
				);
	}

	if (option == "Man") {
		GLuint texID;
		texID = TextureRegistry::getInstance().loadTexture("image/Man.png");
		return std::make_unique<NonColliderSprite>(
			Transform2D({ 
				Vector2D({ 0.0f, 0.0f }),
				Vector2D({ 0.5f, 0.5f }),
				0.0f,
				false,
				false, 
			}),
			"Man",
			"Man",
			&SpriteRegistry::getInstance().makeSprite("Man", texID, 1, 1, { 0, 0 })
		);
	}
	if (option == "Bird") {
		GLuint texID;
		texID = TextureRegistry::getInstance().loadTexture("image/Bird.png");
		return std::make_unique<NonColliderSprite>(
			Transform2D({
				Vector2D({ 0.0f, 0.0f }),
				Vector2D({ 0.5f, 0.5f }),
				0.0f,
				false,
				false,
				}),
				"Bird",
				"Bird",
				&SpriteRegistry::getInstance().makeSprite("Bird", texID, 1, 1, { 0, 0 })
				);
	}
	
	return nullptr;
}

const Sprite* AssetFactory::getOptionPreviewSprite(std::string option) {
	if (option == "BaseGrass") {
		std::string baseFilePath = "image/BaseGrass.png";
		std::string baseKey = "BaseGrass";
		GLuint texID = TextureRegistry::getInstance().loadTexture(baseFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			baseKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return sprite;
	}
	if (option == "House") {
		std::string houseFilePath = "image/House.png";
		std::string houseKey = "House";
		GLuint texID = TextureRegistry::getInstance().loadTexture(houseFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			houseKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return sprite;
	}

	if (option == "Bush") {
		std::string bushFilePath = "image/Bush.png";
		std::string bushKey = "Bush";
		GLuint texID = TextureRegistry::getInstance().loadTexture(bushFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			bushKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return sprite;
	}
	if (option == "BerryBush") {
		std::string berryBushFilePath = "image/BerryBush.png";
		std::string berryBushKey = "BerryBush";
		GLuint texID = TextureRegistry::getInstance().loadTexture(berryBushFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			berryBushFilePath,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return sprite;
	}
	if (option == "AppleTree") {
		std::string appleTreeFilePath = "image/AppleTree.png";
		std::string appleTreeKey = "AppleTree";
		GLuint texID = TextureRegistry::getInstance().loadTexture(appleTreeFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			appleTreeKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return sprite;
	}
	if (option == "OrangeTree") {
		std::string orangeTreeFilePath = "image/OrangeTree.png";
		std::string orangeTreeKey = "OrangeTree";
		GLuint texID = TextureRegistry::getInstance().loadTexture(orangeTreeFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			orangeTreeKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return sprite;
	}

	if (option == "BaseMarsh") {
		std::string baseFilePath = "image/BaseMarsh.png";
		std::string baseKey = "BaseMarsh";
		GLuint texID = TextureRegistry::getInstance().loadTexture(baseFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			baseKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return sprite;
	}

	if (option == "BaseFire") {
		std::string baseFilePath = "image/BaseFire.png";
		std::string baseKey = "BaseFire";
		GLuint texID = TextureRegistry::getInstance().loadTexture(baseFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			baseKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return sprite;
	}

	if (option == "HouseFloor") {
		std::string houseFloorFilePath = "image/HouseFloor.png";
		std::string houseFloorKey = "HouseFloor";
		GLuint texID = TextureRegistry::getInstance().loadTexture(houseFloorFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			houseFloorKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return sprite;
	}
	if (option == "HouseWall") {
		std::string houseWallFilePath = "image/HouseWall.png";
		std::string houseWallKey = "HouseWall";
		GLuint texID = TextureRegistry::getInstance().loadTexture(houseWallFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			houseWallKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return sprite;
	}
	if (option == "Chair") {
		std::string chairFilePath = "image/Chair.png";
		std::string chairKey = "Chair";
		GLuint texID = TextureRegistry::getInstance().loadTexture(chairFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			chairKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return sprite;
	}
	if (option == "Rug") {
		std::string rugFilePath = "image/Rug.png";
		std::string rugKey = "Rug";
		GLuint texID = TextureRegistry::getInstance().loadTexture(rugFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			rugKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return sprite;
	}
	if (option == "Collider") {
		std::string blankFilePath = "image/Blank.png";
		std::string blankKey = "Blank";
		GLuint texID = TextureRegistry::getInstance().loadTexture(blankFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			blankKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return sprite;
	}
	if (option == "RestArea") {
		std::string blankFilePath = "image/Blank.png";
		std::string blankKey = "Blank";
		GLuint texID = TextureRegistry::getInstance().loadTexture(blankFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			blankKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return sprite;
	}

	if (option == "Cliff") {
		std::string cliffFilePath = "image/Cliff.png";
		std::string cliffKey = "Cliff";
		GLuint texID = TextureRegistry::getInstance().loadTexture(cliffFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			cliffKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return sprite;
	}
	if (option == "CliffTop") {
		std::string cliffTopFilePath = "image/CliffTop.png";
		std::string cliffTopKey = "CliffTop";
		GLuint texID = TextureRegistry::getInstance().loadTexture(cliffTopFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			cliffTopKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return sprite;
	}
	if (option == "Shore") {
		std::string shoreFilePath = "image/Shore.png";
		std::string shoreKey = "Shore";
		GLuint texID = TextureRegistry::getInstance().loadTexture(shoreFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			shoreKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return sprite;
	}
	if (option == "StoneShore") {
		std::string stoneShoreFilePath = "image/StoneShore.png";
		std::string stoneShoreKey = "StoneShore";
		GLuint texID = TextureRegistry::getInstance().loadTexture(stoneShoreFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			stoneShoreKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return sprite;
	}

	if (option == "Player") {
		std::string playerFilePath = "image/Player.png";
		std::string playerKey = "Player";

		GLuint texID = TextureRegistry::getInstance().loadTexture(playerFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			playerKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return sprite;
	}

	if (option == "GoOutTeleporter") {
		std::string goOutFilePath = "image/GoOut.png";
		std::string goOutKey = "GoOut";
		GLuint texID = TextureRegistry::getInstance().loadTexture(goOutFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			goOutKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return sprite;
	}
	if (option == "GoInTeleporter") {
		std::string goInFilePath = "image/GoIn.png";
		std::string goInKey = "GoIn";
		GLuint texID = TextureRegistry::getInstance().loadTexture(goInFilePath);
		const Sprite* sprite = &SpriteRegistry::getInstance().makeSprite(
			goInKey,
			texID,
			1,
			1,
			TileIndex({ 0, 0 })
		);
		return sprite;
	}

	if (option == "PauseDisplay") {
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
		return sprite;
	}

	if (option == "Norup") {
		GLuint texID;
		texID = TextureRegistry::getInstance().loadTexture("image/Norup.png");
		return &SpriteRegistry::getInstance().makeSprite(
			"Norup",
			texID,
			1, 1,
			{ 0, 0 }
		);
	}
	if (option == "Granda") {
		GLuint texID;
		texID = TextureRegistry::getInstance().loadTexture("image/Granda.png");
		return &SpriteRegistry::getInstance().makeSprite(
			"Granda",
			texID,
			1, 1,
			{ 0, 0 }
		);
	}
	if (option == "Ploist") {
		GLuint texID;
		texID = TextureRegistry::getInstance().loadTexture("image/Ploist.png");
		return &SpriteRegistry::getInstance().makeSprite(
			"Ploist",
			texID,
			1, 1,
			{ 0, 0 }
		);
	}
	if (option == "Foxire") {
		GLuint texID;
		texID = TextureRegistry::getInstance().loadTexture("image/Foxire.png");
		return &SpriteRegistry::getInstance().makeSprite(
			"Foxire",
			texID,
			1, 1,
			{ 0, 0 }
		);
	}

	if (option == "MainMenu") {
		std::string mainMenufilePath = "image/MainMenu.png";
		std::string mainMenukey = "MainMenu";
		GLuint texID;
		texID = TextureRegistry::getInstance().loadTexture(mainMenufilePath);
		return &SpriteRegistry::getInstance().makeSprite(
			mainMenukey,
			texID,
			1, 1,
			{ 0, 0 }
		);
	}

	if (option == "Man") {
		GLuint texID;
		texID = TextureRegistry::getInstance().loadTexture("image/Man.png");
		return &SpriteRegistry::getInstance().makeSprite(
			"Man",
			texID,
			1, 1,
			{ 0, 0 }
		);
	}
	if (option == "Bird") {
		GLuint texID;
		texID = TextureRegistry::getInstance().loadTexture("image/Bird.png");
		return &SpriteRegistry::getInstance().makeSprite(
			"Bird",
			texID,
			1, 1,
			{ 0, 0 }
		);
	}
	return nullptr;
}