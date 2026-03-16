#ifndef UI_TEXT_ELEMENT_HPP
#define UI_TEXT_ELEMENT_HPP

#include <string>

#include "GameObject2D.hpp"

#include "DrawFunctions.hpp"
#include "utilities.hpp"

// UI GameObjects will be drawn relative to camera space. So be smart when initializing their transform2D
class UITextElement : public GameObject2D {
public:
	UITextElement(Transform2D transform2D, std::string text, ColorRGB textColor, ColorRGB rectangleColor);

	void onStart() override {}
	void draw() override final;
	void update() override {}
	void onDestruction() override {}

protected:
	std::string text_;
	ColorRGB textColor_;
	ColorRGB rectangleColor_;

	bool drawElement_ = true;
};

#endif