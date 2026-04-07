#ifndef GAME_OBJECT_FACTORY
#define GAME_OBJECT_FACTORY

#include "GameObject2D.hpp"
#include <memory>
#include <vector>

enum class FactoryOptions;

// Game Object Factory, Add more options in GameObjectFactory.cpp
class GameObjectFactory {
public:
	static GameObjectFactory& getInstance() {
		static GameObjectFactory instance;
		return instance;
	}

	std::unique_ptr<GameObject2D> createGameObject(FactoryOptions option);

	GameObjectFactory(const GameObjectFactory&) = delete;
	GameObjectFactory& operator=(const GameObjectFactory&) = delete;
	GameObjectFactory(const GameObjectFactory&&) = delete;
	GameObjectFactory& operator=(const GameObjectFactory&&) = delete;

	const std::vector<FactoryOptions>& getFactoryOptions() const { return factoryOptions_; }

private:
	GameObjectFactory();

	std::vector<FactoryOptions> factoryOptions_;

	~GameObjectFactory() {}
};

#endif
