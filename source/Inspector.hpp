#ifndef INSPECTOR_HPP
#define INSPECTOR_HPP

#include <GL/glut.h>
#include <GL/freeglut.h>

#include <vector>
#include <memory>
#include <iostream>
#include <functional>

#include "GameObject2D.hpp"
#include "WindowConstants.hpp"
#include "DrawFunctions.hpp"
#include "IFieldButton.hpp"
#include "IField.hpp"

class Inspector {
	public:
		Inspector();

		void setFocusedGameObject(GameObject2D* focusedGameObject);
		void draw() const;
		void update(const std::function<void(GameObject2D*)>& onObjectChanged);
		void clearFocus();

		~Inspector();

	private:
		void establishIFieldButtons();

		// GameObject currently selected
		GameObject2D* focusedGameObject_;

		std::vector<std::unique_ptr<IField>>* iFields_;
		std::vector<std::unique_ptr<IFieldButton>> iFieldButtons_;

		// For drawing inspectorTitle
		ViewportArea inspectorTitle_;

		// Viewport Context used for Inspector
		ViewportContext inspectorContext_;
};

#endif