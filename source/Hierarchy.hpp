#ifndef HIERARCHY_HPP
#define HIERARCHY_HPP

#include <GL/glut.h>
#include <GL/freeglut.h>

#include <vector>
#include <memory>
#include <iostream>
#include <functional>

#include "GameObject2D.hpp"
#include "WindowConstants.hpp"
#include "DrawFunctions.hpp"
#include "InputManager.hpp"
#include "HierarchyButton.hpp"

class Hierarchy {
	public:
		Hierarchy(std::vector<std::unique_ptr<GameObject2D>>* rootObjects);
		
		void draw() const;
		void update(
			const std::function<void(GameObject2D*)>& onObjectDeleted,
			const std::function<void(GameObject2D*, int, int)>& onObjectReordered
		);
		void resetToRoot();

		~Hierarchy();

		void setFocusedGameObject(GameObject2D* focusedGameObject);
		GameObject2D* focusedGameObject() const { return focusedGameObject_; }
		std::vector<std::unique_ptr<GameObject2D>>* getActiveHierarchyVector() const { return hierarchyObjects_; }
		GameObject2D* getParentOfCurrentView() const { return parentOfCurrentView_; }
	
	private:
		void establishHierarchyButtons();

		// Actual objects in hierarchy
		std::vector<std::unique_ptr<GameObject2D>>* hierarchyObjects_;
		// Always points to rootObjects_
		std::vector<std::unique_ptr<GameObject2D>>* rootObjects_;

		// Buttons
		std::vector<HierarchyButton> hierarchyButtons_;

		// GameObject currently selected
		GameObject2D* focusedGameObject_;
		int focusedGameObjectIndex_;

		// Parent of the current hierarchy level (nullptr when viewing root)
		GameObject2D* parentOfCurrentView_;

		// Flag for if editor is speficially editing a game object and that view should be rendered over scene
		bool gameObjectSpecificView_;

		// Y for scrolling
		float hierarchyY_;

		// For drawing hierarchyTitle
		ViewportArea hierarchyTitle_;

		// Viewport Context used for Hierarchy
		ViewportContext hierarchyContext_;

		// Used to check if current hierarchyButtons are out of date
		size_t lastKnownSizeOfHierarchyObjects_;
};

#endif