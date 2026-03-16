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
class SpriteRegistry {
	public:
		static SpriteRegistry& getInstance() {
			static SpriteRegistry instance;
			return instance;
		}

		const Sprite& makeSprite(std::string nameOfSprite, GLuint texID, int tilesWide, int tilesTall, TileIndex tile);
		void removeSprite(std::string nameOfSprite);

		void clearRegistry() {
			std::cout << "SpriteRegistry::clearRegistry : Clearing " << spriteMap_.size() << " sprites" << std::endl;
			for (auto& pair : spriteMap_) {
				std::cout << "SpriteRegistry::clearRegistry : Removing sprite '" << pair.first << "' with texture ID " << pair.second.getTextureID() << std::endl;
			}
			spriteMap_.clear();
			std::cout << "SpriteRegistry::clearRegistry : Cleared" << std::endl;
		}

		const Sprite& getSprite(std::string nameOfSprite) const;

		SpriteRegistry(const SpriteRegistry&) = delete;
		SpriteRegistry& operator=(const SpriteRegistry&) = delete;
		SpriteRegistry(const SpriteRegistry&&) = delete;
		SpriteRegistry& operator=(const SpriteRegistry&&) = delete;

	private:
		SpriteRegistry()
			: errorSprite_(GLuint(0), { 0.0f, 0.0f, 0.0f, 0.0f })
		{
		}

		~SpriteRegistry() {}

		// Registry
		std::unordered_map<std::string, Sprite> spriteMap_;
		Sprite errorSprite_;  // Will signify an error in the process, should work nicely even if you dont check because TexID is 0
};

#endif
