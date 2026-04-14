#include "Editor.hpp"

Editor::Editor(Scene* scene)
: scene_(scene), hierarchy_(scene->getRootObjects()), assetPanel_(scene)
{
	std::cout << "Editor::Editor() : Editor created " << std::endl;
	std::vector<std::unique_ptr<GameObject2D>>& rootObjects = scene->getRootObjects();

	middlePanelContext_.viewportX = HIERARCHY_PANEL_W;
	middlePanelContext_.viewportY = OBJECTS_PANEL_H;
	middlePanelContext_.viewportWidth = SCENE_WIN_W;
	middlePanelContext_.viewportHeight = SCENE_WIN_H;

	// Technically these do change but not in a way that will matter specifically for updates, yet?
	middlePanelContext_.scrollOffsetX = 0.0f;
	middlePanelContext_.scrollOffsetY = 0.0f;
	middlePanelContext_.orthoLeft = -1.0f;
	middlePanelContext_.orthoRight = 1.0f;
	middlePanelContext_.orthoBottom = -1.0f;
	middlePanelContext_.orthoTop = 1.0f;

	focusedGameObject_ = nullptr;
}

#include "UITextElement.hpp"

void Editor::editorDraw() const {
	assetPanel_.draw();
	scenePanel_.draw();
	hierarchy_.draw();
	inspector_.draw();
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(
		middlePanelContext_.orthoLeft / editorZoomFactor_,
		middlePanelContext_.orthoRight / editorZoomFactor_,
		middlePanelContext_.orthoBottom / editorZoomFactor_,
		middlePanelContext_.orthoTop / editorZoomFactor_,
		-1.0,
		1.0
	);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glViewport(
		middlePanelContext_.viewportX,
		middlePanelContext_.viewportY,
		middlePanelContext_.viewportWidth,
		middlePanelContext_.viewportHeight
	);
	glTranslatef(-editorX_, -editorY_, 0);

	scene_->sceneDraw();

	if (focusedGameObject_) {
		Transform2D transform = focusedGameObject_->getWorldTransform();

		// If I add a hierarchy to UIElements in general change this type to that but this works.
		if (dynamic_cast<UITextElement*>(focusedGameObject_)) {
			transform = focusedGameObject_->getLocalTransform();

			GLint viewport[4];
			glGetIntegerv(GL_VIEWPORT, viewport);
			int vw = viewport[2];
			int vh = viewport[3];

			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();
			glOrtho(0, vw, 0, vh, -1.0, 1.0);

			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();

			float px = (transform.position.x + 1.0f) * 0.5f * vw;
			float py = (transform.position.y + 1.0f) * 0.5f * vh;

			float sx = transform.scale.x * 0.5f * vw;
			float sy = transform.scale.y * 0.5f * vh;

			Vector2D p = { px, py };

			float lengthX = px + (vw * 0.125f);
			float sizeX = (vw * 0.0075f);
			float lengthY = py + (vh * 0.125f);
			float sizeY = (vh * 0.0075f);

			// X
			drawLine(
				p,
				{ lengthX, py },
				{ 1,0,0 }, { 1,0,0 }
			);
			drawTriangle(
				{ lengthX, py },
				sizeX,
				270.0f,
				false,
				false,
				{ 1,0,0 },
				{ 1,0,0 },
				{ 1,0,0 }
			);
			// Y
			drawLine(
				p,
				{ px, lengthY },
				{ 0,1,0 },
				{ 0,1,0 }
			);
			drawTriangle(
				{ px, lengthY },
				sizeY,
				0.0f,
				false,
				false,
				{ 0,1,0 },
				{ 0,1,0 },
				{ 0,1,0 }
			);

			glPopMatrix();
			glMatrixMode(GL_PROJECTION);
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
		}
		else {

			// X
			drawLine(
				transform.position,
				{ transform.position.x + 0.25f, transform.position.y },
				{ 1,0,0 }, { 1,0,0 }
			);
			drawTriangle(
				{ transform.position.x + 0.25f, transform.position.y },
				0.015f,
				270.0f,
				false,
				false,
				{ 1,0,0 },
				{ 1,0,0 },
				{ 1,0,0 }
			);
			// Y
			drawLine(
				transform.position,
				{ transform.position.x, transform.position.y + 0.25f },
				{ 0,1,0 },
				{ 0,1,0 }
			);
			drawTriangle(
				{ transform.position.x, transform.position.y + 0.25f },
				0.015f,
				0.0f,
				false,
				false,
				{ 0,1,0 },
				{ 0,1,0 },
				{ 0,1,0 }
			);
		}
	}

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	topPanel_.draw();
}

void Editor::editorUpdate() {
	if (isInsideViewportContext(InputManager::getInstance().mouseX(), InputManager::getInstance().mouseY(), middlePanelContext_)) {
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
		if (focusedGameObject_) {
			if (InputManager::getInstance().isPressed('m')) {
				Transform2D transform = focusedGameObject_->getWorldTransform();
				editorX_ = transform.position.x;
				editorY_ = transform.position.y;
			}
		}
		if (InputManager::getInstance().isPressed('z')) {
			editorZoomFactor_ = 1.0f;
		}
		if (InputManager::getInstance().isPressed('r')) {
			editorX_ = 0.0f;
			editorY_ = 0.0f;
		}
	}

	// Only update for topPanel if either drop down is active
	if (topPanel_.helpDropActive() || topPanel_.menuDropActive()) {
		topPanel_.update();
	} 
	else {
		// Run this before hierarchy_ because it adds to rootObjects.
		assetPanel_.update();
		
		topPanel_.update();

		// Part of editor responsible for keeping track of rootObjects and focusing objects
		hierarchy_.update();

		// Run this after hierarchy_ runs. BECAUSE inspector_ will actually do stuff to this pointer. And if its stale thats bad.
		if (focusedGameObject_ != hierarchy_.focusedGameObject()) {
			focusedGameObject_ = hierarchy_.focusedGameObject();
			std::cout << "Editor::editorUpdate() : Focused onto " << focusedGameObject_ << std::endl;
			inspector_.setFocusedGameObject(focusedGameObject_);
		}

		// Inspector can delete objects and such and should run last because it imperative it has updated state of pointers
		inspector_.update();

		if (inspector_.isFocusedGameObjectMarkedForErasure()) {
			std::cout << "Editor::editorUpdate() : Editor erasing focusedGameObject" << std::endl;
			std::vector<std::unique_ptr<GameObject2D>>& rootObjects_ = scene_->getRootObjects();
			for (auto it = rootObjects_.begin(); it != rootObjects_.end();) {
				GameObject2D* rO = it->get();

				if (rO == focusedGameObject_) {
					hierarchy_.setFocusedGameObject(nullptr);
					inspector_.setFocusedGameObject(nullptr);
					focusedGameObject_ = nullptr;
					it = rootObjects_.erase(it);
				}
				else {
					++it;
				}
			}
		}
		scenePanel_.update();
	}
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
	std::cout << "Editor::exitEditor() : Exiting editor mode " << std::endl;

	inEditor_ = false; 	
	if (!scene_->isPauseFlagged()) {
		SoundManager::getInstance().unpauseAll();
	}
}