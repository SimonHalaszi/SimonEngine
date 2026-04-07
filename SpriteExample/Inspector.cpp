#include "Inspector.hpp"

Inspector::Inspector()
	: focusedGameObject_(nullptr) {

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

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void Inspector::update() {

}

Inspector::~Inspector() {
	focusedGameObject_ = nullptr;
}