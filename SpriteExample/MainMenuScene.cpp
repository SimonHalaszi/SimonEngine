#include "MainMenuScene.hpp"

MainMenuScene::MainMenuScene() :
	Scene(244, 244, 10)
{
	saveName_ = "MainMenuScene";
	autoLoad_ = false;
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

	createMenu();
}

void MainMenuScene::createMenu() {
	std::string mainMenufilePath = "image/MainMenu.png";
	std::string mainMenukey = "MainMenu";
	std::string controlsMenufilePath = "image/ControlsMenu.png";
	std::string controlsMenukey = "ControlsMenu";
	std::string howToMenufilePath = "image/HowToMenu.png";
	std::string howToMenukey = "HowToMenu";
	GLuint texID;
	texID = TextureRegistry::getInstance().loadTexture(mainMenufilePath);
	const Sprite* main = &SpriteRegistry::getInstance().makeSprite(
		mainMenukey,
		texID,
		1,
		1,
		{ 0, 0 }
	);
	texID = TextureRegistry::getInstance().loadTexture(controlsMenufilePath);
	const Sprite* controls = &SpriteRegistry::getInstance().makeSprite(
		controlsMenukey,
		texID,
		1,
		1,
		{ 0, 0 }
	);
	texID = TextureRegistry::getInstance().loadTexture(howToMenufilePath);
	const Sprite* howTo = &SpriteRegistry::getInstance().makeSprite(
		howToMenukey,
		texID,
		1,
		1,
		{ 0, 0 }
	);
	addRootGameObject2D(std::make_unique<MainMenu>(
		Transform2D({
			Vector2D({ 0.0f, 0.0f }),
			Vector2D({ 1.0f, 1.0f }),
			0.0f,
			false,
			false,
			}),
			main,
			controls,
			howTo
			)
	);
}

