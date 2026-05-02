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
	const Vector2D& pos,
	const float& size, 
	const float& angle,
	const bool& mirror,
	const bool& flip,
	const ColorRGB& colorTL,
	const ColorRGB& colorTR,
	const ColorRGB& colorBL,
	const ColorRGB& colorBR
);

// Drawing a rectangle
void drawRectangle(
	const Vector2D& pos,
	const Vector2D& scale,
	const float& angle,
	const bool& mirror,
	const bool& flip,
	const ColorRGB& colorTL,
	const ColorRGB& colorTR,
	const ColorRGB& colorBL,
	const ColorRGB& colorBR
);

// Drawing a triangle
void drawTriangle(
	const Vector2D& pos,
	const float& size,
	const float& angle,
	const bool& mirror,
	const bool& flip,
	const ColorRGB& colorT,
	const ColorRGB& colorBL,
	const ColorRGB& colorBR
);

// Drawing an image
void drawImage(
	const Vector2D& pos,
	const Vector2D& size,
	const float& angle,
	const bool& mirror,
	const bool& flip,
	const GLuint& textureID
);

// Drawing a sprite
void drawSprite(
	const Vector2D& pos,
	const Vector2D& size,
	const float& angle,
	const bool& mirror,
	const bool& flip,
	const Sprite& sprite
);

// Drawing a line
void drawLine(
	const Vector2D& pos1,
	const Vector2D& pos2,
	const ColorRGB& c1,
	const ColorRGB& c2
);

void drawText(
	const Vector2D& pos,
	const std::string& text,
	const float& lineSpace,
	const ColorRGB& color
);

void drawTextCentered(
	const Vector2D& pos,
	const std::string& text,
	const float& lineSpace,
	const ColorRGB& color
);

// Functions for drawing shapes, sprites, images, etc USING transforms

// Drawing a rectangle given a transform
void drawRectangleWithTransform(
	const Transform2D& worldTransform,
	const ColorRGB& colorTL,
	const ColorRGB& colorTR,
	const ColorRGB& colorBL,
	const ColorRGB& colorBR
);

// Drawing an image
void drawImageWithTransform(
	const Transform2D& worldTransform,
	const GLuint& textureID
);

// Drawing a sprite
void drawSpriteWithTransform(
	const Transform2D& worldTransform,
	const Sprite& sprite
);

#endif