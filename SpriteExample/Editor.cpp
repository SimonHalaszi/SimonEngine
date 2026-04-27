#include "Editor.hpp"

#include <iostream>

#include "AssetFactory.hpp"
#include "CollisionObject2D.hpp"
#include "UIElement.hpp"
#include "EditorSaveLoad.hpp"

Editor::Editor(Scene* scene)
	: scene_(scene), hierarchy_(scene->getRootObjects()), assetPanel_(scene), topPanel_([this]() { saveEditorState(); }, [this]() { loadEditorState(); }) {
	std::cout << "Editor::Editor() : Editor created " << std::endl;

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
	saveName_ = scene->getSaveName();
}

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
		if (dynamic_cast<UIElement*>(focusedGameObject_)) {
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
			if (editorZoomFactor_ > 0.10f) {
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
			editorZoomFactor_ = 1.0f;
		}
	}

	// Only update for topPanel if either drop down is active
	if (topPanel_.helpDropActive() || topPanel_.menuDropActive()) {
		topPanel_.update();
	}
	else {
		// Run this before hierarchy_ because it adds to rootObjects.
		assetPanel_.update(
			hierarchy_.getActiveHierarchyVector(),
			hierarchy_.getParentOfCurrentView(),
			[this](int assetButtonIndex, GameObject2D* parentObject) {
				recordCreateAction(assetButtonIndex, parentObject);
			}
		);

		topPanel_.update();

		// Part of editor responsible for keeping track of rootObjects and focusing objects
		hierarchy_.update(
			[this](GameObject2D* object) {
				recordDeleteAction(object);
			},
			[this](GameObject2D* parentObject, int fromIndex, int toIndex) {
				recordReorderAction(parentObject, fromIndex, toIndex);
			}
		);

		// Run this after hierarchy_ runs. BECAUSE inspector_ will actually do stuff to this pointer. And if its stale thats bad.
		if (focusedGameObject_ != hierarchy_.focusedGameObject()) {
			focusedGameObject_ = hierarchy_.focusedGameObject();
			std::cout << "Editor::editorUpdate() : Focused onto " << focusedGameObject_ << std::endl;
			inspector_.setFocusedGameObject(focusedGameObject_);
		}

		// Inspector can delete objects and such and should run last because it imperative it has updated state of pointers
		inspector_.update([this](GameObject2D* object) {
			recordSnapshotAction(object);
		});
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
	canSave_ = false;
	if (!scene_->isPauseFlagged()) {
		SoundManager::getInstance().unpauseAll();
	}
}

// Resets panels to the default view
void Editor::resetPanelsToDefaultView() {
	focusedGameObject_ = nullptr;
	hierarchy_.resetToRoot();
	inspector_.clearFocus();
	assetPanel_ = AssetPanel(scene_);
	scenePanel_ = ScenePanel();
}

// Create Action - Asset Panel
void Editor::recordCreateAction(int assetButtonIndex, GameObject2D* parentObject) {
	if (!canSave_) {
		return;
	}

	EditorSavedAction action;
	action.type = EditorSavedActionType::Create;
	action.parentPath = buildObjectPath(scene_, parentObject);
	action.assetButtonIndex = assetButtonIndex;
	saveActions_.push_back(action);
}

// Delete Action - Hierarchy Panel
void Editor::recordDeleteAction(GameObject2D* object) {
	if (!canSave_ || !object) {
		return;
	}

	EditorSavedAction action;
	action.type = EditorSavedActionType::Delete;
	action.objectPath = buildObjectPath(scene_, object);
	if (!action.objectPath.empty()) {
		saveActions_.push_back(action);
	}
}

// Reorder Action - Hierarchy Panel
void Editor::recordReorderAction(GameObject2D* parentObject, int fromIndex, int toIndex) {
	if (!canSave_) {
		return;
	}

	EditorSavedAction action;
	action.type = EditorSavedActionType::Reorder;
	action.parentPath = buildObjectPath(scene_, parentObject);
	action.fromIndex = fromIndex;
	action.toIndex = toIndex;
	saveActions_.push_back(action);
}

// Snapshot Action - Inspector Panel
void Editor::recordSnapshotAction(GameObject2D* object) {
	if (!canSave_ || !object) {
		return;
	}

	EditorSavedAction action;
	action.type = EditorSavedActionType::Snapshot;
	action.objectPath = buildObjectPath(scene_, object);
	action.fieldValues = saveIFields(object);
	if (!action.objectPath.empty()) {
		saveActions_.push_back(action);
	}
}

// Save and Load Actions - Top Panel, passed in at initialization
void Editor::saveEditorState() {
	if (!canSave_) {
		std::cout << "Editor::saveEditorState() : Save unavailable after leaving editor mode. Load or reset the scene to establish a new editor state." << std::endl;
		return;
	}

	saveEditorActionsToFile(saveName_, saveActions_);
}

void Editor::loadEditorState() {
	if (!scene_) {
		return;
	}

	const std::vector<EditorSavedAction> previousActions = saveActions_;

	std::vector<EditorSavedAction> loadedActions;
	if (!loadEditorActionsFromFile(saveName_, loadedActions)) {
		return;
	}

	scene_->sceneDeInit();
	scene_->sceneInit();
	resetPanelsToDefaultView();

	if (!replayEditorActions(scene_, loadedActions)) {
		std::cout << "Editor::loadEditorState() : Failed to replay actions from save file" << std::endl;

		// Loaded replay may have partially mutated the scene. Rebuild before rollback.
		scene_->sceneDeInit();
		scene_->sceneInit();
		resetPanelsToDefaultView();

		if (!replayEditorActions(scene_, previousActions)) {
			std::cout << "Editor::loadEditorState() : Failed to restore previous editor state after load failure" << std::endl;
		}
		else {
			std::cout << "Editor::loadEditorState() : Restored previous editor state" << std::endl;
		}
		return;
	}

	saveActions_ = loadedActions;
	std::cout << "Editor::loadEditorState() : Loaded " << saveActions_.size() << " editor actions from save " << saveName_ << std::endl;
}