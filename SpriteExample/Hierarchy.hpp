#ifndef HIERARCHY_HPP
#define HIERARCHY_HPP

#include <GL/glut.h>
#include <GL/freeglut.h>

#include <vector>
#include <memory>
#include <iostream>

#include "GameObject2D.hpp"
#include "WindowConstants.hpp"
#include "drawFunctions.hpp"
#include "InputManager.hpp"
#include "HierarchyButton.hpp"

class Hierarchy {
	public:
		Hierarchy(std::vector<std::unique_ptr<GameObject2D>>& rootObjects);
		
		void draw() const;
		void update();

		~Hierarchy();

		GameObject2D* focusedGameObject() const { return focusedGameObject_; }
	
	private:
		void establishHierarchyButtons();

		// Scene root objects
		std::vector<std::unique_ptr<GameObject2D>>& rootObjects_;

		// Buttons
		std::vector<HierarchyButton> hierarchyButtons_;

		// GameObject currently selected
		GameObject2D* focusedGameObject_;
		int focusedGameObjectIndex_;

		// Flag for if editor is speficially editing a game object and that view should be rendered over scene
		bool gameObjectSpecificView_;

		// Y for scrolling
		float hierarchyY_;

		// For drawing hierarchyTitle
		ViewportArea hierarchyTitle_;

		// Viewport Context used for Hierarchy
		ViewportContext hierarchyContext_;

		// Used to check if current hierarchyButtons are out of date
		size_t lastKnownSizeOfRootObjects_;
};

#endif