#ifndef TEXTURE_REGISTRY_HPP
#define TEXTURE_REGISTRY_HPP

#include <GL/glut.h>
#include <GL/freeglut.h>
#include <FreeImage/FreeImage.h>

#include <unordered_map>
#include <string>
#include <iostream>

// Registry for textures

// Using very epic and awesome design patterns to make Nesty proud

// Not singletons because in the future I plan on every scene managing its own registries. But right now scenes arent added
class TextureRegistry {
	public:
		TextureRegistry() {}

		GLuint loadTexture(std::string filepath);
		void unloadTexture(std::string filepath);

		GLuint getTextureID(std::string filepath) const;

		~TextureRegistry() {
			for (auto& pair : textureMap_) {
				glDeleteTextures(1, &pair.second);
			}
		}

	private:
		// Registry
		std::unordered_map<std::string, GLuint> textureMap_;
};

#endif
