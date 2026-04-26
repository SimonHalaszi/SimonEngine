#include "Game.hpp"

#include "ArchiveScene.hpp"
#include "TemplateScene.hpp"
#include "TitleScreenScene.hpp"

#include "WindowConstants.hpp"

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

	// Play the game from editor
	if (InputManager::getInstance().isSpecialKeyPressed(mapSpecialKey(GLUT_KEY_F1))
	&& currentScene_
	&& editor_->inEditor()) {
		editor_->exitEditor();
	}
	// Return to editor from current scene with state
	if( InputManager::getInstance().isSpecialKeyPressed(mapSpecialKey(GLUT_KEY_F2))
	&& currentScene_ 
	&& !editor_->inEditor()) {
		editor_->enterEditor();
	}
	// Reset the scene in editor
	if (InputManager::getInstance().isSpecialKeyPressed(mapSpecialKey(GLUT_KEY_F3))
	&& currentScene_
	&& editor_->inEditor()) {
		editor_ = nullptr;
		currentScene_->sceneDeInit();
		currentScene_->sceneInit();
		editor_ = std::make_unique<Editor>(currentScene_.get());
		editor_->enterEditor();
	}
	// Reset the scene in scene
	if (InputManager::getInstance().isSpecialKeyPressed(mapSpecialKey(GLUT_KEY_F4))
	&& currentScene_
	&& !editor_->inEditor()) {
		editor_ = nullptr;
		currentScene_->sceneDeInit();
		currentScene_->sceneInit();
		editor_ = std::make_unique<Editor>(currentScene_.get());
		editor_->exitEditor();
	}
	
	// Updates to current scene. When in "editor" mode this will not be called
	if (currentScene_) {
		updatesPerSecond = currentScene_->getUpdateSpeed();

		if (currentScene_->isUpdating() && !editor_->inEditor()) {
			currentScene_->incrementUpdateFrame();
			currentScene_->sceneUpdate();
		}
	}
	// Editor updating logic.
	if(editor_->inEditor()) {
		editor_->editorUpdate();
	}

	if (editor_->topPanelMarkedForQuiting()) {
		safeGameExit();
	}

	// Scene changing logic. Should actually run in "editor" mode
	if (pendingScene_) {
		bool wasInEditorMode = editor_->inEditor();
		// Fully deinit current scene
		if (currentScene_) {
			editor_ = nullptr;
			currentScene_->sceneDeInit();
		}
		// Move pending scene to current scene afterwards
		currentScene_ = std::move(pendingScene_);
		// Fully init new scene
		if (currentScene_) {
			currentScene_->sceneInit();
			updatesPerSecond = currentScene_->getUpdateSpeed();
			editor_ = std::make_unique<Editor>(currentScene_.get());
		}
		// Enter editor based on if you were already or not
		if (wasInEditorMode) {
			editor_->enterEditor();
		}
		else {
			editor_->exitEditor();
		}
	}

	// Input manager updates. Should actually run in "editor" mode
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
	const Editor* editor = Game::getInstance().getEditor();
	
	// Drawing the current scene. Should actually run in "editor" mode
	if (currentScene) {
		glClear(GL_COLOR_BUFFER_BIT);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		if (currentScene->isDrawing() && !editor->inEditor()) {
			glPushMatrix();
			glViewport(0, 0, ENGINE_WIN_W, ENGINE_WIN_H);
			currentScene->sceneDraw();
			glPopMatrix();
		}
		if (editor->inEditor()) {
			editor->editorDraw();
			// Editor will draw the scene
		}
		glFlush();
		glutSwapBuffers();
	}
}

void Game::animationTimer(int v) {
	int animationUpdatesPerSecond = 1;
	// Wont run in editor mode. Animations arent relevant for that
	if (currentScene_) {
		animationUpdatesPerSecond = currentScene_->getAnimationUpdateSpeed();
		if (currentScene_->isUpdatingAnimations() && !editor_->inEditor()) {
			currentScene_->incrementAnimationFrame();
		}
	}
	glutTimerFunc(int(1000 / animationUpdatesPerSecond), GAMEanimationTimer, v); // Creates a frame delay that is counted in miliseconds
}

#include "SceneFactory.hpp";

void Game::init() {
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE); // Changed to RGBA also added Double buffering
	glutInitWindowSize(ENGINE_WIN_W, ENGINE_WIN_H); // window size
	glutInitWindowPosition(ENGINE_WIN_X, ENGINE_WIN_Y);
	glutCreateWindow("(Simon Halaszi) (811196947)");
	
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
		currentScene_ = SceneFactory::getInstance().defaultScene();
	}

	if (currentScene_) {
		currentScene_->sceneInit();
		editor_ = std::make_unique<Editor>(currentScene_.get());
	}

	// CHOOSE TO LAUNCH IN EDITOR OR NOT
	bool launchInEditor = true;
	if (launchInEditor) {
		if (editor_) {
			editor_->enterEditor();
		}
	} 
	else {
		if (editor_) {
			editor_->exitEditor();
		}
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
	if (editor_) {
		editor_ = nullptr;
	}
	if (currentScene_) {
		currentScene_->sceneDeInit();
	}
	std::cout << "GAME::safeGameExit : Exited game" << std::endl;
	exit(0);
}