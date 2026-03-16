#include "GameOverTimer.hpp"

#include "Game.hpp"

bool GameOverTimer::isGameOver_ = false;
std::string GameOverTimer::timeLeft_ = "";

void GameOverTimer::onStart() {
	countdownTimeInUpdateFrames_ = countdownTime_ * float(Game::getInstance().getCurrentScene()->getUpdateSpeed());
	countdownFrame_ = countdownTimeInUpdateFrames_;
	timeLeft_ = std::to_string(countdownFrame_ / float(Game::getInstance().getCurrentScene()->getUpdateSpeed()));
	text_ = timeLeft_;

	isGameOver_ = false;
}

#include "GameOverScreenScene.hpp"
#include "FinishLine.hpp"

void GameOverTimer::update() {
	if (Game::getInstance().getCurrentScene()->isPauseFlagged()) {
		return;
	}

	if (!FinishLine::isGameCompleted()) {
		--countdownFrame_;
	}
	if (countdownFrame_ <= 0) {
		Game::getInstance().changeScene(std::make_unique<GameOverScreenScene>());
	}
	timeLeft_ = std::to_string(countdownFrame_ / float(Game::getInstance().getCurrentScene()->getUpdateSpeed()));
	text_ = timeLeft_;
}