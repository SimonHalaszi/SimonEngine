#include "SceneFactory.hpp"

#include "GameOverScreenScene.hpp"
#include "GameWonScreenScene.hpp"
#include "PlatformerScene.hpp"
#include "TitleScreenScene.hpp"

// Expand this with more options as you go on
SceneFactory::SceneFactory() {
	factoryOptions_.push_back("GameOverScreenScene");
	factoryOptions_.push_back("GameWonScreenScene");
	factoryOptions_.push_back("PlatformerScene");
	factoryOptions_.push_back("TitleScreenScene");
}

std::unique_ptr<Scene> SceneFactory::defaultScene() {
	return std::make_unique<TitleScreenScene>();
}

// Expand this with more options as you go on
std::unique_ptr<Scene> SceneFactory::createScene(std::string option) {
	if (option == "GameOverScreenScene") {
		return std::make_unique<GameOverScreenScene>();
	}
	if (option == "GameWonScreenScene") {
		return std::make_unique<GameWonScreenScene>();
	}
	if (option == "PlatformerScene") {
		return std::make_unique<PlatformerScene>();
	}
	if (option == "TitleScreenScene") {
		return std::make_unique<TitleScreenScene>();
	}
	return nullptr;
}