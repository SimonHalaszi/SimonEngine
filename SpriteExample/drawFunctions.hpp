#ifndef DRAWFUNCTIONS_HPP
#define DRAWFUNTION_HPP

#include <GL/glut.h>
#include <GL/freeglut.h>

#include <iostream>

#include "utilities.hpp"

// Function for drawing squares given a PositionXY, a size (float), and 4 ColorRGB for the vertices
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

// Function for drawing triangles given a PositionXY, a size (float), and 3 ColorRGB for the vertices
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

// Function for drawing a sprite given a PositionXY, a size (float), and a GLuint TextureID, and an optional SubTexture for tiling
void drawSprite(
	PositionXY pos, 
	float size, 
	float angle, 
	bool mirror, 
	bool flip, 
	GLuint textureID, 
	SubTexture subTexture = { 0.0f, 1.0f, 0.0f, 1.0f }
);

void drawLine(
	PositionXY pos1, 
	PositionXY pos2, 
	ColorRGB c1, 
	ColorRGB c2
);

void drawAxis(
	PositionXY pos1, 
	PositionXY pos2, 
	ColorRGB c1, 
	ColorRGB c2, 
	char axis
);

#endif // !DRAWFUNCTIONS_HPP