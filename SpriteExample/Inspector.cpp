#include "Inspector.hpp"
#include "CollisionObject2D.hpp"

Inspector::Inspector()
	: focusedGameObject_(nullptr) {
	
	inspectorTitle_.pos = { 0.0f, 1.0f - (1.0f / 16.0f) };
	inspectorTitle_.scale = { 1.0f, 1.0f / 16.0f };

	inspectorContext_.viewportX = HIERARCHY_PANEL_W + SCENE_WIN_W;
	inspectorContext_.viewportY = OBJECTS_PANEL_H;
	inspectorContext_.viewportWidth = INSPECTOR_PANEL_W;
	inspectorContext_.viewportHeight = INSPECTOR_PANEL_H;
	inspectorContext_.scrollOffsetX = 0.0f;
	inspectorContext_.scrollOffsetY = 0.0f;
	inspectorContext_.orthoLeft = -1.0f;
	inspectorContext_.orthoRight = 1.0f;
	inspectorContext_.orthoBottom = -1.0f;
	inspectorContext_.orthoTop = 1.0f;

	iFieldButtons_.clear();
	iFields_ = nullptr;
}

void Inspector::draw() const {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glViewport(HIERARCHY_PANEL_W + SCENE_WIN_W, OBJECTS_PANEL_H, INSPECTOR_PANEL_W, INSPECTOR_PANEL_H);

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
	glTranslatef(0, -inspectorContext_.scrollOffsetY, 0);

	for (auto& button : iFieldButtons_) {
		button->draw();
	}

	glPopMatrix();

	// Draw Title
	drawRectangle(
		inspectorTitle_.pos,
		inspectorTitle_.scale,
		0.0f,
		false,
		false,
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f }
	);
	drawText(
		{ inspectorTitle_.pos.x - inspectorTitle_.scale.x, inspectorTitle_.pos.y },
		"Inspector",
		0.0f,
		{ 1.0f, 1.0f, 1.0f }
	);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void Inspector::setFocusedGameObject(GameObject2D* focusedGameObject) {
	iFieldButtons_.clear();
	focusedGameObject_ = focusedGameObject;
	if (focusedGameObject_) {
		iFields_ = focusedGameObject_->getIFields();
		establishIFieldButtons();
	}
	else {
		iFields_ = nullptr;
	}
}

void Inspector::establishIFieldButtons() {
	float layerHeight = 1.0f / 16.0f;
	float topCursor = inspectorTitle_.pos.y - inspectorTitle_.scale.y;
	int i = 0;

	ColorRGB color = { 1.0f, 1.0f, 1.0f };

	for (auto itr = iFields_->begin(); itr != iFields_->end(); ++itr) {
		IField* rawField = itr->get();

		if (auto* f = dynamic_cast<Transform2DField*>(rawField)) {
			float halfHeight = 15.0f * layerHeight;
			ViewportArea area = { { 0.0f, topCursor - halfHeight }, { 1.0f, halfHeight } };
			iFieldButtons_.push_back(std::make_unique<Transform2DIFieldButton>(area, color, f->getName(), f));
			topCursor -= halfHeight * 2.0f;
		}
		else if (auto* f = dynamic_cast<Vector2DField*>(rawField)) {
			float halfHeight = 5.0f * layerHeight;
			ViewportArea area = { { 0.0f, topCursor - halfHeight }, { 1.0f, halfHeight } };
			iFieldButtons_.push_back(std::make_unique<Vector2DIFieldButton>(area, color, f->getName(), f));
			topCursor -= halfHeight * 2.0f;
		}
		else if (auto* f = dynamic_cast<BoolField*>(rawField)) {
			float halfHeight = 1.0f * layerHeight;
			ViewportArea area = { { 0.0f, topCursor - halfHeight }, { 1.0f, halfHeight } };
			iFieldButtons_.push_back(std::make_unique<BoolIFieldButton>(area, color, f->getName(), f));
			topCursor -= halfHeight * 2.0f;
		}
		else if (auto* f = dynamic_cast<IntField*>(rawField)) {
			float halfHeight = 2.0f * layerHeight;
			ViewportArea area = { { 0.0f, topCursor - halfHeight }, { 1.0f, halfHeight } };
			iFieldButtons_.push_back(std::make_unique<IntIFieldButton>(area, color, f->getName(), f));
			topCursor -= halfHeight * 2.0f;
		}
		else if (auto* f = dynamic_cast<CharField*>(rawField)) {
			float halfHeight = 2.0f * layerHeight;
			ViewportArea area = { { 0.0f, topCursor - halfHeight }, { 1.0f, halfHeight } };
			iFieldButtons_.push_back(std::make_unique<CharIFieldButton>(area, color, f->getName(), f));
			topCursor -= halfHeight * 2.0f;
		}
		else if (auto* f = dynamic_cast<FloatField*>(rawField)) {
			float halfHeight = 2.0f * layerHeight;
			ViewportArea area = { { 0.0f, topCursor - halfHeight }, { 1.0f, halfHeight } };
			iFieldButtons_.push_back(std::make_unique<FloatIFieldButton>(area, color, f->getName(), f));
			topCursor -= halfHeight * 2.0f;
		}
		else if (auto* f = dynamic_cast<StringField*>(rawField)) {
			float halfHeight = 2.0f * layerHeight;
			ViewportArea area = { { 0.0f, topCursor - halfHeight }, { 1.0f, halfHeight } };
			iFieldButtons_.push_back(std::make_unique<StringIFieldButton>(area, color, f->getName(), f));
			topCursor -= halfHeight * 2.0f;
		}
		++i;
	}
}

void Inspector::update() {
	// Dont bother doing input if we arent in hierarchy panel
	if (isInsideViewportContext(InputManager::getInstance().mouseX(), InputManager::getInstance().mouseY(), inspectorContext_)) {
		float scrollSpeed = 0.1f;

		if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_SCROLLDOWN)) {
			inspectorContext_.scrollOffsetY -= scrollSpeed;
		}
		if (InputManager::getInstance().isMouseButtonPressed(MOUSEBUTTON_SCROLLUP)) {
			inspectorContext_.scrollOffsetY += scrollSpeed;
		}

		if (inspectorContext_.scrollOffsetY > 0.0f) {
			inspectorContext_.scrollOffsetY = 0.0f;
		}

		bool result, gotPositive;
		result = false;
		gotPositive = false;
		for (auto& button : iFieldButtons_) {
			result = button->handleClick(inspectorContext_);
			if (result) {
				gotPositive = true;
			}
		}
		// If handleClick actually did something that changed something updateWorldTransform
		if (gotPositive) {
			focusedGameObject_->updateWorldTransform();

			// Cascade collision enabled state down to children
			CollisionObject2D* collider = dynamic_cast<CollisionObject2D*>(focusedGameObject_);
			if (collider) {
				collider->setCollisionEnabled(collider->isCollisionEnabled());
			}
		}

		const std::string& typedChars = InputManager::getInstance().getTypedChars();
		if (!typedChars.empty()) {
			for (auto& button : iFieldButtons_) {
				button->handleKeyInput(typedChars);
			}
		}
	}
}

Inspector::~Inspector() {
	focusedGameObject_ = nullptr;
}