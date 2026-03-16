#include "CoinDisplay.hpp"

#include "PlatformerPlayer.hpp"

#include "Game.hpp"

void CoinDisplay::onStart() {
	text_ = std::to_string(PlatformerPlayer::getCoinCount());
}

void CoinDisplay::update() {
	if (Game::getInstance().getCurrentScene()->isPauseFlagged()) {
		return;
	}

	text_ = std::to_string(PlatformerPlayer::getCoinCount());
}