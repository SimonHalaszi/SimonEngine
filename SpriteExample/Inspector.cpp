#include "Inspector.hpp"

Inspector::Inspector()
	: focusedGameObject_(nullptr) {

}

void Inspector::draw() const {
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

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

	glPopMatrix();
}

void Inspector::update() {

}

Inspector::~Inspector() {
	focusedGameObject_ = nullptr;
}