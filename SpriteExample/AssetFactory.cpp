#include "AssetFactory.hpp"

// Needed GameObjects
#include "NonColliderSprite.hpp"
#include "Moneser.hpp"

// Expand this with more options as you go on
AssetFactory::AssetFactory() {
	factoryOptions_.push_back("Norup");
	factoryOptions_.push_back("Granda");
	factoryOptions_.push_back("Ploist");
	factoryOptions_.push_back("Foxire");
	factoryOptions_.push_back("Man");
	factoryOptions_.push_back("Bird");
}

// Expand this with more options as you go on
std::unique_ptr<GameObject2D> AssetFactory::createGameObject(std::string option) {
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