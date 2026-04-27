#include "SceneFactory.hpp"

#include "TemplateScene.hpp"

// Expand this with more options as you go on
SceneFactory::SceneFactory() {
	factoryOptions_.push_back("TemplateScene");
	factoryOptions_.push_back("TemplateSceneAgain");
}

std::unique_ptr<Scene> SceneFactory::defaultScene() {
	return std::make_unique<TemplateScene>();
}

// Expand this with more options as you go on
std::unique_ptr<Scene> SceneFactory::createScene(std::string option) {
	if (option == "TemplateScene") {
		return std::make_unique<TemplateScene>();
	}
	if (option == "TemplateSceneAgain") {
		return std::make_unique<TemplateScene>();
	}
	return nullptr;
}