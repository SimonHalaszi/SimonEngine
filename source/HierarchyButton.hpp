#ifndef HIERARCHY_BUTTON_HPP
#define HIERARCHY_BUTTON_HPP

#include <string>
#include <functional>

#include "Utilities.hpp"
#include "DrawFunctions.hpp"
#include "InputManager.hpp"
#include "WindowConstants.hpp"

class HierarchyButton {
public:
	HierarchyButton();
	HierarchyButton(
		ViewportArea viewportArea,
		ColorRGB color,
		std::string text,
		int index
	);

	bool isInside(int mouseX, int mouseY, const ViewportContext& context) const;
	int handleClick(const ViewportContext& context) const;
	void draw() const;
	std::string getText() const { return text_; }
	void setText(const std::string& text) { text_ = text; }
	void setColor(const ColorRGB color) { color_ = color; }

	int returnAssocaitedIndex() const { return associatedObjectIndex_; }

private:
	ViewportArea viewportArea_;
	ColorRGB color_;
	std::string text_;

	int associatedObjectIndex_;
};

#endif