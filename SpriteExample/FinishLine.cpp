#include "FinishLine.hpp"

#include "PlatformerPlayer.hpp"

bool FinishLine::isPopupShowing_ = false;
bool FinishLine::isGameCompleted_ = false;

FinishLine::FinishLine(Transform2D transform2D, std::string spriteKey) {
	localTransform_ = transform2D;
	finishLineSprite_ = nullptr;
	finishLineSpriteKey_ = spriteKey;
	gameWonSoundFilepath_ = "audio/GameWon.mp3";
}

void FinishLine::onStart() {
	finishLineSprite_ = &(SpriteRegistry::getInstance().getSprite(finishLineSpriteKey_));
	popupTimeInUpdateFrames_ = popupTime_ * float(Game::getInstance().getCurrentScene()->getUpdateSpeed());
	sceneChangeDelayTimeInUpdateFrames_ = sceneChangeDelayTime_ * float(Game::getInstance().getCurrentScene()->getUpdateSpeed());

	isPopupShowing_ = false;
	isGameCompleted_ = false;
}

void FinishLine::draw() {
	Transform2D transform = getWorldTransform();

	drawSprite(
		transform.position,
		transform.scale, transform.rotation,
		transform.mirror, transform.flip,
		*finishLineSprite_
	);
}

#include "GameWonScreenScene.hpp"

void FinishLine::update() {
	if (Game::getInstance().getCurrentScene()->isPauseFlagged()) {
		return;
	}

	if (isPopupShowing_) {
		++popupFrame_;
		if (popupFrame_ >= popupTimeInUpdateFrames_) {
			isPopupShowing_ = false;
			popupFrame_ = 0;
		}
	}

	if (isGameCompleted_) {
		++sceneChangeDelayFrame_;
		if (sceneChangeDelayFrame_ >= sceneChangeDelayTimeInUpdateFrames_) {
			Game::getInstance().changeScene(std::make_unique<GameWonScreenScene>());
		}
	}
}

void FinishLine::onDestruction() {}

void FinishLine::onCollision(CollisionObject2D& other) {
	if (Game::getInstance().getCurrentScene()->isPauseFlagged()) {
		return;
	}

	if (other.getTag() == "Player") {
		if (!isPopupShowing_ && PlatformerPlayer::getCoinCount() < 5) {
			isPopupShowing_ = true;
		}
		else if (PlatformerPlayer::getCoinCount() == 5) {
			if (!isGameCompleted_) {
				SoundManager::getInstance().playSound2D(gameWonSoundFilepath_);
			}
			isGameCompleted_ = true;
		}
	}
}