#include "PlatformerScene.hpp"

// Game Objects Used
// #include "GameObject.hpp"
#include "PlatformerPlayer.hpp"
#include "SpriteGameObject.hpp"
#include "SpriteObstacle.hpp"
#include "Coin.hpp"
#include "FinishLine.hpp"
//

PlatformerScene::PlatformerScene() :
	Scene(60, 244, 10)
{
	saveName_ = "PlatformerScene";

	// Initialize Filepaths
	backgroundMusicFilePath_ = "audio/NBC.mp3";

	playerSpriteSheetFilePath_ = "sprite/BillsGuy-sheet.png";
	turfTextureFilePath_ = "sprite/TurfTexture.jpg";
	skyboxTextureFilepath_ = "sprite/Background.jpg";
	concreteTextureFilePath_ = "sprite/Concrete.jpg";
	coinTextureFilepath_ = "sprite/Football.png";
	goalTextureFilepath_ = "sprite/FinishLine.png";

	playerSpriteSheet_ = "PlayerSpriteSheet";
	turfSprite_ = "turfSprite";
	skyboxSprite_ = "skyboxSprite";
	concreteSprite_ = "concreteSprite";
	coinSprite_ = "coinSprite";
	goalSprite_ = "goalSprite";
}

PlatformerScene::~PlatformerScene() {}

// Load Textures, Make Sprite Sheets, Make Sprites, etc (Load and Make Assets)... Add root game objects that will be at there at scene start
void PlatformerScene::init() {
	std::cout << "PlatformerScene::init : Currently Loaded Scene is PlatformerScene" << std::endl;

	SoundManager::getInstance().setMusicTrack(backgroundMusicFilePath_);

	// Printing update information
	std::cout << "PlatformerScene::init : Animation updates " << animationUpdatesPerSecond_ << " times per second " << std::endl;
	std::cout << "PlatformerScene::init : Game updates " << updatesPerSecond_ << " times per second " << std::endl;
	std::cout << "PlatformerScene::init : Frame updates " << framesPerSeconds_ << " times per second " << std::endl;

	// Skybox
	addRootGameObject2D(std::make_unique<SpriteGameObject>(
		Transform2D({
			Vector2D({ 0.0f, 0.0f }),
			Vector2D({ 5.5f, 6.0f }),
			0.0f,
			false,
			false,
		}),
		skyboxTextureFilepath_,
		skyboxSprite_,
		"Skybox"
	)
	);
	// Borders
	addRootGameObject2D(std::make_unique<SpriteObstacle>(
		Transform2D({
			Vector2D({ 0.0f, 2.0f }),
			Vector2D({ 5.5f, 0.5f }),
			0.0f,
			false,
			false,
		}),
		concreteTextureFilePath_,
		concreteSprite_
	)
	);
	addRootGameObject2D(std::make_unique<SpriteObstacle>(
		Transform2D({
			Vector2D({ 6.0f, 0.0f }),
			Vector2D({ 0.5f, 3.0f }),
			0.0f,
			false,
			false,
		}),
		concreteTextureFilePath_,
		concreteSprite_
	)
	);
	addRootGameObject2D(std::make_unique<SpriteObstacle>(
		Transform2D({
			Vector2D({ -6.0f, 0.0f }),
			Vector2D({ 0.5f, 3.0f }),
			0.0f,
			false,
			false,
		}),
		concreteTextureFilePath_,
		concreteSprite_
		)
	);
	// Obstacles
	addRootGameObject2D(std::make_unique<SpriteObstacle>(
		Transform2D({
			Vector2D({ 1.0f, 0.25f }),
			Vector2D({ 0.25f, 0.25f }),
			0.0f,
			false,
			false,
		}),
		concreteTextureFilePath_,
		concreteSprite_
	)
	);
	addRootGameObject2D(std::make_unique<SpriteObstacle>(
		Transform2D({
			Vector2D({ 0.5f, 0.25f }),
			Vector2D({ 0.6f, 0.1f }),
			0.0f,
			false,
			false,
		}),
		concreteTextureFilePath_,
		concreteSprite_
	)
	);
	addRootGameObject2D(std::make_unique<SpriteObstacle>(
		Transform2D({
			Vector2D({ 0.0f, 1.0f }),
			Vector2D({ 0.1f, 0.7f }),
			0.0f,
			false,
			false,
			}),
		concreteTextureFilePath_,
		concreteSprite_
	)
	);
	addRootGameObject2D(std::make_unique<SpriteObstacle>(
		Transform2D({
			Vector2D({ -1.0f, -0.25f }),
			Vector2D({ 0.25f, 0.25f }),
			0.0f,
			false,
			false,
		}),
		concreteTextureFilePath_,
		concreteSprite_
	)
	);
	addRootGameObject2D(std::make_unique<SpriteObstacle>(
		Transform2D({
			Vector2D({ -1.0f, 0.95f }),
			Vector2D({ 0.1f, 0.1f }),
			0.0f,
			false,
			false,
		}),
		concreteTextureFilePath_,
		concreteSprite_
	)
	);
	addRootGameObject2D(std::make_unique<SpriteObstacle>(
		Transform2D({
			Vector2D({ -2.0f, 0.0f }),
			Vector2D({ 0.25f, 0.25f }),
			0.0f,
			false,
			false,
		}),
		concreteTextureFilePath_,
		concreteSprite_
	)
	);
	addRootGameObject2D(std::make_unique<SpriteObstacle>(
		Transform2D({
			Vector2D({ -2.0f, 0.75f }),
			Vector2D({ 0.1f, 0.75f }),
			0.0f,
			false,
			false,
		}),
		concreteTextureFilePath_,
		concreteSprite_
	)
	);
	addRootGameObject2D(std::make_unique<SpriteObstacle>(
		Transform2D({
			Vector2D({ 3.0f, 0.0f }),
			Vector2D({ 0.1f, 0.1f }),
			0.0f,
			false,
			false,
		}),
		concreteTextureFilePath_,
		concreteSprite_
	)
	);
	addRootGameObject2D(std::make_unique<SpriteObstacle>(
		Transform2D({
			Vector2D({ 4.0f, 0.0f }),
			Vector2D({ 0.1f, 0.75f }),
			0.0f,
			false,
			false,
		}),
		concreteTextureFilePath_,
		concreteSprite_
	)
	);
	addRootGameObject2D(std::make_unique<SpriteObstacle>(
		Transform2D({
			Vector2D({ -4.0f, 0.0f }),
			Vector2D({ 0.1f, 0.75f }),
			0.0f,
			false,
			false,
		}),
		concreteTextureFilePath_,
		concreteSprite_
	)
	);
	addRootGameObject2D(std::make_unique<SpriteObstacle>(
		Transform2D({
			Vector2D({ -3.0f, 0.8f }),
			Vector2D({ 0.1f, 0.1f }),
			0.0f,
			false,
			false,
		}),
		concreteTextureFilePath_,
		concreteSprite_
	)
	);
	addRootGameObject2D(std::make_unique<SpriteObstacle>(
		Transform2D({
			Vector2D({ -4.2f, 0.0f }),
			Vector2D({ 0.1f, 0.1f }),
			0.0f,
			false,
			false,
			}),
		concreteTextureFilePath_,
		concreteSprite_
	)
	);
	addRootGameObject2D(std::make_unique<SpriteObstacle>(
		Transform2D({
			Vector2D({ 5.0f, 0.0f }),
			Vector2D({ 0.1f, 0.1f }),
			0.0f,
			false,
			false,
		}),
		concreteTextureFilePath_,
		concreteSprite_
	)
	);

	// Coins
	addRootGameObject2D(std::make_unique<Coin>(
		Transform2D({
			Vector2D({ -1.0f, 1.2f }),
			Vector2D({ 0.05f, 0.05f }),
			0.0f,
			false,
			false,
		}),
		coinTextureFilepath_,
		coinSprite_
	)
	);
	addRootGameObject2D(std::make_unique<Coin>(
		Transform2D({
			Vector2D({ 0.5f, 1.0f }),
			Vector2D({ 0.05f, 0.05f }),
			0.0f,
			false,
			false,
		}),
		coinTextureFilepath_,
		coinSprite_
	)
	);
	addRootGameObject2D(std::make_unique<Coin>(
		Transform2D({
			Vector2D({ 2.0f, 0.0f }),
			Vector2D({ 0.05f, 0.05f }),
			0.0f,
			false,
			false,
		}),
		coinTextureFilepath_,
		coinSprite_
		)
	);
	addRootGameObject2D(std::make_unique<Coin>(
		Transform2D({
			Vector2D({ -2.2f, 1.0f }),
			Vector2D({ 0.05f, 0.05f }),
			0.0f,
			false,
			false,
		}),
		coinTextureFilepath_,
		coinSprite_
	)
	);
	addRootGameObject2D(std::make_unique<Coin>(
		Transform2D({
			Vector2D({ 5.2f, 0.0f }),
			Vector2D({ 0.05f, 0.05f }),
			0.0f,
			false,
			false,
		}),
		coinTextureFilepath_,
		coinSprite_
	)
	);

	// Finish Line
	addRootGameObject2D(std::make_unique<FinishLine>(
		Transform2D({
			Vector2D({ -5.0f, 0.0f }),
			Vector2D({ 0.2f, 0.6f }),
			0.0f,
			false,
			false,
		}),
		goalTextureFilepath_,
		goalSprite_
	)
	);

	// Stage Floor
	addRootGameObject2D(std::make_unique<SpriteObstacle>(
		Transform2D({
			Vector2D({ 0.0f, -1.0f }),
			Vector2D({ 5.5f, 0.5f }),
			0.0f,
			false,
			false,
		}),
		turfTextureFilePath_,
		turfSprite_
	)
	);

	// Player
	addRootGameObject2D(std::make_unique<PlatformerPlayer>(playerSpriteSheetFilePath_, playerSpriteSheet_));
}

// For scene/game specific drawing (Drawing that is not related to a GameObject)
void PlatformerScene::draw() const { }

// For scene/game specific updates/inputs (Updates/Inputs that are not related to GameObjects)
void PlatformerScene::update() {
	if (InputManager::getInstance().isPressed('p')) {
		if (!pauseFlag_ && isUpdatingAnimations_) {
			pauseFlag_ = true;
			isUpdatingAnimations_ = false;
			SoundManager::getInstance().pauseMusic();
			SoundManager::getInstance().pauseSounds();
		}
		else {
			pauseFlag_ = false;
			isUpdatingAnimations_ = true;
			SoundManager::getInstance().unpauseMusic();
			SoundManager::getInstance().unpauseSounds();
		}
	}
	if (InputManager::getInstance().isPressed(27)) {
		Game::getInstance().safeGameExit();
	}
}