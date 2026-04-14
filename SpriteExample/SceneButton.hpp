#ifndef SCENE_BUTTON_HPP
#define SCENE_BUTTON_HPP

#include <string>
#include <functional>

#include "Utilities.hpp"
#include "DrawFunctions.hpp"
#include "InputManager.hpp"
#include "WindowConstants.hpp"

class SceneButton {
public:
	SceneButton();
	SceneButton(
		const ViewportArea& viewportArea,
		const ColorRGB& color,
		const std::string& text
	);

	bool isInside(int mouseX, int mouseY, const ViewportContext& context) const;
	virtual void handleClick(const ViewportContext& context) const = 0;
	void draw() const;

private:
	ViewportArea viewportArea_;
	ColorRGB color_;
	std::string text_;
};

// Add scenes as needed

class GameOverScreenSceneButton : public SceneButton {
public:
	GameOverScreenSceneButton();
	GameOverScreenSceneButton(
		const ViewportArea& viewportArea,
		const ColorRGB& color,
		const std::string& text
	);

	void handleClick(const ViewportContext& context) const override;
};

class GameWonScreenSceneButton : public SceneButton {
public:
	GameWonScreenSceneButton();
	GameWonScreenSceneButton(
		const ViewportArea& viewportArea,
		const ColorRGB& color,
		const std::string& text
	);

	void handleClick(const ViewportContext& context) const override;
};

class PlatformerSceneButton : public SceneButton {
public:
	PlatformerSceneButton();
	PlatformerSceneButton(
		const ViewportArea& viewportArea,
		const ColorRGB& color,
		const std::string& text
	);

	void handleClick(const ViewportContext& context) const override;
};

class TitleScreenSceneButton : public SceneButton {
public:
	TitleScreenSceneButton();
	TitleScreenSceneButton(
		const ViewportArea& viewportArea,
		const ColorRGB& color,
		const std::string& text
	);

	void handleClick(const ViewportContext& context) const override;
};

#endif