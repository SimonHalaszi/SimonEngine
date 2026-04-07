#ifndef DRAW_FUNCTIONS_HPP
#define DRAW_FUNCTIONS_HPP

#include <GL/glut.h>
#include <GL/freeglut.h>

#include <iostream>
#include <string>

#include "Utilities.hpp"
#include "Sprite.hpp"

// Functions for drawing shapes, sprites, images, etc

// Drawing a square
void drawSquare(
	Vector2D pos,
	float size, 
	float angle, 
	bool mirror,
	bool flip,
	ColorRGB c1 = { 1.0f, 1.0f, 1.0f },
	ColorRGB c2 = { 1.0f, 1.0f, 1.0f },
	ColorRGB c3 = { 1.0f, 1.0f, 1.0f },
	ColorRGB c4 = { 1.0f, 1.0f, 1.0f }
);

// Drawing a rectangle
void drawRectangle(
	Vector2D pos,
	Vector2D scale,
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
	Vector2D pos,
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
	Vector2D pos,
	Vector2D size,
	float angle, 
	bool mirror, 
	bool flip, 
	GLuint textureID
);

// Drawing a sprite
void drawSprite(
	Vector2D pos,
	Vector2D size,
	float angle,
	bool mirror,
	bool flip,
	Sprite sprite
);

// Drawing a line
void drawLine(
	Vector2D pos1,
	Vector2D pos2,
	ColorRGB c1, 
	ColorRGB c2
);

void drawText(
	Vector2D pos,
	std::string text,
	float lineSpace,
	ColorRGB color
);

void drawTextCentered(Vector2D centerPos, const std::string& text, float lineSpace, ColorRGB color);

#endif