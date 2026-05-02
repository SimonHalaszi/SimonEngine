#ifndef SCENE_BUTTON_HPP
#define SCENE_BUTTON_HPP

#include <string>
#include <functional>

#include "Scene.hpp"
#include "DrawFunctions.hpp"
#include "InputManager.hpp"
#include "WindowConstants.hpp"
#include "SceneFactory.hpp"

class SceneButton {
public:
	SceneButton();
	SceneButton(
		const ViewportArea& viewportArea,
		const ColorRGB& color,
		const std::string& text
	);

	bool isInside(int mouseX, int mouseY, const ViewportContext& context) const;
	std::unique_ptr<Scene> handleClick(const ViewportContext& context) const;
	void draw() const;

private:
	ViewportArea viewportArea_;
	ColorRGB color_;
	std::string text_;
};

#endif