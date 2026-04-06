#ifndef HIERARCHY_BUTTON_HPP
#define HIERARCHY_BUTTON_HPP

#include <string>
#include <functional>

#include "utilities.hpp"
#include "drawFunctions.hpp"
#include "GameObject2D.hpp"
#include "InputManager.hpp"

class HierarchyButton {
public:
	HierarchyButton();
	HierarchyButton(
		WindowArea windowArea,
		ViewportArea viewportArea,
		ColorRGB color,
		std::string text,
		std::function<void()> buttonAction
	);

	bool isInside(int mouseX, int mouseY) const;
	GameObject2D* handleClick() const;
	bool isClicked() const { return clicked_; }
	void draw() const;

private:
	WindowArea windowArea_;
	ViewportArea viewportArea_;
	ColorRGB color_;
	std::string text_;
	bool clicked_;
	GameObject2D* associatedObject_;
};

#endif