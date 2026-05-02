#ifndef UI_TEXT_ELEMENT_HPP
#define UI_TEXT_ELEMENT_HPP

#include <string>

#include "UIElement.hpp"

#include "DrawFunctions.hpp"
#include "Utilities.hpp"

// UI GameObjects will be drawn relative to camera space. So be smart when initializing their transform2D
class UITextElement : public UIElement {
	public:
		UITextElement() {}
		UITextElement(
			const Transform2D& transform2D,
			const std::string& tag,
			const std::string& name,
			const std::string& text,
			const ColorRGB& textColor,
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
	
	protected:
		std::string text_ = "";
		ColorRGB textColor_ = { 0.0f, 0.0f, 0.0f };
		ColorRGB rectangleColorTL_ = { 0.0f, 0.0f, 0.0f };
		ColorRGB rectangleColorTR_ = { 0.0f, 0.0f, 0.0f };
		ColorRGB rectangleColorBL_ = { 0.0f, 0.0f, 0.0f };
		ColorRGB rectangleColorBR_ = { 0.0f, 0.0f, 0.0f };
};

#endif