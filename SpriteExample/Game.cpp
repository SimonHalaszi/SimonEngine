#include "Game.hpp"

#include "ArchiveScene.hpp"
#include "TemplateScene.hpp"
#include "TitleScreenScene.hpp"

#include "textureRegistry.hpp"
#include "SpriteRegistry.hpp"
#include "SpriteSheetRegistry.hpp"

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

void Game::changeScene(std::unique_ptr<Scene> newScene) {
	pendingScene_ = std::move(newScene);
}

void Game::updateTimer(int v) {
	int updatesPerSecond = 1;
	if (currentScene_) {
		updatesPerSecond = currentScene_->getUpdateSpeed();

		if (currentScene_->isUpdating()) {
			currentScene_->incrementUpdateFrame();
			currentScene_->sceneUpdate();
		}
	}

	if (pendingScene_) {
		if (currentScene_) {
			currentScene_->sceneDeInit();
		}
		currentScene_ = std::move(pendingScene_);
		if (currentScene_) {
			currentScene_->sceneInit();
		}
	}

	InputManager::getInstance().update();

	glutTimerFunc(int(1000 / updatesPerSecond), GAMEupdateTimer, v);
}

void Game::frameTimer(int v) {
	glutPostRedisplay();
	int frameUpdatesPerSecond = 1;
	if (currentScene_) {
		frameUpdatesPerSecond = currentScene_->getFrameSpeed();
	}
	glutTimerFunc(int(1000 / frameUpdatesPerSecond), GAMEframeTimer, v); // Updates
}

void GAMEdraw() {
	const Scene* currentScene = Game::getInstance().getCurrentScene();
	if (currentScene) {
		glClear(GL_COLOR_BUFFER_BIT);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		if (currentScene->isDrawing()) {
			currentScene->sceneDraw();
		}
		glFlush();
		glutSwapBuffers();
	}
}

void Game::animationTimer(int v) {
	int animationUpdatesPerSecond = 1;
	if (currentScene_) {
		animationUpdatesPerSecond = currentScene_->getAnimationUpdateSpeed();
		if (currentScene_->isUpdatingAnimations()) {
			currentScene_->incrementAnimationFrame();
		}
	}
	glutTimerFunc(int(1000 / animationUpdatesPerSecond), GAMEanimationTimer, v); // Creates a frame delay that is counted in miliseconds
}

void Game::init() {
	glClearColor(0.0, 0.0, 0.0, 1.0); // clear the window screen
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glutSpecialFunc(INPUTMANAGERprocSpecialKeys);
	glutSpecialUpFunc(INPUTMANAGERprocSpecialKeysUp);
	glutKeyboardFunc(INPUTMANAGERprocKeys);
	glutKeyboardUpFunc(INPUTMANAGERprocKeysUp);
	glutMouseFunc(INPUTMANAGERprocMouse);
	glutMotionFunc(INPUTMANAGERmouseMove);
	glutPassiveMotionFunc(INPUTMANAGERpassiveMouseMove);

	if (!currentScene_) {
		// THIS IS THE INITIAL SCENE
		currentScene_ = std::make_unique<TitleScreenScene>();
	}

	if (currentScene_) {
		currentScene_->sceneInit();
	}

	glutDisplayFunc(GAMEdraw);

	// Start timers
	glutTimerFunc(0, GAMEanimationTimer, 0);  // Animation Updates
	glutTimerFunc(0, GAMEupdateTimer, 0); // Game Updates
	glutTimerFunc(0, GAMEframeTimer, 0); // Frame Updates
}

void Game::safeGameExit() {
	// sceneDeInit safely frees all resources allocated and all managers
	// If we dont deInit scene before exit we can get some weird errors
	if (currentScene_) {
		currentScene_->sceneDeInit();
	}
	exit(0);
}