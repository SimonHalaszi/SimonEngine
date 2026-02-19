#include "Game.hpp"
#include <iostream>

// in pixels
#define WIN_X 100
#define WIN_Y 100
#define WIN_H 600
#define WIN_W 600

// P.S. if some of these comments are just straight up wrong its because I did a lot of refactoring

// Look how clean my main is :). Makes me want to cry
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE); // Changed to RGBA also added Double buffering
	glutInitWindowSize(WIN_W, WIN_H); // window size
	glutInitWindowPosition(WIN_X, WIN_Y);
	glutCreateWindow("(Simon Halaszi) (811196947)");

	// LET THE GAMES BEGIN
	Game::getInstance().init();

	glutMainLoop();

	return 0;
}