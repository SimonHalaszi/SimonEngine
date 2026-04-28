#include "Camera.hpp"

Camera::Camera(const Transform2D& localTransform) {
	localTransform_ = localTransform;
	name_ = "Camera";
	tag_ = "Camera";
}

void Camera::update() {
	if (Game::getInstance().isPauseFlagged()) {
		return;
	}

	const Transform2D& transform = getWorldTransform();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-transform.position.x, -transform.position.y, 0);
}