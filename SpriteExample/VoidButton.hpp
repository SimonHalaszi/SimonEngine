#ifndef VOID_BUTTON_HPP
#define VOID_BUTTON_HPP

#include <string>
#include <functional>

#include "utilities.hpp"
#include "drawFunctions.hpp"
#include "InputManager.hpp"

class VoidButton {
	public:
		VoidButton();
		VoidButton(
			WindowArea windowArea,
			ViewportArea viewportArea,
			ColorRGB color,
			std::string text,
			std::function<void()> buttonAction
		);

		bool isInside(int mouseX, int mouseY) const;
		void handleClick() const;
		bool isClicked() const { return clicked_; }
		void draw() const;

	private:
		WindowArea windowArea_;
		ViewportArea viewportArea_;
		ColorRGB color_;
		std::string text_;
		bool clicked_;
		std::function<void()> buttonAction_;
};

#endif