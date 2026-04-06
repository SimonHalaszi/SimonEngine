#ifndef TOP_PANEL_HPP
#define TOP_PANEL_HPP

#include <GL/glut.h>
#include <GL/freeglut.h>

#include <vector>
#include <iostream>

#include "WindowConstants.hpp"
#include "drawFunctions.hpp"
#include "VoidButton.hpp"
#include "InputManager.hpp"

class TopPanel {
public:
	TopPanel();

	void draw() const;
	void update();

	bool markedForQuiting() const { return markedForQuiting_; }

	void menuButtonAction();
	void helpButtonAction();
	void quitButtonAction();
	void controlsButtonAction();
	void aboutButtonsAction();
	void supportButtonAction();

private:
	VoidButton menuButton_;
	VoidButton helpButton_;

	bool menuDropActive_ = false;
	bool markedForQuiting_ = false;
	std::vector<VoidButton> menuDropButtons_;
	bool helpDropActive_ = false;
	std::vector<VoidButton> helpDropButtons_;
};

#endif