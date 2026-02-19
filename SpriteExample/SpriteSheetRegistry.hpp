#ifndef SPRITE_SHEET_REGISTRY_HPP
#define SPRITE_SHEET_REGISTRY_HPP

#include <GL/glut.h>
#include <GL/freeglut.h>

#include <unordered_map>
#include <iostream>
#include <string>

#include "Sprite.hpp"
#include "SpriteSheet.hpp"
#include "Utilities.hpp"

// Registry for sprite sheets.

// Using very epic and awesome design patterns to make Nesty proud
class SpriteSheetRegistry {
public:
	SpriteSheetRegistry()
		: errorSpriteSheet_({ Sprite(GLuint(0), { 0.0f, 0.0f, 0.0f, 0.0f }) })
	{}

	~SpriteSheetRegistry() {}

	const SpriteSheet& makeSpriteSheet(std::string nameOfSpriteSheet, GLuint texID, int tilesWide, int tilesTall, TileIndex startTile, TileIndex endTile);
	void removeSpriteSheet(std::string nameOfSpriteSheet);

	const SpriteSheet& getSpriteSheet(std::string nameOfSpriteSheet) const;

private:

	// Registry
	std::unordered_map<std::string, SpriteSheet> spriteSheetMap_;

	SpriteSheet errorSpriteSheet_; // Will signify an error in the process, should work nicely even if you dont check because TexID is 0
};

#endif
