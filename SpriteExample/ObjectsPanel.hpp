#ifndef OBJECTS_PANEL_HPP
#define OBJECTS_PANEL_HPP

#include <GL/glut.h>
#include <GL/freeglut.h>

#include "WindowConstants.hpp"
#include "drawFunctions.hpp"
#include "GameObjectFactory.hpp"

class ObjectsPanel {
public:
	ObjectsPanel();

	void draw() const;
	void update();

private:

};

#endif