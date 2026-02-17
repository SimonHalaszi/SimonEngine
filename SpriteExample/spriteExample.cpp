#include <GL/glut.h>
#include <GL/freeglut.h>
#include <FreeImage/FreeImage.h>
#include <stdio.h>
#include <math.h>
#include <IrrKlang/irrKlang.h>
#include <vector>
using namespace irrklang;

#define WIN_X 100
#define WIN_Y 100
#define WIN_H 600 // in pixels
#define WIN_W 600

int frame = 0;

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


void init(void) {

	glClearColor(0.0, 0.0, 0.0, 1.0); // clear the window screen
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	// SoundEngine->play2D("audio/nyancat.mp3", true);
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glEnable(GL_TEXTURE_2D); // Enable texturing

	glBindTexture(GL_TEXTURE_2D, texID[frame]); // Which texture
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.35, -0.35, 0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.35, -0.35, 0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.35, 0.35, 0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-0.35, 0.35, 0);
	glEnd();

	glDisable(GL_TEXTURE_2D); // Turn texturing off

	glFlush();
	glutSwapBuffers();
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

void timer(int v)
{
	frame++;

	if (frame >= numFrames) {
		frame = 0;
	}

	glutPostRedisplay();
	glutTimerFunc(100, timer, v); // Creates a frame delay that is counted in miliseconds
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB); // RGB mode
	glutInitWindowSize(WIN_W, WIN_H); // window size
	glutInitWindowPosition(WIN_X, WIN_Y);
	glutCreateWindow("Simon Halaszi 811196947");

	glutTimerFunc(0, timer, 0);

	init();

	loadTextures();

	glutDisplayFunc(MyDisplay); // call the drawing function

	glutMainLoop();
	return 0;
}