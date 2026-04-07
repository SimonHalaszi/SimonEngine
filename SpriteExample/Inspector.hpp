#ifndef INSPECTOR_HPP
#define INSPECTOR_HPP

#include <GL/glut.h>
#include <GL/freeglut.h>

#include <vector>
#include <memory>
#include <iostream>

#include "GameObject2D.hpp"
#include "WindowConstants.hpp"
#include "DrawFunctions.hpp"

class Inspector {
	public:
		Inspector();

		void draw() const;
		void update();

		~Inspector();

	private:
		// GameObject currently selected
		GameObject2D* focusedGameObject_;
};

#endif