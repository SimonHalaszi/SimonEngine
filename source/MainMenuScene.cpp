#include "MainMenuScene.hpp"

MainMenuScene::MainMenuScene() :
	Scene(244, 244, 10)
{
	saveName_ = "MainMenuScene";
	autoLoad_ = true;
}

// Load Textures, Make Sprite Sheets, Make Sprites, etc (Load and Make Assets)... Add root game objects that will be at there at scene start
void MainMenuScene::init() {
	std::cout << "MainMenuScene::init() : Currently Loaded Scene is MainMenuScene" << std::endl;

	// Printing update information
	std::cout << "MainMenuScene::init() : Animation updates " << animationUpdatesPerSecond_ << " times per second " << std::endl;
	std::cout << "MainMenuScene::init() : Game updates " << updatesPerSecond_ << " times per second " << std::endl;
	std::cout << "MainMenuScene::init() : Frame updates " << framesPerSeconds_ << " times per second " << std::endl;

	// Play sounds
	SoundManager::getInstance().setMusicTrack("audio/Selfless.mp3");
}
