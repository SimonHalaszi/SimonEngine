#include "CameraAndUI.hpp"

#include "Axis.hpp"
#include "CoinDisplay.hpp"
#include "FinishLinePopUpDisplay.hpp"
#include "GameOverTimer.hpp"
#include "PauseDisplay.hpp"

CameraAndUI::CameraAndUI(Transform2D transform2D) {
	localTransform_ = transform2D;
	tag_ = "Camera";
}

void CameraAndUI::onStart() {
	attachChild(std::make_unique<Axis>(
			Transform2D({ Vector2D({ 0.0f, 0.0f }),
			Vector2D({ 0.0f, 0.0f }),
			0.0f,
			false,
			false, }),
			ColorRGB({ 1.0f, 0.0f, 0.0f }),
			ColorRGB({ 1.0f, 0.0f, 0.0f }),
			false,
			'x'
		)
	);
	attachChild(std::make_unique<Axis>(
			Transform2D({ Vector2D({ 0.0f, 0.0f }),
			Vector2D({ 0.0f, 0.0f }),
			0.0f,
			false,
			false, }),
			ColorRGB({ 0.0f, 1.0f, 0.0f }),
			ColorRGB({ 0.0f, 1.0f, 0.0f }),
			false,
			'y'
		)
	);
	attachChild(std::make_unique<CoinDisplay>(
		Transform2D({ Vector2D({ 0.75f, 0.9f }),
			Vector2D({ 0.15f, 0.05f }),
			0.0f,
			false,
			false, }),
		"0",
		ColorRGB{ 1.0f, 1.0f, 1.0f },
		ColorRGB{ 0.0f, 0.0f, 0.0f }
	)
	);
	attachChild(std::make_unique<GameOverTimer>(
		Transform2D({ Vector2D({ -0.75f, 0.9f }),
			Vector2D({ 0.15f, 0.05f }),
			0.0f,
			false,
			false, }),
		"0",
		ColorRGB{ 1.0f, 1.0f, 1.0f },
		ColorRGB{ 0.0f, 0.0f, 0.0f }
	)
	);
	attachChild(std::make_unique<FinishLinePopUpDisplay>(
		Transform2D({ Vector2D({ 0.0f, -0.9f }),
			Vector2D({ 0.50f, 0.05f }),
			0.0f,
			false,
			false, }),
		"Get all of the coins! Theres 5!",
		ColorRGB{ 1.0f, 1.0f, 1.0f },
		ColorRGB{ 0.0f, 0.0f, 0.0f }
	)
	);
	attachChild(std::make_unique<PauseDisplay>(
		Transform2D({ Vector2D({ 0.0f, 0.9f }),
			Vector2D({ 0.40f, 0.05f }),
			0.0f,
			false,
			false, }),
		"Scene Paused",
		ColorRGB{ 1.0f, 1.0f, 1.0f },
		ColorRGB{ 0.0f, 0.0f, 0.0f }
	)
	);
}


void CameraAndUI::update() {
	if (Game::getInstance().getCurrentScene()->isPauseFlagged()) {
		return;
	}

	Transform2D transform = getWorldTransform();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-transform.position.x, -transform.position.y, 0);
}