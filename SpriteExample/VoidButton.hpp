#ifndef VOID_BUTTON_HPP
#define VOID_BUTTON_HPP

#include <string>
#include <functional>

#include "utilities.hpp"
#include "drawFunctions.hpp"
#include "InputManager.hpp"
#include "WindowConstants.hpp"

class VoidButton {
public:
	VoidButton();
	VoidButton(
		ViewportArea viewportArea,
		ColorRGB color,
		std::string text,
		std::function<void()> buttonAction
	);

	bool isInside(int mouseX, int mouseY, const ViewportContext& context) const;
	void handleClick(const ViewportContext& context) const;
	void draw() const;

private:
	ViewportArea viewportArea_;
	ColorRGB color_;
	std::string text_;
	std::function<void()> buttonAction_;
};

#endif