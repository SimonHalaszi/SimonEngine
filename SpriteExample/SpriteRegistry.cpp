#include "SpriteRegistry.hpp"

const Sprite& SpriteRegistry::makeSprite(std::string nameOfSprite, GLuint texID, int tilesWide, int tilesTall, TileIndex tile) {
	if (spriteMap_.find(nameOfSprite) != spriteMap_.end()) {
		std::cout << "SpriteRegistry::makeSprite : Will not create two sprites with the same name try a different name instead of " << nameOfSprite << std::endl;
		return spriteMap_.at(nameOfSprite);
	}
	
	GLint texWidth = 0, texHeight = 0;
	glBindTexture(GL_TEXTURE_2D, texID);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &texWidth);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &texHeight);

	float tilePixelW = texWidth / (float)tilesWide;
	float tilePixelH = texHeight / (float)tilesTall;

	float u0 = (tile.x * tilePixelW + 0.01f) / texWidth;
	float u1 = ((tile.x + 1) * tilePixelW - 0.01f) / texWidth;

	float v0 = ((tile.y + 1) * tilePixelH - 0.01f) / texHeight;
	float v1 = (tile.y * tilePixelH + 0.01f) / texHeight;

	SubTexture temp;
	temp.u0 = u0;
	temp.u1 = u1;
	temp.v0 = 1.0f - v0;
	temp.v1 = 1.0f - v1;

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