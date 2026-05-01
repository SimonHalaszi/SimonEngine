#include "LoadingGameScene.hpp"

LoadingGameScene::LoadingGameScene() :
	Scene(244, 244, 10)
{
	saveName_ = "LoadingGameScene";
	autoLoad_ = true;
}

// Load Textures, Make Sprite Sheets, Make Sprites, etc (Load and Make Assets)... Add root game objects that will be at there at scene start
void LoadingGameScene::init() {
	std::cout << "LoadingGameScene::init() : Currently Loaded Scene is LoadingGameScene" << std::endl;

	// Printing update information
	std::cout << "LoadingGameScene::init() : Animation updates " << animationUpdatesPerSecond_ << " times per second " << std::endl;
	std::cout << "LoadingGameScene::init() : Game updates " << updatesPerSecond_ << " times per second " << std::endl;
	std::cout << "LoadingGameScene::init() : Frame updates " << framesPerSeconds_ << " times per second " << std::endl;

	// Play sounds
	SoundManager::getInstance().setMusicTrack("audio/WhyAreSundaysSoDepressing.mp3");
}

// If you need to do SceneChanges include the SceneSpecific.hpp and Game.hpp here (In the ThisScene.cpp)
// Otherwise some really annoying circular dependencies are going to happen with Game and Scenes
// #include "SomeOtherScene.hpp"
#include "Game.hpp"
#include "GameScene.hpp"

// For scene/game specific updates/inputs (Updates/Inputs that are not related to GameObjects)
void LoadingGameScene::update() {
	if (InputManager::getInstance().isPressed('p')) {
		pauseFlag_ = !pauseFlag_;
		if (pauseFlag_) {
			SoundManager::getInstance().pauseAll();
		}
		else {
			SoundManager::getInstance().unpauseAll();
		}
	}
	// Example of how a scene input may change the Game class behavior
	if (InputManager::getInstance().isPressed('n')) {
		isDrawing_ = false;
	}
	if (InputManager::getInstance().isPressed('m')) {
		isDrawing_ = true;
	}
}
