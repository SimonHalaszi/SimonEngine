#include <GL/glut.h>
#include <GL/freeglut.h>
#include <FreeImage/FreeImage.h>
#include <stdio.h>
#include <math.h>
#include <IrrKlang/irrKlang.h>

#include <vector>
#include <iostream>
using namespace irrklang;

#define WIN_X 100
#define WIN_Y 100
#define WIN_H 600 // in pixels
#define WIN_W 600

// Creates sound engine
ISoundEngine* SoundEngine = createIrrKlangDevice();

int numFrames = 6; // Number of frames in the animation sequence.
GLuint texID[6]; // Texture ID's for the four textures.

std::vector<char*> textureFileNames = {	// File names for the files from which texture images are loaded
	(char*)"sprite/BillsGuy1.png",
	(char*)"sprite/BillsGuy2.png",
	(char*)"sprite/BillsGuy3.png",
	(char*)"sprite/BillsGuy4.png",
	(char*)"sprite/BillsGuy5.png",
	(char*)"sprite/BillsGuy6.png"
};

std::vector<char*> audioTracks = {
	(char*)"audio/CBS.mp3",
	(char*)"audio/FOX.mp3",
	(char*)"audio/NBC.mp3"
};

struct ColorRGB {
	float red;
	float green;
	float blue;
};

struct PositionXY {
	float x;
	float y;
};

// Global Program Variables
	int frame = 0;

	ColorRGB squareColor = { 1, 0, 0 };
	ColorRGB triangleColor = { 0, 1, 0 };

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
	int animationUpdatesPerSecond = 15;
	int physicsUpdatesPerSecond = 60;


void init(void) {

	glClearColor(0.0, 0.0, 0.0, 1.0); // clear the window screen
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	SoundEngine->play2D(audioTracks[currentAudioTrack], true);
}

// Function for drawing squares given a PositionXY, a size (float), and 4 ColorRGB for the vertices
void drawSquare(PositionXY pos, float size, float angle = 0, ColorRGB c1 = { 1, 1, 1 }, ColorRGB c2 = { 1, 1, 1 }, ColorRGB c3 = { 1, 1, 1 }, ColorRGB c4 = { 1, 1, 1 }) {
	glPushMatrix();

	glTranslatef(pos.x, pos.y, 0.0f);   // Move to triangle position
	glRotatef(angle, 0.0f, 0.0f, 1.0f); // Rotate around Z axis	
	
	glBegin(GL_QUADS);              // Start drawing a quad
		glColor3f(c1.red, c1.green, c1.blue);
		glVertex3f(-size, -size, 0.0f); // Bottom-left
		
		glColor3f(c2.red, c2.green, c2.blue);
		glVertex3f(size, -size, 0.0f); // Bottom-right
		
		glColor3f(c3.red, c3.green, c3.blue);
		glVertex3f(size, size, 0.0f); // Top-right
		
		glColor3f(c4.red, c4.green, c4.blue);
		glVertex3f(-size, size, 0.0f); // Top-left
	glEnd();                        // End drawing

	glPopMatrix();
}

// Function for drawing triangles given a PositionXY, a size (float), and 3 ColorRGB for the vertices
void drawTriangle(PositionXY pos, float size, float angle = 0, ColorRGB c1 = {1, 1, 1}, ColorRGB c2 = {1, 1, 1}, ColorRGB c3 = {1, 1, 1}) {
	glPushMatrix();
	
	glTranslatef(pos.x, pos.y, 0.0f);   // Move to triangle position
	glRotatef(angle, 0.0f, 0.0f, 1.0f); // Rotate around Z axis

	glBegin(GL_TRIANGLES);              // Start drawing a triangle

		glColor3f(c1.red, c1.green, c1.blue);
		glVertex3f(-size, -size, 0.0f); // Bottom-left

		glColor3f(c2.red, c2.green, c2.blue);
		glVertex3f(size, -size, 0.0f); // Bottom-right

		glColor3f(c3.red, c3.green, c3.blue);
		glVertex3f(0.0f, size, 0.0f); // Top

	glEnd();                        // End drawing

	glPopMatrix();
}

// Function for drawing a sprite to a square given a PositionXY, a size (float), and a GLuint TextureID
void drawSprite(PositionXY pos, float size, float angle, bool mirror, GLuint textureID) {
	glPushMatrix();

	glTranslatef(pos.x, pos.y, 0.0f);   // Move to triangle position
	glRotatef(angle, 0.0f, 0.0f, 1.0f); // Rotate around Z axis

	if (mirror) {
		glScalef(-1.0f, 1.0f, 1.0f);
	}

	glEnable(GL_TEXTURE_2D); // Enable texturing
	
		GLint width, height;
		glBindTexture(GL_TEXTURE_2D, textureID); // Which texture

		// Fix blur
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glBegin(GL_POLYGON);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-size, -size, 0);
		glTexCoord2f(1.0, 0.0);
		glVertex3f(size, -size, 0);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(size, size, 0);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-size, size, 0);

	glEnd();

	glDisable(GL_TEXTURE_2D); // Turn texturing off

	glPopMatrix();
}

void drawLine(PositionXY pos1, PositionXY pos2, ColorRGB c1, ColorRGB c2) {
	glBegin(GL_LINES);              // Start drawing a line
		glColor3f(c1.red, c1.green, c1.blue);
		glVertex3f(pos1.x, pos1.y, 0.0f); // Start

		glColor3f(c2.red, c2.green, c2.blue);
		glVertex3f(pos2.x, pos2.y, 0.0f); // End
	glEnd();                        // End drawing
}

void drawAxis(PositionXY pos1, PositionXY pos2, ColorRGB c1, ColorRGB c2, char axis) {
	if (axis == 'x') {
		drawLine(pos1, pos2, c1, c2);
		drawTriangle(pos2, 0.015, 270, c2, c2, c2);
	}
	else if (axis == 'y') {
		drawLine(pos1, pos2, c1, c2);
		drawTriangle(pos2, 0.015, 0, c2, c2, c2);
	}
	else if (axis == 'z') {
		std::cout << "bruh this is 2D" << std::endl;
	}
	else {
		return;
	}
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
		std::swap(squareColor, triangleColor);
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		SoundEngine->removeAllSoundSources();
		currentAudioTrack += 1;
		currentAudioTrack = currentAudioTrack % audioTracks.size();
		SoundEngine->play2D(audioTracks[currentAudioTrack], true);
	}

}

void loadTextures() {
	int i;
	glGenTextures(numFrames, texID); // Get the texture object IDs.
	for (i = 0; i < numFrames; i++) {
		void* imgData; // Pointer to image color data read from the file.
		int imgWidth; // The width of the image that was read.
		int imgHeight; // The height.
		FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename(textureFileNames[i]);
		if (format == FIF_UNKNOWN) {
			printf("Unknown file type for texture image file %s\n", textureFileNames[i]);
			continue;
		}
		FIBITMAP* bitmap = FreeImage_Load(format, textureFileNames[i], 0); // Read image from file.
		if (!bitmap) {
			printf("Failed to load image %s\n", textureFileNames[i]);
			continue;
		}
		FIBITMAP* bitmap2 = FreeImage_ConvertTo24Bits(bitmap); // Convert to RGB or BGR format
		FreeImage_Unload(bitmap);
		imgData = FreeImage_GetBits(bitmap2); // Grab the data we need from the bitmap.
		imgWidth = FreeImage_GetWidth(bitmap2);
		imgHeight = FreeImage_GetHeight(bitmap2);
		if (imgData) {
			printf("Texture image loaded from file %s, size %dx%d\n",
				textureFileNames[i], imgWidth, imgHeight);
			glBindTexture(GL_TEXTURE_2D, texID[i]); // Will load image data into texture object #i
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_BGR_EXT,
				GL_UNSIGNED_BYTE, imgData);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Required since there are no mipmaps.
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		}
		else {
			printf("Failed to get texture data from %s\n", textureFileNames[i]);
		} // end of else
	} // end of for loop
} // end of LoadTextures()

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

	glutTimerFunc(int(1000 * deltaTime), update, v); // Updates

	updateCamera();
}

void timer(int v)
{
	frame++;

	if (frame >= numFrames) {
		frame = 0;
	}

	glutPostRedisplay();
	glutTimerFunc(int(1000 / animationUpdatesPerSecond), timer, v); // Creates a frame delay that is counted in miliseconds
}

void draw() {
	glClear(GL_COLOR_BUFFER_BIT);

	if (screenOn) {

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		drawSprite(playerPos, 0.25, 0, mirrorPlayer, texID[frame]);

		drawSquare({ 0.5, 0 }, 0.1, -15, squareColor, squareColor, squareColor, squareColor);
		drawTriangle({ -0.5, 0 }, 0.1, 45, triangleColor, triangleColor, triangleColor);

		// Draw X and Y axes at orgin of square if wanted
		if (drawAxes) {
			drawAxis({ 0, 0 }, { 0.25, 0 }, { 1, 0 ,0 }, { 1, 0, 0 }, 'x');
			drawAxis({ 0, 0 }, { 0, 0.25 }, { 0, 1 ,0 }, { 0, 1, 0 }, 'y');
		}

	}

	glFlush();
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // RGB mode, DOUBLE needed to actually clear the screen
	glutInitWindowSize(WIN_W, WIN_H); // window size
	glutInitWindowPosition(WIN_X, WIN_Y);
	glutCreateWindow("Simon Halaszi 811196947");

	init();

	loadTextures();

	setupInputs();

	glutDisplayFunc(draw); // call the drawing function

	glutTimerFunc(0, timer, 0);
	glutTimerFunc(0, update, 0); // Updates

	glutMainLoop();
	return 0;
}