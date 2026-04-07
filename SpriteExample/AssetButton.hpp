#ifndef ASSET_BUTTON_HPP
#define ASSET_BUTTON_HPP

#include <string>
#include <functional>

#include "Utilities.hpp"
#include "DrawFunctions.hpp"
#include "InputManager.hpp"
#include "WindowConstants.hpp"
#include "AssetFactory.hpp"

class AssetButton {
public:
	AssetButton();
	AssetButton(
		const ViewportArea& viewportArea,
		const ColorRGB& color,
		const std::string& text,
		const Sprite* previewSprite
	);

	bool isInside(int mouseX, int mouseY, const ViewportContext& context) const;
	std::unique_ptr<GameObject2D> handleClick(const ViewportContext& context) const;
	void draw() const;

private:
	ViewportArea viewportArea_;
	ColorRGB color_;
	std::string text_;
	
	const Sprite* previewSprite_;
};

#endif