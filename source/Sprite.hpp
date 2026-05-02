#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <GL/glut.h>
#include <GL/freeglut.h>

#include <vector>

#include "Utilities.hpp"

// Simple sprite class
class Sprite {
	public:
		Sprite() : texID_(0), uv_({0.0f, 1.0f, 0.0f, 1.0f}) {}
		Sprite(GLuint texID, SubTexture uv) : texID_(texID), uv_(uv) {}

		const GLuint& getTextureID() const { return texID_;  }
		const SubTexture& getUV() const { return uv_; }

	private:
		const GLuint texID_; // ID of texture this sprite pulls from
		const SubTexture uv_; // UV coordinates of the sprite
};

#endif