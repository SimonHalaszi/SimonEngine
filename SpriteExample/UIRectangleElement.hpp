#ifndef UI_RECTANGLE_ELEMENT_HPP
#define UI_RECTANGLE_ELEMENT_HPP

#include <string>

#include "UIElement.hpp"

#include "DrawFunctions.hpp"
#include "Utilities.hpp"

// UI GameObjects will be drawn relative to camera space. So be smart when initializing their transform2D
class UIRectangleElement : public UIElement {
	public:
		UIRectangleElement(
			const Transform2D& transform2D,
			const std::string& tag,
			const std::string& name,
			const ColorRGB& rectangleColorTL,
			const ColorRGB& rectangleColorTR,
			const ColorRGB& rectangleColorBL,
			const ColorRGB& rectangleColorBR
		);

		void onStart() override {}
		void draw() override final;
		void update() override {}
		void onDestruction() override {}
		void establishFields() override {}

		void toggleDrawing() { drawElement_ = !drawElement_; }

	protected:
		ColorRGB rectangleColorTL_;
		ColorRGB rectangleColorTR_;
		ColorRGB rectangleColorBL_;
		ColorRGB rectangleColorBR_;

		bool drawElement_ = true;
};

#endif