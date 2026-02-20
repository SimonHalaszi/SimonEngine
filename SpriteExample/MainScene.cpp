#include "MainScene.hpp"

MainScene::MainScene() :
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

MainScene::~MainScene() {}

void MainScene::init() {
	std::cout << "MainScene::init : Currently Loaded Scene is MainScene" << std::endl;
	std::cout << "MainScene::init : Scene Music belongs to the NFL, CBS, FOX and NBC" << std::endl;

	soundEngine_->play2D(audioTracks_[currentAudioTrack_].data(), true);
	std::cout << "MainScene::init : Started at track from file path " << audioTracks_[currentAudioTrack_] << std::endl;

	// Loading sprite textures from file path
	textures_.loadTexture(runningTilesBillsFilepath_);
	textures_.loadTexture(runningTilesBrownsFilepath_);

	// Making a sprite sheet
	spriteSheets_.makeSpriteSheet(
		billsRunningSheetName_,
		textures_.getTextureID(runningTilesBillsFilepath_),
		6, 1,
		{ 0, 0 }, { 5, 0 }
	);

	// Making a sprite sheet
	spriteSheets_.makeSpriteSheet(
		brownsRunningSheetName_,
		textures_.getTextureID(runningTilesBrownsFilepath_),
		3, 4,
		{ 0, 2 }, { 2, 3 }
	);

	// Making a sprite
	sprites_.makeSprite(
		billsSpriteName_,
		textures_.getTextureID(runningTilesBillsFilepath_),
		6, 1,
		{ 0, 0 }
	);

	// Making a sprite
	sprites_.makeSprite(
		brownsSpriteName_,
		textures_.getTextureID(runningTilesBrownsFilepath_),
		3, 4,
		{ 0, 2 }
	);

	// Just showing errors
	textures_.loadTexture(runningTilesBrownsFilepath_);
	spriteSheets_.makeSpriteSheet(
		billsRunningSheetName_,
		textures_.getTextureID(runningTilesBillsFilepath_),
		6, 1,
		{ 0, 0 }, { 5, 0 }
	);
	sprites_.makeSprite(
		brownsSpriteName_,
		textures_.getTextureID(runningTilesBrownsFilepath_),
		3, 4,
		{ 0, 2 }
	);
	spriteSheets_.getSpriteSheet("bob");

	// Printing update information
	std::cout << "MainScene::init : Animation updates " << animationUpdatesPerSecond_ << " times per second " << std::endl;
	std::cout << "MainScene::init : Game updates " << updatesPerSecond_ << " times per second " << std::endl;
	std::cout << "MainScene::init : Frame updates " << framesPerSeconds_ << " times per second " << std::endl;
}

void MainScene::draw() {
	if (screenOn_) {

		const SpriteSheet& billsRunningSpriteSheet = spriteSheets_.getSpriteSheet(billsRunningSheetName_);
		const SpriteSheet& brownsRunningSpriteSheet = spriteSheets_.getSpriteSheet(brownsRunningSheetName_);

		Sprite billsSprite = sprites_.getSprite(billsSpriteName_);
		Sprite brownsSprite = sprites_.getSprite(brownsSpriteName_);

		// If moving do the sprite sheet animation if not just draw the sprite
		if (moveX_ || moveY_) {
			// Drawing from a sprite sheet
			drawSprite(
				playerPos_,
				0.25f, 0.0f,
				mirrorPlayer_, false,
				billsRunningSpriteSheet[animationFrame_ % billsRunningSpriteSheet.spriteCount()]
			);
		}
		else {
			drawSprite(
				playerPos_,
				0.25f, 0.0f,
				mirrorPlayer_, false,
				billsSprite
			);
		}

		// Drawing a Sprite
		drawSprite(
			{ 0.5f, -0.5f },
			0.1f, 0.0f,
			false, true,
			billsSprite
		);

		drawSprite(
			{ -0.5f, 0.5f },
			0.1f, 0.0f,
			true, false,
			brownsSprite
		);

		// Drawing from a sprite sheet
		drawSprite(
			{ 0.5f, 0.5f },
			0.1f, 0.0f,
			false, false,
			billsRunningSpriteSheet[animationFrame_ % billsRunningSpriteSheet.spriteCount()]
		);
		drawSprite(
			{ -0.5f, -0.5f },
			0.1f, 0.0f,
			true, true,
			brownsRunningSpriteSheet[animationFrame_ % brownsRunningSpriteSheet.spriteCount()]
		);

		drawSquare(
			{ 0.5f, 0.0f },
			0.1f, squareRotation_,
			false, false,
			squareColor1_, squareColor2_, squareColor1_, squareColor2_
		);
		drawTriangle(
			{ -0.5f, 0.0f },
			0.1f, triangleRotation_,
			false, false,
			triangleColor1_, triangleColor1_, triangleColor2_
		);

		// Draw X and Y axes at orgin of square if wanted
		if (drawAxes_) {
			drawAxis(
				{ 0.0f, 0.0f }, { 0.25f, 0.0f },
				{ 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f },
				'x'
			);
			drawAxis(
				{ 0.0f, 0.0f }, { 0.0f, 0.25f },
				{ 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f },
				'y'
			);
		}

	}
}

void MainScene::update() {
	moveX_ = 0.0f;
	moveY_ = 0.0f;

	if (keyLeftPressed_) {
		moveX_ -= 1.0f * deltaTime_;
		mirrorPlayer_ = true;
	}

	if (keyRightPressed_) {
		moveX_ += 1.0f * deltaTime_;
		mirrorPlayer_ = false;
	}

	if (keyUpPressed_) {
		moveY_ += 1.0f * deltaTime_;
	}

	if (keyDownPressed_) {
		moveY_ -= 1.0f * deltaTime_;
	}

	playerPos_.x += moveX_;
	playerPos_.y += moveY_;

	squareRotation_ += 20 * deltaTime_;
	if (squareRotation_ >= 360) {
		squareRotation_ = 0;
	}

	triangleRotation_ += -20 * deltaTime_;
	if (triangleRotation_ <= -360) {
		triangleRotation_ = 0;
	}

	updateCamera();
}

void MainScene::procSpecialKeys(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) {
		keyLeftPressed_ = true;
	}

	if (key == GLUT_KEY_RIGHT) {
		keyRightPressed_ = true;
	}

	if (key == GLUT_KEY_UP) {
		keyUpPressed_ = true;
	}

	if (key == GLUT_KEY_DOWN) {
		keyDownPressed_ = true;
	}
}

void MainScene::procSpecialKeysUp(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) {
		keyLeftPressed_ = false;
	}

	if (key == GLUT_KEY_RIGHT) {
		keyRightPressed_ = false;
	}

	if (key == GLUT_KEY_UP) {
		keyUpPressed_ = false;
	}

	if (key == GLUT_KEY_DOWN) {
		keyDownPressed_ = false;
	}
}

void MainScene::procKeys(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		if (drawAxes_) {
			drawAxes_ = false;
		}
		else {
			drawAxes_ = true;
		}
		break;
	case 'c':
		screenOn_ = false;
		break;
	case 'm':
		screenOn_ = true;
		break;
	case 'p':
		if (musicOn_) {
			soundEngine_->setAllSoundsPaused(true);
			musicOn_ = false;
		}
		else {
			soundEngine_->setAllSoundsPaused(false);
			musicOn_ = true;
		}
		break;
	case 27:
		exit(0);
	}
}

void MainScene::procMouse(int button, int state, int x, int y) {
	//Middle scroll wheel : zoom in or out with next two functions
	if (button == 3) {
		if (state == GLUT_UP) {
			zoomFactor_ -= 0.1f;
		}
	}

	if (button == 4) {
		if (state == GLUT_UP) {
			zoomFactor_ += 0.1f;
		}
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		std::swap(squareColor1_, triangleColor1_);
		std::swap(squareColor2_, triangleColor2_);
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		soundEngine_->removeAllSoundSources();
		currentAudioTrack_ += 1;
		currentAudioTrack_ = currentAudioTrack_ % audioTracks_.size();
		soundEngine_->play2D(audioTracks_[currentAudioTrack_].data(), true);
		std::cout << "MainScene::procMouse : Now playing track from " << audioTracks_[currentAudioTrack_] << std::endl;
	}
}

void MainScene::updateCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1 / zoomFactor_, 1 / zoomFactor_, -1 / zoomFactor_, 1 / zoomFactor_, -1, 1);
	glTranslatef(camX_, camY_, 0);
	glMatrixMode(GL_MODELVIEW);
}