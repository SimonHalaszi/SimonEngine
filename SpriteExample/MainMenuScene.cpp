#include "MainMenuScene.hpp"

MainMenuScene::MainMenuScene() :
	Scene(244, 244, 10)
{
	mainMenu_ = nullptr;
	howToMenu_ = nullptr;
	controlsMenu_ = nullptr;
}

MainMenuScene::~MainMenuScene() {}

// Load Textures, Make Sprite Sheets, Make Sprites, etc (Load and Make Assets)... Add root game objects that will be at there at scene start
void MainMenuScene::init() {
	std::cout << "MainMenuScene::init() : Currently Loaded Scene is MainMenuScene" << std::endl;

	// Printing update information
	std::cout << "MainScene::init() : Animation updates " << animationUpdatesPerSecond_ << " times per second " << std::endl;
	std::cout << "MainScene::init() : Game updates " << updatesPerSecond_ << " times per second " << std::endl;
	std::cout << "MainScene::init() : Frame updates " << framesPerSeconds_ << " times per second " << std::endl;

	// Play sounds
	SoundManager::getInstance().setMusicTrack("audio/GoingShopping.mp3");

	createMenus();
}

// For scene/game specific drawing (Drawing that is not related to a GameObject)
void MainMenuScene::draw() const {
	// For example this draws a background for the entire scene!
	drawSquare(
		{ 0.0f, 0.0f },
		1.0f,
		0.0f, false, false,
		{ 1.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f }
	);
}

// If you need to do SceneChanges include the SceneSpecific.hpp and Game.hpp here (In the ThisScene.cpp)
// Otherwise some really annoying circular dependencies are going to happen with Game and Scenes
// #include "SomeOtherScene.hpp"
#include "Game.hpp"
#include "GameScene.hpp"

// For scene/game specific updates/inputs (Updates/Inputs that are not related to GameObjects)
void MainMenuScene::update() {
	UISpriteElement* menu = getMenuElement();
	// Example of how a scene input may change the Game class behavior
	if (InputManager::getInstance().isPressed('c')) {
		if (menu && controlsMenu_) {
			if (menu->getSprite() == mainMenu_) {
				menu->changeSprite(controlsMenu_);
			}
		}
	}
	if (InputManager::getInstance().isPressed('h')) {
		if (menu && howToMenu_) {
			if (menu->getSprite() == mainMenu_) {
				menu->changeSprite(howToMenu_);
			}
		}
	}
	if (InputManager::getInstance().isPressed('q')) {
		Game::getInstance().safeGameExit();
	}
	if (InputManager::getInstance().isPressed('g')) {
		if (menu) {
			if (menu->getSprite() == controlsMenu_ || menu->getSprite() == howToMenu_) {
				if (mainMenu_) {
					menu->changeSprite(mainMenu_);
				}
			}
			else {
				Game::getInstance().changeScene(std::make_unique<GameScene>());
			}
		}
	}
}

void MainMenuScene::createMenus() {
	std::string mainMenufilePath = "image/MainMenu.png";
	std::string mainMenukey = "MainMenu";
	GLuint texID;
	texID = TextureRegistry::getInstance().loadTexture(mainMenufilePath);
	mainMenu_ = &SpriteRegistry::getInstance().makeSprite(
		mainMenukey,
		texID,
		1,
		1,
		{ 0, 0 }
	);
	addRootGameObject2D(std::make_unique<UISpriteElement>(
		Transform2D({
			Vector2D({ 0.0f, 0.0f }),
			Vector2D({ 1.0f, 1.0f }),
			0.0f,
			false,
			false,
			}),
			"MainMenu",
			"MainMenu",
			mainMenu_
			)
	);
	// Loading other menus
	std::string controlsMenufilePath = "image/ControlsMenu.png";
	std::string controlsMenukey = "ControlsMenu";
	std::string howToMenufilePath = "image/HowToMenu.png";
	std::string howToMenukey = "HowToMenu";
	texID = TextureRegistry::getInstance().loadTexture(controlsMenufilePath);
	controlsMenu_ = &SpriteRegistry::getInstance().makeSprite(
		controlsMenukey,
		texID,
		1,
		1,
		{ 0, 0 }
	);
	texID = TextureRegistry::getInstance().loadTexture(howToMenufilePath);
	howToMenu_ = &SpriteRegistry::getInstance().makeSprite(
		howToMenukey,
		texID,
		1,
		1,
		{ 0, 0 }
	);
}

UISpriteElement* MainMenuScene::getMenuElement() {
	for (const auto& child : rootObjects_) {
		UISpriteElement* uiElement = dynamic_cast<UISpriteElement*>(child.get());
		if (uiElement) {
			return uiElement;
		}
	}
	return nullptr;
}