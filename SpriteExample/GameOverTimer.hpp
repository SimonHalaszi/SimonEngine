#ifndef GAME_OVER_TIMER_HPP
#define GAME_OVER_TIMER_HPP

#include <string>

#include "UITextElement.hpp"
#include "Utilities.hpp"

class GameOverTimer : public UITextElement {
	public:
		GameOverTimer(Transform2D transform2D, std::string text, ColorRGB textColor, ColorRGB rectangleColor) :
			UITextElement(transform2D, text, textColor, rectangleColor) {
		}

		void onStart() override;
		void update() override;
		void onDestruction() override {}

		static bool isGameOver() { return isGameOver_; }
		static std::string getTimeLeft() { return timeLeft_; }
	private:
		
		float countdownTime_ = 60.0f;
		int countdownTimeInUpdateFrames_ = 0;
		int countdownFrame_ = 0;
		static bool isGameOver_;

		static std::string timeLeft_;
};

#endif