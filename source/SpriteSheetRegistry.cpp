#include "SpriteSheetRegistry.hpp"

const SpriteSheet& SpriteSheetRegistry::makeSpriteSheet(std::string nameOfSpriteSheet, GLuint texID, int tilesWide, int tilesTall, TileIndex startTile, TileIndex endTile) {
	if (spriteSheetMap_.find(nameOfSpriteSheet) != spriteSheetMap_.end()) {
		return spriteSheetMap_.at(nameOfSpriteSheet);
	}
	
	std::vector<Sprite> tiles;

	GLint texWidth = 0, texHeight = 0;
	glBindTexture(GL_TEXTURE_2D, texID);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &texWidth);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &texHeight);

	float tilePixelW = texWidth / (float)tilesWide;
	float tilePixelH = texHeight / (float)tilesTall;

	// Go through texture a tile at a time from starTile to and including endTile
	for (int y = startTile.y; y <= endTile.y; ++y) {
		for (int x = startTile.x; x <= endTile.x; ++x) {
			float u0 = (x * tilePixelW + 0.01f) / texWidth;
			float u1 = ((x + 1) * tilePixelW - 0.01f) / texWidth;

			float v0 = ((y + 1) * tilePixelH - 0.01f) / texHeight;
			float v1 = (y * tilePixelH + 0.01f) / texHeight;

			SubTexture temp;
			temp.u0 = u0;
			temp.u1 = u1;
			temp.v0 = 1.0f - v0;
			temp.v1 = 1.0f - v1;

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