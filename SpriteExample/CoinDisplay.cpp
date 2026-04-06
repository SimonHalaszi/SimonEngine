#include "CoinDisplay.hpp"

#include "PlatformerPlayer.hpp"

#include "Game.hpp"

void CoinDisplay::onStart() {
	text_ = std::to_string(PlatformerPlayer::getCoinCount());
	name_ = "CoinDisplay";
}

void CoinDisplay::update() {
	if (Game::getInstance().getCurrentScene()->isPauseFlagged()) {
		return;
	}

	text_ = std::to_string(PlatformerPlayer::getCoinCount());
}