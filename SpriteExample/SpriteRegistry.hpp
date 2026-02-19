#ifndef SPRITE_REGISTRY_HPP
#define SPRITE_REGISTRY_HPP

#include <GL/glut.h>
#include <GL/freeglut.h>

#include <unordered_map>
#include <iostream>
#include <string>

#include "Sprite.hpp"
#include "Utilities.hpp"

// Registry for sprites. 

// Using very epic and awesome design patterns to make Nesty proud

// Not singletons because in the future I plan on every scene managing its own registries. But right now scenes arent added
class SpriteRegistry {
public:
	SpriteRegistry()
		: errorSprite_(GLuint(0), { 0.0f, 0.0f, 0.0f, 0.0f })
	{
	}

	~SpriteRegistry() {}

	const Sprite& makeSprite(std::string nameOfSprite, GLuint texID, int tilesWide, int tilesTall, TileIndex tile);
	void removeSprite(std::string nameOfSprite);

	const Sprite& getSprite(std::string nameOfSprite) const;

	SpriteRegistry(const SpriteRegistry&) = delete;
	SpriteRegistry& operator=(const SpriteRegistry&) = delete;
	SpriteRegistry(const SpriteRegistry&&) = delete;
	SpriteRegistry& operator=(const SpriteRegistry&&) = delete;

private:
	// Registry
	std::unordered_map<std::string, Sprite> spriteMap_;

	Sprite errorSprite_;  // Will signify an error in the process, should work nicely even if you dont check because TexID is 0
};

#endif
