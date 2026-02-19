#ifndef SPRITE_SHEET_HPP
#define SPRITE_SHEET_HPP

#include <GL/glut.h>
#include <GL/freeglut.h>

#include <vector>

#include "Utilities.hpp"
#include "Sprite.hpp"

// Simple sprite sheet class, ong adapter design pattern Nesty should be proud
class SpriteSheet {
public:
	SpriteSheet() : sheet_() {}
	SpriteSheet(const std::vector<Sprite> sheet) : sheet_(sheet) {}

	const std::vector<Sprite>& getSheet() const { return sheet_; }
	int spriteCount() const { return sheet_.size();  }

	// Same thing different story
	Sprite operator[](int i) const { return sheet_[i]; }
	Sprite getSpriteAt(int i) const { return sheet_[i]; }
private:
	std::vector<Sprite> sheet_; // Internal data structure
};

#endif