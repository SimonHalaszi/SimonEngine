#ifndef SCENE_FACTORY_HPP
#define SCENE_FACTORY_HPP

#include "Scene.hpp"
#include <memory>
#include <vector>
#include <string>

// Scene Factory, Add more options in SceneFactory.cpp
class SceneFactory {
public:
	static SceneFactory& getInstance() {
		static SceneFactory instance;
		return instance;
	}

	std::unique_ptr<Scene> createScene(std::string option);

	std::unique_ptr<Scene> defaultScene();

	SceneFactory(const SceneFactory&) = delete;
	SceneFactory& operator=(const SceneFactory&) = delete;
	SceneFactory(const SceneFactory&&) = delete;
	SceneFactory& operator=(const SceneFactory&&) = delete;

	const std::vector<std::string>& getFactoryOptions() const { return factoryOptions_; }

private:
	SceneFactory();

	std::vector<std::string> factoryOptions_;

	~SceneFactory() {}
};

#endif
