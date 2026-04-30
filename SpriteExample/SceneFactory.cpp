#include "SceneFactory.hpp"

// Include all scenes needed
#include "TemplateScene.hpp"
#include "MainMenuScene.hpp"
#include "GameScene.hpp"

// Expand this with more options as you go on
SceneFactory::SceneFactory() {
	factoryOptions_.push_back("TemplateScene");
	factoryOptions_.push_back("MainMenuScene");
	factoryOptions_.push_back("GameScene");
}

std::unique_ptr<Scene> SceneFactory::defaultScene() {
	return std::make_unique<MainMenuScene>();
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
	return nullptr;
}