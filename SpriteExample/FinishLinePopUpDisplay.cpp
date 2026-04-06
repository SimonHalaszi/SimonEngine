#include "FinishLinePopUpDisplay.hpp"

#include "FinishLine.hpp"

void FinishLinePopUpDisplay::onStart() {
	drawElement_ = FinishLine::isPopupShowing();
	name_ = "FinishLinePopUpDisplay";
}

void FinishLinePopUpDisplay::update() {
	if (Game::getInstance().getCurrentScene()->isPauseFlagged()) {
		return;
	}

	drawElement_ = FinishLine::isPopupShowing();
}