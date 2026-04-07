#include "AssetFactory.hpp"

#include "Coin.hpp"
#include "SpriteObstacle.hpp"

// Expand this with more options as you go on
AssetFactory::AssetFactory() {
	factoryOptions_.push_back("Coin");
	factoryOptions_.push_back("ConcreteSpriteObstacle");
	factoryOptions_.push_back("TurfSpriteObstacle");
}

// Expand this with more options as you go on
std::unique_ptr<GameObject2D> AssetFactory::createGameObject(std::string option) {
	if (option == "Coin") {
		return std::make_unique<Coin>(
			Transform2D({
				Vector2D({ 0.0f, 0.0f }),
				Vector2D({ 0.05f, 0.05f }),
				0.0f,
				false,
				false,
			}),
			"sprite/Football.png",
			"coinSprite"
		);
	}
	if (option == "ConcreteSpriteObstacle") {
		return std::make_unique<SpriteObstacle>(
			Transform2D({
				Vector2D({ 0.0f, 0.0f }),
				Vector2D({ 0.1f, 0.1f }),
				0.0f,
				false,
				false,
			}),
			"sprite/Concrete.jpg",
			"concreteSprite"
		);
	}
	if (option == "TurfSpriteObstacle") {
		return std::make_unique<SpriteObstacle>(
			Transform2D({
				Vector2D({ 0.0f, 0.0f }),
				Vector2D({ 0.1f, 0.1f }),
				0.0f,
				false,
				false,
			}),
			"sprite/TurfTexture.jpg",
			"turfSprite"
		);
	}
	return nullptr;
}

const Sprite* AssetFactory::getOptionPreviewSprite(std::string option) {
	if (option == "Coin") {
		TextureRegistry::getInstance().loadTexture("sprite/Football.png");
		SpriteRegistry::getInstance().makeSprite(
			"coinSprite",
			TextureRegistry::getInstance().getTextureID("sprite/Football.png"),
			1, 1,
			{ 0, 0 }
		);
		return &(SpriteRegistry::getInstance().getSprite("coinSprite"));
	}
	if (option == "ConcreteSpriteObstacle") {
		TextureRegistry::getInstance().loadTexture("sprite/Concrete.jpg");
		SpriteRegistry::getInstance().makeSprite(
			"concreteSprite",
			TextureRegistry::getInstance().getTextureID("sprite/Concrete.jpg"),
			1, 1,
			{ 0, 0 }
		);
		return &(SpriteRegistry::getInstance().getSprite("concreteSprite"));
	}
	if (option == "TurfSpriteObstacle") {
		TextureRegistry::getInstance().loadTexture("sprite/TurfTexture.jpg");
		SpriteRegistry::getInstance().makeSprite(
			"turfSprite",
			TextureRegistry::getInstance().getTextureID("sprite/TurfTexture.jpg"),
			1, 1,
			{ 0, 0 }
		);
		return &(SpriteRegistry::getInstance().getSprite("turfSprite"));
	}
	return nullptr;
}