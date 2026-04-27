#ifndef GAME_OBJECT_DRAW_FUNCTIONS_HPP
#define GAME_OBJECT_DRAW_FUNCTIONS_HPP

#include <GL/glut.h>
#include <GL/freeglut.h>

#include <iostream>
#include <string>

#include "Utilities.hpp"
#include "Sprite.hpp"

// Functions for drawing shapes, sprites, images, etc USING transforms

// Drawing a rectangle given a transform
void drawRectangleWithTransform(
	Transform2D transform,
	const ColorRGB& c1,
	const ColorRGB& c2,
	const ColorRGB& c3,
	const ColorRGB& c4
);

// Drawing an image
void drawImageWithTransform(
	Transform2D transform,
	const GLuint& textureID
);

// Drawing a sprite
void drawSpriteWithTransform(
	Transform2D transform,
	const Sprite& sprite
);

#endif