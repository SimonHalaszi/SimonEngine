#include "SceneFactory.hpp"

// Include all scenes needed
#include "TemplateScene.hpp"
#include "MainMenuScene.hpp"
#include "GameScene.hpp"
#include "LoadingGameScene.hpp"
#include "LoadingMainMenuScene.hpp"

// Expand this with more options as you go on
SceneFactory::SceneFactory() {
	factoryOptions_.push_back("MainMenuScene");
	factoryOptions_.push_back("GameScene");

	factoryOptions_.push_back("LoadingMainMenuScene");
	factoryOptions_.push_back("LoadingGameScene");

	factoryOptions_.push_back("TemplateScene");
}

std::unique_ptr<Scene> SceneFactory::defaultScene() {
	return std::make_unique<LoadingMainMenuScene>();
}

// Expand this with more options as you go on
std::unique_ptr<Scene> SceneFactory::createScene(std::string option) {
	if (option == "TemplateScene") {
		return std::make_unique<TemplateScene>();
	}

	if (option == "MainMenuScene") {
		return std::make_unique<MainMenuScene>();
	}
	if (option == "GameScene") {
		return std::make_unique<GameScene>();
	}

	if (option == "LoadingGameScene") {
		return std::make_unique<LoadingGameScene>();
	}
	if (option == "LoadingMainMenuScene") {
		return std::make_unique<LoadingMainMenuScene>();
	}
	return nullptr;
}