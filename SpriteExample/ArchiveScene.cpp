#include "ArchiveScene.hpp"

ArchiveScene::ArchiveScene() :
	Scene(244, 244, 10),
	audioTracks_({
		   "audio/CBS.mp3",
		   "audio/FOX.mp3",
		   "audio/NBC.mp3"
		}),
	runningTilesBrownsFilepath_("sprite/TwoGuys-sheet.png"),
	runningTilesBillsFilepath_("sprite/BillsGuy-sheet.png")
{
	billsRunningSheetName_ = "billsRunning";
	brownsRunningSheetName_ = "brownsRunning";
	brownsSpriteName_ = "brownsSprite";
	billsSpriteName_ = "billsSprite";
}

ArchiveScene::~ArchiveScene() {}

// Load Textures, Make Sprite Sheets, Make Sprites, etc (Load and Make Assets)... Add root game objects that will be at there at scene start
void ArchiveScene::init() {
	std::cout << "ArchiveScene::init : Currently Loaded Scene is ArchiveScene" << std::endl;
	std::cout << "ArchiveScene::init : Scene Music belongs to the NFL, CBS, FOX and NBC" << std::endl;

	soundEngine_->play2D(audioTracks_[currentAudioTrack_].data(), true);
	std::cout << "ArchiveScene::init : Started at track from file path " << audioTracks_[currentAudioTrack_] << std::endl;

	// Loading sprite textures from file path
	TextureRegistry::getInstance().loadTexture(runningTilesBillsFilepath_);
	TextureRegistry::getInstance().loadTexture(runningTilesBrownsFilepath_);

	// Making a sprite sheet
	SpriteSheetRegistry::getInstance().makeSpriteSheet(
		billsRunningSheetName_,
		TextureRegistry::getInstance().getTextureID(runningTilesBillsFilepath_),
		6, 1,
		{ 0, 0 }, { 5, 0 }
	);

	// Making a sprite sheet
	SpriteSheetRegistry::getInstance().makeSpriteSheet(
		brownsRunningSheetName_,
		TextureRegistry::getInstance().getTextureID(runningTilesBrownsFilepath_),
		3, 4,
		{ 0, 2 }, { 2, 3 }
	);

	// Making a sprite
	SpriteRegistry::getInstance().makeSprite(
		billsSpriteName_,
		TextureRegistry::getInstance().getTextureID(runningTilesBillsFilepath_),
		6, 1,
		{ 0, 0 }
	);

	// Making a sprite
	SpriteRegistry::getInstance().makeSprite(
		brownsSpriteName_,
		TextureRegistry::getInstance().getTextureID(runningTilesBrownsFilepath_),
		3, 4,
		{ 0, 2 }
	);

	// Just showing errors
	TextureRegistry::getInstance().loadTexture(runningTilesBrownsFilepath_);
	SpriteSheetRegistry::getInstance().makeSpriteSheet(
		billsRunningSheetName_,
		TextureRegistry::getInstance().getTextureID(runningTilesBillsFilepath_),
		6, 1,
		{ 0, 0 }, { 5, 0 }
	);
	SpriteRegistry::getInstance().makeSprite(
		brownsSpriteName_,
		TextureRegistry::getInstance().getTextureID(runningTilesBrownsFilepath_),
		3, 4,
		{ 0, 2 }
	);
	SpriteSheetRegistry::getInstance().getSpriteSheet("bob");

	// Printing update information
	std::cout << "ArchiveScene::init : Animation updates " << animationUpdatesPerSecond_ << " times per second " << std::endl;
	std::cout << "ArchiveScene::init : Game updates " << updatesPerSecond_ << " times per second " << std::endl;
	std::cout << "ArchiveScene::init : Frame updates " << framesPerSeconds_ << " times per second " << std::endl;

	addRootGameObject2D(std::make_unique<RotatingColorChangingSquare>(
		Transform2D({ Vector2D({ 0.5f, 0.0f }),
		Vector2D({ 0.1f, 0.1f }),
		0.0f,
		false,
		false, }),
		ColorRGB({ 1.0f, 0.0f, 0.0f }), 
		ColorRGB({ 1.0f, 0.8f, 0.2f }), 
		ColorRGB({ 1.0f, 0.0f, 0.0f }),
		ColorRGB({ 1.0f, 0.8f, 0.2f }),
		ColorRGB({ 0.0f, 1.0f, 0.0f }),
		ColorRGB({ 0.2f, 1.0f, 0.8f }),
		ColorRGB({ 0.0f, 1.0f, 0.0f }),
		ColorRGB({ 0.2f, 1.0f, 0.8f })
		)
	);
	addRootGameObject2D(std::make_unique<RotatingColorChangingTriangle>(
		Transform2D({ Vector2D({ -0.5f, 0.0f }),
		Vector2D({ 0.1f, 0.1f }),
		0.0f,
		false,
		false, }),
		ColorRGB({ 0.0f, 1.0f, 0.0f }),
		ColorRGB({ 0.0f, 1.0f, 0.0f }),
		ColorRGB({ 0.2f, 1.0f, 0.8f }),
		ColorRGB({ 1.0f, 0.0f, 0.0f }),
		ColorRGB({ 1.0f, 0.0f, 0.0f }),
		ColorRGB({ 1.0f, 0.8f, 0.2f })
		)
	);
	addRootGameObject2D(std::make_unique<StaticSprite>(
		Transform2D({ Vector2D({ -0.5f, 0.5f }),
		Vector2D({ 0.1f, 0.1f }),
		0.0f,
		true,
		false, }),
		brownsSpriteName_,
		"BrownsOne"
		)
	);
	addRootGameObject2D(std::make_unique<StaticSprite>(
		Transform2D({ Vector2D({ 0.5f, -0.5f }),
		Vector2D({ 0.1f, 0.1f }),
		0.0f,
		false,
		true, }),
		billsSpriteName_,
		"BillsOne"
		)
	);
	addRootGameObject2D(std::make_unique<AnimatedSprite>(
		Transform2D({ Vector2D({ 0.5f, 0.5f }),
		Vector2D({ 0.1f, 0.1f }),
		0.0f,
		false,
		false, }),
		billsRunningSheetName_
		)
	);
	addRootGameObject2D(std::make_unique<AnimatedSprite>(
		Transform2D({ Vector2D({ -0.5f, -0.5f }),
		Vector2D({ 0.1f, 0.1f }),
		0.0f,
		true,
		true, }),
		brownsRunningSheetName_
		)
	);
	addRootGameObject2D(std::make_unique<Axis>(
		Transform2D({ Vector2D({ 0.0f, 0.0f }),
		Vector2D({ 0.0f, 0.0f }),
		0.0f,
		false,
		false, }),
		ColorRGB({ 1.0f, 0.0f, 0.0f }),
		ColorRGB({ 1.0f, 0.0f, 0.0f }),
		true,
		'x'
		)
	);
	addRootGameObject2D(std::make_unique<Axis>(
		Transform2D({ Vector2D({ 0.0f, 0.0f }),
		Vector2D({ 0.0f, 0.0f }),
		0.0f,
		false,
		false, }),
		ColorRGB({ 0.0f, 1.0f, 0.0f }),
		ColorRGB({ 0.0f, 1.0f, 0.0f }),
		true,
		'y'
		)
	);
	addRootGameObject2D(std::make_unique<ArchivePlayer>(billsRunningSheetName_));
}

// For scene/game specific drawing (Drawing that is not related to a GameObject)
void ArchiveScene::draw() const {

}

// Im going to find a better way to do this TOMORROW
#include "TemplateScene.hpp"
#include "Game.hpp"

// For scene/game specific updates/inputs (Updates/Inputs that are not related to GameObjects)
void ArchiveScene::update() {
	if (InputManager::getInstance().isPressed('c')) {
		isDrawing_ = false;
	}
	if (InputManager::getInstance().isPressed('m')) {
		isDrawing_ = true;
	}
	if (InputManager::getInstance().isPressed('p')) {
		if (musicOn_) {
			soundEngine_->setAllSoundsPaused(true);
			musicOn_ = false;
		}
		else {
			soundEngine_->setAllSoundsPaused(false);
			musicOn_ = true;
		}
	}
	if (InputManager::getInstance().isPressed(27)) {
		exit(0);
	}
	if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_SCROLLDOWN)) {
		zoomFactor_ -= 0.1f;
	}
	if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_SCROLLUP)) {
		zoomFactor_ += 0.1f;
	}
	if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_RIGHT)) {
		soundEngine_->removeAllSoundSources();
		currentAudioTrack_ += 1;
		currentAudioTrack_ = currentAudioTrack_ % audioTracks_.size();
		soundEngine_->play2D(audioTracks_[currentAudioTrack_].data(), true);
		std::cout << "MainScene::procMouse : Now playing track from " << audioTracks_[currentAudioTrack_] << std::endl;
	}
	if (InputManager::getInstance().isPressed('n')) {
		Game::getInstance().changeScene(std::make_unique<TemplateScene>());
	}

	updateCamera();
}

void ArchiveScene::updateCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1 / zoomFactor_, 1 / zoomFactor_, -1 / zoomFactor_, 1 / zoomFactor_, -1, 1);
	glTranslatef(camX_, camY_, 0);
	glMatrixMode(GL_MODELVIEW);
}