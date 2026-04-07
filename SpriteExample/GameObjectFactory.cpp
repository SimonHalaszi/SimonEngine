#include "GameObjectFactory.hpp"

#include "Coin.hpp"
#include "SpriteObstacle.hpp"

// Expand this with more options as you go on
enum class FactoryOptions {
	Coin,
	ConcreteSpriteObstacle,
	TurfSpriteObstacle
};

// Expand this with more options as you go on
GameObjectFactory::GameObjectFactory() {
	factoryOptions_.push_back(FactoryOptions::Coin);
	factoryOptions_.push_back(FactoryOptions::ConcreteSpriteObstacle);
	factoryOptions_.push_back(FactoryOptions::TurfSpriteObstacle);
}

// Expand this with more options as you go on
std::unique_ptr<GameObject2D> GameObjectFactory::createGameObject(FactoryOptions option) {
	switch (option) {
		case FactoryOptions::Coin:
			return std::make_unique<Coin>(
				Transform2D({
					Vector2D({ 0.0f, 0.0f }),
					Vector2D({ 0.0f, 0.0f }),
					0.0f,
					false,
					false,
				}),
				"sprite/Football.png",
				"coinSprite"
			);
			break;

		case FactoryOptions::ConcreteSpriteObstacle:
			return std::make_unique<SpriteObstacle>(
				Transform2D({
					Vector2D({ 0.0f, 0.0f }),
					Vector2D({ 0.0f, 0.0f }),
					0.0f,
					false,
					false,
				}),
				"sprite/Concrete.jpg",
				"concreteSprite"
			);
			break;

		case FactoryOptions::TurfSpriteObstacle:
			return std::make_unique<SpriteObstacle>(
				Transform2D({
					Vector2D({ 0.0f, 0.0f }),
					Vector2D({ 0.0f, 0.0f }),
					0.0f,
					false,
					false,
				}),
				"sprite/TurfTexture.jpg",
				"turfSprite"
			);
			break;

		default:
			return nullptr;
	}
}