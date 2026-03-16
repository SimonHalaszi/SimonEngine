#include "TitleScreenScene.hpp"

#include "SpriteGameObject.hpp"
#include "UITextElement.hpp"

TitleScreenScene::TitleScreenScene() :
	Scene(244, 244, 10)
{
	backgroundSpriteFilePath_ = "sprite/Background.jpg";
	backgroundSprite_ = "backgroundSprite";
	titleScreenMusicFilePath_ = "audio/FOX.mp3";
}

TitleScreenScene::~TitleScreenScene() {}

// Load Textures, Make Sprite Sheets, Make Sprites, etc (Load and Make Assets)... Add root game objects that will be at there at scene start
void TitleScreenScene::init() {
	std::cout << "TitleScreenScene::init : Currently Loaded Scene is TitleScreenScene" << std::endl;

	SoundManager::getInstance().setMusicTrack(titleScreenMusicFilePath_);

	// Loading sprite textures from file path
	TextureRegistry::getInstance().loadTexture(backgroundSpriteFilePath_);

	// Making a sprite
	SpriteRegistry::getInstance().makeSprite(
		backgroundSprite_,
		TextureRegistry::getInstance().getTextureID(backgroundSpriteFilePath_),
		1, 1,
		{ 0, 0 }
	);

	// Printing update information
	std::cout << "TitleScreenScene::init : Animation updates " << animationUpdatesPerSecond_ << " times per second " << std::endl;
	std::cout << "TitleScreenScene::init : Game updates " << updatesPerSecond_ << " times per second " << std::endl;
	std::cout << "TitleScreenScene::init : Frame updates " << framesPerSeconds_ << " times per second " << std::endl;

	// Make it so GameObjects get passed the keys to the Assets they use
	addRootGameObject2D(std::make_unique<SpriteGameObject>(
		Transform2D({
			Vector2D({ 0.0f, 0.0f }),
			Vector2D({ 1.0f, 1.0f }),
			0.0f,
			false,
			false,
		}),
		backgroundSprite_,
		"Background"
		)
	);
	addRootGameObject2D(std::make_unique<UITextElement>(
		Transform2D({ Vector2D({ 0.0f, 0.9f }),
			Vector2D({ 0.50f, 0.05f }),
			0.0f,
			false,
			false, 
		}),
		"Wide Receiving",
		ColorRGB{ 1.0f, 1.0f, 1.0f },
		ColorRGB{ 0.0f, 0.0f, 0.0f }
	)
	);
	addRootGameObject2D(std::make_unique<UITextElement>(
		Transform2D({ Vector2D({ 0.0f, -0.9f }),
			Vector2D({ 0.8f, 0.05f }),
			0.0f,
			false,
			false,
		}),
		"Press 'G' To Start",
		ColorRGB{ 1.0f, 1.0f, 1.0f },
		ColorRGB{ 0.0f, 0.0f, 0.0f }
	)
	);
}

// For scene/game specific drawing (Drawing that is not related to a GameObject)
void TitleScreenScene::draw() const {}

// If you need to do SceneChanges include the SceneSpecific.hpp and Game.hpp here (In the ThisScene.cpp)
// Otherwise some really annoying circular dependencies are going to happen with Game and Scenes
#include "PlatformerScene.hpp"
#include "Game.hpp"

// For scene/game specific updates/inputs (Updates/Inputs that are not related to GameObjects)
void TitleScreenScene::update() {
	if (InputManager::getInstance().isPressed('g')) {
		Game::getInstance().changeScene(std::make_unique<PlatformerScene>());
	}
	if (InputManager::getInstance().isPressed(27)) {
		Game::getInstance().safeGameExit();
	}
}