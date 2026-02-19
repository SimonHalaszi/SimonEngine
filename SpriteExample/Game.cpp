#include "Game.hpp"

// Function wrappers needed because OpenGL expects a certain function signature for these
void GAMEanimationTimer(int v) {
	Game::getInstance().animationTimer(v);
}
void GAMEupdateTimer(int v) {
	Game::getInstance().updateTimer(v);
}
void GAMEframeTimer(int v) {
	Game::getInstance().frameTimer(v);
}

void GAMEdraw() {
	Scene* currentScene = Game::getInstance().getCurrentScene();
	if (currentScene) {
		glClear(GL_COLOR_BUFFER_BIT);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		currentScene->draw();
		glFlush();
		glutSwapBuffers();
	}
}
void GAMEprocSpecialKeys(int key, int x, int y) {
	Scene* currentScene = Game::getInstance().getCurrentScene();
	if (currentScene) {
		currentScene->procSpecialKeys(key, x, y);
	}
}
void GAMEprocSpecialKeysUp(int key, int x, int y) {
	Scene* currentScene = Game::getInstance().getCurrentScene();
	if (currentScene) {
		currentScene->procSpecialKeysUp(key, x, y);
	}
}
void GAMEprocKeys(unsigned char key, int x, int y) {
	Scene* currentScene = Game::getInstance().getCurrentScene();
	if (currentScene) {
		currentScene->procKeys(key, x, y);
	}
}
void GAMEprocMouse(int button, int state, int x, int y) {
	Scene* currentScene = Game::getInstance().getCurrentScene();
	if (currentScene) {
		currentScene->procMouse(button, state, x, y);
	}
}

void Game::init() {
	glClearColor(0.0, 0.0, 0.0, 1.0); // clear the window screen
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	currentScene_->init();

	setupInputs();

	glutDisplayFunc(GAMEdraw); // call the drawing function

	glutTimerFunc(0, GAMEanimationTimer, 0);  // Animation Updates
	glutTimerFunc(0, GAMEupdateTimer, 0); // Game Updates
	glutTimerFunc(0, GAMEframeTimer, 0); // Frame Updates
}

void Game::updateTimer(int v) {
	Scene* currentScene = Game::getInstance().getCurrentScene();
	int updatesPerSecond = 1;
	if (currentScene) {
		updatesPerSecond = currentScene->getUpdateSpeed();
		currentScene->update();
	}
	glutTimerFunc(int(1000 / updatesPerSecond), GAMEupdateTimer, v); // Updatess
}

void Game::frameTimer(int v) {
	glutPostRedisplay();
	Scene* currentScene = Game::getInstance().getCurrentScene();
	int frameUpdatesPerSecond = 1;
	if (currentScene) {
		frameUpdatesPerSecond = currentScene->getFrameSpeed();
	}
	glutTimerFunc(int(1000 / frameUpdatesPerSecond), GAMEframeTimer, v); // Updatess
}

void Game::animationTimer(int v) {
	Scene* currentScene = Game::getInstance().getCurrentScene();
	int animationUpdatesPerSecond = 1;
	if (currentScene) {
		animationUpdatesPerSecond = currentScene->getAnimationUpdateSpeed();
		currentScene->incrementAnimationFrame();
	}
	glutTimerFunc(int(1000 / animationUpdatesPerSecond), GAMEanimationTimer, v); // Creates a frame delay that is counted in miliseconds
}

void Game::setupInputs() {
	glutSpecialFunc(GAMEprocSpecialKeys);
	glutSpecialUpFunc(GAMEprocSpecialKeysUp);
	glutKeyboardFunc(GAMEprocKeys);
	glutMouseFunc(GAMEprocMouse);
}