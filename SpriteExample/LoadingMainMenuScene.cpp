#include "LoadingMainMenuScene.hpp"

LoadingMainMenuScene::LoadingMainMenuScene() :
	Scene(244, 244, 10)
{
	saveName_ = "LoadingMainMenuScene";
	autoLoad_ = true;
}

// Load Textures, Make Sprite Sheets, Make Sprites, etc (Load and Make Assets)... Add root game objects that will be at there at scene start
void LoadingMainMenuScene::init() {
	std::cout << "LoadingMainMenuScene::init() : Currently Loaded Scene is LoadingMainMenuScene" << std::endl;

	// Printing update information
	std::cout << "LoadingMainMenuScene::init() : Animation updates " << animationUpdatesPerSecond_ << " times per second " << std::endl;
	std::cout << "LoadingMainMenuScene::init() : Game updates " << updatesPerSecond_ << " times per second " << std::endl;
	std::cout << "LoadingMainMenuScene::init() : Frame updates " << framesPerSeconds_ << " times per second " << std::endl;

	// Play sounds
	SoundManager::getInstance().setMusicTrack("audio/Selfless.mp3");
}
