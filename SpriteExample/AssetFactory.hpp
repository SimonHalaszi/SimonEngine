#ifndef GAME_OBJECT_FACTORY
#define GAME_OBJECT_FACTORY

#include "GameObject2D.hpp"
#include "Sprite.hpp"
#include "SpriteRegistry.hpp"
#include <memory>
#include <vector>
#include <string>

// Game Object Factory, Add more options in GameObjectFactory.cpp
class AssetFactory {
public:
	static AssetFactory& getInstance() {
		static AssetFactory instance;
		return instance;
	}

	std::unique_ptr<GameObject2D> createGameObject(std::string option);
	const Sprite* getOptionPreviewSprite(std::string option);

	AssetFactory(const AssetFactory&) = delete;
	AssetFactory& operator=(const AssetFactory&) = delete;
	AssetFactory(const AssetFactory&&) = delete;
	AssetFactory& operator=(const AssetFactory&&) = delete;

	const std::vector<std::string>& getFactoryOptions() const { return factoryOptions_; }

private:
	AssetFactory();

	std::vector<std::string> factoryOptions_;

	~AssetFactory() {}
};

#endif
