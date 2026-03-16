#ifndef PAUSE_DISPLAY_HPP
#define PAUSE_DISPLAY_HPP

#include <string>

#include "UITextElement.hpp"
#include "utilities.hpp"

class PauseDisplay : public UITextElement {
	public:
		PauseDisplay(Transform2D transform2D, std::string text, ColorRGB textColor, ColorRGB rectangleColor) :
			UITextElement(transform2D, text, textColor, rectangleColor) {
		}

		void onStart() override;
		void update() override;
		void onDestruction() override {}
};

#endif