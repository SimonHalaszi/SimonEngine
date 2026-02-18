#include "Game.hpp"

// Function Wrappers
void GAMEdisplay() {
	Game::getInstance().draw();
}
void GAMEanimationTimer(int v) {
	Game::getInstance().animationTimer(v);
}
void GAMEupdate(int v) {
	Game::getInstance().update(v);
}

void GAMEprocSpecialKeys(int key, int x, int y) {
	Game::getInstance().procSpecialKeys(key, x, y);
}

void GAMEprocSpecialKeysUp(int key, int x, int y) {
	Game::getInstance().procSpecialKeysUp(key, x, y);
}

void GAMEprocKeys(unsigned char key, int x, int y) {
	Game::getInstance().procKeys(key, x, y);
}

void GAMEprocMouse(int button, int state, int x, int y) {
	Game::getInstance().procMouse(button, state, x, y);
}

Game::Game() :
	audioTracks({
		   "audio/CBS.mp3",
		   "audio/FOX.mp3",
		   "audio/NBC.mp3"
	}),
	runningTilesBrownsFilepath("sprite/TwoGuys-sheet.png"),
	runningTilesBillsFilepath("sprite/BillsGuy-sheet.png")
{
	textures = &TextureRegistry::getInstance();
	sprites = &SpriteRegistry::getInstance();
	spriteSheets = &SpriteSheetRegistry::getInstance();

	billsRunningSheetName = "billsRunning";
	brownsRunningSheetName = "brownsRunning";
	brownsSpriteName = "brownsSprite";
	billsSpriteName = "billsSprite";

	soundEngine = irrklang::createIrrKlangDevice();
}

void Game::init() {
	glClearColor(0.0, 0.0, 0.0, 1.0); // clear the window screen
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	soundEngine->play2D(audioTracks[currentAudioTrack].data(), true);

	// Loading sprite sheets
	textures->loadTexture(runningTilesBillsFilepath);
	textures->loadTexture(runningTilesBrownsFilepath);

	// First example of my texture tiling for sprite sheets
	spriteSheets->makeSpriteSheet(
		billsRunningSheetName,
		textures->getTextureID(runningTilesBillsFilepath),
		6, 1,
		{ 0, 0 }, { 5, 0 }
	);

	// See how this sprite sheet is layed out.
	// It goes from left to right and gets cells (0,2) to (2,2) despite them being on differing rows and past some others
	spriteSheets->makeSpriteSheet(
		brownsRunningSheetName,
		textures->getTextureID(runningTilesBrownsFilepath),
		3, 4,
		{ 0, 2 }, { 2, 3 }
	);

	// Getting a singular tile
	sprites->makeSprite(
		billsSpriteName,
		textures->getTextureID(runningTilesBillsFilepath),
		6, 1,
		{ 0, 0 }
	);

	sprites->makeSprite(
		brownsSpriteName,
		textures->getTextureID(runningTilesBrownsFilepath),
		3, 4,
		{ 0, 2 }
	);

	// Just to throw the already loaded error I added
	textures->loadTexture(runningTilesBrownsFilepath);

	setupInputs();

	glutDisplayFunc(GAMEdisplay); // call the drawing function

	glutTimerFunc(0, GAMEanimationTimer, 0);  // Animation Updates
	glutTimerFunc(0, GAMEupdate, 0); // Physics Updates
}

void Game::draw() {
	glClear(GL_COLOR_BUFFER_BIT);

	if (screenOn) {
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		SpriteSheet billsRunningSpriteSheet = SpriteSheetRegistry::getInstance().getSpriteSheet(billsRunningSheetName);
		SpriteSheet brownsRunningSpriteSheet = SpriteSheetRegistry::getInstance().getSpriteSheet(brownsRunningSheetName);

		Sprite billsSprite = SpriteRegistry::getInstance().getSprite(billsSpriteName);
		Sprite brownsSprite = SpriteRegistry::getInstance().getSprite(brownsSpriteName);

		// If moving do the sprite sheet animation if not just draw the sprite
		if (moveX || moveY) {
			// Drawing from a sprite sheet
			drawSprite(
				playerPos,
				0.25f, 0.0f,
				mirrorPlayer, false,
				billsRunningSpriteSheet[frame % billsRunningSpriteSheet.spriteCount()]
			);
		}
		else {
			drawSprite(
				playerPos,
				0.25f, 0.0f,
				mirrorPlayer, false,
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
			billsRunningSpriteSheet[frame % billsRunningSpriteSheet.spriteCount()]
		);
		drawSprite(
			{ -0.5f, -0.5f },
			0.1f, 0.0f,
			true, true,
			brownsRunningSpriteSheet[frame % brownsRunningSpriteSheet.spriteCount()]
		);

		drawSquare(
			{ 0.5f, 0.0f },
			0.1f, squareRotation,
			false, false,
			squareColor1, squareColor2, squareColor1, squareColor2
		);
		drawTriangle(
			{ -0.5f, 0.0f },
			0.1f, triangleRotation,
			false, false,
			triangleColor1, triangleColor1, triangleColor2
		);

		// Draw X and Y axes at orgin of square if wanted
		if (drawAxes) {
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

	glFlush();
	glutSwapBuffers();
}

void Game::update(int v) {
	float deltaTime = (1.0f / physicsUpdatesPerSecond);

	moveX = 0.0f;
	moveY = 0.0f;

	if (keyLeftPressed) {
		moveX -= 1.0f * deltaTime;
		mirrorPlayer = true;
	}

	if (keyRightPressed) {
		moveX += 1.0f * deltaTime;
		mirrorPlayer = false;
	}

	if (keyUpPressed) {
		moveY += 1.0f * deltaTime;
	}


	if (keyDownPressed) {
		moveY -= 1.0f * deltaTime;
	}

	playerPos.x += moveX;
	playerPos.y += moveY;

	squareRotation += 10 * deltaTime;
	if (squareRotation >= 360) {
		squareRotation = 0;
	}

	triangleRotation += -10 * deltaTime;
	if (triangleRotation <= -360) {
		triangleRotation = 0;
	}

	updateCamera();

	glutPostRedisplay(); // Redisplay every physics update
	glutTimerFunc(int(1000 * deltaTime), GAMEupdate, v); // Updatess
}

void Game::animationTimer(int v) {
	frame++; // Changed to an unsigned int, animation vectors will handle their own looping
	glutTimerFunc(int(1000 / animationUpdatesPerSecond), GAMEanimationTimer, v); // Creates a frame delay that is counted in miliseconds
}

void Game::procSpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT) {
		keyLeftPressed = true;
	}

	if (key == GLUT_KEY_RIGHT) {
		keyRightPressed = true;
	}

	if (key == GLUT_KEY_UP) {
		keyUpPressed = true;
	}

	if (key == GLUT_KEY_DOWN) {
		keyDownPressed = true;
	}
}

void Game::procSpecialKeysUp(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT) {
		keyLeftPressed = false;
	}

	if (key == GLUT_KEY_RIGHT) {
		keyRightPressed = false;
	}

	if (key == GLUT_KEY_UP) {
		keyUpPressed = false;
	}

	if (key == GLUT_KEY_DOWN) {
		keyDownPressed = false;
	}
}

void Game::procKeys(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a':
		if (drawAxes) {
			drawAxes = false;
		}
		else {
			drawAxes = true;
		}
		break;
	case 'c':
		screenOn = false;
		break;
	case 'm':
		screenOn = true;
		break;
	case 'p':
		if (musicOn) {
			soundEngine->setAllSoundsPaused(true);
			musicOn = false;
		}
		else {
			soundEngine->setAllSoundsPaused(false);
			musicOn = true;
		}
		break;
	case 27: // escape
		exit(0);
	}
}

void Game::procMouse(int button, int state, int x, int y) {
	//Middle scroll wheel : zoom in or out with next two functions
	if (button == 3) {
		if (state == GLUT_UP) {
			zoomFactor -= 0.1;
		}
	}

	if (button == 4) {
		if (state == GLUT_UP) {
			zoomFactor += 0.1;
		}
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		std::swap(squareColor1, triangleColor1);
		std::swap(squareColor2, triangleColor2);
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		soundEngine->removeAllSoundSources();
		currentAudioTrack += 1;
		currentAudioTrack = currentAudioTrack % audioTracks.size();
		soundEngine->play2D(audioTracks[currentAudioTrack].data(), true);
	}
}

void Game::updateCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1 / zoomFactor, 1 / zoomFactor, -1 / zoomFactor, 1 / zoomFactor, -1, 1);
	glTranslatef(camX, camY, 0);
	glMatrixMode(GL_MODELVIEW);
}

void Game::setupInputs() {
	glutSpecialFunc(GAMEprocSpecialKeys);
	glutSpecialUpFunc(GAMEprocSpecialKeysUp);
	glutKeyboardFunc(GAMEprocKeys);
	glutMouseFunc(GAMEprocMouse);
}