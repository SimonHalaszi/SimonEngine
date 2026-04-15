#ifndef OBJECTS_PANEL_HPP
#define OBJECTS_PANEL_HPP

#include <GL/glut.h>
#include <GL/freeglut.h>

#include "WindowConstants.hpp"
#include "DrawFunctions.hpp"
#include "AssetFactory.hpp"
#include "AssetButton.hpp"
#include "Scene.hpp"

#include <vector>

class AssetPanel {
public:
	AssetPanel(Scene* scene);

	void draw() const;
	void update(std::vector<std::unique_ptr<GameObject2D>>* hierarchyObjects_, GameObject2D* parentOfCurrentView);

private:
	Scene* scene_;

	// Viewport Context used for AssetPanel
	ViewportContext assetPanelContext_;
	// For drawing assetPanelTitle
	ViewportArea assetPanelTitle_;

	std::vector<AssetButton> assetButtons_;

};

#endif