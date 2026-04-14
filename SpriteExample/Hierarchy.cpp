#include "Hierarchy.hpp"

Hierarchy::Hierarchy(std::vector<std::unique_ptr<GameObject2D>>& rootObjects)
	: rootObjects_(rootObjects), focusedGameObject_(nullptr), gameObjectSpecificView_(false), hierarchyY_(0)
{
	hierarchyTitle_.pos = { 0.0f, 1.0f - (1.0f / 16.0f) };
	hierarchyTitle_.scale = { 1.0f, 1.0f / 16.0f };

	hierarchyContext_.viewportX = 0;
	hierarchyContext_.viewportY = OBJECTS_PANEL_H;
	hierarchyContext_.viewportWidth = HIERARCHY_PANEL_W;
	hierarchyContext_.viewportHeight = HIERARCHY_PANEL_H;
	hierarchyContext_.scrollOffsetX = 0.0f;
	hierarchyContext_.scrollOffsetY = 0.0f;
	hierarchyContext_.orthoLeft = -1.0f;
	hierarchyContext_.orthoRight = 1.0f;
	hierarchyContext_.orthoBottom = -1.0f;
	hierarchyContext_.orthoTop = 1.0f;

	establishHierarchyButtons();

	lastKnownSizeOfRootObjects_ = rootObjects_.size();
	focusedGameObjectIndex_ = -1;
}

void Hierarchy::draw() const {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(
		hierarchyContext_.orthoLeft,
		hierarchyContext_.orthoRight,
		hierarchyContext_.orthoBottom,
		hierarchyContext_.orthoTop,
		-1.0,
		1.0
	);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glViewport(
		hierarchyContext_.viewportX,
		hierarchyContext_.viewportY,
		hierarchyContext_.viewportWidth,
		hierarchyContext_.viewportHeight
	);

	// Draw Background
	drawRectangle(
		{ 0.0f, 0.0f },
		{ 1.0f, 1.0f },
		0.0f,
		false,
		false,
		{ 0.5f, 0.5f, 0.5f },
		{ 0.5f, 0.5f, 0.5f },
		{ 0.5f, 0.5f, 0.5f },
		{ 0.5f, 0.5f, 0.5f }
	);

	glPushMatrix();
	glTranslatef(0, -hierarchyContext_.scrollOffsetY, 0);

	for (auto& button : hierarchyButtons_) {
		button.draw();
	}

	glPopMatrix();

	// Draw Title
	drawRectangle(
		hierarchyTitle_.pos,
		hierarchyTitle_.scale,
		0.0f,
		false,
		false,
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f }
	);
	drawText(
		{ hierarchyTitle_.pos.x - hierarchyTitle_.scale.x, hierarchyTitle_.pos.y },
		"Hierarchy",
		0.0f,
		{ 1.0f, 1.0f, 1.0f }
	);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void Hierarchy::update() {
	if (lastKnownSizeOfRootObjects_ != rootObjects_.size()) {
		focusedGameObject_ = nullptr;
		focusedGameObjectIndex_ = -1;
		hierarchyButtons_.clear();
		establishHierarchyButtons();
		lastKnownSizeOfRootObjects_ = rootObjects_.size();
	}

	if (focusedGameObjectIndex_ != -1) {
		std::string rootObjectName = rootObjects_[focusedGameObjectIndex_].get()->getName();
		std::string buttonText = hierarchyButtons_[focusedGameObjectIndex_].getText();
		if (rootObjectName != buttonText) {
			hierarchyButtons_[focusedGameObjectIndex_].setText(rootObjectName);
		}
	}

	// Dont bother doing input if we arent in hierarchy panel
	if (isInsideViewportContext(InputManager::getInstance().mouseX(), InputManager::getInstance().mouseY(), hierarchyContext_)) {
		float scrollSpeed = 0.1f;

		if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_SCROLLDOWN)) {
			hierarchyContext_.scrollOffsetY -= scrollSpeed;
		}
		if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_SCROLLUP)) {
			hierarchyContext_.scrollOffsetY += scrollSpeed;
		}
		if (InputManager::getInstance().isSpecialKeyPressed(mapSpecialKey(GLUT_KEY_UP))) {
			if (focusedGameObjectIndex_ > 0) {
				std::swap(rootObjects_[focusedGameObjectIndex_], rootObjects_[focusedGameObjectIndex_ - 1]);
				focusedGameObjectIndex_ -= 1;
				
				hierarchyButtons_.clear();
				establishHierarchyButtons();
			}
		}
		if (InputManager::getInstance().isSpecialKeyPressed(mapSpecialKey(GLUT_KEY_DOWN))) {
			if (focusedGameObjectIndex_ >= 0 && focusedGameObjectIndex_ < rootObjects_.size() - 1) {
				std::swap(rootObjects_[focusedGameObjectIndex_], rootObjects_[focusedGameObjectIndex_ + 1]);
				focusedGameObjectIndex_ += 1;
				
				hierarchyButtons_.clear();
				establishHierarchyButtons();
			}
		}

		if (hierarchyContext_.scrollOffsetY > 0.0f) {
			hierarchyContext_.scrollOffsetY = 0.0f;
		}

		// Handle Clicking
		if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_LEFT)) {
			int focusIndex = -1;
			for (auto& button : hierarchyButtons_) {
				focusIndex = button.handleClick(hierarchyContext_);
				if (focusIndex == -1) {
					continue;
				}
				else {
					break;
				}
			}

			ColorRGB color1 = { 1.0f, 1.0f, 1.0f };
			ColorRGB color2 = { 0.8f, 0.8f, 0.8f };
			ColorRGB colors[2] = { color1, color2 };

			if (focusIndex != -1) {
				if (focusedGameObjectIndex_ >= 0 && focusedGameObjectIndex_ < hierarchyButtons_.size()) {
					hierarchyButtons_[focusedGameObjectIndex_].setColor(colors[focusedGameObjectIndex_ % 2]);
				}
				focusedGameObject_ = rootObjects_[focusIndex].get();
				focusedGameObjectIndex_ = focusIndex;
				std::cout << "Hierarchy::update() : Focused onto GameObject at " << focusedGameObject_ << std::endl;
			}
			else {
				if (focusedGameObjectIndex_ >= 0 && focusedGameObjectIndex_ < hierarchyButtons_.size()) {
					hierarchyButtons_[focusedGameObjectIndex_].setColor(colors[focusedGameObjectIndex_ % 2]);
				}
				focusedGameObject_ = nullptr;
				focusedGameObjectIndex_ = focusIndex;
				std::cout << "Hierarchy::update() : Focused onto " << focusedGameObject_ << std::endl;
			}
		}
		if (focusedGameObjectIndex_ >= 0 && focusedGameObjectIndex_ < hierarchyButtons_.size()) {
			hierarchyButtons_[focusedGameObjectIndex_].setColor({ 0.1f, 0.9f, 0.1f });
		}
	}
}

void Hierarchy::establishHierarchyButtons() {
	float areaOffset = ((1.0f / 16.0f) * 2);
	ViewportArea startArea = hierarchyTitle_;
	startArea.pos.y -= areaOffset;
	int i = 0;

	ColorRGB color1 = { 1.0f, 1.0f, 1.0f };
	ColorRGB color2 = { 0.8f, 0.8f, 0.8f };
	ColorRGB colors[2] = { color1, color2 };

	for (auto itr = rootObjects_.begin(); itr != rootObjects_.end(); ++itr) {
		hierarchyButtons_.push_back(
			HierarchyButton(
				startArea,
				colors[i % 2],
				itr->get()->getName(),
				i
			)
		);
		startArea.pos.y -= areaOffset;
		++i;
	}
}

void Hierarchy::setFocusedGameObject(GameObject2D* focusedGameObject) {
	focusedGameObject_ = focusedGameObject;
}

Hierarchy::~Hierarchy() {
	focusedGameObject_ = nullptr;
}