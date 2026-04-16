#include "Hierarchy.hpp"

Hierarchy::Hierarchy(std::vector<std::unique_ptr<GameObject2D>>* rootObjects)
	: hierarchyObjects_(rootObjects), rootObjects_(rootObjects), focusedGameObject_(nullptr), gameObjectSpecificView_(false), hierarchyY_(0), parentOfCurrentView_(nullptr)
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

	lastKnownSizeOfHierarchyObjects_ = hierarchyObjects_->size();
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
	if (lastKnownSizeOfHierarchyObjects_ != hierarchyObjects_->size()) {
		focusedGameObject_ = nullptr;
		focusedGameObjectIndex_ = -1;
		hierarchyButtons_.clear();
		establishHierarchyButtons();
		lastKnownSizeOfHierarchyObjects_ = hierarchyObjects_->size();
	}

	if (focusedGameObjectIndex_ != -1) {
		std::string objectName = (*hierarchyObjects_)[focusedGameObjectIndex_].get()->getName();
		std::string buttonText = hierarchyButtons_[focusedGameObjectIndex_].getText();
		if (objectName != buttonText) {
			hierarchyButtons_[focusedGameObjectIndex_].setText(objectName);
		}
	}

	if (InputManager::getInstance().isSpecialKeyPressed(mapSpecialKey(GLUT_KEY_F5))) {
		std::cout << " Hierarchy::update() : Inspector marked focusedGameObject for erasure" << std::endl;
		for (auto it = hierarchyObjects_->begin(); it != hierarchyObjects_->end();) {
			GameObject2D* rO = it->get();

			if (rO == focusedGameObject_) {
				focusedGameObject_ = nullptr;
				it = hierarchyObjects_->erase(it);
				break;
			}
			else {
				++it;
			}
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
				std::swap((*hierarchyObjects_)[focusedGameObjectIndex_], (*hierarchyObjects_)[focusedGameObjectIndex_ - 1]);
				focusedGameObjectIndex_ -= 1;
				
				hierarchyButtons_.clear();
				establishHierarchyButtons();
			}
		}
		if (InputManager::getInstance().isSpecialKeyPressed(mapSpecialKey(GLUT_KEY_DOWN))) {
			if (focusedGameObjectIndex_ >= 0 && static_cast<size_t>(focusedGameObjectIndex_) + 1 < hierarchyObjects_->size()) {
				std::swap((*hierarchyObjects_)[focusedGameObjectIndex_], (*hierarchyObjects_)[focusedGameObjectIndex_ + 1]);
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
				if (focusedGameObjectIndex_ == focusIndex) {
					// Re-clicked the same GameObject, hierarchy into its children
					GameObject2D* selected = (*hierarchyObjects_)[focusIndex].get();
					parentOfCurrentView_ = selected;
					hierarchyObjects_ = selected->getChildren();
					focusedGameObject_ = nullptr;
					focusedGameObjectIndex_ = -1;
					hierarchyButtons_.clear();
					establishHierarchyButtons();
					lastKnownSizeOfHierarchyObjects_ = hierarchyObjects_->size();
					std::cout << "Hierarchy::update() : Drilling into children of " << selected->getName() << std::endl;
					hierarchyContext_.scrollOffsetY = 0.0f;
					hierarchyContext_.scrollOffsetX = 0.0f;
				}
				else {
					if (focusedGameObjectIndex_ >= 0 && focusedGameObjectIndex_ < hierarchyButtons_.size()) {
						hierarchyButtons_[focusedGameObjectIndex_].setColor(colors[focusedGameObjectIndex_ % 2]);
					}
					focusedGameObject_ = (*hierarchyObjects_)[focusIndex].get();
					focusedGameObjectIndex_ = focusIndex;
					std::cout << "Hierarchy::update() : Focused onto GameObject at " << focusedGameObject_ << std::endl;
				}
			}
			else {
				if (hierarchyObjects_ != rootObjects_) {
					// Travel up using tracked parent
					if (parentOfCurrentView_ && parentOfCurrentView_->hasParent()) {
						parentOfCurrentView_ = parentOfCurrentView_->getParent();
						hierarchyObjects_ = parentOfCurrentView_->getChildren();
					}
					else {
						parentOfCurrentView_ = nullptr;
						hierarchyObjects_ = rootObjects_;
					}
					hierarchyButtons_.clear();
					establishHierarchyButtons();
					lastKnownSizeOfHierarchyObjects_ = hierarchyObjects_->size();
				}
				if (focusedGameObjectIndex_ >= 0 && focusedGameObjectIndex_ < hierarchyButtons_.size()) {
					hierarchyButtons_[focusedGameObjectIndex_].setColor(colors[focusedGameObjectIndex_ % 2]);
				}
				focusedGameObject_ = nullptr;
				focusedGameObjectIndex_ = -1;
				std::cout << "Hierarchy::update() : Unfocused, travelling up hierarchy" << std::endl;
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

	for (auto itr = hierarchyObjects_->begin(); itr != hierarchyObjects_->end(); ++itr) {
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