#include "AssetFactory.hpp"

// Needed GameObjects
#include "NonColliderSprite.hpp"

// Expand this with more options as you go on
AssetFactory::AssetFactory() {
	factoryOptions_.push_back("Man");
	factoryOptions_.push_back("Bird");
}

// Expand this with more options as you go on
std::unique_ptr<GameObject2D> AssetFactory::createGameObject(std::string option) {
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