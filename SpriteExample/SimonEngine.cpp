#include <GL/glut.h>
#include <GL/freeglut.h>
#include <FreeImage/FreeImage.h>
#include <stdio.h>
#include <math.h>
#include <IrrKlang/irrKlang.h>

#include <vector>
#include <iostream>
#include <string>

#include "utilities.hpp"
#include "drawFunctions.hpp"
#include "textureRegistry.hpp"

using namespace irrklang;

#define WIN_X 100
#define WIN_Y 100
#define WIN_H 600 // in pixels
#define WIN_W 600

std::vector<GLuint> playerAnimationTextures;

// Global Program Variables
	unsigned int frame = 0;

	ColorRGB squareColor1 = { 1, 0, 0 };
	ColorRGB squareColor2 = { 1, 0.8, 0.2 };
	ColorRGB triangleColor1 = { 0.0, 1, 0.0 };
	ColorRGB triangleColor2 = { 0.2, 1, 0.8 };

	float squareRotation = 0;
	float triangleRotation = 0;

	// Player Variables
	PositionXY playerPos = { 0, 0 };
	float moveX = 0, moveY = 0;
	bool movePressed = false;
	bool mirrorPlayer = false;

	// Inputs
	bool keyLeftPressed = false;
	bool keyRightPressed = false;
	bool keyUpPressed = false;
	bool keyDownPressed = false;

	bool drawAxes = true;
	bool screenOn = true;
	bool musicOn = true;

	float zoomFactor = 1.0; // Global, if you want. Modified by user input. Initially 1.0
	float camX = 0, camY = 0, speed = 1; // Global for camera movement.

	int currentAudioTrack = 0;

	// Update Variables
	int animationUpdatesPerSecond = 10;
	int physicsUpdatesPerSecond = 244;

	// Vectors and Filepaths used for demonstrating tiling and subtexture system
	std::vector<SubTexture> runningTilesBills;
	std::string runningTilesBillsFilepath = "sprite/BillsGuy-sheet.png";

	std::vector<SubTexture> runningTilesBrowns;
	std::string runningTilesBrownsFilepath = "sprite/TwoGuys-sheet.png";

	SubTexture billsTile;
	SubTexture brownsTile;

	// Creates sound engine
	ISoundEngine* SoundEngine = createIrrKlangDevice();

	std::vector<std::string> playerAnimationTextureFilePaths = {	// File names for the files from which texture images are loaded
		"sprite/BillsGuy1.png",
		"sprite/BillsGuy2.png",
		"sprite/BillsGuy3.png",
		"sprite/BillsGuy4.png",
		"sprite/BillsGuy5.png",
		"sprite/BillsGuy6.png"
	};

	std::vector<std::string> audioTracks = {
		"audio/CBS.mp3",
		"audio/FOX.mp3",
		"audio/NBC.mp3"
	};

void init(void) {

	glClearColor(0.0, 0.0, 0.0, 1.0); // clear the window screen
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	SoundEngine->play2D(audioTracks[currentAudioTrack].data(), true);
}

void procSpecialKeys(int key, int x, int y)
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

void procSpecialKeysUp(int key, int x, int y)
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

void procKeys(unsigned char key, int x, int y)
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
			SoundEngine->setAllSoundsPaused(true);
			musicOn = false;
		}
		else {
			SoundEngine->setAllSoundsPaused(false);
			musicOn = true;
		}
		break;
	case 27: // escape
		exit(0);
	}
}

void updateCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1 / zoomFactor, 1 / zoomFactor, -1 / zoomFactor, 1 / zoomFactor, -1, 1);
	glTranslatef(camX, camY, 0);
	glMatrixMode(GL_MODELVIEW);
}

void procMouse(int button, int state, int x, int y) {
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
		SoundEngine->removeAllSoundSources();
		currentAudioTrack += 1;
		currentAudioTrack = currentAudioTrack % audioTracks.size();
		SoundEngine->play2D(audioTracks[currentAudioTrack].data(), true);
	}

}

// Makes a vector of subTexture coordinates
// That is takes the texture from texID, how much tiles it is wide and tall, and the tile you want to start at and end at
// You will get all tiles including startTile to including endTile. Not a half open range.
std::vector<SubTexture> tileTexture(GLuint texID, int tilesWide, int tilesTall, TileIndex startTile, TileIndex endTile) {
	std::vector<SubTexture> tiles;

	// Go through texture a tile at a time from starTile to and including endTile
	for (int y = startTile.y; y <= endTile.y; ++y) {
		for (int x = startTile.x; x <= endTile.x; ++x) {
			SubTexture temp;

			// Calculating the left and right U texture coordinates
			temp.u0 =	x				/ (float)tilesWide;
			temp.u1 =	(x + 1)			/ (float)tilesWide;

			// Calculating the top and bottom V texture coordinates
			temp.v1 =	1.0f - y		/ (float)tilesTall;
			temp.v0 =	1.0f - (y + 1)	/ (float)tilesTall;

			// Add these tile coordinates
			tiles.push_back(temp);
		}
	}

	std::cout << "Created " << tiles.size() << " SubTexture tiles." << std::endl;

	return tiles;
}

// Same thing but a singular tile
SubTexture tileTexture(GLuint texID, int tilesWide, int tilesTall, TileIndex tile) {
	// Go through texture a tile at a time from starTile to and including endTile
	SubTexture temp;

	// Calculating the left and right U texture coordinates
	temp.u0 = tile.x / (float)tilesWide;
	temp.u1 = (tile.x + 1) / (float)tilesWide;

	// Calculating the top and bottom V texture coordinates
	temp.v1 = 1.0f - tile.y / (float)tilesTall;
	temp.v0 = 1.0f - (tile.y + 1) / (float)tilesTall;

	return temp;
}

void setupInputs() {
	glutSpecialFunc(procSpecialKeys);
	glutSpecialUpFunc(procSpecialKeysUp);
	glutKeyboardFunc(procKeys);
	glutMouseFunc(procMouse);
}

void update(int v) {
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
	if(squareRotation >= 360){
		squareRotation = 0;
	}

	triangleRotation += -10 * deltaTime;
	if (triangleRotation <= -360) {
		triangleRotation = 0;
	}

	updateCamera();
	
	glutPostRedisplay(); // Redisplay every physics update
	glutTimerFunc(int(1000 * deltaTime), update, v); // Updatess
}

void timer(int v)
{
	frame++; // Changed to an unsigned int, animation vectors will handle their own looping

	glutTimerFunc(int(1000 / animationUpdatesPerSecond), timer, v); // Creates a frame delay that is counted in miliseconds
}

void draw() {
	glClear(GL_COLOR_BUFFER_BIT);

	if (screenOn) {

		TextureRegistry* texRegistry = &TextureRegistry::getInstance();

		// Using texture registry to get loaded texture IDs
		GLuint billsFilepath = texRegistry->getTextureID(runningTilesBillsFilepath);
		GLuint brownsFilepath = texRegistry->getTextureID(runningTilesBrownsFilepath);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		// Drawing a normal sprite
		drawSprite(
			playerPos, 
			0.25f, 0.0f, 
			mirrorPlayer, false, 
			playerAnimationTextures[frame % runningTilesBills.size()]
		);

		// Drawing a SubTexture'd sprite 
		drawSprite(
			{ 0.5f, -0.5f }, 
			0.1f, 0.0f, 
			false, true, 
			billsFilepath,
			billsTile
		);

		drawSprite(
			{ -0.5f, 0.5f }, 
			0.1f, 0.0f, 
			true, false, 
			brownsFilepath,
			brownsTile
		);

		// Drawing a vector of SubTexture'd sprites
		drawSprite(
			{0.5f, 0.5f}, 
			0.1f, 0.0f, 
			false, false, 
			billsFilepath,
			runningTilesBills[frame % runningTilesBills.size()]
		);
		drawSprite(
			{ -0.5f, -0.5f }, 
			0.1f, 0.0f, 
			true, true, 
			brownsFilepath,
			runningTilesBrowns[frame % runningTilesBrowns.size()]
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

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // RGB mode, added GLUT Double for double buffering, so that screen clearing works
	glutInitWindowSize(WIN_W, WIN_H); // window size
	glutInitWindowPosition(WIN_X, WIN_Y);
	glutCreateWindow("(Simon Halaszi) (811196947)");

	init();

	TextureRegistry* texRegistry = &TextureRegistry::getInstance();

	// Loading in all playerAnimationTextures into a vector
	for (const auto& str : playerAnimationTextureFilePaths) {
		GLuint id = texRegistry->loadTexture(str);
		if(id){
			playerAnimationTextures.push_back(id);
		}
	}

	// Loading sprite sheets
	texRegistry->loadTexture(runningTilesBillsFilepath);
	texRegistry->loadTexture(runningTilesBrownsFilepath);

	// First example of my texture tiling for sprite sheets
	runningTilesBills = tileTexture(
		texRegistry->getTextureID(runningTilesBillsFilepath),
		6, 1, 
		{0, 0}, {5, 0}
	);
	
	// See how this sprite sheet is layed out.
	// It goes from left to right and gets cells (0,2) to (2,2) despite them being on differing rows and past some others
	runningTilesBrowns = tileTexture(
		texRegistry->getTextureID(runningTilesBrownsFilepath),
		3, 4, 
		{ 0, 2 }, { 2, 3 }
	);

	// Getting a singular tile
	billsTile = tileTexture(
		texRegistry->getTextureID(runningTilesBillsFilepath),
		6, 1, 
		{ 0, 0 }
	);
	
	brownsTile = tileTexture(
		texRegistry->getTextureID(runningTilesBrownsFilepath),
		3, 4, 
		{ 0, 2 }
	);

	// Just to throw the already loaded error I added
	texRegistry->loadTexture(playerAnimationTextureFilePaths[0]);

	setupInputs();

	glutDisplayFunc(draw); // call the drawing function

	glutTimerFunc(0, timer, 0);  // Animation Updates
	glutTimerFunc(0, update, 0); // Physics Updates

	glutMainLoop();

	return 0;
}