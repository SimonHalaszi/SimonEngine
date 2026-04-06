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

class Hierarchy {
	public:
		Hierarchy(std::vector<std::unique_ptr<GameObject2D>>& rootObjects);
		
		void draw() const;
		void update();

		~Hierarchy();
	
	private:
		// Scene root objects
		std::vector<std::unique_ptr<GameObject2D>>& rootObjects_;

		// GameObject currently selected
		GameObject2D* focusedGameObject_;

		// Flag for if editor is speficially editing a game object and that view should be rendered over scene
		bool gameObjectSpecificView_;
};

#endif