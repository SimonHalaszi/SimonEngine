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

	// Draw Background
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
		establishHierarchyButtons();
		lastKnownSizeOfRootObjects_ = rootObjects_.size();
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
			if (focusIndex != -1) {
				focusedGameObject_ = rootObjects_[focusIndex].get();
				focusedGameObjectIndex_ = focusIndex;
				std::cout << "Hierarchy::update() : Focused onto GameObject at " << focusedGameObject_ << std::endl;
			}
			else {
				focusedGameObject_ = nullptr;
				focusedGameObjectIndex_ = focusIndex;
				std::cout << "Hierarchy::update() : Focused onto " << focusedGameObject_ << std::endl;
			}
		}
	}
}

void Hierarchy::establishHierarchyButtons() {
	focusedGameObject_ = nullptr;
	focusedGameObjectIndex_ = -1;

	hierarchyButtons_.clear();
	
	float areaOffset = ((1.0f / 16.0f) * 2);
	ViewportArea startArea = hierarchyTitle_;
	startArea.pos.y -= areaOffset;
	int i = 0;

	ColorRGB color1 = { 1.0f, 1.0f, 1.0f };
	ColorRGB color2 = { 0.8f, 0.8f, 0.8f };

	for (auto itr = rootObjects_.begin(); itr != rootObjects_.end(); ++itr) {
		if (i % 2) {
			hierarchyButtons_.push_back(
				HierarchyButton(
					startArea,
					color1,
					itr->get()->getName(),
					i
				)
			);
		}
		else {
			hierarchyButtons_.push_back(
				HierarchyButton(
					startArea,
					color2,
					itr->get()->getName(),
					i
				)
			);
		}
		startArea.pos.y -= areaOffset;
		++i;
	}
}

Hierarchy::~Hierarchy() {
	focusedGameObject_ = nullptr;
}