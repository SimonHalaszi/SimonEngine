#include "SpriteSheetRegistry.hpp"

const SpriteSheet& SpriteSheetRegistry::makeSpriteSheet(std::string nameOfSpriteSheet, GLuint texID, int tilesWide, int tilesTall, TileIndex startTile, TileIndex endTile) {
	if (spriteSheetMap_.find(nameOfSpriteSheet) != spriteSheetMap_.end()) {
		std::cout << "SpriteSheetRegistry::makeSpriteSheet : Will not create two sprite sheets with the same name try a different name instead of " << nameOfSpriteSheet << std::endl;
		return spriteSheetMap_.at(nameOfSpriteSheet);
	}
	
	std::vector<Sprite> tiles;

	// Go through texture a tile at a time from starTile to and including endTile
	for (int y = startTile.y; y <= endTile.y; ++y) {
		for (int x = startTile.x; x <= endTile.x; ++x) {
			SubTexture temp;

			// Calculating the left and right U texture coordinates
			temp.u0 = x / (float)tilesWide;
			temp.u1 = (x + 1) / (float)tilesWide;

			// Calculating the top and bottom V texture coordinates
			temp.v1 = 1.0f - y / (float)tilesTall;
			temp.v0 = 1.0f - (y + 1) / (float)tilesTall;

			Sprite sprite(texID, temp);

			// Add these tile coordinates
			tiles.push_back(sprite);
		}
	}

	std::cout << "SpriteSheetRegistry::makeSpriteSheet : Created " << tiles.size() << " sprite(s) for sprite sheet named " << nameOfSpriteSheet <<std::endl;

	SpriteSheet constructedSheet(tiles);

	spriteSheetMap_.insert({ nameOfSpriteSheet, constructedSheet });
	return spriteSheetMap_.at(nameOfSpriteSheet);
}

void SpriteSheetRegistry::removeSpriteSheet(std::string nameOfSpriteSheet) {
	if (spriteSheetMap_.find(nameOfSpriteSheet) != spriteSheetMap_.end()) {
		spriteSheetMap_.erase(nameOfSpriteSheet);
	}
}

const SpriteSheet& SpriteSheetRegistry::getSpriteSheet(std::string nameOfSpriteSheet) const {
	if (spriteSheetMap_.find(nameOfSpriteSheet) != spriteSheetMap_.end()) {
		return spriteSheetMap_.at(nameOfSpriteSheet);
	}
	else {
		std::cout << "SpriteSheetRegistry::getSpriteSheet : Couldnt get sprite sheet " << nameOfSpriteSheet << std::endl;
		return errorSpriteSheet_;
	}
}