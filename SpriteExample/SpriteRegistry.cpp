#include "SpriteRegistry.hpp"

std::unordered_map<std::string, Sprite> SpriteRegistry::spriteMap_ = {};

const Sprite& SpriteRegistry::makeSprite(std::string nameOfSprite, GLuint texID, int tilesWide, int tilesTall, TileIndex tile) {
	if (spriteMap_.find(nameOfSprite) != spriteMap_.end()) {
		std::cout << "SpriteRegistry::makeSprite : Will not create two sprites with the same name try a different name instead of " << nameOfSprite << std::endl;
		return spriteMap_.at(nameOfSprite);
	}
	
	// Go through texture a tile at a time from starTile to and including endTile
	SubTexture temp;

	// Calculating the left and right U texture coordinates
	temp.u0 = tile.x / (float)tilesWide;
	temp.u1 = (tile.x + 1) / (float)tilesWide;

	// Calculating the top and bottom V texture coordinates
	temp.v1 = 1.0f - tile.y / (float)tilesTall;
	temp.v0 = 1.0f - (tile.y + 1) / (float)tilesTall;

	std::cout << "SpriteRegistry::makeSprite : Created sprite named " << nameOfSprite << std::endl;

	spriteMap_.insert({ nameOfSprite, {texID, temp} });
	return spriteMap_.at(nameOfSprite);
}

void SpriteRegistry::removeSprite(std::string nameOfSprite) {
	if (spriteMap_.find(nameOfSprite) != spriteMap_.end()) {
		spriteMap_.erase(nameOfSprite);
	}
}

const Sprite& SpriteRegistry::getSprite(std::string nameOfSprite) const {
	if (spriteMap_.find(nameOfSprite) != spriteMap_.end()) {
		return spriteMap_.at(nameOfSprite);
	}
	else {
		std::cout << "SpriteRegistry::getSprite : Couldnt get sprite " << nameOfSprite << std::endl;
		return errorSprite_;
	}
}