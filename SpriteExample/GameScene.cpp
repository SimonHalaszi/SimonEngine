#include "GameScene.hpp"

GameScene::GameScene() :
	Scene(244, 244, 10)
{
	saveName_ = "GameScene";
	autoLoad_ = true;
}

// Load Textures, Make Sprite Sheets, Make Sprites, etc (Load and Make Assets)... Add root game objects that will be at there at scene start
void GameScene::init() {
	std::cout << "GameScene::init() : Currently Loaded Scene is GameScene" << std::endl;

	// Printing update information
	std::cout << "GameScene::init() : Animation updates " << animationUpdatesPerSecond_ << " times per second " << std::endl;
	std::cout << "GameScene::init() : Game updates " << updatesPerSecond_ << " times per second " << std::endl;
	std::cout << "GameScene::init() : Frame updates " << framesPerSeconds_ << " times per second " << std::endl;

	// Play sounds
	SoundManager::getInstance().setMusicTrack("audio/WhyAreSundaysSoDepressing.mp3");
}

#include "Game.hpp"

// For scene/game specific updates/inputs (Updates/Inputs that are not related to GameObjects)
void GameScene::update() {
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
