#include "Editor.hpp"

Editor::Editor(Scene* scene)
: scene_(scene), hierarchy_(scene->getRootObjects()) {
	std::cout << "Editor::Editor() : Editor created " << std::endl;
	std::vector<std::unique_ptr<GameObject2D>>& rootObjects = scene->getRootObjects();
	for (auto& rootObject : rootObjects) {
		rootObject->updateWorldTransform();
	}
}

void Editor::editorDraw() const {
	// Translate position moved to to scene view
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-editorX_, -editorY_, 0);
	glOrtho(-1 / editorZoomFactor_, 1 / editorZoomFactor_, -1 / editorZoomFactor_, 1 / editorZoomFactor_, -1, 1);

	hierarchy_.draw();
	inspector_.draw();
	topPanel_.draw();
	objectsPanel_.draw();
}

void Editor::editorUpdate() {
	// Handle moving around in the editor scene view
	float physicsTime = 1.0f / scene_->getUpdateSpeed();
	if (InputManager::getInstance().isSpecialKeyDown(mapSpecialKey(GLUT_KEY_LEFT))) {
		editorX_ -= moveSpeed_ * physicsTime;
	}
	if (InputManager::getInstance().isSpecialKeyDown(mapSpecialKey(GLUT_KEY_RIGHT))) {
		editorX_ += moveSpeed_ * physicsTime;
	}
	if (InputManager::getInstance().isSpecialKeyDown(mapSpecialKey(GLUT_KEY_UP))) {
		editorY_ += moveSpeed_ * physicsTime;
	}
	if (InputManager::getInstance().isSpecialKeyDown(mapSpecialKey(GLUT_KEY_DOWN))) {
		editorY_ -= moveSpeed_ * physicsTime;
	}
	if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_SCROLLDOWN)) {
		if (editorZoomFactor_ > 0.1f) {
			editorZoomFactor_ -= 0.1f;
		}
	}
	if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_SCROLLUP)) {
		editorZoomFactor_ += 0.1f;
	}

	hierarchy_.update();
	inspector_.update();
	topPanel_.update();
	objectsPanel_.update();
}

Editor::~Editor() {
	std::cout << "Editor::~Editor() : Current editor destroyed " << std::endl;
	
	scene_ = nullptr;
}
void Editor::enterEditor() { 
	inEditor_ = true;
	std::cout << "Editor::enterEditor() : Entering editor mode " << std::endl;
	SoundManager::getInstance().pauseAll(); 
}

void Editor::exitEditor() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, 0);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	std::cout << "Editor::exitEditor() : Exiting editor mode " << std::endl;

	inEditor_ = false; 	
	if (!scene_->isPauseFlagged()) {
		SoundManager::getInstance().unpauseAll();
	}
}