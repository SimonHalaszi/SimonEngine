#include "ObjectsPanel.hpp"

ObjectsPanel::ObjectsPanel() {}

void ObjectsPanel::draw() const {
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glViewport(0, 0, OBJECTS_PANEL_W, OBJECTS_PANEL_H);

	drawRectangle(
		{ 0.0f, 0.0f },
		{ 1.0f, 1.0f },
		0.0f,
		false,
		false,
		{ 0.2f, 0.2f, 0.2f },
		{ 0.2f, 0.2f, 0.2f },
		{ 0.2f, 0.2f, 0.2f },
		{ 0.2f, 0.2f, 0.2f }
	);

	glPopMatrix();
}

void ObjectsPanel::update() {

}