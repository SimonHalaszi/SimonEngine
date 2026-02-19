#ifndef DRAW_FUNCTIONS_HPP
#define DRAW_FUNCTIONS_HPP

#include <GL/glut.h>
#include <GL/freeglut.h>

#include <iostream>

#include "Utilities.hpp"
#include "Sprite.hpp"

// Functions for drawing shapes, sprites, images, etc

// Drawing a square
void drawSquare(
	PositionXY pos, 
	float size, 
	float angle, 
	bool mirror,
	bool flip,
	ColorRGB c1 = { 1.0f, 1.0f, 1.0f },
	ColorRGB c2 = { 1.0f, 1.0f, 1.0f },
	ColorRGB c3 = { 1.0f, 1.0f, 1.0f },
	ColorRGB c4 = { 1.0f, 1.0f, 1.0f }
);

// Drawing a triangle
void drawTriangle(
	PositionXY pos, 
	float size, 
	float angle, 
	bool mirror,
	bool flip,
	ColorRGB c1 = { 1.0f, 1.0f, 1.0f },
	ColorRGB c2 = { 1.0f, 1.0f, 1.0f },
	ColorRGB c3 = { 1.0f, 1.0f, 1.0f }
);

// Drawing an image
void drawImage(
	PositionXY pos, 
	float size, 
	float angle, 
	bool mirror, 
	bool flip, 
	GLuint textureID
);

// Drawing a sprite
void drawSprite(
	PositionXY pos,
	float size,
	float angle,
	bool mirror,
	bool flip,
	Sprite sprite
);

// Drawing a line
void drawLine(
	PositionXY pos1, 
	PositionXY pos2, 
	ColorRGB c1, 
	ColorRGB c2
);

// Drawing an axis
void drawAxis(
	PositionXY pos1, 
	PositionXY pos2, 
	ColorRGB c1, 
	ColorRGB c2, 
	char axis
);

#endif