#include "Hierarchy.hpp"

Hierarchy::Hierarchy(std::vector<std::unique_ptr<GameObject2D>>& rootObjects)
: rootObjects_(rootObjects), focusedGameObject_(nullptr), gameObjectSpecificView_(false) 
{}

void Hierarchy::draw() const {
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glViewport(0, OBJECTS_PANEL_H, HIERARCHY_PANEL_W, HIERARCHY_PANEL_H);

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

void Hierarchy::update() {

}

Hierarchy::~Hierarchy() {
	focusedGameObject_ = nullptr;
}