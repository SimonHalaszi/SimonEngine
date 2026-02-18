#ifndef SPRITE_REGISTRY_HPP
#define SPRITE_REGISTRY_HPP

#include <GL/glut.h>
#include <GL/freeglut.h>

#include <unordered_map>
#include <iostream>
#include <string>

#include "Sprite.hpp"
#include "Utilities.hpp"

// Using very epic and awesome design patterns to make Nesty proud
class SpriteRegistry {
public:

	static SpriteRegistry& getInstance() {
		static SpriteRegistry instance;
		return instance;
	}

	const Sprite& makeSprite(std::string nameOfSprite, GLuint texID, int tilesWide, int tilesTall, TileIndex tile);
	void removeSprite(std::string nameOfSprite);

	const Sprite& getSprite(std::string nameOfSprite) const;

	SpriteRegistry(const SpriteRegistry&) = delete;
	SpriteRegistry& operator=(const SpriteRegistry&) = delete;
	SpriteRegistry(const SpriteRegistry&&) = delete;
	SpriteRegistry& operator=(const SpriteRegistry&&) = delete;

private:
	SpriteRegistry() 
		: errorSprite_(GLuint(0), {0.0f, 0.0f, 0.0f, 0.0f})
	{}

	~SpriteRegistry() {}

	// Registry
	static std::unordered_map<std::string, Sprite> spriteMap_;

	Sprite errorSprite_;
};

#endif
