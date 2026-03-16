#ifndef FINISH_LINE_POPUP_DISPLAY_HPP
#define FINISH_LINE_POPUP_DISPLAY_HPP

#include <string>

#include "UITextElement.hpp"
#include "utilities.hpp"

class FinishLinePopUpDisplay : public UITextElement {
	public:
		FinishLinePopUpDisplay(Transform2D transform2D, std::string text, ColorRGB textColor, ColorRGB rectangleColor) :
			UITextElement(transform2D, text, textColor, rectangleColor) {
		}

		void onStart() override;
		void update() override;
		void onDestruction() override {}
};

#endif