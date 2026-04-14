#include "Inspector.hpp"

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
}

void Inspector::establishIFieldButtons() {
	ViewportArea startArea = inspectorTitle_;
	for (auto& field : *iFields_) {
		IField* rawField = field.get();
		IntField* intCheck = dynamic_cast<IntField*>(rawField);
		if (intCheck) {
			// create respective IFieldButton with field
			// startArea.pos.x += iFieldButtons_.back()->getViewportArea().scale.x + // layer height
			continue;
		}
		CharField* charCheck = dynamic_cast<CharField*>(rawField);
		if (charCheck) {
			// create respective IFieldButton with field
			// startArea.pos.x += iFieldButtons_.back()->getViewportArea().scale.x + // layer height
			continue;
		}
		FloatField* floatCheck = dynamic_cast<FloatField*>(rawField);
		if (floatCheck) {
			// create respective IFieldButton with field
			// startArea.pos.x += iFieldButtons_.back()->getViewportArea().scale.x + // layer height
			continue;
		}
		BoolField* boolCheck = dynamic_cast<BoolField*>(rawField);
		if (boolCheck) {
			// create respective IFieldButton with field
			// startArea.pos.x += iFieldButtons_.back()->getViewportArea().scale.x + // layer height
			continue;
		}
		StringField* stringCheck = dynamic_cast<StringField*>(rawField);
		if (stringCheck) {
			// create respective IFieldButton with field
			// startArea.pos.x += iFieldButtons_.back()->getViewportArea().scale.x + // layer height
			continue;
		}
		Vector2DField* vector2DCheck = dynamic_cast<Vector2DField*>(rawField);
		if (vector2DCheck) {
			// create respective IFieldButton with field
			// startArea.pos.x += iFieldButtons_.back()->getViewportArea().scale.x + // layer height
			continue;
		}
		Transform2DField* transform2DCheck = dynamic_cast<Transform2DField*>(rawField);
		if (transform2DCheck) {
			// create respective IFieldButton with field
			// startArea.pos.x += iFieldButtons_.back()->getViewportArea().scale.x + // layer height
			continue;
		}
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

		for (auto& button : iFieldButtons_) {
			button->handleClick(inspectorContext_);
		}
	}
}

Inspector::~Inspector() {
	focusedGameObject_ = nullptr;
}