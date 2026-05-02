#ifndef SCENE_PANEL_HPP
#define SCENE_PANEL_HPP

#include <GL/glut.h>
#include <GL/freeglut.h>

#include "WindowConstants.hpp"
#include "DrawFunctions.hpp"
#include "SceneButton.hpp"
#include "Scene.hpp"

#include <vector>

class ScenePanel {
public:
	ScenePanel();

	void draw() const;
	void update();

private:
	// Viewport Context used for AssetPanel
	ViewportContext scenePanelContext_;
	// For drawing assetPanelTitle
	ViewportArea scenePanelTitle_;

	std::vector<SceneButton> sceneButtons_;

};

#endif