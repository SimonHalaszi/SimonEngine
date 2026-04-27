#include "Camera.hpp"

Camera::Camera(const Transform2D& transform2D) {
	localTransform_ = transform2D;
	name_ = "Camera";
	tag_ = "Camera";
}

void Camera::update() {
	if (Game::getInstance().getCurrentScene()->isPauseFlagged()) {
		return;
	}

	Transform2D transform = getWorldTransform();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-transform.position.x, -transform.position.y, 0);
}